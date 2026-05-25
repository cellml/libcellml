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

#include "analyser_p.h"
#include "analyserequationast_p.h"

namespace libcellml {

bool containsSymEngineByPredicate(const SEExpression &seExpression, const auto &predicate)
{
    if (predicate(seExpression)) {
        return true;
    }

    for (const auto &arg : seExpression->get_args()) {
        if (containsSymEngineByPredicate(arg, predicate)) {
            return true;
        }
    }

    return false;
}

SEExpression simplifySEExpression(const SEExpression &seExpression)
{
    if (seExpression->get_type_code() == SymEngine::SYMENGINE_EQUALITY) {
        auto args = seExpression->get_args();

        return SymEngine::simplify(SymEngine::Eq(args.front(), SymEngine::expand(args.back())));
    }

    auto simplifiedArgs = [&](const SEExpression &seExpression) {
        SymEngine::vec_basic args;

        args.reserve(seExpression->get_args().size());

        for (const auto &arg : seExpression->get_args()) {
            args.push_back(simplifySEExpression(arg));
        }

        return args;
    };

    if (seExpression->get_type_code() == SymEngine::SYMENGINE_CONSTANT) {
        return seExpression;
    }

    if (seExpression->get_type_code() == SymEngine::SYMENGINE_ADD) {
        return SymEngine::simplify(SymEngine::expand(SymEngine::add(simplifiedArgs(seExpression))));
    }

    if (seExpression->get_type_code() == SymEngine::SYMENGINE_MUL) {
        return SymEngine::simplify(SymEngine::expand(SymEngine::mul(simplifiedArgs(seExpression))));
    }

    if (seExpression->get_type_code() == SymEngine::SYMENGINE_POW) {
        auto args = simplifiedArgs(seExpression);

        return SymEngine::simplify(SymEngine::pow(args.front(), args.back()));
    }

    return SymEngine::simplify(seExpression);
}

SEExpression AnalyserInternalEquation::rearrangeForSESymbol(const SESymbol &seSymbol)
{
    auto isSEExpressionComplex = [&](const auto &self, const SEExpression &seExpression) -> bool {
        if (SymEngine::is_a_Complex(*seExpression)) {
            return true;
        }

        for (const auto &arg : seExpression->get_args()) {
            if (self(self, arg)) {
                return true;
            }
        }

        return false;
    };

    auto containsSESymbol = [&](const SEExpression &seExpression) -> bool {
        auto predicate = [&](const SEExpression &candidate) {
            return (candidate->get_type_code() == SymEngine::SYMENGINE_SYMBOL)
                   && (SymEngine::rcp_static_cast<const SymEngine::Symbol>(candidate)->get_name() == seSymbol->get_name());
        };

        return containsSymEngineByPredicate(seExpression, predicate);
    };

    auto containsAnySESymbol = [&](const SEExpression &seExpression) -> bool {
        auto predicate = [](const SEExpression &candidate) {
            return candidate->get_type_code() == SymEngine::SYMENGINE_SYMBOL;
        };

        return containsSymEngineByPredicate(seExpression, predicate);
    };

    auto filterSolutions = [&](SymEngine::vec_basic solutions) {
        solutions.erase(std::remove_if(solutions.begin(), solutions.end(),
                                       [&](const SEExpression &solution) {
                                           return isSEExpressionComplex(isSEExpressionComplex, solution)
                                                  || containsSESymbol(solution);
                                       }),
                        solutions.end());

        return solutions;
    };

    auto containsSEExp = [&](const SEExpression &seExpression) -> bool {
        auto predicate = [&](const SEExpression &candidate) {
            if (candidate->get_type_code() != SymEngine::SYMENGINE_POW) {
                return false;
            }

            auto args = candidate->get_args();

            return SymEngine::eq(*args.front(), *SymEngine::E);
        };

        return containsSymEngineByPredicate(seExpression, predicate);
    };

    auto containsSELog = [&](const SEExpression &seExpression) -> bool {
        auto predicate = [&](const SEExpression &candidate) {
            return candidate->get_type_code() == SymEngine::SYMENGINE_LOG;
        };

        return containsSymEngineByPredicate(seExpression, predicate);
    };

    auto invertSimpleOddPower = [&](const SEExpression &seExpression) -> SEExpression {
        auto equalityArgs = seExpression->get_args();

        for (size_t i = 0; i < 2; ++i) {
            auto powerSide = equalityArgs[i];
            auto otherSide = equalityArgs[1 - i];

            if (powerSide->get_type_code() != SymEngine::SYMENGINE_POW) {
                continue;
            }

            auto powerArgs = powerSide->get_args();

            if ((powerArgs.front()->get_type_code() != SymEngine::SYMENGINE_SYMBOL)
                || (powerArgs.back()->get_type_code() != SymEngine::SYMENGINE_INTEGER)) {
                continue;
            }

            auto baseSymbol = SymEngine::rcp_static_cast<const SymEngine::Symbol>(powerArgs.front());
            auto exponent = SymEngine::rcp_static_cast<const SymEngine::Integer>(powerArgs.back())->as_int();

            if ((baseSymbol->get_name() == seSymbol->get_name()) && (exponent > 0)) {
                return SymEngine::pow(otherSide, SymEngine::div(SymEngine::integer(1), SymEngine::integer(exponent)));
            }
        }

        return SymEngine::null;
    };

    // Solve the equation for the given variable.

    SymEngine::RCP<const SymEngine::Set> solutionSet;

    try {
        solutionSet = SymEngine::solve(mSEExpression, seSymbol);
    } catch (const std::exception &) {
        // SymEngine failed to solve the equation. This is likely because the variable we are trying to rearrange for is
        // nested within a function that SymEngine cannot invert (e.g., sin(), log()), or because the equation is not a
        // polynomial that SymEngine can handle.

        return SymEngine::null;
    }

    // Filter the solutions to remove any that are complex or that contain the variable we are trying to rearrange for.

    auto solutions = filterSolutions(solutionSet->get_args());

    // If there isn't exactly one solution left, we cannot be sure which one to return, so return null.

    if (solutions.size() != 1) {
        return SymEngine::null;
    }

    auto exactSolution = solutions.front();

    // If the exact solution is fully numeric, convert it to a number node.

    if (!containsAnySESymbol(exactSolution)) {
        return SymEngine::number(SymEngine::eval_double(*exactSolution));
    }

    // The solution is symbolic or could not be reduced to a number, so return the exact solution, but first try to
    // simplify exponentials and logarithms, if there are any.

    auto simplifiedSolution = exactSolution;

    if (containsSEExp(exactSolution) || containsSELog(exactSolution)) {
        simplifiedSolution = simplifySEExpression(exactSolution);
    }

    // Try to do a simple odd-power inversion, if possible.

    auto oddPowerInversion = invertSimpleOddPower(mSEExpression);

    return oddPowerInversion.is_null() ? simplifiedSolution : oddPowerInversion;
}

SEExpressionResult Analyser::AnalyserImpl::astToSymEngine(const AnalyserEquationAstPtr &ast,
                                                          OSName2OSInfoMap *osName2osInfoMap)
{
    // Make sure that we have an AST to convert.

    if (ast == nullptr) {
        return {true, SymEngine::null};
    }

    // If an opaque symbol to AST map is provided and the node type is not natively supported by SymEngine, then we
    // substitute the entire subtree with a fresh opaque symbol so that SymEngine can still manipulate the enclosing
    // expression algebraically.

    auto opaqueSymbol = [&]() -> SEExpressionResult {
        auto name = "__opaque_symbol_" + std::to_string(osName2osInfoMap->size());

        osName2osInfoMap->emplace(name, OSInfo {ast, SymEngine::null});

        return {true, SymEngine::symbol(name)};
    };

    // Types that SymEngine cannot represent natively are substituted with a fresh opaque symbol before we attempt to
    // recurse into their children, so that the children themselves are not converted unnecessarily.

    if (osName2osInfoMap != nullptr) {
        auto astType = ast->type();

        if (astType == AnalyserEquationAst::Type::DIFF) {
            // Create a predictably named opaque symbol using the state variable's SymEngine symbol name so that
            // matchVariableAndEquation() can construct the name directly, without searching the map.

            auto rightAst = ast->rightChild();
            [[maybe_unused]] auto [rightSuccess, right] = astToSymEngine(rightAst, nullptr);
            [[maybe_unused]] auto [leftSuccess, left] = astToSymEngine(ast->leftChild(), nullptr);
            auto name = "__diff_" + SymEngine::rcp_dynamic_cast<const SymEngine::Symbol>(right)->get_name();

            osName2osInfoMap->emplace(name, OSInfo {ast, SymEngine::function_symbol("diff", {left, right})});

            return {true, SymEngine::symbol(name)};
        }

        if (astType == AnalyserEquationAst::Type::PIECEWISE) {
            return opaqueSymbol();
        }
    }

    // Recursively convert the left and right children.

    auto leftAst = ast->leftChild();
    auto rightAst = ast->rightChild();

    auto [leftSuccess, left] = astToSymEngine(leftAst, osName2osInfoMap);
    auto [rightSuccess, right] = astToSymEngine(rightAst, osName2osInfoMap);

    if (!leftSuccess || !rightSuccess) {
        if (osName2osInfoMap != nullptr) {
            return opaqueSymbol();
        }

        return {false, SymEngine::null};
    }

    // Check the AST's type and return its SymEngine equivalent.

    auto astType = ast->type();

    switch (astType) {
        // Equality.

    case AnalyserEquationAst::Type::EQUALITY:
        return {true, SymEngine::Eq(left, right)};

        // Relational and logical operators.

    case AnalyserEquationAst::Type::EQ:
        return {true, SymEngine::Eq(left, right)};
    case AnalyserEquationAst::Type::NEQ:
        return {true, SymEngine::Ne(left, right)};
    case AnalyserEquationAst::Type::LT:
        return {true, SymEngine::Lt(left, right)};
    case AnalyserEquationAst::Type::LEQ:
        return {true, SymEngine::Le(left, right)};
    case AnalyserEquationAst::Type::GT:
        return {true, SymEngine::Gt(left, right)};
    case AnalyserEquationAst::Type::GEQ:
        return {true, SymEngine::Ge(left, right)};
    case AnalyserEquationAst::Type::AND:
    case AnalyserEquationAst::Type::OR:
    case AnalyserEquationAst::Type::XOR: {
        if (!SymEngine::is_a_Boolean(*left) || !SymEngine::is_a_Boolean(*right)) {
            return {false, SymEngine::null};
        }

        auto leftBoolean = SymEngine::rcp_dynamic_cast<const SymEngine::Boolean>(left);
        auto rightBoolean = SymEngine::rcp_dynamic_cast<const SymEngine::Boolean>(right);

        if (astType == AnalyserEquationAst::Type::AND) {
            return {true, SymEngine::logical_and(SymEngine::set_boolean({leftBoolean, rightBoolean}))};
        }

        if (astType == AnalyserEquationAst::Type::OR) {
            return {true, SymEngine::logical_or(SymEngine::set_boolean({leftBoolean, rightBoolean}))};
        }

        return {true, SymEngine::logical_xor(SymEngine::vec_boolean({leftBoolean, rightBoolean}))};
    }
    case AnalyserEquationAst::Type::NOT: {
        if (!SymEngine::is_a_Boolean(*left)) {
            return {false, SymEngine::null};
        }

        return {true, SymEngine::logical_not(SymEngine::rcp_dynamic_cast<const SymEngine::Boolean>(left))};
    }

        // Arithmetic operators.

    case AnalyserEquationAst::Type::PLUS:
        if (!right.is_null()) {
            return {true, SymEngine::add(left, right)};
        }

        return {true, left};
    case AnalyserEquationAst::Type::MINUS:
        if (!right.is_null()) {
            return {true, SymEngine::sub(left, right)};
        }

        return {true, SymEngine::mul(SymEngine::integer(-1), left)};
    case AnalyserEquationAst::Type::TIMES:
        return {true, SymEngine::mul(left, right)};
    case AnalyserEquationAst::Type::DIVIDE:
        return {true, SymEngine::div(left, right)};
    case AnalyserEquationAst::Type::POWER:
        return {true, SymEngine::pow(left, right)};
    case AnalyserEquationAst::Type::ROOT:
        if (!right.is_null()) {
            return {true, SymEngine::pow(right, SymEngine::div(SymEngine::integer(1), left))};
        }

        return {true, SymEngine::pow(left, SymEngine::div(SymEngine::integer(1), SymEngine::integer(2)))};
    case AnalyserEquationAst::Type::ABS:
        return {true, SymEngine::abs(left)};
    case AnalyserEquationAst::Type::EXP:
        return {true, SymEngine::exp(left)};
    case AnalyserEquationAst::Type::LN:
        return {true, SymEngine::log(left)};
    case AnalyserEquationAst::Type::LOG:
        if (!right.is_null()) {
            return {true, SymEngine::div(SymEngine::log(right), SymEngine::log(left))};
        }

        return {true, SymEngine::div(SymEngine::log(left), SymEngine::log(SymEngine::integer(10)))};
    case AnalyserEquationAst::Type::CEILING:
        return {true, SymEngine::ceiling(left)};
    case AnalyserEquationAst::Type::FLOOR:
        return {true, SymEngine::floor(left)};
    case AnalyserEquationAst::Type::MIN:
        return {true, SymEngine::min({left, right})};
    case AnalyserEquationAst::Type::MAX:
        return {true, SymEngine::max({left, right})};
    case AnalyserEquationAst::Type::REM:
        return {true, SymEngine::function_symbol("mod", {left, right})};

        // Calculus elements.

    case AnalyserEquationAst::Type::DIFF:
        return {true, SymEngine::function_symbol("diff", {left, right})};

        // Trigonometric operators.

    case AnalyserEquationAst::Type::SIN:
        return {true, SymEngine::sin(left)};
    case AnalyserEquationAst::Type::COS:
        return {true, SymEngine::cos(left)};
    case AnalyserEquationAst::Type::TAN:
        return {true, SymEngine::tan(left)};
    case AnalyserEquationAst::Type::SEC:
        return {true, SymEngine::sec(left)};
    case AnalyserEquationAst::Type::CSC:
        return {true, SymEngine::csc(left)};
    case AnalyserEquationAst::Type::COT:
        return {true, SymEngine::cot(left)};
    case AnalyserEquationAst::Type::SINH:
        return {true, SymEngine::sinh(left)};
    case AnalyserEquationAst::Type::COSH:
        return {true, SymEngine::cosh(left)};
    case AnalyserEquationAst::Type::TANH:
        return {true, SymEngine::tanh(left)};
    case AnalyserEquationAst::Type::SECH:
        return {true, SymEngine::sech(left)};
    case AnalyserEquationAst::Type::CSCH:
        return {true, SymEngine::csch(left)};
    case AnalyserEquationAst::Type::COTH:
        return {true, SymEngine::coth(left)};
    case AnalyserEquationAst::Type::ASIN:
        return {true, SymEngine::asin(left)};
    case AnalyserEquationAst::Type::ACOS:
        return {true, SymEngine::acos(left)};
    case AnalyserEquationAst::Type::ATAN:
        return {true, SymEngine::atan(left)};
    case AnalyserEquationAst::Type::ASEC:
        return {true, SymEngine::asec(left)};
    case AnalyserEquationAst::Type::ACSC:
        return {true, SymEngine::acsc(left)};
    case AnalyserEquationAst::Type::ACOT:
        return {true, SymEngine::acot(left)};
    case AnalyserEquationAst::Type::ASINH:
        return {true, SymEngine::asinh(left)};
    case AnalyserEquationAst::Type::ACOSH:
        return {true, SymEngine::acosh(left)};
    case AnalyserEquationAst::Type::ATANH:
        return {true, SymEngine::atanh(left)};
    case AnalyserEquationAst::Type::ASECH:
        return {true, SymEngine::asech(left)};
    case AnalyserEquationAst::Type::ACSCH:
        return {true, SymEngine::acsch(left)};
    case AnalyserEquationAst::Type::ACOTH:
        return {true, SymEngine::acoth(left)};

        // Token elements.

    case AnalyserEquationAst::Type::CI: {
        auto aiVariable = internalVariable(ast->variable());

        if (mAIVariable2SESymbolMap.find(aiVariable) == mAIVariable2SESymbolMap.end()) {
            // We haven't yet created a SymEngine symbol for this internal variable, so create one (making sure that its
            // name is unique) and add it to mAIVariable2SESymbolMap and mSESymbol2AIVariableMap.

            auto variableName = aiVariable->mVariable->name();
            auto uniqueSeVariable = SymEngine::symbol(variableName);
            auto uniqueVariableNameIndex = MAX_SIZE_T;

            while (mSESymbol2AIVariableMap.find(uniqueSeVariable) != mSESymbol2AIVariableMap.end()) {
                uniqueSeVariable = SymEngine::symbol(variableName + "_" + convertToString(++uniqueVariableNameIndex));
            }

            auto seVariable = std::move(uniqueSeVariable);

            mAIVariable2SESymbolMap[aiVariable] = seVariable;
            mSESymbol2AIVariableMap[seVariable] = aiVariable;
        }

        return {true, mAIVariable2SESymbolMap.at(aiVariable)};
    }
    case AnalyserEquationAst::Type::CN: {
        // Whole CN values should be converted to integers, so that SymEngine can simplify them properly.

        auto cnValue = std::stod(ast->value());
        auto roundedCnValue = std::llround(cnValue);

        if (areNearlyEqual(cnValue, static_cast<double>(roundedCnValue))) {
            return {true, SymEngine::integer(roundedCnValue)};
        }

        return {true, SymEngine::number(cnValue)};
    }

        // Qualifier elements.

    case AnalyserEquationAst::Type::DEGREE:
    case AnalyserEquationAst::Type::LOGBASE:
    case AnalyserEquationAst::Type::BVAR:
        return {true, left};

        // Constants.

    case AnalyserEquationAst::Type::TRUE:
        return {true, SymEngine::number(1.0)};
    case AnalyserEquationAst::Type::FALSE:
        return {true, SymEngine::number(0.0)};
    case AnalyserEquationAst::Type::E:
        return {true, SymEngine::E};
    case AnalyserEquationAst::Type::PI:
        return {true, SymEngine::pi};
    case AnalyserEquationAst::Type::INF:
        return {true, SymEngine::Inf};
    default:
        // Conversion is not possible with this type. So, substitute the entire subtree with a fresh opaque symbol if an
        // opaque symbol to AST map is provided.

        if (osName2osInfoMap != nullptr) {
            return opaqueSymbol();
        }

        return {false, SymEngine::null};
    }
}

AnalyserEquationAstPtr Analyser::AnalyserImpl::simplifyAst(const AnalyserEquationAstPtr &ast)
{
    auto cnValue = [](const AnalyserEquationAstPtr &ast, double &value) -> bool {
        if ((ast == nullptr) || (ast->type() != AnalyserEquationAst::Type::CN)) {
            return false;
        }

        value = std::stod(ast->value());

        return true;
    };

    auto isCnValue = [&cnValue](const AnalyserEquationAstPtr &ast, double value) {
        double astValue;

        if (!cnValue(ast, astValue)) {
            return false;
        }

        return areNearlyEqual(astValue, value);
    };

    auto makeUnaryMinus = [&](const AnalyserEquationAstPtr &child, const AnalyserEquationAstPtr &parentAst) {
        auto res = AnalyserEquationAst::create();

        res->setType(AnalyserEquationAst::Type::MINUS);
        res->setParent(parentAst);
        res->setLeftChild(child);

        child->setParent(res);

        return simplifyAst(res);
    };

    auto makeCnNode = [](double value, const AnalyserEquationAstPtr &parentAst) {
        auto res = AnalyserEquationAst::create();

        res->setType(AnalyserEquationAst::Type::CN);
        res->setValue(convertToString(value));
        res->setParent(parentAst);

        return res;
    };

    // Recursively simplify the given AST's children first.

    if (ast == nullptr) {
        return ast;
    }

    auto leftAst = simplifyAst(ast->leftChild());
    auto rightAst = simplifyAst(ast->rightChild());

    if (leftAst != ast->leftChild()) {
        ast->setLeftChild(leftAst);
    }

    if (rightAst != ast->rightChild()) {
        ast->setRightChild(rightAst);
    }

    if (leftAst != nullptr) {
        leftAst->setParent(ast);
    }

    auto rightExists = rightAst != nullptr;

    if (rightExists) {
        rightAst->setParent(ast);
    }

    // Attempt to simplify the given AST based on its type and the types and values of its children.

    double leftValue;
    auto leftIsConstant = false;
    auto leftIsZero = false;
    auto leftIsOne = false;
    auto leftIsNegOne = false;

    if (cnValue(leftAst, leftValue)) {
        leftIsConstant = true;
        leftIsZero = areNearlyEqual(leftValue, 0.0);
        leftIsOne = areNearlyEqual(leftValue, 1.0);
        leftIsNegOne = areNearlyEqual(leftValue, -1.0);
    }

    double rightValue;
    auto rightIsConstant = false;
    auto rightIsZero = false;
    auto rightIsOne = false;
    auto rightIsNegOne = false;

    if (cnValue(rightAst, rightValue)) {
        rightIsConstant = true;
        rightIsZero = areNearlyEqual(rightValue, 0.0);
        rightIsOne = areNearlyEqual(rightValue, 1.0);
        rightIsNegOne = areNearlyEqual(rightValue, -1.0);
    }

    switch (ast->type()) {
        // Relational and logical operators.

    case AnalyserEquationAst::Type::EQ:
        // a == b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(areNearlyEqual(leftValue, rightValue) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::NEQ:
        // a != b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(!areNearlyEqual(leftValue, rightValue) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::LT:
        // a < b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((leftValue < rightValue) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::LEQ:
        // a <= b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((leftValue <= rightValue) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::GT:
        // a > b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((leftValue > rightValue) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::GEQ:
        // a >= b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((leftValue >= rightValue) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::AND:
        // a && b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((!leftIsZero && !rightIsZero) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::OR:
        // a || b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((!leftIsZero || !rightIsZero) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::XOR:
        // a xor b -> 1.0 or 0.0 (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode((!leftIsZero != !rightIsZero) ? 1.0 : 0.0, ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::NOT:
        // !a -> 1.0 or 0.0 (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(leftIsZero ? 1.0 : 0.0, ast->parent());
        }

        break;

        // Arithmetic operators.

    case AnalyserEquationAst::Type::PLUS: {
        if (rightExists) {
            // Binary plus cases.

            // a + b -> c (where a and b are constants).

            if (leftIsConstant && rightIsConstant) {
                return makeCnNode(leftValue + rightValue, ast->parent());
            }

            // 0.0 + a -> a.

            if (leftIsZero) {
                rightAst->setParent(ast->parent());

                return rightAst;
            }

            // a + 0.0 -> a.

            if (rightIsZero) {
                leftAst->setParent(ast->parent());

                return leftAst;
            }
        } else {
            // Unary plus cases.

            // +a -> a.

            leftAst->setParent(ast->parent());

            return leftAst;
        }

        break;
    }
    case AnalyserEquationAst::Type::MINUS:
        if (rightExists) {
            // Binary minus cases.

            // a - b -> c (where a and b are constants).

            if (leftIsConstant && rightIsConstant) {
                return makeCnNode(leftValue - rightValue, ast->parent());
            }

            // 0.0 - a -> -a.

            if (leftIsZero) {
                return makeUnaryMinus(rightAst, ast->parent());
            }

            // a - 0.0 -> a.

            if (rightIsZero) {
                leftAst->setParent(ast->parent());

                return leftAst;
            }
        } else {
            // Unary minus cases.

            // -a -> b (where a is a constant).

            if (leftIsConstant) {
                return makeCnNode(-leftValue, ast->parent());
            }

            // -(-a) -> a.

            auto leftAstRightChild = leftAst->rightChild();

            if ((leftAst->type() == AnalyserEquationAst::Type::MINUS)
                && (leftAstRightChild == nullptr)) {
                auto res = leftAst->leftChild();

                res->setParent(ast->parent());

                return res;
            }

            // Push the negation down to the leaves of additive/subtractive trees (i.e. -(a + b - c) -> -a - b + c).

            auto negateAdditiveSubtree = [&](const auto &selfNegate, const AnalyserEquationAstPtr &subtree,
                                             const AnalyserEquationAstPtr &parentAst) -> AnalyserEquationAstPtr {
                // -(a + b) -> -a - b.

                if (subtree->type() == AnalyserEquationAst::Type::PLUS) {
                    auto res = AnalyserEquationAst::create();

                    res->setType(AnalyserEquationAst::Type::PLUS);
                    res->setParent(parentAst);

                    auto negatedLeft = selfNegate(selfNegate, subtree->leftChild(), res);
                    auto negatedRight = selfNegate(selfNegate, subtree->rightChild(), res);

                    res->setLeftChild(negatedLeft);
                    res->setRightChild(negatedRight);

                    negatedLeft->setParent(res);
                    negatedRight->setParent(res);

                    return simplifyAst(res);
                }

                // -(a - b) -> -a + b.

                if ((subtree->type() == AnalyserEquationAst::Type::MINUS)
                    && (subtree->rightChild() != nullptr)) {
                    auto res = AnalyserEquationAst::create();

                    res->setType(AnalyserEquationAst::Type::PLUS);
                    res->setParent(parentAst);

                    auto negatedLeft = selfNegate(selfNegate, subtree->leftChild(), res);
                    auto right = subtree->rightChild();

                    res->setLeftChild(negatedLeft);
                    res->setRightChild(right);

                    negatedLeft->setParent(res);
                    right->setParent(res);

                    return simplifyAst(res);
                }

                return makeUnaryMinus(subtree, parentAst);
            };

            // -(a ± b) -> -a ∓ b.

            auto leftAstType = leftAst->type();

            if ((leftAstType == AnalyserEquationAst::Type::PLUS)
                || (leftAstType == AnalyserEquationAst::Type::MINUS)) {
                return simplifyAst(negateAdditiveSubtree(negateAdditiveSubtree, leftAst, ast->parent()));
            }

            // -((a ± b) */ c) -> (-a ∓ -b) */ c.

            auto leftAstLeftChild = leftAst->leftChild();

            if (((leftAstType == AnalyserEquationAst::Type::TIMES) || (leftAstType == AnalyserEquationAst::Type::DIVIDE))
                && ((leftAstLeftChild->type() == AnalyserEquationAst::Type::PLUS)
                    || (leftAstLeftChild->type() == AnalyserEquationAst::Type::MINUS))) {
                auto res = AnalyserEquationAst::create();

                res->setType(leftAstType);
                res->setParent(ast->parent());

                auto negatedLeft = negateAdditiveSubtree(negateAdditiveSubtree, leftAstLeftChild, res);
                auto right = leftAstRightChild;

                res->setLeftChild(negatedLeft);
                res->setRightChild(right);

                negatedLeft->setParent(res);
                right->setParent(res);

                return simplifyAst(res);
            }
        }

        break;
    case AnalyserEquationAst::Type::TIMES: {
        // a * b -> c (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(leftValue * rightValue, ast->parent());
        }

        // 0.0 * a -> 0.0.

        if (leftIsZero) {
            return makeCnNode(0.0, ast->parent());
        }

        // a * 0.0 -> 0.0.

        if (rightIsZero) {
            return makeCnNode(0.0, ast->parent());
        }

        // 1.0 * a -> a.

        if (leftIsOne) {
            rightAst->setParent(ast->parent());

            return rightAst;
        }

        // a * 1.0 -> a.

        if (rightIsOne) {
            leftAst->setParent(ast->parent());

            return leftAst;
        }

        // -1.0 * a -> -a.

        if (leftIsNegOne) {
            return makeUnaryMinus(rightAst, ast->parent());
        }

        // a * -1.0 -> -a.

        if (rightIsNegOne) {
            return makeUnaryMinus(leftAst, ast->parent());
        }

        // ( 1.0 / a ) * b -> b / a.

        if ((leftAst->type() == AnalyserEquationAst::Type::DIVIDE) && isCnValue(leftAst->leftChild(), 1.0)) {
            auto res = AnalyserEquationAst::create();
            auto leftAstRightChild = leftAst->rightChild();

            res->setType(AnalyserEquationAst::Type::DIVIDE);
            res->setParent(ast->parent());
            res->setLeftChild(rightAst);
            res->setRightChild(leftAstRightChild);

            rightAst->setParent(res);
            leftAstRightChild->setParent(res);

            return simplifyAst(res);
        }

        // a * ( 1.0 / b ) -> a / b.

        if ((rightAst->type() == AnalyserEquationAst::Type::DIVIDE) && isCnValue(rightAst->leftChild(), 1.0)) {
            auto res = AnalyserEquationAst::create();
            auto rightAstRightChild = rightAst->rightChild();

            res->setType(AnalyserEquationAst::Type::DIVIDE);
            res->setParent(ast->parent());
            res->setLeftChild(leftAst);
            res->setRightChild(rightAstRightChild);

            leftAst->setParent(res);
            rightAstRightChild->setParent(res);

            return simplifyAst(res);
        }

        break;
    }
    case AnalyserEquationAst::Type::DIVIDE: {
        // a / b -> c (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(leftValue / rightValue, ast->parent());
        }

