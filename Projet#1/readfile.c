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
#define Buffer_size     128

//  ----------------------------------------------------------------------


/*
void line_spitter(char *str)
{
    char words[4][128];
    char *p = strtok (str, "\t, ");
    int i = 0;

     while (p)
    {
        strcpy(words[i], p);
        //printf("%s\n", words[i]);
        p = strtok(NULL, "\t, ");
        i++;
        
    }

     for (i = 0; i < 4; ++i) 
        {
            printf("%s\n", words[i]);
        }
    

}
*/

int main(int argc, char *argv[])
{
        if(argc != 2)
        {
            printf("Incorrect number of arguments entered");
            exit(EXIT_FAILURE);
        }

    FILE *file;
    int program_count = 0;
    int syscall_count = 0;
    char line[Buffer_size];
    char program_cal[MAX_COMMANDS][MAX_SYSCALLS_PER_PROCESS][Buffer_size]; // buffer for commands
    char program_index[MAX_COMMANDS][MAX_COMMAND_NAME];

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, Buffer_size, file)) 
    {
        line[strlen(line)-1] = '\0';
        
        if (line[0] == '#') // if a comment, skip
        {
            //printf("A line was skipped\n");
            continue;
        }

        else if (line[0] == ' ')
            {
            
                strcpy(program_cal[program_count][syscall_count], line);
                syscall_count ++;
                //line_spitter(line);
            }
        else
        {
            //printf("%s\n", line);
            strcpy(program_index[program_count], line);
            printf("%s\n", program_index[program_count]);
            program_count ++;
           
            //printf("%s\n", line);
        }
      

        
    }
    
}
