#include "Mesh.h"

#include "Utils.h"

#include <stdexcept>

extern void glBufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
extern void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
extern void glEnableVertexAttribArray(GLuint index);

namespace gl {

namespace {

GLuint checkType(GLuint primitiveType) {
    switch (primitiveType) {
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_LOOP:
        case GL_LINE_STRIP:
        case GL_LINE_STRIP_ADJACENCY:
        case GL_LINES_ADJACENCY:
        case GL_TRIANGLES:
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP_ADJACENCY:
        case GL_TRIANGLES_ADJACENCY:
            //case GL_PATCHES:
            return primitiveType;
        default:
            throw std::runtime_error("invalid primitive mesh type");
    }
}

size_t computeVertexSize(const VertexAttributeDescriptors& vertexDescriptors) {
    size_t vertexSize = 0;
    for (const auto& vertexDescriptor : vertexDescriptors)
        vertexSize += vertexDescriptor.attributeSize;
    return vertexSize;
}

}  // namespace

Mesh::Mesh(GLuint primitiveType, const VertexAttributeDescriptors& vertexDescriptors, const void *pVBegin, const size_t vertexCount) :
                primitiveType(checkType(primitiveType)), vertexCount(vertexCount) {
    const size_t vertexSize = computeVertexSize(vertexDescriptors);
    auto vaoBound = scope_bind(vao);
    auto vboBound = scope_bind(vbo);
    glBufferData(vbo.target, vertexCount * vertexSize, pVBegin, vbo.usage);

    GLuint index = 0;
    GLsizei offset = 0;
    for (const auto& descriptor : vertexDescriptors) {
        glVertexAttribPointer(index, descriptor.size, descriptor.type, descriptor.normalized, vertexSize, reinterpret_cast<const GLvoid *>(offset));
        glEnableVertexAttribArray(index);
        ++index;
        offset += descriptor.attributeSize;
    }
}

Mesh::~Mesh() {
}
void Mesh::bind() const {
    vao.bind();
}
void Mesh::draw() const {
    callDraw();
    glCheckError();
}
void Mesh::unbind() const {
    vao.unbind();
}
void Mesh::callDraw() const {
    glDrawArrays(primitiveType, 0, vertexCount);
}

IndexedMesh::IndexedMesh(GLuint primitiveType, const VertexAttributeDescriptors& vertexDescriptors, const void *pVBegin, const size_t vertexCount, const GLuint *pIBegin,
                         const size_t indexCount) :
                Mesh(primitiveType, vertexDescriptors, pVBegin, vertexCount), indexCount(indexCount), ivbo() {
    auto ivboBound = scope_bind(ivbo);
    glBufferData(ivbo.target, indexCount * sizeof(GLuint), pIBegin, ivbo.usage);
    glCheckError();
}
IndexedMesh::~IndexedMesh() {
}
void IndexedMesh::bind() const {
    Mesh::bind();
    ivbo.bind();
}
void IndexedMesh::callDraw() const {
    glDrawElements(primitiveType, indexCount, GL_UNSIGNED_INT, 0);
}
void IndexedMesh::unbind() const {
    ivbo.unbind();
    Mesh::unbind();
}

} /* namespace gl */
