#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 normal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 proj, view, model;
uniform float time;

void main() {
   gl_Position = proj * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
   FragPos = (model * vec4(pos, 1.0)).xyz;
   mat3 normalMatrix = transpose(inverse(mat3(model)));
   Normal = normalMatrix * normal;
   FragPos = FragPos;
}
