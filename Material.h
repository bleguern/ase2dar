#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "3DMath.h"
#include "Shader.h"
#include "List.h"
#include "Map.h"
#include "AseFile.h"

class Material
{

	char* name;                      //MATERIAL_NAME # (NULL)
	char* type;                      //MATERIAL_CLASS # (NULL)
	
	Shader shader;
	
	List<Map> map;                        //MAP_# (NULL)

public:
	Material():name(NULL),type(NULL),shader(),map() {}
	~Material() {}

	bool LoadDefault();

	bool LoadFromASE(AseFile);
	bool SaveToDAR(AseFile);

	void Info();
};

static Material material_tmp;


#endif