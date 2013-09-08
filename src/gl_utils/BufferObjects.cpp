#include "BufferObjects.h"

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

BufferObject::BufferObject(GLenum target, GLenum usage) :
                GlObject(allocateBufferObject()), target(target), usage(usage) {
}
BufferObject::~BufferObject() {
    glDeleteBuffers(1, &id);
}
void BufferObject::bind() const {
    glBindBuffer(target, id);
}
void BufferObject::unbind() const {
    glBindBuffer(target, 0);
}

StaticVbo::StaticVbo() :
                BufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW) {
}

StaticIndexedVbo::StaticIndexedVbo() :
                BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW) {
}

StreamUploadPbo::StreamUploadPbo() :
                BufferObject(GL_PIXEL_UNPACK_BUFFER, GL_STREAM_DRAW) {
}

StaticUploadPbo::StaticUploadPbo() :
                BufferObject(GL_PIXEL_UNPACK_BUFFER, GL_STATIC_DRAW) {
}
} /* namespace gl */
