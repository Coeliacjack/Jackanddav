#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
typedef struct Devices{
    char device_name[MAX_DEVICE_NAME];              //DEVICE NAME
    int read_speed;
    int write_speed;
}Device;

typedef struct PROCESES{             
    int cumutive_time_on_CPU;
    char Syst_call[20];
    char Element_3[20];
    int data_size;
}PROCESS;

Device device_list[MAX_DEVICES];
int device_count = 0;
int program_count = 0;

PROCESS program_call[MAX_COMMANDS][MAX_SYSCALLS_PER_PROCESS]; // buffer for commands
char program_index[MAX_COMMANDS][MAX_COMMAND_NAME];



int calc_device_io(char device_name[], char read_or_write[], char size[]){

    Device device;
    int time_taken;

    for (int i = 0; i < device_count; i++) {
        if (strcmp(device_name, device_list[i].device_name) == 0) {
            device = device_list[i];
        }
    }
    if (strcmp(read_or_write, "read") == 0) {

        time_taken = (atoi(size)*pow(10,6))/device.read_speed ;
    }
    else {

        time_taken = (atoi(size)*pow(10,6))/device.write_speed ;
    }

    return time_taken;

}
Device parse_device_line(char *line) {
    Device device;
    char read_speed_str[20], write_speed_str[20];
    sscanf(line, "device %19s %19s %19s", device.device_name, read_speed_str, write_speed_str);

    // Remove 'Bps' from the speed and convert it to int
    device.read_speed = atoi(read_speed_str);
    device.write_speed = atoi(write_speed_str);

    return device;
}

void read_devices_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open the file");
        exit(1);
    }

    char line[Buffer_size];
    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        if(device_count <= MAX_DEVICES) {
            device_list[device_count] = parse_device_line(line);
            device_count++;
        } else {
            fprintf(stderr, "Reached maximum device limit. Ignoring further entries.\n");
            break;
        }
    }
    fclose(file);
}
PROCESS parse_process_line(char *line) {
    PROCESS process;
    char time_on_CPU_str[20], data_size_str[20];
    sscanf(line, "\t %19s %19s %19s %19s", time_on_CPU_str, process.Syst_call, process.Element_3, data_size_str);

    // Remove 'B or usecs' from the time/size and convert it to int
    process.cumutive_time_on_CPU = atoi(time_on_CPU_str);
    process.data_size = atoi(data_size_str);
    //printf("%s\n", process.Syst_call);

    return process;
}

void read_progams_from_file(char file_name[]){
    FILE *file;
    
    int syscall_count = 0;
    char line[Buffer_size];
    

    file = fopen(file_name, "r");

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
            
                //strcpy(program_call[program_count][syscall_count], line);
                program_call[program_count][syscall_count] = parse_process_line(line);
                //printf("Process:%d\n", program_call[program_count][syscall_count].cumutive_time_on_CPU);
                syscall_count ++;
                //line_spitter(line);
            }
        else
        {
            //printf("%s\n", line);
            strcpy(program_index[program_count], line);
            //printf("%s\n", program_index[program_count]);
            program_count ++;
           
            //printf("%s\n", line);
        }
    }
}

int main(int argc, char *argv[])
{
        if(argc != 3)
        {
            printf("Incorrect number of arguments entered");
            exit(EXIT_FAILURE);
        }
    read_devices_from_file(argv[1]);
    read_progams_from_file(argv[2]);
    printf("Time:%d\n", program_call[3][0].cumutive_time_on_CPU);
    //printf("Process:%s\n", program_call[0][0].Syst_call);
    
   /*
    
    for (int i = 0; i < 20; i++)
    {
        printf("process:%s\n" ,program_call[3][i].Syst_call);
    }
 
    for (int i = 0; i < program_count; i++)
    {
        for (int n = 0; n < 40; n++)
        {
            if (strcmp(program_call[i][n].Syst_call, "exit") == 0)
            {
                break;
            }
            else
            {
                printf("process:%s\n" ,program_call[2][n].Syst_call);
            }
        }
    }
    */

    
}
