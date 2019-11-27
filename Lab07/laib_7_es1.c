/*
=============================================================
Name        : laib_7_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_7 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define difstonesnumber 4
int actualmax=0;

typedef struct{
    int zaffiri, smeraldi, rubini, topazi;
    int tot;
}stones;

int createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int count);

int main(){
    int i, count=0;
    char value[difstonesnumber+1]="zsrt";
    char *sol, *bestsol;
    stones numberstones;

    printf("Enter number of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.zaffiri, &numberstones.smeraldi, &numberstones.rubini, &numberstones.topazi);
    numberstones.tot=numberstones.zaffiri+numberstones.smeraldi+numberstones.rubini+numberstones.topazi;

    sol=calloc(numberstones.tot+1, sizeof(char));
    bestsol=calloc(numberstones.tot+1, sizeof(char));
    count=createnecklace(0, value, sol, bestsol, numberstones, count);

    printf("Total stones: %d!\n\n", numberstones.tot);
    printf("Best sol:\n");
    printf("---------------------------------------\n");
    for(i=0 ; i<actualmax-1 ; i++)
        printf("%c-", toupper(bestsol[i]));
    printf("%c\n", toupper(bestsol[i]));
    printf("---------------------------------------\n");
    printf("LENGTH: %d!\n", actualmax);
    printf("------------\n");

    return EXIT_SUCCESS;
}

int createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int count){
    int i;

    if(pos>actualmax){
        actualmax=pos;
        strcpy(bestsol, sol);
        return count+1;
    }

    for(i=0 ; i<strlen(val) ; i++){
        if(val[i]=='z' && total.zaffiri>0){
            total.zaffiri--;
            total.tot--;
            sol[pos]=val[i];
            count=createnecklace(pos+1, "zr", sol, bestsol, total, count);
            total.zaffiri++;
            total.tot++;
        }
        if(val[i]=='s' && total.smeraldi>0){
            total.smeraldi--;
            total.tot--;
            sol[pos]=val[i];
            count=createnecklace(pos+1, "st", sol, bestsol, total, count);
            total.smeraldi++;
            total.tot++;
        }
        if(val[i]=='r' && total.rubini>0){
            total.rubini--;
            total.tot--;
            sol[pos]=val[i];
            count=createnecklace(pos+1, "st", sol, bestsol, total, count);
            total.rubini++;
            total.tot++;
        }
        if(val[i]=='t' && total.topazi>0){
            total.topazi--;
            total.tot--;
            sol[pos]=val[i];
            count=createnecklace(pos+1, "zr", sol, bestsol, total, count);
            total.topazi++;
            total.tot++;
        }
    }

    return count;
}
