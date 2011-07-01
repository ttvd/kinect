uniform sampler2D tex;

uniform float step_width;
uniform float step_height;

void main()
{
	vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);

	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-2.0 * step_width, -2.0 * step_height)) * 1.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, -2.0 * step_height)) * 4.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, -2.0 * step_height)) * 7.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, -2.0 * step_height)) * 4.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(2.0 * step_width, -2.0 * step_height)) * 1.0;

	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-2.0 * step_width, -1.0 * step_height)) * 4.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, -1.0 * step_height)) * 16.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, -1.0 * step_height)) * 26.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, -1.0 * step_height)) * 16.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(2.0 * step_width, -1.0 * step_height)) * 4.0;

	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-2.0 * step_width, 0.0 * step_height)) * 7.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, 0.0 * step_height)) * 26.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, 0.0 * step_height)) * 41.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, 0.0 * step_height)) * 26.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(2.0 * step_width, 0.0 * step_height)) * 7.0;

	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-2.0 * step_width, 1.0 * step_height)) * 4.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, 1.0 * step_height)) * 16.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, 1.0 * step_height)) * 26.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, 1.0 * step_height)) * 16.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(2.0 * step_width, 1.0 * step_height)) * 4.0;

	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-2.0 * step_width, 2.0 * step_height)) * 1.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(-1.0 * step_width, 2.0 * step_height)) * 4.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(0.0 * step_width, 2.0 * step_height)) * 7.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(1.0 * step_width, 2.0 * step_height)) * 4.0;
	sum += texture2D(tex, gl_TexCoord[0].xy + vec2(2.0 * step_width, 2.0 * step_height)) * 1.0;

	sum = sum / 273.0;
	gl_FragColor = vec4(sum.rgb, 1.0);
}
