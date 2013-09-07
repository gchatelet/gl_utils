#pragma once

#include "RAIIBase.h"

namespace gl {

class TextureObject: public ::gl::utils::GlObject {
public:
    TextureObject(GLenum target);
    virtual ~TextureObject();

    const GLenum target;

protected:
    virtual void bind() const;
    virtual void unbind() const;
};

struct Texture2D: public TextureObject {
    Texture2D();
};

struct TextureRectangle: public TextureObject {
    TextureRectangle();
};

} /* namespace gl */
