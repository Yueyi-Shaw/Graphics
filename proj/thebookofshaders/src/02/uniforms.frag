#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;// Canvas size (width,height)
uniform vec2 u_mouse;// mouse position in screen pixels
uniform float u_time;// Time in seconds since load#ifdef GL_ES

void main(){
    vec2 st=gl_FragCoord.xy/u_resolution;

    gl_FragColor=vec4(u_mouse/u_resolution,st.x,abs(sin(u_time)));
}