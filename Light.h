#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "3DMath.h"
#include "AseFile.h"


#define MAX_OPENGL_LIGHTS            8

class Light
{
	char* name;                      //NODE_NAME #

	char* type;                      //LIGHT_TYPE # (NULL)
	
	Vector3 position;                //TM_POS # # # (0.0f, 0.0f, 0.0f)

	Vector3 color;                   //LIGHT_COLOR # # # (1.0f, 1.0f, 1.0f)
	
	GLfloat intensity;               //LIGHT_INTENS # (1.0f)
	
	//Not in use for the moment
	char* att_type;                  //(NULL)
	GLfloat att_power;               //(0.0f)
	
	Vector3 direction;               //TM_POS # # # (0.0f, 0.0f, 0.0f)
	
	GLfloat cut_off;                 //LIGHT_HOTSPOT # (0.0f)

	char* shadows;                   //LIGHT_SHADOWS # (NULL)

public:

	Light():name(NULL),type(NULL),color(1.0f, 1.0f, 1.0f),
		position(0.0f, 0.0f, 0.0f),intensity(1.0f),att_type(NULL),att_power(0.0f),
		direction(0.0f, 0.0f, 0.0f),cut_off(0.0f),shadows(NULL) {}
	~Light() {}

	bool LoadFromASE(AseFile);
	bool SaveToDAR(AseFile);
};

static Light light_tmp;


#endif