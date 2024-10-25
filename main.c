#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "./src/headers/fileUtils.h"

#define MAX_FILES 255

void getFiles(char files[MAX_FILES][255], int *fileCount);

int main()
{
    char title[255], files[MAX_FILES][255], isEpisodeInput[10];
    int fileCount = 0, isEpisode = 0;

    getFiles(files, &fileCount);

    printf("=== Rename All Files In This Folder and Sort by ASC ===\n");
    printf("Input Title: ");
    scanf(" %[^\n]s", title);

    while (1)
    {
        printf("Flag Episode (if this videos and want adding name episode after title) | Enter 'y' for Yes or 'n' for No: ");
        scanf("%9s", isEpisodeInput);

        char firstChar = tolower(isEpisodeInput[0]);

        if (firstChar == 'y')
        {
            isEpisode = 1;
            break;
        }
        else if (firstChar == 'n')
        {
            isEpisode = 0;
            break;
        }
        else
        {
            printf("Invalid input. Please enter 'y' for Yes or 'n' for No.\n");
        }
    }

    clearOutputDirectory("output");
    copyAllFiles(files, fileCount, title, isEpisode);

    printf("Press Enter to exit...");
    getchar();
    getchar();

    return 0;
}

void getFiles(char files[MAX_FILES][255], int *fileCount)
{
    DIR *dir;
    struct dirent *entry;
    char *dirPath = ".";

    if ((dir = opendir(dirPath)) == NULL)
    {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            if (strcmp(entry->d_name, "main.c") != 0 &&
                strcmp(entry->d_name, "Makefile") != 0 &&
                !strstr(entry->d_name, ".o") &&
                !strstr(entry->d_name, ".exe") &&
                !strstr(entry->d_name, ".c") &&
                !strstr(entry->d_name, ".h") &&
                !strstr(entry->d_name, ".md") &&
                entry->d_name[0] != '.')
            {
                strcpy(files[*fileCount], entry->d_name);
                (*fileCount)++;
            }
        }
    }
    closedir(dir);
}