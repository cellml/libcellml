/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "generatorinterpreter.h"

#include <iterator>

#include "libcellml/analyserequation.h"
#include "libcellml/analyserequationast.h"
#include "libcellml/analyservariable.h"

#include "commonutils.h"
#include "generatorinterpreter_p.h"
#include "interpreteraststatement.h"
#include "interpreteraststatement_p.h"
#include "utilities.h"

#include "libcellml/undefines.h"

namespace libcellml {

GeneratorInterpreter::GeneratorInterpreterImpl::GeneratorInterpreterImpl(const AnalyserModelPtr &model,
                                                                         const GeneratorProfilePtr &profile,
                                                                         const std::string &code)
{
    initialise(model, profile, code);
}

GeneratorInterpreter::GeneratorInterpreterImpl::GeneratorInterpreterImpl(const AnalyserModelPtr &model)
{
    initialise(model, mProfile, mCode);
}

GeneratorInterpreter::GeneratorInterpreterImpl::GeneratorInterpreterImpl(const AnalyserEquationAstPtr &ast,
                                                                         const GeneratorProfilePtr &profile)
{
    if (profile != nullptr) {
        mProfile = profile;
    }

    auto [code, dummyAstStatement] = generateCode(ast);

    mCode = code;
}

void GeneratorInterpreter::GeneratorInterpreterImpl::initialise(const AnalyserModelPtr &model,
                                                                const GeneratorProfilePtr &profile,
                                                                const std::string &code)
{
    mModel = model;
    mModelHasOdes = modelHasOdes(model);
    mModelHasNlas = modelHasNlas(model);
    mProfile = profile;
    mCode = code;

    // Add code for solving the NLA systems.

    nlaSystems();

    // Add code for the implementation to initialise our variables.

    auto equations = mModel->equations();
    std::vector<AnalyserEquationPtr> remainingEquations {std::begin(equations), std::end(equations)};

    initialiseVariables(remainingEquations);

    mInitialiseVariablesAstStatements = mAstStatements;

    // Add code for the implementation to compute our computed constants.

    mAstStatements.clear();

    computeComputedConstants(remainingEquations);

    mComputeComputedConstantsAstStatements = mAstStatements;

    // Add code for the implementation to compute our rates (and any variables
    // on which they depend).

    mAstStatements.clear();

    computeRates(remainingEquations);

    mComputeRatesAstStatements = mAstStatements;

    // Add code for the implementation to compute our variables.
    // Note: this method computes the remaining variables, i.e. the ones not needed to compute our rates, but also the
    //       variables that depend on the value of some states/rates and all the external variables. This method is
    //       typically called after having integrated a model, thus ensuring that variables that rely on the value of
    //       some states/rates are up to date.

    mAstStatements.clear();

    computeVariables(remainingEquations);

    mComputeVariablesAstStatements = mAstStatements;
}

bool modelHasOdes(const AnalyserModelPtr &model)
{
    switch (model->type()) {
    case AnalyserModel::Type::ODE:
    case AnalyserModel::Type::DAE:
        return true;
    default:
        return false;
    }
}

bool modelHasNlas(const AnalyserModelPtr &model)
{
    switch (model->type()) {
    case AnalyserModel::Type::NLA:
    case AnalyserModel::Type::DAE:
        return true;
    default:
        return false;
    }
}

AnalyserVariablePtr analyserVariable(const AnalyserModelPtr &model, const VariablePtr &variable)
{
    // Make sure that we have a model.

    if (model == nullptr) {
        return nullptr;
    }

    // Find and return the analyser variable associated with the given variable.

    AnalyserVariablePtr res;
    auto modelVoi = model->voi();
    auto modelVoiVariable = (modelVoi != nullptr) ? modelVoi->variable() : nullptr;

    if ((modelVoiVariable != nullptr)
        && model->areEquivalentVariables(variable, modelVoiVariable)) {
        res = modelVoi;
    } else {
        for (const auto &modelState : model->states()) {
            if (model->areEquivalentVariables(variable, modelState->variable())) {
                res = modelState;

                break;
            }
        }

        if (res == nullptr) {
            // Normally, we would have:
            //
            //     for (const auto &modelVariable : model->variables()) {
            //         if (model->areEquivalentVariables(variable, modelVariable->variable())) {
            //             res = modelVariable;
            //
            //             break;
            //         }
            //     }
            //
            // but we always have variables, so llvm-cov will complain that the
            // false branch of our for loop is never reached. The below code is
            // a bit more verbose but at least it makes llvm-cov happy.

            auto modelVariables = model->variables();
            auto modelVariable = modelVariables.begin();

            do {
                if (model->areEquivalentVariables(variable, (*modelVariable)->variable())) {
                    res = *modelVariable;
                } else {
                    ++modelVariable;
                }
            } while (res == nullptr);
        }
    }

    return res;
}

double GeneratorInterpreter::GeneratorInterpreterImpl::scalingFactor(const VariablePtr &variable) const
{
    // Return the scaling factor for the given variable.

    return Units::scalingFactor(variable->units(), analyserVariable(mModel, variable)->variable()->units());
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isNegativeNumber(const AnalyserEquationAstPtr &ast) const
{
    if (ast->type() == AnalyserEquationAst::Type::CN) {
        double doubleValue;

        convertToDouble(ast->value(), doubleValue);

        return doubleValue < 0.0;
    }

    return false;
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isRelationalOperator(const AnalyserEquationAstPtr &ast) const
{
    switch (ast->type()) {
    case AnalyserEquationAst::Type::EQ:
        return mProfile->hasEqOperator();
    case AnalyserEquationAst::Type::NEQ:
        return mProfile->hasNeqOperator();
    case AnalyserEquationAst::Type::LT:
        return mProfile->hasLtOperator();
    case AnalyserEquationAst::Type::LEQ:
        return mProfile->hasLeqOperator();
    case AnalyserEquationAst::Type::GT:
        return mProfile->hasGtOperator();
    case AnalyserEquationAst::Type::GEQ:
        return mProfile->hasGeqOperator();
    default:
        return false;
    }
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isAndOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::AND)
           && mProfile->hasAndOperator();
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isOrOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::OR)
           && mProfile->hasOrOperator();
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isXorOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::XOR)
           && mProfile->hasXorOperator();
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isLogicalOperator(const AnalyserEquationAstPtr &ast) const
{
    // Note: AnalyserEquationAst::Type::NOT is a unary logical operator, hence we don't include it here since this
    //       method is only used to determine whether parentheses should be added around some code.

    return isAndOperator(ast) || isOrOperator(ast) || isXorOperator(ast);
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isPlusOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::PLUS;
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isMinusOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::MINUS;
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isTimesOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::TIMES;
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isDivideOperator(const AnalyserEquationAstPtr &ast) const
{
    return ast->type() == AnalyserEquationAst::Type::DIVIDE;
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isPowerOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::POWER)
           && mProfile->hasPowerOperator();
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isRootOperator(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::ROOT)
           && mProfile->hasPowerOperator();
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isPiecewiseStatement(const AnalyserEquationAstPtr &ast) const
{
    return (ast->type() == AnalyserEquationAst::Type::PIECEWISE)
           && mProfile->hasConditionalOperator();
}

std::string newLineIfNotEmpty(const std::string &code)
{
    return code.empty() ? "" : "\n";
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateMethodBodyCode(const std::string &methodBody) const
{
    return methodBody.empty() ?
               (mProfile->emptyMethodString().empty() ?
                    "" :
                    mProfile->indentString() + mProfile->emptyMethodString()) :
               methodBody;
}

std::string generateDoubleCode(const std::string &value)
{
    if (value.find('.') != std::string::npos) {
        return value;
    }

    auto ePos = value.find('e');

    if (ePos == std::string::npos) {
        return value + ".0";
    }

    return value.substr(0, ePos) + ".0" + value.substr(ePos);
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateVariableNameCode(const VariablePtr &variable,
                                                                                     bool rate) const
{
    // Generate some code for a variable name, but only if we have a model. If we don't have a model, it means that we
    // are using the generator from the analyser, in which case we just want to return the original name of the
    // variable.

    if (mModel == nullptr) {
        return variable->name();
    }

    auto analyserVariable = libcellml::analyserVariable(mModel, variable);

    if (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) {
        return mProfile->voiString();
    }

    std::string arrayName;

    if (analyserVariable->type() == AnalyserVariable::Type::STATE) {
        arrayName = rate ?
                        mProfile->ratesArrayString() :
                        mProfile->statesArrayString();
    } else {
        arrayName = mProfile->variablesArrayString();
    }

    return arrayName + mProfile->openArrayString() + convertToString(analyserVariable->index()) + mProfile->closeArrayString();
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateOperatorCode(const std::string &op,
                                                                                 const AnalyserEquationAstPtr &ast,
                                                                                 const InterpreterAstStatementPtr &astStatement) const
{
    // Generate the code for the left and right branches of the given AST.

    std::string res;
    auto astLeftChild = ast->leftChild();
    auto astRightChild = ast->rightChild();
    auto [leftCode, leftAstStatement] = generateCode(astLeftChild);
    auto [rightCode, rightAstStatement] = generateCode(astRightChild);

    if (astStatement != nullptr) {
        astStatement->mPimpl->mLeftChild = leftAstStatement;
        astStatement->mPimpl->mRightChild = rightAstStatement;
    }

    // Determine whether parentheses should be added around the left and/or right piece of code, and this based on the
    // precedence of the operators used in CellML, which are listed below from higher to lower precedence:
    //  1. Parentheses                                           [Left to right]
    //  2. POWER (as an operator, not as a function, i.e.        [Left to right]
    //            as in Matlab and not in C, for example)
    //  3. Unary PLUS, Unary MINUS, NOT                          [Right to left]
    //  4. TIMES, DIVIDE                                         [Left to right]
    //  5. PLUS, MINUS                                           [Left to right]
    //  6. LT, LEQ, GT, GEQ                                      [Left to right]
    //  7. EQ, NEQ                                               [Left to right]
    //  8. XOR (bitwise)                                         [Left to right]
    //  9. AND (logical)                                         [Left to right]
    // 10. OR (logical)                                          [Left to right]
    // 11. PIECEWISE (as an operator)                            [Right to left]

    if (isPlusOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        }
    } else if (isMinusOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        }

        if (isNegativeNumber(astRightChild)
            || isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)
            || (rightCode.rfind(mProfile->minusString(), 0) == 0)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        }
    } else if (isTimesOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        }
    } else if (isDivideOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isTimesOperator(astRightChild)
            || isDivideOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        }
    } else if (isAndOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add parentheses around OR and PIECEWISE.
        //       However, it looks better/clearer to have some around some other operators (agreed, this is somewhat
        //       subjective).

        if (isRelationalOperator(astLeftChild)
            || isOrOperator(astLeftChild)
            || isXorOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        } else if (isPowerOperator(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isRootOperator(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isOrOperator(astRightChild)
            || isXorOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        } else if (isPowerOperator(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isRootOperator(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        }
    } else if (isOrOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add parentheses around PIECEWISE. However, it
        //       looks better/clearer to have some around some other operators (agreed, this is somewhat subjective).

        if (isRelationalOperator(astLeftChild)
            || isAndOperator(astLeftChild)
            || isXorOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        } else if (isPowerOperator(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isRootOperator(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isAndOperator(astRightChild)
            || isXorOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        } else if (isPowerOperator(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isRootOperator(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        }
    } else if (isXorOperator(ast)) {
        // Note: according to the precedence rules above, we only need to add parentheses around AND, OR and PIECEWISE.
        //       However, it looks better/clearer to have some around some other operators (agreed, this is somewhat
        //       subjective).

        if (isRelationalOperator(astLeftChild)
            || isAndOperator(astLeftChild)
            || isOrOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChild)
                   || isMinusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        } else if (isPowerOperator(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isRootOperator(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        }

        if (isRelationalOperator(astRightChild)
            || isAndOperator(astRightChild)
            || isOrOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)
                   || isMinusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        } else if (isPowerOperator(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isRootOperator(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        }
    } else if (isPowerOperator(ast)) {
        if (isRelationalOperator(astLeftChild)
            || isLogicalOperator(astLeftChild)
            || isMinusOperator(astLeftChild)
            || isTimesOperator(astLeftChild)
            || isDivideOperator(astLeftChild)
            || isPiecewiseStatement(astLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChild)) {
            if (astLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        }

        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astLeftChild)
            || isTimesOperator(astRightChild)
            || isDivideOperator(astRightChild)
            || isPowerOperator(astRightChild)
            || isRootOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        }
    } else if (isRootOperator(ast)) {
        if (isRelationalOperator(astRightChild)
            || isLogicalOperator(astRightChild)
            || isMinusOperator(astRightChild)
            || isTimesOperator(astRightChild)
            || isDivideOperator(astRightChild)
            || isPiecewiseStatement(astRightChild)) {
            rightCode = "(" + rightCode + ")";
        } else if (isPlusOperator(astRightChild)) {
            if (astRightChild->rightChild() != nullptr) {
                rightCode = "(" + rightCode + ")";
            }
        }

        auto astLeftChildLeftChild = astLeftChild->leftChild();

        if (isRelationalOperator(astLeftChildLeftChild)
            || isLogicalOperator(astLeftChildLeftChild)
            || isMinusOperator(astLeftChildLeftChild)
            || isTimesOperator(astLeftChildLeftChild)
            || isDivideOperator(astLeftChildLeftChild)
            || isPowerOperator(astLeftChildLeftChild)
            || isRootOperator(astLeftChildLeftChild)
            || isPiecewiseStatement(astLeftChildLeftChild)) {
            leftCode = "(" + leftCode + ")";
        } else if (isPlusOperator(astLeftChildLeftChild)) {
            if (astLeftChildLeftChild->rightChild() != nullptr) {
                leftCode = "(" + leftCode + ")";
            }
        }

        return rightCode + op + "(1.0/" + leftCode + ")";
    }

    return leftCode + op + rightCode;
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateMinusUnaryCode(const AnalyserEquationAstPtr &ast,
                                                                                   const InterpreterAstStatementPtr &astStatement) const
{
    // Generate the code for the left branch of the given AST.

    auto astLeftChild = ast->leftChild();
    auto [leftCode, leftAstStatement] = generateCode(astLeftChild);

    astStatement->mPimpl->mLeftChild = leftAstStatement;

    // Determine whether parentheses should be added around the left code.

    if (isRelationalOperator(astLeftChild)
        || isLogicalOperator(astLeftChild)
        || isPlusOperator(astLeftChild)
        || isMinusOperator(astLeftChild)
        || isPiecewiseStatement(astLeftChild)) {
        leftCode = "(" + leftCode + ")";
    }

    return mProfile->minusString() + leftCode;
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateOneParameterFunctionCode(const std::string &function,
                                                                                             const AnalyserEquationAstPtr &ast,
                                                                                             const InterpreterAstStatementPtr &astStatement) const
{
    auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

    if (astStatement != nullptr) {
        astStatement->mPimpl->mLeftChild = leftAstStatement;
    }

    return function + "(" + leftCode + ")";
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateTwoParameterFunctionCode(const std::string &function,
                                                                                             const AnalyserEquationAstPtr &ast,
                                                                                             const InterpreterAstStatementPtr &astStatement) const
{
    auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());
    auto [rightCode, rightAstStatement] = generateCode(ast->rightChild());

    if (astStatement != nullptr) {
        astStatement->mPimpl->mLeftChild = leftAstStatement;
        astStatement->mPimpl->mRightChild = rightAstStatement;
    }

    return function + "(" + leftCode + ", " + rightCode + ")";
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generatePiecewiseIfCode(const std::string &condition,
                                                                                    const std::string &value) const
{
    return replace(replace(mProfile->hasConditionalOperator() ?
                               mProfile->conditionalOperatorIfString() :
                               mProfile->piecewiseIfString(),
                           "[CONDITION]", condition),
                   "[IF_STATEMENT]", value);
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generatePiecewiseElseCode(const std::string &value) const
{
    return replace(mProfile->hasConditionalOperator() ?
                       mProfile->conditionalOperatorElseString() :
                       mProfile->piecewiseElseString(),
                   "[ELSE_STATEMENT]", value);
}

std::tuple<std::string, InterpreterAstStatementPtr> GeneratorInterpreter::GeneratorInterpreterImpl::generateCode(const AnalyserEquationAstPtr &ast) const
{
    // Make sure that we have an AST to work on.

    if (ast == nullptr) {
        return {};
    }

    // Generate the code for the given AST.
    // Note: AnalyserEquationAst::Type::BVAR is only relevant when there is no model (in which case we want to generate
    //       something like dx/dt, as is in the case of the analyser when we want to mention an equation) since
    //       otherwise we don't need to generate any code for it (since we will, instead, want to generate something
    //       like rates[0]).

    std::string code;
    InterpreterAstStatementPtr astStatement;

    switch (ast->type()) {
    case AnalyserEquationAst::Type::EQUALITY:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::EQUALITY);
        code = generateOperatorCode(mProfile->equalityString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::EQ:
        if (mProfile->hasEqOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::EQ);
            code = generateOperatorCode(mProfile->eqString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->eqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::NEQ:
        if (mProfile->hasNeqOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::NEQ);
            code = generateOperatorCode(mProfile->neqString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->neqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LT:
        if (mProfile->hasLtOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::LT);
            code = generateOperatorCode(mProfile->ltString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->ltString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::LEQ:
        if (mProfile->hasLeqOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::LEQ);
            code = generateOperatorCode(mProfile->leqString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->leqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GT:
        if (mProfile->hasGtOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::GT);
            code = generateOperatorCode(mProfile->gtString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->gtString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::GEQ:
        if (mProfile->hasGeqOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::GEQ);
            code = generateOperatorCode(mProfile->geqString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->geqString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::AND:
        if (mProfile->hasAndOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::AND);
            code = generateOperatorCode(mProfile->andString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->andString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::OR:
        if (mProfile->hasOrOperator()) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::OR);
            code = generateOperatorCode(mProfile->orString(), ast, astStatement);
        } else {
            code = generateTwoParameterFunctionCode(mProfile->orString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::XOR:
        if (mProfile->hasXorOperator()) {
            code = generateOperatorCode(mProfile->xorString(), ast);
        } else {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::XOR);
            code = generateTwoParameterFunctionCode(mProfile->xorString(), ast, astStatement);
        }

        break;
    case AnalyserEquationAst::Type::NOT:
        if (mProfile->hasNotOperator()) {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::NOT, leftAstStatement);
            code = mProfile->notString() + leftCode;
        } else {
            code = generateOneParameterFunctionCode(mProfile->notString(), ast);
        }

        break;
    case AnalyserEquationAst::Type::PLUS:
        if (ast->rightChild() != nullptr) {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::PLUS);
            code = generateOperatorCode(mProfile->plusString(), ast, astStatement);
        } else {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

            astStatement = leftAstStatement;
            code = leftCode;
        }

        break;
    case AnalyserEquationAst::Type::MINUS:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::MINUS);

        code = (ast->rightChild() != nullptr) ?
                   generateOperatorCode(mProfile->minusString(), ast, astStatement) :
                   generateMinusUnaryCode(ast, astStatement);

        break;
    case AnalyserEquationAst::Type::TIMES:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::TIMES);
        code = generateOperatorCode(mProfile->timesString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::DIVIDE:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::DIVIDE);
        code = generateOperatorCode(mProfile->divideString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::POWER: {
        auto [rightCode, rightAstStatement] = generateCode(ast->rightChild());
        double doubleValue;
        auto validConversion = convertToDouble(rightCode, doubleValue);

        if (validConversion && areEqual(doubleValue, 0.5)) {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SQUARE_ROOT,
                                                           leftAstStatement);
            code = mProfile->squareRootString() + "(" + leftCode + ")";
        } else if (validConversion && areEqual(doubleValue, 2.0)
                   && !mProfile->squareString().empty()) {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SQUARE,
                                                           leftAstStatement);
            code = mProfile->squareString() + "(" + leftCode + ")";
        } else if (mProfile->hasPowerOperator()) {
            code = generateOperatorCode(mProfile->powerString(), ast);
        } else {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::POWER,
                                                           leftAstStatement,
                                                           rightAstStatement);
            code = mProfile->powerString() + "(" + leftCode + ", " + rightCode + ")";
        }
    } break;
    case AnalyserEquationAst::Type::ROOT: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto astLeftChild = ast->leftChild();
            auto [leftCode, leftAstStatement] = generateCode(astLeftChild);
            double doubleValue;
            auto validConversion = convertToDouble(leftCode, doubleValue);

            if (validConversion && areEqual(doubleValue, 2.0)) {
                auto [rightCode, rightAstStatement] = generateCode(astRightChild);

                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SQUARE_ROOT,
                                                               rightAstStatement);
                code = mProfile->squareRootString() + "(" + rightCode + ")";
            } else if (validConversion && areEqual(doubleValue, 0.5)
                       && !mProfile->squareString().empty()) {
                auto [rightCode, rightAstStatement] = generateCode(astRightChild);

                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SQUARE,
                                                               rightAstStatement);
                code = mProfile->squareString() + "(" + rightCode + ")";
            } else if (mProfile->hasPowerOperator()) {
                code = generateOperatorCode(mProfile->powerString(), ast);
            } else {
                auto [rightCode, rightAstStatement] = generateCode(astRightChild);
                auto inverseValueAst = AnalyserEquationAst::create();
                auto inverseValueAstStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::DIVIDE);

                inverseValueAst->setType(AnalyserEquationAst::Type::DIVIDE);
                inverseValueAst->setParent(ast);

                auto inverseValueAstLeftChild = AnalyserEquationAst::create();

                inverseValueAstLeftChild->setType(AnalyserEquationAst::Type::CN);
                inverseValueAstLeftChild->setValue("1.0");
                inverseValueAstLeftChild->setParent(inverseValueAst);

                inverseValueAst->setLeftChild(inverseValueAstLeftChild);
                inverseValueAst->setRightChild(astLeftChild->leftChild());

                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::POWER,
                                                               rightAstStatement,
                                                               inverseValueAstStatement);
                code = mProfile->powerString() + "(" + rightCode + ", " + generateOperatorCode(mProfile->divideString(), inverseValueAst, inverseValueAstStatement) + ")";
            }
        } else {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SQUARE_ROOT,
                                                           leftAstStatement);
            code = mProfile->squareRootString() + "(" + leftCode + ")";
        }
    } break;
    case AnalyserEquationAst::Type::ABS:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ABS);
        code = generateOneParameterFunctionCode(mProfile->absoluteValueString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::EXP:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::EXP);
        code = generateOneParameterFunctionCode(mProfile->exponentialString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::LN:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::LN);
        code = generateOneParameterFunctionCode(mProfile->naturalLogarithmString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::LOG: {
        auto astRightChild = ast->rightChild();

        if (astRightChild != nullptr) {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());
            double doubleValue;
            auto [rightCode, rightAstStatement] = generateCode(astRightChild);

            if (convertToDouble(leftCode, doubleValue)
                && areEqual(doubleValue, 10.0)) {
                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::LOG,
                                                               rightAstStatement);
                code = mProfile->commonLogarithmString() + "(" + rightCode + ")";
            } else {
                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::DIVIDE,
                                                               InterpreterAstStatement::create(InterpreterAstStatement::Type::LN,
                                                                                               rightAstStatement),
                                                               InterpreterAstStatement::create(InterpreterAstStatement::Type::LN,
                                                                                               leftAstStatement));
                code = mProfile->naturalLogarithmString() + "(" + rightCode + ")/" + mProfile->naturalLogarithmString() + "(" + leftCode + ")";
            }
        } else {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::LOG);
            code = generateOneParameterFunctionCode(mProfile->commonLogarithmString(), ast, astStatement);
        }
    } break;
    case AnalyserEquationAst::Type::CEILING:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::CEILING);
        code = generateOneParameterFunctionCode(mProfile->ceilingString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::FLOOR:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::FLOOR);
        code = generateOneParameterFunctionCode(mProfile->floorString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::MIN:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::MIN);
        code = generateTwoParameterFunctionCode(mProfile->minString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::MAX:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::MAX);
        code = generateTwoParameterFunctionCode(mProfile->maxString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::REM:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::REM);
        code = generateTwoParameterFunctionCode(mProfile->remString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::DIFF:
        if (mModel != nullptr) {
            auto [rightCode, rightAstStatement] = generateCode(ast->rightChild());

            astStatement = rightAstStatement;
            code = rightCode;
        } else {
            auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());
            auto [rightCode, rightAstStatement] = generateCode(ast->rightChild());

            code = "d" + rightCode + "/d" + leftCode;
        }

        break;
    case AnalyserEquationAst::Type::SIN:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SIN);
        code = generateOneParameterFunctionCode(mProfile->sinString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::COS:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::COS);
        code = generateOneParameterFunctionCode(mProfile->cosString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::TAN:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::TAN);
        code = generateOneParameterFunctionCode(mProfile->tanString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::SEC:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SEC);
        code = generateOneParameterFunctionCode(mProfile->secString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::CSC:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::CSC);
        code = generateOneParameterFunctionCode(mProfile->cscString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::COT:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::COT);
        code = generateOneParameterFunctionCode(mProfile->cotString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::SINH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SINH);
        code = generateOneParameterFunctionCode(mProfile->sinhString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::COSH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::COSH);
        code = generateOneParameterFunctionCode(mProfile->coshString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::TANH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::TANH);
        code = generateOneParameterFunctionCode(mProfile->tanhString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::SECH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::SECH);
        code = generateOneParameterFunctionCode(mProfile->sechString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::CSCH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::CSCH);
        code = generateOneParameterFunctionCode(mProfile->cschString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::COTH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::COTH);
        code = generateOneParameterFunctionCode(mProfile->cothString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ASIN:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ASIN);
        code = generateOneParameterFunctionCode(mProfile->asinString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ACOS:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ACOS);
        code = generateOneParameterFunctionCode(mProfile->acosString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ATAN:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ATAN);
        code = generateOneParameterFunctionCode(mProfile->atanString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ASEC:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ASEC);
        code = generateOneParameterFunctionCode(mProfile->asecString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ACSC:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ACSC);
        code = generateOneParameterFunctionCode(mProfile->acscString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ACOT:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ACOT);
        code = generateOneParameterFunctionCode(mProfile->acotString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ASINH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ASINH);
        code = generateOneParameterFunctionCode(mProfile->asinhString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ACOSH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ACOSH);
        code = generateOneParameterFunctionCode(mProfile->acoshString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ATANH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ATANH);
        code = generateOneParameterFunctionCode(mProfile->atanhString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ASECH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ASECH);
        code = generateOneParameterFunctionCode(mProfile->asechString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ACSCH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ACSCH);
        code = generateOneParameterFunctionCode(mProfile->acschString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::ACOTH:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::ACOTH);
        code = generateOneParameterFunctionCode(mProfile->acothString(), ast, astStatement);

        break;
    case AnalyserEquationAst::Type::PIECEWISE: {
        auto astLeftChild = ast->leftChild();
        auto astRightChild = ast->rightChild();
        auto [leftCode, leftAstStatement] = generateCode(astLeftChild);
        auto [rightCode, rightAstStatement] = generateCode(astRightChild);

        if (astRightChild != nullptr) {
            if (astRightChild->type() == AnalyserEquationAst::Type::PIECE) {
                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::PIECEWISE,
                                                               leftAstStatement,
                                                               InterpreterAstStatement::create(InterpreterAstStatement::Type::PIECEWISE,
                                                                                               rightAstStatement,
                                                                                               InterpreterAstStatement::create(InterpreterAstStatement::Type::NAN)));
                code = leftCode + generatePiecewiseElseCode(rightCode + generatePiecewiseElseCode(mProfile->nanString()));
            } else {
                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::PIECEWISE,
                                                               leftAstStatement,
                                                               rightAstStatement);
                code = leftCode + generatePiecewiseElseCode(rightCode);
            }
        } else if (astLeftChild != nullptr) {
            if (astLeftChild->type() == AnalyserEquationAst::Type::PIECE) {
                astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::PIECEWISE,
                                                               leftAstStatement,
                                                               InterpreterAstStatement::create(InterpreterAstStatement::Type::NAN));
                code = leftCode + generatePiecewiseElseCode(mProfile->nanString());
            } else {
                astStatement = leftAstStatement;
                code = mProfile->nanString();
            }
        } else {
            astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::NAN);
            code = mProfile->nanString();
        }
    } break;
    case AnalyserEquationAst::Type::PIECE: {
        auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());
        auto [rightCode, rightAstStatement] = generateCode(ast->rightChild());

        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::PIECE,
                                                       leftAstStatement,
                                                       rightAstStatement);
        code = generatePiecewiseIfCode(rightCode, leftCode);
    } break;
    case AnalyserEquationAst::Type::OTHERWISE: {
        auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

        astStatement = leftAstStatement;
        code = leftCode;
    } break;
    case AnalyserEquationAst::Type::CI: {
        auto variable = ast->variable();
        bool rate = ast->parent()->type() == AnalyserEquationAst::Type::DIFF;

        if (mModel != nullptr) {
            auto analyserVariable = libcellml::analyserVariable(mModel, variable);

            astStatement = (analyserVariable->type() == AnalyserVariable::Type::VARIABLE_OF_INTEGRATION) ?
                               InterpreterAstStatement::create(InterpreterAstStatement::Type::VOI) :
                               InterpreterAstStatement::create(analyserVariable, rate);
        }

        code = generateVariableNameCode(variable, rate);
    } break;
    case AnalyserEquationAst::Type::CN: {
        double doubleValue;

        convertToDouble(ast->value(), doubleValue);

        astStatement = InterpreterAstStatement::create(doubleValue);
        code = generateDoubleCode(ast->value());
    } break;
    case AnalyserEquationAst::Type::DEGREE:
    case AnalyserEquationAst::Type::LOGBASE: {
        auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

        astStatement = leftAstStatement;
        code = leftCode;
    } break;
    case AnalyserEquationAst::Type::BVAR: {
        auto [leftCode, leftAstStatement] = generateCode(ast->leftChild());

        astStatement = leftAstStatement;
        code = leftCode;
    } break;
    case AnalyserEquationAst::Type::TRUE:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::TRUE);
        code = mProfile->trueString();

        break;
    case AnalyserEquationAst::Type::FALSE:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::FALSE);
        code = mProfile->falseString();

        break;
    case AnalyserEquationAst::Type::E:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::E);
        code = mProfile->eString();

        break;
    case AnalyserEquationAst::Type::PI:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::PI);
        code = mProfile->piString();

        break;
    case AnalyserEquationAst::Type::INF:
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::INF);
        code = mProfile->infString();

        break;
    default: // AnalyserEquationAst::Type::NAN.
        astStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::NAN);
        code = mProfile->nanString();

        break;
    }

    return {code, astStatement};
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isToBeComputedAgain(const AnalyserEquationPtr &equation) const
{
    // NLA and algebraic equations that are state/rate-based and external equations are to be computed again (in the
    // computeVariables() method).

    switch (equation->type()) {
    case AnalyserEquation::Type::NLA:
    case AnalyserEquation::Type::ALGEBRAIC:
        return equation->isStateRateBased();
    case AnalyserEquation::Type::EXTERNAL:
        return true;
    default:
        return false;
    }
}

