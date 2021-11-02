#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform vec3 lightPos;
out vec4 out_Color;
void main(void)
{
vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);
vec3 baseColor = vec3(1.0f, 0.7f, 0.05f);
vec3 lightVector = normalize(lightPos - ex_worldPosition.xyz);
float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);
vec3 diffuse = dot_product * vec3( 1.0f, 1.0f, 1.0f);
vec3 ambient = vec3( 0.1, 0.1, 0.1);
out_Color = vec4(baseColor, 1.f) * (vec4(ambient, 1.f)
        +   vec4(diffuse, 1.f)); 
}