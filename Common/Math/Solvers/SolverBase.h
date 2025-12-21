#ifndef HOMEWORKHELPER_SOLVERBASE_H
#define HOMEWORKHELPER_SOLVERBASE_H

namespace Math
{
    class SolverBase
    {
    protected:
        bool isUsingFloats;
        union
        {
            int i;
            float f;
        } firstNumber, secondNumber;

    public:
        SolverBase() : isUsingFloats(false),
                       firstNumber(0),
                       secondNumber(0)
        {
        }
        SolverBase(int aFirst, int aSecond) : isUsingFloats(false),
                       firstNumber(aFirst),
                       secondNumber(aSecond)
        {
        }

        SolverBase(float aFirst, float aSecond) : isUsingFloats(true),
                       firstNumber{.f = aFirst},
                       secondNumber{.f =aSecond}
        {
        }

        virtual ~SolverBase() = default;

        bool Solve(int anAnswer) const
        {
            return anAnswer == GetAnswerInt();
        }

        bool Solve(float anAnswer) const
        {
            return anAnswer == GetAnswerFloat();
        }

        virtual int GetAnswerInt() const = 0;

        virtual float GetAnswerFloat() const = 0;
    };
} // Math

#endif //HOMEWORKHELPER_SOLVERBASE_H
