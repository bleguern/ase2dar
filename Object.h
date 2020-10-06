#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "AseFile.h"
#include "Mesh.h"
#include "Material.h"
#include "Light.h"

class Object
{
	char* name;                      //SCENE_FILENAME # (NULL)

	AseFile file;
	
	List<Mesh> mesh;                 //GEOMOBJECT (NULL)
	List<Material> material;         //MATERIAL # (NULL)
	List<Light> light;               //LIGHTOBJECT (NULL)
	
	//unsigned int id_frame;         //(0)
	//unsigned int nb_frame;         //SCENE_LASTFRAME # (1)

	unsigned int nb_face;            //(0)

	GLfloat weight;                  //(0.0f)

public:
	Object():name(NULL),file(),mesh(),material(),light(),/*id_frame(0),nb_frame(1),*/nb_face(0),weight(0.0f) {}
	Object(char *object_path):name(NULL),file(object_path),mesh(),material(),light(),/*id_frame(0),nb_frame(1),*/nb_face(0),weight(0.0f) {}
	~Object() {}

	bool LoadFromASE();
	bool SaveToDAR();

	void Info();
};


static Object object_tmp;

#endif