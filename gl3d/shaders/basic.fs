#version 330 core

in vec2 frag_texCoord;

out vec4 color;

uniform sampler2D tex;
uniform float lightning;

void main()
{
  color = texture(tex, frag_texCoord);
}
