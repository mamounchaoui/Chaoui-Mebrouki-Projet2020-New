#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "employe.h"


int nbrligne2(FILE* dbb)
{
    char c[128];
    int count = 0;
    while( fgets(c, 128, dbb) != NULL)
    {
        count++;
    }
    return count;
}
void Creer_profil2(char nom[128], char prenom[128], char mail[128], char code_postal[128], char competence[128], char collegue[128], char entreprise[128])
{
    char str1[128];
    int id,y,a;
    char* v1,*v2,*v3;
    y=0;

    FILE *db1 = fopen("test/employe.csv", "r+");
    a=nbrligne2(db1);
    id=a;
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    int i,j,k,kk,ok1,ok2,pos;
    
    // recherche de l'ancien collègue dans la table employe
    while (y<a-1)
    {
        ok1=0;
        ok2=0;
        i=0;
        j=0;
        fscanf(db1,"%s",str1);
        v1=strtok(str1,",");
        v2=strtok(NULL,",");
        v3=strtok(NULL,",");

        while (v2[i]==collegue[i] && v2[i]!='\0')
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
        while (v3[k]==collegue[i] && v3[k]!='\0')
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
        // cas où on a pu trouver le collègue
        if (ok1==1 && ok2==1)
        {
            pos=y;// sauvegarde de la postion du collègues dans la table employe
            y=a-1;
        }
        y++;
        // cas où on a pas pu trouver le collègue
        if (y==a-1 && (ok1==0 || ok2==0))
        {
            v1="";
        }
    }

    FILE *db2 = fopen("test/entreprise.csv", "r");
    int b,x,l,m,ok3;
    char str2[128];
    char* w1,*w2;
    int ll,ii,jj;
    b=nbrligne2(db2);
    fseek(db2,0,SEEK_SET);
    fscanf(db2,"%*s");
    x=0;
    // recherche de l'entreprise dans la table entreprise
    while (x<b-1)
    {
        ok3=0;
        l=0;m=0;
        fscanf(db2,"%s",str2);

        w1=strtok(str2,",");
        w2=strtok(NULL,",");

        while (w2[l]==entreprise[l] && w2[l]!='\0')
        {
            l++;
            m++;
        }
        if (m==strlen(w2))
        {
            ok3=1;
        }
        // cas où on a pu trouver l'entreprise
        if (ok3==1)
        {
            x=b-1;
        }
        x++;
        // cas où on a pas pu trouver l'entreprise
        if (x==b-1 && ok3==0)
        {
            w1="";
        }
    }
    
    char* p1,*p2,*p3;
    char str11[128];
    char tempo[128];
    kk=0;
    ll=0;
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    // calcul du nombre de profils qui travaillent pour la même entreprise que le nouveau profil ajouté   
    while (kk<a-2 )
    {
        if (kk==pos)
        {
            fscanf(db1,"%s",str11);
        }
        
        ii=0;jj=0;
        fscanf(db1,"%s",str11);
        strcpy(tempo,str11);
        p1=strtok(str11,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        int jjj=0;
        int kkk=0;
        // gestion des attributs collegues et entreprise    
        while (kkk<strlen(tempo))
        {
            if (tempo[kkk]==',')
            {
                jjj++;
                kkk++;
                if (jjj==6)
                {
                    if (tempo[kkk]==',' && tempo[kkk+1]!='\0')
                    {
                        p3=strtok(NULL,",");
                        p2="";
                    }
                    else if (tempo[kkk]==',' && tempo[kkk+1]=='\0')
                    {
                        p2="";
                        p3="";
                    }
                                
                    else
                    {
                        int ff;
                        char cc;
                        p2=strtok(NULL,",");
                        ff=kkk+strlen(p2)+1;
                        cc=tempo[ff];
                        if (cc=='\0')
                        {
                            p3="";
                        }
                        else
                        {
                            p3=strtok(NULL,",");
                        }                
                    }                
                }
                        
            }
            else
            {
                kkk++;
            }
                    
        }
        while (p3[ii]==w1[ii] && p3[ii]!='\0' && w1[ii]!='\0')
        {
            ii++;
            jj++;
        }
        // à chaque fois qu'on rencontre un profil qui travail pour la même entreprise que le nouveau profil ajouté, on incrémente ll
        if (jj==strlen(p3) && jj==strlen(w1))
        {
            ll++;
        }
        // la valeur finale de ll (après la fin de cette boucle) représentera le nombre total de collègues à ajouter au nouveau profil
        kk++;

    }
    kk=0;
    int pp,rr;
    char coll[128];
    rr=0;pp=0;
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    // identification des profils qui travaillent pour la même entreprise que le nouveau profil ajouté
    while (kk<a-1)
    {
        if (kk==pos)
        {
            fscanf(db1,"%s",str11);
        }
        
        ii=0;jj=0;
        fscanf(db1,"%s",str11);
        strcpy(tempo,str11);
        p1=strtok(str11,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");
        p2=strtok(NULL,",");

        int jjj=0;
        int kkk=0;
                
        while (kkk<strlen(tempo))
        {
            if (tempo[kkk]==',')
            {
                jjj++;
                kkk++;
                if (jjj==6)
                {
                    if (tempo[kkk]==',' && tempo[kkk+1]!='\0')
                    {
                        p3=strtok(NULL,",");
                        p2="";
                    }
                    else if (tempo[kkk]==',' && tempo[kkk+1]=='\0')
                    {
                        p2="";
                        p3="";
                    }
                                
                    else
                    {
                        int ff;
                        char cc;
                        p2=strtok(NULL,",");
                        ff=kkk+strlen(p2)+1;
                        cc=tempo[ff];
                        if (cc=='\0')
                        {
                            p3="";
                        }
                        else
                        {
                            p3=strtok(NULL,",");
                        }                
                    }                
                }
                        
            }
            else
            {
                kkk++;
            }
                    
        }

        while (p3[ii]==w1[ii] && p3[ii]!='\0' && w1[ii]!='\0')
        {
            ii++;
            jj++;
        }
        
        // sauvegarde des identifients des profils qui travaillent pour la même entreprise que le nouveau profil ajouté
        if (jj==strlen(p3) && jj==strlen(w1))
        {
            pp++;
            // cas où en rencontre le premier profil à sauvegarder et qu'on sait qu'il y en aura d'autres par la suite
            if (pp<ll && ll>1)
            {
                for (int qq = 0; qq< strlen(p1); qq++)
                {
                    coll[rr]=p1[qq];
                    rr++;
                }
                coll[rr]=';';
                rr++;
            }
            // cas où on sait qu'il y a uniquement un profil qui travail pour la même entrepise que le nouveau profil ajouté
            else if (pp==1 && ll==1)
            {
                for (int qq = 0; qq< strlen(p1); qq++)
                {
                    coll[rr]=p1[qq];
                    rr++;
                }
                coll[rr]='\0';
            }
            // cas où en rencontre le dernier profil à sauvegarder
            else if (pp==ll && ll!=1)
            {
                for (int qq = 0; qq< strlen(p1); qq++)
                {
                    coll[rr]=p1[qq];
                    rr++;
                }
                coll[rr]='\0';
            }
                    
        }
        
        if (ll==0)
        {
            kk=k-2;
        }
        kk++;
    }
    fseek(db1,0,SEEK_END);
    if (ll==0)
    {
        fprintf(db1,"\n%d,%s,%s,%s,%s,%s,%s,%s",id,nom,prenom,mail,code_postal,competence,v1,w1);
    }
    else if (ll!=0 && strlen(v1)!=0)
    {
        fprintf(db1,"\n%d,%s,%s,%s,%s,%s,%s;%s,%s",id,nom,prenom,mail,code_postal,competence,v1,coll,w1);
    }
    else if (ll!=0 && strlen(v1)==0)
    {
        fprintf(db1,"\n%d,%s,%s,%s,%s,%s,%s,%s",id,nom,prenom,mail,code_postal,competence,coll,w1);
    }
    

    char str4[128];
    FILE *db4 = fopen("test/tmp.csv", "w"); // fichier qui contiendra les données du fichier employé.c à jour
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%s",str4);
    fprintf(db4,"%s",str4);
    char* t2,*t3,*t4,*t5,*t6,*t7,*t8;   
    int e,f,g;
    e=0;

    // ajout aux aurtes le profil le nouveau profil qui travail dans la même entreprise qu'eux
    while (e<a)
    {
        f=0;g=0;
        fscanf(db1,"%s",str4);
        strcpy(tempo,str4);
        if (e==a-1)
        {
            fprintf(db4,"\n%s",str4);
        }
        else
        {
            t2=strtok(str4,",");
            t2=strtok(NULL,",");
            t3=strtok(NULL,",");
            t4=strtok(NULL,",");
            t5=strtok(NULL,",");
            t6=strtok(NULL,",");
            int jjj=0;
            int kkk=0;
                    
            while (kkk<strlen(tempo))
            {
                if (tempo[kkk]==',')
                {
                    jjj++;
                    kkk++;
                    if (jjj==6)
                    {
                        if (tempo[kkk]==',' && tempo[kkk+1]!='\0')
                        {
                            t8=strtok(NULL,",");
                            t7="";
                        }
                        else if (tempo[kkk]==',' && tempo[kkk+1]=='\0')
                        {
                            t7="";
                            t8="";
                        }
                                    
                        else
                        {
                            int ff;
                            char cc;
                            t7=strtok(NULL,",");
                            ff=kkk+strlen(t7)+1;
                            cc=tempo[ff];
                            if (cc=='\0')
                            {
                                t8="";
                            }
                            else
                            {
                                t8=strtok(NULL,",");
                            }                
                        }                
                    }
                            
                }
                else
                {
                    kkk++;
                }
                        
            }

            while (t8[f]==w1[f] && t8[f]!='\0' && w1[f]!='\0')
            {
                f++;
                g++;
            }
            if (g==strlen(t8) && g==strlen(w1))
            {
                // cas où le profil n'a pas de collègues
                if (strlen(t7)==0)
                {
                   fprintf(db4,"\n%d,%s,%s,%s,%s,%s,%d,%s",e+1,t2,t3,t4,t5,t6,a,t8);
                }
                // cas où le profil a au moins un collègue
                else if (strlen(t7)!=0)
                {
                    fprintf(db4,"\n%d,%s,%s,%s,%s,%s,%s;%d,%s",e+1,t2,t3,t4,t5,t6,t7,a,t8);
                }
                
                
            }
            // cas où le profil n'est pas concerné par la modification
            else
            {
                fprintf(db4,"\n%s",tempo);
            }
                
        }
        
        e++;
        
    }
    fseek(db4,0,SEEK_END);
    fclose(db1);
    fclose(db2);
    fclose(db4);

    remove("test/employe.csv");
    rename("test/tmp.csv","test/employe.csv");    
}
void Modifier_profil2(char nom[128], char prenom[128], char compe[128], char col[128], char code[128], char entrep[128], int choix)
{
    return;
}
void Transitionner_profil2(char nom[128], char prenom[128])
{
    return;
}
void Supprimer_profil2(char nom[128], char prenom[128])
{
    return;
}
void Recherche_par_poste2(char nom[128], char prenom[128], int choix)
{
    return;
}
void Rechercher_par_anciencollegue2(char nom[128], char prenom[128], char entreprise[128], int choix)
{
    return;
}
