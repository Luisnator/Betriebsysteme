#include <stdio.h>
#include "lists.c"
#include "global.c"
#include "lists.h"
#include "global.h"

typedef struct Process
{
    LIST_NODE_HEADER(struct Process);
    char name;
    int seconds;
    int prio;
} Process;
typedef struct Processlist{
    LIST_HEADER(Process);
};
struct Processlist Processlist;
Process *process;
void freeDataNode(Process *process,void *userData)
{

}
int compareShortesJobFirst(Process *process, Process *process1, void *dummy)
{
    if(process->seconds < process1->seconds)
    {
        return -1;
    }
    else if(process->seconds > process1->seconds)
    {
        return +1;
    }
    else
    {
        return 0;
    }
}
int comparePrio(Process *process, Process *process1, void *dummy)
{
    if(process->prio > process1->prio)
    {
        return -1;
    }
    else if(process->prio < process1->prio)
    {
        return +1;
    }
    else
    {
        return 0;
    }
}
int main() {
    List_init(&Processlist);
    printf("Hello, World!\n");
    init();
    printf("FirstComeFirstServe: \n");
    firstComeFirstServe();
    init();
    printf("\nShortestJobFirst: \n");
    shortestJobFirst();
    init();
    printf("\nPrioJobFirst: \n");
    prioJobFirst();
    init();
    printf("\nRoundRobin: \n");
    roundRobin();
    return 0;
}
void init(){
    List_done(&Processlist,(ListNodeFreeFunction)freeDataNode,NULL);
    fillprocess('A',30,2);
    fillprocess('B',20,1);
    fillprocess('C',25,5);
    fillprocess('D',28,4);
    fillprocess('E',18,3);

}
void fillprocess(char name, int seconds, int prio)
{
    process = LIST_NEW_NODE(Process);
    process->name=name;
    process->seconds=seconds;
    process->prio=prio;
    List_append(&Processlist,process);
}
void firstComeFirstServe()
{
    long count = List_count(&Processlist);
    double mvz = 0;
    long time = 0;
    for(int i = 0 ; i < count;i++)
    {
        process = List_getFirst(&Processlist);
        mvz += ((double)process->seconds * (double)(count-i));
        time += process->seconds;
        printf("%c wurde abgearbeitet(aktuelle Zeit: %d Minuten). \n",process->name,time);
    }
    mvz = mvz / count;
    printf("Mittlere Verweilszeit: %fs \n",mvz*60);
}
void shortestJobFirst()
{
    List_sort(&Processlist,(ListNodeCompareFunction)compareShortesJobFirst,NULL);
    firstComeFirstServe();
}
void prioJobFirst()
{
    List_sort(&Processlist,(ListNodeCompareFunction)comparePrio,NULL);
    firstComeFirstServe();
}
void roundRobin()
{
    long count = List_count(&Processlist);
    double mvz = 0;
    int temp = 0;
    int temp2 = 0;
    while(!List_isEmpty(&Processlist))
    {
        process = List_getFirst(&Processlist);
        process->seconds--;
        temp++;
        printf("Es wurde 1 Minute an %c gearbeitet \n", process->name);
        if(process->seconds <= 0)
        {
              mvz += temp * (count-temp2);
              temp2++;
              temp = 0;
              printf("Prozess %c wurde beendet \n", process->name);
        }
        else
        {
            List_append(&Processlist,process);
        }
    }
    mvz = mvz / count;
    printf("Mittlere Verweilszeit: %fs \n",mvz *60);
}
void roundRobinPrio()
{

}
