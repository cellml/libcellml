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

#undef NAN

namespace libcellml {

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

void printStringStringMap(const StringStringMap &map)
{
    Debug() << "Print out of string -> string map";
    for (const auto &iter : map) {
        Debug() << iter.first << ": " << iter.second;
    }
}

static const std::string SPACES = "  ";
static const std::string TRUNK = "  │";

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
    std::string res;

    switch (ast->mType) {
        // Assignment.

    case GeneratorEquationAst::Type::ASSIGNMENT:
        res = "ASSIGNMENT";

        break;

        // Relational and logical operators.

    case GeneratorEquationAst::Type::EQ:
        res = "EQ";

        break;
    case GeneratorEquationAst::Type::NEQ:
        res = "NEQ";

        break;
    case GeneratorEquationAst::Type::LT:
        res = "LT";

        break;
    case GeneratorEquationAst::Type::LEQ:
        res = "LEQ";

        break;
    case GeneratorEquationAst::Type::GT:
        res = "GT";

        break;
    case GeneratorEquationAst::Type::GEQ:
        res = "LEQ";

        break;
    case GeneratorEquationAst::Type::AND:
        res = "AND";

        break;
    case GeneratorEquationAst::Type::OR:
        res = "OR";

        break;
    case GeneratorEquationAst::Type::XOR:
        res = "XOR";

        break;
    case GeneratorEquationAst::Type::NOT:
        res = "NOT";

        break;

        // Arithmetic operators.

    case GeneratorEquationAst::Type::PLUS:
        res = "PLUS";

        break;
    case GeneratorEquationAst::Type::MINUS:
        res = "MINUS";

        break;
    case GeneratorEquationAst::Type::TIMES:
        res = "TIMES";

        break;
    case GeneratorEquationAst::Type::DIVIDE:
        res = "DIVIDE";

        break;
    case GeneratorEquationAst::Type::POWER:
        res = "POWER";

        break;
    case GeneratorEquationAst::Type::ROOT:
        res = "ROOT";

        break;
    case GeneratorEquationAst::Type::ABS:
        res = "ABS";

        break;
    case GeneratorEquationAst::Type::EXP:
        res = "EXP";

        break;
    case GeneratorEquationAst::Type::LN:
        res = "LN";

        break;
    case GeneratorEquationAst::Type::LOG:
        res = "LOG";

        break;
    case GeneratorEquationAst::Type::CEILING:
        res = "CEILING";

        break;
    case GeneratorEquationAst::Type::FLOOR:
        res = "FLOOR";

        break;
    case GeneratorEquationAst::Type::MIN:
        res = "MIN";

        break;
    case GeneratorEquationAst::Type::MAX:
        res = "MAX";

        break;
    case GeneratorEquationAst::Type::REM:
        res = "REM";

        break;

        // Calculus elements.

    case GeneratorEquationAst::Type::DIFF:
        res = "DIFF";

        break;

        // Trigonometric operators.

    case GeneratorEquationAst::Type::SIN:
        res = "SIN";

        break;
    case GeneratorEquationAst::Type::COS:
        res = "COS";

        break;
    case GeneratorEquationAst::Type::TAN:
        res = "TAN";

        break;
    case GeneratorEquationAst::Type::SEC:
        res = "SEC";

        break;
    case GeneratorEquationAst::Type::CSC:
        res = "CSC";

        break;
    case GeneratorEquationAst::Type::COT:
        res = "COT";

        break;
    case GeneratorEquationAst::Type::SINH:
        res = "SINH";

        break;
    case GeneratorEquationAst::Type::COSH:
        res = "COSH";

        break;
    case GeneratorEquationAst::Type::TANH:
        res = "TANH";

        break;
    case GeneratorEquationAst::Type::SECH:
        res = "SECH";

        break;
    case GeneratorEquationAst::Type::CSCH:
        res = "CSCH";

        break;
    case GeneratorEquationAst::Type::COTH:
        res = "COTH";

        break;
    case GeneratorEquationAst::Type::ASIN:
        res = "ASIN";

        break;
    case GeneratorEquationAst::Type::ACOS:
        res = "ACOS";

        break;
    case GeneratorEquationAst::Type::ATAN:
        res = "ATAN";

        break;
    case GeneratorEquationAst::Type::ASEC:
        res = "ASEC";

        break;
    case GeneratorEquationAst::Type::ACSC:
        res = "ACSC";

        break;
    case GeneratorEquationAst::Type::ACOT:
        res = "ACOT";

        break;
    case GeneratorEquationAst::Type::ASINH:
        res = "ASINH";

        break;
    case GeneratorEquationAst::Type::ACOSH:
        res = "ACOSH";

        break;
    case GeneratorEquationAst::Type::ATANH:
        res = "ATANH";

        break;
    case GeneratorEquationAst::Type::ASECH:
        res = "ASECH";

        break;
    case GeneratorEquationAst::Type::ACSCH:
        res = "ACSCH";

        break;
    case GeneratorEquationAst::Type::ACOTH:
        res = "ACOTH";

        break;

        // Piecewise statement.

    case GeneratorEquationAst::Type::PIECEWISE:
        res = "PIECEWISE";

        break;
    case GeneratorEquationAst::Type::PIECE:
        res = "PIECE";

        break;
    case GeneratorEquationAst::Type::OTHERWISE:
        res = "OTHERWISE";

        break;

        // Token elements.

    case GeneratorEquationAst::Type::CI:
        res = ast->mVariable->name();

        break;
    case GeneratorEquationAst::Type::CN:
        res = ast->mValue;

        break;

        // Qualifier elements.

    case GeneratorEquationAst::Type::DEGREE:
        res = "DEGREE";

        break;
    case GeneratorEquationAst::Type::LOGBASE:
        res = "LOGBASE";

        break;
    case GeneratorEquationAst::Type::BVAR:
        res = "BVAR";

        break;

        // Constants.

    case GeneratorEquationAst::Type::TRUE:
        res = "TRUE";

        break;
    case GeneratorEquationAst::Type::FALSE:
        res = "FALSE";

        break;
    case GeneratorEquationAst::Type::E:
        res = "E";

        break;
    case GeneratorEquationAst::Type::PI:
        res = "PI";

        break;
    case GeneratorEquationAst::Type::INF:
        res = "INF";

        break;
    case GeneratorEquationAst::Type::NAN:
        res = "NAN";

        break;
    }

    return res;
}

void doPrintAst(const GeneratorEquationAstPtr &ast,
                GeneratorEquationAstTrunk *prevTrunk, bool isLeft)
{
    if (ast == nullptr) {
        return;
    }

    std::string prevStr = SPACES;
    GeneratorEquationAstTrunk trunk(prevTrunk, prevStr);

    doPrintAst(ast->mLeft, &trunk, true);

    if (prevTrunk == nullptr) {
        trunk.mStr = "──";
    } else if (isLeft) {
        trunk.mStr = "╭──";
        prevStr = TRUNK;
    } else {
        trunk.mStr = "╰──";
        prevTrunk->mStr = prevStr;
    }

    doPrintAst(&trunk);

    std::cout << doPrintAst(ast) << std::endl;

    if (prevTrunk != nullptr) {
        prevTrunk->mStr = prevStr;
    }

    trunk.mStr = TRUNK;

    doPrintAst(ast->mRight, &trunk, false);
}

void printAst(const GeneratorEquationAstPtr &ast)
{
    doPrintAst(ast, nullptr, false);
}

} // namespace libcellml
