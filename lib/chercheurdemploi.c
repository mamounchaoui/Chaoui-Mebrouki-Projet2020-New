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
        
        // récupère les 3 premiers attributs de la table employe
        v1=strtok(str1,",");
        v2=strtok(NULL,",");//nom
        v3=strtok(NULL,",");//prenom

        // comparaison entre employe.nom et le nom saisi par l'utilisateur
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
        // comparaison entre employe.prenom et le prenom saisi par l'utilisateur
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
        // si la personne se trouve dans la table employe
        if (ok1==1 && ok2==1)
        {
            goto ajout;
        }
        fscanf(db1,"%s",str1);
        y++;
        // si on a parcouru toute la table et q'on a pas trouvé la personne saisie par l'utilisateur
        if (y==a-1 && (ok1==0 || ok2==0))
        {
            v1="";
        }
        

    }
    ajout:
    // on se positionne à la fin du fichier chercheur d'emploi.csv et on ajoute le profil
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
    FILE* fp = fopen("test/tmp.csv", "w");// fichier temporaire où on va recopier les données du fichier chercheurdemploi.csv avec les modifications apportées

    n=nbrligne(db);
    fseek(db,0,SEEK_SET);
    fscanf(db,"%s",str);
    char* v="abcd";
    v=strtok(str,",");
    while (v!=NULL && x<n)
    {
        v=strtok(NULL,",");//nom
        i=0;
        y=0;
        while (v[i]==nom[i] && v[i]!='\0')
        {
            y++;
            i++;

        }
        j=0;
        z=0;
        v=strtok(NULL,",");//prenom
        while (v[j]==prenom[j] && v[j]!='\0')
        {
            z++;
            j++;

        }
        t=strlen(nom);
        k=strlen(prenom);
        // si on identifie le profil qu'on souhaite modifier , on modifie les données que l'utilisateur souhaite chanfer ou ajouter
        if (y==t && z==k)
        {
            goto modification;
        }
        // sinon on passe au profil suivant
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
    
    // ajouter une compétence
    if (choix == 1)
    {
        char tempo[128];
        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        while (t<n)
        {                       
            fscanf(db,"%s",str);
            strcpy(tempo,str);
            m2=strtok(str,",");//id
            m2=strtok(NULL,",");//nom
            m3=strtok(NULL,",");//prenom
            m4=strtok(NULL,",");//mail
            m5=strtok(NULL,",");//code postal
            m6=strtok(NULL,",");//compétence
            // m7=strtok(NULL,",");

            int kk=0;
            int jj=0;
            //cette boucle permet de savoir si cette personne a des anciens collègues ou pas
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        //ca soù la personne n'a pas d'anciens collègues
                        if (tempo[kk-1]==',' && tempo[kk]=='\0')
                        {
                            m7="";
                        }
                        
                        // cas où la personne a au moins un ancien collègue
                        else
                        {
                            m7=strtok(NULL,",");
                        }
                        
                        
                    }
                    
                }
                else
                {
                    kk++;
                }
            }    

            // si on rencontre le profil qu'on souhaite modifier,on ajoute la compétence saisaie par l'utilisateur   
            if (t==x)
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s;%s,%s", t, m2, m3, m4, m5, m6, compe, m7);
            }
            // sinon on recopie le profil sans apporter de modification
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
            }
            
            t++;
        }
        goto fin;
    }

    // ajouter un ancien collègue de travail
    else if (choix == 2)
    {
        FILE* db3=fopen("test/employe.csv", "r");
        char str3[128];
        char tempo[128];
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
            strcpy(tempo,str);
            m2=strtok(str,",");
            m2=strtok(NULL,",");
            m3=strtok(NULL,",");
            m4=strtok(NULL,",");
            m5=strtok(NULL,",");
            m6=strtok(NULL,",");

            int kk=0;
            int jj=0;
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        if (tempo[kk-1]==',' && tempo[kk]=='\0')
                        {
                            m7="";
                        }
                        
                        else
                        {
                            m7=strtok(NULL,",");
                        }
                            
                    }
                    
                }
                else
                {
                    kk++;
                }
            }    
            // si on rencontre le profil qu'on souhaite modifier,on ajoute l'ancien collègue de travail        
            if (t==x)
            {
                // cas où on a pas pu trouver l'ancien collègue (dans la table employe) qu l'utilisateur souhaite ajouter
                if (ok==0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
                }
                // cas où le profil qu'on souhaite modifier ne contient pas d'anciens collègues
                else if (ok==1 && strlen(m7)==0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, l1);
                }
                // cas où le profil qu'on souhaite contient au moins un ancien collègue
                else if (ok==1 && strlen(m7)!=0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s;%s", t, m2, m3, m4, m5, m6, m7, l1);
                }
                
                
                
            }
            // sinon on recopie le profil sans apporter de modification
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7);
            }
            
            t++;
        }
        goto fin;
    }

    // modifier le code postal
    else if (choix == 3)
    {
        char tempo[128];
        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        while (t<n)
        {                       
            fscanf(db,"%s",str);
            strcpy(tempo,str);
            m2=strtok(str,",");
            m2=strtok(NULL,",");
            m3=strtok(NULL,",");
            m4=strtok(NULL,",");
            m5=strtok(NULL,",");
            m6=strtok(NULL,",");
            // m7=strtok(NULL,",");

            int kk=0;
            int jj=0;
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        if (tempo[kk-1]==',' && tempo[kk]=='\0')
                        {
                            m7="";
                        }
                        
                        else
                        {
                            m7=strtok(NULL,",");
                        }
                        
                        
                    }
                    
                }
                else
                {
                    kk++;
                }
            }

            // si on rencontre le profil qu'on souhaite modifier,on modifie le code postal       
            if (t==x)
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, code, m6, m7);
            }
            // sinon on recopie le profil sans apporter de modification
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
    remove("test/chercheurdemploi.csv");//on supprime le fichier de départ
    rename("test/tmp.csv","test/chercheurdemploi.csv");//on renomme le fichier temporaires qui contient les données à jour
}

