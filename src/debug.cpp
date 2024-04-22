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

#include "debug.h"

#include "libcellml/analyserequation.h"
#include "libcellml/analyserequationast.h"
#include "libcellml/analysermodel.h"
#include "libcellml/analyservariable.h"
#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/generatorprofile.h"
#include "libcellml/interpreter.h"
#include "libcellml/model.h"
#include "libcellml/variable.h"

#include "commonutils.h"
#include "generatorinterpreter_p.h"
#include "utilities.h"

#include "libcellml/undefines.h"

#include "interpreteraststatement_debug.cpp"
#include "interpreterrpnstatement_debug.cpp"

namespace libcellml {

std::string astAsCode(const AnalyserEquationAstPtr &ast)
{
    if (ast == nullptr) {
        return "nullptr";
    }

    static GeneratorProfilePtr generatorProfile = nullptr;

    if (generatorProfile == nullptr) {
        generatorProfile = GeneratorProfile::create();

        generatorProfile->setAbsoluteValueString("abs");
        generatorProfile->setNaturalLogarithmString("ln");
        generatorProfile->setCommonLogarithmString("log");
        generatorProfile->setRemString("rem");
        generatorProfile->setAsinString("arcsin");
        generatorProfile->setAcosString("arccos");
        generatorProfile->setAtanString("arctan");
        generatorProfile->setAsecString("arcsec");
        generatorProfile->setAcscString("arccsc");
        generatorProfile->setAcotString("arccot");
        generatorProfile->setAsinhString("arcsinh");
        generatorProfile->setAcoshString("arccosh");
        generatorProfile->setAtanhString("arctanh");
        generatorProfile->setAsechString("arcsech");
        generatorProfile->setAcschString("arccsch");
        generatorProfile->setAcothString("arccoth");
        generatorProfile->setTrueString("true");
        generatorProfile->setFalseString("false");
        generatorProfile->setEString("exponentiale");
        generatorProfile->setPiString("pi");
        generatorProfile->setInfString("infinity");
        generatorProfile->setNanString("notanumber");
    }

    return Generator::equationCode(ast, generatorProfile);
}

void printAnalyserModelEquations(const AnalyserModelPtr &model)
{
    size_t eqnNb = 0;

    for (const auto &eqn : model->equations()) {
        Debug() << "\n---------------------------------------[API equation #" << ++eqnNb << "]";

        if (eqn->ast() != nullptr) {
            Debug() << "\n"
                    << astAsCode(eqn->ast());
        } else {
            Debug() << "\nNo equation";
        }

        Debug() << "\nType: " << AnalyserEquation::typeAsString(eqn->type());

        if (eqn->variableCount() != 0) {
            Debug() << "\nVariables:";

            for (const auto &var : eqn->variables()) {
                Debug() << " - " << var->variable()->name();
            }
        } else {
            Debug() << "\nNo variables";
        }

        if (eqn->dependencyCount() != 0) {
            Debug() << "\nDependencies:";

            for (const auto &dep : eqn->dependencies()) {
                if (dep->ast() != nullptr) {
                    Debug() << " - " << astAsCode(dep->ast());
                } else if (dep->type() == AnalyserEquation::Type::EXTERNAL) {
                    Debug() << " - External equation for '" << dep->variable(0)->variable()->name() << "'";
                } else {
                    Debug() << " - ??? [" << AnalyserEquation::typeAsString(dep->type()) << "]";
                }
            }
        } else {
            Debug() << "\nNo dependencies";
        }

        if (eqn->type() == AnalyserEquation::Type::NLA) {
            if (eqn->nlaSiblingCount() != 0) {
                Debug() << "\nNLA siblings:";

                for (const auto &nlaSibling : eqn->nlaSiblings()) {
                    if (nlaSibling->ast() != nullptr) {
                        Debug() << " - " << astAsCode(nlaSibling->ast());
                    } else if (nlaSibling->type() == AnalyserEquation::Type::EXTERNAL) {
                        Debug() << " - External equation for '" << nlaSibling->variable(0)->variable()->name() << "'";
                    } else {
                        Debug() << " - ??? [" << AnalyserEquation::typeAsString(nlaSibling->type()) << "]";
                    }
                }
            } else {
                Debug() << "\nNo NLA siblings";
            }
        }
    }

    Debug() << "\n---------------------------------------[END]\n";
}

void printAnalyserModelVariables(const AnalyserModelPtr &model)
{
    size_t varNb = 0;

    for (const auto &var : model->variables()) {
        Debug() << "\n---------------------------------------[API variable " << ++varNb << "]";
        Debug() << "\nName: " << var->variable()->name();
        Debug() << "Type: " << AnalyserVariable::typeAsString(var->type());

        if (var->equationCount() != 0) {
            Debug() << "\nEquations:";

            for (const auto &eqn : var->equations()) {
                if (eqn->ast() != nullptr) {
                    Debug() << " - " << astAsCode(eqn->ast());
                } else if (eqn->type() == AnalyserEquation::Type::EXTERNAL) {
                    Debug() << " - External equation for '" << eqn->variable(0)->variable()->name() << "'";
                } else {
                    Debug() << " - ??? [" << AnalyserEquation::typeAsString(eqn->type()) << "]";
                }
            }
        } else {
            Debug() << "\nNo equations";
        }
    }
}

void printHistory(const History &history)
{
    for (const auto &h : history) {
        printHistoryEpoch(h);
    }
}

void printHistoryEpoch(const HistoryEpochPtr &historyEpoch)
{
    Debug() << "'" << historyEpoch->mSourceModel->name() << "' '" << historyEpoch->mName << "' '" << historyEpoch->mSourceUrl << "' -> '" << historyEpoch->mDestinationUrl << "'";
}

void printStack(const IndexStack &stack)
{
    bool first = true;
    Debug(false) << "[";
    for (const auto &iter : stack) {
        if (!first) {
            Debug(false) << ", ";
        }
        Debug(false) << iter;
        first = false;
    }
    Debug() << "]";
}

void printEquivalenceMap(const EquivalenceMap &map)
{
    Debug() << "Print out of equivalence map";
    for (const auto &iter : map) {
        auto key = iter.first;
        Debug(false) << "key: ";
        printStack(key);
        auto vector = iter.second;
        for (const auto &vectorIt : vector) {
            Debug(false) << "value: ";
            printStack(vectorIt);
        }
    }
}

void printEquivalenceMapWithModelInfo(const EquivalenceMap &map, const ModelPtr &model)
{
    for (const auto &iter : map) {
        auto key = iter.first;
        Debug(false) << "key: ";
        printStackWithModelInfo(key, model);
        auto vector = iter.second;
        for (const auto &vectorIt : vector) {
            Debug(false) << "value: ";
            printStackWithModelInfo(vectorIt, model);
        }
    }
}

void printStackWithModelInfo(const IndexStack &stack, const ModelPtr &model)
{
    bool first = true;
    ComponentPtr entity;
    Debug(false) << "[";
    for (auto iter = stack.begin(); iter != stack.end(); ++iter) {
        if (!first) {
            Debug(false) << ", ";
        }
        auto next = iter;
        if (first) {
            entity = model->component(*iter);
            Debug(false) << entity->name();
        } else if (++next == stack.end()) {
            Debug(false) << entity->variable(*iter)->name();
        } else {
            entity = entity->component(*iter);
            Debug(false) << entity->name();
        }
        first = false;
    }
    Debug() << "]";
}

void printConnectionMap(const ConnectionMap &map)
{
    Debug() << "Print out of connection map";
    for (const auto &iter : map) {
        auto key = iter.first;
        auto value = iter.second;
        Debug() << "first: " << key->name();
        Debug() << "second: " << value->name();
    }
}

void printComponentMap(const ComponentMap &map)
{
    Debug() << "Print out of component map";
    for (const auto &iter : map) {
        auto key = iter.first;
        auto value = iter.second;
        Debug() << "first: " << key->name();
        if (value) {
            Debug() << "second: " << value->name();
        } else {
            Debug() << "second: null";
        }
    }
}

void printStringStringMap(const StringStringMap &map)
{
    Debug() << "Print out of string -> string map";
    for (const auto &iter : map) {
        Debug() << iter.first << ": " << iter.second;
    }
}

static const std::string SPACES = "  ";
static const std::string TRUNK = "  │";

struct AnalyserEquationAstTrunk
{
    AnalyserEquationAstTrunk *mPrev;
    std::string mStr;

