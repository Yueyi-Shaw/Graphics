#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main(){
    vec2 st=gl_FragCoord.xy/u_resolution;
    //generate a basic wave
    float y=sin(st.x*20.+u_time)/3.+.5;
    //modify y
    y = ceil(y);
    if(abs(st.y-y)<.01){
        gl_FragColor=vec4(vec3(0.,1.,0.),1.);
        return;
    }
    gl_FragColor=vec4(vec3(0.,0.,0.),1.);
}