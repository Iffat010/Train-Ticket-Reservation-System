// Railway reservation using linked lists and Queues.

// If the reservation is full, prompt reservation full!! Put them in waiting list (queue) and give a waiting list number.
// If a passenger wishes to cancel his ticket, he may cancel. Then the passenger in waiting list is booked automatically.
// Display all the contents of reserved passengers.


#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define size 20


typedef struct NODE
{

    int reg_no;
    int age;
    char name[20];
    struct NODE *next;

}
node;


node* deq();
int create();
int reserve(node*);
int cancel(int);
void enq(node*);
void display();


node *start;
node *front;
node *rear;
int count=0;
int num=0;


int create( )
{

    node *new;
    new=(node *)malloc(sizeof(node));
    new->reg_no=1;
    printf("Name of the passenger: ");
    scanf("%s", new->name);
    printf("Age of the passenger: ");
    scanf("%d", &new->age);

    if(new->age>=90 || new->age<=10)
    {
        free(new);
        return -1;
    }

    start=new;
    new->next=NULL;
    num++;
    return 1;

}


int reserve(node *start)
{

    int temp;

    if(start==NULL)
    {
        temp = create(start);
        return temp;
    }

    else
    {

        node *temp, *new_node;
        temp=start;

        while(temp->next!=NULL)
        {
            temp=temp->next;
        }

        new_node=(node *)malloc(sizeof(node));

        printf("Name of the passenger: ");
        scanf("%s", new_node->name);
        printf("Age of the passenger: ");
        scanf("%d", &new_node->age);
        if(new_node->age >=90 || new_node->age<=10)
        {
            return -1;
        }
        new_node->next=NULL;
        if(num<=size)
        {
            num++;
            new_node->reg_no=num;
            temp->next=new_node;

            return 1;
        }
        else
        {
            enq(new_node);
            return 0;
        }

    }

}


int cancel(int reg)
{

    node *ptr, *preptr, *new;
    ptr=start;
    preptr=NULL;

    if(start==NULL)
        return -1;

    if(ptr->next==NULL && ptr->reg_no==reg)
    {
        start=NULL;
        num--;
        free(ptr);
        return 1;
    }

    else
    {

        while(ptr->reg_no!=reg && ptr->next!=NULL)
        {
            preptr=ptr;
            ptr=ptr->next;
        }
        if(ptr==NULL && ptr->reg_no!=reg)
            return -1;
        else
            preptr->next=ptr->next;
        free(ptr);
        new=deq();
        while(preptr->next!=NULL)
            preptr=preptr->next;
        preptr->next=new;
        num--;
        return 1;

    }

}


void enq(node *new_node)
{

    if(rear==NULL)
    {
        rear=new_node;
        rear->next=NULL;
        front=rear;
    }

    else
    {

        node *temp;
        temp=new_node;
        rear->next=temp;
        temp->next=NULL;
        rear=temp;

    }

    count++;

}


node* deq()
{

    node *front1;
    front1=front;

    if(front==NULL)
        return NULL;

    else
    {

        count-- ;

        if(front->next!=NULL)
        {
            front=front->next;
            front1->next=NULL;
            return front1;
        }

        else
        {
            front=NULL;
            rear=NULL;

            return front1;
        }

    }

}


void display()
{

    node *temp;
    temp=start;

    while(temp!=NULL)
    {
        printf("\nRegistration Number: %d\n", temp->reg_no);
        printf("Name of the passenger: %s\n\n", temp->name);
        temp=temp->next;
    }

}


int main()
{

    int choice;
    int status=0;
    int canc=0;
    int reg=0;
    start=NULL;
    rear=NULL;
    front=NULL;


    printf("\t\t\t ****TRAIN TICKET RESERVATION****\t\t\t\t\n");
    printf("\t\t\t\tBANGLADESH RAILWAY   \t\t\t\t\n");
    printf("\t\t\t     FROM CHITTAGONG TO DHAKA\t\t\t\t\n");
    printf("\n\t\t\t     TRAIN                   CLASS  \t\t\t\t\n");
    printf("\t\t\tMOHANAGAR EXPRESS           SNIGDHA  \t\t\t\t\n");
    printf("\n\t\t\t  JOURNEY DATE: 12/06/2022 12:30PM \t\t\t\t\n");
    int ch =0;

    while(ch!=4)
    {

        printf("\n\nDo you want to - \n ");
        printf("1. Book a Ticket \n ");
        printf("2. Display Passenger Details \n ");
        printf("3. Cancel a Booking \n ");
        printf("4. Exit\n\n");

        scanf("%d", &choice);
        switch(choice)
        {

        case 1 :
            status=reserve(start);

            if(status == -1)
            {
                printf("\n Age not eligible");
            }
            else
                printf(" \nBooking Successful!!! Enjoy your journey! Your Reg No is %d\n\n", num);

            break;

        case 2:
            display();
            break;

        case 3:
            printf(" \n Provide the Registration number to be canceled\n");
            scanf(" %d", &reg);
            if(reg>num)
                printf("Invalid!!");
            else
            {
                canc=cancel(reg);
                if(canc==-1)
                    printf("\nRegistration number invalid!!\n");
                else
                    printf("\nRegistration canceled successfully\n");
            }
            break;

        case 4:
            exit(0);
            break;

        default:
            printf("\nWrong choice!\n");


        }

    }

}
