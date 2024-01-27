#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <time.h>
#include <zlib.h>

void getCurrentTime(char* str, size_t bufferSize);
int zipDir(const char* dirPath, const char* destZip);

#endif
