#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "banner.h"

#define TARGET_DIR "victim_data/"
#define EXTENSION ".locked"
#define LOG_FILE "attack.log"

int ends_with(const char *str, const char *suffix);

int main()
{
    print_banner("scanner");

    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(TARGET_DIR);
    if (!dir)
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (ends_with(entry->d_name,EXTENSION))
        {
            printf("[!] Locked file found: %s\n", entry->d_name);
            count++;
        }
        
    }
    closedir(dir);

    printf("\n📊 Total locked files: %d\n", count);

    printf("\n📄 Attack log:\n-----------------------\n");
    FILE *log = fopen(LOG_FILE, "r");
    if (log)
    {
        char line[256];
        while (fgets(line, sizeof(line), log))
        {
            printf("%s", line);
        }
        fclose(log);
    }
    else
    {
        printf("No log file found.\n");
    }
    return EXIT_SUCCESS;
}

int ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix) return 0;
    size_t len_str = strlen(str);
    size_t len_suf = strlen(suffix);
    if (len_suf > len_str) return 0;
    return strcmp(str + len_str - len_suf, suffix) == 0;
    
}