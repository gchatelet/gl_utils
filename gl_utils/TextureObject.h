#pragma once

#include "RAIIBase.h"

namespace gl {

/**
 * TextureObject
 * allocation  : glGenTextures
 * destruction : glDeleteTextures
 * binding     : glBindTexture
 */
class TextureObject: public ::gl::utils::GlObject {
public:
    TextureObject(GLenum target);
    virtual ~TextureObject();

    const GLenum target;

protected:
    virtual void bind() const;
    virtual void unbind() const;
};

/**
 * TextureObject with
 * target : GL_TEXTURE_2D
 */
struct Texture2D: public TextureObject {
    Texture2D();
};

/**
 * TextureObject with
 * target : GL_TEXTURE_RECTANGLE
 */
struct TextureRectangle: public TextureObject {
    TextureRectangle();
};

} /* namespace gl */
