
void main()
{
	vec2 st = gl_FragCoord.xy/iResolution.xy;
	gl_FragColor = vec4(st.x,st.y,cos(iTime),1.0);
    gl_FragColor = vec4(1.0, 0.0, 0.0, 0.1);
}