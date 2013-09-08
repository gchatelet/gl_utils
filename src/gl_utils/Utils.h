#pragma once

namespace gl {

/**
 * Function throwing on OpenGL error.
 * This function can be inserted from time to time as a checkpoint
 * to check that OpenGL is in a sane state.
 */
void glCheckError();

} /* namespace gl */