        // 0.0 / a -> 0.0.

        if (leftIsZero) {
            return makeCnNode(0.0, ast->parent());
        }

        // a / 1.0 -> a.

        if (rightIsOne) {
            leftAst->setParent(ast->parent());

            return leftAst;
        }

        // a / -1.0 -> -a.

        if (rightIsNegOne) {
            return makeUnaryMinus(leftAst, ast->parent());
        }

        // 1.0 / (1.0 / a) -> a.

        if (leftIsOne && (rightAst->type() == AnalyserEquationAst::Type::DIVIDE)
            && isCnValue(rightAst->leftChild(), 1.0)) {
            auto res = rightAst->rightChild();

            res->setParent(ast->parent());

            return res;
        }

        break;
    }
    case AnalyserEquationAst::Type::POWER: {
        // a ^ b -> c (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(std::pow(leftValue, rightValue), ast->parent());
        }

        // a ^ 0.0 -> 1.0.

        if (rightIsZero) {
            return makeCnNode(1.0, ast->parent());
        }

        // 0.0 ^ a -> 0.0.
        // Note: the case of 0.0^0.0 is already handled by the a^b -> c case above, since both 0.0 and 0.0 are
        //       constants.

        if (leftIsZero) {
            return makeCnNode(0.0, ast->parent());
        }

        // 1.0 ^ a -> 1.0.

        if (leftIsOne) {
            return makeCnNode(1.0, ast->parent());
        }

        // a ^ 1.0 -> a.

        if (rightIsOne) {
            leftAst->setParent(ast->parent());

            return leftAst;
        }

        // a ^ -1.0 -> 1.0 / a.

        if (rightIsNegOne) {
            auto res = AnalyserEquationAst::create();

            res->setType(AnalyserEquationAst::Type::DIVIDE);
            res->setParent(ast->parent());
            res->setLeftChild(makeCnNode(1.0, ast));
            res->setRightChild(leftAst);

            leftAst->setParent(res);

            return simplifyAst(res);
        }

        break;
    }
    case AnalyserEquationAst::Type::ROOT: {
        if (leftAst->type() == AnalyserEquationAst::Type::DEGREE) {
            auto degreeAst = leftAst->leftChild();
            double degreeValue;

            if (cnValue(degreeAst, degreeValue)) {
                // root(a, b) -> c (where a and b are constants).

                if (rightIsConstant) {
                    return makeCnNode(std::pow(rightValue, 1.0 / degreeValue), ast->parent());
                }
            }
        } else {
            // sqrt(a) -> b (where a is a constant).

            if (leftIsConstant) {
                return makeCnNode(std::sqrt(leftValue), ast->parent());
            }
        }

        break;
    }
    case AnalyserEquationAst::Type::ABS:
        // |a| -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::abs(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::EXP:
        // exp(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::exp(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::LN:
        // ln(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::log(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::LOG:
        if (leftAst->type() == AnalyserEquationAst::Type::LOGBASE) {
            auto logBaseAst = leftAst->leftChild();
            double logBaseValue;

            if (cnValue(logBaseAst, logBaseValue)) {
                // log(a, b) -> c (where a and b are constants).

                if (rightIsConstant) {
                    return makeCnNode(std::pow(rightValue, 1.0 / logBaseValue), ast->parent());
                }
            }
        } else {
            // log(a) -> b (where a is a constant).

            if (leftIsConstant) {
                return makeCnNode(std::log(leftValue) / std::log(10.0), ast->parent());
            }
        }

        break;
    case AnalyserEquationAst::Type::CEILING:
        // ceiling(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::ceil(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::FLOOR:
        // floor(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::floor(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::MIN:
        // min(a, b) -> c (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(std::min(leftValue, rightValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::MAX:
        // max(a, b) -> c (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(std::max(leftValue, rightValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::REM:
        // rem(a, b) -> c (where a and b are constants).

        if (leftIsConstant && rightIsConstant) {
            return makeCnNode(std::fmod(leftValue, rightValue), ast->parent());
        }

        break;

        // Trigonometric operators.

    case AnalyserEquationAst::Type::SIN:
        // sin(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::sin(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::COS:
        // cos(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::cos(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::TAN:
        // tan(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::tan(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::SEC:
        // sec(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(1.0 / std::cos(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::CSC:
        // csc(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(1.0 / std::sin(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::COT:
        // cot(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(1.0 / std::tan(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::SINH:
        // sinh(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::sinh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::COSH:
        // cosh(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::cosh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::TANH:
        // tanh(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::tanh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::SECH:
        // sech(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(1.0 / std::cosh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::CSCH:
        // csch(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(1.0 / std::sinh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::COTH:
        // coth(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(1.0 / std::tanh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ASIN:
        // asin(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::asin(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ACOS:
        // acos(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::acos(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ATAN:
        // atan(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::atan(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ASEC:
        // asec(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::acos(1.0 / leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ACSC:
        // acsc(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::asin(1.0 / leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ACOT:
        // acot(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::atan(1.0 / leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ASINH:
        // asinh(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::asinh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ACOSH:
        // acosh(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::acosh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ATANH:
        // atanh(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::atanh(leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ASECH:
        // asech(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::acosh(1.0 / leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ACSCH:
        // acsch(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::asinh(1.0 / leftValue), ast->parent());
        }

        break;
    case AnalyserEquationAst::Type::ACOTH:
        // acoth(a) -> b (where a is a constant).

        if (leftIsConstant) {
            return makeCnNode(std::atanh(1.0 / leftValue), ast->parent());
        }

        break;
    default:
        break;
    }

    return ast;
}

