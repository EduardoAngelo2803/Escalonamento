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

typedef struct {

    char id[SIZE];
    int timePeriod;
    int timeDur;
    int timeWait;

} Process;

Process list[SIZE];

void selection_sort () {
  int i, j, min, aux;
  
  for (i = 0; i < count-1; i++) {
  
    min = i;

    for (j = i+1; j < count; j++) {
      
        if (list[j].timePeriod < list[min].timePeriod) {
            min = j;
        }
    }
    
    if (i != min) {
        aux = list[i].timePeriod;
        list[i].timePeriod = list[min].timePeriod;
        list[min].timePeriod = aux;
    }
  }
}

void calcular () {

    
}

void insertion_sort(int max) {

    int i, j, auxPeriod, auxDur, auxWait;
    char auxId[SIZE];

    for (i = 1; i < max; i++)
    {

        auxPeriod = list[i].timePeriod;
        auxDur = list[i].timeDur;
        auxWait = list[i].timeWait;
        strcpy(auxId, list[i].id);
        for (j = i - 1; j >= 0 && auxPeriod < list[j].timePeriod; j--)
        {

            list[j + 1].timePeriod = list[j].timePeriod;
            list[j + 1].timeDur = list[j].timeDur;
            list[j + 1].timeWait = list[j].timeWait;
            strcpy(list[j + 1].id, list[j].id);
        }

        list[j + 1].timePeriod = auxPeriod;
        list[j + 1].timeDur = auxDur;
        list[j + 1].timeWait = auxWait;
        strcpy(list[j + 1].id, auxId);
    }
}

void separatorarguments() {

    int flags = 0;
    char *ptr;

    ptr = strtok(argList[countI+1], " ");

    while (ptr != NULL) {

        //Variável auxiliar para colocar o período e o cpu burst na struct
        if(flags == 0) {

            strcpy(list[count].id, ptr);
            flags = 1;
        }

        else if(flags == 1) {
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

    FILE *file;
    
    file = fopen(argv[1], "r");
    fscanf(file, "%d", &timeTotal);
   
    int flag = 0;
    int count = 0;
    if (file) {

        char line[1024];
        while (fgets(line, 1024, file)) {
            
            if (flag > 0) {

                if (sscanf(line, "%s %d %d", list[count].id, &list[count].timePeriod, &list[count].timeDur) == 2);
                
            }
            if (flag > 0)
                count++;

            flag = 1;
        }
    }

    int max = count;

    // selection_sort();
    insertion_sort(max);

    for (int i = 0; i < count; i++) {

        printf("%s %d %d\n", list[i].id, list[i].timePeriod, list[i].timeDur);
    }

        return 0;
}