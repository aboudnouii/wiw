#include<stdio.h>
#include <stdlib.h>
struct PDT
{
    int state; // 0-free 1-not free
    int size;
    int num;
};
struct Process
{
    int size;
    int num;
};
void read(struct PDT P[],struct Process N[],int npt,int npr)
{
    for(int i = 0; i < npt; i++) { //reading partition info
        printf("Enter the size of partition %d: \n", i+1);
        scanf("%d", &P[i].size);
        P[i].state = 0; // Set state to free
        P[i].num=i+1;
    }
        for(int i = 0; i < npr; i++)//reading processes info
        {
        printf("enter the size of process %d: \n", i+1);
        scanf("%d", &N[i].size);
        N[i].num=i+1;
    }
}
void displayPDT(struct PDT P[] ,int npt)
{
    printf("---------------------------------------------------\n");
    printf("PDT :\n");
    for (int i = 0; i < npt; i++)
    {
            printf("---------------------------------------------------\n");
            printf("P Number : %d\n",P[i].num);
            printf("Size : %d\n",P[i].size);
            printf("Status : ", P[i].state == 0 ? "Free" : "Allocated");
            printf("\n");
            printf("---------------------------------------------------\n");
    }
}

void deallocation(struct PDT P[]) {
    int z;
    printf("enter the number of partition that you want to delete: ");
    scanf("%d", &z);
    if(P[z-1].state != 0) {
        P[z-1].state = 0;
        P[z-1].num = -1;
    } else {
        printf("Partition is already free.\n");
    }
}
void firstFit(struct PDT partitions[], int m,struct Process processes[], int n,int allocation[])
{   int x,z=0;
    for (int i = 0; i < n; i++)
        allocation[i] = -1; // Initialize allocation array

    for (int i = 0; i < n; i++)//first fit algorithm
    {
        for (int j = 0; j < m; j++)
        {
            if (partitions[j].size >= processes[i].size && partitions[j].state == 0)
            {//fill pdt
                partitions[j].num=processes[i].num;
                allocation[i] = j;
                partitions[j].state = 1; // Mark partition as allocated
            x=partitions[j].size-processes[i].size;
            z=+x;
            printf("\ninternal fregmantation of P %d = %d\n",j+1,x);
                break;
            }
        }
    }
    printf("external fregmantation = %d\n\n",z);

    printf("\nProcess No.\tProcess Size\tBlock No.\n"); //display processes status after do algorithm
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processes[i].size);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
// Best Fit memory allocation function
void bestFit(struct PDT partitions[], int m,struct Process processes[], int n,int allocation[])
{
    int x,z=0;
    for (int i = 0; i < n; i++)
        allocation[i] = -1; // Initialize allocation array

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;//temp of indes of best case
        for (int j = 0; j < m; j++)
        {
            if (partitions[j].size >= processes[i].size && partitions[j].state == 0)
            {
                if (bestIdx == -1 || partitions[j].size < partitions[bestIdx].size)//see best fregmantation of partition and process
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)//fill pdt
        {
            partitions[bestIdx].num=processes[i].num;
            allocation[i] = bestIdx;
            partitions[bestIdx].state = 1; // Mark partition as allocated
            x=partitions[bestIdx].size-processes[i].size;
            z=+x;
            printf("\ninternal fregmantation of P %d = %d\n",bestIdx+1,x);
        }
    }
    printf("external fregmantation = %d\n\n",z);
    printf("\nProcess No.\tProcess Size\tBlock No.\n");//display processes status after do algorithm
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processes[i].size);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
int main()
{
    int npt;
    int npr;
    int choix;
    printf("enter the number of partitions: \n");
    scanf("%d", &npt);
    struct PDT t[npt];
    int allocation[npt];
    printf("enter the number of processes: \n");
    scanf("%d", &npr);
    struct Process s[npr];
    read(t,s,npt,npr);
    printf("\nMENU :\n");
    printf("---------------------------------------------------\n");
    int x;
       do{
    printf("FirsFit : 1\n");
    printf("BestFit : 2\n");
    printf("Display PDT : 3\n");
    printf("Deallocate Partition : 4\n");
    printf("Exit : 5\n");
    printf("Enter your choice : \n");
    scanf(" %d",&x);
    switch(x)
    {
        case 1:
                firstFit(t,npt,s,npr,allocation);
            break;
            case 2:
                bestFit(t,npt,s,npr,allocation);
                break;
            case 3:
                displayPDT(t,npt);
                break;
            case 4:
                deallocation(t);
                break;
            default:
                exit(0);
    }
    }while(1);
    return 0;
}
