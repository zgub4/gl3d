#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texCoord;

out vec2 frag_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(in_position, 1.0f);
  frag_texCoord = vec2(in_texCoord.s, 1.0f - in_texCoord.t);
}