AnalyserEquationAstPtr Analyser::AnalyserImpl::symEngineToAst(const SEExpression &seExpression,
                                                              const AnalyserEquationAstPtr &parentAst,
                                                              const OSName2OSInfoMap *osName2osInfoMap)
{
    // Swap the LHS and RHS of the equation, if needed.

    auto seExpressionArgs = seExpression->get_args();
    auto seExpressionArgsSize = seExpressionArgs.size();
    auto seExpressionLhs = (seExpressionArgsSize > 0) ? seExpressionArgs.front() : SEExpression();
    auto seExpressionRhs = (seExpressionArgsSize > 1) ? seExpressionArgs.back() : SEExpression();

    if ((parentAst == nullptr)
        && ((osName2osInfoMap != nullptr)
            || (seExpressionLhs->get_type_code() != SymEngine::SYMENGINE_SYMBOL))) {
        std::swap(seExpressionArgs.front(), seExpressionArgs.back());
    }

    // Our top AST node.

    auto res = AnalyserEquationAst::create();

    res->setParent(parentAst);

    // Check the type of the SymEngine expression and return its AST equivalent, recursively converting its arguments as
    // needed.

    auto cnValueString = [](double value) {
        auto res = convertToString(value);

        if ((res.find('.') == std::string::npos) && (res.find('e') == std::string::npos)) {
            res += ".0";
        }

        return res;
    };

    auto currentAst = res;

    switch (seExpression->get_type_code()) {
        // Relational and logical operators.

    case SymEngine::SYMENGINE_EQUALITY:
        // Convert to either AnalyserEquationAst::Type::EQUALITY or AnalyserEquationAst::Type::EQ depending on whether
        // we are at the top level or not.

        currentAst->setType((parentAst == nullptr) ?
                                AnalyserEquationAst::Type::EQUALITY :
                                AnalyserEquationAst::Type::EQ);

        break;
    case SymEngine::SYMENGINE_UNEQUALITY:
        currentAst->setType(AnalyserEquationAst::Type::NEQ);

        break;
    case SymEngine::SYMENGINE_STRICTLESSTHAN:
        currentAst->setType(AnalyserEquationAst::Type::LT);

        break;
    case SymEngine::SYMENGINE_LESSTHAN:
        currentAst->setType(AnalyserEquationAst::Type::LEQ);

        break;

        // Note: AnalyserEquationAst::Type::GT and AnalyserEquationAst::Type::GEQ are not accounted for since SymEngine
        //       doesn't have strict greater than and greater than or equal to operators.

    case SymEngine::SYMENGINE_AND:
        currentAst->setType(AnalyserEquationAst::Type::AND);

        break;
    case SymEngine::SYMENGINE_OR:
        currentAst->setType(AnalyserEquationAst::Type::OR);

        break;
    case SymEngine::SYMENGINE_XOR:
        currentAst->setType(AnalyserEquationAst::Type::XOR);

        break;
    case SymEngine::SYMENGINE_NOT:
        currentAst->setType(AnalyserEquationAst::Type::NOT);

        break;

        // Arithmetic operators.

    case SymEngine::SYMENGINE_ADD:
        currentAst->setType(AnalyserEquationAst::Type::PLUS);

        break;

        // Note: AnalyserEquationAst::Type::MINUS is not accounted for since SymEngine doesn't have a minus operator.

    case SymEngine::SYMENGINE_MUL:
        currentAst->setType(AnalyserEquationAst::Type::TIMES);

        break;

        // Note: AnalyserEquationAst::Type::DIVIDE is not accounted for since SymEngine doesn't have a divide operator.

    case SymEngine::SYMENGINE_POW: {
        auto base = seExpressionArgs.front();

        if ((base->get_type_code() == SymEngine::SYMENGINE_CONSTANT)
            && SymEngine::eq(*SymEngine::rcp_static_cast<const SymEngine::Constant>(base), *SymEngine::E)) {
            currentAst->setType(AnalyserEquationAst::Type::EXP);
            currentAst->setLeftChild(symEngineToAst(seExpressionArgs.back(), currentAst, osName2osInfoMap));

            return res;
        }

        currentAst->setType(AnalyserEquationAst::Type::POWER);

        break;
    }

        // Note: AnalyserEquationAst::Type::ROOT is not accounted for since SymEngine doesn't have a root operator.

    case SymEngine::SYMENGINE_ABS:
        currentAst->setType(AnalyserEquationAst::Type::ABS);

        break;

        // Note: AnalyserEquationAst::Type::EXP is not accounted for since SymEngine doesn't have an exponential
        //       operator.

    case SymEngine::SYMENGINE_LOG:
        currentAst->setType(AnalyserEquationAst::Type::LN);

        break;

        // Note: SymEngine doesn't have a log function with a base argument, so although we can easily convert
        //       AnalyserEquationAst::Type::LOG to SymEngine::SYMENGINE_LOG, to do the reverse is a bit more involved
        //       and not worth the effort at the moment, so we just convert SymEngine::SYMENGINE_LOG to
        //       AnalyserEquationAst::Type::LN.

    case SymEngine::SYMENGINE_CEILING:
        currentAst->setType(AnalyserEquationAst::Type::CEILING);

        break;
    case SymEngine::SYMENGINE_FLOOR:
        currentAst->setType(AnalyserEquationAst::Type::FLOOR);

        break;
    case SymEngine::SYMENGINE_MIN:
        currentAst->setType(AnalyserEquationAst::Type::MIN);

        break;
    case SymEngine::SYMENGINE_MAX:
        currentAst->setType(AnalyserEquationAst::Type::MAX);

        break;

        // Note: AnalyserEquationAst::Type::REM is accounted for in the default case since SymEngine doesn't have a
        //       built-in remainder function, so we converted it to a function symbol with the name "mod".

        // Calculus elements.

        // Note: we handle derivatives separately, so we are not accounting for SymEngine::SYMENGINE_DERIVATIVE here.

        // Trigonometric operators.

    case SymEngine::SYMENGINE_SIN:
        currentAst->setType(AnalyserEquationAst::Type::SIN);

        break;
    case SymEngine::SYMENGINE_COS:
        currentAst->setType(AnalyserEquationAst::Type::COS);

        break;
    case SymEngine::SYMENGINE_TAN:
        currentAst->setType(AnalyserEquationAst::Type::TAN);

        break;
    case SymEngine::SYMENGINE_SEC:
        currentAst->setType(AnalyserEquationAst::Type::SEC);

        break;
    case SymEngine::SYMENGINE_CSC:
        currentAst->setType(AnalyserEquationAst::Type::CSC);

        break;
    case SymEngine::SYMENGINE_COT:
        currentAst->setType(AnalyserEquationAst::Type::COT);

        break;
    case SymEngine::SYMENGINE_SINH:
        currentAst->setType(AnalyserEquationAst::Type::SINH);

        break;
    case SymEngine::SYMENGINE_COSH:
        currentAst->setType(AnalyserEquationAst::Type::COSH);

        break;
    case SymEngine::SYMENGINE_TANH:
        currentAst->setType(AnalyserEquationAst::Type::TANH);

        break;
    case SymEngine::SYMENGINE_SECH:
        currentAst->setType(AnalyserEquationAst::Type::SECH);

        break;
    case SymEngine::SYMENGINE_CSCH:
        currentAst->setType(AnalyserEquationAst::Type::CSCH);

        break;
    case SymEngine::SYMENGINE_COTH:
        currentAst->setType(AnalyserEquationAst::Type::COTH);

        break;
    case SymEngine::SYMENGINE_ASIN:
        currentAst->setType(AnalyserEquationAst::Type::ASIN);

        break;
    case SymEngine::SYMENGINE_ACOS:
        currentAst->setType(AnalyserEquationAst::Type::ACOS);

        break;
    case SymEngine::SYMENGINE_ATAN:
        currentAst->setType(AnalyserEquationAst::Type::ATAN);

        break;
    case SymEngine::SYMENGINE_ASEC:
        currentAst->setType(AnalyserEquationAst::Type::ASEC);

        break;
    case SymEngine::SYMENGINE_ACSC:
        currentAst->setType(AnalyserEquationAst::Type::ACSC);

        break;
    case SymEngine::SYMENGINE_ACOT:
        currentAst->setType(AnalyserEquationAst::Type::ACOT);

        break;
    case SymEngine::SYMENGINE_ASINH:
        currentAst->setType(AnalyserEquationAst::Type::ASINH);

        break;
    case SymEngine::SYMENGINE_ACOSH:
        currentAst->setType(AnalyserEquationAst::Type::ACOSH);

        break;
    case SymEngine::SYMENGINE_ATANH:
        currentAst->setType(AnalyserEquationAst::Type::ATANH);

        break;
    case SymEngine::SYMENGINE_ASECH:
        currentAst->setType(AnalyserEquationAst::Type::ASECH);

        break;
    case SymEngine::SYMENGINE_ACSCH:
        currentAst->setType(AnalyserEquationAst::Type::ACSCH);

        break;
    case SymEngine::SYMENGINE_ACOTH:
        currentAst->setType(AnalyserEquationAst::Type::ACOTH);

        break;

        // Token elements.

    case SymEngine::SYMENGINE_SYMBOL: {
        // If the symbol is an opaque placeholder for a non-SymEngine-native AST subtree, then we substitute it back.

        auto seSymbol = SymEngine::rcp_dynamic_cast<const SymEngine::Symbol>(seExpression);

        if (osName2osInfoMap != nullptr) {
            auto it = osName2osInfoMap->find(seSymbol->get_name());

            if (it != osName2osInfoMap->end()) {
                return it->second.ast->clone(parentAst);
            }
        }

        // Otherwise, it's a regular variable.

        currentAst->setType(AnalyserEquationAst::Type::CI);
        currentAst->setVariable(mSESymbol2AIVariableMap.at(seSymbol)->mVariable);

        break;
    }
    case SymEngine::SYMENGINE_INTEGER:
        currentAst->setType(AnalyserEquationAst::Type::CN);
        currentAst->setValue(cnValueString(static_cast<double>(std::stoll(seExpression->__str__()))));

        break;
    case SymEngine::SYMENGINE_REAL_DOUBLE:
        currentAst->setType(AnalyserEquationAst::Type::CN);
        currentAst->setValue(cnValueString(std::stod(seExpression->__str__())));

        break;
    case SymEngine::SYMENGINE_RATIONAL: {
        currentAst->setType(AnalyserEquationAst::Type::CN);
        currentAst->setValue(cnValueString(SymEngine::eval_double(*seExpression)));

        break;
    }

        // Qualifier elements.

        // Note: we don't need to account for AnalyserEquationAst::Type::DEGREE, AnalyserEquationAst::Type::LOGBASE, and
        //       AnalyserEquationAst::Type::BVAR since we already account for them elsewhere.

        // Constants.

        // Note: we don't need to account for AnalyserEquationAst::Type::TRUE and AnalyserEquationAst::Type::FALSE. We
        //       use SymEngine::number(1.0) and SymEngine::number(0.0) to represent true and false, respectively, so
        //       they are converted to CN nodes rather than TRUE and FALSE nodes.

    case SymEngine::SYMENGINE_CONSTANT:
        // It must be either e or π.

        if (SymEngine::eq(*SymEngine::rcp_dynamic_cast<const SymEngine::Constant>(seExpression), *SymEngine::E)) {
            currentAst->setType(AnalyserEquationAst::Type::E);
        } else {
            currentAst->setType(AnalyserEquationAst::Type::PI);
        }

        break;
    case SymEngine::SYMENGINE_INFTY:
        currentAst->setType(AnalyserEquationAst::Type::INF);

        break;
    default: { // SymEngine::SYMENGINE_FUNCTIONSYMBOL.
        auto functionName = SymEngine::rcp_dynamic_cast<const SymEngine::FunctionSymbol>(seExpression)->get_name();

        if (functionName == "diff") {
            currentAst->setType(AnalyserEquationAst::Type::DIFF);

            auto bVarAst = AnalyserEquationAst::create();

            bVarAst->setType(AnalyserEquationAst::Type::BVAR);
            bVarAst->setParent(currentAst);
            bVarAst->setLeftChild(symEngineToAst(seExpressionLhs, bVarAst, osName2osInfoMap));

            currentAst->setLeftChild(bVarAst);
            currentAst->setRightChild(symEngineToAst(seExpressionRhs, currentAst, osName2osInfoMap));

            return res;
        }

        // "mod".

        currentAst->setType(AnalyserEquationAst::Type::REM);

        break;
    }
    }

    // All arguments (except the last one) are guaranteed to be left arguments in the AST tree.

    for (size_t i = 0; i + 1 < seExpressionArgsSize; ++i) {
        currentAst->setLeftChild(symEngineToAst(seExpressionArgs[i], currentAst, osName2osInfoMap));

        if (i < seExpressionArgsSize - 2) {
            // There are more than two arguments left, so we need to create a copy of our original AST node.

            auto ast = AnalyserEquationAst::create();

            ast->setType(currentAst->type());
            ast->setParent(currentAst);
            ast->setValue(currentAst->value());
            ast->setVariable(currentAst->variable());

            currentAst->setRightChild(ast);

            currentAst = ast;
        }
    }

    // The last argument is created and placed where appropriate.

    if (seExpressionArgsSize > 0) {
        auto childAst = symEngineToAst(seExpressionArgs.back(), currentAst, osName2osInfoMap);

        if (seExpressionArgsSize == 1) {
            currentAst->setLeftChild(childAst);
        } else {
            currentAst->setRightChild(childAst);
        }
    }

    return res;
}