    AnalyserEquationAstTrunk(AnalyserEquationAstTrunk *prev,
                             const std::string &str);
};

AnalyserEquationAstTrunk::AnalyserEquationAstTrunk(AnalyserEquationAstTrunk *prev,
                                                   const std::string &str)
    : mPrev(prev)
    , mStr(str)
{
}

std::string doPrintAstAsTree(AnalyserEquationAstTrunk *trunk)
{
    if (trunk == nullptr) {
        return {};
    }

    auto res = doPrintAstAsTree(trunk->mPrev);

    if ((trunk->mPrev != nullptr) && (trunk->mPrev->mStr == SPACES)
        && ((trunk->mStr == SPACES) || (trunk->mStr == TRUNK))) {
        res += " ";
    }

    return res + trunk->mStr;
}

std::string ciValue(const AnalyserVariablePtr &analyserVariable, bool rate)
{
    std::string res;

    if (analyserVariable->type() == AnalyserVariable::Type::STATE) {
        res = rate ? "rates" : "states";
    } else {
        res = "variables";
    }

    auto variable = analyserVariable->variable();

    res += "[" + std::to_string(analyserVariable->index()) + "] | "
           + owningComponent(variable)->name() + " | "
           + variable->name() + std::string(rate ? "'" : "");

    return res;
}

std::string doPrintAstAsTree(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast)
{
    std::string res;

    switch (ast->type()) {
        // Equality.

    case AnalyserEquationAst::Type::EQUALITY:
        res = "EQUALITY";

        break;

        // Relational and logical operators.

    case AnalyserEquationAst::Type::EQ:
        res = "EQ";

        break;
    case AnalyserEquationAst::Type::NEQ:
        res = "NEQ";

        break;
    case AnalyserEquationAst::Type::LT:
        res = "LT";

        break;
    case AnalyserEquationAst::Type::LEQ:
        res = "LEQ";

        break;
    case AnalyserEquationAst::Type::GT:
        res = "GT";

        break;
    case AnalyserEquationAst::Type::GEQ:
        res = "LEQ";

        break;
    case AnalyserEquationAst::Type::AND:
        res = "AND";

        break;
    case AnalyserEquationAst::Type::OR:
        res = "OR";

        break;
    case AnalyserEquationAst::Type::XOR:
        res = "XOR";

        break;
    case AnalyserEquationAst::Type::NOT:
        res = "NOT";

        break;

        // Arithmetic operators.

    case AnalyserEquationAst::Type::PLUS:
        res = "PLUS";

        break;
    case AnalyserEquationAst::Type::MINUS:
        res = "MINUS";

        break;
    case AnalyserEquationAst::Type::TIMES:
        res = "TIMES";

        break;
    case AnalyserEquationAst::Type::DIVIDE:
        res = "DIVIDE";

        break;
    case AnalyserEquationAst::Type::POWER:
        res = "POWER";

        break;
    case AnalyserEquationAst::Type::ROOT:
        res = "ROOT";

        break;
    case AnalyserEquationAst::Type::ABS:
        res = "ABS";

        break;
    case AnalyserEquationAst::Type::EXP:
        res = "EXP";

        break;
    case AnalyserEquationAst::Type::LN:
        res = "LN";

        break;
    case AnalyserEquationAst::Type::LOG:
        res = "LOG";

        break;
    case AnalyserEquationAst::Type::CEILING:
        res = "CEILING";

        break;
    case AnalyserEquationAst::Type::FLOOR:
        res = "FLOOR";

        break;
    case AnalyserEquationAst::Type::MIN:
        res = "MIN";

        break;
    case AnalyserEquationAst::Type::MAX:
        res = "MAX";

        break;
    case AnalyserEquationAst::Type::REM:
        res = "REM";

        break;

        // Calculus elements.

    case AnalyserEquationAst::Type::DIFF:
        res = "DIFF";

        break;

        // Trigonometric operators.

    case AnalyserEquationAst::Type::SIN:
        res = "SIN";

        break;
    case AnalyserEquationAst::Type::COS:
        res = "COS";

        break;
    case AnalyserEquationAst::Type::TAN:
        res = "TAN";

        break;
    case AnalyserEquationAst::Type::SEC:
        res = "SEC";

        break;
    case AnalyserEquationAst::Type::CSC:
        res = "CSC";

        break;
    case AnalyserEquationAst::Type::COT:
        res = "COT";

        break;
    case AnalyserEquationAst::Type::SINH:
        res = "SINH";

        break;
    case AnalyserEquationAst::Type::COSH:
        res = "COSH";

        break;
    case AnalyserEquationAst::Type::TANH:
        res = "TANH";

        break;
    case AnalyserEquationAst::Type::SECH:
        res = "SECH";

        break;
    case AnalyserEquationAst::Type::CSCH:
        res = "CSCH";

        break;
    case AnalyserEquationAst::Type::COTH:
        res = "COTH";

        break;
    case AnalyserEquationAst::Type::ASIN:
        res = "ASIN";

        break;
    case AnalyserEquationAst::Type::ACOS:
        res = "ACOS";

        break;
    case AnalyserEquationAst::Type::ATAN:
        res = "ATAN";

        break;
    case AnalyserEquationAst::Type::ASEC:
        res = "ASEC";

        break;
    case AnalyserEquationAst::Type::ACSC:
        res = "ACSC";

        break;
    case AnalyserEquationAst::Type::ACOT:
        res = "ACOT";

        break;
    case AnalyserEquationAst::Type::ASINH:
        res = "ASINH";

        break;
    case AnalyserEquationAst::Type::ACOSH:
        res = "ACOSH";

        break;
    case AnalyserEquationAst::Type::ATANH:
        res = "ATANH";

        break;
    case AnalyserEquationAst::Type::ASECH:
        res = "ASECH";

        break;
    case AnalyserEquationAst::Type::ACSCH:
        res = "ACSCH";

        break;
    case AnalyserEquationAst::Type::ACOTH:
        res = "ACOTH";

        break;

        // Piecewise statement.

    case AnalyserEquationAst::Type::PIECEWISE:
        res = "PIECEWISE";

        break;
    case AnalyserEquationAst::Type::PIECE:
        res = "PIECE";

        break;
    case AnalyserEquationAst::Type::OTHERWISE:
        res = "OTHERWISE";

        break;

        // Token elements.

    case AnalyserEquationAst::Type::CI:
        res = ciValue(libcellml::analyserVariable(model, ast->variable()),
                      ast->parent()->type() == AnalyserEquationAst::Type::DIFF);

        break;
    case AnalyserEquationAst::Type::CN:
        res = ast->value();

        break;

        // Qualifier elements.

    case AnalyserEquationAst::Type::DEGREE:
        res = "DEGREE";

        break;
    case AnalyserEquationAst::Type::LOGBASE:
        res = "LOGBASE";

        break;
    case AnalyserEquationAst::Type::BVAR:
        res = "BVAR";

        break;

        // Constants.

    case AnalyserEquationAst::Type::TRUE:
        res = "TRUE";

        break;
    case AnalyserEquationAst::Type::FALSE:
        res = "FALSE";

        break;
    case AnalyserEquationAst::Type::E:
        res = "E";

        break;
    case AnalyserEquationAst::Type::PI:
        res = "PI";

        break;
    case AnalyserEquationAst::Type::INF:
        res = "INF";

        break;
    case AnalyserEquationAst::Type::NAN:
        res = "NAN";

        break;
    }

    return res;
}

std::string doPrintAstAsTree(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast,
                             AnalyserEquationAstTrunk *prevTrunk, bool isLeft)
{
    if (ast == nullptr) {
        return {};
    }

    std::string res;
    std::string prevStr = SPACES;
    AnalyserEquationAstTrunk trunk(prevTrunk, prevStr);
    auto astLeftChild = ast->leftChild();

    if (astLeftChild != nullptr) {
        res += doPrintAstAsTree(model, astLeftChild, &trunk, true);
    }

    if (prevTrunk == nullptr) {
        trunk.mStr = "──";
    } else if (isLeft) {
        trunk.mStr = "╭──";
        prevStr = TRUNK;
    } else {
        trunk.mStr = "╰──";
        prevTrunk->mStr = prevStr;
    }

    auto astRightChild = ast->rightChild();

    res += doPrintAstAsTree(&trunk);

    if (astLeftChild != nullptr) {
        res += (astRightChild != nullptr) ? "┤" : "┘";
    }

    res += " " + doPrintAstAsTree(model, ast) + "\n";

    if (prevTrunk != nullptr) {
        prevTrunk->mStr = prevStr;
    }

    trunk.mStr = TRUNK;

    if (astRightChild != nullptr) {
        res += doPrintAstAsTree(model, astRightChild, &trunk, false);
    }

    return res;
}

void printAstAsTree(const AnalyserModelPtr &model, const AnalyserEquationAstPtr &ast)
{
    Debug() << doPrintAstAsTree(model, ast, nullptr, false);
}

void printAstAsCode(const AnalyserEquationAstPtr &ast)
{
    Debug() << astAsCode(ast);
}

struct InterpreterAstStatementTrunk
{
    InterpreterAstStatementTrunk *mPrev;
    std::string mStr;

