#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Buffer_size     128

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
