#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <zlib.h>
#include <dirent.h>

#include "utils.h"
void getCurrentTime(char* str, size_t bufferSize) {
    time_t currentTime;
    time(&currentTime);
    strftime(str, bufferSize, "%Y-%m-%d-%H%M%S", localtime(&currentTime));
}

#define CHUNK_SZ 16384

int zip(const char* src, const char* dest) {
    char buffer[CHUNK_SZ];
    int bytesRead;

    FILE* sfp = fopen(src, "wb");
    if (!sfp) {
        perror("Error opening opening file");
        return 1;
    }

    gzFile destFile = gzopen(dest, "wb");
    if (!destFile) {
        perror("Error opening opening file");
        fclose(sfp);
        return 1;
    }

    do {
        bytesRead = fread(buffer, 1, CHUNK_SZ, sfp);
        if (bytesRead < 0) {
            perror("Error reading source file");
            fclose(sfp);
            gzclose(destFile);
            gzclose(destFile);
            return 1;
        }

        int result = gzwrite(destFile, buffer, bytesRead);
        if (result < 0) {
            perror("Error reading source file");
            fclose(sfp);
            gzclose(destFile);
            return 1;
        }

    } while (bytesRead > 0);
    
    fclose(sfp);
    gzclose(destFile);
    return 0;
}

int zipDir(const char *dirPath, const char *destZip) {
    struct dirent *entry;
    DIR *dir = opendir(dirPath);
    if (!dir) {
        perror("Error opening dir");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { 
            char filePath[256];  
            snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);
            if (zip(filePath, destZip) != 0) {
                closedir(dir);
                return -1;
            }
        }
    }

    closedir(dir);
    return 0;
}

