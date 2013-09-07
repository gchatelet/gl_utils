#pragma once

#include "RAIIBase.h"
#include "BufferObjects.h"
#include "VertexArrayObject.h"

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

class Mesh: public ::gl::utils::IBindable {
public:
    Mesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount);
    virtual ~Mesh();

    virtual void bind() const;
    virtual void unbind() const;

    void draw() const;

protected:
    const GLuint primitiveType;
    virtual void callDraw() const;

private:
    const size_t vertexCount;
    const gl::VertexArrayObject vao;
    const gl::StaticVbo vbo;
};

class IndexedMesh: public Mesh {
public:
    IndexedMesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount, const GLuint *pIBegin, const size_t indexCount);
    virtual ~IndexedMesh();

    virtual void bind() const;
    virtual void unbind() const;

protected:
    virtual void callDraw() const;

private:
    const size_t indexCount;
    const gl::StaticIndexedVbo ivbo;
};


} /* namespace gl */
