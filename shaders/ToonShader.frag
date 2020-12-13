#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    float linear;
    vec3 position;
    vec3 lightcolor;
};

in vec3 normalOutput;
in vec3 posOutput;
in vec3 normalRaw;

uniform vec3 color;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 fragColor;

void main()
{
    vec3 viewDir = normalize(viewPos - posOutput);
    float edge = max(0, dot(normalize(normalOutput), viewDir));
    
   if (edge < 0.5) {
        fragColor = vec4(vec3(0,0,0), 1);
    }
    else{
        float intensity;
        vec3 colorOut;
        
        vec3 norm = normalize(normalOutput);
        vec3 lightDir = normalize(light.position - posOutput);
        
        float diffuse = dot(lightDir,normalize(normalRaw));
        
        vec3 viewDir = normalize(viewPos - posOutput);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = (light.lightcolor) * (spec * material.specular);
        
        intensity = dot(light.position,normalize(normalRaw));
        
        if (intensity > 0.95)
            colorOut = vec3(1.0,1,1) * color ;
        else if (intensity > 0.5)
            colorOut = vec3(0.7,0.7,0.7) * color;
        else if (intensity > 0.05)
            colorOut = vec3(0.35,0.35,0.35) * color;
        else
            colorOut = vec3(0.1,0.1,0.1) * color;
        fragColor = vec4(colorOut, 1.0);
    }

}
