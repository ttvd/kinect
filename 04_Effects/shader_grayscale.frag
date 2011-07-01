uniform sampler2D tex;

void main()
{
	float luma = dot(texture2D(tex, gl_TexCoord[0].xy).rgb, vec3(0.3, 0.59, 0.11));
	gl_FragColor = vec4(luma, luma, luma, 1.0);
}
