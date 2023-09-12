#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_DEVICES                     4
#define MAX_DEVICE_NAME                 20
#define MAX_COMMANDS                    10
#define MAX_COMMAND_NAME                20
#define MAX_SYSCALLS_PER_PROCESS        40
#define MAX_RUNNING_PROCESSES           50

#define MAX_LENGTH                      256
#define Buffer_size     128

typedef struct Devices{
    char device_name[MAX_DEVICE_NAME];              //DEVICE NAME
    int read_speed;
    int write_speed;
}Device;

Device device_list[MAX_DEVICES];
int device_count = 0;



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

    for (i = 0; i < MAX_DEVICES; ++i)
    {
        printf("%s\n", words[i]);
    }


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

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        if(device_count < MAX_DEVICES) {
            device_list[device_count] = parse_device_line(line);
            device_count++;
        } else {
            fprintf(stderr, "Reached maximum device limit. Ignoring further entries.\n");
            break;
        }
    }

    fclose(file);
}

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


    file = fopen(argv[1], "r");

    //fill device_list with devices
    read_devices_from_file(argv[1]);
    int return_int = calc_device_io("usb3.1", "read", "640000000Bps");

    //finding how long device takes


    printf("thing is: %d", return_int);
    return 0;

    if (file == NULL) {
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, Buffer_size, file))
    {


        if (line[0] == '#')
        {

            printf("A line was skipped\n");
            continue;
        }

        else if (line[0] == ' ')
        {
            syscall_count ++;
            line[strlen(line)-1] = '\0';
            line_spitter(line);
        }

        else
        {
            program_count ++;
            printf("%s\n", line);
        }


    }



}
