#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include "../headers/fileUtils.h"

const char *getFileExtension(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    return (dot && dot != filename) ? dot : "";
}

void clearOutputDirectory(const char *outputDir)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(outputDir)) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG)
            {
                char filePath[512];
                snprintf(filePath, sizeof(filePath), "%s/%s", outputDir, entry->d_name);
                remove(filePath);
            }
        }
        closedir(dir);
    }
    else
    {

#ifdef _WIN32
        _mkdir(outputDir);
#else
        mkdir(outputDir, 0777);
#endif
    }
}

void copyFile(const char *source, const char *destination)
{
    char buffer[1024];
    FILE *src = fopen(source, "rb");
    FILE *dest = fopen(destination, "wb");

    if (src == NULL || dest == NULL)
    {
        perror("Error opening file");
        return;
    }

    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, 1, n, dest);
    }

    fclose(src);
    fclose(dest);
}

void copyAllFiles(char files[][255], int fileCount, const char *title, int isEpisode)
{

    char destination[512];
    for (int i = 0; i < fileCount; i++)
    {
        char num[12];

        const char *extension = getFileExtension(files[i]);

        snprintf(destination, sizeof(destination), "output/%s", title);
        sprintf(num, "%d", i + 1);

        if (isEpisode)
            strcat(destination, " Episode ");

        strcat(destination, num);

        if (i == fileCount - 1)
            strcat(destination, " End");

        strcat(destination, extension);

        copyFile(files[i], destination);
        printf("Copied: %s to %s\n", files[i], destination);
    }
}