bool GeneratorInterpreter::GeneratorInterpreterImpl::isSomeConstant(const AnalyserEquationPtr &equation,
                                                                    bool includeComputedConstants) const
{
    auto type = equation->type();

    return (type == AnalyserEquation::Type::TRUE_CONSTANT)
           || (!includeComputedConstants && (type == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT));
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateZeroInitialisationCode(const AnalyserVariablePtr &variable)
{
    bool rate = variable->type() == AnalyserVariable::Type::STATE;

    mAstStatements.push_back(InterpreterAstStatement::create(InterpreterAstStatement::Type::EQUALITY,
                                                             InterpreterAstStatement::create(variable, rate),
                                                             InterpreterAstStatement::create(0.0)));

    return mProfile->indentString()
           + generateVariableNameCode(variable->variable(), rate)
           + mProfile->equalityString()
           + "0.0"
           + mProfile->commandSeparatorString() + "\n";
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateInitialisationCode(const AnalyserVariablePtr &variable)
{
    // Determine whether the initialising variable

    auto initialisingVariable = variable->initialisingVariable();
    InterpreterAstStatementPtr initialValueAstStatement;
    std::string initialValueCode;

    if (isCellMLReal(initialisingVariable->initialValue())) {
        double initialValue;

        convertToDouble(initialisingVariable->initialValue(), initialValue);

        initialValueAstStatement = InterpreterAstStatement::create(initialValue);
        initialValueCode = generateDoubleCode(initialisingVariable->initialValue());
    } else {
        auto initValueVariable = owningComponent(initialisingVariable)->variable(initialisingVariable->initialValue());
        auto analyserInitialValueVariable = analyserVariable(mModel, initValueVariable);

        initialValueAstStatement = InterpreterAstStatement::create(analyserInitialValueVariable);
        initialValueCode = mProfile->variablesArrayString() + mProfile->openArrayString() + convertToString(analyserInitialValueVariable->index()) + mProfile->closeArrayString();
    }

    // Determine the scaling factor, if any.

    auto scalingFactor = GeneratorInterpreter::GeneratorInterpreterImpl::scalingFactor(initialisingVariable);

    if (!areNearlyEqual(scalingFactor, 1.0)) {
        initialValueAstStatement = InterpreterAstStatement::create(InterpreterAstStatement::Type::TIMES,
                                                                   InterpreterAstStatement::create(1.0 / scalingFactor),
                                                                   initialValueAstStatement);
        initialValueCode = generateDoubleCode(convertToString(1.0 / scalingFactor)) + mProfile->timesString() + initialValueCode;
    }

    mAstStatements.push_back(InterpreterAstStatement::create(InterpreterAstStatement::Type::EQUALITY,
                                                             InterpreterAstStatement::create(variable),
                                                             initialValueAstStatement));

    return mProfile->indentString()
           + generateVariableNameCode(variable->variable())
           + mProfile->equalityString()
           + initialValueCode
           + mProfile->commandSeparatorString() + "\n";
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateEquationCode(const AnalyserEquationPtr &equation,
                                                                                 std::vector<AnalyserEquationPtr> &remainingEquations,
                                                                                 std::vector<AnalyserEquationPtr> &equationsForDependencies,
                                                                                 bool includeComputedConstants)
{
    std::string res;

    if (std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end()) {
        // Stop tracking the equation and its NLA siblings, if any.
        // Note: we need to do this as soon as possible to avoid recursive calls, something that would happen if we were
        //       to do this at the end of this if statement.

        remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), equation));

        for (const auto &nlaSibling : equation->nlaSiblings()) {
            remainingEquations.erase(std::find(remainingEquations.begin(), remainingEquations.end(), nlaSibling));
        }

        // Generate any dependency that this equation may have.

        if (!isSomeConstant(equation, includeComputedConstants)) {
            for (const auto &dependency : equation->dependencies()) {
                if ((dependency->type() != AnalyserEquation::Type::ODE)
                    && !isSomeConstant(dependency, includeComputedConstants)
                    && (equationsForDependencies.empty()
                        || isToBeComputedAgain(dependency)
                        || (std::find(equationsForDependencies.begin(), equationsForDependencies.end(), dependency) != equationsForDependencies.end()))) {
                    //---GRY--- TO BE REMOVED...
                    // auto r = generateEquationCode(dependency, remainingEquations, equationsForDependencies, includeComputedConstants);
                    // if (!r.empty()) {
                    //     printf(">>> DEP: %s", r.c_str());
                    // }
                    // res += r;
                    res += generateEquationCode(dependency, remainingEquations, equationsForDependencies, includeComputedConstants);
                }
            }
        }

        // Generate the equation code itself, based on the equation type.

        switch (equation->type()) {
        case AnalyserEquation::Type::EXTERNAL:
            for (const auto &variable : equation->variables()) {
                mAstStatements.push_back(InterpreterAstStatement::create(InterpreterAstStatement::Type::EQUALITY,
                                                                         InterpreterAstStatement::create(variable),
                                                                         InterpreterAstStatement::create(variable->index())));

                res += mProfile->indentString()
                       + generateVariableNameCode(variable->variable())
                       + mProfile->equalityString()
                       + replace(mProfile->externalVariableMethodCallString(mModelHasOdes),
                                 "[INDEX]", convertToString(variable->index()))
                       + mProfile->commandSeparatorString() + "\n";
            }

            break;
        case AnalyserEquation::Type::NLA:
            if (!mProfile->findRootCallString(mModelHasOdes).empty()) {
                res += mProfile->indentString()
                       + replace(mProfile->findRootCallString(mModelHasOdes),
                                 "[INDEX]", convertToString(equation->nlaSystemIndex()));
            }

            break;
        default:
            auto [code, astStatement] = generateCode(equation->ast());

            mAstStatements.push_back(astStatement);

            res += mProfile->indentString() + code + mProfile->commandSeparatorString() + "\n";

            break;
        }
    }

    return res;
}

