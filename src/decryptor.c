#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "banner.h"

#define TARGET_DIR "victim_data/"
#define EXTENSION ".locked"
#define XOR_KEY 0x5A

void xor_decrypt(const char *locked_path);
int ends_with(const char *str, const char *suffix);

int main()
{
    print_banner("decryptor");

    DIR *dir;
    struct dirent *entry;

    dir = opendir(TARGET_DIR);
    if (!dir)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (ends_with(entry->d_name, EXTENSION))
        {
            char path[256];
            size_t needed = strlen(TARGET_DIR) + strlen(entry->d_name) + 1;
            if (needed >= sizeof(path)) continue;

            snprintf(path, sizeof(path), "%s%s", TARGET_DIR, entry->d_name);
            xor_decrypt(path);
            printf("[✓] Decrypted: %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

void xor_decrypt(const char *locked_path)
{
    FILE *in = fopen(locked_path, "rb");
    if (!in) return;

    char output_path[256];
    size_t base_len = strlen(locked_path) - strlen(EXTENSION);
    if (base_len >= sizeof(output_path)) base_len = sizeof(output_path) - 1;

    memcpy(output_path, locked_path, base_len);
    output_path[base_len] = '\0';

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

    remove(locked_path);
}

int ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix) return 0;
    size_t len_str = strlen(str);
    size_t len_suf = strlen(suffix);
    if (len_suf > len_str) return 0;
    return strcmp(str + len_str - len_suf, suffix) == 0;
}