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


int supprimer_entreprise(FILE* fic,FILE* fic2, char* nom_ent)
{
    
    char chunk[128]= {0};
    int l=0,i=0;
    int nbr = trouver_nom_ent(fic,nom_ent);
    char num[128] = {0};
    if(nbr == 0)
        return 0;
        
    FILE * new = fopen("test/replique.csv","w");
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

    supprimer_poste_index(fic2,nbr);
    return 1;
}

void creer_poste_a_pourvoir(FILE* fic, poste* unposte){
     
    int l=0,compt=1;
    // char debut[50] = "id,titre,competences,entreprise\n";
    char chunk[128];

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

int supprimer_poste(FILE* fic, int indexEnt, char* titre)
{   
    if(indexEnt == 0)
        return 0;
    FILE * new = fopen("test/replique.csv","w");
    char chunk[128]= {0};
    int i=0,j=0,nbrVir=0,Verif=0,conversion,retour=0;
    char num[128] = {0};
    char nomposte[128] = {0};

    fputs("id,titre,competences,entreprise\n",new);
    fseek(fic,32,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL)
    {   
        while(chunk[i] != '\0' && chunk[i] != '\n'){
            if(chunk[i]==','){
                nbrVir++;i++;
            }
            if(nbrVir == 1){
                while(chunk[i]!=','){
                    nomposte[j] = chunk[i];
                    i++;j++;
                }
                if(chunk[i]==','){
                    nbrVir++;
                }
                if(strcmp(nomposte,titre) == 0){
                    Verif++;
                }
                for(int l=0;l<j;l++){
                    nomposte[l] = '\0';
                }
            }
            if(nbrVir == 3){
                j=0;
                while(chunk[i] != '\0' && chunk[i] != '\n'){
                    num[j] = chunk[i];
                    i++;j++;
                }
                conversion = atoi(num);
                if(conversion == indexEnt){
                    Verif++;
                }
                for(int l=0;l<j;l++){
                    num[l] = '\0';
                }
            }
            i++;
        }
        if(Verif != 2){
            fputs(chunk,new);
        }
        if(Verif == 2){
            retour = 1;
        }
        nbrVir =0; i=0; j=0; Verif =0;
    }

    fclose(fic);
    fclose(new);
    remove("test/poste.csv");
    rename("test/replique.csv","test/poste.csv");
    return retour;
}

void supprimer_poste_index(FILE* fichier, int indexEnt)
{
    FILE * new2 = fopen("test/replique2.csv","w");
    char chunk[128]= {0};
    int i=0,j=0,nbrVir=0,Verif=0,conversion;
    char num[128] = {0};

    fputs("id,titre,competences,entreprise\n",new2);
    fseek(fichier,32,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fichier) != NULL)
    {   
        while(chunk[i] != '\0' && chunk[i] != '\n'){
            if(chunk[i]==','){
                nbrVir++;i++;
            }
            if(nbrVir == 3){
                j=0;
                while(chunk[i] != '\0' && chunk[i] != '\n'){
                    num[j] = chunk[i];
                    i++;j++;
                }
                conversion = atoi(num);
                if(conversion == indexEnt){
                    Verif++;
                }
                for(int l=0;l<j;l++){
                    num[l] = '\0';
                }
            }
            i++;
        }
        if(Verif != 1){
            fputs(chunk,new2);
        }
        nbrVir =0; i=0; j=0; Verif =0;
    }

    fclose(fichier);
    fclose(new2);
    remove("test/poste.csv");
    rename("test/replique2.csv","test/poste.csv");
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
    char nbr[128] = {0};
    char UneComp[128] = {0};

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


int trouver_emploi_par_competence(FILE* fic, char* competencess, int emploiTrouve[128]){
    
    int i=0,j,k=0,nbrVirgule=0,compteur=0,n=0;
    char chunk[128] = {0};
    char nbr[128] = {0};
    char UnEmploi[128] = {0};

    fseek(fic,53,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
        while(nbrVirgule < 5){
            j=0;
            if(chunk[i]==','){
                nbrVirgule++;
                i++;
            }
            while(nbrVirgule == 5){
                while(chunk[i] != ';' && chunk[i]!=','){
                    UnEmploi[j] = chunk[i];
                    j++; i++;
                }
                if(chunk[i] == ';'){
                    i++;
                }
                if(chunk[i] == ','){
                    nbrVirgule++;
                }
                if(strcmp(UnEmploi,competencess) == 0){
                    compteur++;
                    emploiTrouve[k] = atoi(nbr);
                    k++;
                }
                for(n=0;n<j;n++){
                    UnEmploi[n]='\0';
                }
                j=0;
            }
            if(nbrVirgule == 0){
                nbr[i] = chunk[i];
            }
            i++;
            if(nbrVirgule == 6){
                i=0;
            }
        }
        nbrVirgule =0;
    }
        return compteur;    
}

int trouver_emploi_par_codep(FILE* fic, char* codepp, int emploiTrouve[128]){
    
    int i=0,j,k=0,nbrVirgule=0,compteur=0,n=0;
    char chunk[128] = {0};
    char nbr[128] = {0};
    char UnEmploi[128] = {0};

    fseek(fic,53,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
        while(nbrVirgule < 4){
            j=0;
            if(chunk[i]==','){
                nbrVirgule++;
                i++;
            }
            while(nbrVirgule == 4){
                while(chunk[i]!=','){
                    UnEmploi[j] = chunk[i];
                    j++; i++;
                }
                if(chunk[i] == ','){
                    nbrVirgule++;
                }
                if(strcmp(UnEmploi,codepp) == 0){
                    compteur++;
                    emploiTrouve[k] = atoi(nbr);
                    k++;
                }
                for(n=0;n<j;n++){
                    UnEmploi[n]='\0';
                }
                j=0;
            }
            if(nbrVirgule == 0){
                nbr[i] = chunk[i];
            }
            i++;
            if(nbrVirgule == 5){
                i=0;
            }
        }
        nbrVirgule =0;
    }
        return compteur;    
}

int trouver_emploi_par_competcode(FILE* fic, char* comp,char* codepos, int emploiTrouve[128]){
    int condition1;
    int condition2;
    int compTrouve[128] = {0};
    int codeTrouve[128] = {0};
    int i=0,j=0,k=0;

    condition1 = trouver_emploi_par_competence(fic,comp,compTrouve);
    condition2 = trouver_emploi_par_codep(fic,codepos,codeTrouve);
    if(condition1 == 0 || condition2 == 0)
        return k;

    for(i=0;i<condition1;i++){
        for(j=0;j<condition2;j++){
            if(compTrouve[j] == codeTrouve[i]){
                emploiTrouve[k]=compTrouve[j];
                k++;
            }
        }
    }

    return k;
}


chercheurEmploi* get_emploi(FILE* fic, int indexB){

    int l=0,i=0,j=0,nbrVirgule=0;
    char chunk[128] ={0};
    char Nom1[128] = {0};
    char Prenom1[128] = {0};
    char mail1[128] = {0};
    char debug[128]={0};
    char code1[128] = {0};
    
    debug[1]=' ';
    printf("%s",debug);
    
    chercheurEmploi *tmp = (chercheurEmploi*)malloc(sizeof(chercheurEmploi));

    fseek(fic,0,SEEK_SET);
    while(fgets(chunk, sizeof(chunk), fic) != NULL) {
        if(l == indexB){
            while(nbrVirgule != 5 ){
                while(chunk[i] != ',' && chunk[i] != '\n'){
                    
                    switch(nbrVirgule){
                        case 0: i++; break;
                        case 1: 
                                Nom1[j]=chunk[i];
                                i++;j++;
                                break;
                        case 2: 
                                Prenom1[j]=chunk[i];
                                i++;j++;
                                break;
                        case 3: 
                                mail1[j]=chunk[i];
                                i++;j++;
                                break;
                        case 4:
                                code1[j]=chunk[i];
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
    tmp->nom = Nom1;
    tmp->Prenom = Prenom1;
    tmp->codepostal=code1;
    tmp->mail=mail1;
    
    return tmp;
}