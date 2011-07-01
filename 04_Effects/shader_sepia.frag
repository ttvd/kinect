uniform sampler2D tex;

void main()
{
	vec3 color = texture2D(tex, gl_TexCoord[0].xy).rgb;
	gl_FragColor = vec4(dot(color, vec3(0.393, 0.769, 0.189)), dot(color, vec3(0.349, 0.686, 0.168)), dot(color, vec3(0.272, 0.534, 0.131)), 1.0);
}
