#version 330 core
// This is a sample fragment shader.

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

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 normalOutput;
in vec3 posOutput;
in vec3 normalRaw;

uniform vec3 color;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
           float distant = length(light.position - posOutput);
           float attenuation = 1.0 / (light.linear * distant);
           
            vec3 ambient = (light.lightcolor) * material.ambient;
               ambient *= attenuation;
               
            vec3 norm = normalize(normalOutput);
            vec3 lightDir = normalize(light.position - posOutput);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = (light.lightcolor) * (diff * material.diffuse);
               diffuse *= attenuation;
            
            vec3 viewDir = normalize(viewPos - posOutput);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            vec3 specular = (light.lightcolor) * (spec * material.specular);
               specular *= attenuation;
        
            // Use the color passed in. An alpha of 1.0f means it is not transparent.
            vec3 result = (ambient + diffuse + specular) * color;
            fragColor = vec4((normalRaw + 1)/2, 1.0);
            fragColor = vec4(result, 1.0);
}
