////////////////////////////////////////////////////////////////////////////////
//
///	Class to perform the management of an opengl FBO
/// Typical use : Render to Texture
///	Typical usage :
///			GlFrameBufferObject fbo;
///			fbo.bind();
///			fbo.attachTexture(GL_COLOR_ATTACHMENT0_EXT,... texId0);
///			fbo.attachTexture(GL_COLOR_ATTACHMENT1_EXT,... texId1);
///			fbo.checkFramebufferStatus(); // must return true
///     ... drawing operations
///			fbo.unbind();
///			to desactivate the FBO use GlFrameBufferObject::Disable();
///			Desactivate the FBO and release hand to OPENGL standard FrameBuffer object
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "RAIIBase.h"

namespace gl {

class FrameBufferObject : public ::gl::utils::GlObject {

	mutable GLint m_OldFboID;	//The ID of the old FBO when we will bind our instance FBO (it's to restore the old FBO)

public:
	FrameBufferObject(void);
	virtual ~FrameBufferObject(void);

	/// Bind this FBO as current render target
	virtual void bind() const;
	virtual void unbind() const;

public:

	/// Bind a texture to the "attachment" point of this FBO (GL_COLOR_ATTACHMENT0, textarget, texID)
	/// A fbo must be binded.
	void attachTexture( GLenum attachment, GLenum texType, GLuint texId,
								int mipLevel = 0, int zSlice = 0);

	//--------------------------------------------------------------------
	//Hardware capabilities -> Be carefull (initialize Opengl before calling those funcs)
	//---------------------
	//Check if the active FBO is ready to do a render task
	static bool checkFramebufferStatus();
	// BEGIN : Static methods global to all FBOs
	// Return number of color attachments permitted
	static int getMaxColorAttachments();
	//--------------------------------------------------------------------

	/// Disable all FBO rendering and return to classic opengl framebuffer pipeline
	///  NOTE:
	///     This is NOT an "unbind" for this specific FBO, but rather
	///     disables all FBO rendering. This call is intentionally "static"
	///     and named "Disable" instead of "Unbind" for this reason. The
	///     motivation for this strange semantic is performance. Providing "Unbind"
	///     would likely lead to a large number of unnecessary FBO enablings/disabling.
	static void disable();
	/// END : Static methods global to all FBOs
};

} /* namespace gl */

