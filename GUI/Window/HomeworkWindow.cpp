#include "HomeworkWindow.h"

#include <format>

#include "GUI/ImguiComponents/Window.h"
#include "GUI/ImguiComponents/Label.h"
#include "GUI/ImguiComponents/Checkbox.h"
#include "GUI/ImguiComponents/IntField.h"
#include "GUI/ImguiComponents/FloatField.h"
#include "GUI/ImguiComponents/Button.h"
#include "GUI/ImguiComponents/SameLine.h"
#include "GUI/ImguiComponents/SeparatorLine.h"

namespace HomeworkHelper
{
    void HomeworkWindow::GenerateImguiContent()
    {
        myGenerator.SetExtremes(myMin, myMax);

        // Temporary content to test the system
        int flags = Component::WindowFlags::RemoveTopBar | Component::WindowFlags::DisableResize |
                    Component::WindowFlags::SetPositionEveryStart | Component::WindowFlags::SetSizeEveryStart;
        const auto& baseWindow = myComponents.emplace_back(
            std::make_unique<Component::Window>("Homework", nullptr, Common::Vec2{}, Common::Vec2{}, flags)
        );
        auto& window = dynamic_cast<Component::Window &>(*baseWindow);

        window.AddChildNode(
            std::make_unique<Component::Label>(
                "Välj inom vilket spann talen ska genereras och vilka matematik operationer som ska skapas."
            )
        );

        for (int i = 0; i < mySelectedSymbols.size(); ++i) {
            window.AddChildNode(
                std::make_unique<Component::Checkbox>(
                    std::string(1, mySymbolList[i]),
                    &mySelectedSymbols[i],
                    [this, i] {
                        if (mySelectedSymbols[i]) {
                            myGenerator.AddGenerator(mySymbolList[i]);
                        }
                        else {
                            myGenerator.RemoveGenerator(mySymbolList[i]);
                        }
                        NewQuestion();
                    }
                )
            );
            if (i < mySelectedSymbols.size() - 1) {
                window.AddChildNode(std::make_unique<Component::SameLine>());
            }
        }

        window.AddChildNode(
            std::make_unique<Component::IntField>(
                "Minimum",
                &myMin,
                [this] {
                    myGenerator.SetExtremes(myMin, myMax);
                    NewQuestion();
                }
            )
        );

        window.AddChildNode(
            std::make_unique<Component::IntField>(
                "Maximum",
                &myMax,
                [this] {
                    myGenerator.SetExtremes(myMin, myMax);
                    NewQuestion();
                }
            )
        );

        std::make_unique<Component::Checkbox>(
            "Decimal tal",
            &myIsUsingFloats,
            [this] {
                myGenerator.SetUseFloats(myIsUsingFloats);
                NewQuestion();
            }
        );

        window.AddChildNode(std::make_unique<Component::SeparatorLine>());
        window.AddChildNode(std::make_unique<Component::DynamicLabel>([this] { return myGenerator.GetQuestion(); }));

        if (myIsUsingFloats) {
            myAnswer.f = 0.f;
            window.AddChildNode(
                std::make_unique<Component::FloatField>("Svar", &myAnswer.f, [this] {
                    myHasAnswered = false;
                    myShouldShowAnswer = false;
                })
            );
        }
        else {
            myAnswer.i = 0;
            window.AddChildNode(
                std::make_unique<Component::IntField>("Svar", &myAnswer.i, [this] {
                    myHasAnswered = false;
                    myShouldShowAnswer = false;
                })
            );
        }

        window.AddChildNode(
            std::make_unique<Component::DynamicLabel>(
                [this]()-> std::string {
                    if (myHasAnswered) {
                        if (myGenerator.GetQuestion().empty()) {
                            return "Du måste skapa en ny fråga innan du kan svara!";
                        }
                        bool isCorrect = myIsUsingFloats ?
                                             myGenerator.CheckAnswer(myAnswer.f) :
                                             myGenerator.CheckAnswer(myAnswer.i);
                        if (isCorrect) {
                            return "Rätt svar! Bra gjort :D";
                        }
                        return "Fel svar. Försök igen!";
                    }
                    if (myShouldShowAnswer) {
                        const std::string& answer = myIsUsingFloats ?
                                                        std::to_string(myGenerator.GetAnswerFloat()) :
                                                        std::to_string(myGenerator.GetAnswerInt());
                        return "Rätt svar är: " + answer;
                    }
                    return "";
                }
            )
        );

        window.AddChildNode(
            std::make_unique<Component::Button>("Svara", Common::Vec2{0.f, 0.f}, [this] { myHasAnswered = true; })
        );
        window.AddChildNode(std::make_unique<Component::SameLine>());
        window.AddChildNode(
            std::make_unique<Component::Button>(
                "Ny Fråga",
                Common::Vec2{0.f, 0.f},
                [this] {
                    NewQuestion();
                }
            )
        );
        window.AddChildNode(std::make_unique<Component::SameLine>());
        window.AddChildNode(
            std::make_unique<Component::Button>(
                "Visa svar",
                Common::Vec2{0.f, 0.f},
                [this] { myShouldShowAnswer = true; }
            )
        );
    }

    void HomeworkWindow::UpdateImguiContent()
    {
        for (const auto& component: myComponents) {
            component->UpdateContent();
        }
    }

    void HomeworkWindow::SetWindowData(ImGui_ImplVulkanH_Window* someWindowData)
    {
        myWindowData = someWindowData;
    }

    void HomeworkWindow::NewQuestion()
    {
        myHasAnswered = false;
        myShouldShowAnswer = false;
        myGenerator.GenerateQuestion();
    }
} // HomeworkHelper
