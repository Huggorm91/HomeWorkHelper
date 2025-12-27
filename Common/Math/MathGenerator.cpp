#include "MathGenerator.h"

#include "Solvers/Add.h"
#include "Solvers/Subtract.h"
#include "Solvers/Multiply.h"
#include "Solvers/Divide.h"

namespace Math
{
    MathGenerator::MathGenerator() :
        myIsUsingFloats(false),
        myMin(0),
        myMax(0),
        myCurrentSolverIndex(0),
        myEngine(std::random_device{}())
    {
    }

    MathGenerator::MathGenerator(const std::string_view& aSymbolList, int aMin, int aMax, bool useFloats) :
        myIsUsingFloats(useFloats),
        myMin(aMin),
        myMax(aMax),
        myCurrentSolverIndex(0),
        myEngine(std::random_device{}())
    {
        AddGenerators(aSymbolList);
    }

    void MathGenerator::AddGenerator(char aSymbol)
    {
        myNumberGenerator = std::uniform_int_distribution<int>(0, static_cast<int>(mySolvers.size()));

        switch (aSymbol) {
            case '+': {
                mySolvers.emplace_back(std::make_unique<Add>(myEngine, myMin, myMax, myIsUsingFloats));
                break;
            }
            case '-': {
                mySolvers.emplace_back(std::make_unique<Subtract>(myEngine, myMin, myMax, myIsUsingFloats));
                break;
            }
            case '*': {
                mySolvers.emplace_back(std::make_unique<Multiply>(myEngine, myMin, myMax, myIsUsingFloats));
                break;
            }
            case '/': {
                mySolvers.emplace_back(std::make_unique<Divide>(myEngine, myMin, myMax, myIsUsingFloats));
                break;
            }
            default:
                break;
        }
    }

    void MathGenerator::AddGenerators(const std::string_view& aSymbolList)
    {
        for (char symbol: aSymbolList) {
            AddGenerator(symbol);
        }
    }

    void MathGenerator::RemoveGenerator(char aSymbol)
    {
        int indexToRemove = -1;
        for (int i = 0; i < mySolvers.size(); ++i) {
            if (mySolvers[i]->GetSymbol() == aSymbol) {
                indexToRemove = i;
            }
        }
        if (indexToRemove != -1) {
            mySolvers.erase(mySolvers.begin() + indexToRemove);
            myNumberGenerator = std::uniform_int_distribution<int>(0, std::max(static_cast<int>(mySolvers.size()-1), 0));

            if (myCurrentSolverIndex == indexToRemove) {
                GenerateQuestion();
            }
            else if (myCurrentSolverIndex > indexToRemove) {
                myCurrentSolverIndex--;
            }
        }
    }

    void MathGenerator::ClearGenerators()
    {
        mySolvers.clear();
        myNumberGenerator.reset();
        myQuestion = "";
        myCurrentSolverIndex = -1;
    }

    void MathGenerator::SetExtremes(int aMin, int aMax)
    {
        myMin = aMin;
        myMax = aMax;
        if (myMin > myMax) {
            std::swap(myMin, myMax);
        }
        for (auto& solver: mySolvers) {
            solver->SetExtremes(myMin, myMax);
        }
    }

    int MathGenerator::GetMin() const
    {
        return myMin;
    }

    int MathGenerator::GetMax() const
    {
        return myMax;
    }

    void MathGenerator::SetUseFloats(bool aUseFloats)
    {
        myIsUsingFloats = aUseFloats;
        std::string symbols;
        for (const auto& solver: mySolvers) {
            symbols += solver->GetSymbol();
        }
        ClearGenerators();
        AddGenerators(symbols);
    }

    void MathGenerator::GenerateQuestion()
    {
        myQuestion = "";
        myCurrentSolverIndex = -1;
        if (!mySolvers.empty()) {
            myCurrentSolverIndex = myNumberGenerator(myEngine);
            myQuestion = mySolvers[myCurrentSolverIndex]->GenerateEquation();
        }
    }

    std::string MathGenerator::GetQuestion() const
    {
        return myQuestion;
    }

    int MathGenerator::GetAnswerInt() const
    {
        if (myCurrentSolverIndex >= 0) {
            return mySolvers[myCurrentSolverIndex]->GetAnswerInt();
        }
        return false;
    }

    float MathGenerator::GetAnswerFloat() const
    {
        if (myCurrentSolverIndex >= 0) {
            return mySolvers[myCurrentSolverIndex]->GetAnswerFloat();
        }
        return false;
    }

    bool MathGenerator::CheckAnswer(int anAnswer) const
    {
        if (myCurrentSolverIndex >= 0) {
            return mySolvers[myCurrentSolverIndex]->Solve(anAnswer);
        }
        return false;
    }

    bool MathGenerator::CheckAnswer(float anAnswer) const
    {
        if (myCurrentSolverIndex >= 0) {
            return mySolvers[myCurrentSolverIndex]->Solve(anAnswer);
        }
        return false;
    }
} // Math
