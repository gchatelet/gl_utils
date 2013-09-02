#include "GlBufferObjects.h"

extern void glGenBuffers (GLsizei n, GLuint *buffers);
extern void glDeleteBuffers (GLsizei n, const GLuint *buffers);
extern void glBindBuffer (GLenum target, GLuint buffer);

namespace gl {

namespace {

GLuint allocateBufferObject() {
    GLuint id;
    glGenBuffers(1, &id);
    return id;
}

}  // namespace

GlBufferObject::GlBufferObject(GLenum target, GLenum usage) :
                GlObject(allocateBufferObject()), target(target), usage(usage) {
}
GlBufferObject::~GlBufferObject() {
    glDeleteBuffers(1, &id);
}
void GlBufferObject::bind() const {
    glBindBuffer(target, id);
}
void GlBufferObject::unbind() const {
    glBindBuffer(target, 0);
}

GlStaticVbo::GlStaticVbo() :
                GlBufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW) {
}

GlStaticIndexedVbo::GlStaticIndexedVbo() :
                GlBufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
}

GlStreamUploadPbo::GlStreamUploadPbo() :
                GlBufferObject(GL_PIXEL_UNPACK_BUFFER, GL_STREAM_DRAW) {
}

GlStaticUploadPbo::GlStaticUploadPbo() :
                GlBufferObject(GL_PIXEL_UNPACK_BUFFER, GL_STATIC_DRAW) {
}
} /* namespace gl */
