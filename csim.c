/*
 * Alex Baker
 * alexebaker
 * 101372834
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "cachelab.h"


void read_trace(char** trace_file, int* verbose);


int main(int argc, char **argv)
{
    int help = 0;
    int verbose = 0;
    int s_value = 0;
    int E_value = 0;
    int b_value = 0;
    int hit_count = 0;
    int miss_count = 0;
    int evict_count = 0;
    char *trace_file = "";
    char *usage = "Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>";

    int arg = 0;
    char* ptr = "";

    /* Parse cli args */
    while ((arg = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch (arg)
        {
            case 'h':
                help = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case 's':
                s_value = strtol(optarg, &ptr, 10);
                break;
            case 'E':
                E_value = strtol(optarg, &ptr, 10);
                break;
            case 'b':
                b_value = strtol(optarg, &ptr, 10);
                break;
            case 't':
                trace_file = optarg;
                break;
            default:
                printf("%s\n", usage);
                exit(EXIT_FAILURE);
                break;
        }
    }

    if (help)
    {
        printf("%s\n", usage);
        exit(EXIT_SUCCESS);
    }

    read_trace(&trace_file, &verbose);

    printSummary(hit_count, miss_count, evict_count);
    exit(EXIT_SUCCESS);
}


void read_trace(char** trace_file, int* verbose)
{
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    fp = fopen(*trace_file, "r");
    if (fp == NULL)
    {
        printf("Unable to open file: %s\n", *trace_file);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (*verbose)
        {
            printf("%s", line);
        }
    }

    fclose(fp);
    if (line) free(line);
    return;
}
