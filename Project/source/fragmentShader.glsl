#version 400 core

in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float lightIntensity;

vec3 colorA = vec3(0.149,0.141,0.912);

void main()
{
  

   vec4 AmbientColor = vec4(lightColor * lightIntensity, 1.0f);

    out_Color= texture(textureSampler, pass_textureCoords) * AmbientColor;
}