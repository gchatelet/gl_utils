#pragma once

#include "RAIIBase.h"
#include "BufferObjects.h"
#include "VertexArrayObject.h"

#include <vector>

namespace gl {

struct VertexAttributeDescriptor {
    size_t attributeSize;
    GLint glDimension;
    GLenum glComponentType;
    GLboolean glNormalized;
};

template<typename T>
VertexAttributeDescriptor describe(GLint dimension, GLenum componentType = GL_FLOAT, GLboolean normalized = GL_FALSE) {
    return {sizeof(T), dimension, componentType, normalized};
}

typedef std::vector<VertexAttributeDescriptor> VertexAttributeDescriptors;

class Mesh : public ::gl::utils::IBindable {
public:
    Mesh(GLuint primitiveType, const VertexAttributeDescriptors& vertexDescriptors, const void *pVBegin, const size_t vertexCount);
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

class IndexedMesh : public Mesh {
public:
    IndexedMesh(GLuint primitiveType, const VertexAttributeDescriptors&, const void *pVBegin, const size_t vertexCount, const GLuint *pIBegin, const size_t indexCount);
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
