#ifndef _MAP_H_
#define _MAP_H_

#include "AseFile.h"



class Map
{
	char* name;                //MAP_NAME (NULL)
	
	char* file_type;           //(NULL)
	
	char* file_path;           //BITMAP # (NULL)

	char* type;                //MAP_# (NULL)
	
	GLfloat amount;            //MAP_AMOUNT # (1.0f)

	GLfloat u_offset;          //UVW_U_OFFSET # (0.0f)
	GLfloat v_offset;          //UVW_V_OFFSET # (0.0f)
	GLfloat u_tiling;          //UVW_U_TILING # (1.0f)
	GLfloat v_tiling;          //UVW_V_TILING # (1.0f)
	GLfloat blur;              //UVW_BLUR # (1.0f)

public:
	Map():name(NULL),file_type(NULL),file_path(NULL),type(NULL),
		amount(1.0f),u_offset(0.0f),v_offset(0.0f),
		u_tiling(1.0f),v_tiling(1.0f),blur(1.0f) {}
	Map(char *str):name(NULL),file_type(NULL),file_path(NULL),type(NULL),
		amount(1.0f),u_offset(0.0f),v_offset(0.0f),
		u_tiling(1.0f),v_tiling(1.0f),blur(1.0f)
	{
		type = (char*)malloc(strlen(str));
		strcpy(type, str);
	}
	~Map() {}

	bool LoadFromASE(AseFile);
	bool SaveToDAR(AseFile);
	bool UpFileType();
};

static Map map_tmp;

#endif