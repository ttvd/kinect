uniform sampler2D tex;

uniform float step_width;
uniform float step_height;

void main()
{
	float luma = dot(texture2D(tex, gl_TexCoord[0].xy).rgb, vec3(0.3, 0.59, 0.11));
	gl_FragColor = vec4(luma, luma, luma, 1.0);

	vec3 luma_coeff = vec3(0.3, 0.59, 0.11);

	float a2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, -1.0 * step_height)).rgb, luma_coeff);
	float c2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, -1.0 * step_height)).rgb, luma_coeff);
	float f2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, 1.0 * step_height)).rgb, luma_coeff);
	float h2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, 1.0 * step_height)).rgb, luma_coeff);

	float b2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, -1.0 * step_height)).rgb, luma_coeff);
	float e2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, 0.0 * step_height)).rgb, luma_coeff);
	float g2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, 1.0 * step_height)).rgb, luma_coeff);
	float d2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, 0.0 * step_height)).rgb, luma_coeff);

	float x2 = dot(texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, 0.0 * step_height)).rgb, luma_coeff);

	float intensity = 0.125 * abs(a2 - x2) + 0.25 * abs(b2 - x2) + 0.125 * abs(c2 - x2) + 0.25 * abs(d2 - x2) +	0.25 * abs(e2 - x2) + 0.125 * abs(f2 - x2) + 0.25 * abs(g2 - x2) + 0.125 * abs(h2 - x2);

	if(intensity * 255.0 < 10.0)
	{
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else
	{
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
