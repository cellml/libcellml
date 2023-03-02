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

#include "libcellml/analyserequationast.h"
#include "libcellml/component.h"
#include "libcellml/generator.h"
#include "libcellml/model.h"
#include "libcellml/variable.h"

#ifdef NAN
#    undef NAN
#endif

namespace libcellml {

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
        auto key = iter.first;    Debug(false) << "key: ";
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

void doPrintAst(AnalyserEquationAstTrunk *trunk)
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

std::string doPrintAst(const AnalyserEquationAstPtr &ast)
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

    case AnalyserEquationAst::Type::CI: {
        auto astVariable = ast->variable();

        if (astVariable != nullptr) {
            res = astVariable->name();
        }

        break;
    }
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

void doPrintAst(const AnalyserEquationAstPtr &ast,
                AnalyserEquationAstTrunk *prevTrunk, bool isLeft)
{
    if (ast == nullptr) {
        return;
    }

    std::string prevStr = SPACES;
    AnalyserEquationAstTrunk trunk(prevTrunk, prevStr);

    auto astLeftChild = ast->leftChild();

    if (astLeftChild != nullptr) {
        doPrintAst(astLeftChild, &trunk, true);
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

    doPrintAst(&trunk);

    std::cout << doPrintAst(ast) << std::endl;

    if (prevTrunk != nullptr) {
        prevTrunk->mStr = prevStr;
    }

    trunk.mStr = TRUNK;

    auto astRightChild = ast->rightChild();

    if (astRightChild != nullptr) {
        doPrintAst(astRightChild, &trunk, false);
    }
}

void printAst(const AnalyserEquationAstPtr &ast)
{
    doPrintAst(ast, nullptr, false);
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

} // namespace libcellml