void Analyser::AnalyserImpl::replaceAstTree(const AnalyserInternalEquationPtr &equation, const AnalyserEquationAstPtr &ast)
{
    equation->mAst = ast;

    equation->mDependencies.clear();

    equation->mVariables.clear();
    equation->mStateVariables.clear();
    equation->mAllVariables.clear();

    AnalyserEquationAstPtrs astStack;

    astStack.push_back(ast);

    do {
        auto crtAst = astStack.back();

        astStack.pop_back();

        if (crtAst->type() == AnalyserEquationAst::Type::CI) {
            auto astVariable = crtAst->variable();

            if (crtAst->parent()->type() == AnalyserEquationAst::Type::DIFF) {
                equation->addStateVariable(internalVariable(astVariable));
            } else if (crtAst->parent()->type() != AnalyserEquationAst::Type::BVAR) {
                equation->addVariable(internalVariable(astVariable));
            }
        }

        if (crtAst->leftChild() != nullptr) {
            astStack.push_back(crtAst->leftChild());
        }

        if (crtAst->rightChild() != nullptr) {
            astStack.push_back(crtAst->rightChild());
        }
    } while (!astStack.empty());
}

void Analyser::AnalyserImpl::updateEquationFromSEExpression(const AnalyserInternalEquationPtr &equation,
                                                            const SEExpression &seExpression)
{
    equation->mSEExpression = simplifySEExpression(seExpression);

    replaceAstTree(equation, simplifyAst(symEngineToAst(equation->mSEExpression)));
}

