#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//  you may need other standard header files


//  CITS2002 Project 1 2023
//  Student1:   23451626   DAVIN DO
//  Student2:   STUDENT-NUMBER2   NAME-2


//  myscheduler (v1.0)
//  Compile with:  cc -std=c11 -Wall -Werror -o myscheduler myscheduler.c


//  THESE CONSTANTS DEFINE THE MAXIMUM SIZE OF sysconfig AND command DETAILS
//  THAT YOUR PROGRAM NEEDS TO SUPPORT.  YOU'LL REQUIRE THESE //  CONSTANTS
//  WHEN DEFINING THE MAXIMUM SIZES OF ANY REQUIRED DATA STRUCTURES.

#define MAX_DEVICES                     4
#define MAX_DEVICE_NAME                 20
#define MAX_COMMANDS                    10
#define MAX_COMMAND_NAME                20
#define MAX_SYSCALLS_PER_PROCESS        40
#define MAX_RUNNING_PROCESSES           50

//  NOTE THAT DEVICE DATA-TRANSFER-RATES ARE MEASURED IN BYTES/SECOND,
//  THAT ALL TIMES ARE MEASURED IN MICROSECONDS (usecs),
//  AND THAT THE TOTAL-PROCESS-COMPLETION-TIME WILL NOT EXCEED 2000 SECONDS
//  (SO YOU CAN SAFELY USE 'STANDARD' 32-BIT ints TO STORE TIMES).

#define DEFAULT_TIME_QUANTUM            100

#define TIME_CONTEXT_SWITCH             5
#define TIME_CORE_STATE_TRANSITIONS     10
#define TIME_ACQUIRE_BUS                20


//  ----------------------------------------------------------------------

#define CHAR_COMMENT                    '#'

#define MAX_LENGTH                      256 //ASDFASDFASDF


void read_sysconfig(const char *filename, long *time_quantum)
{
    FILE *file = fopen(filename, "r");      //open file (fopen() mode)

    if(file == NULL) {
        printf("Cannot open '%s' \n", filename);        //if file does not exist, cannot open, etc
        exit(EXIT_FAILURE);
    }

    char line[MAX_LENGTH];      //BUFFER

    //parameters: from buffer, max number of characters to read, file pointer
    while(fgets(line , MAX_LENGTH , file) != NULL){
        char *split_lines = strtok(line, "\n\t\r"); //splits newline, tab and returns

        if (split_lines[0] == '#' || " " == NULL) {
            continue;   //skips comments
        }
        
       printf("%s\n", line);
    }    
    
    fclose(file);
}


int main(int argc, char *argv[])
{
//  ENSURE THAT WE HAVE THE CORRECT NUMBER OF COMMAND-LINE ARGUMENTS
    if(argc != 3) {
        printf("Usage: %s sysconfig-file command-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //struct Device devices[MAX_DEVICES];
    const char *filename = argv[1]; //use argv[1] as filename (sysconfig)
    long time_quantum = 0;





//  READ THE SYSTEM CONFIGURATION FILE
    read_sysconfig(filename, &time_quantum);
}