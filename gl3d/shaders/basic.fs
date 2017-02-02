#version 330 core

//uniform vec4 uni_color;
in vec3 frag_color;
in vec2 frag_texCoord;

out vec4 color;

uniform sampler2D tex;

void main() {
  color = texture(tex, frag_texCoord);
}
