#include "GlVertexArrayObject.h"

extern void glBindVertexArray (GLuint array);
extern void glDeleteVertexArrays (GLsizei n, const GLuint *arrays);
extern void glGenVertexArrays (GLsizei n, GLuint *arrays);

namespace gl {

namespace {

GLuint allocateVertexArrayObject() {
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}

}  // namespace

GlVertexArrayObject::GlVertexArrayObject() :
                GlObject(allocateVertexArrayObject()) {
}

GlVertexArrayObject::~GlVertexArrayObject() {
    glDeleteVertexArrays(1, &id);
}

void GlVertexArrayObject::bind() const {
    glBindVertexArray(id);
}

void GlVertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

} /* namespace gl */
