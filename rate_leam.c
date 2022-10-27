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
    int flags = 0;
    char *ptr;

    ptr = strtok(argList[countI+1], " ");

    while (ptr != NULL)
    {
        //Variável auxiliar para colocar o período e o cpu burst na struct
        if(flags == 0) {

            strcpy(list[count].id, ptr);
            flags = 1;
        }

        else if(flags == 1)     {
            list[count].timePeriod = (int*)ptr;
            flags = 2;

        }else if(flags == 2) {

            list[count].timeDur = (int*)ptr;
            
        }
        ptr = strtok(NULL, " ");
    }
    count++;
    countI++;
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
   // printf("%d", timeTotal);
    int flag = 0;
    int count = 0;
    if (file)
    {

        char line[1024];
        while (fgets(line, 1024, file)) {
            
            if (flag > 0)
            {
                printf("%s", line);
                if (sscanf(line, "%s %d %d", list[count].id, &list[count].timePeriod, &list[count].timeDur) == 2)
                {
                }
                

            }
            if (flag > 0)
                count++;

            flag = 1;
    }

    }

  //  while (fscanf(file, "%c %d \n", &, &data) != NULL)
  /*  { /*
        argList[r] = malloc(sizeof *argList[r] * 100);
        fgets(argList[r], 100, file);
        argList[r][strlen(argList[r]) - 1] = '\0';
        r++; */

 //       fscanf("")
   // }

    //separatorarguments();

    printf("%s\n", list[0].id);
    printf("%d\n", list[0].timePeriod);
    printf("%d\n", list[0].timeDur);

 /*  for (int i = 0; i < r; i++)
    {

        printf("%s\n", list[i].id);
        printf("%d\n", list[i].timeDur);
        printf("%d\n", list[i].timePeriod);
    }*/

    return 0;
}