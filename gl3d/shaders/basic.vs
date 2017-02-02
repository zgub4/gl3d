#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_texCoord;

out vec3 frag_color;
out vec2 frag_texCoord;

uniform mat4 transform;

void main() {
  gl_Position = transform * vec4(in_position, 1.0f);
  frag_color = in_color;
  frag_texCoord = vec2(in_texCoord.s, 1.0f - in_texCoord.t);
}
