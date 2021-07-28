#version 120

attribute vec3 vertices;
attribute vec3 normals;
attribute vec2 uvs;

varying vec3 frag_pos;
varying vec3 normals_frag;

uniform mat4 model;
uniform mat4 VP;

void main()
{
	frag_pos = vec3(model * vec4(vertices, 1.0));
	normals_frag = normals;
	
	gl_Position = (VP * model) * vec4(vertices, 1.0);
}
