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


int main(int argc, char **argv)
{
    int help = 0;
    int verbose = 0;
    int s_value = 0;
    int E_value = 0;
    int b_value = 0;
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
                exit(1);
                break;
        }
    }

    if (help)
    {
        printf("%s\n", usage);
        exit(0);
    }

    printSummary(0, 0, 0);
    return 0;
}


