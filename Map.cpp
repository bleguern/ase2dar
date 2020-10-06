#include "Map.h"



bool Map::LoadFromASE(AseFile file)
{
	if(!file.PosAfterTAG(MAP_NAME) || !file.GetStr(name, FALSE) ||
		!file.PosAfterTAG(MAP_AMOUNT) || !file.GetF(amount) ||
		!file.PosAfterTAG(MAP_FILE_PATH) || !file.GetStr(file_path, FALSE))
	{
		return false;
	}

	if(NULL == (file_type = (char*)malloc(3)))
		return false;

	strcpy(file_type, file_path+(strlen(file_path)-3));

	if(!UpFileType())
		return false;

	if(!file.PosAfterTAG(MAP_U_OFFSET) || !file.GetF(u_offset) ||
		!file.PosAfterTAG(MAP_V_OFFSET) || !file.GetF(v_offset) ||
		!file.PosAfterTAG(MAP_U_TILING) || !file.GetF(u_tiling) ||
		!file.PosAfterTAG(MAP_V_TILING) || !file.GetF(v_tiling) ||
		!file.PosAfterTAG(MAP_BLUR) || !file.GetF(blur))
	{
		return false;
	}

	return true;
}

bool Map::SaveToDAR(AseFile file)
{
	if(!file.SetTAG("name") || !file.SetStr(name) ||
		!file.SetTAG("file_type") || !file.SetStr(file_type) ||
		!file.SetTAG("file_path") || !file.SetStr(file_path) ||
		!file.SetTAG("type") || !file.SetStr(type) ||
		!file.SetTAG("amount") || !file.SetF(amount) ||
		!file.SetTAG("u_offset") || !file.SetF(u_offset) ||
		!file.SetTAG("v_offset") || !file.SetF(v_offset) ||
		!file.SetTAG("u_tiling") || !file.SetF(u_tiling) ||
		!file.SetTAG("v_tiling") || !file.SetF(v_tiling) ||
		!file.SetTAG("blur") || !file.SetF(blur))
	{
		return false;
	}

	return true;
}


bool Map::UpFileType()
{
	int i;
	if(strlen(file_type) != 3)
		return false;

	for(i = 0; i < 3; i++)
	{
		if(((unsigned int)type[i] > 96) && ((unsigned int)type[i] < 123))
			type[i] -= 32;
	}

	return true;
}