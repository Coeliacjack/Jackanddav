#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

//my own definitions

#define MAX_LENGTH                      256



/*
struct Process{
    int id;                         //PID
    enum ProcessStates state;       //state
    int arrival_time;               //ARRIVAL TIME
    int ex_time;                  //EXECUTION TIME
    int remaining_time;          //REMAINING TIME
};

 */

struct Device{

    char name_of[MAX_DEVICE_NAME];              //DEVICE NAME
    int read_speed;
    int write_speed;
};
/*
struct Command {
    char name[MAX_COMMAND_NAME]
    struct SysCall {
        int time;
        int size;
        char
    }MAX_SYSCALLS_PER_PROCESS;


};
*/



void read_sysconfig(const char filename, struct Device *devices, long *time_quantum)
{
    FILE *file = fopen(&filename, "r");      //open file (fopen() mode)

    if(file == NULL) {
        printf("Cannot open '%c' \n", filename);        //if file does not exist, cannot open, etc
        exit(EXIT_FAILURE);
    }

    int device_count = 0;       //initialize device count
    char line[MAX_LENGTH];      //BUFFER

    //parameters: from buffer, max number of characters to read, file pointer
    while(fgets(line , sizeof(line) , file) != NULL){
        char *split_lines = strtok(line, "\n\t\r"); //splits newline, tab and returns

        if (split_lines[0] == '#' || split_lines == NULL) {
            continue;   //skips comments
        }

        char *token = strtok(split_lines, "\t");    //split once again - now assigned to 'token'

        if(strcmp(token, "device") == 0){   //strcmp - returns 0 if it says device - time to read the info!!!

            char *device_name = strtok(NULL, "\t");             //tokenizing same string from last position
            char *read_speed_string = strtok(NULL, "\t");       //hence null pointer
            char *write_speed_string = strtok(NULL, "\t");       //--must convert string to int



            if(device_count < MAX_DEVICES) {
                strcpy(devices[device_count].name_of, device_name);         //copy device name outlined by struct to array of device counter (keeping track of each device)
                devices[device_count].read_speed = strtol(read_speed_string, NULL, 10);
                devices[device_count].write_speed = strtol(write_speed_string, NULL, 10);

                device_count++;
            }

            else if (strcmp(token, "timequantum") == 0) {                                   //read time quantum, extract
                char *time_quantum_string = strtok(NULL, "\t");
                *time_quantum = strtol(time_quantum_string, NULL, 10);

            }
        }
    }
    fclose(file);
}


int main(int argc, char *argv[]) {
//  ENSURE THAT WE HAVE THE CORRECT NUMBER OF COMMAND-LINE ARGUMENTS
    if (argc != 3) {
        printf("Usage: %s sysconfig-file command-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char filename = 0;
    struct Device *devices = NULL;
    long time_quantum = 0;
    read_sysconfig(filename, devices, &time_quantum);

    exit(EXIT_SUCCESS);

/*

//SYSTEM CALLS

void sleep_command(unsigned int microseconds){
    usleep(microseconds);                   //SLEEPING
};



int Queue[MAX_RUNNING_PROCESSES], frontReady  = -1, rearReady = -1;




void read_commands(const char filename)
{
    FILE *file = fopen(&filename, "r");

    if(file == NULL) {
        printf("Cannot open '%c' \n", filename);        //if file does not exist, cannot open, etc
        exit(EXIT_FAILURE);
    }


    char line[MAX_SYSCALLS_PER_PROCESS];
    unsigned int elapsed_time = 0;              //unsigned int so no overflows

    //parameters: from buffer, max number of characters to read, file pointer
    while(fgets(line , sizeof(line) , file) != NULL) {
        char *split_lines = strtok(line, "\n\t\r"); //splits newline, tab and returns

        if (split_lines[0] == '#' || split_lines == NULL) {
            continue;   //skips comments
        }

        char *token = strtok(split_lines, "\t");    //split once again - now assigned to 'token'

        if (strcmp(token, "sleep") == 0) {   //strcmp - returns 0 if it says device - time to read the info!!!


        }












//  ----------------------------------------------------------------------

void execute_commands(void) {

            //put in states
            //PUT DATA STRUCTURES HERE

        }

//  ----------------------------------------------------------------------



int main(int argc, char *argv[]) {
//  ENSURE THAT WE HAVE THE CORRECT NUMBER OF COMMAND-LINE ARGUMENTS
            if (argc != 3) {
                printf("Usage: %s sysconfig-file command-file\n", argv[0]);
                exit(EXIT_FAILURE);
            }

            struct Device devices[MAX_DEVICES];
            const char *filename = argv[1]; //use argv[1] as filename (sysconfig)
            long time_quantum = 0;





//  READ THE SYSTEM CONFIGURATION FILE
            read_sysconfig(filename, devices, &time_quantum);

//  READ THE COMMAND FILE
            read_commands(argv[0], argv[2]);

//  EXECUTE COMMANDS, STARTING AT FIRST IN command-file, UNTIL NONE REMAIN
            execute_commands();

//  PRINT THE PROGRAM'S RESULTS
            printf("measurements  %i  %i\n", 0, 0);

            exit(EXIT_SUCCESS);
        }

//  vim: ts=8 sw=4

*/
}
