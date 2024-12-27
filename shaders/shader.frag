#version 460

out vec4 color;

uniform vec3 L_direction;
uniform vec3 viewPos;
uniform vec3 col;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;
//get a checker board pattern on object surface
uniform bool checkered;
uniform float divs;
float checkered_fn();
// draw a line grid on the surface of an object
uniform bool subDivide;
uniform float lineDivs;
float line_fn();
// returns a fraction of the far value depending on the distance from the camera
float blend(float far);
//calculates directional light
vec3 directional_light();
// point light system
#define MAX_POINT_LIGHTS 20
uniform struct pointLight {
    vec3 position;
    vec3 color;
} pointLights[MAX_POINT_LIGHTS];
uniform int availablePointLights;
vec3 calcPointLight(pointLight light);
// beginning of main function
void main() {
    vec3 result = vec3(0.0);

    result += directional_light();

    if (checkered) {
        if (checkered_fn() == 0)
            result *= 0.5;
    }

    if (subDivide) {
        if (line_fn() == 0)
            result *= 0.3;
    }

    float attenuation = pow(blend(600.0), 2.0);
    result = mix(result, vec3(0.2), attenuation);

    color = vec4(result, 1.0);
    //color = vec4(1.0, 0.58, 0.1, 0.0);
}
float checkered_fn() {
    float squareDivs = 2.0 / divs;
    vec2 sec = step(vec2(0.5), fract(texCoords / squareDivs));
    return int(sec.x + sec.y) % 2;
}
float line_fn() {
    float _step = 1.0 / lineDivs;
    vec2 b = step(vec2(0.005), fract(texCoords / _step));
    vec2 t = step(vec2(0.005), 1.0 - fract(texCoords / _step));

    return b.x * b.y * t.x * t.y;
}
float blend(float far) {
    float dist = clamp(length(viewPos - fragPos), 0.0, far);
    return dist / far;
}
vec3 directional_light() {
    vec3 result = vec3(0.0);
    vec3 ambient = vec3(0.1) * col;
    result += ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-L_direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * col;
    result += diffuse;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwaydir = normalize(lightDir + viewDir);
    // vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(norm, halfwaydir), 0.0), 32.0);
    vec3 specular = spec * col;
    result += specular;

    return result;
}
vec3 calcPointLight(pointLight light) {
    vec3 result = vec3(0.0);

    vec3 ambient = vec3(0.2) * col * light.color;
    result += ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * col * light.color;
    result += diffuse;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwaydir = normalize(lightDir + viewDir);
    // vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(norm, halfwaydir), 0.0), 16.0);
    vec3 specular = spec * col * light.color;
    result += specular;

    return result;
}
