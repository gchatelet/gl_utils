#include "VertexArrayObject.h"

extern void glBindVertexArray(GLuint array);
extern void glDeleteVertexArrays(GLsizei n, const GLuint *arrays);
extern void glGenVertexArrays(GLsizei n, GLuint *arrays);

namespace gl {

namespace {

GLuint allocateVertexArrayObject() {
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}

}  // namespace

VertexArrayObject::VertexArrayObject() :
                GlObject(allocateVertexArrayObject()) {
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &id);
}

void VertexArrayObject::bind() const {
    glBindVertexArray(id);
}

void VertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

} /* namespace gl */
