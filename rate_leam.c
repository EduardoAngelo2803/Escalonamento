#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3
#define BUFFER 100

int timeTotal;
int count = 0;
int max;
int timeSpent;
int count2 = 0;

typedef struct {

    char id[SIZE];
    int timePeriod;
    int timeDur;
    int timeWait;
    int exeComp;
    int lostDead;
    int killed;
    int priority;

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
    list[0].priority = 1;
}

void full () {

    int i = 0;

    if ((list[i].timeDur + list[i + 1].timeDur) < list[i].timePeriod || (timeSpent + list[i].timeDur - list[i].timeWait) % list[i].timePeriod == 0)
    {
        printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
        timeSpent += list[i].timeDur;

    }
}

void calcular() {

    timeSpent = 0;

    printf("EXECUTION BY RATE\n");

    while(timeSpent <= timeTotal) {

        full();  
        iddle();
        lost();
        kill();
        printf("%d\n\n", timeSpent);
        break;
        /*
        printf("[%s] for %d units - F \n", list[0].id, list[0].timeDur);

        timeSpent += list[0].timeDur;
        list[0].exeComp++;

        //Caso o t2 consiga completar seu processo inteiro
        if (list[0].timeDur + list[1].timeDur < list[0].timePeriod) {

            printf("[%s] for %d units - F \n", list[1].id, list[1].timeDur);
            list[1].exeComp++;
            timeSpent += list[1].timeDur;

            //Ele vai rodar apenas pela metade, Half
            if(list[0].timeDur + list[1].timeDur > list[0].timePeriod){

                printf("[%s] for %d units - H \n", list[1].id, list[0].timePeriod - list[0].timeDur);
                timeSpent += list[0].timePeriod - list[0].timeDur;

                list[1].timeWait = list[0].timePeriod - list[0].timeDur;

                //Caso o t1 tenha encerrado, o t2 assume novamente
                if (list[1].timePeriod > timeSpent){

                    printf("[%s] for %d units - F \n", list[1].id, list[1].timeWait);
                    list[1].exeComp++;
                    timeSpent += list[1].timeWait;

                }else {

                    list[1].lostDead++;

                    //Caso o período de t1 chegue e ele precise assumir a prioridade
                    if(list[0].timePeriod == timeSpent || timeSpent%list[0].timePeriod == 0) {

                        printf("[%s] for %d units - F \n", list[0].id, list[0].timeDur);
                        list[0].exeComp++;
                    }
                    //Caso os dois processos acabem sua execução, mas nenhum deles tenha chegado para executar novamente
                    if(list[0].exeComp >=1  && list[1].exeComp >= 1 && list[0].timePeriod > timeSpent) {

                        printf("iddle for %d units\n", list[0].timePeriod - timeSpent);

                    }
                }
            }

            if (list[0].exeComp >= 1 && list[1].exeComp >= 1 && list[0].timePeriod%timeSpent != 0) {

                printf("iddle for %d units\n", list[0].timePeriod - timeSpent);
                timeSpent += (list[0].timePeriod - timeSpent);

            }

        }else if (list[0].timeDur + list[1].timeDur > list[0].timePeriod) {

            printf("[%s] for %d units - H\n", list[1].id, list[0].timePeriod - list[0].timeDur);
            timeSpent += list[0].timePeriod - list[0].timeDur;

            list[1].timeWait = list[0].timePeriod - list[0].timeDur;

            if(list[0].timePeriod*2 > timeSpent + list[0].timeDur) {

                printf("[%s] for %d units - F\n", list[0].id, list[0].timeDur);
                timeSpent += list[0].timeDur;
            }
        }

        }

        */
    }
}

void calcular2() {

    printf("EXECUTION BY TIME\n");

    int j = 1;

    while(timeSpent < timeTotal) {


        if(count2 > 7) {
            break;
        }
        for (int i = 0; i < max; i++)
        {

            if(timeSpent == timeTotal) {
                continue;
            }
            else if((timeSpent == 0 || list[i].priority == 1) && timeSpent + list[i].timeDur <= timeTotal) {

                printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                timeSpent += list[i].timeDur;
            }

            else if ((list[i].timeDur + timeSpent) % list[i-1].timePeriod == 0 || (timeSpent + list[i].timeDur - list[i].timeWait) % list[i].timePeriod == 0)
            {
                //FULL
                printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                timeSpent += list[i].timeDur;

            }
            else if (((list[i].timeDur + timeSpent) % list[i-1].timePeriod != 0) && (timeSpent + list[i].timeWait) <
            list[i].timePeriod)
            {
                int mult2;

                // IDDLE
                mult2 = (list[i].timeDur + timeSpent) / list[i-1].timePeriod;
                list[i].timeWait = timeSpent + list[i].timeDur - (list[i-1].timePeriod * mult2);
                timeSpent = list[i-1].timePeriod * mult2;
                printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
                
            }
            else if ((timeSpent + list[i].timeDur) % list[i].timePeriod != 0)
            {
                int mult;
                // LOST
                
                printf("[%s] for %d units - L \n", list[i].id, (timeSpent + list[i].timeWait) % list[i].timePeriod);
                timeSpent += timeSpent + list[i].timeWait % list[i].timePeriod;
                mult = (list[i].timeDur + timeSpent) / list[i - 1].timePeriod;
                timeSpent = mult * list[i].timePeriod;
                
            }
            else if(timeSpent + list[i].timeDur > timeTotal) {
                //Variável para pegar or esto da divisão inteira
                
                printf("[%s] for %d units - K \n", list[i].id, timeTotal - timeSpent);
                timeSpent += timeTotal - timeSpent;
            }
           // printf("%d\n", timeSpent);
        }
        count2++;
    }

}
void iddle(int i) {

    if ((list[i].timeDur + timeSpent) % list[i - 1].timePeriod != 0)
    {
        int mult2;
        mult2 = (list[i].timeDur + timeSpent) / list[i - 1].timePeriod;
        list[i].timeWait = timeSpent + list[i].timeDur - (list[i-1].timePeriod * mult2);
        timeSpent = list[i-1].timePeriod * mult2;
        printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
    }
}

void lost() {

    int i;

    if((timeSpent + list[i].timeDur) % list[i].timePeriod == 0) {

        printf("[%s] for %d units - L \n", list[i].id, timeTotal - timeSpent);
        timeSpent += timeTotal - timeSpent;
    }
}

void kill() {

    //lost();
}

/*void calcPriority() {

    if(){}

     else if(){}

      else if(){}

      else if(){}
}
*/



int main(int argc, char **argv) {

    if(argc <= 1) {

        printf("no arguments entered! Please input one! Ex: ./rate 'namefile'\n");
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

    max = count;

    insertion_sort(max);
    
    calcular2();

    
    /* for (int i = 0; i < count; i++) {

         printf("%s %d %d\n", list[i].id, list[i].timePeriod, list[i].timeDur);
     }

         return 0;
         */
}