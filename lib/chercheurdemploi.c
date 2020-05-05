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

void Modifier_profil(char nom[128], char prenom[128], char compe[128], char col[128], char code[128], int choix)
{
    int i,t,y,j,z,k,x,n,ok;
    char str[128];
    char* m2,*m3,*m4,*m5,*m6,*m7;
    x=0 ;
    
    FILE* db = fopen("test/chercheurdemploi.csv", "r+");
    FILE* fp = fopen("test/tmp.csv", "w");

    n=nbrligne(db);
    fseek(db,0,SEEK_SET);
    fscanf(db,"%s",str);
    char* v="abcd";
    v=strtok(str,",");
    while (v!=NULL && x<n)
    {
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
            goto modification;
        }
        else
        {
            goto next;
        }
        next:
        fscanf(db,"%s",str);
        
        v=strtok(str,",");
        x++;
    }
    modification:
    
    if (choix == 1)
    {
       
        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        while (t<n)
        {                       
            fscanf(db,"%s",str);
            m2=strtok(str,",");
            m2=strtok(NULL,",");
            m3=strtok(NULL,",");
            m4=strtok(NULL,",");
            m5=strtok(NULL,",");
            m6=strtok(NULL,",");
            m7=strtok(NULL,",");
                    
            if (t==x)
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s;%s,%s", t, m2, m3, m4, m5, m6, compe, m7);
            }
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
            }
            
            t++;
        }
        goto fin;
    }
    else if (choix == 2)
    {
        FILE* db3=fopen("test/employe.csv", "r");
        char str3[128];
        int z,zz,ii,jj,kk,nn;
        char* l1,*l2,*l3;
        z=0;
        zz=nbrligne(db3);
        fseek(db3,0,SEEK_SET);
        fscanf(db3,"%*s");

        while (z<zz-1)
        {
            ii=0;jj=0;kk=0;nn=0;ok=0;
            fscanf(db3,"%s",str3);
            l1=strtok(str3,",");
            l2=strtok(NULL,",");
            l3=strtok(NULL,",");

            
            while (col[ii]==l2[ii]  && col[ii]!='\0')
            {
                ii++;
                jj++;
            }
            ii++;
            while (col[ii]==l3[kk] && col[ii]!='\0')
            {
                ii++;
                kk++;
                nn++;
            }


            if (jj==strlen(l2) && nn==strlen(l3))
            {
                z=zz-2;
                ok=1;
            }
            z++;
            
            
        }
        fclose(db3);
        

        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        while (t<n)
        {                       
            fscanf(db,"%s",str);
            m2=strtok(str,",");
            m2=strtok(NULL,",");
            m3=strtok(NULL,",");
            m4=strtok(NULL,",");
            m5=strtok(NULL,",");
            m6=strtok(NULL,",");
            m7=strtok(NULL,",");
                    
            if (t==x)
            {
                if (ok==0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
                }
                
                else
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s;%s", t, m2, m3, m4, m5, m6, m7, l1);
                }
                
                
            }
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
            }
            
            t++;
        }
        goto fin;
    }

    else if (choix == 3)
    {
        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        while (t<n)
        {                       
            fscanf(db,"%s",str);
            m2=strtok(str,",");
            m2=strtok(NULL,",");
            m3=strtok(NULL,",");
            m4=strtok(NULL,",");
            m5=strtok(NULL,",");
            m6=strtok(NULL,",");
            m7=strtok(NULL,",");
                    
            if (t==x)
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, code, m6, m7);
            }
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
            }
            
            t++;
        }
        goto fin;
        
    }
    
    
    fin:
    fclose(db);
    fclose(fp);
    remove("test/chercheurdemploi.csv");
    rename("test/tmp.csv","test/chercheurdemploi.csv");
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
        strcpy(ajout,str);
        
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

