#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "ser.h"

void getCurrentTime(char *dateTimeString, size_t bufferSize) {
    time_t currentTime;
    time(&currentTime);
    strftime(dateTimeString, bufferSize, "%Y-%m-%d-%H%M%S", localtime(&currentTime));
}

int main(void) {
    Config config;
    deserialize("/etc/simplersync/config.json", &config);

    char date[128];
    char command[512];

    while (1) {
        getCurrentTime(date, 128);

        snprintf(command, sizeof(command), "scp -r %s@%s:%s %s/%s", config.username, config.remoteHost, config.remoteDirectory, config.localDirectory, date);

        if (system(command) != 0) {
            fprintf(stderr, "An error occurred during backup!\n");
        }

        
        sleep(config.backupFrequencyHours * 3600);

    }

    return 0;
}

