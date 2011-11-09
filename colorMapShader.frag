uniform sampler3D volume;
uniform sampler1D lookupTable;
uniform float sliceTrans;

void main()
{
        vec4 my_intensity = texture3D(volume, gl_TexCoord[0].xyz);
        vec4 my_colorlookup = texture1D(lookupTable, my_intensity.x);
	if(my_colorlookup.a == 0.0)
	{
		discard;
	}
	else
	{
                my_colorlookup.a = sliceTrans * my_colorlookup.a;
		gl_FragColor = my_colorlookup;
	}
	
}
