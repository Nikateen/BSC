#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LL.h"

char inputFile[]="./jerry.txt";
int numberOfFiles = 3;
int numberOfLines = 5;

int noder(char *line, char* timeStamp, char *ID, struct node **head){

    char youtubeLink[1000] = "https://www.youtube.com/watch?v=";
    strcat(youtubeLink,ID);
    strcat(youtubeLink,"&t=");
    strcat(youtubeLink,timeStamp);
    char *token;
    //for first word
    token = strtok(line, " ");
    //addNode(head,token,youtubeLink, LLlen(head)+1 );
    push(head,token,youtubeLink);

    //for the rest of the words
    while( ( token = strtok(NULL," ") ) != NULL ){
        //addNode(head, token, youtubeLink, LLlen(head)+1 );
        push(head,token,youtubeLink);
    }

    

    return 0;
}



int process(char ID[1000], struct node **head){
    FILE *fileName;
    char line[20000];
    int lineCounter=0;

    char idPath[128] = "./IDS/";
    strcat(idPath,ID);
    
    char* token = strtok(idPath, "\n");


    strcat(token,".txt");
    fileName=fopen(token,"r");

    while(  ( fgets(line, sizeof(line), fileName) ) && (lineCounter < numberOfLines)  ){
        char* formattedLine;
        char* timeStamp;
        int tme;

        formattedLine = strtok(line,"</");
        formattedLine = strstr(formattedLine,">");

        timeStamp = strstr(line,"start=\"");
        timeStamp = strtok(timeStamp," ");
        timeStamp = timeStamp + 7;

        char* IDlink = strtok(ID, "\n");

        formattedLine++;

        noder(formattedLine, timeStamp, IDlink, head);
        lineCounter++;
    }
    
    return 0;

}

int main()
{
    FILE *linkPath;
    int linkCounter=0;
    char ID[1000];
    //opening the links
    linkPath=fopen(inputFile,"r");
    //Creating the LL
    struct node* head=newNode("_START","NULL");
    while(  ( fgets(ID, sizeof(ID), linkPath) ) && (linkCounter < numberOfFiles)  ){
        process(ID,&head);
        linkCounter++;
    }
    removeDuplicates(&head);
    printData(&head);
}