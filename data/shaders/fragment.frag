#version 120

uniform vec4 Color;

varying vec3 frag_pos;
varying vec3 normals_frag;

uniform vec3 light_pos;

void main()
{
	vec3 norm = normalize(normals_frag);
	vec3 lightDir = normalize(light_pos - frag_pos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1,1,1);
	vec3 ambient = vec3(0.1,0.1,0.1);
	vec3 result = (ambient + diffuse) * vec3(Color.x, Color.y, Color.z);
	
	gl_FragColor = vec4(result, Color.w);
}
