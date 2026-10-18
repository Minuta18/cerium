#ifndef CERIUM_RMLGLFWSYSTEMINTERFACE_HPP
#define CERIUM_RMLGLFWSYSTEMINTERFACE_HPP

#include <RmlUi/Core/SystemInterface.h>

class GLFWWindow;

class RmlGLFWSystemInterface final : public Rml::SystemInterface {
    GLFWWindow* window;
    double startTime = 0.0;

public:
    explicit RmlGLFWSystemInterface(GLFWWindow* window);

    double GetElapsedTime() override;

    int TranslateString(
        Rml::String &translated, const Rml::String &input
    ) override;

    void JoinPath(
        Rml::String &translated_path,
        const Rml::String &document_path,
        const Rml::String &path
    ) override;

    bool LogMessage(Rml::Log::Type type, const Rml::String &message) override;

    void GetClipboardText(Rml::String &text) override;
    void SetClipboardText(const Rml::String &text) override;

    void SetMouseCursor(const Rml::String &cursor_name) override;
    void ActivateKeyboard(
        Rml::Vector2f caret_position, float line_height
    ) override;
    void DeactivateKeyboard() override;
};

#endif //CERIUM_RMLGLFWSYSTEMINTERFACE_HPP
