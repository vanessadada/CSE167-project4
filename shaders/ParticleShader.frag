
#version 330 core
in vec4 particleColor;

uniform float fixedIntensity;
uniform vec3 endColor;
uniform vec3 startColor;

out vec4 fragColor;

void main()
{
   fragColor = particleColor;
    fragColor = vec4(((1-fixedIntensity) * startColor),1.0) + vec4((fixedIntensity * endColor), 0.0);
}
