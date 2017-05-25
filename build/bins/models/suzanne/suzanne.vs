#version 330 core

layout (location=0) in vec3 position;

out vec4 vertexColor;

uniform mat4 proj, view, model;

void main() {
   gl_Position = proj * view * model * vec4(position, 1.0);
   //gl_Position = vec4(position, 1.0);
   vertexColor = vec4(0.5, 0, 0, 1.0);
}

// projection = glm::perspective(fov, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);
