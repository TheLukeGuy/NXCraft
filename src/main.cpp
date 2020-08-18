#include <iostream>
#include <switch.h>

int main() {
    consoleInit(nullptr);

    while (appletMainLoop()) {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) {
            break;
        }

        consoleUpdate(nullptr);
    }
    
    consoleExit(nullptr);
    return EXIT_SUCCESS;
}
