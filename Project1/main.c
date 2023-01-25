#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int hist_index;
//#include "functions.h"

#define MAX_COMMAND_SIZE 128
#define HOST_NAME_MAX 64

char *history[15];

void mycomputername()
{
    char name[HOST_NAME_MAX];

    int ret = gethostname(name, HOST_NAME_MAX);

    puts(name);

}

void listdir()
{
    system("ls");
}



void printfile(char *filename)
{
    char input = '\n';
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("stfu");
    }

    
    while ((read = getline(&line, &len, file)) != -1) { // reading while available
        
        if(input != '\n'){ // if anything other than enter pressed stop reading
            break;
            
        }
        else{
            line[strcspn(line, "\n")] = 0; // deleting newline from string in order to avoid multiple empty lines in the output
            printf("%s", line);
        }

        fflush(stdin);

        scanf("%c",&input);
    }
    


    fclose(file);
}

void printfiletofile(char *oldfile, char *newfile)
{
    char *command;
    asprintf(&command, "cp %s %s", oldfile, newfile); // building the string

    system(command);
}

void addhistory(char *command)
{
    if (hist_index == 15)
    {
        hist_index = 0; // resetting the counter
    }
    if (command != NULL)
    {
        strcpy(history[hist_index], command);
        hist_index++;
    }
}
int dididothat(char *command)
{
    int ret;
    for (int i = 0; i < sizeof(history)/sizeof(history[0]); i++)
    {
        //looping the whole array in order to find the fiven command
        ret = strcmp(history[i], command);
        if (ret == 0)
        {
            return 1;
        }
    }
    return 0;
}

void hellotext()
{
    system("gedit"); // opens gedit text editor
}

void whatsmyip(){
    system("hostname -i");
}




int main(void)
{
    // initializing  history array
    for (size_t i = 0; i < 15; i++)
    {
        history[i] = malloc(MAX_COMMAND_SIZE);
    }

    char input[MAX_COMMAND_SIZE] = "";          // input string
    char *copyofstr = malloc(MAX_COMMAND_SIZE); // copy of a input string

    char *username = getenv("USER"); // getting username to print in front of the every prompt

    printf("%s >>> ", username);

    while (1) // leaving the loop with break statement
    {
        fflush(stdin);          // cleaning stdin in order to make sure retrieved input is correct
        //scanf("%[^\n]", input); // getting whole command from user
        //scanf(" %s", input);
        fgets(input, 128, stdin);
        input[strcspn(input, "\n")] = 0;
        strcpy(copyofstr, input);

        char *ptr; // pointer that is used for every token
        ptr = strtok(input, " ");

        if (ptr != NULL)
        {
            if (strcmp(ptr, "dididothat") != 0) // to prevent adding dididothat to history
            {
                addhistory(copyofstr);
            }


            if (strcmp(ptr, "listdir") == 0)
            {
                listdir();
            }
            else if (strcmp(ptr, "mycomputername") == 0)
            {
                mycomputername();
            }
            else if (strcmp(ptr, "whatsmyip") == 0)
            {
                whatsmyip();
            }
            else if (strcmp(ptr, "printfile") == 0)
            {
                ptr = strtok(NULL, " ");

                char *file1 = ptr;
                ptr = strtok(NULL, " "); // > sign is retrieved

                if (ptr != NULL)
                { // it has two arguments

                    ptr = strtok(NULL, " "); // second files name is retrieved
                    char *file2 = ptr;
                    printfiletofile(file1, file2); // that is printfile method for 2 arguments
                    ptr = strtok(NULL, " ");
                    if (ptr != NULL)
                    {
                        printf("komut dogru girilmedi");
                    }
                }
                else
                {
                    // printfile called with 1 argument
                    printfile(file1);
                }
            }
            else if (strcmp(ptr, "dididothat") == 0)
            {
                ptr = strtok(NULL, "");
                char *oldcommand = ptr;

                int ret = dididothat(oldcommand); // checking the history array
                if (ret == 0)
                {
                    printf("No");
                }
                else
                {
                    printf("Yes");
                }
                printf("\n");
            }
            else if (strcmp(ptr, "hellotext") == 0)
            {
                hellotext();
            }
            else if (strcmp(ptr, "exit") == 0)
            {
                break;
            }
            else
            {
                printf("bilinmeyen bir komut girildi");
            }
        }
        else
        {
            
        }

        printf("%s >>> ", username);
    }

    return 0;
}
