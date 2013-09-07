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

}  // namespace

Mesh::Mesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount) :
                primitiveType(checkType(primitiveType)), vertexCount(vertexCount) {
    auto vaoBound = scope_bind(vao);
    auto vboBound = scope_bind(vbo);
    glBufferData(vbo.target, vertexCount * sizeof(VertexPosUv0), pVBegin, vbo.usage);
    glCheckError();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosUv0), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosUv0), (const GLvoid*) (sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);
    glCheckError();
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

IndexedMesh::IndexedMesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount, const GLuint *pIBegin, const size_t indexCount) :
                Mesh(primitiveType, pVBegin, vertexCount), indexCount(indexCount), ivbo() {
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
