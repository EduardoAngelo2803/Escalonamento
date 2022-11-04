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

void hold();

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
        list[j+1].timeWait = 0;
    }
    list[0].priority = 1;
}

void calcular2() {

    printf("EXECUTION BY TIME\n");

    int j = 1;

    while(timeSpent < timeTotal) {

        for (int i = 0; i < max; i++) {

            if(timeSpent == timeTotal) {
                continue;
            }
            else if((timeSpent == 0 || list[i].priority == 1) && timeSpent + list[i].timeDur <= timeTotal) {

                printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                timeSpent += list[i].timeDur;
                list[i].exeComp++;
            }

            else if ((list[i].timeDur + timeSpent) % list[i-1].timePeriod == 0 || (timeSpent + list[i].timeDur - list[i].timeWait) % list[i].timePeriod == 0)
            {
                //FULL
                printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                timeSpent += list[i].timeDur;
                list[i].exeComp++;


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
                timeSpent = list[i].timePeriod;
                list[i].lostDead++;

                
                
            }
            else if(timeSpent + list[i].timeDur > timeTotal) {
                //Variável para pegar or esto da divisão inteira
                
                printf("[%s] for %d units - K \n", list[i].id, timeTotal - timeSpent);
                timeSpent += timeTotal - timeSpent;
                list[i].killed++;
            }
          
        }
    }
}

void calcular3 () {

    timeSpent = 0;
    int auxper[count];
    int j, i, mult = 1;
    int flag = 0;
    for(j = 0; j < max; j++) {

        auxper[j] = list[j].timePeriod;       
    }

    while(timeSpent < timeTotal) {

        for(i = 0; i < max; i++) {

            if(list[i].priority == 1) {

                //FULL
                if(timeSpent == 0) {

                    printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                    timeSpent += list[i].timeDur;
                    list[i].exeComp++;
                //FULL
                }else if ((timeSpent % list[i].timePeriod) == 0) {

                    printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                    timeSpent += list[i].timeDur;
                    list[i].exeComp++;
                //KILL
                }else if(timeSpent + list[i].timeDur >= timeTotal) {

                    printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                    timeSpent = timeTotal;
                    list[i].killed++;
                    break;
                    
                }

           

            }else if(list[i].priority != 1) {
             
                //FINISH
                if (((timeSpent + list[i].timeDur) % list[i-1].timePeriod) == 0) {

                    printf("[%s] for %d units - F\n", list[i].id, list[i].timeDur);
                    timeSpent += list[i].timeDur;
                    list[i].timeWait = 0;                    
                    list[i].exeComp++;
                                
                //FINISH
                }else if (((timeSpent + list[i].timeWait) / list[i].timePeriod < 1) && list[i].timeWait > 0) {

                    printf("[%s] for %d units - F\n", list[i].id, list[i].timeDur);
                    timeSpent += list[i].timeDur;
                    list[i].timeWait = 0;
                    list[i].exeComp++;
                //HOLD
                }else if (((list[i].timeDur + timeSpent) / list[i-1].timePeriod) >= 1) {

                    if(list[i].timeWait == 0) {           

                        mult = (list[i].timeDur + timeSpent) / list[i-1].timePeriod;
                        list[i].timeWait = timeSpent + list[i].timeDur - list[i-1].timePeriod * mult;
                        printf("[%s] for %d units - H\n", list[i].id, list[i].timeDur-list[i].timeWait);
                        timeSpent = list[i-1].timePeriod; 
                        
                    }else if(((list[i].timeWait + timeSpent) / list[i].timePeriod) < 1) {

                        mult = (list[i].timeDur + timeSpent) / list[i-1].timePeriod;
                        list[i].timeWait = timeSpent + list[i].timeDur - list[i-1].timePeriod * mult;
                        printf("[%s] for %d units - H\n", list[i].id, list[i].timeDur-list[i].timeWait);
                        timeSpent = list[i-1].timePeriod; 
                    }
                
                //LOST
                }else if (((timeSpent + list[i].timeWait) % list[i].timePeriod != 0) || (timeSpent + list[i].timeDur) % list[i].timePeriod != 0) {

                    printf("[%s] for %d units - L\n", list[i].id, list[i].timePeriod - timeSpent);
                    timeSpent = list[i].timePeriod;
                    list[i].lostDead++;
                
                //KILL
                }else if(timeSpent + list[i].timeDur >= timeTotal) {

                    printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                    timeSpent = timeTotal;
                    list[i].killed++;

                }

            }else {

                printf("iddle for %d\n", list[0].timePeriod - timeSpent);

            }
            
            
            if ((timeSpent > list[i].timePeriod) && (list[i].timePeriod + auxper[i]) < timeTotal) {

                list[i].timePeriod += auxper[i];

                  
            }
                    
                    printf("\n%d %d %d", timeSpent, list[i].timeWait, list[i].timePeriod);    

        }
       
     
    }   
}

