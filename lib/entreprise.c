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
    FILE * new = fopen("test/replique.csv","w");
    char chunk[128]= {0};
    int l=0,i=0;
    int nbr = trouver_nom_ent(fic,nom_ent);
    char num[128] = {0};

    fseek(fic,0,SEEK_SET);
if(nbr != 0){
    while(fgets(chunk, sizeof(chunk), fic) != NULL)
    {   
        if(l<nbr){
            fputs(chunk,new);
        }
        if(l>nbr){
            while(chunk[i] != ','){
                int m = l-1;
                sprintf(num, "%d",m);
                i++;
            }
            while(chunk[i] != '\n' && chunk[i] != '\0'){
                num[i]=chunk[i];
                i++;
            }
            num[i] = '\n';
            fputs(num,new);
            for(int k =0;k<=i;k++){
                num[k] = '\0';
            }
            i = 0;
        }
        l++;
    }
}
    fclose(fic);
    fclose(new);
    remove("test/entreprise.csv");
    rename("test/replique.csv","test/entreprise.csv");
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
    char chunk[128] = {0};
    char Nom[128] = {0};
    char retour[128] = {0};

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
        if(strcmp(Nom,nomEnt) == 0){
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

entreprise* get_ent(FILE* fic, int indexB){
    int l=0,i=0,j=0,nbrVirgule=0;
    char chunk[128] ={0};
    char Nom[128] = {0};
    char code[128] = {0};
    char mail[128] = {0};

    entreprise *tmp = (entreprise*)malloc(sizeof(entreprise));

    fseek(fic,0,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
        if(l == indexB){
            while(nbrVirgule != 4 ){
                while(chunk[i] != ',' && chunk[i] != '\n'){
                    
                    switch(nbrVirgule){
                        case 0: i++; break;
                        case 1: 
                                Nom[j]=chunk[i];
                                i++;j++;
                                break;
                        case 2: 
                                code[j]=chunk[i];
                                i++;j++;
                                break;
                        case 3: 
                                mail[j]=chunk[i];
                                i++;j++;
                                break;
                    }
                }
                if(chunk[i] == ',' || chunk[i] == '\n' ){
                    nbrVirgule++;
                    i++;
                    j=0;
                }
            }
        }
    l++;
    }
    tmp->index=indexB;
    tmp->nom = Nom;
    tmp->codepost=code;
    tmp->courriel=mail;
    
    return tmp;
}

int trouver_poste_par_competence(FILE* fic, char* competence, int entTrouve[128])
{
    int i=0,j,k=0,nbrVirgule=0,compteur=0,n=0;
    char chunk[128] = {0};
    char nbr[128];
    char UneComp[128];

    fseek(fic,32,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
        while(nbrVirgule < 2){
            j=0;
            if(chunk[i]==','){
                nbrVirgule++;
                i++;
            }
            while(nbrVirgule == 2){
                while(chunk[i] != ';' && chunk[i]!=','){
                    UneComp[j] = chunk[i];
                    j++; i++;
                }
                if(chunk[i] == ';'){
                    i++;
                }
                if(chunk[i] == ','){
                    nbrVirgule++;
                }
                if(strcmp(UneComp,competence) == 0){
                    compteur++;
                    entTrouve[k] = atoi(nbr);
                    k++;
                }
                for(n=0;n<j;n++){
                    UneComp[n]='\0';
                }
                j=0;
            }
            if(nbrVirgule == 0){
                nbr[i] = chunk[i];
            }
            i++;
            if(nbrVirgule == 3){
                i=0;
            }
        }
        nbrVirgule =0;
    }
        return compteur;
}