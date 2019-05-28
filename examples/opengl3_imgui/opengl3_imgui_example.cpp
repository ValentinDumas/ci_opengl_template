#include <imgui/imgui.h>
#include "imgui_sfml/imgui-SFML.h" // TODO: put it as one file in externals folder

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

enum LoadFontType {
    LOAD_CUSTOM_FONTS = 0, LOAD_DEFAULT_FONTS = 1
};

struct Point
{
    float x;
    float y;
};

struct Rect
{
    float x;
    float y;
    float w;
    float h;
};

/// Reference: https://eliasdaler.github.io/using-imgui-with-sfml-pt1
/// Reference: https://eliasdaler.github.io/using-imgui-with-sfml-pt2
namespace ImGui {
    namespace custom
    {
        bool InputRect(const char *label, Rect *rectPtr, int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0) {
            ImGui::PushID(label);
            ImGui::BeginGroup();

            bool valueChanged = false;

            std::array<float *, 4> arr = {&rectPtr->x, &rectPtr->y,
                                          &rectPtr->w, &rectPtr->h};

            for (auto &elem : arr) {
                ImGui::PushID(elem);
                ImGui::PushItemWidth(64.f);
                valueChanged |= ImGui::InputFloat("##arr", elem, 0, 0,
                                                  decimal_precision, extra_flags);
                ImGui::PopID();
                ImGui::SameLine();
            }

            ImGui::SameLine();
            ImGui::TextUnformatted(label);
            ImGui::EndGroup();

            ImGui::PopID(); // pop label id;

            return valueChanged;
        }

        static auto vector_getter = [](void* vec, int idx, const char** out_text)
        {
            auto& vector = *static_cast<std::vector<std::string>*>(vec);
            if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
            *out_text = vector.at(idx).c_str();
            return true;
        };

        bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
        {
            if (values.empty()) { return false; }
            return ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
        }

        bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
        {
            if (values.empty()) { return false; }
            return ImGui::ListBox(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
        }

        // TODO: see if there is a way to return some InputText's result for further processing.
//        void InputText(const char* label)
//        {
//            std::array<char, 256> arrayOfChars = { "" };
//            ImGui::InputText(label, arrayOfChars.data(), arrayOfChars.size());
//        }
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window, LoadFontType::LOAD_DEFAULT_FONTS);

    sf::Color bgColor;
    float color[3] = {0.f, 0.f, 0.f}; // Define a color (0.0f <= x <= 1.0f)
    char windowTitle[255] = "C++ SFML (with OpenGL) + ImGui";

    window.setTitle(windowTitle);
    //window.resetGLStates(); // Call it you ONLY draw ImGui

    std::array<int, 10> arr = {0};
    Point point{0.f, 0.f};
    Rect rect{0.f, 0.f, 0.f, 0.f};

    if (sf::Joystick::isConnected(0))
    {
        // le joystick numéro 0 est connecté
        std::cout << "Le joystick 0 est connecté !" << std::endl;

        // combien de boutons le joystick numéro 0 a-t-il ?
        unsigned int buttonCount = sf::Joystick::getButtonCount(0);
        std::cout << "Le joystick 0 a " << buttonCount << " boutons" << std::endl;

        // est-ce que le joystick numéro 0 possède un axe Z ?
        bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);
    }

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Joystick::isButtonPressed(0, 1))
        {
            // oui : on shoot !!
            std::cout << "Button 1 pressed !" << std::endl;
        }

        ////// Note: You must create all widgets between ImGui::SFML::Update() and ImGui::Render()    !!
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample window"); // Begin ImGui window
        {
            float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
            ImGui::SetWindowPos(ImVec2(x,y));

            if(ImGui::ColorEdit3("Background color", color))
            {
                bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
                bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
                bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
            }

            ImGui::InputText("Window Title", windowTitle, 255);

            if(ImGui::Button("Update window title"))
            {
                // This code is executed only if the user clicked on the button;
                window.setTitle(windowTitle);
            }

            ImGui::SameLine();

            if(ImGui::Button("Update window title##Second"))
            {
                // This code is executed only if the user clicked on the button;
                window.setTitle(windowTitle);
            }

            // Input text with a callback
            std::array<char, 256> textArr = {""};
            ImGui::InputText("Text", textArr.data(), textArr.size(),
                             ImGuiInputTextFlags_CallbackCharFilter,
                             [](ImGuiTextEditCallbackData* data)
                             {
                                 data->EventChar = 'A';
                                 return 0;
                             }
            );
        }
        ImGui::End();

        ImGui::Begin("Sample window");
        {
            for (int i = 0; i < arr.size(); ++i) {
                ImGui::PushID(i);
                ImGui::InputInt("##", &arr[i]);
                ImGui::PopID();
            }

            ImGui::InputFloat2("Point", &point.x);
            ImGui::InputFloat4("RectUnsafe", &rect.x);

            ImGui::custom::InputRect("RectSafe", &rect);
        }
        ImGui::End();

        ImGui::ShowDemoWindow(); // Demo window (ImGui)

        window.clear(bgColor);
        //windows.draw(smthg);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
