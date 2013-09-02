#pragma once

#include "GlRAIIBase.h"

namespace gl {

class GlVertexArrayObject : public gl::utils::GlObject {
public:
    GlVertexArrayObject();
    virtual ~GlVertexArrayObject();

    virtual void bind() const;
    virtual void unbind() const;
};

} /* namespace gl */
