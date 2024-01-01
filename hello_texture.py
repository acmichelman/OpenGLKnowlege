import glfw
from OpenGL.GL import *
import numpy as np
from PIL import Image

vertex_shader_source = """
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

void main() {
    gl_Position = vec4(position, 1.0);
    TexCoord = texCoord;
}
"""

fragment_shader_source = """
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, TexCoord);
}
"""

def load_texture(path):
    texture = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, texture)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    
    image = Image.open(path)
    image = image.transpose(Image.FLIP_TOP_BOTTOM)
    img_data = np.array(image.getdata(), np.uint8)
    
    format = GL_RGBA if image.mode == 'RGBA' else GL_RGB
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, img_data)
    glGenerateMipmap(GL_TEXTURE_2D)
    
    return texture

def setup_vertex_data():
    vertices = np.array([
        -0.5, -0.5, 0.0,  0.0, 0.0,  # Bottom left
         0.5, -0.5, 0.0,  1.0, 0.0,  # Bottom right
         0.5,  0.5, 0.0,  1.0, 1.0,  # Top right
        -0.5, -0.5, 0.0,  0.0, 0.0,  # Bottom left
         0.5,  0.5, 0.0,  1.0, 1.0,  # Top right
        -0.5,  0.5, 0.0,  0.0, 1.0   # Top left
    ], dtype=np.float32)

    VBO = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, VBO)
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_STATIC_DRAW)

    VAO = glGenVertexArrays(1)
    glBindVertexArray(VAO)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * 4, None)
    glEnableVertexAttribArray(0)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * 4, ctypes.c_void_p(3 * 4))
    glEnableVertexAttribArray(1)

    return VAO

def compile_shader(source, shader_type):
    shader = glCreateShader(shader_type)
    glShaderSource(shader, source)
    glCompileShader(shader)
    if glGetShaderiv(shader, GL_COMPILE_STATUS) != GL_TRUE:
        raise RuntimeError(glGetShaderInfoLog(shader))
    return shader

def compile_shaders():
    vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER)
    fragment_shader = compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER)

    program = glCreateProgram()
    glAttachShader(program, vertex_shader)
    glAttachShader(program, fragment_shader)
    glLinkProgram(program)

    if glGetProgramiv(program, GL_LINK_STATUS) != GL_TRUE:
        raise RuntimeError(glGetProgramInfoLog(program))

    return program

def init():
    global VAO, shader_program, texture
    vertex_shader = compile_shader(vertex_shader_source, GL_VERTEX_SHADER)
    fragment_shader = compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER)
    shader_program = compile_shaders()

    # Load texture
    texture = load_texture("test.jpg")

    # Set up vertex data
    VAO = setup_vertex_data()

def main():
    if not glfw.init():
        raise Exception("GLFW cannot be initialized!")

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 3)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 3)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, GL_TRUE)
    window = glfw.create_window(800, 600, "OpenGL Window", None, None)

    if not window:
        glfw.terminate()
        raise Exception("GLFW window cannot be created!")

    glfw.make_context_current(window)
    init()
    # OpenGL context is now set up, rest of the code goes here

    while not glfw.window_should_close(window):
        glfw.poll_events()

        glClear(GL_COLOR_BUFFER_BIT)

        glUseProgram(shader_program)
        glBindTexture(GL_TEXTURE_2D, texture)
        glBindVertexArray(VAO)
        glDrawArrays(GL_TRIANGLES, 0, 6)

        glfw.swap_buffers(window)
    glfw.terminate()

if __name__ == "__main__":
    main()
