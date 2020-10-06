#include "Object.h"


bool Object::LoadFromASE()
{
	if(!file.OpenToRead())
	{
		return FALSE;
	}

	unsigned int i, nb_material;
	int nb_mesh, nb_light;

	//NB_MESH
	if((nb_mesh = file.CountTAG(OBJECT_MESH, TRUE)) < 0)
		return FALSE;

	if((nb_light = file.CountTAG(OBJECT_LIGHT, TRUE)) < 0)
		return FALSE;

	//OBJECT
	if(!file.PosAfterTAG(OBJECT) || !file.EnterStreamFromASE())
		return FALSE;

		//OJECT_NAME
		if(!file.PosAfterTAG(OBJECT_NAME) || !file.GetStr(name, FALSE))
			return FALSE;
	
	if(!file.ExitStreamFromASE())
		return FALSE;

	//MATERIAL
	if(!file.PosAfterTAG(OBJECT_MATERIAL_LIST) || !file.EnterStreamFromASE())
		return FALSE;

		//NB_MATERIAL
		if(!file.PosAfterTAG(OBJECT_NB_MATERIAL) || !file.GetUInt(nb_material))
			return FALSE;

		if(!nb_material && nb_mesh)
		{
			material_tmp = *new Material();
			
			if(!material_tmp.LoadDefault())
				return FALSE;
			
			material.Add(material_tmp);
		}
		else
		{
			for(i = 0; i < nb_material; i++)
			{
				char *tmp, id[3];
				if(NULL == (tmp = (char*)malloc(strlen(OBJECT_MATERIAL)+3)))
					return FALSE;

				strcpy(tmp, OBJECT_MATERIAL);
				sprintf(id, "%i ", i);
				strcat(tmp, id);
					
				if(!file.PosAfterTAG(tmp) || !file.EnterStreamFromASE())
					return FALSE;

					material_tmp = *new Material();

					if(material_tmp.LoadFromASE(file))
						material.Add(material_tmp);

				if(!file.ExitStreamFromASE())
					return FALSE;
			}
		}

	if(!file.ExitStreamFromASE())
		return FALSE;

	if(nb_mesh)
	{
		/*if(!file.GoStart())
			return FALSE;*/

		for(i = 0; i < (unsigned int)nb_mesh; i++)
		{
			//MESH
			if(!file.PosAfterTAG(OBJECT_MESH) || !file.EnterStreamFromASE())
				return FALSE;

				mesh_tmp = *new Mesh();

				if(mesh_tmp.LoadFromASE(file))
					mesh.Add(mesh_tmp);

			if(!file.ExitStreamFromASE())
				return FALSE;
		}
	}

	if(nb_light)
	{
		if(nb_light > MAX_OPENGL_LIGHTS)
			nb_light = MAX_OPENGL_LIGHTS;

		/*if(!file.GoStart())
			return FALSE;*/

		for(i = 0; i < (unsigned int)nb_light; i++)
		{
			//MESH
			if(!file.PosAfterTAG(OBJECT_LIGHT) || !file.EnterStreamFromASE())
				return FALSE;

				light_tmp = *new Light();

				if(light_tmp.LoadFromASE(file))
					light.Add(light_tmp);

			if(!file.ExitStreamFromASE())
				return FALSE;
		}
	}

	return file.CloseAfterRead();
}



bool Object::SaveToDAR()
{
	unsigned int i;

	if(!file.OpenToSave())
	{
		return FALSE;
	}

	if(!file.SetStr(DAR_FILE_VERSION_TAG))
		return FALSE;

	if(strlen(name))
	{
		if(!file.SetTAG("name") || !file.SetStr(name))
			return FALSE;
	}

	if(material.GetNbNode())
	{
		for(i = 0; i < material.GetNbNode(); i++)
		{
			if(!file.SetStream("material", i) || !file.SetEnterSreamToDAR())
				return FALSE;

			if(!material[i].SaveToDAR(file))
				return FALSE;

			if(!file.SetExitSreamToDAR())
				return FALSE;
		}
	}

	if(mesh.GetNbNode())
	{
		for(i = 0; i < mesh.GetNbNode(); i++)
		{
			if(!file.SetStream("mesh", i) || !file.SetEnterSreamToDAR())
				return FALSE;

			if(!mesh[i].SaveToDAR(file))
				return FALSE;

			if(!file.SetExitSreamToDAR())
				return FALSE;
		}
	}

	if(light.GetNbNode())
	{
		for(i = 0; i < light.GetNbNode(); i++)
		{
			if(!file.SetStream("light", i) || !file.SetEnterSreamToDAR())
				return FALSE;

			if(!light[i].SaveToDAR(file))
				return FALSE;

			if(!file.SetExitSreamToDAR())
				return FALSE;
		}
	}

	return file.CloseAfterSave();
}



void Object::Info()
{
	unsigned int i;

	printf("Object Info :\nnb material : %i\n", material.GetNbNode());

	if(material.GetNbNode())
	{
		for(i = 0; i < material.GetNbNode(); i++)
		{
			printf(" - Material %i : ", i);
			material[i].Info();
		}
	}

	printf("nb mesh : %i\nnb light : %i\n", mesh.GetNbNode(), light.GetNbNode());
}
