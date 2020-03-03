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

#include "libcellml/generator.h"
#include "libcellml/variable.h"

namespace libcellml {

void printStack(const IndexStack &stack)
{
    Debug(false) << "[";
    for (auto iter = stack.begin(); iter < stack.end(); ++iter) {
        Debug(false) << *iter;
        if (iter + 1 < stack.end()) {
            Debug(false) << ", ";
        }
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
        for (auto vectorIt = vector.begin(); vectorIt < vector.end(); ++vectorIt) {
            Debug(false) << "value: ";
            printStack(*vectorIt);
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

static const std::string SPACES = "   ";
static const std::string TRUNK = "   |";

struct GeneratorEquationAstTrunk
{
    GeneratorEquationAstTrunk *mPrev;
    std::string mStr;

    GeneratorEquationAstTrunk(GeneratorEquationAstTrunk *prev,
                              const std::string &str);
};

GeneratorEquationAstTrunk::GeneratorEquationAstTrunk(GeneratorEquationAstTrunk *prev,
                                                     const std::string &str)
    : mPrev(prev)
    , mStr(str)
{
}

void doPrintAst(GeneratorEquationAstTrunk *trunk)
{
    if (trunk == nullptr) {
        return;
    }

    doPrintAst(trunk->mPrev);

    if ((trunk->mPrev != nullptr) && (trunk->mPrev->mStr == SPACES)
        && ((trunk->mStr == SPACES) || (trunk->mStr == TRUNK))) {
        std::cout << " ";
    }

    std::cout << trunk->mStr;
}

std::string doPrintAst(const GeneratorEquationAstPtr &ast)
{
    switch (ast->mType) {
        // Assignment.

    case GeneratorEquationAst::Type::ASSIGNMENT:
        return "ASSIGNMENT";

        // Relational and logical operators.

    case GeneratorEquationAst::Type::EQ:
        return "EQ";
    case GeneratorEquationAst::Type::NEQ:
        return "NEQ";
    case GeneratorEquationAst::Type::LT:
        return "LT";
    case GeneratorEquationAst::Type::LEQ:
        return "LEQ";
    case GeneratorEquationAst::Type::GT:
        return "GT";
    case GeneratorEquationAst::Type::GEQ:
        return "LEQ";
    case GeneratorEquationAst::Type::AND:
        return "AND";
    case GeneratorEquationAst::Type::OR:
        return "OR";
    case GeneratorEquationAst::Type::XOR:
        return "XOR";
    case GeneratorEquationAst::Type::NOT:
        return "NOT";

        // Arithmetic operators.

    case GeneratorEquationAst::Type::PLUS:
        return "PLUS";
    case GeneratorEquationAst::Type::MINUS:
        return "MINUS";
    case GeneratorEquationAst::Type::TIMES:
        return "TIMES";
    case GeneratorEquationAst::Type::DIVIDE:
        return "DIVIDE";
    case GeneratorEquationAst::Type::POWER:
        return "POWER";
    case GeneratorEquationAst::Type::ROOT:
        return "ROOT";
    case GeneratorEquationAst::Type::ABS:
        return "ABS";
    case GeneratorEquationAst::Type::EXP:
        return "EXP";
    case GeneratorEquationAst::Type::LN:
        return "LN";
    case GeneratorEquationAst::Type::LOG:
        return "LOG";
    case GeneratorEquationAst::Type::CEILING:
        return "CEILING";
    case GeneratorEquationAst::Type::FLOOR:
        return "FLOOR";
    case GeneratorEquationAst::Type::MIN:
        return "MIN";
    case GeneratorEquationAst::Type::MAX:
        return "MAX";
    case GeneratorEquationAst::Type::REM:
        return "REM";

        // Calculus elements.

    case GeneratorEquationAst::Type::DIFF:
        return "DIFF";

        // Trigonometric operators.

    case GeneratorEquationAst::Type::SIN:
        return "SIN";
    case GeneratorEquationAst::Type::COS:
        return "COS";
    case GeneratorEquationAst::Type::TAN:
        return "TAN";
    case GeneratorEquationAst::Type::SEC:
        return "SEC";
    case GeneratorEquationAst::Type::CSC:
        return "CSC";
    case GeneratorEquationAst::Type::COT:
        return "COT";
    case GeneratorEquationAst::Type::SINH:
        return "SINH";
    case GeneratorEquationAst::Type::COSH:
        return "COSH";
    case GeneratorEquationAst::Type::TANH:
        return "TANH";
    case GeneratorEquationAst::Type::SECH:
        return "SECH";
    case GeneratorEquationAst::Type::CSCH:
        return "CSCH";
    case GeneratorEquationAst::Type::COTH:
        return "COTH";
    case GeneratorEquationAst::Type::ASIN:
        return "ASIN";
    case GeneratorEquationAst::Type::ACOS:
        return "ACOS";
    case GeneratorEquationAst::Type::ATAN:
        return "ATAN";
    case GeneratorEquationAst::Type::ASEC:
        return "ASEC";
    case GeneratorEquationAst::Type::ACSC:
        return "ACSC";
    case GeneratorEquationAst::Type::ACOT:
        return "ACOT";
    case GeneratorEquationAst::Type::ASINH:
        return "ASINH";
    case GeneratorEquationAst::Type::ACOSH:
        return "ACOSH";
    case GeneratorEquationAst::Type::ATANH:
        return "ATANH";
    case GeneratorEquationAst::Type::ASECH:
        return "ASECH";
    case GeneratorEquationAst::Type::ACSCH:
        return "ACSCH";
    case GeneratorEquationAst::Type::ACOTH:
        return "ACOTH";

        // Piecewise statement.

    case GeneratorEquationAst::Type::PIECEWISE:
        return "PIECEWISE";
    case GeneratorEquationAst::Type::PIECE:
        return "PIECE";
    case GeneratorEquationAst::Type::OTHERWISE:
        return "OTHERWISE";

        // Token elements.

    case GeneratorEquationAst::Type::CI:
        return ast->mVariable->name();
    case GeneratorEquationAst::Type::CN:
        return ast->mValue;

        // Qualifier elements.

    case GeneratorEquationAst::Type::DEGREE:
        return "DEGREE";
    case GeneratorEquationAst::Type::LOGBASE:
        return "LOGBASE";
    case GeneratorEquationAst::Type::BVAR:
        return "BVAR";

        // Constants.

    case GeneratorEquationAst::Type::TRUE:
        return "TRUE";
    case GeneratorEquationAst::Type::FALSE:
        return "FALSE";
    case GeneratorEquationAst::Type::E:
        return "E";
    case GeneratorEquationAst::Type::PI:
        return "PI";
    case GeneratorEquationAst::Type::INF:
        return "INF";
    case GeneratorEquationAst::Type::NAN:
        return "NAN";
    }
}

void doPrintAst(const GeneratorEquationAstPtr &ast,
                GeneratorEquationAstTrunk *prevTrunk, bool isLeft)
{
    if (ast == nullptr) {
        return;
    }

    std::string prevStr = SPACES;
    auto trunk = new struct GeneratorEquationAstTrunk(prevTrunk, prevStr);

    doPrintAst(ast->mLeft, trunk, true);

    if (prevTrunk == nullptr) {
        trunk->mStr = "---";
    } else if (isLeft) {
        trunk->mStr = ".---";
        prevStr = TRUNK;
    } else {
        trunk->mStr = "`---";
        prevTrunk->mStr = prevStr;
    }

    doPrintAst(trunk);

    std::cout << doPrintAst(ast) << std::endl;

    if (prevTrunk != nullptr) {
        prevTrunk->mStr = prevStr;
    }

    trunk->mStr = TRUNK;

    doPrintAst(ast->mRight, trunk, false);

    delete trunk;
}

void printAst(const GeneratorEquationAstPtr &ast)
{
    doPrintAst(ast, nullptr, false);
}

} // namespace libcellml
