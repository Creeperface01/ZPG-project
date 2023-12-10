#version 330

#define MAX_LIGHTS 32

struct light {
    vec3 position;
    vec3 color;
    float intensity;
};

struct directionalLight {
    vec3 position;
    vec3 color;
    float intensity;
    vec3 direction;
};

struct spotlight {
    vec3 position;
    vec3 color;
    float intensity;
    vec3 direction;
    float cutOff;
    float outerCutOff;
};

uniform vec3 viewPos;

uniform uint lightsSize;
uniform light lights[MAX_LIGHTS];

uniform uint spotlightsSize;
uniform spotlight spotlights[MAX_LIGHTS];

uniform uint directionalLightsSize;
uniform directionalLight directionalLights[MAX_LIGHTS];

uniform sampler2D textureUnitID;
uniform bool hasTexture;

uniform vec3 color;

out vec4 frag_colour;

in vec3 fragPos;
in vec3 normal;
in vec2 uv;

const vec3 ambientLight = vec3(0.1, 0.1, 0.1);

float calculateDiffuseLight(light lightData) {
    vec3 lightDir = normalize(lightData.position - fragPos);
    float diff = max(dot(lightDir, normalize(normal)), 0.0);

    return diff;
}

float calculateSpecularLight(light lightData) {
    vec3 lightDir = normalize(lightData.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(normal));

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    return 0.5 * spec;
}

vec3 calculateLight(light lightData) {
    return (calculateDiffuseLight(lightData) + calculateSpecularLight(lightData)) * lightData.intensity * lightData.color;
}

vec3 calculateSpotlight(spotlight lightData) {
    vec3 lightDir = normalize(lightData.position - fragPos);
    float theta = dot(lightDir, normalize(-lightData.direction));

    float epsilon   = lightData.cutOff - lightData.outerCutOff;
    float intensity = clamp((theta - lightData.outerCutOff) / epsilon, 0.0, 1.0);

    light data = light(lightData.position, lightData.color, lightData.intensity);

    float diffuse = calculateDiffuseLight(data);
    float specular = calculateSpecularLight(data);

    return (diffuse + specular) * intensity * lightData.intensity * lightData.color;
}

vec3 calculateDirectionalLight(directionalLight lightData) {
    vec3 lightDir = normalize(-lightData.direction);

    float diff = max(dot(lightDir, normalize(normal)), 0.0);

    return diff * lightData.intensity * lightData.color;
}

void main () {
    vec4 objectColor = vec4(color, 1);

    if (hasTexture) {
        objectColor = texture(textureUnitID, uv);
    }

    vec3 result = ambientLight;

    for (uint i = 0u; i < lightsSize; i++) {
        result += calculateLight(lights[i]);
    }

    for (uint i = 0u; i < spotlightsSize; i++) {
        result += calculateSpotlight(spotlights[i]);
    }

    for (uint i = 0u; i < directionalLightsSize; i++) {
        result += calculateDirectionalLight(directionalLights[i]);
    }

    frag_colour = vec4(result, 1) * objectColor;
}