void Analyser::AnalyserImpl::makeVariableKnown(const AnalyserInternalVariablePtr &variable,
                                               const AnalyserInternalEquationPtr &equation)
{
    // Update all the other equations to consider this variable known.

    for (const auto &otherEquation : variable->mUnmatchedEquations) {
        // Add the variable as a dependency for the equation, but only if it isn't the equation we are matching the
        // variable with.

        if (otherEquation == equation) {
            continue;
        }

        otherEquation->mDependencies.push_back(variable);

        // Stop tracking the variable since it is now known.

        otherEquation->mVariables.erase(std::remove(otherEquation->mVariables.begin(), otherEquation->mVariables.end(), variable), otherEquation->mVariables.end());
        otherEquation->mStateVariables.erase(std::remove(otherEquation->mStateVariables.begin(), otherEquation->mStateVariables.end(), variable), otherEquation->mStateVariables.end());
    }

    // Stop tracking the variable since it is now known.

    variable->mUnmatchedEquations.clear();
}

bool Analyser::AnalyserImpl::matchVariableAndEquation(const AnalyserInternalVariablePtr &variable,
                                                      const AnalyserInternalEquationPtr &equation)
{
    // We first need to ensure that the variable is isolated in the equation, so we can match it. If it isn't, we try to
    // rearrange the equation to isolate the variable. If we can't rearrange the equation, then we can't match the
    // variable and the equation.

    if (!equation->isVariableIsolated(variable)) {
        // If the equation has no native SymEngine representation (e.g., because it is a derivative or it contains a
        // piecewise statement), then we build a temporary SymEngine expression by substituting every unsupported
        // subtree with a fresh opaque symbol. SymEngine can then manipulate the enclosing expression algebraically,
        // treating those subtrees as opaque unknowns, and the opaque symbols are resolved back to their original AST
        // subtrees after solving.

        OSName2OSInfoMap osName2osInfoMap;
        auto actualSEExpression = equation->mSEExpression;

        if (actualSEExpression.is_null()) {
            [[maybe_unused]] auto [success, seExpression] = astToSymEngine(equation->mAst, &osName2osInfoMap);

            actualSEExpression = seExpression;
        }

        // Try to rearrange the equation to isolate the variable.

        auto seSymbol = mAIVariable2SESymbolMap[variable];
        auto origSEExpression = equation->mSEExpression;

        equation->mSEExpression = actualSEExpression;

        auto rearrangedSEExpression = equation->rearrangeForSESymbol(seSymbol);

        equation->mSEExpression = origSEExpression;

        if (!rearrangedSEExpression.is_null()) {
            // Update the equation using the rearranged SymEngine expression. When opaque symbols are present (i.e. the
            // equation contains non-SymEngine-native nodes), then we reconstruct the AST directly using the opaque
            // symbol to AST map.

            if (osName2osInfoMap.empty()) {
                updateEquationFromSEExpression(equation, SymEngine::Eq(seSymbol, rearrangedSEExpression));
            } else {
                auto simplifiedSEExpression = simplifySEExpression(SymEngine::Eq(seSymbol, rearrangedSEExpression));

                replaceAstTree(equation, simplifyAst(symEngineToAst(simplifiedSEExpression, nullptr, &osName2osInfoMap)));
            }

            equation->mHasBeenRearranged = true;
        } else if (variable->mType == AnalyserInternalVariable::Type::STATE) {
            // We can't rearrange the equation to isolate the variable. However, the variable is a state variable, so
            // we can try to rearrange the equation to isolate the derivative of the variable instead.

            astToSymEngine(equation->mAst, &osName2osInfoMap);

            auto diffOpaqueSymbolName = "__diff_" + seSymbol->get_name();
            auto diffOpaqueSymbol = SymEngine::symbol(diffOpaqueSymbolName);
            auto &seDiffExpression = osName2osInfoMap.at(diffOpaqueSymbolName).seDiffExpression;

            equation->mSEExpression = SymEngine::msubs(origSEExpression, {{seDiffExpression, diffOpaqueSymbol}});

            rearrangedSEExpression = equation->rearrangeForSESymbol(diffOpaqueSymbol);

            equation->mSEExpression = origSEExpression;

            if (rearrangedSEExpression.is_null()) {
                return false;
            }

            updateEquationFromSEExpression(equation, SymEngine::Eq(seDiffExpression, rearrangedSEExpression));

            equation->mHasBeenRearranged = true;
        } else {
            return false;
        }
    } else if (equation->isVariable(variable, equation->mAst->rightChild())) {
        // The variable is on the right-hand side of the equation, so we swap the left-hand side and right-hand side of
        // the equation to isolate the variable.

        auto leftChild = equation->mAst->leftChild();
        auto rightAst = equation->mAst->rightChild();

        equation->mAst->setLeftChild(rightAst);
        equation->mAst->setRightChild(leftChild);
        leftChild->setParent(equation->mAst);
        rightAst->setParent(equation->mAst);

        auto [success, seExpression] = astToSymEngine(equation->mAst);

        if (success) {
            equation->mSEExpression = simplifySEExpression(seExpression);
        }
    }

    // If the equation was not rearranged, then simplify its AST directly.

    if (!equation->mHasBeenRearranged) {
        replaceAstTree(equation, simplifyAst(equation->mAst));
    }

    // We can now match the variable and the equation.

    equation->addUnknownVariable(variable);

    variable->mMatchedEquation = equation;

    // Update all other variables in the equation to consider this variable known.

    for (const auto &otherVariables : {equation->mStateVariables, equation->mVariables}) {
        for (const auto &otherVariable : otherVariables) {
            // Don't update the variable we are matching.

            if (otherVariable == variable) {
                continue;
            }

            // Stop tracking the variable since it is now known and add it as a dependency for the equation.

            otherVariable->mUnmatchedEquations.erase(std::remove(otherVariable->mUnmatchedEquations.begin(),
                                                                 otherVariable->mUnmatchedEquations.end(),
                                                                 equation),
                                                     otherVariable->mUnmatchedEquations.end());

            equation->mDependencies.push_back(otherVariable);
        }
    }

    // Stop tracking the variable and all other variables in the equation since they are now known.

    equation->mVariables.clear();
    equation->mStateVariables.clear();

    makeVariableKnown(variable, equation);

    // Update the variable to use the variable from the equation's component that it is equivalent to.

    auto i = MAX_SIZE_T;

    while (true) {
        auto localVariable = equation->mComponent->variable(++i);

        if (mAnalyserModel->areEquivalentVariables(variable->mVariable, localVariable)) {
            variable->setVariable(localVariable, false);

            break;
        }
    }

    return true;
}

