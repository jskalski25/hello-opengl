#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const float vertices[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
};

const char *vertex_source = 
"#version 330 core\n"
"in vec2 aPos;"
"void main() {"
    "gl_Position = vec4(aPos, 0.0f, 1.0f);"
"}";

const char *fragment_source =
"#version 330 core\n"
"out vec4 fragColor;"
"void main() {"
    "fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);"
"}";

int main(void) {
    const int screen_width = 800;
    const int screen_height = 600;

    if (!glfwInit()) {
        return -1; 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    std::cout << glGetString(GL_VERSION) << "\n";

    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLuint pos_location;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
    glCompileShader(vertex_shader);

    GLint status = GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cerr << "error compiling vertex shader\n";
        glfwTerminate();
        return -1;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cerr << "error compiling vertex shader\n";
        glfwTerminate();
        return -1;
    }

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    pos_location = glGetAttribLocation(program, "aPos");
    glEnableVertexAttribArray(pos_location);
    glVertexAttribPointer(pos_location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    glViewport(0, 0, screen_width, screen_height);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}