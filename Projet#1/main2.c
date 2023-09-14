#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//  you may need other standard header files


//  CITS2002 Project 1 2023
//  Student1:   23451626   Davin Do
//  Student2:   23616299    Jack Carter


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


typedef struct Process{
    int cumulative_time_on_CPU;
    char Syst_call[20];
    char Element_3[20];
    int data_size;
}Process;


//QUEUE STUFF

typedef struct Queue{
    Process processes[MAX_RUNNING_PROCESSES];       //array to hold processes
    int front;
    int rear;
}Queue;


//set queues to -1 when empty
void initializeQueue(Queue *q){
    q->front = -1;
    q->rear = -1;
}

//check if empty
int isEmpty(Queue *q){
    return q->front == -1;
}

//check if full
int isFull(Queue *q){
    return q->rear == MAX_RUNNING_PROCESSES - 1;
}


//enqueue the queue - using circular queue

int enqeue(Queue *q, Process p) {
    if (isFull(q)) {
        printf("QUEUE IS FULL\n");
        return 0;
    } else q->rear = (q->rear + 1) % MAX_RUNNING_PROCESSES;       //increment rear index of array
    q->processes[q->rear] = p;                                     //add process to rear

    if (q->front == -1) {           //set front to rear (if first element)
        q->front = q->rear;
    }
    return 1;
}

Process dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("QUEUE IS EMPTY\n");

        exit(1);
    } else {
        Process p = q->processes[q->front];         //extract process at front of queue


        if (q->front == q->rear) {              //check if only 1 process in queue, if so reset front and rear to -1
            q->front = -1;
            q->rear = -1;
        } else {
            q->front = (q->front + 1) % MAX_RUNNING_PROCESSES;          //move front pointer to next process for circular queue
        }
        return p;       //return dequeued process
    }
}







Device device_list[MAX_DEVICES];
int device_count = 0;
int program_count = 0;
int Time_Quantum = DEFAULT_TIME_QUANTUM;
Process program_call[MAX_COMMANDS][MAX_SYSCALLS_PER_PROCESS]; // buffer for commands
char program_index[MAX_COMMANDS][MAX_COMMAND_NAME];



void time_on_cpu(Process* procstruct, int commands, int syscall, int cumul_process_time) {

    int required_time = program_call[commands][syscall].cumulative_time_on_CPU - cumul_process_time;

    if (required_time > Time_Quantum) {

        strcpy(procstruct->Element_3, "Elapsed time");
        procstruct->cumulative_time_on_CPU += Time_Quantum;
    } else {
        procstruct->cumulative_time_on_CPU += required_time;
        // call system call

        //finish later


    }
}



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

void read_sysconfig(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open the file");
        exit(1);
    }

    char line[Buffer_size];
    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        if (line[0] == 't')
        {
            char time_str[9];
            sscanf(line, "timequantum %9s", time_str);
            Time_Quantum = atoi(time_str);

        }

        if(device_count <= MAX_DEVICES) {
            device_list[device_count] = parse_device_line(line);
            device_count++;
        } else {
            fprintf(stderr, "Max devices reached\n");
            break;
        }
    }
    fclose(file);

}

Process parse_process_line(char *line) {
    Process process;
    char time_on_CPU_str[20], data_size_str[20];
    sscanf(line, "\t %19s %19s %19s %19s", time_on_CPU_str, process.Syst_call, process.Element_3, data_size_str);

    // Remove 'B or usecs' from the time/size and convert it to int
    process.cumulative_time_on_CPU = atoi(time_on_CPU_str);
    process.data_size = atoi(data_size_str);
    //printf("%s\n", process.Syst_call);

    return process;
}

void read_commands(char file_name[]){
    int syscall_count = 0;
    FILE *file;

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
            program_call[program_count-1][syscall_count] = parse_process_line(line);
            syscall_count ++;
            //line_spitter(line);
        }
        else
        {
            //printf("%s\n", line);
            strcpy(program_index[program_count], line);
            //printf("%s\n", program_index[program_count]);
            program_count ++;
            syscall_count = 0;
            //printf("%s\n", line);
        }

    }
    fclose(file);
}

void execute_commands(char *program_name)
{
    // This adds a program to the ready queue

    // this will be a small append
    printf("The program %s has been added to the running queue \n", program_name);
}
int index_process(char *program_name)
{   // this program returns an int of which position the program is in
    int i = 0;
    while (1)
    {
        if (strcmp(program_name, program_index[i]) == 0)
        {
            return i;
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    //  ENSURE THAT WE HAVE THE CORRECT NUMBER OF COMMAND-LINE ARGUMENTS
    if(argc != 3) {
        printf("Usage: %s sysconfig-file command-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //  READ THE SYSTEM CONFIGURATION FILE
    read_sysconfig(argv[1]);

    //  READ THE COMMAND FILE
    read_commands(argv[2]);
    //starts the first program
    execute_commands(program_index[0]);



    /*
    for (int i = 0; i < program_count -1 ; i++)
    {
        for (int n = 0; n < 40; n++)
        {
            printf("process:%s\n" ,program_call[i][n].Syst_call);

            if (strcmp(program_call[i][n].Syst_call, "exit") == 0)
            {
                break;
            }
        }
    }
    */

}