void Analyser::AnalyserImpl::matchVariablesAndEquations(AnalyserInternalVariablePtrs &variables,
                                                        AnalyserInternalEquationPtrs &equations)
{
    // Initialise our matching by identifying which variables and equations are initially unknown, and the relationships
    // between them.

    for (const auto &equation : equations) {
        auto iter = equation->mVariables.begin();

        while (iter != equation->mVariables.end()) {
            auto variable = *iter;

            // Ignore the variables that do not require matching and, instead, add them as dependencies.

            if ((std::find(variables.begin(), variables.end(), variable) == variables.end())
                || (variable->mType == AnalyserInternalVariable::Type::STATE)) {
                equation->mDependencies.push_back(variable);

                iter = equation->mVariables.erase(iter);
            } else {
                // The variable is unknown, so track it as a candidate for matching.

                variable->mUnmatchedEquations.push_back(equation);

                ++iter;
            }
        }

        // State variables are initially unknown, so track them as candidates for matching too.

        for (const auto &stateVariable : equation->mStateVariables) {
            stateVariable->mUnmatchedEquations.push_back(equation);
        }
    }

    // Begin our matching process (see https://doi.org/10.1145/2666202.2666204 for more details).

    auto markEquationsAsNla = [&](const AnalyserInternalEquationPtrs &equations) {
        for (const auto &equation : equations) {
            equation->mType = AnalyserInternalEquation::Type::NLA;

            for (const auto &variable : equation->mAllVariables) {
                if ((variable->mMatchedEquation == nullptr)
                    && (variable->mType != AnalyserInternalVariable::Type::VARIABLE_OF_INTEGRATION)
                    && (variable->mType != AnalyserInternalVariable::Type::INITIALISED)) {
                    variable->mType = AnalyserInternalVariable::Type::ALGEBRAIC_VARIABLE;

                    equation->addUnknownVariable(variable);
                }
            }
        }
    };

    AnalyserInternalVariablePtrs preTearingVariables;
    AnalyserInternalVariablePtrs tearingVariables;
    AnalyserInternalEquationPtrs allEquations = equations;
    auto progressMade = false;

    while (variables.size() > 0) {
        auto iterationProgress = false;

        // Match all our unmatched equations with a single unmatched variable it can rearrange for.

        bool localEquationProgress;

        do {
            localEquationProgress = false;

            // Identify the equations that we can currently match.

            auto iter = equations.begin();

            while (iter != equations.end()) {
                auto equation = *iter;

                // We can't match equations that don't have one unmatched variable.

                if (equation->mVariables.size() + equation->mStateVariables.size() != 1) {
                    ++iter;

                    continue;
                }

                // We can only match equations where the variable is not the variable of integration and can be
                // rearranged for.

                auto variable = (equation->mVariables.size() == 1) ? equation->mVariables.front() : equation->mStateVariables.front();

                if (!matchVariableAndEquation(variable, equation)) {
                    ++iter;

                    continue;
                }

                // Keep track of the variable as one of our first variables by placing it before any variables that
                // depend on it.

                auto insertIter = std::find_if(mFirstVariables.begin(), mFirstVariables.end(), [&](const auto &otherVariable) {
                    const auto &dependencies = otherVariable->mMatchedEquation->mDependencies;

                    return std::find(dependencies.begin(), dependencies.end(), variable) != dependencies.end();
                });

                mFirstVariables.insert(insertIter, variable);

                // Add the variable to our pre-tearing variables if we haven't identified any tearing variables yet.

                if (tearingVariables.size() == 0) {
                    preTearingVariables.push_back(variable);
                }

                // Stop tracking the variable and the equation since they are now matched.

                variables.erase(std::remove(variables.begin(), variables.end(), variable), variables.end());

                iter = equations.erase(iter);

                localEquationProgress = true;
                progressMade = true;
                iterationProgress = true;
            }
        } while (localEquationProgress);

        // Match all unmatched variables with a single unmatched equation it can be rearranged for.

        bool localVariableProgress;

        do {
            localVariableProgress = false;

            // Identify the variables that we can currently match.

            auto iter = variables.begin();

            while (iter != variables.end()) {
                auto variable = *iter;

                // We can only match variables that are not external variables.

                if (variable->mIsExternalVariable) {
                    iter = variables.erase(iter);

                    continue;
                }

                // We can't match variables that have more than one unmatched equation.

                if (variable->mUnmatchedEquations.size() > 1) {
                    ++iter;

                    continue;
                }

                // We can only match variables that are not a variable with no equations left that include it.

                if (variable->mUnmatchedEquations.size() == 0) {
                    iter = variables.erase(iter);

                    continue;
                }

                // Check whether we can match the variable and the equation.

                auto equation = variable->mUnmatchedEquations.front();

                if (matchVariableAndEquation(variable, equation)) {
                    // The variable and the equation can be matched, so keep track of the variable as one of our last
                    // variables and stop tracking the equation.

                    mLastVariables.insert(mLastVariables.begin(), variable);
                    equations.erase(std::remove(equations.begin(), equations.end(), equation), equations.end());

                    progressMade = true;
                } else {
                    // The variable and the equation can't be matched, so it's an "impossible assignment" which means
                    // that the variable should be considered as one of our tearing variables.

                    tearingVariables.push_back(variable);

                    makeVariableKnown(variable, nullptr);
                }

                // Stop tracking the variable since it is now matched or a tearing variable.

                iter = variables.erase(iter);

                localVariableProgress = true;
                iterationProgress = true;
            }
        } while (localVariableProgress);

        // Pick a tearing variable by choosing the variable that would make the greatest progress towards matching if it
        // were known. We measure this by considering the following statistics:
        //  - the number of equations that would be made matched if this variable was known; and
        //  - the number of unmatched relationships involving the variable.
        // The chosen tearing variable has the greatest sum of these two statistics. If several variables are tied,
        // we can pick any of them, so we just pick the first one.

        size_t maxSum = 0;
        AnalyserInternalVariablePtr tearingVariable;

        for (const auto &variable : variables) {
            // Calculate the statistics for this variable.

            size_t matchMaking = 0;

            for (const auto &equation : variable->mUnmatchedEquations) {
                if (equation->mStateVariables.size() + equation->mVariables.size() == 2) {
                    ++matchMaking;
                }
            }

            size_t sum = matchMaking + variable->mUnmatchedEquations.size();

            // Check if this variable is a better tearing variable than our current best.

            if (sum > maxSum) {
                maxSum = sum;

                tearingVariable = variable;
            }
        }

        // We have identified a tearing variable but we have more equations than variables, then we can't actually pick
        // a tearing variable since we won't be able to make progress towards matching by making any variable known.

        if ((tearingVariable != nullptr) && (variables.size() > equations.size())) {
            tearingVariable = nullptr;
        }

        // If we have identified a tearing variable, then track it and consider it as known for the rest of the matching
        // process.

        if (tearingVariable != nullptr) {
            tearingVariables.push_back(tearingVariable);

            variables.erase(std::remove(variables.begin(), variables.end(), tearingVariable), variables.end());

            makeVariableKnown(tearingVariable, nullptr);

            iterationProgress = true;
        }

        // If we haven't made any progress towards matching in this iteration, then it means that we can stop the
        // matching process.

        if (!iterationProgress) {
            break;
        }
    }

    // If there are no tearing variables, then either we are done with matching or we have unmatched variables left. In
    // the latter case, the remaining equations must be marked as NLA equations.

    if (tearingVariables.empty()) {
        if (!variables.empty()) {
            markEquationsAsNla(equations);
        }

        return;
    }

    // Reset the unmatched equations of tearing variables as they will be repopulated after equation substitution.

    for (const auto &tearingVariable : tearingVariables) {
        tearingVariable->mUnmatchedEquations.clear();
    }

    // Create a substitution map for SymEngine expressions based on the equations we have matched so far.

    SymEngine::map_basic_basic substitutionMap;

    for (const auto &equation : allEquations) {
        // Ignore the equations that we haven't managed to match or that we don't have a SymEngine equivalent for.

        if (std::find(equations.begin(), equations.end(), equation) != equations.end()
            || equation->mSEExpression.is_null()) {
            continue;
        }

        // SymEngine may have swapped the LHS and RHS of our equation, so we need to check both sides of the equation to
        // identify on which side our unknown variable is and thus determine the correct substitution.

        auto seSymbolFromSEExpression = [](const SEExpression &seExpression) {
            SESymbol res;

            if (seExpression->get_type_code() == SymEngine::SYMENGINE_SYMBOL) {
                res = SymEngine::rcp_static_cast<const SymEngine::Symbol>(seExpression);
            }

            return res;
        };

        auto seExpressionArgs = equation->mSEExpression->get_args();
        auto seExpressionLhs = seExpressionArgs.front();
        auto seExpressionRhs = seExpressionArgs.back();
        auto seSymbolLhs = seSymbolFromSEExpression(seExpressionLhs);

        auto unknownVariable = equation->mUnknownVariables.front();

        if (std::find(preTearingVariables.begin(), preTearingVariables.end(), unknownVariable) != preTearingVariables.end()) {
            continue;
        }

        // We have identified the unknown variable and the correct substitution, so add it to our substitution map.

        if (!seSymbolLhs.is_null()
            && (mSESymbol2AIVariableMap.at(seSymbolLhs) == unknownVariable)) {
            substitutionMap[seExpressionLhs] = seExpressionRhs;
        } else {
            substitutionMap[seExpressionRhs] = seExpressionLhs;
        }
    }

    // Substitute the SymEngine expressions of all our equations and regenerate the AST tree for all our equations.

    for (const auto &equation : equations) {
        // If the equation doesn't have a SymEngine equivalent, then we still need to "replace" its AST tree so that its
        // internals get updated.

        if (equation->mSEExpression.is_null()) {
            replaceAstTree(equation, equation->mAst);

            continue;
        }

        // Do the substitution for this equation and then update the equation based on the result.

        for (size_t i = 0; i < substitutionMap.size(); ++i) {
            equation->mSEExpression = SymEngine::msubs(equation->mSEExpression, substitutionMap);
        }

        updateEquationFromSEExpression(equation, equation->mSEExpression);
    }

    // We have made some progress towards matching variables and equations, so try again using our tearing variables.

    if (progressMade) {
        matchVariablesAndEquations(tearingVariables, equations);

        return;
    }

    // Our matching algorithm has stalled which means that the rest of the system must be classified as an NLA system.

    markEquationsAsNla(equations);
}

