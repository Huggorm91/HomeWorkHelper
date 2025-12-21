#ifndef HOMEWORKHELPER_ADD_H
#define HOMEWORKHELPER_ADD_H
#include "SolverBase.h"

namespace Math
{
    class Add: public SolverBase
    {
    public:
        Add() = default;
        Add(int aFirst, int aSecond);
        Add(float aFirst, float aSecond);
        ~Add() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;
    };
} // Math

#endif //HOMEWORKHELPER_ADD_H