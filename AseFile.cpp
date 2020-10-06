#include "AseFile.h"


//OK
bool AseFile::OpenToRead()
{
	if(NULL == (input_fd = fopen(input_path, "r")))
		return FALSE;

	if(fseek(input_fd, 0L, SEEK_SET))
		return FALSE;

	if(fgetpos(input_fd, &pos))
		return FALSE;

	return TRUE;
}



bool AseFile::OpenToSave()
{
	if(NULL == (output_fd = fopen(output_path, "w")))
		return FALSE;

	if(fseek(output_fd, 0L, SEEK_SET))
		return FALSE;

	if(fgetpos(output_fd, &pos))
		return FALSE;

	return TRUE;
}


bool AseFile::CloseAfterRead()
{
	if(fclose(input_fd))
	{
		return FALSE;
	}

	return TRUE;
}


bool AseFile::CloseAfterSave()
{
	if(fclose(output_fd))
	{
		return FALSE;
	}

	return TRUE;
}

bool AseFile::GetInt(int& number)
{
	if(fscanf(input_fd, "%i", &number) != 1)
		return FALSE;

	return TRUE;
}

bool AseFile::GetUInt(unsigned int& number)
{
	if(fscanf(input_fd, "%i", &number) != 1)
		return FALSE;

	return TRUE;
}

bool AseFile::Get3UInt(UInt3& vector)
{
	if(fscanf(input_fd, "%i %i %i", &vector.Num[0], &vector.Num[1], &vector.Num[2]) != 3)
		return FALSE;

	return TRUE;
}

bool AseFile::GetF(GLfloat& number)
{
	if(fscanf(input_fd, "%f", &number) != 1)
		return FALSE;

	return TRUE;
}

bool AseFile::Get3F(Vector3& vector)
{
	if(fscanf(input_fd, "%f %f %f", &vector.x, &vector.y, &vector.z) != 3)
		return FALSE;

	return TRUE;
}

bool AseFile::GetStr(char * &str, bool tag)
{
	int i = 0;
	char c;

	if(fgetpos(input_fd, &pos))
		return FALSE;

	if(!tag)
	{
		do
		{
			fscanf(input_fd, "%c", &c);
			i++;
		}
		while((!feof(input_fd)) && (c != '\n'));
		i -= 2;
	}
	else
	{
		while((!feof(input_fd)) && ((c != '{') && (c != '\n')))
		{
			fscanf(input_fd, "%c", &c);
			i++;
		}
	}


	if(fsetpos(input_fd, &pos))
		return FALSE;

	if(!tag)
	{
		if(NULL == (str = (char*)malloc(i-1)))
			return FALSE;

		fscanf(input_fd, "%*c");
	}
	else
	{
		if(NULL == (str = (char*)malloc(i)))
			return FALSE;
	}


	if(fgets(str, i, input_fd) == NULL)
		return FALSE;

	return TRUE;
}



