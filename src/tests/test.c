#include <stdio.h>
#include "ser.h"

int main(void) {
    Config testConfig = {"test", "test", "test", "test", 24};
    serialize("testconfig.json", &testConfig);

    return 0;
}
