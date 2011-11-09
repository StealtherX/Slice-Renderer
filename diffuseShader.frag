uniform sampler3D volume;
uniform sampler1D lookupTable;
uniform float sliceTrans;

const float cellSize = 1.0 / 1024.0;
vec3 LightPosition = vec3(0.3,0,0.1);


vec3 getNormal(vec3 at)
{
    vec3 n = vec3(texture3D(volume, at - vec3(cellSize, 0.0, 0.0)).x - texture3D(volume, at + vec3(cellSize, 0.0, 0.0)).x,
                  texture3D(volume, at - vec3(0.0, cellSize, 0.0)).y - texture3D(volume, at + vec3(0.0, cellSize, 0.0)).y,
                  texture3D(volume, at - vec3(0.0, 0.0, cellSize)).z - texture3D(volume, at + vec3(0.0, 0.0, cellSize)).z
                 );
    
    return normalize(n);
}

void main()
{
        const vec4 AmbientColor = vec4(0.05, 0.05, 0.05, 0.05);
	
        vec4 my_intensity = texture3D(volume, gl_TexCoord[0].xyz);
        vec4 my_colorlookup = texture1D(lookupTable, my_intensity.x);
	if(my_colorlookup.a == 0.0)
	{
		discard;
	}
       /* if (my_intensity.x < 0.375)
        {
            discard;
        }*/
        //else
         //       my_colorlookup.a *= 0.1;
	
	vec3 normalized_normal = getNormal(gl_TexCoord[0].xyz);
	vec3 lightVector = normalize(LightPosition - gl_TexCoord[0].xyz);
	
	float diffuseTerm = clamp(dot(normalized_normal, lightVector), 0.0, 1.0);
	
        gl_FragColor = AmbientColor +  my_colorlookup * diffuseTerm;
	
	
}
