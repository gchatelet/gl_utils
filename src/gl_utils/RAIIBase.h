#pragma once

#include <GL/gl.h>
#include <cassert>

namespace gl {
namespace utils {

/**
 * Provides OpenGL binding abstraction with reference counting.
 */
class IBindable {
public:
    IBindable() : m_ReferenceCount(0) { }
    virtual ~IBindable() { }

    // non copyable
    IBindable(const IBindable&) = delete;
    IBindable & operator=(const IBindable&) = delete;

protected:
    virtual void bind() const=0;
    virtual void unbind() const=0;

private:
    template<class BINDABLE> friend struct Binder;

    inline void doBind() const {
        if (m_ReferenceCount == 0) bind();
        ++m_ReferenceCount;
    }

    inline void doUnbind() const {
        assert(m_ReferenceCount > 0);
        --m_ReferenceCount;
        if (m_ReferenceCount == 0) unbind();
    }

    mutable unsigned m_ReferenceCount = 0;
};

/**
 * Friend struct to provide typed RAII for scope binding.
 */
template<typename BINDABLE>
struct Binder {
    Binder(const BINDABLE& bindable) : bindable(bindable) { bindable.doBind(); }
    ~Binder() { bindable.doUnbind(); }
    // non copyable but movable
    Binder(Binder&&) = default;
    Binder() = delete;
    Binder(const Binder&) = delete;
    Binder & operator=(const Binder&) = delete;
private:
    const BINDABLE& bindable;
};

/**
 * Base of an OpenGl object.
 * It manages the generation/deletion of the underlying OpenGl id.
 */
class GlObject: public IBindable {
public:
    explicit GlObject(GLuint id) : id(id) {}
    virtual ~GlObject() {}

    const GLuint id;
};

} /* namespace utils */

template<typename BINDABLE>
utils::Binder<BINDABLE> scope_bind(const BINDABLE& bindable) { return {bindable}; }

} /* namespace gl */
