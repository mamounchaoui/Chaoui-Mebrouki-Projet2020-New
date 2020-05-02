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

void Transitionner_profil(char nom[128], char prenom[128], char entrep[128])
{
    int i,t,y,j,z,k,x,a;
    char str[128];
    char str1[128];
    char ajout[128];
    x=0;
    FILE* db=fopen("test/chercheurdemploi.csv", "r+");
    int w=nbrligne(db);
    FILE* fp;
    fp=fopen("test/tmp.csv", "w");
    fseek(db,0,SEEK_SET);
    
    FILE* db2=fopen("test/entreprise.csv", "r+");
    y=nbrligne(db2);
    fseek(db2,0,SEEK_SET);
    fscanf(db2,"%*s");
    char* temp1,*temp2;
    a=0;
    int o,d,e;
    while (a<y)
    {
        fscanf(db2,"%s",str1);
        o=0;
        d=0;
        e=0;
        temp1=strtok(str1,",");
        temp2=strtok(NULL,",");
        while (temp2[o]==entrep[o] && temp2[o]!='\0')
        {
            o++;
            d++;
        }

        if (d==strlen(entrep))
        {
            e=1;
            a=y;
        }
        a++;
        if (a==y && e==0)
        {
            temp1="";
        }
            
    }
    

    char* t2,*t3,*t4,*t5,*t6,*t7;
    fscanf(db,"%s",str);
    printf("%s\n",str);
    char* v;
    int ok;
    v=strtok(str,",");
    while (v!=NULL && x<w )
    {
        ok=0;
        v=strtok(NULL,",");
        i=0;
        y=0;
        while (v[i]==nom[i] && v[i]!='\0')
        {
            y++;
            i++;

        }
        j=0;
        z=0;
        v=strtok(NULL,",");
        while (v[j]==prenom[j] && v[j]!='\0')
        {
            z++;
            j++;

        }
        t=strlen(nom);
        k=strlen(prenom);
        if (y==t && z==k)
        {
            ok=1;
            fseek(db,0,SEEK_SET);
            fscanf(db,"%s",str);
            fprintf(fp,"%s",str);
            int m=1;
            while (m<w-1)
            {   
                if (m==x)
                {
                    fscanf(db,"%s",str);
                }
                             
                fscanf(db,"%s",str);
                // printf("%s\n",str);
                t2=strtok(str,",");
                t2=strtok(NULL,",");
                t3=strtok(NULL,",");
                t4=strtok(NULL,",");
                t5=strtok(NULL,",");
                t6=strtok(NULL,",");
                t7=strtok(NULL,",");
                
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", m, t2, t3, t4, t5, t6, t7);
                m++;
                
                
            }
            
            goto fin;
        }
        else
        {
            goto next;
        }
        next:
        fscanf(db,"%s",str);
        printf("%s\n",str);
        strcpy(ajout,str);
        printf("%s\n",ajout);
        
        x++;
        v=strtok(str,",");
    
        if (x==w && ok==0)
        {
            printf("on arrive pas à vous identifier\n");
            goto fin2;
        }
        
    }
    fin:
    fclose(db);
    fclose(fp);
    FILE* db1=fopen("test/employe.csv", "r+");
    
    printf("%s\n",ajout);
    t2=strtok(ajout,",");
    t2=strtok(NULL,",");
    t3=strtok(NULL,",");
    t4=strtok(NULL,",");
    t5=strtok(NULL,",");
    t6=strtok(NULL,",");
    t7=strtok(NULL,",");
    int f;
    f=nbrligne(db1);
    printf("%d\n",f);
    fseek(db1,0,SEEK_CUR);
    // id,nom,prenom,mail,code_postal,competences,collegues,entreprise
    fprintf(db1,"\n%d,%s,%s,%s,%s,%s,%s,%s",f,t2,t3,t4,t5,t6,t7,temp1);
    fclose(db1);
    remove("test/chercheurdemploi.csv");
    rename("test/tmp.csv","test/chercheurdemploi.csv");
    fin2:
    return;
}

void Supprimer_profil(char nom[128], char prenom[128])
{
    int i,t,y,j,z,k,x;
    char str[128];
    x=0;
    FILE* db=fopen("test/chercheurdemploi.csv", "r+");
    int w=nbrligne(db);
    FILE* fp;
    fp=fopen("test/tmp.csv", "w");
    fseek(db,0,SEEK_SET);
    char* t2,*t3,*t4,*t5,*t6,*t7;
    fscanf(db,"%s",str);

    char* v;
    int ok;
    v=strtok(str,",");
    while (v!=NULL && x<w )
    {
        ok=0;
        v=strtok(NULL,",");
        i=0;
        y=0;
        while (v[i]==nom[i] && v[i]!='\0')
        {
            y++;
            i++;

        }
        j=0;
        z=0;
        v=strtok(NULL,",");
        while (v[j]==prenom[j] && v[j]!='\0')
        {
            z++;
            j++;

        }
        t=strlen(nom);
        k=strlen(prenom);
        if (y==t && z==k)
        {
            ok=1;
            fseek(db,0,SEEK_SET);
            fscanf(db,"%s",str);
            fprintf(fp,"%s",str);
            int m=1;
            while (m<w-1)
            {   
                if (m==x)
                {
                    fscanf(db,"%s",str);
                }
                             
                fscanf(db,"%s",str);
                t2=strtok(str,",");
                t2=strtok(NULL,",");
                t3=strtok(NULL,",");
                t4=strtok(NULL,",");
                t5=strtok(NULL,",");
                t6=strtok(NULL,",");
                t7=strtok(NULL,",");
                
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", m, t2, t3, t4, t5, t6, t7);
                m++;
                
                
            }
            
            goto fin;
        }
        else
        {
            goto next;
        }
        next:
        // fscanf(db,"%*s");
        fscanf(db,"%s",str);
        x++;
        v=strtok(str,",");
        if (x==w && ok==0)
        {
            printf("on arrive pas à vous identifier\n");
            goto fin2;
        }
        
    }
    fin:
    fclose(db);
    fclose(fp);
    remove("test/chercheurdemploi.csv");
    rename("test/tmp.csv","test/chercheurdemploi.csv");
    fin2:
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