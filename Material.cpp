#include "Material.h"

bool Material::LoadDefault()
{
	if(NULL == (name = (char*)malloc(strlen("Default"))))
		return FALSE;

	strcpy(name, "Default");

	if(NULL == (type = (char*)malloc(strlen("Standard"))))
		return FALSE;

	strcpy(type, "Standard");
	
	return shader.LoadDefault();
}



bool Material::LoadFromASE(AseFile file)
{
	unsigned int i;
	int nb_map;

	if(((nb_map = file.CountTAG(MATERIAL_NB_MAP, FALSE)) < 0) ||
		!file.PosAfterTAG(MATERIAL_NAME) || !file.GetStr(name, FALSE) ||
		!file.PosAfterTAG(MATERIAL_TYPE) || !file.GetStr(type, FALSE) ||
		!shader.LoadFromASE(file))
	{
		return false;
	}

	if(nb_map)
	{
		for(i = 0; i < (unsigned int)nb_map; i++)
		{
			char *tmp_1, *tmp_2;
			
			if(!file.PosAfterTAG(MATERIAL_MAP) || !file.GetStr(tmp_1, TRUE))
				return FALSE;

			if(NULL == (tmp_2 = (char*)malloc(strlen(MATERIAL_MAP)+strlen(tmp_1)+1)))
				return FALSE;

			strcpy(tmp_2, MATERIAL_MAP);
			strcat(tmp_2, tmp_1);

			if(!file.EnterStreamFromASE())
				return FALSE;

				map_tmp = *new Map(tmp_1);

				if(map_tmp.LoadFromASE(file))
					map.Add(map_tmp);

			if(!file.ExitStreamFromASE())
				return FALSE;
		}
	}

	return TRUE;
}


bool Material::SaveToDAR(AseFile file)
{
	unsigned int i;

	if(!file.SetTAG("name") || !file.SetStr(name) ||
		!file.SetTAG("type") || !file.SetStr(type) ||
		!file.SetStream("shader", -1) || !file.SetEnterSreamToDAR() ||
		!shader.SaveToDAR(file) || !file.SetExitSreamToDAR())
	{
		return false;
	}

	if(map.GetNbNode())
	{
		for(i = 0; i < map.GetNbNode(); i++)
		{
			if(!file.SetStream("map", i) || !file.SetEnterSreamToDAR() ||
				!map[i].SaveToDAR(file) || !file.SetExitSreamToDAR())
			{
				return false;
			}
		}
	}

	return TRUE;
}


void Material::Info()
{
	printf("nb map : %i\n", map.GetNbNode());
}