void Transitionner_profil(char nom[128], char prenom[128], char entrep[128])
{
    int i,t,y,j,z,k,x,a;
    char str[128];
    char str1[128];
    char ajout[128];
    int o,d,e,w;
    int okk;
    char* temp1,*temp2;
    
    FILE* db=fopen("test/chercheurdemploi.csv", "r+");
    FILE* db2=fopen("test/entreprise.csv", "r+");
    FILE* fp=fopen("test/tmp.csv", "w");// fichier tempo où on va recopier les profils du fichier chercheurdemploi.csv à part le frofil qu'on souhaite transitionner
   
    w=nbrligne(db);
    y=nbrligne(db2);
    fseek(db,0,SEEK_SET);
    fseek(db2,0,SEEK_SET);
    fscanf(db2,"%*s");
    
    a=0;
    x=0;
    okk=0;
    // recherche de l'entreprise dans la table entreprise que le chercheur d'emploi va intégrer
    while (a<y-1)
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

        if (d==strlen(entrep) && d==strlen(temp2))
        {
            e=1;
            a=y;
            okk=1;
        }
        a++;
        if (a==y-1 && okk==0)
        {
            temp1="";
        }
          
    }
    fclose(db2);
    

    char* t2,*t3,*t4,*t5,*t6,*t7;
    fscanf(db,"%s",str);
    char* v;
    int ok;
    v=strtok(str,",");
    // recherche du profil de la personne (dans la table chercheur d'emploi) qui souhaite changer de statut 
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
        char tempo[128];
        if (y==t && z==k)
        {
            ok=1;
            fseek(db,0,SEEK_SET);
            fscanf(db,"%s",str);
            fprintf(fp,"%s",str);// recopie de l'entête du fichier chercheurdemploi.csv dans le fichier tmp.csv
            int m=1;
            while (m<w-1)
            {   //si on rencontre le profil qu'on souhaite transitionner,on passe directement au profil suivant
                if (m==x)
                {
                    fscanf(db,"%s",str);
                }

                // récupération des autres profils  
                fscanf(db,"%s",str);
                strcpy(tempo,str);
                t2=strtok(str,",");
                t2=strtok(NULL,",");
                t3=strtok(NULL,",");
                t4=strtok(NULL,",");
                t5=strtok(NULL,",");
                t6=strtok(NULL,",");

                int kk=0;
                int jj=0;
                // gestion de l'attibut collègues de la table chercheurdemploi
                while (kk<strlen(tempo))
                {
                    if (tempo[kk]==',')
                    {
                        jj++;
                        kk++;
                        if (jj==6)
                        {
                            // cas l'attribut ne contient aucune donnée
                            if (tempo[kk-1]==',' && tempo[kk]=='\0')
                            {
                                t7="";
                            }
                            
                            // cas l'attribut ne contient au moins une donnée donnée
                            else
                            {
                                t7=strtok(NULL,",");
                            }
                            
                            
                        }
                        
                    }
                    else
                    {
                        kk++;
                    }
                }
                // recopie du profil dans le fichier tmp.csv
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
    
        // cas où le fichier a été parcouru en entier et qu'on pas trouvé le profil qui souhaite transitionner de statut
        if (x==w && ok==0)
        {
            printf("on arrive pas à vous identifier\n");
            // goto fin2;
            return;
        }    
    }
    fin:
    fclose(db);
    fclose(fp);
    FILE* db1=fopen("test/employe.csv", "r+");
    FILE* db3=fopen("test/tmp1.csv", "w");// fichier qui va contenir les profils de la table employe + le profil qui vient de changer de statut + des modifs au niveau de l'attibut collegues
    int bb;
    char* p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8;
    char str11[128];
    bb=nbrligne(db1);
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%s",str11);
    char tempo[128];
    int kk,jj,ii,ll;
    kk=0;
    ll=0;
    fprintf(db3,"%s",str11);
    while (ll<bb-1)
    {
        ii=0;jj=0;
        fscanf(db1,"%s",str11);
        strcpy(tempo,str11);
        p1=strtok(str11,",");
        p2=strtok(NULL,",");
        p3=strtok(NULL,",");
        p4=strtok(NULL,",");
        p5=strtok(NULL,",");
        p6=strtok(NULL,",");
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
                    // cas où l'attribut collegues ne contient aucune donnée et l'attribut entreprise contient une donnée
                    if (tempo[kkk]==',' && tempo[kkk+1]!='\0')
                    {
                        p8=strtok(NULL,",");
                        p7="";
                    }
                    // cas où l'attribut collegues et l'attribut entreprise ne contiennent aucune donnée
                    else if (tempo[kkk]==',' && tempo[kkk+1]=='\0')
                    {
                        p7="";
                        p8="";
                    }
                    // cas où l'attribut collegues contient au moins une donnée et l'attribut entreprise contient aussi une donnée 
                    // ou bien l'attribut collegues contient au moins une donnée et l'attribut entreprise ne contient aucune donnée
                    else
                    {
                        int ff;
                        char cc;
                        p7=strtok(NULL,",");
                        ff=kkk+strlen(p7)+1;
                        cc=tempo[ff];
                        // l'attribut entreprise ne contient aucune donnée
                        if (cc=='\0')
                        {
                            p8="";
                        }
                        // l'attribut entreprise contient une donnée 
                        else
                        {
                            p8=strtok(NULL,",");
                        }                
                    }                
                }
                        
            }
            else
            {
                kkk++;
            }
                    
        }
        while (p8[ii]==temp1[ii] && p8[ii]!='\0' && temp1[ii]!='\0')
        {
            ii++;
            jj++;
        }
        
        // ajout des profils dans le fichiers tmp.csv dont l'attribut collegues doit être modifié
        if (jj==strlen(p8) && jj==strlen(temp1))
        {
            if (strlen(p7)!=0)
            {
                fprintf(db3,"\n%s,%s,%s,%s,%s,%s,%s;%d,%s",p1,p2,p3,p4,p5,p6,p7,bb,p8);
            }
            else if (strlen(p7)==0)
            {
                fprintf(db3,"\n%s,%s,%s,%s,%s,%s,%d,%s",p1,p2,p3,p4,p5,p6,bb,p8);
            }
            
            
            
        }
        // ajout des profils dans le fichiers tmp.csv qui ne seront pas modifiés
        else
        {
            fprintf(db3,"\n%s,%s,%s,%s,%s,%s,%s,%s",p1,p2,p3,p4,p5,p6,p7,p8);
        }
        
        
        ll++;

    }
    
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    kk=0;
    ll=0;

    while (kk<bb-1 && e!=0)
    {
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
        // calcul du nombre de profils qui travaillent pour la même entreprise que le nouveau profil ajouté       
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
        while (p3[ii]==temp1[ii] && p3[ii]!='\0' && temp1[ii]!='\0')
        {
            ii++;
            jj++;
        }
        
        if (jj==strlen(p3) && jj==strlen(temp1))
        {
            ll++;
        }
        
        kk++;

    }
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    kk=0;
    int pp,rr;
    char coll[128];
    rr=0;pp=0;

    // identification des profils qui travaillent pour la même entreprise que le nouveau profil ajouté
    while (kk<bb-1 && e!=0)
    {
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

        while (p3[ii]==temp1[ii] && p3[ii]!='\0' && temp1[ii]!='\0')
        {
            ii++;
            jj++;
        }
        
        // sauvegarde des identifients des profils qui travaillent pour la même entreprise que le nouveau profil ajouté
        if (jj==strlen(p3) && jj==strlen(temp1))
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
            // cas où en rencontre le denier profil à sauvegarder
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
            kk=bb-2;
        }
        kk++;
    }
    
    strcpy(tempo,ajout);
    t2=strtok(ajout,",");
    t2=strtok(NULL,",");
    t3=strtok(NULL,",");
    t4=strtok(NULL,",");
    t5=strtok(NULL,",");
    t6=strtok(NULL,",");
    int kkk=0;
    int jjj=0;
    while (kkk<strlen(tempo))
    {
        if (tempo[kkk]==',')
        {
            jjj++;
            kkk++;
            if (jjj==6)
            {
                if (tempo[kkk-1]==',' && tempo[kkk]=='\0')
                {
                    t7="";
                }
                            
                else
                {
                    t7=strtok(NULL,",");
                }
                            
                            
            }
                        
        }
        else
        {
            kkk++;
        }
    }
    // ajout du profil à transitionner dans le fichier tmp1.csv
    fseek(db2,0,SEEK_END);
    if (ll==0 && e!=0 && strlen(t7)!=0)
    {
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,%s,%s",bb,t2,t3,t4,t5,t6,t7,temp1);
    }
    else  if (ll==0 && e!=0 && strlen(t7)==0)
    {
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,,%s",bb,t2,t3,t4,t5,t6,temp1);
    }
    
    
    else if (e==0 && strlen(t7)!=0)
    {
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,%s,",bb,t2,t3,t4,t5,t6,t7);
    }

    else if (e==0 && strlen(t7)==0)
    {
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,,",bb,t2,t3,t4,t5,t6);
    }
    
    
    else if (e!=0 && strlen(t7)!=0)
    {
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,%s;%s,%s",bb,t2,t3,t4,t5,t6,t7,coll,temp1);
    }

    else if (e!=0 && strlen(t7)==0)
    {
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,%s,%s",bb,t2,t3,t4,t5,t6,coll,temp1);
    }
    
    
    fclose(db1);
    fclose(db3);
    remove("test/chercheurdemploi.csv");// on supprime le fichier chercheurdemploi.csv de départ
    rename("test/tmp.csv","test/chercheurdemploi.csv");// on rennome le fichier tmp.csv qui contient les données du fichier chercheurdemploi.csv à jour
    remove("test/employe.csv");// on supprime le fichier employe.csv de départ
    rename("test/tmp1.csv","test/employe.csv");// on rennome le fichier tmp.csv qui contient les données du fichier employe.csv à jour
    return;
}