bool AseFile::SetUInt(unsigned int number)
{
	if(fprintf(output_fd, "%i\n", number) < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::Set3UInt(UInt3 vector)
{
	if(fprintf(output_fd, "%i %i %i\n", vector.Num[0], vector.Num[1], vector.Num[2]) < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::SetF(GLfloat number)
{
	if(fprintf(output_fd, "%f\n", number) < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::Set3F(Vector3 vector)
{
	if(fprintf(output_fd, "%f %f %f\n", vector.x, vector.y, vector.z) < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::SetStr(char* str)
{
	if(fputs(str, output_fd) < 0)
		return FALSE;

	if(fprintf(output_fd, "\n") < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::SetTAG(char* str)
{	
	if(fputs(str, output_fd) < 0)
		return FALSE;

	if(fprintf(output_fd, "=") < 1)
		return FALSE;

	return TRUE;
}


bool AseFile::SetStream(char* str, int id)
{		
	if(fputs(str, output_fd) < 0)
		return FALSE;

	if(id != -1)
	{
		if(fprintf(output_fd, "_%i", id) < 1)
			return FALSE;
	}


	return TRUE;
}

bool AseFile::SetEnterSreamToDAR()
{
	if(fprintf(output_fd, "<\n") < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::SetExitSreamToDAR()
{
	if(fprintf(output_fd, ">\n") < 1)
		return FALSE;

	return TRUE;
}

bool AseFile::SetNormalToDAR(Vector3 vector, VertexNormal vertexnormal)
{
	if(fprintf(output_fd, "%f %f %f	%f %f %f	%f %f %f	%f %f %f\n", 
		vector.x, vector.y, vector.z, 
		vertexnormal.Vertex[0].x, vertexnormal.Vertex[0].y, vertexnormal.Vertex[0].z, 
		vertexnormal.Vertex[1].x, vertexnormal.Vertex[1].y, vertexnormal.Vertex[1].z, 
		vertexnormal.Vertex[2].x, vertexnormal.Vertex[2].y, vertexnormal.Vertex[2].z) < 1)
	{
		return FALSE;
	}

	return TRUE;
}

int AseFile::CountTAG(char* str, bool pass)
{
	if((strlen(str)) < 2)
		return 0;

	char *tmp;
	if(NULL == (tmp = (char*)malloc(strlen(str)-4)))
		return -1;

	int count = 0;

	if(pass)
	{
		if(fseek(input_fd, 0L, SEEK_SET))
			return -1;
	}
	else
	{
		if(fgetpos(input_fd, &pos))
			return FALSE;
	}


	while(!feof(input_fd))
	{
		fscanf(input_fd, "%c", &tmp[0]);

		if(pass)
		{
			if(tmp[0] == str[0])
			{
				fgets(tmp+1, strlen(str), input_fd);

				if(!strcmp(tmp, str))
				{
					count++;
				}
			}
		}
		else
		{
			if(tmp[0] == '{')
			{
				if(!ExitStreamFromASE())
					return FALSE;
			}
			else if(tmp[0] == '}')
			{
				if(fsetpos(input_fd, &pos))
					return FALSE;
				
				return count;
			}
			else if(tmp[0] == str[0])
			{
				fgets(tmp+1, strlen(str), input_fd);

				if(!strcmp(tmp, str))
				{
					count++;
				}
			}
		}
	}

	if(pass)
	{
		if(fseek(input_fd, 0L, SEEK_SET))
			return -1;
	}
	else
	{
		if(fsetpos(input_fd, &pos))
			return FALSE;
	}

	return count;
}


bool AseFile::EnterStreamFromASE()
{
	char c;

	fscanf(input_fd, "%c", &c);
	if(c != '{')
		return FALSE;

	return TRUE;
}

bool AseFile::PosAfterTAG(char *str)
{
	char *tmp;
	if(NULL == (tmp = (char*)malloc(strlen(str)-4)))
		return FALSE;

	while(!feof(input_fd))
	{
		fscanf(input_fd, "%c", &tmp[0]);

		if(tmp[0] == '{')
		{
			if(!ExitStreamFromASE())
				return FALSE;
		}
		else if(tmp[0] == '}')
		{
			if(fgetpos(input_fd, &pos))
				return FALSE;

			pos -= 2;

			if(fsetpos(input_fd, &pos))
				return FALSE;

			return FALSE;
		}
		else if(tmp[0] == str[0])
		{
			fgets(tmp+1, strlen(str), input_fd);

			if(!strcmp(tmp, str))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}


bool AseFile::ExitStreamFromASE()
{
	int depth = 1;
	char c;

	while(!feof(input_fd))
	{
		fscanf(input_fd, "%c", &c);

		if(c == '{')
		{
			depth++;
		}
		else if(c == '}')
		{
			depth--;
		}

		if(!depth)
			return TRUE;
	}

	return FALSE;
}



bool AseFile::GetVertexFromASE(Vector3* &vector, unsigned int nb_vertex)
{
	unsigned int i;
	if(NULL == (vector = new Vector3[nb_vertex]))
		return FALSE;

	for(i = 0; i < nb_vertex; i++)
	{
		if(fscanf(input_fd, "			*MESH_VERTEX %*i	%f	%f	%f\n", &vector[i].x, &vector[i].y, &vector[i].z) != 3)
			return FALSE;
	}

	return TRUE;
}


bool AseFile::GetVertexFaceIDFromASE(UInt3* &uint, unsigned int nb_face)
{
	unsigned int i;
	char c;
	if(NULL == (uint = new UInt3[nb_face]))
		return FALSE;

	for(i = 0; i < nb_face; i++)
	{
		if(fscanf(input_fd, "			*MESH_FACE %*i: A: %i B: %i C: %i", &uint[i].Num[0], &uint[i].Num[1], &uint[i].Num[2]) != 3)
			return FALSE;

		do
		{
			fscanf(input_fd, "%c", &c);
		}while(c != '\n');
	}

	return TRUE;
}

bool AseFile::GetVertexMapCoordFromASE(Vector3* &vector, unsigned int nb_vertex_map_coord)
{
	unsigned int i;
	if(NULL == (vector = new Vector3[nb_vertex_map_coord]))
		return FALSE;

	for(i = 0; i < nb_vertex_map_coord; i++)
	{
		if(fscanf(input_fd, "			*MESH_TVERT %*i	%f	%f	%f\n", &vector[i].x, &vector[i].y, &vector[i].z) != 3)
			return FALSE;
	}

	return TRUE;
}

bool AseFile::GetFaceMapCoordIDFromASE(UInt3* &uint, unsigned int nb_face_map_coord)
{
	unsigned int i;
	if(NULL == (uint = new UInt3[nb_face_map_coord]))
		return FALSE;

	for(i = 0; i < nb_face_map_coord; i++)
	{
		if(fscanf(input_fd, "			*MESH_TFACE %*i	%i	%i	%i\n", &uint[i].Num[0], &uint[i].Num[1], &uint[i].Num[2]) != 3)
			return FALSE;
	}

	return TRUE;
}



bool AseFile::GetNormalFromASE(Vector3* &vector, VertexNormal* &vertexnormal, unsigned int nb_face)
{
	unsigned int i, j;

	if(NULL == (vector = new Vector3[nb_face]))
		return FALSE;

	if(NULL == (vertexnormal = new VertexNormal[nb_face]))
		return FALSE;

	for(i = 0; i < nb_face; i++)
	{
		if(fscanf(input_fd, "			*MESH_FACENORMAL %*i	%f	%f	%f\n", &vector[i].x, &vector[i].y, &vector[i].z) != 3)
			return FALSE;

		for(j = 0; j < 3; j++)
		{
			if(fscanf(input_fd, "				*MESH_VERTEXNORMAL %*i	%f	%f	%f\n", &vertexnormal[i].Vertex[j].x, &vertexnormal[i].Vertex[j].y, &vertexnormal[i].Vertex[j].z) != 3)
				return FALSE;
		}
	}

	return TRUE;
}



/*bool AseFile::GoStart()
{
	if(fseek(input_fd, 0L, SEEK_SET))
		return FALSE;

	if(fgetpos(input_fd, &pos))
		return FALSE;

	return TRUE;
}*/