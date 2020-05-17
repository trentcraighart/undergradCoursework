#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/kernel.h>


int function1(){
    printf("Enumerating all processes\n\n");
    system("ps aux > temp");
    FILE *fp;
    char * line;
    int i = 0;
    size_t len = 0;
    ssize_t read;
    fp = fopen("temp", "r");

    while((read = getline(&line, &len, fp)) != -1){
        printf("%d  ", i);
        printf("%s", line);
        i++;
    }
    fclose(fp);

    return 0;
}

int function2(){
    printf("PID of process to find running threads: ");
    char input[10], final[40];
    fgets(input, 10, stdin);
    int i;
    for(i = 0; i < 10; i++){
        if(input[i] == '\n'){
            input[i] = ' ';
        }
    }

    strcpy(final, "ps -e -T | grep \"");
    strcat(final, input);
    strcat(final, "\" > temp");
    system(final);

    FILE *fp;
    char * line;
    size_t len = 0;
    ssize_t read;
    fp = fopen("temp", "r");

    while((read = getline(&line, &len, fp)) != -1){
        printf("%s", line);
    }
    fclose(fp);

    return 0;
}

int function3(){
    printf("PID of process to find loaded modules: ");
    char input[10], final[40];
    fgets(input, 10, stdin);
    int i;
    for(i = 0; i < 10; i++){
        if(input[i] == '\n'){
            input[i] = ' ';
        }
    }

    strcpy(final, "lsof -p ");
    strcat(final, input);
    strcat(final, " > temp");
    system(final);

    FILE *fp;
    char * line;
    size_t len = 0;
    ssize_t read;
    fp = fopen("temp", "r");

    while((read = getline(&line, &len, fp)) != -1){
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}

int function4(){
    printf("PID of process to find executable pages: ");
    char input[10], final[40];
    fgets(input, 10, stdin);
    int i;
    for(i = 0; i < 10; i++){
        if(input[i] == '\n'){
            input[i] = ' ';
        }
    }

    strcpy(final, "lsof -n | grep \"");
    strcat(final, input);
    strcat(final, "\" > temp");
    system(final);

    FILE *fp;
    char * line;
    size_t len = 0;
    ssize_t read;
    fp = fopen("temp", "r");
    read = getline(&line, &len, fp);

    while((read = getline(&line, &len, fp)) != -1){
        printf("%s", line);
    }
    fclose(fp);

    return 0;
}

int function5(){
    printf("PID of process you want the memory printed for: ");
    char input[10], final[40];
    fgets(input, 10, stdin);
    int i;
    for(i = 0; i < 10; i++){
        if(input[i] == '\n'){
            input[i] = ' ';
        }
    }

    strcpy(final, "/proc/");
    strcat(final, input);
    strcat(final, "/mem");
    system(final);

    FILE *fp;
    char * line;
    size_t len = 0;
    ssize_t read;
    fp = fopen(final, "r");
    read = getline(&line, &len, fp);

    while((read = getline(&line, &len, fp)) != -1){
        printf("%s", line);
    }
    fclose(fp);

    return 0;
}



int main(void)
{
    char resp, cont = 'y';
    printf("Welcome to week 5 Hw by Trent Vasquez for Linux Systems\n");
    printf("NOTE: results are subject to privlages on the system");
    char line[8];

    while(cont == 'y'){
        printf("Instructions: for the process you wish to run:\n");
        printf(" 1 - Enumerate running process\n 2 - List threads in process\n 3 - Enumerate all the loaded modules in process\n");
        printf(" 4 - Show executable pages in process\n 5 - Read Memory of process\n");
        
        fgets(line, 8, stdin);
        resp = line[0];
        
        if(resp == '1')
            function1();

        if(resp == '2')
            function2();

        if(resp == '3')
            function3();

        if(resp == '4')
            function4();

        if(resp == '5') 
            function5();

        printf("Do you wish to continue? y to continue: \n");
        fgets(line, 8, stdin);
        cont = line[0];
    }

}

