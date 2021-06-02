
void main()
{
	vec2 st = gl_FragCoord.xy/iResolution.xy;
	gl_FragColor = vec4(0.9,1.0 - st.y,st.x,1.0);
}