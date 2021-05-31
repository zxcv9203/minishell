#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	DIR *dir_info;
	struct dirent *dir_entry;
	char home[1024];

	strncpy(home, getenv("HOME"), sizeof(home));
	if ((dir_info = opendir(home)) == NULL)
	{
		printf("ERROR : opendir failed\n");
		return (0);
	}
	while ((dir_entry = readdir(dir_info)) != NULL)
		printf("%s\n", dir_entry->d_name);
	closedir(dir_info);
}
