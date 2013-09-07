#include "TextureObject.h"

namespace gl {

namespace {

GLuint allocateTextureObject() {
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

}  // namespace

TextureObject::TextureObject(GLenum target) :
                GlObject(allocateTextureObject()), target(target) {
}
TextureObject::~TextureObject() {
    glDeleteTextures(1, &id);
}
void TextureObject::bind() const {
    glBindTexture(target, id);
}
void TextureObject::unbind() const {
    glBindTexture(target, 0);
}

Texture2D::Texture2D() :
                TextureObject(GL_TEXTURE_2D) {
}

TextureRectangle::TextureRectangle() :
                TextureObject(GL_TEXTURE_RECTANGLE) {
}

} /* namespace gl */
