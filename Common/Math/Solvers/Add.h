#ifndef HOMEWORKHELPER_ADD_H
#define HOMEWORKHELPER_ADD_H
#include "SolverBase.h"

namespace Math
{
    class Add: public SolverBase
    {
    public:
        Add(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats);
        ~Add() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;

        char GetSymbol() const override;
    };
} // Math

#endif //HOMEWORKHELPER_ADD_H