#pragma once

#include "RAIIBase.h"

namespace gl {

/**
 * BufferObject
 * allocation  : glGenBuffers
 * destruction : glDeleteBuffers
 * binding     : glBindBuffer
 */
class BufferObject: public ::gl::utils::GlObject {
public:
    BufferObject(GLenum target, GLenum usage);
    virtual ~BufferObject();

    virtual void bind() const;
    virtual void unbind() const;

    const GLenum target;
    const GLenum usage;
};

/**
 * BufferObject with
 * target : GL_ARRAY_BUFFER
 * usage  : GL_STATIC_DRAW
 */
struct StaticVbo: public BufferObject {
    StaticVbo();
};

/**
 * BufferObject with
 * target : GL_ELEMENT_ARRAY_BUFFER
 * usage  : GL_STATIC_DRAW
 */
struct StaticIndexedVbo: public BufferObject {
    StaticIndexedVbo();
};

/**
 * BufferObject with
 * target : GL_PIXEL_UNPACK_BUFFER
 * usage  : GL_STREAM_DRAW
 */
struct StreamUploadPbo: public BufferObject {
    StreamUploadPbo();
};

/**
 * BufferObject with
 * target : GL_PIXEL_UNPACK_BUFFER
 * usage  : GL_STATIC_DRAW
 */
struct StaticUploadPbo: public BufferObject {
    StaticUploadPbo();
};

} /* namespace gl */
