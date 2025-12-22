#include "MathGenerator.h"

#include "Solvers/Add.h"
#include "Solvers/Subtract.h"
#include "Solvers/Multiply.h"
#include "Solvers/Divide.h"

namespace Math
{
    MathGenerator::MathGenerator() : isUsingFloats(false),
                                     myMin(0),
                                     myMax(0),
                                     myCurrentSolverIndex(0),
                                     myEngine(std::random_device{}())
    {
    }

    MathGenerator::MathGenerator(const std::string_view& aSymbolList, int aMin, int aMax, bool useFloats) :
        isUsingFloats(useFloats),
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
                    mySolvers.emplace_back(std::make_unique<Add>(myEngine, myMin, myMax, isUsingFloats));
                break;
            }
            case '-': {
                    mySolvers.emplace_back(std::make_unique<Subtract>(myEngine, myMin, myMax, isUsingFloats));
                break;
            }
            case '*': {
                    mySolvers.emplace_back(std::make_unique<Multiply>(myEngine, myMin, myMax, isUsingFloats));
                break;
            }
            case '/': {
                    mySolvers.emplace_back(std::make_unique<Divide>(myEngine, myMin, myMax, isUsingFloats));
                break;
            }
            default:
                break;
        }
    }

    void MathGenerator::AddGenerators(const std::string_view& aSymbolList)
    {
		// Loop through string and add each symbol using AddGenerator()
    }

    void MathGenerator::ClearGenerators()
    {
		mySolvers.clear();
		myNumberGenerator.reset();
    }

    void MathGenerator::SetExtremes(int aMin, int aMax)
    {
        myMin = aMin;
        myMax = aMax;
        if (myMin > myMax) {
            std::swap(myMin, myMax);
        }
    }

    void MathGenerator::GenerateQuestion()
    {
		myCurrentSolverIndex = myNumberGenerator(myEngine);
		myQuestion = mySolvers[myCurrentSolverIndex]->GenerateEquation();
    }

    std::string MathGenerator::GetQuestion() const
    {
		return myQuestion;
    }

    bool MathGenerator::CheckAnswer(int anAnswer)
    {
		return mySolvers[myCurrentSolverIndex]->Solve(anAnswer);
    }

    bool MathGenerator::CheckAnswer(float anAnswer)
    {
		return mySolvers[myCurrentSolverIndex]->Solve(anAnswer);
    }
} // Math
