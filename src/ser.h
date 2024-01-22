#ifndef SER_H
#define SER_H

#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

typedef struct {
    char username[50];
    char remoteHost[32];
    char remoteDirectory[128];
    char localDirectory[128];
    int backupFrequencyHours;
} Config;

void serialize(const char *filename, const Config *config);
int deserialize(const char *filename, Config *config);

#endif
