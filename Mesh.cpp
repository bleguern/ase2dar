#include "Mesh.h"



bool Mesh::LoadFromASE(AseFile file)
{
	if(!file.PosAfterTAG(MESH_NAME) || !file.GetStr(name, FALSE) ||
		!file.PosAfterTAG(MESH) || !file.EnterStreamFromASE() ||
		!file.PosAfterTAG(MESH_NB_VERTEX) || !file.GetUInt(nb_vertex) ||
		!nb_vertex ||
		!file.PosAfterTAG(MESH_NB_FACE) || !file.GetUInt(nb_face) ||
		!nb_face ||
		!file.PosAfterTAG(MESH_VERTEX_LIST) || !file.EnterStreamFromASE() ||
		!file.GetVertexFromASE(vertex, nb_vertex) || !file.ExitStreamFromASE() ||
		!file.PosAfterTAG(MESH_FACE_LIST) || !file.EnterStreamFromASE() ||
		!file.GetVertexFaceIDFromASE(face_vertex_id, nb_face) || !file.ExitStreamFromASE() ||
		!file.PosAfterTAG(MESH_NB_VERTEX_MAP_COORD) || !file.GetUInt(nb_vertex_map_coord))
	{
		return false;
	}

	if(nb_vertex_map_coord)
	{
		//VERTEX_MAP_COORD
		if(!file.PosAfterTAG(MESH_VERTEX_MAP_COORD_LIST) || !file.EnterStreamFromASE() ||
			!file.GetVertexMapCoordFromASE(vertex_map_coord, nb_vertex_map_coord) || !file.ExitStreamFromASE() ||
			!file.PosAfterTAG(MESH_NB_FACE_MAP_COORD) || !file.GetUInt(nb_face_map_coord) ||
			!nb_face_map_coord ||
			!file.PosAfterTAG(MESH_FACE_MAP_COORD_LIST) || !file.EnterStreamFromASE() ||
			!file.GetFaceMapCoordIDFromASE(face_map_coord_id, nb_face_map_coord) || !file.ExitStreamFromASE())
		{
				return false;
		}
	}


	//NORMAL
	if(!file.PosAfterTAG(MESH_NORMALS) || !file.EnterStreamFromASE() ||
		!file.GetNormalFromASE(face_normal, vertex_normal, nb_face) || !file.ExitStreamFromASE() ||
		!file.ExitStreamFromASE())
	{
		return false;
	}

	//MATERIAL ID
	if(file.PosAfterTAG(MESH_MATERIAL_ID))
	{
		if(!file.GetInt(id_material))
			return false;
	}
	else
	{
		id_material = 0;
	}

	return true;
}


bool Mesh::SaveToDAR(AseFile file)
{
	unsigned int i;

	if(!file.SetTAG("name") || !file.SetStr(name) ||
		!file.SetTAG("weight") || !file.SetF(weight) ||
		!file.SetTAG("nb_vertex") || !file.SetUInt(nb_vertex) ||
		!file.SetTAG("nb_vertex_map_coord") || !file.SetUInt(nb_vertex_map_coord) ||
		!file.SetTAG("nb_face") || !file.SetUInt(nb_face) ||
		!file.SetTAG("nb_face_map_coord") || !file.SetUInt(nb_face_map_coord) ||
		!file.SetTAG("id_material") || !file.SetUInt((unsigned int)id_material) ||
		!file.SetStream("vertex", -1) || !file.SetEnterSreamToDAR())
	{
		return false;
	}

	for(i = 0; i < nb_vertex; i++)
	{
		if(!file.Set3F(vertex[i]))
			return false;
	}

	if(!file.SetExitSreamToDAR())
		return false;

	if(nb_vertex_map_coord)
	{
		if(!file.SetStream("vertex_map_coord", -1) || !file.SetEnterSreamToDAR())
			return false;

			for(i = 0; i < nb_vertex_map_coord; i++)
			{
				if(!file.Set3F(vertex_map_coord[i]))
					return false;
			}

		if(!file.SetExitSreamToDAR())
			return false;
	}

	if(!file.SetStream("face", -1) || !file.SetEnterSreamToDAR())
		return false;

		for(i = 0; i < nb_face; i++)
		{
			if(!file.Set3UInt(face_vertex_id[i]))
				return false;
		}

	if(!file.SetExitSreamToDAR())
		return false;

	if(nb_face_map_coord)
	{
		if(!file.SetStream("face_map_coord", -1) || !file.SetEnterSreamToDAR())
			return false;

			for(i = 0; i < nb_face_map_coord; i++)
			{
				if(!file.Set3UInt(face_map_coord_id[i]))
					return false;
			}

		if(!file.SetExitSreamToDAR())
			return false;
	}

	if(!file.SetStream("normal", -1) || !file.SetEnterSreamToDAR())
		return false;

		for(i = 0; i < nb_face; i++)
		{
			if(!file.SetNormalToDAR(face_normal[i], vertex_normal[i]))
				return false;
		}

	if(!file.SetExitSreamToDAR())
		return false;

	return true;
}
