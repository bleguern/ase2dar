//ASE2DAR v1.0a by DaRoN



#include "ase2dar.h"
#include "List.h"
#include "Object.h"

int convert(char*, bool);
void info();


List<Object> list;


int main(int argc, char *argv[])
{
	bool infos = FALSE;
	int i;

	printf("<< ase2dar v1.0a by DaRoN >>\n");

	if(argc < 2)
	{
		info();
		exit(0);
	}
	else
	{
		if(strcmp(argv[1], "-i") == 0)
		{
			if(argc < 3)
			{
				info();
				exit(0);
			}
			infos = !infos;
			i = 2;
			printf("Info option activated.\n\n");
		}
		else
		{
			i = 1;
			printf("No option activated.\n\n");
		}

		while(i < argc)
		{
			printf("Converting file : %s...\n", argv[i]);

			switch(convert(argv[i], infos))
			{
			case 0:
				{
					printf("Converting successfull!\n\n");
					break;
				}
			case 1:
				{
					printf("File opening or reading error!\n\n");
					break;
				}
			case 2:
				{
					printf("File saving error!\n\n");
					break;
				}
			default:
				break;
			}

			i++;
		}
	}

	return 0;
}


int convert(char *path, bool infos)
{
	object_tmp = *new Object(path);

	if(!object_tmp.LoadFromASE())
		return 1;

	if(!object_tmp.SaveToDAR())
		return 2;

	list.Add(object_tmp);

	if(infos)
		object_tmp.Info();

	return 0;
}


void info()
{
	printf("ase2dar v1.0a\nSyntax : ase2dar.exe -option file_to_convert ...\n[option] :\ni : View informations during convertion.\n");
}