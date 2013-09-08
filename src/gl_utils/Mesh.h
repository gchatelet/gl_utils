#pragma once

#include "RAIIBase.h"
#include "BufferObjects.h"
#include "VertexArrayObject.h"

#include <vector>

namespace gl {

/**
 * Describes the layout of a vertex in memory for OpenGL.
 * See http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribPointer.xml for
 * a better description of the fields.
 *
 * Use the describe method below.
 */
struct VertexAttributeDescriptor {
    // the size of the attribute. eg: sizeof(float[3]) for a position.
    size_t attributeSize;
    // the number dimensions for the type. eg: 3 for a position.
    GLint size;
    // the OpenGL type representing the dimension. eg: GL_FLOAT for a position.
    GLenum type;
    // if the coordinate should be normalized on import
    GLboolean normalized;
};

/**
 * Helper function to create a description of an attribute.
 * eg: description of an UV coordinate made of two floats
 * const auto attributeDescription = gl::describe<float[2]>(2, GL_FLOAT);
 */
template<typename T>
VertexAttributeDescriptor describe(GLint dimension, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE) {
    return {sizeof(T), dimension, type, normalized};
}

// A vector of attribute descriptors describing the Vertex layout.
typedef std::vector<VertexAttributeDescriptor> VertexAttributeDescriptors;



/**
 * A simple mesh managing its own VAO and VBO.
 * This is a static Mesh that is set once for all and can't change.
 */
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


/**
 * An indexed mesh managing its own VAO, VBO for vertices and VBO for indices.
 * This is a static Mesh that is set once for all and can't change.
 */
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
