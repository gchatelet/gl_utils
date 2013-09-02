#pragma once

#include "GlRAIIBase.h"
#include "GlBufferObjects.h"
#include "GlVertexArrayObject.h"

#include <glm/glm.hpp>

namespace gl {

struct VertexPosUv0 {
    glm::vec3 position;
    glm::vec2 uv0;
    VertexPosUv0(glm::vec3 pos) :
            position(pos) {
    }
    VertexPosUv0(glm::vec3 pos, glm::vec2 uv0) :
            position(pos), uv0(uv0) {
    }
};

class GlMesh: public ::gl::utils::IBindable {
public:
    GlMesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount);
    virtual ~GlMesh();

    virtual void bind() const;
    virtual void unbind() const;

    void draw() const;

protected:
    const GLuint primitiveType;
    virtual void callDraw() const;

private:
    const size_t vertexCount;
    const gl::GlVertexArrayObject vao;
    const gl::GlStaticVbo vbo;
};

class GlIndexedMesh: public GlMesh {
public:
    GlIndexedMesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount, const GLuint *pIBegin, const size_t indexCount);
    virtual ~GlIndexedMesh();

    virtual void bind() const;
    virtual void unbind() const;

protected:
    virtual void callDraw() const;

private:
    const size_t indexCount;
    const gl::GlStaticIndexedVbo ivbo;
};


} /* namespace gl */
