#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

#define Length.01

float plot(vec2 st,float pct){
    return smoothstep(pct-Length,pct,st.y)-
    smoothstep(pct,pct+Length,st.y);
}

float linear(vec2 st,float pct){
    return clamp((st.y-pct+Length)/Length,0.,1.)
    -clamp((st.y-pct)/Length,0.,1.);
}

void main(){
    // Hermite interpolation
    vec2 st=gl_FragCoord.xy/u_resolution;

    float y=smoothstep(.1,.9,st.x);

    vec3 basecolor=vec3(y);
    float pct=plot(st,y);
    vec3 color1=(1.-pct)*basecolor+pct*vec3(1.,0.,0.);

    float y2=clamp((st.x-.1)/.8,0.,1.);
    if(abs(st.y-y2)<0.005){
        gl_FragColor=vec4(vec3(0.,1.,0.),1.);
        return;
    }
    gl_FragColor=vec4(color1,1.);
}