std::string GeneratorInterpreter::GeneratorInterpreterImpl::generateEquationCode(const AnalyserEquationPtr &equation,
                                                                                 std::vector<AnalyserEquationPtr> &remainingEquations)
{
    std::vector<AnalyserEquationPtr> dummyEquationsForComputeVariables;

    return generateEquationCode(equation, remainingEquations, dummyEquationsForComputeVariables, true);
}

void GeneratorInterpreter::GeneratorInterpreterImpl::nlaSystems()
{
    if (mModelHasNlas
        && !mProfile->objectiveFunctionMethodString(mModelHasOdes).empty()
        && !mProfile->findRootMethodString(mModelHasOdes).empty()
        && !mProfile->nlaSolveCallString(mModelHasOdes).empty()) {
        std::vector<AnalyserEquationPtr> handledNlaEquations;

        for (const auto &equation : mModel->equations()) {
            if ((equation->type() == AnalyserEquation::Type::NLA)
                && (std::find(handledNlaEquations.begin(), handledNlaEquations.end(), equation) == handledNlaEquations.end())) {
                std::string methodBody;
                auto i = MAX_SIZE_T;
                auto variables = equation->variables();
                auto variablesSize = variables.size();

                for (i = 0; i < variablesSize; ++i) {
                    auto arrayString = (variables[i]->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->variablesArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + convertToString(variables[i]->index()) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                methodBody += newLineIfNotEmpty(mCode);

                i = MAX_SIZE_T;

                auto [equationCode, equationAstStatement] = generateCode(equation->ast());

                methodBody += mProfile->indentString()
                              + mProfile->fArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                              + mProfile->equalityString()
                              + equationCode
                              + mProfile->commandSeparatorString() + "\n";

                handledNlaEquations.push_back(equation);

                for (const auto &nlaSibling : equation->nlaSiblings()) {
                    auto [nlaSiblingCode, nlaSiblingAstStatement] = generateCode(nlaSibling->ast());

                    methodBody += mProfile->indentString()
                                  + mProfile->fArrayString() + mProfile->openArrayString() + convertToString(++i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + nlaSiblingCode
                                  + mProfile->commandSeparatorString() + "\n";

                    handledNlaEquations.push_back(nlaSibling);
                }

                mCode += newLineIfNotEmpty(mCode)
                         + replace(replace(mProfile->objectiveFunctionMethodString(mModelHasOdes),
                                           "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                   "[CODE]", generateMethodBodyCode(methodBody));

                methodBody = {};

                for (i = 0; i < variablesSize; ++i) {
                    auto arrayString = (variables[i]->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->variablesArrayString();

                    methodBody += mProfile->indentString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(i) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + arrayString + mProfile->openArrayString() + convertToString(variables[i]->index()) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                methodBody += newLineIfNotEmpty(mCode)
                              + mProfile->indentString()
                              + replace(replace(mProfile->nlaSolveCallString(mModelHasOdes),
                                                "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                        "[SIZE]", convertToString(equation->variableCount()));

                methodBody += newLineIfNotEmpty(mCode);

                for (i = 0; i < variablesSize; ++i) {
                    auto arrayString = (variables[i]->type() == AnalyserVariable::Type::STATE) ?
                                           mProfile->ratesArrayString() :
                                           mProfile->variablesArrayString();

                    methodBody += mProfile->indentString()
                                  + arrayString + mProfile->openArrayString() + convertToString(variables[i]->index()) + mProfile->closeArrayString()
                                  + mProfile->equalityString()
                                  + mProfile->uArrayString() + mProfile->openArrayString() + convertToString(i) + mProfile->closeArrayString()
                                  + mProfile->commandSeparatorString() + "\n";
                }

                mCode += newLineIfNotEmpty(mCode)
                         + replace(replace(replace(mProfile->findRootMethodString(mModelHasOdes),
                                                   "[INDEX]", convertToString(equation->nlaSystemIndex())),
                                           "[SIZE]", convertToString(variablesSize)),
                                   "[CODE]", generateMethodBodyCode(methodBody));
            }
        }
    }
}

void GeneratorInterpreter::GeneratorInterpreterImpl::initialiseVariables(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationInitialiseVariablesMethodString = mProfile->implementationInitialiseVariablesMethodString(mModelHasOdes,
                                                                                                                 mModel->hasExternalVariables());

    if (!implementationInitialiseVariablesMethodString.empty()) {
        // Initialise our constants and our algebraic variables that have an initial value. Also use an initial guess of
        // zero for computed constants and algebraic variables computed using an NLA system.
        // Note: a variable which is the only unknown in an equation, but which is not on its own on either the LHS or
        //       RHS of that equation (e.g., x = y+z with x and y known and z unknown) is (currently) to be computed
        //       using an NLA system for which we need an initial guess. We use an initial guess of zero, which is fine
        //       since such an NLA system has only one solution.

        std::string methodBody;

        for (const auto &variable : mModel->variables()) {
            switch (variable->type()) {
            case AnalyserVariable::Type::CONSTANT:
                methodBody += generateInitialisationCode(variable);

                break;
            case AnalyserVariable::Type::COMPUTED_CONSTANT:
            case AnalyserVariable::Type::ALGEBRAIC:
                if (variable->initialisingVariable() != nullptr) {
                    methodBody += generateInitialisationCode(variable);
                } else if (variable->equation(0)->type() == AnalyserEquation::Type::NLA) {
                    methodBody += generateZeroInitialisationCode(variable);
                }

                break;
            default: // Other types we don't care about.
                break;
            }
        }

        // Initialise our true constants.

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::TRUE_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        // Initialise our states.

        for (const auto &state : mModel->states()) {
            methodBody += generateInitialisationCode(state);
        }

        // Use an initial guess of zero for rates computed using an NLA system
        // (see the note above).

        for (const auto &state : mModel->states()) {
            if (state->equation(0)->type() == AnalyserEquation::Type::NLA) {
                methodBody += generateZeroInitialisationCode(state);
            }
        }

        // Initialise our external variables.

        if (mModel->hasExternalVariables()) {
            auto equations = mModel->equations();
            std::vector<AnalyserEquationPtr> remainingExternalEquations;

            std::copy_if(equations.begin(), equations.end(),
                         std::back_inserter(remainingExternalEquations),
                         [](const AnalyserEquationPtr &equation) { return equation->type() == AnalyserEquation::Type::EXTERNAL; });

            for (const auto &equation : mModel->equations()) {
                if (equation->type() == AnalyserEquation::Type::EXTERNAL) {
                    methodBody += generateEquationCode(equation, remainingExternalEquations);
                }
            }
        }

        mCode += newLineIfNotEmpty(mCode)
                 + replace(implementationInitialiseVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void GeneratorInterpreter::GeneratorInterpreterImpl::computeComputedConstants(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    if (!mProfile->implementationComputeComputedConstantsMethodString().empty()) {
        std::string methodBody;

        for (const auto &equation : mModel->equations()) {
            if (equation->type() == AnalyserEquation::Type::VARIABLE_BASED_CONSTANT) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += newLineIfNotEmpty(mCode)
                 + replace(mProfile->implementationComputeComputedConstantsMethodString(),
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void GeneratorInterpreter::GeneratorInterpreterImpl::computeRates(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeRatesMethodString = mProfile->implementationComputeRatesMethodString(mModel->hasExternalVariables());

    if (mModelHasOdes
        && !implementationComputeRatesMethodString.empty()) {
        std::string methodBody;

        for (const auto &equation : mModel->equations()) {
            // A rate is computed either through an ODE equation or through an NLA equation in case the rate is not on
            // its own on either the LHS or RHS of the equation.

            if ((equation->type() == AnalyserEquation::Type::ODE)
                || ((equation->type() == AnalyserEquation::Type::NLA)
                    && (equation->variableCount() == 1)
                    && (equation->variable(0)->type() == AnalyserVariable::Type::STATE))) {
                methodBody += generateEquationCode(equation, remainingEquations);
            }
        }

        mCode += newLineIfNotEmpty(mCode)
                 + replace(implementationComputeRatesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

void GeneratorInterpreter::GeneratorInterpreterImpl::computeVariables(std::vector<AnalyserEquationPtr> &remainingEquations)
{
    auto implementationComputeVariablesMethodString = mProfile->implementationComputeVariablesMethodString(mModelHasOdes,
                                                                                                           mModel->hasExternalVariables());

    if (!implementationComputeVariablesMethodString.empty()) {
        std::string methodBody;
        auto equations = mModel->equations();
        std::vector<AnalyserEquationPtr> newRemainingEquations {std::begin(equations), std::end(equations)};

        for (const auto &equation : equations) {
            if ((std::find(remainingEquations.begin(), remainingEquations.end(), equation) != remainingEquations.end())
                || isToBeComputedAgain(equation)) {
                methodBody += generateEquationCode(equation, newRemainingEquations, remainingEquations, false);
            }
        }

        mCode += newLineIfNotEmpty(mCode)
                 + replace(implementationComputeVariablesMethodString,
                           "[CODE]", generateMethodBodyCode(methodBody));
    }
}

GeneratorInterpreter::GeneratorInterpreter(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile,
                                           const std::string &code)
    : mPimpl(new GeneratorInterpreterImpl(model, profile, code))
{
}

GeneratorInterpreter::GeneratorInterpreter(const AnalyserModelPtr &model)
    : mPimpl(new GeneratorInterpreterImpl(model))
{
}

GeneratorInterpreter::GeneratorInterpreter(const AnalyserEquationAstPtr &ast, const GeneratorProfilePtr &profile)
    : mPimpl(new GeneratorInterpreterImpl(ast, profile))
{
}

GeneratorInterpreter::~GeneratorInterpreter()
{
    delete mPimpl;
}

GeneratorInterpreterPtr GeneratorInterpreter::create(const AnalyserModelPtr &model, const GeneratorProfilePtr &profile,
                                                     const std::string &code) noexcept
{
    return std::shared_ptr<GeneratorInterpreter> {new GeneratorInterpreter {model, profile, code}};
}

GeneratorInterpreterPtr GeneratorInterpreter::create(const AnalyserModelPtr &model) noexcept
{
    return std::shared_ptr<GeneratorInterpreter> {new GeneratorInterpreter {model}};
}

GeneratorInterpreterPtr GeneratorInterpreter::create(const AnalyserEquationAstPtr &ast,
                                                     const GeneratorProfilePtr &profile) noexcept
{
    return std::shared_ptr<GeneratorInterpreter> {new GeneratorInterpreter {ast, profile}};
}

std::string GeneratorInterpreter::code() const
{
    return mPimpl->mCode;
}

std::vector<InterpreterAstStatementPtr> GeneratorInterpreter::initialiseVariablesAstStatements() const
{
    return mPimpl->mInitialiseVariablesAstStatements;
}

std::vector<InterpreterAstStatementPtr> GeneratorInterpreter::computeComputedConstantsAstStatements() const
{
    return mPimpl->mComputeComputedConstantsAstStatements;
}

std::vector<InterpreterAstStatementPtr> GeneratorInterpreter::computeRatesAstStatements() const
{
    return mPimpl->mComputeRatesAstStatements;
}

std::vector<InterpreterAstStatementPtr> GeneratorInterpreter::computeVariablesAstStatements() const
{
    return mPimpl->mComputeVariablesAstStatements;
}

} // namespace libcellml
