#ifndef CERIUM_GRAPHICS_RMLOPENGLRENDERER_HPP
#define CERIUM_GRAPHICS_RMLOPENGLRENDERER_HPP

#include <RmlUi/Core/RenderInterface.h>
#include <glm/glm.hpp>

class RmlOpenGLRenderer : public Rml::RenderInterface {
    glm::mat4 transform;
    bool scissorEnabled = false;
    glm::ivec4 scissor = { 0, 0, 0, 0 };
    glm::ivec2 viewport = { 0, 0 };
public:
    bool init();
    void shutdown();

    void beginFrame(glm::ivec2 frameViewport);
    void endFrame();

    Rml::CompiledGeometryHandle CompileGeometry(
        Rml::Span<const Rml::Vertex> vertices,
        Rml::Span<const int> indices
    ) override;

    void RenderGeometry(
        Rml::CompiledGeometryHandle geometry,
        Rml::Vector2f translation,
        Rml::TextureHandle texture
    ) override;

    void ReleaseGeometry(Rml::CompiledGeometryHandle geometry) override;

    void EnableScissorRegion(bool enable) override;
    void SetScissorRegion(Rml::Rectanglei region) override;

    void SetTransform(const Rml::Matrix4f *transform) override;
};

#endif // CERIUM_GRAPHICS_RMLOPENGLRENDERER_HPP
