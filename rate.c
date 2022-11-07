#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 64
#define BUFFER 100

int timeTotal;
int count = 0;
int max;
int timeSpent;
int count2 = 0;
int counti = 2;
int flagKill = 0;
FILE *f;
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
    int flagKill;

} Process;

Process list[SIZE];

void insertion_sort(int max) {

    int i, j, auxPeriod, auxDur, auxWait, auxexComp, auxlostDead, auxKilled, auxFlagKill;
    char auxId[SIZE];

    for (i = 1; i < max; i++)
    {

        auxPeriod = list[i].timePeriod;
        auxDur = list[i].timeDur;
        auxWait = list[i].timeWait;
        auxexComp = list[i].exeComp;
        auxlostDead = list[i].lostDead;
        auxKilled = list[i].killed;
        auxFlagKill = list[i].flagKill;
        strcpy(auxId, list[i].id);

        for (j = i - 1; j >= 0 && auxPeriod < list[j].timePeriod; j--) {

            list[j + 1].timePeriod = list[j].timePeriod;
            list[j + 1].timeDur = list[j].timeDur;
            list[j + 1].timeWait = list[j].timeWait;
            list[j + 1].exeComp = list[j].exeComp;
            list[j + 1].lostDead = list[j].lostDead;
            list[j + 1].killed = list[j].killed;
            list[j + 1].flagKill = list[j].flagKill;
            strcpy(list[j + 1].id, list[j].id);
        }

        list[j + 1].timePeriod = auxPeriod;
        list[j + 1].timeDur = auxDur;
        list[j + 1].timeWait = auxWait;
        list[j + 1].exeComp = auxexComp;
        list[j + 1].lostDead = auxlostDead;
        list[j + 1].killed = auxKilled;
        list[j + 1].flagKill = auxFlagKill;
        strcpy(list[j + 1].id, auxId);
        list[j+1].timeWait = 0;
    }
    list[0].priority = 1;

    for(int i = 0; i < max; i++) {

        list[i].flagKill = 0;
    }
}

int verHold(int i) {

    int flag = max-1;
    timeSpent;

    for(int j = i; j > 0; j--) {

        if(list[i].timeWait == 0) {

            if(list[i].timeDur + timeSpent > list[j-1].timePeriod) {
            
                flag = j-1;;
            }

        }else {

            if(list[i].timeWait + timeSpent > list[j-1].timePeriod) {
            
                flag = j-1;;
            }

        }
    }
   
    return flag;
}

int verMenorPer (int i) {
    int pos = i;

    for (int j = i; j > 0; j--) {

        if(list[i].timePeriod > list[j-1].timePeriod) {

            pos = j - 1;

        }
    }
    return pos;
}

