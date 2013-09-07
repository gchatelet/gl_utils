#pragma once

#include "RAIIBase.h"

namespace gl {

class BufferObject: public ::gl::utils::GlObject {
public:
    BufferObject(GLenum target, GLenum usage);
    virtual ~BufferObject();

    virtual void bind() const;
    virtual void unbind() const;

    const GLenum target;
    const GLenum usage;
};

struct StaticVbo: public BufferObject {
    StaticVbo();
};

struct StaticIndexedVbo: public BufferObject {
    StaticIndexedVbo();
};

struct StreamUploadPbo: public BufferObject {
    StreamUploadPbo();
};

struct StaticUploadPbo: public BufferObject {
    StaticUploadPbo();
};

} /* namespace gl */
