#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3
#define BUFFER 100

int countI = 0;
int timeTotal;
char *argList[BUFFER];
int count = 0;
int countAux = 0;

typedef struct
{

    char id[SIZE];
    int timePeriod;
    int timeDur;
    int timeWait;

} Process;

Process list[SIZE];

void calcular () {

    /*
    printf("Processo 1: \n");

    scanf("%19[0-9a-zA-Z]", list[0].id);
    scanf("%d", &list[0].timeExec);
    scanf("%d", &list[0].timeWait);

    printf("Processo 2: \n");
    scanf("%19[0-9a-zA-Z]", list[0].id);
    scanf("%d", &list[1].timeExec);
    scanf("%d", &list[1].timeWait);

    int unit; */
    
}

void separatorarguments()
{
    
    char *ptr;

    ptr = strtok(argList[countI+1], " ");

    while (ptr != NULL)
    {
        list[count].timePeriod = ptr;
        count++;
        ptr = strtok(NULL, " ");
    }
    list[countAux].timeDur = list[count - 1].timePeriod;
}

int main (int argc, char** argv) {

    if(argc <= 1) {

        printf("no argList entered!\n");
        exit(1);
    }

    int r = 0;
    FILE *file;
    
    file = fopen(argv[1], "r");
    fscanf(file, "%d", &timeTotal);
    
    while (!feof(file) && !ferror(file))
    {
        argList[r] = malloc(sizeof *argList[r] * 100);
        fgets(argList[r], 100, file);
        argList[r][strlen(argList[r]) - 1] = '\0';
        r++;
    }

    

   // calcular();

    for (int i = 0; i < r; i++) {
        
        printf("%s\n", argList[i]);
    
    }

    return 0;
}