void Recherche_par_poste(char nom[128], char prenom[128], int choix)
{
    char str1[128];
    char str2[128];
    char str3[128];
    int ok,ok1,ok2,ok3,ok4,ok5,ok6;
    int m,n,nn;

    FILE *db1 = fopen("test/poste.csv", "r");
    FILE *db2 = fopen("test/entreprise.csv", "r");
    FILE* db3 = fopen("test/chercheurdemploi.csv", "r");
    m=nbrligne(db1);
    n=nbrligne(db2);
    nn=nbrligne(db3);
    
   
    fseek(db1,0,SEEK_SET);
    fseek(db2,0,SEEK_SET);
    fseek(db3,0,SEEK_SET);

    char* v2,*v3,*v4;
    char* w1,*w2,*w3,*w4;
    char* x2,*x3,*x5,*x6;
    int a,b,c,d,e,f;
    int x;
    ok=0;
    d=0;
    f=1;
    v2="abcd";
    w1="abcd";
    fscanf(db1,"%*s");
    fscanf(db2,"%*s");
    fscanf(db3,"%*s");

    int zz=0;
    int ii,jj,kk,ll;
    if (choix==1)
    {
        while (zz<nn-1)
        {
            ii=0;jj=0;kk=0;ll=0;ok1=0;
            fscanf(db3,"%s",str3);
            x2=strtok(str3,",");
            x2=strtok(NULL,",");
            x3=strtok(NULL,",");
            x5=strtok(NULL,",");
            x5=strtok(NULL,",");
            x6=strtok(NULL,",");

            while (x2[jj]==nom[jj] && x2[jj]!='\0')
            {
                jj++;
                ii++;
            }
            
            while (x3[kk]==prenom[kk] && x3[ll]!='\0')
            {
                kk++;
                ll++;
            }

            if (ii==strlen(nom) && ll==strlen(prenom))
            {
                ok1=1;
            }

            else
            {
                goto suiv;
            }
            
            x=0;
            while (x<m-1)
            {
                a=0;b=0;c=0;d=0;ok2=0;ok3=0;
                // récupération des données de la table poste
                fscanf(db1,"%s",str1);
                v2=strtok(str1,",");
                v2=strtok(NULL,",");
                v3=strtok(NULL,",");
                v4=strtok(NULL,",");
                
                while (v3[a]!='\0')
                {
                    if (v3[a]==';')
                    {
                        b++;
                        a++;
                    }
                    else
                    {
                        a++;
                    }    
                }
                int ee;
                char* v;
                if (b==0)
                {
                    while (x6[b]!='\0')
                    {
                        if (x6[b]==v3[c])
                        {
                            b++;
                            c++;
                            d++;
                        }
                        else
                        {
                            b++;
                        }

                        if (d==strlen(v3))
                        {
                            ok2=1;
                        }
                        
                    }    
                }
                
                else
                {
                    v=strtok(v3,";");
                    for (int mm = 0; mm < b+1; mm++)
                    {
                        c=0;d=00;ee=0;
                        while (x6[c]!='\0')
                        {
                            if (x6[c]==v[ee])
                            {
                                c++;
                                ee++;
                                d++;
                            }
                            else
                            {
                                d=0;
                                c++;
                            }
                            
                            if (d==strlen(v) && x6[c]==';')
                            {
                                ok2=1;
                                x6[c]='\0';
                                mm=b+1;
                            }
                            
                            else if (d==strlen(v) && x6[c]=='\0')
                            {
                                ok2=1;
                                x6[c]='\0';
                                mm=b+1;
                            }
                            
                        }
                        v=strtok(NULL,";");
                    }
                    
                }
                if (ok1==1 && ok2 ==1)
                {
                    ok3=1;
                }
                
                else
                {
                    goto suiv2;
                }
                
                e=0;
                int g,h;
                while (e<n-1)
                {
                    g=0;h=0;ok4=0;
                    fscanf(db2,"%s",str2);
                    w1=strtok(str2,",");
                    w2=strtok(NULL,",");
                    w3=strtok(NULL,",");
                    w4=strtok(NULL,",");

                    while (v4[g]==w1[g] && v4[g]!='\0')
                    {
                        g++;
                        h++;
                    }

                    if (h==strlen(v4) && h==strlen(w1))
                    {
                        ok4=1;
                    }
                    
                    if (ok3==1 && ok4==1)
                    {
                        ok++;
                        f++;
                        if (f==2)
                        {
                            printf("Voici le(s) résultat(s) de votre recherche\n");
                        }
                        printf("le titre du poste est:%s\n",v2);
                        printf("le nom de l'entreprise:%s\n",w2);
                        printf("l'adresse mail de l'entreprise est:%s\n",w4);
                        printf("le code postal de l'entreprise est:%s\n",w3);
                        printf("---------------------------------------\n");
                    }
                    
                    e++;
                    if (e==n-1)
                    {
                        fseek(db2,0,SEEK_SET);
                        fscanf(db2,"%*s");
                    }
                    
                }
                
                suiv2:
                x++;
                if (x==m-1)
                {
                    fseek(db1,0,SEEK_SET);
                    fscanf(db1,"%*s");
                }
                
                    
            }
            suiv:
            zz++;
            if (zz==nn-1 && ok==0)
            {
                printf("nous n'avons pas pu trouver des résultats correspondant à votre profil\n");
            }
            
        }
    }
    
    else if (choix==2)
    {
        while (zz<nn-1)
        {
            ii=0;jj=0;kk=0;ll=0;ok1=0;
            fscanf(db3,"%s",str3);
            x2=strtok(str3,",");
            x2=strtok(NULL,",");
            x3=strtok(NULL,",");
            x5=strtok(NULL,",");
            x5=strtok(NULL,",");
            x6=strtok(NULL,",");
            

            while (x2[jj]==nom[jj] && x2[jj]!='\0')
            {
                jj++;
                ii++;
            }
            
            while (x3[kk]==prenom[kk] && x3[ll]!='\0')
            {
                kk++;
                ll++;
            }

            if (ii==strlen(nom) && ll==strlen(prenom))
            {
                ok1=1;
            }

            else
            {
                goto suiv3;
            }
            
            x=0;
            while (x<m-1)
            {
                a=0;b=0;c=0;d=0;ok2=0;ok3=1;
                // récupération des données de la table poste
                fscanf(db1,"%s",str1);
                v2=strtok(str1,",");
                v2=strtok(NULL,",");
                v3=strtok(NULL,",");
                v4=strtok(NULL,",");
                
                while (v3[a]!='\0')
                {
                    if (v3[a]==';')
                    {
                        b++;
                        a++;
                    }
                    else
                    {
                        a++;
                    }    
                }
                int ee;
                char* v;
                if (b==0)
                {
                    while (x6[b]!='\0')
                    {
                        if (x6[b]==v3[c])
                        {
                            b++;
                            c++;
                            d++;
                        }
                        else
                        {
                            b++;
                        }

                        if (d==strlen(v3))
                        {
                            ok2=1;
                        }
                        
                    }    
                }
                
                else
                {
                    v=strtok(v3,";");
                    for (int mm = 0; mm < b+1; mm++)
                    {
                        c=0;d=00;ee=0;
                        while (x6[c]!='\0')
                        {
                            if (x6[c]==v[ee])
                            {
                                c++;
                                ee++;
                                d++;
                            }
                            else
                            {
                                d=0;
                                c++;
                            }
                            
                            if (d==strlen(v) && x6[c]==';')
                            {
                                ok2=1;
                                x6[c]='\0';
                                mm=b+1;
                            }
                            
                            else if (d==strlen(v) && x6[c]=='\0')
                            {
                                ok2=1;
                                x6[c]='\0';
                                mm=b+1;
                            }
                            
                        }
                        v=strtok(NULL,";");
                    }
                    
                }
                if (ok1==1 && ok2 ==1)
                {
                    ok3=1;
                }
                
                else
                {
                    goto suiv4;
                }
                
                e=0;
                int g,h;
                while (e<n-1)
                {
                    g=0;h=0;ok4=0,ok5=0,ok6=0;
                    fscanf(db2,"%s",str2);
                    w1=strtok(str2,",");
                    w2=strtok(NULL,",");
                    w3=strtok(NULL,",");
                    w4=strtok(NULL,",");

                    while (v4[g]==w1[g] && v4[g]!='\0')
                    {
                        g++;
                        h++;
                    }

                    if (h==strlen(v4) && h==strlen(w1))
                    {
                        ok4=1;
                    }
                    
                    if (ok3==1 && ok4==1)
                    {
                        ok5=1;
                    }
                    g=0;h=0;
                    while (x5[g]==w3[g] && x5[g]!='\0')
                    {
                        g++;
                        h++;
                    }
                    
                    if (h==strlen(x5) && h==strlen(w3))
                    {
                    ok6=1;
                    }
                    
                    if (ok5==1 && ok6==1)
                    {
                        ok++;
                        f++;
                        if (f==2)
                        {
                            printf("Voici le(s) résultat(s) de votre recherche\n");
                        }
                        printf("le titre du poste est:%s\n",v2);
                        printf("le nom de l'entreprise:%s\n",w2);
                        printf("l'adresse mail de l'entreprise est:%s\n",w4);
                        printf("le code postal de l'entreprise est:%s\n",w3);
                        printf("---------------------------------------\n");
                    }
                    
                    e++;
                    if (e==n-1)
                    {
                        fseek(db2,0,SEEK_SET);
                        fscanf(db2,"%*s");
                    }
                    
                }
                
                suiv4:
                x++;
                if (x==m-1)
                {
                    fseek(db1,0,SEEK_SET);
                    fscanf(db1,"%*s");
                }
                
                    
            }
            suiv3:
            zz++;
            if (zz==nn-1 && ok==0)
            {
                printf("nous n'avons pas pu trouver des résultats correspondant à votre profil\n");
            }
            
        }
    }
    

    fclose(db1);
    fclose(db2);
    fclose(db3);
}

void Rechercher_par_anciencollegue()
{
    return;
}