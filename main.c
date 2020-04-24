#include <stdio.h>  //printf, fprintf, perror,
#include <time.h>   //time, ctime
#include <stdlib.h> //setenv, exit

#define NO_ERRORS 0
#define ERR_SETENV 1
#define ERR_TIMESTRING 2
#define ERR_PRINT 3
#define ERR_TIMESYSCALL 4
#define ERR_ARGS 5

int main(int argc, char *argv[]) {

    if (argc != 1) {
        fprintf(stdout, "Usage: ./californiaTime (no arguments provided)\n");
        exit(ERR_ARGS);
    }

    time_t pstTime;

    if (setenv("TZ", "PST8PDT", 1) == -1) {
        perror("Error while setting environment variables");
        exit(ERR_SETENV);
    }

    if (time(&pstTime) == (time_t) -1) {
        perror("Error while getting time from the OS");
        exit(ERR_TIMESYSCALL);
    }

    char *timeString;
    if ((timeString = ctime(&pstTime)) == NULL) {
        perror("Error while getting time in a string");
        exit(ERR_TIMESTRING);
    }

    if (printf("Time in California: %s", timeString) < 0) {
        perror("Error while printing time");
        exit(ERR_PRINT);
    }

    exit(NO_ERRORS);
}
