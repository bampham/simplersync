#include <stdlib.h>
#include <stdio.h>
#include <jansson.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    char username[50];
    char remoteHost[32];
    char remoteDirectory[128];
    char localDirectory[128];
    int backupFrequencyHours;
} Config;

void serialize(const char *filename, const Config *config) {
    json_t *root = json_object();
    
    json_object_set_new(root, "username", json_string(config->username));
    json_object_set_new(root, "remoteHost", json_string(config->remoteHost));
    json_object_set_new(root, "remoteDirectory", json_string(config->remoteDirectory));
    json_object_set_new(root, "localDirectory", json_string(config->localDirectory));
    json_object_set_new(root, "backupFrequencyHours", json_integer(config->backupFrequencyHours));

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        json_decref(root);  
        return;
    }

    char *jsonString = json_dumps(root, JSON_INDENT(2));
    fprintf(file, "%s\n", jsonString);

    fclose(file);
    free(jsonString);
    json_decref(root);
}

int deserialize(const char *filename, Config *config) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;  
    }

    json_error_t error;
    json_t *root = json_loadf(file, 0, &error);
    fclose(file);

    if (!root) {
        fprintf(stderr, "JSON error on line %d: %s\n", error.line, error.text);
        return 0;  
    }

    json_t *usernameJson = json_object_get(root, "username");
    json_t *remoteHostJson = json_object_get(root, "remoteHost");
    json_t *remoteDirectoryJson = json_object_get(root, "remoteDirectory");
    json_t *localDirectoryJson = json_object_get(root, "localDirectory");
    json_t *backupFrequencyJson = json_object_get(root, "backupFrequencyHours");

    if (!usernameJson || !remoteHostJson || !remoteDirectoryJson || !localDirectoryJson || !backupFrequencyJson) {
        fprintf(stderr, "Error getting values from JSON object\n");
        json_decref(root);
        return 0;  
    }

    snprintf(config->username, sizeof(config->username), "%s", json_string_value(usernameJson));
    snprintf(config->remoteHost, sizeof(config->remoteHost), "%s", json_string_value(remoteHostJson));
    snprintf(config->remoteDirectory, sizeof(config->remoteDirectory), "%s", json_string_value(remoteDirectoryJson));
    snprintf(config->localDirectory, sizeof(config->localDirectory), "%s", json_string_value(localDirectoryJson));
    config->backupFrequencyHours = json_integer_value(backupFrequencyJson);

    json_decref(root);

    return 1;  
}

int main(void) {
    Config config;
    deserialize("/etc/simplersync/config.json", &config);

    while (1) {
        char command[512];
        snprintf(command, sizeof(command), "scp -r %s@%s:%s %s", config.username, config.remoteHost, config.remoteDirectory, config.localDirectory);

        if (system(command) != 0) {
            fprintf(stderr, "An error occurred during backup!\n");
        }

        sleep(config.backupFrequencyHours * 3600);
    }

    return 0;
}

