#version 330 core

out vec4 FragColor;

in vec3 currPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


vec4 pointLight()
{
    // light intensity reduce in distance
    vec3 lightVec = lightPos - currPos;
    float dist = length(lightVec);
    float a = 0.05f;
    float b = 0.01f;
    float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);
    
    float ambient = 0.2f; // simulated environment light

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // using phong shading
    return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor; 
}

vec4 directionalLight()
{
    float ambient = 0.2f; // simulated environment light

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f)); // constant direction of light, constant intensity

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // using phong shading
    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{   
    // set cosine value of light cones
    float innerCone = 0.95f;
    float outerCone = 0.90f;
    
    float ambient = 0.2f; // simulated environment light

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - currPos);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // spot light also use constant light direction
    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    // within inner cone: always the hard light
    // from inner cone to outer cone: intensity reduces
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    // using phong shading
    return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor; 
}

void main()
{
    // final light color
    FragColor = directionalLight();
}