void Analyser::AnalyserImpl::substituteVariablesInEquations()
{
    auto substituteVariables = [&](const auto &self, const AnalyserEquationAstPtr &ast,
                                   const AnalyserInternalEquationPtr &internalEquation,
                                   std::unordered_set<AnalyserInternalEquation *> &visitedEquations,
                                   bool &substitutionComplete, const AnalyserEquationAstPtr &parentAst) -> AnalyserEquationAstPtr {
        if (ast == nullptr) {
            return nullptr;
        }

        if (ast->type() == AnalyserEquationAst::Type::CI) {
            auto matchedEquation = internalVariable(ast->variable())->mMatchedEquation;

            if ((matchedEquation != nullptr)
                && (matchedEquation != internalEquation)
                && matchedEquation->mHasBeenRearranged
                && (visitedEquations.find(matchedEquation.get()) == visitedEquations.end())) {
                visitedEquations.insert(matchedEquation.get());

                auto substitutedAst = self(self, matchedEquation->mAst->rightChild(), internalEquation, visitedEquations,
                                           substitutionComplete, parentAst);

                visitedEquations.erase(matchedEquation.get());

                return substitutedAst;
            }

            substitutionComplete = false;

            return ast->clone(parentAst);
        }

        auto res = AnalyserEquationAst::create();

        res->setType(ast->type());
        res->setValue(ast->value());
        res->setVariable(ast->variable());
        res->setParent(parentAst);
        res->setLeftChild(self(self, ast->leftChild(), internalEquation, visitedEquations, substitutionComplete, res));
        res->setRightChild(self(self, ast->rightChild(), internalEquation, visitedEquations, substitutionComplete, res));

        return res;
    };

    // Substitute all our matched variables in our equations to simplify them and potentially identify more matches.

    for (const auto &internalEquation : mInternalEquations) {
        if (!internalEquation->mHasBeenRearranged) {
            continue;
        }

        auto substitutedEquationAst = AnalyserEquationAst::create();
        std::unordered_set<AnalyserInternalEquation *> visitedEquations = {internalEquation.get()};
        auto substitutionComplete = true;

        substitutedEquationAst->setType(AnalyserEquationAst::Type::EQUALITY);
        substitutedEquationAst->setLeftChild(internalEquation->mAst->leftChild()->clone(substitutedEquationAst));
        substitutedEquationAst->setRightChild(substituteVariables(substituteVariables, internalEquation->mAst->rightChild(),
                                                                  internalEquation, visitedEquations, substitutionComplete,
                                                                  substitutedEquationAst));

        if (!substitutionComplete) {
            continue;
        }

        auto simplifiedSubstitutedEquationAst = simplifyAst(substitutedEquationAst);
        auto [success, seExpression] = astToSymEngine(simplifiedSubstitutedEquationAst);

        if (success) {
            updateEquationFromSEExpression(internalEquation, seExpression);
        } else {
            replaceAstTree(internalEquation, simplifiedSubstitutedEquationAst);
        }
    }
}

