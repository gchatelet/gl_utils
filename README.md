gl_utils
========

A small library to provide the [RAII](http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization) principle to OpenGL.

It does not intend to provide any window creation or user input helpers.

Pseudocode Example
------------------

### Textures

    // #include "gl_utils/Texture.h"
    
    gl::Texture2D texture;
    const auto a = scope_bind(texture);
    glTexImage2D(texture.target, 0, GL_RGBA8, windowWidth, windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    

### Static vertex buffer

    // #include "gl_utils/BufferObjects.h"
    
    gl::StaticVbo vbo;
    const auto b = scope_bind(vbo);
    // do gl stuff
    

### Vertex array object

    // #include "gl_utils/VertexArrayObject.h"
    
    gl::VertexArrayObject vao;
    const auto c = scope_bind(vao);
    // do gl stuff

### Mesh

    // #include "gl_utils/Mesh.h"
    // #include <tuple>
    
    typedef std::tuple<float, float, float> Position;
    typedef std::tuple<float, float> UV;
    typedef std::tuple<Position, UV> Vertex;
    
    // describing the layout of the buffer.
    const gl::VertexAttributeDescriptors vertexDescriptors { gl::describe<Position>(3, GL_FLOAT), gl::describe<UV>(2, GL_FLOAT) };
    
    // the buffer itself
    const float z = 1;
    const std::vector<Vertex> vertices = { Vertex { Position { -1, -1, z }, UV { 0, 0 } }, //
                    Vertex { Position { -1, 1, z }, UV { 0, 1 } }, //
                    Vertex { Position { 1, 1, z }, UV { 1, 1 } }, //
                    Vertex { Position { 1, -1, z }, UV { 1, 0 } } };

    gl::Mesh mesh(GL_TRIANGLE_FAN, vertexDescriptors, vertices.data(), vertices.size());
    auto bound = scope_bind(mesh);
    mesh.draw();

License
-------

    see LICENSE file
