#version 330
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
out vec3 ex_worldNormal;
out vec4 ex_worldPosition;
void main () {
     gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(in_Position,1.0f);
     ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
     ex_worldNormal = normalMatrix * in_Normal;
};