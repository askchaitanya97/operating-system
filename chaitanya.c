#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int a=0,m=0,sid=1,fid=1;

struct node
{
    int data,arrival_time,id,p,remaining,start_time,completion,c;
    struct node *next;
};

typedef struct node node;

struct queue
{
    int count,priority;
    node *front;
    node *rear;
};

typedef struct queue queue;

void initialize(queue *q,int p)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
    q->priority = p;
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}

void enqueue(queue *q, int value,int pr)
{
    node *tmp;
    tmp = malloc(sizeof(node));
    tmp->data = value;
    tmp->c=0;
    
    if(pr==0)
    {
      tmp->id = fid++;	
	}
	else if(pr==1)
	{
	  tmp->id = sid++;
	}
	
	tmp->p = pr;
    tmp->arrival_time = a;
    tmp->next = NULL;
    
    if(!isempty(q))
    {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else
    {
        q->front = q->rear = tmp;
    }
    q->count++;
}

node* dequeue(queue *q)
{
    node *tmp;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    tmp->next = NULL;
    return(tmp);
}

void add(queue *q, node *tmp,int pr)
{    	
	tmp->p = pr;
    tmp->next = NULL;
    
    if(!isempty(q))
    {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else
    {
        q->front = q->rear = tmp;
    }
    q->count++;
}

void roundrobin(queue *faculty, queue *student)
{	
	int fc = faculty->count;
	int sc = student->count;
	int i,aa=0,rr,r;
	//const int quantum = 3;
	
	printf("\n\n Query    \t  arrival time \t  burst time \t  start time \t  completion time \t remaining time ");
	
	for(i=1;i<=fc;i++)
    {
	 node *e;
	 e = dequeue(faculty);	 
     e->start_time = aa;
     r = e->remaining;
     
     if(e->data <= 3)
	 {
	 	e->completion = e->start_time + e->data;
	 	e->remaining = 0;
	 	goto label;
	 }
     
     if(e->c==0)
     {
       e->remaining = e->data - 3;
	 }
	 else if(e->c > 0)
	 {
	   e->remaining -= 3;	
     }	
	 
	 if(r > 3)
	 {
	  e->completion = e->start_time + 3;
	  aa += 3;
	  e->c = e->c +1;
	  add(faculty,e,0);
	  fc++;
	 }
	 else
	 {
	  e->completion = e->start_time + r;	
	  e->remaining  = 0;
	  aa += 3;
	 }
	
	label:
	 printf("\n\n Faculty %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t   %d",e->id,e->arrival_time,e->data,e->start_time,e->completion,e->remaining); 
    }
    
    for(i=1;i<=sc;i++)
    {
	 node *e;
	 e = dequeue(student);	 
     e->start_time = aa;
     r = e->remaining;
     
     if(e->data <= 3)
	 {
	 	e->completion = e->start_time + e->data;
	 	e->remaining = 0;
	 	goto label2;
	 }
     
     if(e->c==0)
     {
       e->remaining = e->data - 3;
	 }
	 else if(e->c > 0)
	 {
	   e->remaining -= 3;	
     }	
     
     
	 
	 if(r > 3)
	 {
	  e->completion = e->start_time + 3;
	  aa = e->completion;
	  e->c = e->c +1;
	  add(student,e,0);
	  sc++;
	 }
	 else
	 {
	  e->completion = e->start_time + r;	
	  e->remaining  = 0;
	  aa = e->completion;
	 }
	 
	 label2:
	
	 printf("\n\n Student %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t   %d",e->id,e->arrival_time,e->data,e->start_time,e->completion,e->remaining); 
    }
    
    
    
}


int main()
{
	int p,b;
    queue *faculty,*student;
    
    faculty = malloc(sizeof(queue));
    student = malloc(sizeof(queue));
    
    initialize(faculty,0);
    initialize(student,1);
    
    printf("\n Mr.Sudesh Sharma wishes to dedicate only 3 minutes to handle each request");
    printf("\n\n (0 - faculty, 1 - student, otherwise - end session) \n");
    
    while(1)
    {
     printf("\n Choose option : ");
     scanf("%d",&p);
          
	 if(p==0)
	 {
	  printf(" Enter query time : ");
	  scanf("%d",&b);
	  enqueue(faculty,b,p);
	  m++;
	 }     
     else if(p==1)
     {
      printf(" Enter query time : ");
      scanf("%d",&b);
      enqueue(student,b,p);
      m++;
	 }     
     else
	 {
	  break; 
	 }
	      
     a++;
	}
	
	printf("\n session over");
	roundrobin(faculty,student);
   
	return 0;
}




