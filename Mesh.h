#ifndef _MESH_H_
#define _MESH_H_

#include "3DMath.h"
#include "AseFile.h"

class Mesh
{
	char* name;                              //NODE_NAME # (NULL)
	
	Vector3* vertex;                         //MESH_VERTEX # # # # (* = nb_vertex) (NULL)
	Vector3* vertex_map_coord;               //MESH_TVERT # # # # (* = nb_vertex_map_coord) (NULL)
	VertexNormal* vertex_normal;             //MESH_VERTEXNORMAL # # # # (* = nb_face) (NULL)
	
	UInt3* face_vertex_id;                   //MESH_FACE # A: # B: # C: # (* = nb_face) (NULL)
	UInt3* face_map_coord_id;                //MESH_TFACE # # # # (* = nb_face_map_coord) (NULL)
	Vector3* face_normal;                    //MESH_FACENORMAL # # # # (* = nb_face) (NULL)

	unsigned int nb_vertex;                  //MESH_NUMVERTEX # (0)
	unsigned int nb_vertex_map_coord;        //MESH_NUMTVERTEX # (0)
	
	unsigned int nb_face;                    //MESH_NUMFACES # (0)
	unsigned int nb_face_map_coord;          //MESH_NUMTVFACES # (0)
	
	int id_material;                         //MATERIAL_REF # (-1)
	
	GLfloat weight;                          //(0.0f)

public:
	Mesh():name(NULL),vertex(NULL),vertex_map_coord(NULL),vertex_normal(NULL),face_vertex_id(NULL),face_map_coord_id(NULL),face_normal(NULL),
		nb_vertex(0),nb_vertex_map_coord(0),nb_face(0),nb_face_map_coord(0),id_material(-1),weight(0.0f) {}
	~Mesh() {}

	bool LoadFromASE(AseFile);
	bool SaveToDAR(AseFile);
};

static Mesh mesh_tmp;

#endif