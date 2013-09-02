#include "GlTextureObject.h"

namespace gl {

namespace {

GLuint allocateTextureObject() {
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

}  // namespace

GlTextureObject::GlTextureObject(GLenum target) :
                GlObject(allocateTextureObject()), target(target) {
}
GlTextureObject::~GlTextureObject() {
    glDeleteTextures(1, &id);
}
void GlTextureObject::bind() const {
    glBindTexture(target, id);
}
void GlTextureObject::unbind() const {
    glBindTexture(target, 0);
}

GlTexture2D::GlTexture2D() :
                GlTextureObject(GL_TEXTURE_2D) {
}

GlTextureRectangle::GlTextureRectangle() :
                GlTextureObject(GL_TEXTURE_RECTANGLE) {
}

} /* namespace gl */
