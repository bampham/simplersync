#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "ser.h"
#include "utils.h"

int main(void) {
    Config config;
    if (deserialize("/etc/simplersync/config.json", &config) != 0) {
        fprintf(stderr, "Error deserializing /etc/simplersync/config.json");
    }

    char date[128];
    char command[512];
    char src[256];
    char dest[256];

    while (1) {
        getCurrentTime(date, sizeof(date));
        snprintf(command, sizeof(command), "scp -r %s@%s:%s %s/%s", config.username, config.remoteHost, config.remoteDirectory, config.destinationDirectory, date);
        if (system(command) != 0) fprintf(stderr, "An error occurred during backup!\n");

        snprintf(src, sizeof(src), "%s/%s", config.destinationDirectory, date);
        snprintf(dest, sizeof(dest), "%s/%s.zip", config.destinationDirectory, date);

        if (zipDir(src, dest) != 0) {
            fprintf(stderr, "Error zipping dir");
        }

        if (rmdir(src) != 0) {
            fprintf(stderr, "Error deleting dir");
        }

        bzero(src, sizeof(src));
        bzero(dest, sizeof(dest));
        bzero(date, sizeof(date));
        bzero(command, sizeof(command));
        sleep(config.backupFrequencyHours * 3600);
    }

    return 0;
}

