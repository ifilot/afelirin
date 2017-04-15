#version 330 core

in  vec3 position0;
in  vec2 uv0;
in  vec3 position_worldspace;
in  vec3 eye_cameraspace;
in  vec3 lightdirection_cameraspace;
in  vec3 normal_cameraspace;

out vec4 fragColor;

uniform sampler2D tex;

void main() {
    // color
    vec4 color = texture(tex, uv0);

    // light source
    vec3 l = normalize(lightdirection_cameraspace);

    // normal
    vec3 n = normalize(normal_cameraspace);

    // eye position
    vec3 e = normalize(eye_cameraspace);
    vec3 r = reflect(-l, n);

    // calculate diffuse
    float cosTheta = clamp(dot(n, l), 0, 1);

    // calculate reflection
    float cosAlpha = clamp(dot(e,r), 0, 1);

    vec3 light_color = vec3(1,1,1);
    float lightpower = 1.5f;

    float z = clamp((position0.z + 5.0f) / 10.0, 0, 1);

    vec3 environment_light = vec3(1,1,1);
    vec3 ambient = vec3(color);
    vec3 diffuse = vec3(color) * lightpower * cosTheta;
    vec3 specular = vec3(1,1,1) * light_color * lightpower * pow(cosAlpha, 5);

    fragColor = vec4(0.3 * environment_light +
                     0.1 * ambient +
                     0.4 * diffuse +
                     0.2 * specular, 1.0);
}
