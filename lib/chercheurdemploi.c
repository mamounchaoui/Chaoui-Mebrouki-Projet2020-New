#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chercheurdemploi.h"


int nbrligne(FILE* dbb)
{
    char c[128];
    int count = 0;
    while( fgets(c, 128, dbb) != NULL)
    {
        count++;
    }
    return count;
}

void Creer_profil(char nom[128], char prenom[128],char mail[128], char code_postal[128], char competence[128], char ancien_collegue[128])
{
    char str[128];
    char str1[128];
    int id;

    FILE *db = fopen("test/chercheurdemploi.csv", "r+");
   
    id=nbrligne(db);
    fseek(db,0,SEEK_SET);
    fscanf(db,"%s",str);

    FILE *db1 = fopen("test/employe.csv", "r");
    int y=0;
    int a;
    a=nbrligne(db1);
    fseek(db1,0,SEEK_SET);
    char* v1,*v2,*v3;
    fscanf(db1,"%*s");
    fscanf(db1,"%s",str1);
    int i,j,k,ok1,ok2;
    
    while (y<a-1)
    {
        ok1=0;
        ok2=0;
        i=0;
        j=0;
        
        v1=strtok(str1,",");
        v2=strtok(NULL,",");
        v3=strtok(NULL,",");

        while (v2[i]==ancien_collegue[i] && v2[i]!='\0')
        {
            i++;
            j++;
        }
        if (j==strlen(v2))
        {
            ok1=1;
            j=0;
        }
        k=0;
        i++;
        while (v3[k]==ancien_collegue[i] && v3[k]!='\0')
        {
            i++;
            k++;
            j++;
        }
        if (j==strlen(v3))
        {
            ok2=1;
            j=0;
        }
        
        if (ok1==1 && ok2==1)
        {
            goto ajout;
        }
        fscanf(db1,"%s",str1);
        y++;
        if (y==a-1 && (ok1==0 || ok2==0))
        {
            v1="";
        }
        

    }
    ajout:
    fseek(db,0,SEEK_END);
    fprintf(db,"\n%d,%s,%s,%s,%s,%s,%s",id,nom,prenom,mail,code_postal,competence,v1);

    
    fclose(db);
    fclose(db1);
}

void Modifier_profil()
{
    return;
}

void Transitionner_profil()
{
    return;
}

void Supprimer_profil()
{
    return;
}

void Recherche_par_poste()
{
    return;
}

void Rechercher_par_anciencollegue()
{
    return;
}