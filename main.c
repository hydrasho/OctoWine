#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#define OCTOWINELIB "/opt/octowineLIB/" // chemin pour la liste des prefix

char **getPrefix(char *url_to_octolib, int *nbr);
void octowine_help();

int main(int argc, char *argv[])
{
	char winelink[] = "/usr/bin/wine";
	char octolib[] = OCTOWINELIB;
	char *prefix;
	int i = 0;
	int nbr = 0;
	char **listePrefix;

	if(argc == 1)
		octowine_help();
	if(argc >= 2)
	{
		//command with argument --liste, --etc...
		if(argv[1][0] == '-')
		{
			if(strcmp(argv[1], "--liste") == 0 || strcmp(argv[1], "-l") == 0)
			{
				listePrefix = getPrefix(OCTOWINELIB, &nbr);
				printf("||| %d prefix: |||\n", nbr);
				while(i < nbr){
					printf("- %s\n", listePrefix[i]);
					i++;
				}
			}
			if(strcmp(argv[1], "--gui") == 0 || strcmp(argv[1], "-g") == 0)
			{
				printf("lancement de octowine-GUI");
				execl("/usr/bin", "octowine-gui", argv[2], NULL);
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
			prefix = strcat(octolib, argv[1]);
			setenv("WINEDEBUG", "-all", 0);
			setenv("WINEPREFIX", prefix, 0);
			if(argv[i][0] == '-')//verifie si c'est une commande sur prefix
			{

				if(strcmp(argv[i], "--play") == 0 || strcmp(argv[i], "-p") == 0)
				{
					i++;
					printf("ouverture de %s", prefix);

					return (0);
				}
				if(strcmp(argv[i], "--winetricks") == 0 || strcmp(argv[i], "-w") == 0)
				{
					printf("lancement de winetricks");
					i++;
					if(argc == 4)
					{
						printf("HERE i = %d\n\n\n", i);
						execl("/usr/bin/winetricks", "winetricks", argv[i], NULL);
					}
					else
						execl("/usr/bin/winetricks", "winetricks", NULL);
					return (0);
				}
				if(strcmp(argv[i], "--winecfg") == 0 || strcmp(argv[i], "-W") == 0)
				{
					printf("lancement de winecfg");
					execl("/usr/bin/winecfg", "winecfg", NULL);
					return (0);
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
					if(strcmp(argv[i], "+G") == 0 || strcmp(argv[i], "+g") == 0)
					{
						printf("Ajouts de gamemode\n");
						setenv("LD_PRELOAD", "/usr/lib/libgamemodeauto.so", 0);
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
				printf("%d=i  et %d=argc\n", i, argc);
				if (argc > i +1)
				{
					//printf("yaura des argu\n", i, argc);
					execl(winelink, "wine", argv[i] ,argv[i+1], NULL);
					return (0);
				}
				execl(winelink, "wine", argv[i] ,argv[i+1], NULL);
				return (0);
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

char **getPrefix(char *url_to_octolib, int *nbr){
	char **liste = malloc(sizeof(char) * 250);
	int i = 0;
	char *str;
	struct dirent* file = NULL;
	DIR *directory = NULL;
	directory = opendir(url_to_octolib);
	if (directory == NULL)
	{
		perror("");
		return NULL;
	}
	while((file = readdir(directory)) != NULL)
	{
		
		if(strcmp(file->d_name, "..") == 0 || strcmp(file->d_name, ".") == 0)
			continue;
		str = file->d_name;
		liste[i] = str;
		i++;
	}
	liste[i] = NULL;
	
	*nbr = i;
	closedir(directory);
	return liste;
}
