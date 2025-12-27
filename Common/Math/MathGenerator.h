#ifndef HOMEWORKHELPER_MATHGENERATOR_H
#define HOMEWORKHELPER_MATHGENERATOR_H
#include <memory>
#include <vector>
#include "Solvers/SolverBase.h"

namespace Math
{
    class MathGenerator
    {
    public:
        MathGenerator();
        MathGenerator(const std::string_view& aSymbolList, int aMin, int aMax, bool useFloats = false);
        ~MathGenerator() = default;

        void AddGenerator(char aSymbol);
        void AddGenerators(const std::string_view& aSymbolList);
        void RemoveGenerator(char aSymbol);
        void ClearGenerators();

        void SetExtremes(int aMin, int aMax);
        int GetMin() const;
        int GetMax() const;

        void SetUseFloats(bool aUseFloats);

        void GenerateQuestion();
        std::string GetQuestion() const;

        int GetAnswerInt() const;
        float GetAnswerFloat() const;

        bool CheckAnswer(int anAnswer) const;
        bool CheckAnswer(float anAnswer) const;

    private:
        bool myIsUsingFloats;
        int myMin;
        int myMax;
		int myCurrentSolverIndex;
        std::uniform_int_distribution<int> myNumberGenerator;
        std::string myQuestion;
        std::vector<std::unique_ptr<SolverBase>> mySolvers;
        std::mt19937 myEngine;
    };
} // Math

#endif //HOMEWORKHELPER_MATHGENERATOR_H
