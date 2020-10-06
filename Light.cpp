#include "Light.h"


bool Light::LoadFromASE(AseFile file)
{
	if(!file.PosAfterTAG(LIGHT_NAME) || !file.GetStr(name, FALSE) ||
		!file.PosAfterTAG(LIGHT_TYPE) || !file.GetStr(type, TRUE) ||
		!file.PosAfterTAG(LIGHT_NODE) || !file.EnterStreamFromASE() ||
		!file.PosAfterTAG(LIGHT_POS) || !file.Get3F(position) ||
		!file.ExitStreamFromASE())
	{
		return false;
	}


	if(!strcmp(type, "Target"))
	{
		if(!file.PosAfterTAG(LIGHT_NODE) || !file.EnterStreamFromASE() ||
			!file.PosAfterTAG(LIGHT_DIRECTION) || !file.Get3F(direction) ||
			!file.ExitStreamFromASE())
		{
			return false;
		}
	}

	if(!file.PosAfterTAG(LIGHT_SHADOWS) || !file.GetStr(shadows, TRUE) ||
		!file.PosAfterTAG(LIGHT_SETTINGS) || !file.EnterStreamFromASE() ||
		!file.PosAfterTAG(LIGHT_COLOR) || !file.Get3F(color) ||
		!file.PosAfterTAG(LIGHT_INTENSITY) || !file.GetF(intensity))
	{
		return false;
	}

	if(!strcmp(type, "Target"))
	{
		if(!file.PosAfterTAG(LIGHT_CUTOFF) || !file.GetF(cut_off))
			return false;
	}

	if(!file.ExitStreamFromASE())
		return false;

	return TRUE;
}

bool Light::SaveToDAR(AseFile file)
{
	if(!file.SetTAG("name") || !file.SetStr(name) ||
		!file.SetTAG("type") || !file.SetStr(type) ||
		!file.SetTAG("shadows") || !file.SetStr(shadows) ||
		!file.SetTAG("position") || !file.Set3F(position) ||
		!file.SetTAG("color") || !file.Set3F(color) ||
		!file.SetTAG("intensity") || !file.SetF(intensity))
	{
		return false;
	}

	if(!strcmp(type, "Target"))
	{
		if(!file.SetTAG("direction") || !file.Set3F(direction) ||
			!file.SetTAG("cut_off") || !file.SetF(cut_off))
		{
			return false;
		}
	}

	return true;
}