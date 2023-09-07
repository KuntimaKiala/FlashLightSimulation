#version 330 core 

out vec4 FragColor;
in vec3 Color;  
in vec2 TexCoord ;
uniform vec2 mouse ;
uniform vec2 window; 
uniform sampler2D flashlightTexture;
uniform float flashlightRadius ;
void main()
{
    vec2 fragCoord = vec2(((window.x -gl_FragCoord.x)/window.x)*2.0f-1.0f  + mouse.x, ((window.y-gl_FragCoord.y)/window.y)*2.0f-1.0f + mouse.y);
    float dist = length(fragCoord);
    vec4 flashlightColor = texture(flashlightTexture, TexCoord);
    float intensity = smoothstep(flashlightRadius, 0.0, dist);
    FragColor = vec4(flashlightColor.r * intensity, flashlightColor.g * intensity, 0.0, flashlightColor.a*intensity);
}


        


