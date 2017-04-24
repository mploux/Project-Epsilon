#version 330
layout (triangles) in;
layout (line_strip, max_vertices = 18) out;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

in VS_OUT {
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
} gs_in[];

out vec3 color;

void draw_arrows(int index)
{
	color = vec3(0, 0, 1);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * (gl_in[index].gl_Position + vec4(gs_in[index].normal * 0.1, 0.0));
	EmitVertex();
	EndPrimitive();

	// color = vec3(1, 0, 0);
	// gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[index].gl_Position;
	// EmitVertex();
	// gl_Position = projectionMatrix * viewMatrix * modelMatrix * (gl_in[index].gl_Position + vec4(gs_in[index].tangent * 0.1, 0.0));
	// EmitVertex();
	// EndPrimitive();
	//
	// color = vec3(0, 1, 0);
	// gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[index].gl_Position;
	// EmitVertex();
	// gl_Position = projectionMatrix * viewMatrix * modelMatrix * (gl_in[index].gl_Position + vec4(gs_in[index].bitangent * 0.1, 0.0));
	// EmitVertex();
	// EndPrimitive();
	// color = vec3(1, 1, 1);
}

void main(void)
{
	draw_arrows(0);
	// draw_arrows(1);
	// draw_arrows(2);

	color = vec3(1, 0, 1);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}
