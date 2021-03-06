/*
=============================================================
Name        : laib_7_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_7 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

/*
    PER VERIFICARE DIRETTAMENTE IL FILE DI TEST, COMMENTARE DA RIGA -37- A RIGA -41- E "SCOMMENTARE" LE PRTI ATTUALMENTE COMMENTATE.
    IL NOME DEL FILE DI TESTO PER IL TEST VA CAMBIATO ALL'INTERNO DELLA fopen ALLA RIGA -42-.
    FARE ATTENZIONE A "SCOMMENTARE" ANCHE LA PARENTESI A RIGA -64-.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define difstonesnumber 4
int actualmax=0;
int flag=0;

typedef struct{
    int zaffiri, smeraldi, rubini, topazi;
    int tot;
}stones;

void createnecklace(int pos, char *val, char *sol, char *bestsol, int k, stones total);

int main(){
    int i, measure;
    char value[difstonesnumber+1]="ZSRT";
    char *sol, *bestsol;
    stones numberstones;
/*
    printf("Enter number of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.zaffiri, &numberstones.smeraldi, &numberstones.rubini, &numberstones.topazi);
    numberstones.tot=measure=numberstones.zaffiri+numberstones.smeraldi+numberstones.rubini+numberstones.topazi;
*/
    FILE *fp=fopen("test2.txt", "r");
    while(fscanf(fp, "%d%d%d%d", &numberstones.zaffiri, &numberstones.rubini, &numberstones.topazi, &numberstones.smeraldi)!=EOF){
    numberstones.tot=measure=numberstones.zaffiri+numberstones.smeraldi+numberstones.rubini+numberstones.topazi;
    flag=0; actualmax=1;

    sol=calloc(numberstones.tot+1, sizeof(char));
    bestsol=calloc(numberstones.tot+1, sizeof(char));
    for( ; measure>0 && !flag ; measure--)
        createnecklace(0, value, sol, bestsol, measure, numberstones);

    printf("Total stones: %d!\n", numberstones.tot);
    printf("Best sol:\n");
    printf("------------------------------------------------------------------------------\n");
    for(i=0 ; i<actualmax-1 ; i++)
        printf("%c-", bestsol[i]);
    printf("%c\n", bestsol[i]);
    printf("------------------------------------------------------------------------------\n");
    printf("LENGTH: %d!\n", actualmax);
    printf("------------\n\n");

    free(sol);
    free(bestsol);
    }
    return EXIT_SUCCESS;
}

void createnecklace(int pos, char *val, char *sol, char *bestsol, int k, stones total){
    int i;

    if(pos>=k){          /* terminazione */
        flag=1;
        printf("\a");
        actualmax=pos;
        strcpy(bestsol, sol);
        return;
    }

    for(i=0 ; i<strlen(val) && !flag ; i++){
        if(val[i]=='Z' && total.zaffiri>=1){
            if(total.zaffiri==1 && total.rubini>0){
                total.zaffiri--; total.tot--;           /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "R", sol, bestsol, k, total);
                total.zaffiri++; total.tot++;           /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.rubini==0 && pos+total.zaffiri==k){
                total.zaffiri--; total.tot--;           /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "Z", sol, bestsol, k, total);
                total.zaffiri++; total.tot++;           /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.rubini==0 && pos+total.zaffiri!=k)
                return;
            else if(total.rubini>0){
                total.zaffiri--; total.tot--;           /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "ZR", sol, bestsol, k, total);
                total.zaffiri++; total.tot++;           /* BACKTRACK */
                if(flag)
                    return;
            }
        }
        //
        //
        //
        if(val[i]=='S' && total.smeraldi>=1){
            if(total.smeraldi==1 && total.topazi>0){
                total.smeraldi--; total.tot--;          /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "T", sol, bestsol, k, total);
                total.smeraldi++; total.tot++;           /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.topazi==0 && pos+total.smeraldi==k){
                total.smeraldi--; total.tot--;           /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "S", sol, bestsol, k, total);
                total.smeraldi++; total.tot++;           /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.topazi>0){
                total.smeraldi--; total.tot--;           /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "ST", sol, bestsol, k, total);
                total.smeraldi++; total.tot++;           /* BACKTRACK */
                if(flag)
                    return;
            }
        }
        //
        //
        //
        if(val[i]=='R' && total.rubini>0){
            if(total.smeraldi==0 && total.topazi>0){
                total.rubini--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "T", sol, bestsol, k, total);
                total.rubini++; total.tot++;            /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.smeraldi>0 && total.topazi==0 && pos+1+total.smeraldi==k){
                total.rubini--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "S", sol, bestsol, k, total);
                total.rubini++; total.tot++;            /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.smeraldi>0 && total.topazi>0){
                total.rubini--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "ST", sol, bestsol, k, total);
                total.rubini++; total.tot++;            /* BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.smeraldi==0 && total.topazi==0 && pos==k-1){
                total.rubini--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "", sol, bestsol, k, total);
                total.rubini++; total.tot++;            /* BACKTRACK */
                if(flag)
                    return;
            }
        }
        //
        //
        //
        if(val[i]=='T' && total.topazi>0){
            if(total.zaffiri==0 && total.rubini>0){
                total.topazi--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "R", sol, bestsol, k, total);
                total.topazi++; total.tot++;            /*BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.zaffiri>0 && total.rubini==0 && pos+1+total.zaffiri==k){
                total.topazi--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "Z", sol, bestsol, k, total);
                total.topazi++; total.tot++;            /*BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.zaffiri>0 && total.rubini==0 && pos+1+total.zaffiri!=k)
                return;
            else if(total.zaffiri>0 && total.rubini>0){
                total.topazi--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "Z", sol, bestsol, k, total);
                total.topazi++; total.tot++;            /*BACKTRACK */
                if(flag)
                    return;
            }
            else if(total.zaffiri==0 && total.rubini==0 && pos==k-1){
                total.topazi--; total.tot--;            /* rimuovo le pietre gia' utilizzate */
                sol[pos]=val[i];
                createnecklace(pos+1, "", sol, bestsol, k, total);
                total.topazi++; total.tot++;            /*BACKTRACK */
                if(flag)
                    return;
            }
        }
    }
}
