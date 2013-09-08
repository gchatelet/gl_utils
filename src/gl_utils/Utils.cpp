#include "Utils.h"

#include <GL/gl.h>

#include <vector>
#include <sstream>
#include <stdexcept>

namespace gl {

namespace  {

#ifndef NDEBUG
static const char* getErrorString(unsigned error) {
    switch (error) {
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
            //case GL_STACK_UNDERFLOW:
            //  throw std::runtime_error("OpenGL : Stack underflow");
            //case GL_STACK_OVERFLOW:
            //  throw std::runtime_error("OpenGL : Stack overflow");
    }
    return "Unknown error";
}
#endif

}  // namespace

void glCheckError() {
#ifndef NDEBUG
    std::vector<unsigned> errors;
    unsigned error = GL_NO_ERROR;
    for (; (error = glGetError()) != GL_NO_ERROR;)
        errors.push_back(error);
    if (errors.empty())
        return;
    std::ostringstream oss;
    oss << "OpenGL errors :\n";
    for (const unsigned error : errors)
        oss << " - " << getErrorString(error) << '\n';
    throw std::runtime_error(oss.str());
#endif
}

} /* namespace gl */