int verificarPer (int i) {
    
    int j;
    for(j = i; j > 0; j--) {
        
        if(list[i].timeWait == 0 && list[i].priority != 1) {
           
            if (timeSpent + list[i].timeDur < list[j-1].timePeriod) {
               
                return 1;
            }

        }else if ((timeSpent+list[i].timeWait) > list[j].timePeriod && list[i].priority != 1) {
            
            return 2;

        
        }else if(list[i].priority != 1){

            if((timeSpent+list[i].timeWait) < list[j-1].timePeriod)   {
                
                return 3;
            }

        }
    }

    return 0;
}

int verificarPriori (int i) {
          
    if(list[i].priority == 1) {
           
        if (timeSpent == list[i].timePeriod && (timeSpent + list[i].timeDur < timeTotal)) {
            
            return 1;

        }else if(timeSpent + list[i].timeDur > timeTotal || timeSpent + list[i].timeWait > timeTotal) {

            return 2;
        }

    }else {
        
        return 0;
    }

}

void calcular4() {
    int auxper[count];
    int i, j, aux, aux2;
    int counti = 2;

     for(j = 0; j < max; j++) {

        auxper[j] = list[j].timePeriod;       
    }

    while(timeSpent < timeTotal) {

        for(i = 0; i < max; i++) {

            if(timeSpent == 0 && list[0].timeDur > 0) {

                printf("[%s] for %d units - F \n", list[0].id, list[0].timeDur);
                timeSpent += list[0].timeDur;
                list[i].exeComp++;
                counti--;

            }else if(timeSpent > 0) {
                
                aux2 = verificarPriori(i);       
                aux = verificarPer(i);
               
                if(aux2 == 1) {

                    printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                    timeSpent += list[i].timeDur;
                    list[i].exeComp++;
                    counti--;
                    
                }else if(aux2 == 2) {

                    printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                    list[i].killed++;
                    timeSpent = timeTotal;
                    counti--;
                    break;
                    
                }else if(list[i].exeComp <= 0) {


                    if(aux == 1 && list[i].priority != 1) {

                        printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                        timeSpent += list[i].timeDur;
                        list[i].exeComp++;
                        counti--;

                    }else if(aux == 2 && list[i].priority != 1) {

                        printf("[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
                        list[i].timeWait = 0;
                        timeSpent = list[i].timePeriod;
                        list[i].lostDead++;
                        list[i].killed++;
                        counti--;
                    }else if(aux == 3 && list[i].priority != 1) {

                        timeSpent += list[i].timeWait;
                        printf("[%s] for %d units - F \n", list[i].id, list[i].timeWait);
                        list[i].timeWait = 0;
                        list[i].exeComp++;
                        counti--;

                    }else if(aux == 0 && list[i].priority != 1 && list[i].exeComp < 1) {
                    
                        list[i].timeWait = timeSpent + list[i].timeDur - list[i-1].timePeriod;
                        printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
                        timeSpent += list[i].timeDur - list[i].timeWait;
                        counti--;
           
                    }

                }else if(list[i].exeComp > 0 ) {

                    if(timeSpent == list[i].timePeriod) {

                        if(timeSpent + list[i].timeDur > timeTotal || timeSpent + list[i].timeWait > timeTotal) {
                            
                            printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                            list[i].killed++;
                            timeSpent = timeTotal;
                            counti--;
                            break;
                        }
                    }
                }
            }

            if ((timeSpent > list[i].timePeriod) && (list[i].timePeriod + auxper[i]) < timeTotal) {

                list[i].timePeriod += auxper[i];                 
            }        
        }

        if (counti == 2) {

                int firstperiod;
                int contiddle = timeSpent;
                int auxiddle = 0;
                firstperiod = list[0].timePeriod;
             
                for(int j = 0; j < max; j++) {

                    if(list[j].timePeriod < firstperiod) {

                        firstperiod = list[j].timePeriod;
                    }
                }

                while(contiddle + auxiddle < firstperiod) {

                    auxiddle++;
                
                }
                
                printf("iddle for %d units\n", auxiddle);
                timeSpent = firstperiod;        
            }

        counti = 2;
    }
}

void hold(int i) {

    if ((list[i].timeDur + timeSpent) % list[i - 1].timePeriod != 0)
    {
        int mult2;
        mult2 = (list[i].timeDur + timeSpent) / list[i - 1].timePeriod;
        list[i].timeWait = timeSpent + list[i].timeDur - (list[i-1].timePeriod * mult2);
        timeSpent = list[i-1].timePeriod * mult2;
        printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
    }
}

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
    
    calcular4();

    printf("\nLOST DEADLINES\n");
   
    for (int i = 0; i < count; i++) {

        printf("[%s] %d\n", list[i].id, list[i].lostDead);
     }

    printf("\nCOMPLETE EXECUTION\n");

    for (int i = 0; i < count; i++) {

        printf("[%s] %d\n", list[i].id, list[i].exeComp);
    }

    printf("\nKILLED\n");

    for (int i = 0; i < count; i++) {

        printf("[%s] %d\n", list[i].id, list[i].killed);
    }


         return 0;
         
}