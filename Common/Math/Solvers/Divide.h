#ifndef HOMEWORKHELPER_DIVIDE_H
#define HOMEWORKHELPER_DIVIDE_H
#include "SolverBase.h"

namespace Math
{
    class Divide : public SolverBase
    {
    public:
        Divide() = default;
        Divide(int aFirst, int aSecond);
        Divide(float aFirst, float aSecond);
        ~Divide() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;
    };
} // Math

#endif //HOMEWORKHELPER_DIVIDE_H