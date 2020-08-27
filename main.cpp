#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OCTOWINELIB "/opt/octowineLIB/"

void octowine_help();

int main(int argc, char *argv[])
{
	char octolib[] = OCTOWINELIB;
	int i;
	if(argc == 1)
		octowine_help();
	if(argc >= 2)
	{
		//command with argument --liste, --etc...
		if(argv[1][0] == '-')
		{
			if(strcmp(argv[1], "--liste") == 0 || strcmp(argv[1], "-l") == 0)
			{
				printf("liste des prefix:");
			}
		}
		//end of command with argument
		else
		{
				if(argc < 3)
				{
					octowine_help();
					return 0;
				}
				i = 2;
				//DEBUG printf("%s", strcat(octolib, argv[1]));
				setenv("WINEDEBUG", "-all", 0);
				setenv("WINEPREFIX", strcat(octolib, argv[1]), 0);
				if(argv[i][0] == '-')//verifie si c'est une commande sur prefix
				{
					if(strcmp(argv[i], "--winetricks") == 0 || strcmp(argv[i], "-w") == 0)
					{
						printf("lancement de winetricks");
						i++;
						if(argc == 4)
						{
							execl("/usr/bin/winetricks", "winetricks", argv[i], NULL);
						}
						else
							execl("/usr/bin/winetricks", "winetricks", NULL);
					}
					if(strcmp(argv[i], "--winecfg") == 0 || strcmp(argv[i], "-W") == 0)
					{
						printf("lancement de winecfg");
						execl("/usr/bin/winecfg", "winecfg", NULL);
					}
					return (0);//au cas où
				}
				else //si c'est un executable et recherche doption
				{
					while(argv[i][0] == '+')
					{
						if(strcmp(argv[i], "+E") == 0 || strcmp(argv[i], "+e") == 0)
						{
							printf("Ajouts du ESYNC\n");
							setenv("WINEESYNC", "1", 0);
							i++;
							if(argc == i)
								break;
							continue;
						}
						if(strcmp(argv[i], "+F") == 0 || strcmp(argv[i], "+e") == 0)
						{
							printf("Ajouts du FSYNC\n");
							setenv("WINEFSYNC", "1", 0);
							i++;
							if(argc == i)
								break;
							continue;
						}
						if(strcmp(argv[i], "+N") == 0 || strcmp(argv[i], "+n") == 0)
						{
							printf("Ajouts du Debug\n");
							setenv("WINEDEBUG", "+all", 0);
							i++;
							if(argc == i)
								break;
							continue;
						}
					}
					//argv pour lexecutable
					if(argc == i)
					{
						printf("tu compte executer aucun executable ? comme tu veux !");
						return (0);
					}
					printf("%s\n", argv[i]);

				}


		}
	}
	return (0);
}

void octowine_help()
{
	printf(" ===================== Octowine ===================== \n");
	printf(" octowine <namePrefix> <file.exe> <arg>               \n");
	printf(" You can add +E for add ESYNC and +N for add DEBUG    \n");
	printf(" octowine --liste | for your list on prefix     \n");
	printf(" octowine <nameprefix> -R | for remove prefix     \n");
	printf(" octowine <nameprefix> -w [<arg>] | for execute winetricks     \n");
	printf(" octowine <nameprefix> -W | for execute wineCFG     \n");
	printf(" ==================================================== \n");
}
	/*execl("/usr/bin/wine", "wine", "/opt/digordie/DigOrDie.exe", "NULL");*/
