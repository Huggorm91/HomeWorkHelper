#ifndef HOMEWORKHELPER_DIVIDE_H
#define HOMEWORKHELPER_DIVIDE_H
#include "SolverBase.h"

namespace Math
{
    class Divide : public SolverBase
    {
    public:
        Divide(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats);
        ~Divide() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;

        char GetSymbol() const override;

        private:
        void GenerateNumbers() override;
    };
} // Math

#endif //HOMEWORKHELPER_DIVIDE_H