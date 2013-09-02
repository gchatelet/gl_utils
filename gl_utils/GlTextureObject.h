#pragma once

#include "GlRAIIBase.h"

namespace gl {

class GlTextureObject: public ::gl::utils::GlObject {
public:
    GlTextureObject(GLenum target);
    virtual ~GlTextureObject();

    const GLenum target;

protected:
    virtual void bind() const;
    virtual void unbind() const;
};

struct GlTexture2D: public GlTextureObject {
    GlTexture2D();
};

struct GlTextureRectangle: public GlTextureObject {
    GlTextureRectangle();
};

} /* namespace gl */
