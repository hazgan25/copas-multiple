#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void clearOutputDirectory(const char *outputDir);
void copyFile(const char *source, const char *destination);
void copyAllFiles(char files[][255], int fileCount, const char *title, int isEpisode);

#endif
