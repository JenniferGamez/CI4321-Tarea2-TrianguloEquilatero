#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

// Codigo fuente de Vertex Shader y Fragment Shader
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos; // Posición del vértice
layout(location = 1) in vec3 aColor; // Color del vértice
out vec3 vertexColor; // Color a pasar al fragment shader
void main() {
    gl_Position = vec4(aPos, 1.0); // Definir posición
    vertexColor = aColor; // Pasar color
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor; // Recibir color del vertex shader
out vec4 FragColor; // Color de salida
void main() {
    FragColor = vec4(vertexColor, 1.0); // Establecer color final
}
)";

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Inicializar GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triángulo Equilátero con OpenGL usando C++", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Inicializar GLEW
    glewInit();

    // Compilar shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Parametros del triangulo equilatero
    float sideLength = 1.0f; // Longitud del lado
    float height = (sideLength * (sqrt(3) / 2)); // Altura del triángulo

    // Vertices del triangulo (x, y, z) centrado
    GLfloat vertices[] = {
        0.0f, height / 2, 0.0f,                 // Vértice superior
        -sideLength / 2, -height / 2, 0.0f,     // Vértice inferior izquierdo
        sideLength / 2, -height / 2, 0.0f       // Vértice inferior derecho
    };

    // Colores para cada vertice, normalizado
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,  // Rojo (ff0000) para el vertice superior
        0.0f, 1.0f, 0.0f,  // Verde (00ff00) para el vertice inferior izquierdo
        0.0f, 0.0f, 1.0f   // Azul (0000ff) para el vertice inferior derecho
    };

    // Crear VBOs y VAO
    GLuint VBO[2], VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO);

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colores
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Desvincular VAO
    glBindVertexArray(0);

    // Valor Hexadecimal (#1b1e2b) a RGB - FONDO
    // Rojo (R): 1b en hexadecimal = 27 en decimal = 27 / 255.0 = 0.1059
    // Verde (G): 1e en hexadecimal = 30 en decimal = 30 / 255.0 = 0.1176
    // Azul (B): 2b en hexadecimal = 43 en decimal = 43 / 255.0 = 0.1686

    // Establecer el color de fondo a #1b1e2b
    glClearColor(0.1059f, 0.1176f, 0.1686f, 1.0f);

    // Bucle de renderizado
    while (!glfwWindowShouldClose(window)) {
  
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        
        // Dibujar triangulo
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Intercambiar buffers y sondear eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpiar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
