#version 450 core

uniform float u_time;
uniform vec2 u_resolution;

out vec4 FragColor;

void main() {
    float t = u_time;
    vec2 r = u_resolution;
    vec3 c;
    float l, z = t;
    for (int i = 0; i < 3; i++) {
        vec2 uv, p = gl_FragCoord.xy / r;
        uv = p;
        p -= 0.5;
        p.x *= r.x / r.y;
        z += 0.07;
        l = length(p);
        uv += p / l * (sin(z) + 1.0) * abs(sin(l * 9.0 - z - z));
        c[i] = 0.01 / length(mod(uv, 1.0) - 0.5);
    }
    FragColor = vec4(c/l, t);
}