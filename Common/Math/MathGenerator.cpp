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
                                     myNumberGenerator{},
                                     myEngine(std::random_device{}())
    {
    }

    MathGenerator::MathGenerator(const std::string_view& aSymbolList, int aMin, int aMax, bool useFloats) :
        isUsingFloats(useFloats),
        myMin(aMin),
        myMax(aMax),
        myNumberGenerator{},
        myEngine(std::random_device{}())
    {
    }

    void MathGenerator::AddGenerator(char aSymbol)
    {
        union
        {
            int i;
            float f;
        } firstNumber, secondNumber;

        if (isUsingFloats) {
            firstNumber.f = myNumberGenerator.f(myEngine);
            secondNumber.f = myNumberGenerator.f(myEngine);
        }
        else {
            firstNumber.i = myNumberGenerator.i(myEngine);
            secondNumber.i = myNumberGenerator.i(myEngine);
        }

        switch (aSymbol) {
            case '+': {
                if (isUsingFloats) {
                    mySolvers.emplace_back(std::make_unique<Add>(firstNumber.f, secondNumber.f));
                }
                else {
                    mySolvers.emplace_back(std::make_unique<Add>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            case '-': {
                if (isUsingFloats) {
                    mySolvers.emplace_back(std::make_unique<Subtract>(firstNumber.f, secondNumber.f));
                }
                else {
                    mySolvers.emplace_back(std::make_unique<Subtract>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            case '*': {
                if (isUsingFloats) {
                    mySolvers.emplace_back(std::make_unique<Multiply>(firstNumber.f, secondNumber.f));
                }
                else {
                    mySolvers.emplace_back(std::make_unique<Multiply>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            case '/': {
                if (isUsingFloats) {
                    while (secondNumber.f == 0.f) {
                        secondNumber.f = myNumberGenerator.f(myEngine);
                    }
                    mySolvers.emplace_back(std::make_unique<Divide>(firstNumber.f, secondNumber.f));
                }
                else {
                    while (secondNumber.i == 0) {
                        secondNumber.i = myNumberGenerator.i(myEngine);
                    }
                    mySolvers.emplace_back(std::make_unique<Divide>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            default:
                break;
        }
    }

    void MathGenerator::AddGenerators(const std::string_view& aSymbolList)
    {
    }

    void MathGenerator::ClearGenerators()
    {
    }

    void MathGenerator::SetExtremes(int aMin, int aMax)
    {
        myMin = aMin;
        myMax = aMax;
        if (myMin > myMax) {
            std::swap(myMin, myMax);
        }
        if (isUsingFloats) {
            myNumberGenerator.f = std::uniform_real_distribution<float>(
                static_cast<float>(myMin),
                static_cast<float>(myMax)
            );
        }
        else {
            myNumberGenerator.i = std::uniform_int_distribution<int>(myMin, myMax);
        }
    }

    void MathGenerator::GenerateQuestion()
    {
    }

    std::string_view MathGenerator::GetQuestion() const
    {
    }

    bool MathGenerator::CheckAnswer(int anAnswer)
    {
    }

    bool MathGenerator::CheckAnswer(float anAnswer)
    {
    }
} // Math