void Supprimer_profil(char nom[128], char prenom[128])
{
    int i,t,y,j,z,k,x,w;
    char* t2,*t3,*t4,*t5,*t6,*t7;
    char* v1,*v2;
    int ok;
    char str[128];
    
    FILE* db=fopen("test/chercheurdemploi.csv", "r+");
    FILE* fp=fopen("test/tmp.csv", "w");// contiendra la mise à du fichier chercheurdemploi.csv
    w=nbrligne(db);
    fseek(db,0,SEEK_SET);
    fscanf(db,"%s",str);

    x=0;
    // recherche du profil à supprimer
    while (x<w-1)
    {
        ok=0;
        fscanf(db,"%s",str);
        v1=strtok(str,",");
        v1=strtok(NULL,",");
        i=0;
        y=0;
        while (v1[i]==nom[i] && v1[i]!='\0')
        {
            y++;
            i++;
        }
        j=0;
        z=0;
        v2=strtok(NULL,",");
        while (v2[j]==prenom[j] && v2[j]!='\0')
        {
            z++;
            j++;
        }
        t=strlen(nom);
        k=strlen(prenom);
        // si en rencontre le profil à supprimer, on recopie les profils du fichier chercheurdemploi dans le fichier tmp.csv à l'exception du profil qu'on souhaite supprimer
        if (y==t && z==k && k==strlen(v2) && y==strlen(v1))
        {
            ok=1;
            fseek(db,0,SEEK_SET);
            fscanf(db,"%s",str);
            fprintf(fp,"%s",str);
            int m=1;
            char tempo[128];
            // si on rencontre le profil qu'on souhaite supprimer, on passe au profil suivant
            while (m<w-1)
            {   
                if (m==x+1)
                {
                    fscanf(db,"%s",str);
                }
                             
                fscanf(db,"%s",str);
                strcpy(tempo,str);
                t2=strtok(str,",");
                t2=strtok(NULL,",");
                t3=strtok(NULL,",");
                t4=strtok(NULL,",");
                t5=strtok(NULL,",");
                t6=strtok(NULL,",");
                int kk=0;
                int jj=0;
                while (kk<strlen(tempo))
                {
                    if (tempo[kk]==',')
                    {
                        jj++;
                        kk++;
                        if (jj==6)
                        {
                            if (tempo[kk-1]==',' && tempo[kk]=='\0')
                            {
                                t7="";
                            }
                            
                            else
                            {
                                t7=strtok(NULL,",");
                            }
                            
                            
                        }
                        
                    }
                    else
                    {
                        kk++;
                    }
                }
                
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
        x++;
        // ca soù on arrive pas à identifier le profil qu'on souhaite supprimer
        if (x==w-1 && ok==0)
        {
            printf("on arrive pas à vous identifier\n");
            goto fin2;
        }
        
    }
    fin:
    fclose(db);
    fclose(fp);
    remove("test/chercheurdemploi.csv");// suppression du fichier chercheurdemploi.csv de départ
    rename("test/tmp.csv","test/chercheurdemploi.csv");// on renomme le fichier tmp.csv qui contient les données à jour
    fin2:
    return;
}

void Recherche_par_poste(char nom[128], char prenom[128], int choix)
{
    char str1[128];
    char str2[128];
    char str3[128];
    int ok,okk,ok1,ok2,ok3,ok4,ok5,ok6;
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
    okk=0;
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
    // recherche par compétences
    if (choix==1)
    {
        // recherche du profil (qui souhaite faire la recherche par compétence) pour récupérer ses compétences
        while (zz<nn-1)
        {
            ii=0;jj=0;kk=0;ll=0;ok1=0;
            fscanf(db3,"%s",str3);
            x2=strtok(str3,",");//id
            x2=strtok(NULL,",");//nom
            x3=strtok(NULL,",");//prenom
            x5=strtok(NULL,",");//mail
            x5=strtok(NULL,",");//code_postal
            x6=strtok(NULL,",");//competence

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
            // si on identifie le profil
            if (ii==strlen(nom) && ll==strlen(prenom) && ii==strlen(x2) && ll==strlen(x3))
            {
                ok1=1;
                okk++;
            }
            // sinon on passe au profil suivant
            else
            {
                goto suiv;
            }
            
            x=0;
            // recherche des postes qui correspondent à la compétence du chercheur d'emploi
            while (x<m-1)
            {
                a=0;b=0;c=0;d=0;ok2=0;ok3=0;
                fscanf(db1,"%s",str1);
                v2=strtok(str1,",");//id
                v2=strtok(NULL,",");//titre
                v3=strtok(NULL,",");//competence
                v4=strtok(NULL,",");//entreprise
                
                //calcul du nombre de compétences par poste
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
                //cas où le poste ne contient qu'une seule compétence
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
                //cas où le poste contient plusieurs compétences
                else
                {
                    v=strtok(v3,";");
                    for (int mm = 0; mm < b+1; mm++)
                    {
                        c=0;d=00;ee=0;
                        // vérifier si les compétences du chercheur d'emploi corresppond aux compétences du poste
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
                // si les compétences du chercheur d'emploi corresppondent aux compétences du poste
                if (ok1==1 && ok2 ==1)
                {
                    ok3=1;
                }
                // sinon on passe au poste suivant
                else
                {
                    goto suiv2;
                }
                
                e=0;
                int g,h;
                // recherche du nom de l'entreprise dont les compétences correspondent aux compétences du chercheur d'emploi
                while (e<n-1)
                {
                    g=0;h=0;ok4=0;
                    fscanf(db2,"%s",str2);
                    w1=strtok(str2,",");//id
                    w2=strtok(NULL,",");//nom
                    w3=strtok(NULL,",");//code_postal
                    w4=strtok(NULL,",");//mail

                    while (v4[g]==w1[g] && v4[g]!='\0')
                    {
                        g++;
                        h++;
                    }

                    if (h==strlen(v4) && h==strlen(w1))
                    {
                        ok4=1;
                    }
                    // si on indentifie l'entreprise, on affiche ses données
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
                    // sinon on passe à l'entreprise suivante
                    e++;
                    // si on arrive à la fin du fichier entrepise.csv , on remet le curseur au début du fichier et on saute l'entête du fichier
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
            // cas où on ne trouve pas de résultats qui correspondent au profil du chercheur d'emploi
            if (zz==nn-1 && ok==0 && okk!=0)
            {
                printf("nous n'avons pas pu trouver des résultats correspondant à votre profil\n");
            }
            // cas où on arrive pas à identifier le chercheur d'emploi
            if (zz==nn-1 && okk==0)
            {
                printf("votre profil n'existe pas\n");
            }    
        }
    }
    // recherche par compétences et code postal
    else if (choix==2)
    {
        // recherche du profil (qui souhaite faire la recherche par compétences et par code postal) pour récupérer ses compétences
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
            // si on identifie le profil
            if (ii==strlen(nom) && ll==strlen(prenom) && ii==strlen(x2) && ll==strlen(x3))
            {
                ok1=1;
                okk++;
            }
            // sinon on passe au profil suivant
            else
            {
                goto suiv3;
            }
            
            x=0;
            // recherche des postes qui correspondent à la compétence du chercheur d'emploi
            while (x<m-1)
            {
                a=0;b=0;c=0;d=0;ok2=0;ok3=1;
                fscanf(db1,"%s",str1);
                v2=strtok(str1,",");
                v2=strtok(NULL,",");
                v3=strtok(NULL,",");
                v4=strtok(NULL,",");
                //calcul du nombre de compétences par poste
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
                // cas où le poste ne contient qu'une seule compétence
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
                // cas où le poste contient plusieurs compétences
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
                // si les compétences du chercheur d'emploi corresppondent aux compétences du poste
                if (ok1==1 && ok2 ==1)
                {
                    ok3=1;
                }
                // sinon on passe au poste suivant
                else
                {
                    goto suiv4;
                }
                
                e=0;
                int g,h;
                // recherche du nom de l'entreprise dont les compétences correspondent aux compétences du chercheur d'emploi
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
                    // cas où on indentifie l'entreprise
                    if (h==strlen(v4) && h==strlen(w1))
                    {
                        ok4=1;
                    }
                    
                    if (ok3==1 && ok4==1)
                    {
                        ok5=1;
                    }
                    g=0;h=0;
                    // cas où le code postal de l'entreprise correspond au code postal du chercheur d'emploi
                    while (x5[g]==w3[g] && x5[g]!='\0')
                    {
                        g++;
                        h++;
                    }
                    
                    if (h==strlen(x5) && h==strlen(w3))
                    {
                    ok6=1;
                    }
                    // cas où on indentifie l'entreprise et que le code postal de l'entreprise correspond au code postal du chercheur d'emploi
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
            if (zz==nn-1 && ok==0 && okk!=0)
            {
                printf("nous n'avons pas pu trouver des résultats correspondant à votre profil\n");
            }

            if (zz==nn-1 && okk==0)
            {
                printf("votre profil n'existe pas\n");
            }
            
        }
    }
    

    fclose(db1);
    fclose(db2);
    fclose(db3);
}

void Rechercher_par_anciencollegue(char nom[128], char prenom[128], char entrep[128], int choix)
{
    char str1[128];
    char str2[128];
    char str3[128];
    char str4[128];
    char tempo[128];

    FILE *db1 = fopen("test/entreprise.csv", "r");
    FILE *db2 = fopen("test/poste.csv", "r");
    FILE *db3 = fopen("test/employe.csv", "r");
    FILE *db4 = fopen("test/chercheurdemploi.csv", "r");

    int a,b,c,d;
    a=nbrligne(db1);
    b=nbrligne(db2);
    c=nbrligne(db3);
    d=nbrligne(db4);
   
    fseek(db1,0,SEEK_SET);
    fseek(db2,0,SEEK_SET);
    fseek(db3,0,SEEK_SET);
    fseek(db4,0,SEEK_SET);

    char* v1,*v2; //entreprise
    char* w1,*w3; //poste
    char* x1,*x2,*x3,*x4,*x7,*x8; //employe
    char* y2,*y3,*y6,*y7; //chercheurdemploi
    char* v;

    fscanf(db1,"%*s");
    fscanf(db2,"%*s");
    fscanf(db3,"%*s");
    fscanf(db4,"%*s");

    int e,f,g,ok1,ok2,ok3,ok;
    e=0;
    ok=0;

    //  Recherche par entreprise
    if (choix==1)
    {
        // identification de l'entreprise
        while (e<a-1)
        {
            f=0;g=0;ok1=0;
            fscanf(db1,"%s",str1);
            v1=strtok(str1,",");
            v2=strtok(NULL,",");

            while (v2[f]==entrep[f] && v2[f]!='\0')
            {
                f++;
                g++;
            }
            if (g==strlen(v2))
            {
                ok1=1;
            }
            else
            {
                goto next1;
            }
            
            int h,i,j;
            h=0;
            // recherche des personnes sui travaillent pour cette entreprise
            while (h<c-1 && ok1==1)
            {
                i=0;j=0;ok2=0;
                fscanf(db3,"%s",str3);
                strcpy(tempo,str3);
                x1=strtok(str3,",");//id
                x2=strtok(NULL,",");//nom
                x3=strtok(NULL,",");//prenom
                x4=strtok(NULL,",");//mail
                x7=strtok(NULL,",");//code_postal
                x7=strtok(NULL,",");//competence

                int jjj=0;
                int kkk=0;
                
                // gestion des attributs collegies et entreprise
                while (kkk<strlen(tempo))
                {
                    if (tempo[kkk]==',')
                    {
                        jjj++;
                        kkk++;
                        if (jjj==6)
                        {
                            // cas où l'attribut collegue ne contient aucune donnée
                            if (tempo[kkk]==',' && tempo[kkk+1]!='\0')
                            {
                                x8=strtok(NULL,",");
                                x7="";
                            }
                            // cas où les attributs collegue et entrepise ne contiennent aucune donnée
                            else if (tempo[kkk]==',' && tempo[kkk+1]=='\0')
                            {
                                x7="";
                                x8="";
                            }
                            // cas où l'attribut collegues contient au moins une donnée et l'attribut entreprise contient aussi une donnée 
                            // ou bien l'attribut collegues contient au moins une donnée et l'attribut entreprise ne contient aucune donnée           
                            else
                            {
                                int ff;
                                char cc;
                                x7=strtok(NULL,",");
                                ff=kkk+strlen(x7)+1;
                                cc=tempo[ff];
                                // cas où l'attribut entreprise ne contient aucune donnée
                                if (cc=='\0')
                                {
                                    x8="";
                                }
                                // cas où l'attribut entreprise contient une donnée
                                else
                                {
                                    x8=strtok(NULL,",");
                                }                
                            }                
                        }
                                
                    }
                    else
                    {
                        kkk++;
                    }
                            
                }
                while (x8[i]==v1[i] && x8[i]!='\0' && v1[i]!='\0')
                {
                    i++;
                    j++;
                }
                // si le profil travail pour l'entreprise
                if (j==strlen(x8) && j==strlen(v1))
                {
                    ok2=1;
                }
                // sinon on passe au profil suivant
                else
                {
                    goto next2;
                }
                
                int k,l,m,n,o,p,q,r;
                k=0;
                // verifier si l'employe est un ancien collègue du chercheur d'emploi
                while (k<d-1 && ok2==1)
                {
                    l=0;m=0;n=0;o=0,p=0;q=0;r=0;ok3=0;
                    fscanf(db4,"%s",str4);
                    strcpy(tempo,str4);
                    y2=strtok(str4,",");
                    y2=strtok(NULL,",");
                    y3=strtok(NULL,",");
                    y6=strtok(NULL,",");
                    y6=strtok(NULL,",");
                    y6=strtok(NULL,",");
                    int kk=0;
                    int jj=0;
                    while (kk<strlen(tempo))
                    {
                        if (tempo[kk]==',')
                        {
                            jj++;
                            kk++;
                            if (jj==6)
                            {
                                if (tempo[kk-1]==',' && tempo[kk]=='\0')
                                {
                                    y7="";
                                }
                                
                                else
                                {
                                    y7=strtok(NULL,",");
                                }
                                
                                
                            }
                            
                        }
                        else
                        {
                            kk++;
                        }
                    }

                    while (y2[l]==nom[l] && y2[l]!='\0')
                    {
                        l++;
                        m++;
                    }
                    
                    while (y3[n]==prenom[n] && y3[n]!='\0')
                    {
                        n++;
                        o++;
                    }
                    
                    if (m==strlen(nom) && o==strlen(prenom))
                    {
                        ok3=1;
                    }

                    else
                    {
                        goto next3;
                    }
                    
                    if (ok3==1)
                    {
                        while (y7[p]!='\0')
                        {
                            if (y7[p]==x1[r])
                            {
                                p++;
                                q++;
                                r++;
                            }
                            
                            else
                            {
                                p++;
                            }
                            
                        }

                        if (q==strlen(x1))
                        {
                            ok++;
                            if (ok==1)
                            {
                                printf("voici le(s) résultat(s) de votre recherche:\n");
                            }
                            printf("Nom du (de la) collègue:%s\n",x2);
                            printf("Prénom du (de la) collègue:%s\n",x3);
                            printf("Adresse mail du (de la) collègue:%s\n",x4);
                            printf("---------------------------------------------\n");
                        }
                        
                    }
                    next3:
                    k++;
                    if (k==d-1)
                    {
                        fseek(db4,0,SEEK_SET);
                        fscanf(db4,"%*s");
                    }
                    
                }
                
                next2:
                h++;
                if (h==c-1)
                {
                    fseek(db3,0,SEEK_SET);
                    fscanf(db3,"%*s");
                }
                
            }
            
            next1:
            e++;
            if (e==a-1 && ok==0)
            {
                printf("nous n'avons pas pu trouver des résultats pour votre recherche:\n");
            }
            
        }
    }
    // Recherche par compétences 
    else if (choix==2)
    {
        // identification du chercheur d'emploi
        while (e<d-1)
        {
            f=0;g=0;ok1=0;
            int x,y;
            x=0;y=0;
            fscanf(db4,"%s",str4);
            strcpy(tempo,str4);
            y2=strtok(str4,",");
            y2=strtok(NULL,",");
            y3=strtok(NULL,",");
            y6=strtok(NULL,",");
            y6=strtok(NULL,",");
            y6=strtok(NULL,",");
            int kk=0;
            int jj=0;
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        if (tempo[kk-1]==',' && tempo[kk]=='\0')
                        {
                            y7="";
                        }
                            
                        else
                        {
                            y7=strtok(NULL,",");
                        }
                            
                            
                    }
                        
                }
                else
                {
                    kk++;
                }
            }

            while (y2[f]==nom[f] && y2[f]!='\0')
            {
                f++;
                g++;
            }

            while (y3[x]==prenom[x] && y3[x]!='\0')
            {
                x++;
                y++;
            }
            
            if (g==strlen(nom) && y==strlen(prenom))
            {
                ok1=1;
            }

            else
            {
                goto next4;
            }
            
            int i,j,k,l;
            i=0;
            // recherche des anciens collègues du chercheur d'emploi
            while (i<c-1 && ok1==1)
            {
                j=0;k=0;l=0;ok2=0;
                fscanf(db3,"%s",str3);
                strcpy(tempo,str3);
                x1=strtok(str3,",");
                x2=strtok(NULL,",");
                x3=strtok(NULL,",");
                x4=strtok(NULL,",");
                x7=strtok(NULL,",");
                x7=strtok(NULL,",");

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
                                x8=strtok(NULL,",");
                                x7="";
                            }
                            else if (tempo[kkk]==',' && tempo[kkk+1]=='\0')
                            {
                                x7="";
                                x8="";
                            }
                                        
                            else
                            {
                                int ff;
                                char cc;
                                x7=strtok(NULL,",");
                                ff=kkk+strlen(x7)+1;
                                cc=tempo[ff];
                                if (cc=='\0')
                                {
                                    x8="";
                                }
                                else
                                {
                                    x8=strtok(NULL,",");
                                }                
                            }                
                        }                        
                    }
                    else
                    {
                        kkk++;
                    }
                            
                }

                while (y7[j]!='\0')
                {
                    if (y7[j]==x1[k])
                    {
                        j++;
                        k++;
                        l++;
                    }
                    
                    else
                    {
                        j++;
                    }
                    
                }
                
                if (l==strlen(x1))
                {
                    ok2=1;
                }
                
                else
                {
                    goto next5;
                }
                
                int l,m,n,o,p,q,r,s,t,u,w;
                l=0;
                // recherche de l'entreprise pour laquelle l'employe travail
                while (l<b-1 && ok2==1)
                {
                    m=0;n=0;o=0;p=0;q=0;r=0;s=0;t=0;u=0;w=0;ok3=0;
                    fscanf(db2,"%s",str2);
                    w1=strtok(str2,",");
                    w3=strtok(NULL,",");
                    w3=strtok(NULL,",");

                    while (w1[m]==x8[m] && w1[m]!='\0' && x8[m]!='\0')
                    {
                        m++;
                        n++;
                    }

                    if (n==strlen(w1) && n==strlen(x8))
                    {
                        ok3=1;
                    }
                    else
                    {
                        goto next6;
                    }
                    
                    if (ok3==1)
                    {
                        while (y6[o]!='\0')
                        {
                            if (y6[o]==';')
                            {
                                p++;
                                o++;
                            }
                            else
                            {
                                o++;
                            }    
                        }
                        char vv[128];
                        strcpy(vv,y6);
                        if (p==0)
                        {
                            while (w3[q]!='\0')
                            {
                                if (w3[q]==y6[r])
                                {
                                    q++;
                                    r++;
                                    s++;
                                }
                                else
                                {
                                    q++;
                                }

                                if (s==strlen(y6) && w3[q]==';')
                                {
                                    w3[q]='\0';
                                    ok++;
                                    if (ok==1)
                                    {
                                        printf("voici le(s) résultat(s) de votre recherche:\n");
                                    }
                                    printf("Nom du (de la) collègue:%s\n",x2);
                                    printf("Prénom du (de la) collègue:%s\n",x3);
                                    printf("Adresse mail du (de la) collègue:%s\n",x4);
                                    printf("---------------------------------------------\n");
                                    
                                }
                                else if (s==strlen(y6) && w3[q]=='\0')
                                {
                                    w3[q]='\0';
                                    ok++;
                                    if (ok==1)
                                    {
                                        printf("voici le(s) résultat(s) de votre recherche:\n");
                                    }
                                    printf("Nom du (de la) collègue:%s\n",x2);
                                    printf("Prénom du (de la) collègue:%s\n",x3);
                                    printf("Adresse mail du (de la) collègue:%s\n",x4);
                                    printf("---------------------------------------------\n");
                                }
                                
                                
                            }    
                        }
                        
                        else
                        {
                            v=strtok(vv,";");
                            for (int mm = 0; mm < p+1; mm++)
                            {
                                t=0;u=0;w=0;
                                while (w3[t]!='\0')
                                {
                                    if (w3[t]==v[u])
                                    {
                                        t++;
                                        u++;
                                        w++;
                                    }
                                    else
                                    {
                                        w=0;
                                        t++;
                                    }
                                    
                                    if (t==strlen(v) && w3[t]==';')
                                    {
                                        ok++;
                                        w3[t]='\0';
                                        mm=p+1;
                                        if (ok==1)
                                        {
                                            printf("voici le(s) résultat(s) de votre recherche:\n");
                                        }
                                        printf("Nom du (de la) collègue:%s\n",x2);
                                        printf("Prénom du (de la) collègue:%s\n",x3);
                                        printf("Adresse mail du (de la) collègue:%s\n",x4);
                                        printf("---------------------------------------------\n");
                                    }
                                    
                                    else if (t==strlen(v) && w3[t]=='\0')
                                    {
                                        ok++;
                                        w3[t]='\0';
                                        mm=p+1;
                                        if (ok==1)
                                        {
                                            printf("voici le(s) résultat(s) de votre recherche:\n");
                                        }
                                        printf("Nom du (de la) collègue:%s\n",x2);
                                        printf("Prénom du (de la) collègue:%s\n",x3);
                                        printf("Adresse mail du (de la) collègue:%s\n",x4);
                                        printf("---------------------------------------------\n");
                                    }
                                    
                                }
                                v=strtok(NULL,";");
                            }
                            
                        }
                    }
                    
                    next6:
                    l++;
                    if (l==b-1)
                    {
                        fseek(db2,0,SEEK_SET);
                        fscanf(db2,"%*s");
                    }
                    
                    
                }
                
                next5:
                i++;
                if (i==c-1)
                {
                fseek(db3,0,SEEK_SET);
                fscanf(db3,"%*s");
                }
                
            }
            
            
            next4:
            e++;
            if (e==d-1 && ok==0)
            {
                printf("nous n'avons pas pu trouver des résultats pour vtre recherche\n");
            }       
        }   
    }
    
    fclose(db1);
    fclose(db2);
    fclose(db3);
    fclose(db4);
}