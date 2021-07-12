
void main()
{
	vec2 st = gl_FragCoord.xy/iResolution.xy;
	float s = 1.0;
	gl_FragColor = vec4(s,s,s,1.0);
}