#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3
#define BUFFER 100

int timeTotal;
int count = 0;

typedef struct
{

    char id[SIZE];
    int timePeriod;
    int timeDur;
    int timeWait;
    int exeComp;
    int lostDead;
    int killed;

} Process;

Process list[SIZE];

void insertion_sort(int max) {

    int i, j, auxPeriod, auxDur, auxWait, auxexComp, auxlostDead, auxKilled;
    char auxId[SIZE];

    for (i = 1; i < max; i++)
    {

        auxPeriod = list[i].timePeriod;
        auxDur = list[i].timeDur;
        auxWait = list[i].timeWait;
        auxexComp = list[i].exeComp;
        auxlostDead = list[i].lostDead;
        auxKilled = list[i].killed;

        strcpy(auxId, list[i].id);
        for (j = i - 1; j >= 0 && auxPeriod < list[j].timePeriod; j--)
        {

            list[j + 1].timePeriod = list[j].timePeriod;
            list[j + 1].timeDur = list[j].timeDur;
            list[j + 1].timeWait = list[j].timeWait;
            list[j + 1].exeComp = list[j].exeComp;
            list[j + 1].lostDead = list[j].lostDead;
            list[j + 1].killed = list[j].killed;
            strcpy(list[j + 1].id, list[j].id);
        }

        list[j + 1].timePeriod = auxPeriod;
        list[j + 1].timeDur = auxDur;
        list[j + 1].timeWait = auxWait;
        list[j + 1].exeComp = auxexComp;
        list[j + 1].lostDead = auxlostDead;
        list[j + 1].killed = auxKilled;
        strcpy(list[j + 1].id, auxId);
    }
}

void calcular() {


    printf("[%s] for %d units - F \n", list[0].id, list[0].timeDur);

    timeTotal -= list[0].timeDur;
    list[0].exeComp++;

        if(list[0].timeDur+list[1].timeDur < list[0].timePeriod) {

        printf("[%s] for %d units - F \n", list[1].id, list[1].timeDur);
        list[1].exeComp++;

        }else {

            printf("[%s] for %d units - H \n", list[1].id, list[0].timePeriod - list[0].timeDur);
            timeTotal -= list[0].timePeriod - list[0].timeDur;
        }


}
int main (int argc, char** argv) {

    if(argc <= 1) {

        printf("no argList entered! Please input one! Ex: ./rate 'namefile'\n");
        exit(EXIT_FAILURE);

    }else if (argc > 2) {

        printf("Many arguments entered! Please input just one, Ex: ./rate 'namefile'\n");
        exit(EXIT_FAILURE);
    }

    FILE *file;

    file = fopen(argv[1], "r");
    fscanf(file, "%d", &timeTotal);
   
    int flag = 0;
    int count = 0;
    if (file) {

        char line[1024];
        while (fgets(line, 1024, file)) {
            //Condicional para ignorar a primeira linha, que é o tempo total
            if (flag > 0) {

                if (sscanf(line, "%s %d %d", list[count].id, &list[count].timePeriod, &list[count].timeDur) == 2);
                
            }
            if (flag > 0)
                count++;

            flag = 1;
        }
    }

    int max = count;

    insertion_sort(max);
    
    calcular();
    
   /* for (int i = 0; i < count; i++) {

        printf("%s %d %d\n", list[i].id, list[i].timePeriod, list[i].timeDur);
    }

        return 0;
        */
}