void Analyser::AnalyserImpl::classifyVariablesAndEquations()
{
    // Classify our analyser internal equations and analyser internal variables.

    for (const auto *orderedVariables : {&mFirstVariables, &mLastVariables}) {
        for (const auto &orderedVariable : *orderedVariables) {
            auto matchedEquation = orderedVariable->mMatchedEquation;

            // The matched equation of state variables and variables that should be state variables are always
            // classified as ODEs.

            if ((orderedVariable->mType == AnalyserInternalVariable::Type::STATE)
                || (orderedVariable->mType == AnalyserInternalVariable::Type::SHOULD_BE_STATE)) {
                matchedEquation->mType = AnalyserInternalEquation::Type::ODE;

                continue;
            }

            // For other variables, we need to inspect the variables that their matched equation depends on in order to
            // classify them.

            std::unordered_set<AnalyserInternalVariable *> dependentVariables;
            auto onlyConstants = true;
            auto onlyComputedConstants = true;

            auto classifyDependentVariable = [&](const AnalyserInternalVariablePtr &dependentVariable) {
                if (dependentVariable == orderedVariable) {
                    return;
                }

                if (!dependentVariables.insert(dependentVariable.get()).second) {
                    return;
                }

                if (dependentVariable->mIsExternalVariable) {
                    onlyConstants = false;
                    onlyComputedConstants = false;

                    return;
                }

                switch (dependentVariable->mType) {
                case AnalyserInternalVariable::Type::CONSTANT:
                    onlyComputedConstants = false;

                    break;
                case AnalyserInternalVariable::Type::INITIALISED:
                case AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT:
                case AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT:
                    onlyConstants = false;

                    break;
                default:
                    onlyConstants = false;
                    onlyComputedConstants = false;

                    break;
                }
            };

            for (const auto &dependentVariable : matchedEquation->mDependencies) {
                classifyDependentVariable(dependentVariable);
            }

            for (const auto &dependentVariable : matchedEquation->mAllVariables) {
                classifyDependentVariable(dependentVariable);
            }

            // Classify equations and variables.

            if (onlyConstants) {
                orderedVariable->mType = AnalyserInternalVariable::Type::COMPUTED_TRUE_CONSTANT;
                matchedEquation->mType = AnalyserInternalEquation::Type::CONSTANT;
            } else if (onlyComputedConstants) {
                orderedVariable->mType = AnalyserInternalVariable::Type::COMPUTED_VARIABLE_BASED_CONSTANT;
                matchedEquation->mType = AnalyserInternalEquation::Type::COMPUTED_CONSTANT;
            } else {
                orderedVariable->mType = AnalyserInternalVariable::Type::ALGEBRAIC_VARIABLE;
                matchedEquation->mType = AnalyserInternalEquation::Type::ALGEBRAIC;
            }
        }
    }

    // Mark any remaining unknown variables as initialised variables, should they be external variables.

    for (const auto &internalVariable : mInternalVariables) {
        if (internalVariable->mIsExternalVariable && (internalVariable->mType == AnalyserInternalVariable::Type::UNKNOWN)) {
            internalVariable->mType = AnalyserInternalVariable::Type::INITIALISED;
        }
    }

    // Mark any remaining equations with no unknown variables as NLAs.

    for (const auto &internalEquation : mInternalEquations) {
        if (internalEquation->mUnknownVariables.empty() && (internalEquation->mType == AnalyserInternalEquation::Type::UNKNOWN)) {
            internalEquation->mType = AnalyserInternalEquation::Type::NLA;
        }
    }
}

} // namespace libcellml
