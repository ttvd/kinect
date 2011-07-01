uniform sampler2D tex;

void main()
{
	gl_FragColor = vec4(texture2D(tex, gl_TexCoord[0].xy).rgb, 1.0);

	//float r = (texture2D(tex, gl_TexCoord[0].xy)).r;
	//float g = (texture2D(tex, gl_TexCoord[0].xy)).g;
	//float b = (texture2D(tex, gl_TexCoord[0].xy)).b;

	//gl_FragColor = vec4(r, g, b, 1.0);
}
