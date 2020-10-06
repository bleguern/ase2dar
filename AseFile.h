#ifndef _ASEFILE_H_
#define _ASEFILE_H_

#include "3DMath.h"

//ASE FILE CONSTANT

//FOR OBJECT
#define OBJECT                      "*SCENE "
#define OBJECT_NAME                 "*SCENE_FILENAME "
#define OBJECT_NB_FRAME             "*SCENE_LASTFRAME "
#define OBJECT_NB_MESH              "*GEOMOBJECT "
#define OBJECT_NB_LIGHT             "*LIGHTOBJECT "
#define OBJECT_NB_MATERIAL          "*MATERIAL_COUNT "
#define OBJECT_MESH                 "*GEOMOBJECT "
#define OBJECT_LIGHT                "*LIGHTOBJECT "
#define OBJECT_MATERIAL             "*MATERIAL "
#define OBJECT_MATERIAL_LIST        "*MATERIAL_LIST "


//FOR MESH
#define MESH                        "*MESH "
#define MESH_NAME                   "*NODE_NAME "
#define MESH_NB_VERTEX              "*MESH_NUMVERTEX "
#define MESH_NB_VERTEX_MAP_COORD    "*MESH_NUMTVERTEX "
#define MESH_NB_FACE                "*MESH_NUMFACES "
#define MESH_NB_FACE_MAP_COORD      "*MESH_NUMTVFACES "
#define MESH_VERTEX                 "*MESH_VERTEX "
#define MESH_VERTEX_LIST            "*MESH_VERTEX_LIST "
#define MESH_VERTEX_MAP_COORD       "*MESH_TVERT "
#define MESH_VERTEX_MAP_COORD_LIST  "*MESH_TVERTLIST " 
#define MESH_VERTEX_NORMAL          "*MESH_VERTEXNORMAL "
#define MESH_FACE                   "*MESH_FACE "
#define MESH_FACE_LIST              "*MESH_FACE_LIST "
#define MESH_FACE_MAP_COORD         "*MESH_TFACE "
#define MESH_FACE_MAP_COORD_LIST    "*MESH_TFACELIST " 
#define	MESH_FACE_NORMAL            "*MESH_FACENORMAL "
#define MESH_MATERIAL_ID            "*MATERIAL_REF "
#define MESH_NORMALS                "*MESH_NORMALS "


//FOR MATERIAL
#define MATERIAL_TYPE               "*MATERIAL_CLASS "
#define MATERIAL_NAME               "*MATERIAL_NAME "
#define MATERIAL_NB_MAP             "*MAP_"
#define MATERIAL_MAP                "*MAP_"


//FOR SHADER
#define SHADER_AMBIENT              "*MATERIAL_AMBIENT "
#define SHADER_DIFFUSE              "*MATERIAL_DIFFUSE "
#define SHADER_SPECULAR             "*MATERIAL_SPECULAR "
#define SHADER_SHINE                "*MATERIAL_SHINE "
#define SHADER_SHINE_STRENGTH       "*MATERIAL_SHINESTRENGTH "
#define SHADER_TRANSPARENCY         "*MATERIAL_TRANSPARENCY "
#define SHADER_TYPE                 "*MATERIAL_SHADING "




//FOR MAP
#define MAP_NAME                    "*MAP_NAME "
#define MAP_TYPE                    "*MAP_"
#define MAP_FILE_PATH               "*BITMAP "
#define MAP_AMOUNT                  "*MAP_AMOUNT "
#define MAP_U_OFFSET                "*UVW_U_OFFSET "
#define MAP_V_OFFSET                "*UVW_V_OFFSET "
#define MAP_U_TILING                "*UVW_U_TILING "
#define MAP_V_TILING                "*UVW_V_TILING "
#define MAP_BLUR                    "*UVW_BLUR "


//FOR LIGHTS
#define LIGHT_NAME                  "*NODE_NAME "
#define LIGHT_TYPE                  "*LIGHT_TYPE "
#define LIGHT_SHADOWS               "*LIGHT_SHADOWS "
#define LIGHT_NODE                  "*NODE_TM "
#define LIGHT_POS                   "*TM_POS "
#define LIGHT_DIRECTION             "*TM_POS "
#define LIGHT_SETTINGS              "*LIGHT_SETTINGS "
#define LIGHT_COLOR                 "*LIGHT_COLOR "
#define LIGHT_INTENSITY             "*LIGHT_INTENS "
#define LIGHT_CUTOFF                "*LIGHT_HOTSPOT "


class AseFile
{
	FILE *input_fd;
	FILE *output_fd;
	char *input_path;
	char *output_path;
	fpos_t pos;

public:
	AseFile():input_fd(NULL),output_fd(NULL),input_path(NULL),output_path(NULL),pos(0) {}
	AseFile(char *file_path):input_fd(NULL),output_fd(NULL),input_path(NULL),output_path(NULL),pos(0)
	{
		input_path = (char*)malloc(strlen(file_path)-4);
		input_path = file_path;
		output_path = (char*)malloc(strlen(file_path)-8);		
		strncpy(output_path, file_path, strlen(file_path)-4);
		strcat(output_path, ".dar");
	}
	~AseFile() {}

	//NEW!!!
	bool OpenToRead();
	bool OpenToSave();
	bool CloseAfterRead();
	bool CloseAfterSave();

	//bool GoStart();

	bool PosAfterTAG(char*);
	int CountTAG(char*, bool);

	bool GetInt(int&);
	bool GetUInt(unsigned int&);
	bool Get3UInt(UInt3&);
	bool GetF(GLfloat&);
	bool Get3F(Vector3&);
	bool GetStr(char*&, bool);

	bool EnterStreamFromASE();
	bool ExitStreamFromASE();

	bool GetVertexFromASE(Vector3*&, unsigned int);
	bool GetVertexMapCoordFromASE(Vector3*&, unsigned int);
	bool GetVertexFaceIDFromASE(UInt3*&, unsigned int);
	bool GetFaceMapCoordIDFromASE(UInt3*&, unsigned int);
	bool GetNormalFromASE(Vector3*&, VertexNormal*&, unsigned int);


	bool SetUInt(unsigned int);
	bool Set3UInt(UInt3);
	bool SetF(GLfloat);
	bool Set3F(Vector3);
	bool SetStr(char*);
	bool SetTAG(char*);
	bool SetStream(char*, int);

	bool SetEnterSreamToDAR();
	bool SetExitSreamToDAR();
	bool SetNormalToDAR(Vector3, VertexNormal);

};


#endif