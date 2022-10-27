#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 3



typedef struct {

    char id[SIZE];
    int timeDur;
    int timeExec;
    int timeWait;

} Process;

Process list[SIZE];

void calcular () {

    

    printf("Processo 1: \n");

    scanf("%19[0-9a-zA-Z]", list[0].id);
    scanf("%d", &list[0].timeExec);
    scanf("%d", &list[0].timeWait);

    printf("Processo 2: \n");
   // fgets(list[1].id, 2, stdin);
    scanf("%d", &list[1].timeExec);
    scanf("%d", &list[1].timeWait);
}

int main () {

    calcular();

    printf("%s\n", list[0].id);

    return 0;
}