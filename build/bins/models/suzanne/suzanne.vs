#version 330 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;

out vec4 vertexColor;

uniform mat4 proj, view, model;

mat4 other = mat4(1);

void main() {
   gl_Position = proj * view * model * vec4(position, 1.0);
   vertexColor = vec4(position, 1.0);
}
