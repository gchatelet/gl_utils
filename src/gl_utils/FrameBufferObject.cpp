#include "FrameBufferObject.hpp"
#include <iostream>

extern void glGenFramebuffers(GLsizei n, GLuint *ids);
extern void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
extern void glBindFramebuffer(GLenum target, GLuint framebuffer);

extern void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer);
extern GLenum glCheckFramebufferStatus(    GLenum      target);

namespace gl {

namespace {

inline static GLuint allocateFboObject() {
	GLuint id;
	glGenFramebuffers(1, &id);
	return id;
}

}  // namespace

FrameBufferObject::FrameBufferObject(void)
  : GlObject(allocateFboObject()), m_OldFboID(0)
{
}

FrameBufferObject::~FrameBufferObject(void)
{
	glDeleteFramebuffers(1, &id);
}

void FrameBufferObject::bind() const {
  // Only binds if m_fboId is different than the currently bound FBO
	glGetIntegerv( GL_FRAMEBUFFER_BINDING, &m_OldFboID );
	if (id != (GLuint)m_OldFboID) {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}
}

void FrameBufferObject::unbind() const {
  // Restore the previous active FBO
	// Returns FBO binding to the previously enabled FBO
	if (id != (GLuint)m_OldFboID) {
		glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)m_OldFboID);
	}
}

void FrameBufferObject::disable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/// Bind a texture to the "attachment" point of this FBO (GL_COLOR_ATTACHMENT0_EXT, textarget, texID)
void FrameBufferObject::attachTexture( GLenum attachment, GLenum texType, GLuint texId,int mipLevel, int zSlice)
{
	if (texType == GL_TEXTURE_1D) {
		glFramebufferTexture1D( GL_FRAMEBUFFER, attachment,
								   GL_TEXTURE_1D, texId, mipLevel );
	}
	else if (texType == GL_TEXTURE_3D) {
		glFramebufferTexture3D( GL_FRAMEBUFFER, attachment,
								   GL_TEXTURE_3D, texId, mipLevel, zSlice );
	}
	else {
		// Default is GL_TEXTURE_2D, GL_TEXTURE_RECTANGLE, or cube faces
		glFramebufferTexture2D( GL_FRAMEBUFFER, attachment,
								   texType, texId, mipLevel );
	}
}

//--------------------------------------------------------------------
// hardware test

int FrameBufferObject::getMaxColorAttachments()
{
	GLint maxAttach = 0;
	glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS, &maxAttach );
	return maxAttach;
}

// Checks framebuffer status.
bool FrameBufferObject::checkFramebufferStatus() {
  GLenum status;
  status = (GLenum) glCheckFramebufferStatus(GL_FRAMEBUFFER);
  switch(status) {
    case GL_FRAMEBUFFER_COMPLETE:
      return true;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tFramebuffer incomplete, incomplete attachment\n");
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tUnsupported framebuffer format\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tFramebuffer incomplete, missing attachment\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tFramebuffer incomplete, attached images must have same dimensions\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tFramebuffer incomplete, attached images must have same format\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tFramebuffer incomplete, missing draw buffer\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      std::cerr << ("CheckFramebufferStatus() ERROR:\n\tFramebuffer incomplete, missing read buffer\n");
      break;
  }
  return false;
}

} /* namespace gl */
