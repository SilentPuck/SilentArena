#include <stdio.h>
#include "banner.h"

void print_banner(const char *module) {
    printf("🕶 SilentArena Lite v0.1 — %s\n", module);
    printf("Forged in silence. Written in C.\n");
    printf("Use --simulate flag. Log: attack.log\n\n");
}
