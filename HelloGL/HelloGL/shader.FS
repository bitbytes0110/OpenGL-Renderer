#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D WoodTexture;
uniform sampler2D FaceTexture;

uniform float mixValue;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
	//FragColor = texture(FaceTexture, TexCoord);
	//FragColor = texture(WoodTexture, TexCoord) * vec4(ourColor, 1.0f);

	FragColor = mix(texture(WoodTexture, TexCoord), texture(FaceTexture, vec2(-TexCoord.x,TexCoord.y)) ,mixValue)*vec4(ourColor, 1.0f);

}