int verificarPer (int i) {
    
    int j, flagPer = 0;
    
    for(j = i; j > 0; j--) {
       
        if(max == 2) {
            
            if(list[i].timeWait == 0 && list[i].priority != 1) {
            
                if (timeSpent + list[i].timeDur < list[j-1].timePeriod && timeSpent + list[i].timeDur <= timeTotal) {
                
                    return 1;
                }

            }else if (timeSpent + list[i].timeWait > list[j].timePeriod) {

                return 2;

            }else if(list[i].priority != 1){

                if (((timeSpent+list[i].timeWait) < list[i-1].timePeriod) && ((timeSpent + list[i].timeWait) < list[i].timePeriod) && timeSpent + list[i].timeWait <= timeTotal)   {
                    
                    return 3;
                }

            }else if(timeSpent + list[i].timeDur > timeTotal || timeSpent + list[i].timeWait > timeTotal) {

                return 4;

            }else {

                return 0;
            }

        }else if (max > 2) {
            
            if(timeSpent == list[j-1].timePeriod) {
                
                flagPer = 5;

            }
            if (flagPer != 5) {
          
                if(list[i].timeWait == 0 && list[i].priority != 1) {
                
                    if(timeSpent + list[i].timeDur > list[j-1].timePeriod) {
                        
                        flagPer = 0;

                    }else if (timeSpent + list[i].timeDur <= list[j-1].timePeriod) {
                        
                        flagPer = 1;
                    }

                }else if (timeSpent + list[i].timeWait > list[j-1].timePeriod) {
                    
                    flagPer = 0;

                }else if (timeSpent + list[i].timeWait > list[i].timePeriod) {
                    
                    flagPer = 2;

                }else if(list[i].priority != 1){

                    if((timeSpent+list[i].timeWait) <= list[j-1].timePeriod && timeSpent + list[i].timeWait <= list[i].timePeriod)   {
                        
                        flagPer = 3;
                    }

                }else if(timeSpent + list[i].timeDur > timeTotal || timeSpent + list[i].timeWait > timeTotal) {

                    flagPer = 4;

                }else {
                   
                    flagPer = 0;
                }
            }
        }
    }

    if(flagPer == 1) {
        return 1;
    }else if(flagPer == 2) {
        return 2;
    }else if(flagPer == 3) {
        return 3;
    }else if(flagPer == 4) {
        return 4;
    }else if(flagPer == 0){
        return 0;
    }else if(flagPer == 5){
        return 5;
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

void calcProcess(int i) {

    int aux = verificarPer(i);
    printf(" %d ", aux);
    if(aux == 1) {

        printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
        fprintf(f, "[%s] for %d units - F \n", list[i].id, list[i].timeDur);
        list[i].exeComp++;
        timeSpent += list[i].timeDur;
        
    }else if(aux == 4) {
        
        printf("[%s] for %d units - K\n", list[i].id, timeTotal-timeSpent);
        fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
        list[i].killed++;
        timeSpent = timeTotal;
        counti--;
        
    }else if (aux == 2) {

        printf("[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
        fprintf(f, "[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
        list[i].timeWait = 0;
        timeSpent = list[i].timePeriod;
        list[i].lostDead++;
        counti--;

    }else if (aux == 3) {

        timeSpent += list[i].timeWait;
        printf("[%s] for %d units - F \n", list[i].id, list[i].timeWait);
        fprintf(f, "[%s] for %d units - F \n", list[i].id, list[i].timeWait);
        
        list[i].timeWait = 0;
        list[i].exeComp++;
        counti--;

    }else if (aux == 0) {

        list[i].timeWait = timeSpent + list[i].timeDur - list[i-1].timePeriod;
        printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
        fprintf(f, "[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
        timeSpent += list[i].timeDur - list[i].timeWait;
        counti--;
    }
}

void VerKilled (int i) {

    if(max == 2) {

        if (i == 0) {

            i = 1;

            if(list[i].timeWait + timeSpent == timeTotal || list[i].timeDur + timeSpent == timeTotal) {

                list[i].killed++;
            
            }
        }

    }else if (max > 2) {

        int c = max-1;

        for(int j = i; j > 0; j--) {

            if(list[j].timePeriod > timeTotal) {

                c--;

            }
            if(c == 0) {

                if(timeSpent + list[i].timeDur > timeTotal) {

                    list[i].flagKill = 1;

                }
            }
        }
    }
}

void calcular4() {

    int auxper[count];
    int i, j, aux, aux2, count2 = 0;
     
    int flag = 0;
    f = fopen("rate_leam.out", "w");

     for(j = 0; j < max; j++) {

        auxper[j] = list[j].timePeriod;       
    }

    printf("EXECUTION BY RATE\n");
    fprintf(f, "EXECUTION BY RATE\n");

    while(timeSpent < timeTotal) {

        for(i = 0; i < max; i++) {

            if(timeSpent == 0 && list[0].timeDur > 0) {
                //FULL
                printf("[%s] for %d units - F \n", list[0].id, list[0].timeDur);
                fprintf(f, "[%s] for %d units - F \n", list[0].id, list[0].timeDur);
                timeSpent += list[0].timeDur;
                list[i].exeComp++;
                flag = 1;
                counti--;

            }else if(timeSpent > 0) {
                

                if(max == 2) {

                    aux2 = verificarPriori(i);       
                    aux = verificarPer(i);
                    
                    if(aux2 == 1) {
                        //FULL
                        printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                        fprintf(f, "[%s] for %d units - F \n", list[0].id, list[0].timeDur);
                        timeSpent += list[i].timeDur;
                        list[i].exeComp++;
                        flag = 1;
                        counti--;
                        
                    }else if(aux2 == 2) {
                        //KILL
                        printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                        fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                        list[i].killed++;
                        timeSpent = timeTotal;
                        counti--;
                        VerKilled(i);
                        break;
                    
                    }else if(list[i].exeComp <= 0) {
                        
                        if(timeSpent + list[i].timeDur > timeTotal || timeSpent + list[i].timeWait > timeTotal){
                            
                            if(list[i].timeWait == 0 && timeSpent != list[i].timePeriod) {
                                
                                if (list[i].timePeriod >= timeTotal && list[i-1].timePeriod >= timeTotal) {

                                    printf("[%s] for %d units - K\n", list[i].id, timeTotal-timeSpent);
                                    fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                                    list[i].killed++;
                                    timeSpent = timeTotal;
                                    counti--;
                                    break;

                                } else if (timeSpent + list[i].timeDur < list[i-1].timePeriod && timeSpent + list[i].timeDur < list[i].timePeriod) {

                                    printf("[%s] for %d units - K\n", list[i].id, timeTotal-timeSpent);
                                    fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                                    list[i].killed++;
                                    timeSpent = timeTotal;
                                    counti--;
                                    break;
                                }
      
                            }else if(list[i].timePeriod > timeTotal && list[i].timePeriod > timeTotal) {

                                printf("[%s] for %d units - K\n", list[i].id, timeTotal-timeSpent);
                                fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                                list[i].killed++;
                                timeSpent = timeTotal;
                                counti--;
                                break;

                            }else if ((timeSpent + list[i].timeWait < list[i-1].timePeriod) && (timeSpent + list[i].timeWait < list[i].timePeriod)) {
                               
                                printf("[%s] for %d units - K\n", list[i].id, timeTotal-timeSpent);
                                fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                                list[i].killed++;
                                timeSpent = timeTotal;
                                counti--;

                            }

                        }if(aux == 1 && list[i].priority != 1) {
                            //FULL                      
                            printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                            fprintf(f, "[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                            timeSpent += list[i].timeDur;
                            list[i].exeComp++;
                            counti--;

                        }else if(aux == 2 && list[i].priority != 1) {
                            //LOSS
                            printf("[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
                            fprintf(f, "[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
                            list[i].timeWait = 0;
                            timeSpent = list[i].timePeriod;
                            list[i].lostDead++;
                            counti--;

                        }else if(aux == 3 && list[i].priority != 1) {
                            //FULL
                            
                            timeSpent += list[i].timeWait;                        
                            printf("[%s] for %d units - F \n", list[i].id, list[i].timeWait);
                            fprintf(f, "[%s] for %d units - F \n", list[i].id, list[i].timeWait);
                            list[i].timeWait = 0;
                            list[i].exeComp++;
                            counti--;

                        }else if(aux == 0 && list[i].priority != 1) {
                            //HOLD
                            
                           if(list[i].timeWait > 0){

                                printf("aquiiii");
                                list[i].timeWait = timeSpent + list[i].timeWait - list[i-1].timePeriod;                    
                                printf("[%s] for %d units - H \n", list[i].id, list[i-1].timePeriod - timeSpent);
                                fprintf(f, "[%s] for %d units - H \n", list[i].id, list[i-1].timePeriod - timeSpent);
                                list[i].timeWait = timeSpent + list[i].timeWait - list[i-1].timePeriod; 
                            
                                timeSpent = list[i-1].timePeriod;
                                counti--;

                            } else if(list[i].timeWait == 0) {
                                printf("aqui");
                                list[i].timeWait = list[i].timeDur - (list[i-1].timePeriod - timeSpent);
                                printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
                                fprintf(f, "[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);                         
                                timeSpent += list[i].timeDur - list[i].timeWait;
                                counti--;
                                printf("%d", list[i].timeWait);

                            }            
                        }

                    }else if(list[i].exeComp > 0 ) {
                        
                        if(list[i].timeWait == 0) {

                            if (timeSpent >= list[i].timePeriod && (timeSpent + list[i].timeDur < timeTotal)) {
                                            
                                calcProcess(i);
                                counti--;
                            }
                        //Quer dizer que ele já executou, e precisa executar novamente depois do processo de maior prioridade  
                        }else if (list[i].timeWait > 0) {

                            calcProcess(i);
                            counti--;
                        }
                    }

                }else if (max > 2) {

                    aux2 = verificarPriori(i);       
                    aux = verificarPer(i);

                    if(aux2 == 1) {
                        //FULL
                        printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                        fprintf(f, "[%s] for %d units - F \n", list[0].id, list[0].timeDur);
                        timeSpent += list[i].timeDur;
                        list[i].exeComp++;
                        flag = 1;
                        counti--;
                        
                    }else if(aux2 == 2 && list[i].exeComp < 1) {
                        //KILL
                        printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                        fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                        list[i].killed++;
                        timeSpent = timeTotal;
                        counti--;
                        break;    


                    }else if(list[i].exeComp <= 0) {

                        if (aux == 5) {

                            break;

                        }else if(aux == 1 && list[i].priority != 1) {
                            //FULL
                        
                            printf("[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                            fprintf(f, "[%s] for %d units - F \n", list[i].id, list[i].timeDur);
                            timeSpent += list[i].timeDur;
                            list[i].exeComp++;
                            counti--;

                        }else if(aux == 2 && list[i].priority != 1) {
                            //LOSS
                            
                            printf("[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
                            fprintf(f, "[%s] for %d units - L \n", list[i].id, list[i].timePeriod - timeSpent);
                            list[i].timeWait = 0;
                            timeSpent = list[i].timePeriod;
                            list[i].lostDead++;
                            counti--;

                        }else if(aux == 3 && list[i].priority != 1) {
                            //FULL
                            
                            timeSpent += list[i].timeWait;                        
                            printf("[%s] for %d units - F \n", list[i].id, list[i].timeWait);
                            fprintf(f, "[%s] for %d units - F \n", list[i].id, list[i].timeWait);
                            list[i].timeWait = 0;
                            list[i].exeComp++;
                            counti--;


                        }else if(aux == 0 && list[i].priority != 1) {
                            //HOLD
                            
                            if(list[i].timeWait == 0) {

                                int auxHold = verHold(i);
                                list[i].timeWait = timeSpent + list[i].timeDur - list[auxHold].timePeriod;
                                printf("[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);
                                fprintf(f, "[%s] for %d units - H \n", list[i].id, list[i].timeDur - list[i].timeWait);                         
                                timeSpent += list[i].timeDur - list[i].timeWait;
                                counti--;

                            }else {

                                int auxHold = verHold(i);
                        
                                printf("[%s] for %d units - H \n", list[i].id, list[auxHold].timePeriod - timeSpent);
                                fprintf(f, "[%s] for %d units - H \n", list[i].id, list[auxHold].timePeriod - timeSpent);
                                list[i].timeWait = list[i].timeWait - (list[auxHold].timePeriod - timeSpent);
                            
                                timeSpent = list[auxHold].timePeriod;
                                counti--;
                            }           
                        }

                    }else if(list[i].exeComp > 0 ) {
                        
                        if(list[i].timeWait == 0) {

                            if(timeSpent >= list[i].timePeriod && (timeSpent + list[i].timeDur > timeTotal)) {
                                
                                printf("[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                                fprintf(f, "[%s] for %d units - K \n", list[i].id, timeTotal-timeSpent);
                                list[i].killed++;
                                timeSpent = timeTotal;
                                counti--;
                                break; 

                            }if (timeSpent >= list[i].timePeriod && (timeSpent + list[i].timeDur < timeTotal)) {
                                         
                                calcProcess(i);
                                counti--;
                            }
                        //Quer dizer que ele já executou, e precisa executar novamente depois do processo de maior prioridade  
                        }else if (list[i].timeWait > 0) {
                                
                            calcProcess(i);
                            counti--;
                        }
                   }
                }
            }

            if (timeSpent >= list[i].timePeriod && max == 2)  {
                
                if(list[i].timePeriod + auxper[i] <= timeTotal) {

                    list[i].timePeriod += auxper[i]; 

                }else if (list[i].timePeriod + auxper[i] > timeTotal) {

                    list[i].timePeriod += auxper[i];
                }    

            }else if (max > 2) {

                if (timeSpent > list[i].timePeriod) {

                    if(list[i].timePeriod + auxper[i] <= timeTotal) {

                        list[i].timePeriod += auxper[i]; 

                    }else if (list[i].timePeriod + auxper[i] > timeTotal) {

                        list[i].timePeriod += auxper[i];
                    }  

                }
            }   

            if (counti == 2 && i == max-1) {

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
                
                printf("idle for %d units\n", auxiddle);
                fprintf(f, "idle for %d units\n", auxiddle);
                timeSpent = firstperiod;        
            }
            
        }

        
        flag = 0;
        counti = 2;
        count2++;
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

        char *line[1024];
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
    fprintf(f, "\nLOST DEADLINES\n");
  
    for (int i = 0; i < max; i++) {

        printf("[%s] %d\n", list[i].id, list[i].lostDead);
        fprintf(f, "[%s] %d\n", list[i].id, list[i].lostDead);
     }

    printf("\nCOMPLETE EXECUTION\n");
    fprintf(f, "\nCOMPLETE EXECUTION\n");

    for (int i = 0; i < max; i++) {

        printf("[%s] %d\n", list[i].id, list[i].exeComp);
        fprintf(f, "[%s] %d\n", list[i].id, list[i].exeComp);
        
    }

    printf("\nKILLED\n");
    fprintf(f, "\nKILLED\n");

    for(int i = 0; i < max; i++) {

        if(timeSpent >= timeTotal && list[i].timePeriod == timeTotal && list[i].killed < 1) {

            list[i].killed++;
        }
    }

    for (int i = 0; i < max; i++) {

        if (i == max-1) {
            printf("[%s] %d\n", list[i].id, list[i].killed);
            fprintf(f, "[%s] %d", list[i].id, list[i].killed);
            break;
        }
        printf("[%s] %d\n", list[i].id, list[i].killed);
        fprintf(f, "[%s] %d\n", list[i].id, list[i].killed);
        
    }

    return 0;
         
}