#include "GlMesh.h"

#include "GlUtils.h"

#include <stdexcept>

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

GlMesh::GlMesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount) :
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

GlMesh::~GlMesh() {
}
void GlMesh::bind() const {
    vao.bind();
}
void GlMesh::draw() const {
    callDraw();
    glCheckError();
}
void GlMesh::unbind() const {
    vao.unbind();
}
void GlMesh::callDraw() const {
    glDrawArrays(primitiveType, 0, vertexCount);
}

GlIndexedMesh::GlIndexedMesh(GLuint primitiveType, const VertexPosUv0 *pVBegin, const size_t vertexCount, const GLuint *pIBegin, const size_t indexCount) :
                GlMesh(primitiveType, pVBegin, vertexCount), indexCount(indexCount), ivbo() {
    auto ivboBound = scope_bind(ivbo);
    glBufferData(ivbo.target, indexCount * sizeof(GLuint), pIBegin, ivbo.usage);
    glCheckError();
}
GlIndexedMesh::~GlIndexedMesh() {
}
void GlIndexedMesh::bind() const {
    GlMesh::bind();
    ivbo.bind();
}
void GlIndexedMesh::callDraw() const {
    glDrawElements(primitiveType, indexCount, GL_UNSIGNED_INT, 0);
}
void GlIndexedMesh::unbind() const {
    ivbo.unbind();
    GlMesh::unbind();
}

} /* namespace gl */
