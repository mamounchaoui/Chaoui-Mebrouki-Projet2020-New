#include "entreprise.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


void creer_profil_entreprise(FILE* fic, entreprise* ent)
{
    int l=0,compt=1;
    //char nom[128],codep[128],cour[128];
    char debut[50] = "id,nom,code postal,mail\n";
    char chunk[128];

    fputs(debut,fic);
    fseek(fic,0,SEEK_SET);

    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
         if(chunk[0] == '\n'){
            fseek(fic,-1,SEEK_CUR);
            goto here;
        }
        //fputs(chunk, stdout);
        l++;
     }
here:
    while(compt != 5){
        switch(compt){
            case 1: fprintf(fic,"%d",l); break; 
            case 2: fputs(ent->nom,fic); break; 
            case 3: fputs(ent->codepost,fic); break;
            case 4: fputs(ent->courriel,fic);break;
        }
        if(compt < 4){
            fputs(",",fic);
        }
        compt++;
    }
    fputs("\n",fic);
    
}


void supprimer_entreprise(FILE* fic, char* nom_ent)
{
    return ;
}

void creer_poste_a_pourvoir(FILE* fic, poste* unposte){
     
    int l=0,compt=1;
    char debut[50] = "id,titre,competences,entreprise\n";
    char chunk[128];

    fputs(debut,fic);
    fseek(fic,0,SEEK_SET);

    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
         if(chunk[0] == '\n'){
            fseek(fic,-1,SEEK_CUR);
            goto here;
        }
        //fputs(chunk, stdout);
        l++;
     }
here:
    while(compt != 5){
        switch(compt){
            case 1: fprintf(fic,"%d",l); break; 
            case 2: fputs(unposte->titre,fic); break; 
            case 3: fputs(unposte->competences,fic); break;
            case 4: fprintf(fic,"%d",unposte->ent->index);break;
        }
        if(compt < 4){
            fputs(",",fic);
        }
        compt++;
    }
    fputs("\n",fic);
    
}

void supprimer_poste(FILE* fic, char* titre)
{
    return ;
}

int trouver_nom_ent(FILE* fic,char* nomEnt)
{
    int l=0,i=0,j,flag=0;
    char chunk[128],Nom[128],retour[128];

    fseek(fic,0,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
        
        j=0;flag = 0;
        while(flag == 0){
        if(chunk[i]==','){
            flag++;
            i++;
        }
        while(chunk[i] != ',' && flag == 1){
            Nom[j]=chunk[i];
            i++;
            j++;
        }
        //fputs(chunk, stdout);
        if(strcmp(Nom,nomEnt) == 0){
            //printf("Trouvé l'index est : %c \n",chunk[0]);
            int k=0;
            while(chunk[k] != ','){
                retour[k]=chunk[k];
                k++;
            }
            return atoi(retour);
        }
        for(int k=0;k<j;k++){
            Nom[k]='\0';
        }

        i++;
        }
        if(flag == 1)
            i=0;
        l++;
     }

    return 0;
}

int trouver_poste_par_competence(FILE* fic, char* competence, int entTrouve[128])
{
    return 0;
}