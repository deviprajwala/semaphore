#include<stdio.h>
#define queue_size 10

int in=0,out=0;

struct semaphore
{
 int value;//number of process waiting on the semaphore
 int q[queue_size];//processes present in the queue with two pointers
};
typedef struct semaphore *semaphore;

semaphore getsema();
int wait(semaphore s,int p);
int signal(semaphore s);

semaphore getsema()
{
 semaphore s;
 s=(semaphore)malloc(sizeof(struct semaphore));
 s->value=0;
 //s->q[queue_size]=0;
 return s;
}

int wait(semaphore s,int p)
{
  s->value--;
  if(s->value<0)
  {
    s->q[in]=p;
    printf("\nprocess %d is added to list of semaphores and blocked\n",p); 
  }
 return in;
}

int signal(semaphore s)
{
 int p;
 s->value++;
 if(s->value<=0)
 {
   p=s->q[out];
   s->q[out]=0;
   out++;
   printf("process %d is removed from the list of semaphores and waked\n",p); 
 }
 return out;
}

int main()
{
 semaphore s;
 s=getsema();
 int process1=1,processs2=2,c=1,p,q;
 while(c==1)
 {
  printf("There are two processes, enter the process to be executed:1 or 2\n");
  scanf("%d",&p);
  printf("In order to view the operation of semaphore enter the other process\n");
  scanf("%d",&q);
  printf("\nThe first process entered is:%d\nThe second process entered is:%d\n",p,q);
  in=wait(s,q);
  printf("Process %d waits until process %d completes its execution\n",q,p);
  printf("\n-------------------------------------------\n");
  printf("process %d is executing.......\n",p);
  printf("\n-------------------------------------------\n");
  printf("Execution of process %d is completed \n",p);
  out=signal(s);
  
  printf("\n-------------------------------------------\n");
  printf("process %d is executing.......\n",q);
  printf("\n-------------------------------------------\n");
  printf("Enter 1 to continue:\n");
  scanf("%d",&c); 
 }

return 0;
}
