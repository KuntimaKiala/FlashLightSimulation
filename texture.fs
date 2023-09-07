#version 330 core 

out vec4 FragColor;
in vec3 Color;  
in vec2 TexCoord ;
 uniform vec2 mouse ;
uniform sampler2D flashlightTexture;
void main()
{
    vec2 fragCoord = vec2(((500.0f -gl_FragCoord.x)/500.0f)*2.0f-1.0f  + mouse.x, ((500.0f-gl_FragCoord.y)/500.0f)*2.0f-1.0f + mouse.y);
    float dist = length(fragCoord);
    vec4 flashlightColor = texture(flashlightTexture, TexCoord);
    float intensity = smoothstep(0.25, 0.0, dist);
    

    vec3 baseColor = vec3(1.0, 0.0, 0.0); // Red color
    //FragColor = vec4(flashlightColor.rgb * intensity , flashlightColor.a);
    FragColor = vec4(flashlightColor.r * intensity, flashlightColor.g * intensity, 0.0, 1.0);
}


        