    InterpreterAstStatementTrunk(InterpreterAstStatementTrunk *prev,
                                 const std::string &str);
};

InterpreterAstStatementTrunk::InterpreterAstStatementTrunk(InterpreterAstStatementTrunk *prev,
                                                           const std::string &str)
    : mPrev(prev)
    , mStr(str)
{
}

std::string doPrintInterpreterAstStatement(InterpreterAstStatementTrunk *trunk)
{
    if (trunk == nullptr) {
        return {};
    }

    auto res = doPrintInterpreterAstStatement(trunk->mPrev);

    if ((trunk->mPrev != nullptr) && (trunk->mPrev->mStr == SPACES)
        && ((trunk->mStr == SPACES) || (trunk->mStr == TRUNK))) {
        res += " ";
    }

    return res + trunk->mStr;
}

std::string doPrintInterpreterAstStatement(const InterpreterAstStatementPtr &interpreterAstStatement)
{
    std::string res;

    switch (interpreterAstStatement->type()) {
        // Equality.

    case InterpreterAstStatement::Type::EQUALITY:
        res = "EQUALITY";

        break;

        // Relational and logical operators.

    case InterpreterAstStatement::Type::EQ:
        res = "EQ";

        break;
    case InterpreterAstStatement::Type::NEQ:
        res = "NEQ";

        break;
    case InterpreterAstStatement::Type::LT:
        res = "LT";

        break;
    case InterpreterAstStatement::Type::LEQ:
        res = "LEQ";

        break;
    case InterpreterAstStatement::Type::GT:
        res = "GT";

        break;
    case InterpreterAstStatement::Type::GEQ:
        res = "LEQ";

        break;
    case InterpreterAstStatement::Type::AND:
        res = "AND";

        break;
    case InterpreterAstStatement::Type::OR:
        res = "OR";

        break;
    case InterpreterAstStatement::Type::XOR:
        res = "XOR";

        break;
    case InterpreterAstStatement::Type::NOT:
        res = "NOT";

        break;

        // Arithmetic operators.

    case InterpreterAstStatement::Type::PLUS:
        res = "PLUS";

        break;
    case InterpreterAstStatement::Type::MINUS:
        res = "MINUS";

        break;
    case InterpreterAstStatement::Type::TIMES:
        res = "TIMES";

        break;
    case InterpreterAstStatement::Type::DIVIDE:
        res = "DIVIDE";

        break;
    case InterpreterAstStatement::Type::POWER:
        res = "POWER";

        break;
    case InterpreterAstStatement::Type::SQUARE_ROOT:
        res = "SQUARE_ROOT";

        break;
    case InterpreterAstStatement::Type::SQUARE:
        res = "SQUARE";

        break;
    case InterpreterAstStatement::Type::ABS:
        res = "ABS";

        break;
    case InterpreterAstStatement::Type::EXP:
        res = "EXP";

        break;
    case InterpreterAstStatement::Type::LN:
        res = "LN";

        break;
    case InterpreterAstStatement::Type::LOG:
        res = "LOG";

        break;
    case InterpreterAstStatement::Type::CEILING:
        res = "CEILING";

        break;
    case InterpreterAstStatement::Type::FLOOR:
        res = "FLOOR";

        break;
    case InterpreterAstStatement::Type::MIN:
        res = "MIN";

        break;
    case InterpreterAstStatement::Type::MAX:
        res = "MAX";

        break;
    case InterpreterAstStatement::Type::REM:
        res = "REM";

        break;

        // Trigonometric operators.

    case InterpreterAstStatement::Type::SIN:
        res = "SIN";

        break;
    case InterpreterAstStatement::Type::COS:
        res = "COS";

        break;
    case InterpreterAstStatement::Type::TAN:
        res = "TAN";

        break;
    case InterpreterAstStatement::Type::SEC:
        res = "SEC";

        break;
    case InterpreterAstStatement::Type::CSC:
        res = "CSC";

        break;
    case InterpreterAstStatement::Type::COT:
        res = "COT";

        break;
    case InterpreterAstStatement::Type::SINH:
        res = "SINH";

        break;
    case InterpreterAstStatement::Type::COSH:
        res = "COSH";

        break;
    case InterpreterAstStatement::Type::TANH:
        res = "TANH";

        break;
    case InterpreterAstStatement::Type::SECH:
        res = "SECH";

        break;
    case InterpreterAstStatement::Type::CSCH:
        res = "CSCH";

        break;
    case InterpreterAstStatement::Type::COTH:
        res = "COTH";

        break;
    case InterpreterAstStatement::Type::ASIN:
        res = "ASIN";

        break;
    case InterpreterAstStatement::Type::ACOS:
        res = "ACOS";

        break;
    case InterpreterAstStatement::Type::ATAN:
        res = "ATAN";

        break;
    case InterpreterAstStatement::Type::ASEC:
        res = "ASEC";

        break;
    case InterpreterAstStatement::Type::ACSC:
        res = "ACSC";

        break;
    case InterpreterAstStatement::Type::ACOT:
        res = "ACOT";

        break;
    case InterpreterAstStatement::Type::ASINH:
        res = "ASINH";

        break;
    case InterpreterAstStatement::Type::ACOSH:
        res = "ACOSH";

        break;
    case InterpreterAstStatement::Type::ATANH:
        res = "ATANH";

        break;
    case InterpreterAstStatement::Type::ASECH:
        res = "ASECH";

        break;
    case InterpreterAstStatement::Type::ACSCH:
        res = "ACSCH";

        break;
    case InterpreterAstStatement::Type::ACOTH:
        res = "ACOTH";

        break;

        // Piecewise statement.

    case InterpreterAstStatement::Type::PIECEWISE:
        res = "PIECEWISE";

        break;
    case InterpreterAstStatement::Type::PIECE:
        res = "PIECE";

        break;

        // Token elements.

    case InterpreterAstStatement::Type::VOI:
        res = "VOI";

        break;
    case InterpreterAstStatement::Type::STATE:
    case InterpreterAstStatement::Type::RATE:
    case InterpreterAstStatement::Type::VARIABLE:
        res = ciValue(interpreterAstStatement->variable(),
                      interpreterAstStatement->type() == InterpreterAstStatement::Type::RATE);

        break;
    case InterpreterAstStatement::Type::NUMBER:
        res = convertToString(interpreterAstStatement->value());

        break;

        // Qualifier elements.

    case InterpreterAstStatement::Type::DEGREE:
        res = "DEGREE";

        break;
    case InterpreterAstStatement::Type::LOGBASE:
        res = "LOGBASE";

        break;
    case InterpreterAstStatement::Type::BVAR:
        res = "BVAR";

        break;

        // Constants.

    case InterpreterAstStatement::Type::TRUE:
        res = "TRUE";

        break;
    case InterpreterAstStatement::Type::FALSE:
        res = "FALSE";

        break;
    case InterpreterAstStatement::Type::E:
        res = "E";

        break;
    case InterpreterAstStatement::Type::PI:
        res = "PI";

        break;
    case InterpreterAstStatement::Type::INF:
        res = "INF";

        break;
    case InterpreterAstStatement::Type::NAN:
        res = "NAN";

        break;

        // Miscellaneous.

    case InterpreterAstStatement::Type::EXTERNAL:
        res = "EXTERNAL[" + convertToString(interpreterAstStatement->externalIndex()) + "]";

        break;
    }

    return res;
}

std::string doPrintInterpreterAstStatement(const InterpreterAstStatementPtr &interpreterAstStatement,
                                           InterpreterAstStatementTrunk *prevTrunk, bool isLeft)
{
    if (interpreterAstStatement == nullptr) {
        return {};
    }

    std::string res;
    std::string prevStr = SPACES;
    InterpreterAstStatementTrunk trunk(prevTrunk, prevStr);
    auto astLeftChild = interpreterAstStatement->leftChild();

    if (astLeftChild != nullptr) {
        res += doPrintInterpreterAstStatement(astLeftChild, &trunk, true);
    }

    if (prevTrunk == nullptr) {
        trunk.mStr = "──";
    } else if (isLeft) {
        trunk.mStr = "╭──";
        prevStr = TRUNK;
    } else {
        trunk.mStr = "╰──";
        prevTrunk->mStr = prevStr;
    }

    auto astRightChild = interpreterAstStatement->rightChild();

    res += doPrintInterpreterAstStatement(&trunk);

    if (astLeftChild != nullptr) {
        res += (astRightChild != nullptr) ? "┤" : "┘";
    }

    res += " " + doPrintInterpreterAstStatement(interpreterAstStatement) + "\n";

    if (prevTrunk != nullptr) {
        prevTrunk->mStr = prevStr;
    }

    trunk.mStr = TRUNK;

    if (astRightChild != nullptr) {
        res += doPrintInterpreterAstStatement(astRightChild, &trunk, false);
    }

    return res;
}

void printInterpreterAstStatement(const InterpreterAstStatementPtr &interpreterAstStatement)
{
    Debug() << doPrintInterpreterAstStatement(interpreterAstStatement, nullptr, false);
}

void doPrintInterpreterRpnStatement(const InterpreterRpnStatementPtr &interpreterRpnStatement)
{
    switch (interpreterRpnStatement->type()) {
        // Equality.

    case InterpreterRpnStatement::Type::EQUALITY:
        Debug() << "EQUALITY";
        Debug() << "---------";

        break;

        // Relational and logical operators.

    case InterpreterRpnStatement::Type::EQ:
        Debug() << "EQ";

        break;
    case InterpreterRpnStatement::Type::NEQ:
        Debug() << "NEQ";

        break;
    case InterpreterRpnStatement::Type::LT:
        Debug() << "LT";

        break;
    case InterpreterRpnStatement::Type::LEQ:
        Debug() << "LEQ";

        break;
    case InterpreterRpnStatement::Type::GT:
        Debug() << "GT";

        break;
    case InterpreterRpnStatement::Type::GEQ:
        Debug() << "LEQ";

        break;
    case InterpreterRpnStatement::Type::AND:
        Debug() << "AND";

        break;
    case InterpreterRpnStatement::Type::OR:
        Debug() << "OR";

        break;
    case InterpreterRpnStatement::Type::XOR:
        Debug() << "XOR";

        break;
    case InterpreterRpnStatement::Type::NOT:
        Debug() << "NOT";

        break;

        // Arithmetic operators.

    case InterpreterRpnStatement::Type::PLUS:
        Debug() << "PLUS";

        break;
    case InterpreterRpnStatement::Type::UNARY_MINUS:
        Debug() << "UNARY_MINUS";

        break;
    case InterpreterRpnStatement::Type::MINUS:
        Debug() << "MINUS";

        break;
    case InterpreterRpnStatement::Type::TIMES:
        Debug() << "TIMES";

        break;
    case InterpreterRpnStatement::Type::DIVIDE:
        Debug() << "DIVIDE";

        break;
    case InterpreterRpnStatement::Type::POWER:
        Debug() << "POWER";

        break;
    case InterpreterRpnStatement::Type::SQUARE_ROOT:
        Debug() << "SQUARE_ROOT";

        break;
    case InterpreterRpnStatement::Type::SQUARE:
        Debug() << "SQUARE";

        break;
    case InterpreterRpnStatement::Type::ABS:
        Debug() << "ABS";

        break;
    case InterpreterRpnStatement::Type::EXP:
        Debug() << "EXP";

        break;
    case InterpreterRpnStatement::Type::LN:
        Debug() << "LN";

        break;
    case InterpreterRpnStatement::Type::LOG:
        Debug() << "LOG";

        break;
    case InterpreterRpnStatement::Type::CEILING:
        Debug() << "CEILING";

        break;
    case InterpreterRpnStatement::Type::FLOOR:
        Debug() << "FLOOR";

        break;
    case InterpreterRpnStatement::Type::MIN:
        Debug() << "MIN";

        break;
    case InterpreterRpnStatement::Type::MAX:
        Debug() << "MAX";

        break;
    case InterpreterRpnStatement::Type::REM:
        Debug() << "REM";

        break;

        // Trigonometric operators.

    case InterpreterRpnStatement::Type::SIN:
        Debug() << "SIN";

        break;
    case InterpreterRpnStatement::Type::COS:
        Debug() << "COS";

        break;
    case InterpreterRpnStatement::Type::TAN:
        Debug() << "TAN";

        break;
    case InterpreterRpnStatement::Type::SEC:
        Debug() << "SEC";

        break;
    case InterpreterRpnStatement::Type::CSC:
        Debug() << "CSC";

        break;
    case InterpreterRpnStatement::Type::COT:
        Debug() << "COT";

        break;
    case InterpreterRpnStatement::Type::SINH:
        Debug() << "SINH";

        break;
    case InterpreterRpnStatement::Type::COSH:
        Debug() << "COSH";

        break;
    case InterpreterRpnStatement::Type::TANH:
        Debug() << "TANH";

        break;
    case InterpreterRpnStatement::Type::SECH:
        Debug() << "SECH";

        break;
    case InterpreterRpnStatement::Type::CSCH:
        Debug() << "CSCH";

        break;
    case InterpreterRpnStatement::Type::COTH:
        Debug() << "COTH";

        break;
    case InterpreterRpnStatement::Type::ASIN:
        Debug() << "ASIN";

        break;
    case InterpreterRpnStatement::Type::ACOS:
        Debug() << "ACOS";

        break;
    case InterpreterRpnStatement::Type::ATAN:
        Debug() << "ATAN";

        break;
    case InterpreterRpnStatement::Type::ASEC:
        Debug() << "ASEC";

        break;
    case InterpreterRpnStatement::Type::ACSC:
        Debug() << "ACSC";

        break;
    case InterpreterRpnStatement::Type::ACOT:
        Debug() << "ACOT";

        break;
    case InterpreterRpnStatement::Type::ASINH:
        Debug() << "ASINH";

        break;
    case InterpreterRpnStatement::Type::ACOSH:
        Debug() << "ACOSH";

        break;
    case InterpreterRpnStatement::Type::ATANH:
        Debug() << "ATANH";

        break;
    case InterpreterRpnStatement::Type::ASECH:
        Debug() << "ASECH";

        break;
    case InterpreterRpnStatement::Type::ACSCH:
        Debug() << "ACSCH";

        break;
    case InterpreterRpnStatement::Type::ACOTH:
        Debug() << "ACOTH";

        break;

        // Piecewise statement.

    case InterpreterRpnStatement::Type::PIECEWISE:
        Debug() << "PIECEWISE";

        break;

        // Token elements.

    case InterpreterRpnStatement::Type::VOI:
        Debug() << "VOI";

        break;
    case InterpreterRpnStatement::Type::STATE:
    case InterpreterRpnStatement::Type::RATE:
    case InterpreterRpnStatement::Type::VARIABLE:
        Debug() << ciValue(interpreterRpnStatement->variable(),
                      interpreterRpnStatement->type() == InterpreterRpnStatement::Type::RATE);

        break;
    case InterpreterRpnStatement::Type::NUMBER:
        Debug() << convertToString(interpreterRpnStatement->value());

        break;

        // Qualifier elements.

    case InterpreterRpnStatement::Type::DEGREE:
        Debug() << "DEGREE";

        break;
    case InterpreterRpnStatement::Type::LOGBASE:
        Debug() << "LOGBASE";

        break;
    case InterpreterRpnStatement::Type::BVAR:
        Debug() << "BVAR";

        break;

        // Constants.

    case InterpreterRpnStatement::Type::TRUE:
        Debug() << "TRUE";

        break;
    case InterpreterRpnStatement::Type::FALSE:
        Debug() << "FALSE";

        break;
    case InterpreterRpnStatement::Type::E:
        Debug() << "E";

        break;
    case InterpreterRpnStatement::Type::PI:
        Debug() << "PI";

        break;
    case InterpreterRpnStatement::Type::INF:
        Debug() << "INF";

        break;
    case InterpreterRpnStatement::Type::NAN:
        Debug() << "NAN";

        break;

        // Miscellaneous.

    case InterpreterRpnStatement::Type::EXTERNAL:
        Debug() << "EXTERNAL[" + convertToString(interpreterRpnStatement->externalIndex()) + "]";

        break;
    }
}

void printInterpreterRpnStatements(const InterpreterRpnStatementPtrs &interpreterRpnStatements)
{
    Debug() << "---------";

    for (const auto &interpreterRpnStatement : interpreterRpnStatements) {
        doPrintInterpreterRpnStatement(interpreterRpnStatement);
    }
}

void printImportLibrary(const ImportLibrary &importlibrary)
{
    Debug() << " == Import library ==";
    for (const auto &entry : importlibrary) {
        std::string name = "(null)";
        if (entry.second != nullptr) {
            name = entry.second->name();
        }
        Debug() << entry.first << " - " << name;
    }
    Debug() << " == ";
}

void printVariableMap(const VariableMap &map)
{
    Debug() << " == Variable map ==";
    for (const auto &entry : map) {
        auto v1 = entry->variable1();
        auto v2 = entry->variable2();

        Debug(false) << "v1: ";
        if (v1 == nullptr) {
            Debug(false) << "(nullptr)";
        } else {
            Debug(false) << v1->name();
        }
        Debug(false) << " - v2: ";
        if (v2 == nullptr) {
            Debug(false) << "(nullptr)";
        } else {
            Debug(false) << v2->name();
        }
        Debug() << "";
    }
}

void printNamedPath(const ParentedEntityPtr &parented)
{
    if (parented != nullptr) {
        std::vector<std::string> names;
        auto named = std::dynamic_pointer_cast<libcellml::NamedEntity>(parented);
        if (named != nullptr) {
            names.push_back(named->name());
            auto parent = named->parent();
            while (parent != nullptr) {
                auto named = std::dynamic_pointer_cast<libcellml::NamedEntity>(parent);
                if (named != nullptr) {
                    names.push_back(named->name());
                }
                parent = parent->parent();
            }
        }

        while (!names.empty()) {
            Debug(false) << "/" << names.back();
            names.pop_back();
        }
    } else {
        Debug() << "nullptr variable.";
    }
}

void printEquivalences(const VariablePtr &variable)
{
    Debug(false) << "Equivalence for: ";
    printNamedPath(variable);
    Debug();
    if (variable != nullptr) {
        for (size_t j = 0; j < variable->equivalentVariableCount(); ++j) {
            Debug(false) << " - ";
            printNamedPath(variable->equivalentVariable(j));
            Debug();
        }
    }
}

void printUnits(const UnitsPtr &units)
{
    Debug(false) << "Units: " << (units ? units->name() : "nullptr");
    if (units) {
        if (units->isImport()) {
            Debug(false) << " (is imported)";
        }
        Debug() << "";
        auto model = owningModel(units);
        for (size_t i = 0; i < units->unitCount(); ++i) {
            const std::string ref = units->unitAttributeReference(i);
            Debug(false) << " - " << (i + 1) << ": " << ref;
            if (model) {
                Debug() << ", " << model->hasUnits(ref);
            } else {
                Debug() << ", modelless units.";
            }
        }
    }
    Debug() << "*****";
}

void listModelsUnits(const ModelPtr &model)
{
    Debug() << "Model name: " << model->name() << ", units count: " << model->unitsCount();
    for (size_t i = 0; i < model->unitsCount(); ++i) {
        printUnits(model->units(i));
    }
}

} // namespace libcellml
