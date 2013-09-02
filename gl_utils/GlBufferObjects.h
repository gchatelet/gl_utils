#pragma once

#include "GlRAIIBase.h"

namespace gl {

class GlBufferObject: public ::gl::utils::GlObject {
public:
    GlBufferObject(GLenum target, GLenum usage);
    virtual ~GlBufferObject();

    virtual void bind() const;
    virtual void unbind() const;

    const GLenum target;
    const GLenum usage;
};

struct GlStaticVbo: public GlBufferObject {
    GlStaticVbo();
};

struct GlStaticIndexedVbo: public GlBufferObject {
    GlStaticIndexedVbo();
};

struct GlStreamUploadPbo: public GlBufferObject {
    GlStreamUploadPbo();
};

struct GlStaticUploadPbo: public GlBufferObject {
    GlStaticUploadPbo();
};

} /* namespace gl */
