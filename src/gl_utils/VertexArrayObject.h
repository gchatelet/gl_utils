#pragma once

#include "RAIIBase.h"

namespace gl {

/**
 * VertexArrayObject
 * allocation  : glGenVertexArrays
 * destruction : glDeleteVertexArrays
 * binding     : glBindVertexArray
 */
class VertexArrayObject : public gl::utils::GlObject {
public:
    VertexArrayObject();
    virtual ~VertexArrayObject();

    virtual void bind() const;
    virtual void unbind() const;
};

} /* namespace gl */
