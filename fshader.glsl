#version 120

varying vec4 color;
varying vec2 texCoord;
varying vec4 N, L, V;
varying float distance;

uniform sampler2D texture;
uniform int use_texture;
//uniform float shininess;

vec4 ambient, diffuse, specular;

void main()
{
	vec4 the_color = color;
	
	if (use_texture == 1)
	{
		the_color = texture2D(texture, texCoord);
	}
	
	vec4 NN = normalize(N);
	vec4 VV = normalize(V);
	vec4 LL = normalize(L);
	ambient = the_color * 0.2;
	vec4 H = normalize(LL + VV); 
	diffuse = max(dot(LL, NN), 0.0) * 1.0 * the_color;
	specular = pow(max(dot(NN, H), 0.0), 450) * vec4(1.0, 1.0, 1.0, 1.0);
	gl_FragColor = ambient + diffuse + specular;
	//gl_FragColor = the_color;
}
