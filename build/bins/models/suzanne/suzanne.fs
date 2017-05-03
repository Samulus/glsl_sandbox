#version 330 core

layout (location=0) out vec3 gPosition;
layout (location=1) out vec3 gNormal;
layout (location=2) out vec4 gColor;

in vec3 FragPos;
in vec3 Normal;

uniform float time;

void main() {
   gPosition = FragPos;
   gNormal   = normalize(Normal);
   gColor    = vec4(0, 0.1, 0, 1); // why is 'gNormal' in FQ.fs set to this value
}
