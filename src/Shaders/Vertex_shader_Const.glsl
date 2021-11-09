#version 330
layout(location=0) in vec4 vp;
layout(location=1) in vec4 vc;
layout(location=2) in vec2 tmp_uv;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec4 my_Colour;
out vec2 uv;
void main () {
     gl_Position = projectionMatrix * viewMatrix * modelMatrix *  vp;
     my_Colour = vc;
     uv = tmp_uv;
};