#version 120

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;
attribute vec4 vNormal;

varying vec2 texCoord;
varying vec4 color;
varying vec4 N;
varying vec4 L;
varying vec4 V;
varying float distance;

uniform mat4 ctm;
uniform mat4 model_view;
uniform mat4 projection;
//uniform mat4 orthop;
uniform vec4 light_position;

void main()
{
	texCoord = vTexCoord;
	color = vColor;
	gl_Position = projection * model_view * ctm * vPosition;
	N = normalize(model_view * ctm * vNormal);
	vec4 L_temp = model_view * (light_position - ctm * vPosition);
	L = normalize(L_temp);
	vec4 eye_point = vec4(0.0, 0.0, 0.0, 1.0);
	V = normalize(eye_point - (model_view * ctm * vPosition));
	distance = length(L_temp);
}
