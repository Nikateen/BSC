#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char data[50];
    char videoID[100];
    struct node *link;
};

struct node* newNode(char *data,char *videoID){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    strcpy(temp->data, data);
    strcpy(temp->videoID,videoID);
    temp->link=NULL;
    return temp;
}

int LLlen(struct node **head)
{
    int count = 0;
    struct node *temp;
    temp = *head;
    
    while (temp != NULL) {
        count++;
        temp = temp ->link;
    }
    return count;
}

int addNode(struct node** head, char *data, char *videoID, int pos){
    struct node *temp = newNode(data, videoID);
    struct node *start = *head;

    if(pos == 0){
        temp->link = *head;
        *head = temp;
        return 0;
    }

    int i =0;
    while( (i<pos-1) && (start ->link != NULL) ){
        start = start->link;
        i++;
    }
    temp->link=start->link;
    start->link = temp;
    return 0;
}

int delNode(struct node **head,int pos){
    struct node *start=*head;
    struct node* temp;

    if(head == NULL){
        printf("DELETE ERROR: Null value for linked list \n");
        return 0;
    }

    if(pos > LLlen(head) ){
        printf("DELETE ERROR: Index doesn't exist \n");
        return 0;
    }

    if(pos == 0){
        *head = (*head)->link;
        free(start);
        return 0;
    }

    int i=0;
    while(i<pos-1){
        start=start->link;
        i++;
    }
    temp=start->link;
    start->link=temp->link;
    free(temp);
    return 0;
}

int printData(struct node **head){
    struct node *start=*head;
    int i=0;
    while(start != NULL){
        printf("%-5d: %-20s ,link: %s \n",i,start ->data,start->videoID);
        start=start->link;
        i++;
    }
    return 0;
}

int push(struct node **head, char *data, char *videoID){
    struct node *start=*head;
    int count =0;

    while((start->link)!=NULL && strcmp( (start->link->data), data) < 0  ){
            start = start->link;
            count++;
        }
    addNode(head,data,videoID,count+1);
    return 0;
}

int removeDuplicates(struct node **start) 
{ 
    struct node *ptr1, *ptr2, *dup; 
    ptr1 = *start; 
  
    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->link != NULL) 
    { 
        ptr2 = ptr1; 
  
        /* Compare the picked element with rest 
           of the elements */
        while (ptr2->link != NULL) 
        { 
            /* If duplicate then delete it */
            if ( strcmp(ptr1->data, ptr2->link->data) == 0 )
            { 
                /* sequence of steps is important here */
                dup = ptr2->link; 
                ptr2->link = ptr2->link->link; 
                free(dup); 
            } 
            else /* This is tricky */
                ptr2 = ptr2->link; 
        } 
        ptr1 = ptr1->link; 
    } 
    return 0;
}

