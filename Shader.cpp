#include "Shader.h"


bool Shader::LoadDefault()
{
	if(NULL == (type = (char*)malloc(strlen("Blinn"))))
		return FALSE;

	strcpy(type, "Blinn");

	return TRUE;
}

bool Shader::LoadFromASE(AseFile file)
{
	if(!file.PosAfterTAG(SHADER_AMBIENT) || !file.Get3F(ambient))
		return FALSE;

	if(!file.PosAfterTAG(SHADER_DIFFUSE) || !file.Get3F(diffuse))
		return FALSE;

	if(!file.PosAfterTAG(SHADER_SPECULAR) || !file.Get3F(specular))
		return FALSE;

	if(!file.PosAfterTAG(SHADER_SHINE) || !file.GetF(shine))
		return FALSE;

	if(!file.PosAfterTAG(SHADER_SHINE_STRENGTH) || !file.GetF(shine_strength))
		return FALSE;

	if(!file.PosAfterTAG(SHADER_TRANSPARENCY) || !file.GetF(transparency))
		return FALSE;

	if(!file.PosAfterTAG(SHADER_TYPE) || !file.GetStr(type, TRUE))
		return FALSE;

	return TRUE;
}


bool Shader::SaveToDAR(AseFile file)
{
	if(!file.SetTAG("type") || !file.SetStr(type))
		return FALSE;

	if(!file.SetTAG("ambient") || !file.Set3F(ambient))
		return FALSE;

	if(!file.SetTAG("diffuse") || !file.Set3F(diffuse))
		return FALSE;

	if(!file.SetTAG("specular") || !file.Set3F(specular))
		return FALSE;

	if(!file.SetTAG("transparency") || !file.SetF(transparency))
		return FALSE;

	if(!file.SetTAG("shine_strength") || !file.SetF(shine_strength))
		return FALSE;

	if(!file.SetTAG("shine") || !file.SetF(shine))
		return FALSE;


	return TRUE;
}
