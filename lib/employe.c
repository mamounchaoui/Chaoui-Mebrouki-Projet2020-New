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
    int i,t,y,j,z,k,x,n,ok;
    char str[128];
    char* m2,*m3,*m4,*m5,*m6,*m7,*m8;
    x=0 ;
    
    FILE* db = fopen("test/employe.csv", "r+");
    FILE* fp = fopen("test/tmp.csv", "w");// fichier temporaire où on va recopier les données du fichier employe.csv avec les modifications apportées

    n=nbrligne2(db);
    fseek(db,0,SEEK_SET);
    fscanf(db,"%s",str);
    char* v="abcd";
    v=strtok(str,",");
    // recherche du profil à modifier
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
    // ajouter un compétence
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
            m2=strtok(str,",");
            m2=strtok(NULL,",");
            m3=strtok(NULL,",");
            m4=strtok(NULL,",");
            m5=strtok(NULL,",");
            m6=strtok(NULL,",");
            int jj=0;
            int kk=0;
            
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        if (tempo[kk]==',' && tempo[kk+1]!='\0')
                        {
                            m8=strtok(NULL,",");
                            m7="";
                        }
                        else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                        {
                            m7="";
                            m8="";
                        }
                        
                        else
                        {
                            int ff;
                            char cc;
                            m7=strtok(NULL,",");
                            ff=kk+strlen(m7)+1;
                            cc=tempo[ff];
                            if (cc=='\0')
                            {
                                m8=" ";
                            }
                            else
                            {
                                m8=strtok(NULL,",");
                            }
                        }
                        
                        
                    }
                    
                }
                else
                {
                    kk++;
                }
                
            } 

            // si en rencontre le profil à modifier, on fait les modifications nécessaires et le recopie dans tmp       
            if (t==x)
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s;%s,%s,%s", t, m2, m3, m4, m5, m6, compe, m7, m8);
            }
            // sinon on recopie sans faire aucune modification
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, m8);
            }
            
            t++;
        }
        goto fin;
    }
    // ajouter un collègue
    else if (choix == 2)
    {
        FILE* db3=fopen("test/employe.csv", "r");
        char str3[128];
        char tempo[128];
        int z,zz,ii,jj,kk,nn;
        char* l1,*l2,*l3;
        z=0;
        zz=nbrligne2(db3);
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
                        if (tempo[kk]==',' && tempo[kk+1]!='\0')
                        {
                            m8=strtok(NULL,",");
                            m7="";
                        }
                        else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                        {
                            m7="";
                            m8="";
                        }
                        
                        else
                        {
                            int ff;
                            char cc;
                            m7=strtok(NULL,",");
                            ff=kk+strlen(m7)+1;
                            cc=tempo[ff];
                            if (cc=='\0')
                            {
                                m8=" ";
                            }
                            else
                            {
                                m8=strtok(NULL,",");
                            }
                        }
                        
                        
                    }
                    
                }
                else
                {
                    kk++;
                }
                
            } 
            // cas où on recontre le profil qu'on souhaite modifier       
            if (t==x)
            {
                // si on arrive pas à trouver le collègue à ajouter
                if (ok==0 )
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, m8);
                }
                // collègue trouvé + profil ne contient pas de collègues + entreprise qui existe
                else if (ok==1 && strlen(m7)==0 && strlen(m8)!=0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, l1, m8);
                }
                // collègue trouvé + profil ne contient pas de collègues + entreprise qui n'existe pas
                else if (ok==1 && strlen(m7)==0 && strlen(m8)==0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,", t, m2, m3, m4, m5, m6, l1);
                }
                // cas où il n'a pas de problèmes
                else
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s;%s,%s", t, m2, m3, m4, m5, m6, l1, m7, m8);
                }
                    
            }
            // sinom on recoprie sans modifier
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, m8);
            }
            
            t++;
        }
        goto fin;
    }
    // modifier le code postal
    else if (choix == 3)
    {
        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        char tempo[128];
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
            
            int jj=0;
            int kk=0;
            
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        if (tempo[kk]==',' && tempo[kk+1]!='\0')
                        {
                            m8=strtok(NULL,",");
                            m7="";
                        }
                        else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                        {
                            m7="";
                            m8="";
                        }
                        
                        else
                        {
                            int ff;
                            char cc;
                            m7=strtok(NULL,",");
                            ff=kk+strlen(m7)+1;
                            cc=tempo[ff];
                            if (cc=='\0')
                            {
                                m8=" ";
                            }
                            else
                            {
                                m8=strtok(NULL,",");
                            }
                        }
                        
                        
                    }
                    
                }
                else
                {
                    kk++;
                }
                
            }
            // si en rencontre le profil à modifier, on fait les modifications nécessaires et le recopie dans tmp         
            if (t==x)
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, code, m6, m7, m8);
            }
            // sino on recopie sans modifier
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, m8);
            }
            
            t++;
        }
        goto fin;
        
    }
    // modifier l'entreprise
    else if (choix == 4)
    {
        FILE* db4=fopen("test/entreprise.csv", "r");
        char str4[128];
        int z,zz,ii,jj;
        char* l1,*l2;
        z=0;
        zz=nbrligne2(db4);
        fseek(db4,0,SEEK_SET);
        fscanf(db4,"%*s");

        while (z<zz-1)
        {
            ii=0;jj=0;ok=0;
            fscanf(db4,"%s",str4);
            l1=strtok(str4,",");
            l2=strtok(NULL,",");

            
            while (entrep[ii]==l2[ii]  && entrep[ii]!='\0')
            {
                ii++;
                jj++;
            }
           
            if (jj==strlen(l2) && jj==strlen(entrep))
            {
                z=zz-2;
                ok=1;
            }
            z++;
            
            
        }
        fclose(db4);
        

        fseek(db,0,SEEK_SET);
        fscanf(db,"%s",str);
        fprintf(fp,"%s",str);
        t=1;
        char tempo[128];
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
            
            int jj=0;
            int kk=0;
            
            while (kk<strlen(tempo))
            {
                if (tempo[kk]==',')
                {
                    jj++;
                    kk++;
                    if (jj==6)
                    {
                        if (tempo[kk]==',' && tempo[kk+1]!='\0')
                        {
                            m8=strtok(NULL,",");
                            m7="";
                        }
                        else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                        {
                            m7="";
                            m8="";
                        }
                        
                        else
                        {
                            int ff;
                            char cc;
                            m7=strtok(NULL,",");
                            ff=kk+strlen(m7)+1;
                            cc=tempo[ff];
                            if (cc=='\0')
                            {
                                m8=" ";
                            }
                            else
                            {
                                m8=strtok(NULL,",");
                            }
                        }
                        
                        
                    }
                    
                }
                else
                {
                    kk++;
                }
                
            }
            // si en rencontre le profil à modifier          
            if (t==x)
            {
                // cas où le profil ne contient pas d'entreprise
                if (ok==0)
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, m8);
                }
                // cas où le profil ne contient une entreprise
                else
                {
                    fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, l1);
                }
                
                
            }
            // sinon on recopie sans modifier
            else
            {
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", t, m2, m3, m4, m5, m6, m7, m8);
            }
            
            t++;
        }
        goto fin;
        
    }
       
    fin:
    fclose(db);
    fclose(fp);
    remove("test/employe.csv");
    rename("test/tmp.csv","test/employe.csv");
}
void Transitionner_profil2(char nom[128], char prenom[128])
{
    char str1[128];
    char* v1,*v2,*v3,*v4,*v5,*v6,*v7;
    int pos,ok1;
    char t[128];
    char tempo[128];

    FILE* db1=fopen("test/employe.csv", "r+");
    FILE* db2=fopen("test/chercheurdemploi.csv", "r+");
    FILE* db3=fopen("test/tmp.csv", "w"); // fichier qui contiendra les données d'employe.csv après avoir transitionné le profil

    int a,b;
    a=nbrligne2(db1);
    b=nbrligne2(db2);

    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    int c,d,e,f;
    c=0;ok1=0;
    // identification du profil à trensitionner et l'ajoueter dans le fichier chercheurdemploi.csv
    while (c<a-1)
    {
        d=0;e=0;f=0;
        fscanf(db1,"%s",str1);
        strcpy(tempo,str1);
        v1=strtok(str1,",");
        v2=strtok(NULL,",");
        v3=strtok(NULL,",");
        v4=strtok(NULL,",");
        v5=strtok(NULL,",");
        v6=strtok(NULL,",");
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
                        v7="";
                    }
                        
                    // cas où la personne a au moins un ancien collègue
                    else
                    {
                        v7=strtok(NULL,",");
                    }
                        
                        
                }
                    
            }
            else
            {
                kk++;
            }
        }

        while (v2[d]==nom[d] && v2[d]!='\0' && nom[d]!='\0')
        {
            d++;
            e++;
        }
        d=0;

        while (v3[d]==prenom[d] && v3[d]!='\0' && prenom[d]!='\0')
        {
            d++;
            f++;
        }

        if (e==strlen(v2) && e==strlen(nom) && f==strlen(v3) && f==strlen(prenom))
        {
            ok1++;
            pos=c;
            c=a-1;
            fseek(db2,0,SEEK_END);
            // ajout dans le fichier chercheurdemploi.csv
            fprintf(db2,"\n%d,%s,%s,%s,%s,%s,%s",b,v2,v3,v4,v5,v6,v7);
        }   
        c++;
        // cas où on a pas pu identifier le profil
        if (c==a-1 && ok1==0)
        {
            printf("nous n'avons pas pu vous identifier\n");
            return;
        }
        strcpy(t,v1);// sauvegarde le l'id du profil à transitionner 
    }

    char* x2,*x3,*x4,*x5,*x6,*x7,*x8;
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%s",str1);
    fprintf(db3,"%s",str1);
    int g;
    g=0;

    // recopie des autres profils dans le fichier tmp.csv
    while (g<a-2)
    {
        fscanf(db1,"%s",str1);
        // si on rencontre le profil à transitionner , on passe au profil suivant
        if (g==pos)
        {
            fscanf(db1,"%s",str1);
        }
        strcpy(tempo,str1);
        x2=strtok(str1,",");
        x2=strtok(NULL,",");
        x3=strtok(NULL,",");
        x4=strtok(NULL,",");
        x5=strtok(NULL,",");
        x6=strtok(NULL,",");
        int jj=0;
        int kk=0;

        // gestion des attributs collegues et entreprise   
        while (kk<strlen(tempo))
        {
            if (tempo[kk]==',')
            {
                jj++;
                kk++;
                if (jj==6)
                {
                    if (tempo[kk]==',' && tempo[kk+1]!='\0')
                    {
                        x8=strtok(NULL,",");
                        x7="";
                    }
                    else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                    {
                        x7="";
                        x8="";
                    }
                        
                    else
                    {
                        int ff;
                        char cc;
                        x7=strtok(NULL,",");
                        ff=kk+strlen(x7)+1;
                        cc=tempo[ff];
                        if (cc=='\0')
                        {
                            x8=" ";
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
                kk++;
            }
                
        }
        // ajout du profil dans le fichier tmp.csv
        fprintf(db3,"\n%d,%s,%s,%s,%s,%s,%s,%s",g+1,x2,x3,x4,x5,x6,x7,x8);
        g++;
    }
    
    
    fclose(db1);
    fclose(db2);
    fclose(db3);

    remove("test/employe.csv");// suppresion du fichier employe de départ
    rename("test/tmp.csv","test/employe.csv");// renommage du fichier tmp qui contient les données de employe à jour

    char str4[128];
    char str5[128];
    char *w1,*w2,*w3,*w4,*w5,*w6,*w7,*w8;

    FILE* db4=fopen("test/chercheurdemploi.csv", "r");
    FILE* db5=fopen("test/employe.csv", "r");
    FILE* db6=fopen("test/tmp1.csv", "w");// fichier qui contiendra les données de chercheurdemploi après avoir ajuster l'attribut collegues
    FILE* db7=fopen("test/tmp2.csv", "w");// idem avec le fichier employe

    int h,i;
    h=nbrligne2(db4);
    i=nbrligne2(db5);

    fseek(db4,0,SEEK_SET);
    fseek(db5,0,SEEK_SET);

    fscanf(db4,"%s",str4);
    fprintf(db6,"%s",str4);

    fscanf(db5,"%s",str5);
    fprintf(db7,"%s",str5);

    int j,k,l,m,n,p;
    char v[128];
    j=0;
    // char cc;

    // ajustement de l'attribut collegues des profils de chercheurdemploi
    while (j<h-1)
    {
        k=0;l=0;m=0;p=0;
        fscanf(db4,"%s",str4);
        strcpy(tempo,str4);
        w1=strtok(str4,",");
        w2=strtok(NULL,",");
        w3=strtok(NULL,",");
        w4=strtok(NULL,",");
        w5=strtok(NULL,",");
        w6=strtok(NULL,",");
        // w7=strtok(NULL,",");

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
                        w7="";
                    }
                        
                    // cas où la personne a au moins un ancien collègue
                    else
                    {
                        w7=strtok(NULL,",");
                    }
                        
                        
                }
                    
            }
            else
            {
                kk++;
            }
        }
        
        // on compte le nombre de collègues du profil
        while (w7[k]!='\0' )
        {
            // cc=w7[k];
            // printf("%c\n",cc);
            if(w7[k]==t[l])
            {
                k++;
                l++;
                m++;
                if (m==strlen(t))
                {
                    goto suiv;
                }    
            }
            else
            {
                k++;
                l=0;
                m=0;
            }
        }

        suiv:
        // cas où le profil a plusieurs collègues
        if (m==strlen(t) && m!=strlen(w7))
        {
            n=k-m-1;
            // cc=w7[n];
            // printf("%c\n",cc);
            if (w7[n]==';' && w7[k]==';')
            {
                while (p<n)
                {
                    v[p]=w7[p];
                    p++;
                }
                while (w7[k]!='\0')
                {
                    v[p]=w7[k];
                    p++;
                    k++;
                }
                v[p]='\0';   
                fprintf(db6,"\n%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, v);
            }
            else if (w7[n]!=';' && w7[k]==';')
            {
                k++;
                while (w7[k]!='\0')
                {
                    v[p]=w7[k];
                    p++;
                    k++;
                }
                // strcpy(vv,v);
                v[p]='\0';
                printf("%s\n",v);
                fprintf(db6,"\n%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, v);
            }
            else if (w7[n]==';' && w7[k]=='\0')
            {
                while (p<n)
                {
                    v[p]=w7[p];
                    p++;
                }
                v[p]='\0';
                fprintf(db6,"\n%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, v);
            }
                    
        }
        // cas où le profil a un seul collègue
        else if (m==strlen(t) && m==strlen(w7))
        {
            fprintf(db6,"\n%s,%s,%s,%s,%s,%s,",w1, w2, w3, w4, w5, w6);
        }
            
        else
        {
            fprintf(db6,"\n%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, w7);
        }
            
        j++;
    }

    j=0;
    // ajustement de l'attribut collegues des profils de employe
    while (j<i-1)
    {
        k=0;l=0;m=0;p=0;
        fscanf(db5,"%s",str5);
        strcpy(tempo,str5);
        w1=strtok(str5,",");
        w2=strtok(NULL,",");
        w3=strtok(NULL,",");
        w4=strtok(NULL,",");
        w5=strtok(NULL,",");
        w6=strtok(NULL,",");
        // w7=strtok(NULL,",");
        // w8=strtok(NULL,",");

        int jj=0;
        int kk=0;
        // gestion des attributs collegues et entreprise   
        while (kk<strlen(tempo))
        {
            // c=tmp[k];
            // printf("%c\n",c);
            if (tempo[kk]==',')
            {
                jj++;
                kk++;
                if (jj==6)
                {
                    if (tempo[kk]==',' && tempo[kk+1]!='\0')
                    {
                        w8=strtok(NULL,",");
                        w7="";
                    }
                    else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                    {
                        w7="";
                        w8="";
                    }
                        
                    else
                    {
                        int ff;
                        char cc;
                        w7=strtok(NULL,",");
                        ff=kk+strlen(w7)+1;
                        cc=tempo[ff];
                        if (cc=='\0')
                        {
                            w8=" ";
                        }
                        else
                        {
                            w8=strtok(NULL,",");
                        }
                    }
                        
                        
                }
                    
            }
            else
            {
                kk++;
            }
                
        }

        while (w7[k]!='\0' )
        {
            // cc=w7[k];
            // printf("%c\n",cc);
            if(w7[k]==t[l])
            {
                k++;
                l++;
                m++;
                if (m==strlen(t))
                {
                    goto suiv2;
                }
                
            }
            else
            {
                k++;
                l=0;
                m=0;
            }
        }

        suiv2:
        // cas où le profil a plusieurs collègues
        if (m==strlen(t) && m!=strlen(w7))
        {
            n=k-m-1;
            // cc=w7[n];
            // printf("%c\n",cc);
            if (w7[n]==';' && w7[k]==';')
            {
                while (p<n)
                {
                    v[p]=w7[p];
                    p++;
                }
                while (w7[k]!='\0')
                {
                    v[p]=w7[k];
                    p++;
                    k++;
                }
                v[p]='\0';   
                fprintf(db7,"\n%s,%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, v,w8);
            }
            else if (w7[n]!=';' && w7[k]==';')
            {
                k++;
                while (w7[k]!='\0')
                {
                    v[p]=w7[k];
                    p++;
                    k++;
                }
                // strcpy(vv,v);
                v[p]='\0';
                fprintf(db7,"\n%s,%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, v, w8);
            }
            else if (w7[n]==';' && w7[k]=='\0')
            {
                while (p<n)
                {
                    v[p]=w7[p];
                    p++;
                }
                v[p]='\0';
                fprintf(db7,"\n%s,%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, v, w8);
            }
                    
        }
        // cas où le profil a un seul collegue
        else if (m==strlen(t) && m==strlen(w7))
        {
            fprintf(db7,"\n%s,%s,%s,%s,%s,%s,,%s",w1, w2, w3, w4, w5, w6, w8);
        }
            
        else
        {
            fprintf(db7,"\n%s,%s,%s,%s,%s,%s,%s,%s",w1, w2, w3, w4, w5, w6, w7, w8);
        }
            
        j++;
    }
    fclose(db6);
    fclose(db7);
    remove("test/chercheurdemploi.csv");
    rename("test/tmp1.csv","test/chercheurdemploi.csv");// nouvau fichier chercheurdemploi.csv aves les données à jour
    remove("test/employe.csv");
    rename("test/tmp2.csv","test/employe.csv");// nouvau fichier employe.csv aves les données à jour

    FILE* db8=fopen("test/employe.csv", "r");
    FILE* db9=fopen("test/tmp3.csv", "w");// fichier qui contiendra les données de employe.csv après avoir décrémenté à l'attribut collègues tous les id qui sont supérieurs à l'id du profil transitionné
    int aa,bb;
    char *t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8;
    char str2[128];
    aa=nbrligne2(db8);
    fseek(db8,0,SEEK_SET);
    fscanf(db8,"%s",str2);
    fprintf(db9,"%s",str2);
    bb=0;
    // on décrémente les id de lattribut collegues qui doivent être décrémentés du fichier employe
    while (bb<aa-1)
    {
        k=0;l=0;m=0;p=0;
        fscanf(db8,"%s",str2);
        strcpy(tempo,str2);
        t1=strtok(str2,",");
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
                            t8=" ";
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
        while (t7[k]!='\0' )
        {
            if (t7[k]==';')
            {
                k++;
                l++;
            }
            else
            {
                k++;
            }
            
            
        }
        int dd;
        char* pp;
        // cas où le profil n'a pas de collègues
        if (l==0)
        {
            dd=atoi(t7);
            if (dd>pos)
            {
                fprintf(db9,"\n%s,%s,%s,%s,%s,%s,%d,%s",t1,t2,t3,t4,t5,t6,dd-1,t8);
            }
            else
            {
                fprintf(db9,"\n%s",tempo);
            }
            
        }
        // cas où le profil à plusieurs collègues
        else if (l>0)
        {
            int tab[128];
            char collegue[128];
            int hh=0;
            pp=strtok(t7,";");
            char qq[128]="a";
            for (int gg = 0; gg < l+1; gg++)
            {
                dd=atoi(pp);
                if (dd>pos)
                {
                    tab[hh]=dd-1;
                    hh++;
                }
                else
                {
                    tab[hh]=dd;
                    hh++;
                }
                pp=strtok(NULL,";");   
            }
            for (int gg = 0; gg < l+1; gg++)
            {
                m=0;
                if (gg==l)
                {
                    sprintf(collegue, "%d",tab[gg]);
                }
                else
                {
                    sprintf(collegue, "%d;",tab[gg]);
                }
                
                
                while(m<strlen(collegue)){
                    qq[p]=collegue[m];
                    m++;
                    p++;
                }
            }
            fprintf(db9,"\n%s,%s,%s,%s,%s,%s,%s,%s",t1,t2,t3,t4,t5,t6,qq,t8);
            
        }
        bb++;
    }
    FILE* db10=fopen("test/chercheurdemploi.csv", "r");
    FILE* db11=fopen("test/tmp4.csv", "w");// fichier qui contiendra les données de chercheurdemploi.csv après avoir décrémenté à l'attribut collègues tous les id qui sont supérieurs à l'id du profil transitionné
    aa=nbrligne2(db10);
    fseek(db10,0,SEEK_SET);
    fscanf(db10,"%s",str2);
    fprintf(db11,"%s",str2);
    bb=0;
    // on décrémente les id de lattribut collegues qui doivent être décrémentés du fichier chercheurdemploi
    while (bb<aa-1)
    {
        k=0;l=0;m=0;p=0;
        fscanf(db10,"%s",str2);
        strcpy(tempo,str2);
        t1=strtok(str2,",");
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
        while (t7[k]!='\0' )
        {
            if (t7[k]==';')
            {
                k++;
                l++;
            }
            else
            {
                k++;
            }
            
            
        }
        int dd;
        char* pp;
        // cas où le profil a un seul collegue
        if (l==0)
        {
            dd=atoi(t7);
            if (dd>pos)
            {
                fprintf(db11,"\n%s,%s,%s,%s,%s,%s,%d",t1,t2,t3,t4,t5,t6,dd-1);
            }
            else
            {
                fprintf(db11,"\n%s",tempo);
            }
            
        }
        // cas où le profil a plusieurs collegues
        else if (l>0)
        {
            int tab[128];
            char collegue[128];
            int hh=0;
            pp=strtok(t7,";");
            char qq[128]="a";
            for (int gg = 0; gg < l+1; gg++)
            {
                dd=atoi(pp);
                if (dd>pos)
                {
                    tab[hh]=dd-1;
                    hh++;
                }
                else
                {
                    tab[hh]=dd;
                    hh++;
                }
                pp=strtok(NULL,";");   
            }
            for (int gg = 0; gg < l+1; gg++)
            {
                m=0;
                if (gg==l)
                {
                    sprintf(collegue, "%d",tab[gg]);
                }
                else
                {
                    sprintf(collegue, "%d;",tab[gg]);
                }
                
                
                while(m<strlen(collegue)){
                    qq[p]=collegue[m];
                    m++;
                    p++;
                }
            }
            fprintf(db11,"\n%s,%s,%s,%s,%s,%s,%s",t1,t2,t3,t4,t5,t6,qq);
            
        }
        bb++;
    }

    fclose(db8);
    fclose(db9);
    fclose(db10);
    fclose(db11);
    remove("test/chercheurdemploi.csv");
    rename("test/tmp4.csv","test/chercheurdemploi.csv");
    remove("test/employe.csv");
    rename("test/tmp3.csv","test/employe.csv");

    return;

}
// cette fonction est exactement basée sur le principe de Transitionner_profil2
void Supprimer_profil2(char nom[128], char prenom[128])
{
    int i,t,y,j,z,k,x,w;
    char str[128];
    char* t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8;;
    char* v1,*v2,*v3;
    char tt[128];
    char tempo[128];
    FILE* db=fopen("test/employe.csv", "r+");
    FILE* fp=fopen("test/tmp.csv", "w");// contiendra les données de employe à jour
    w=nbrligne2(db);
    fseek(db,0,SEEK_SET);
    fscanf(db,"%*s");
   
    int ok;
    x=0;
    // identification et suppression du profil à supprimer
    while (x<w-1 )
    {
        ok=0;
        fscanf(db,"%s",str);
        v1=strtok(str,",");
        v2=strtok(NULL,",");
        i=0;
        y=0;
        while (v2[i]==nom[i] && v2[i]!='\0')
        {
            y++;
            i++;

        }
        j=0;
        z=0;
        v3=strtok(NULL,",");
        while (v3[j]==prenom[j] && v3[j]!='\0')
        {
            z++;
            j++;

        }
        t=strlen(nom);
        k=strlen(prenom);
        if (y==t && z==k && k==strlen(v3) && y==strlen(v2))
        {
            ok=1;
            strcpy(tt,v1);
            fseek(db,0,SEEK_SET);
            fscanf(db,"%s",str);
            fprintf(fp,"%s",str);
            int m=1;

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
                
                int jj=0;
                int kk=0;
                
                while (kk<strlen(tempo))
                {
                    if (tempo[kk]==',')
                    {
                        jj++;
                        kk++;
                        if (jj==6)
                        {
                            if (tempo[kk]==',' && tempo[kk+1]!='\0')
                            {
                                t8=strtok(NULL,",");
                                t7="";
                            }
                            else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                            {
                                t7="";
                                t8="";
                            }
                            
                            else
                            {
                                int ff;
                                char cc;
                                t7=strtok(NULL,",");
                                ff=kk+strlen(t7)+1;
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
                        kk++;
                    }
                    
                }
                
                fprintf(fp,"\n%d,%s,%s,%s,%s,%s,%s,%s", m, t2, t3, t4, t5, t6, t7, t8);
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
        if (x==w-1 && ok==0)
        {
            printf("on arrive pas à vous identifier\n");
            goto fin2;
        }
        
    }
    fin:
    fclose(db);
    fclose(fp);
    remove("test/employe.csv");
    rename("test/tmp.csv","test/employe.csv");

    char str2[128];
    FILE* db1=fopen("test/employe.csv", "r+");
    FILE* db2=fopen("test/tmp1.csv", "w");

    int aa;
    aa=nbrligne2(db1);
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%s",str2);
    fprintf(db2,"%s",str2);
    char v[128];
    int l,m,n,p;
    int bb;
    bb=0;
    while (bb<aa-1)
    {
        k=0;l=0;m=0;p=0;
        fscanf(db1,"%s",str2);
        strcpy(tempo,str2);
        t1=strtok(str2,",");
        t2=strtok(NULL,",");
        t3=strtok(NULL,",");
        t4=strtok(NULL,",");
        t5=strtok(NULL,",");
        t6=strtok(NULL,",");
        int jj=0;
        int kk=0;
                
        while (kk<strlen(tempo))
        {
            if (tempo[kk]==',')
            {
                jj++;
                kk++;
                if (jj==6)
                {
                    if (tempo[kk]==',' && tempo[kk+1]!='\0')
                    {
                        t8=strtok(NULL,",");
                        t7="";
                    }
                    else if (tempo[kk]==',' && tempo[kk+1]=='\0')
                    {
                        t7="";
                        t8="";
                    }
                            
                    else
                    {
                        int ff;
                        char cc;
                        t7=strtok(NULL,",");
                        ff=kk+strlen(t7)+1;
                        cc=tempo[ff];
                        if (cc=='\0')
                        {
                            t8=" ";
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
                kk++;
            }
                    
        }

        while (t7[k]!='\0' )
        {
            if(t7[k]==tt[l])
            {
                k++;
                l++;
                m++;
                if (m==strlen(tt))
                {
                    goto suiv2;
                }
                
            }
            else
            {
                k++;
                l=0;
                m=0;
            }
        }

        suiv2:
        if (m==strlen(tt) && m!=strlen(t7))
        {
            n=k-m-1;
            if (t7[n]==';' && t7[k]==';')
            {
                while (p<n)
                {
                    v[p]=t7[p];
                    p++;
                }
                while (t7[k]!='\0')
                {
                    v[p]=t7[k];
                    p++;
                    k++;
                }
                v[p]='\0';   
                fprintf(db2,"\n%s,%s,%s,%s,%s,%s,%s,%s",t1, t2, t3, t4, t5, t6, v,t8);
            }
            else if (t7[n]!=';' && t7[k]==';')
            {
                k++;
                while (t7[k]!='\0')
                {
                    v[p]=t7[k];
                    p++;
                    k++;
                }
                // strcpy(vv,v);
                v[p]='\0';
                // printf("%s\n",v);
                fprintf(db2,"\n%s,%s,%s,%s,%s,%s,%s,%s",t1, t2, t3, t4, t5, t6, v, t8);
            }
            else if (t7[n]==';' && t7[k]=='\0')
            {
                while (p<n)
                {
                    v[p]=t7[p];
                    p++;
                }
                v[p]='\0';
                fprintf(db2,"\n%s,%s,%s,%s,%s,%s,%s,%s",t1, t2, t3, t4, t5, t6, v, t8);
            }
                    
        }
        else if (m==strlen(tt) && m==strlen(t7))
        {
            fprintf(db2,"\n%s,%s,%s,%s,%s,%s,,%s",t1, t2, t3, t4, t5, t6, t8);
        }
            
        else
        {
            fprintf(db2,"\n%s,%s,%s,%s,%s,%s,%s,%s",t1, t2, t3, t4, t5, t6, t7, t8);
        }
            
        bb++;
    }
    fclose(db1);
    fclose(db2);
    remove("test/employe.csv");
    rename("test/tmp1.csv","test/employe.csv");

    FILE* db3=fopen("test/employe.csv", "r+");
    FILE* db4=fopen("test/tmp2.csv", "w");

    aa=nbrligne2(db3);
    fseek(db3,0,SEEK_SET);
    fscanf(db3,"%s",str2);
    fprintf(db4,"%s",str2);
    bb=0;
    while (bb<aa-1)
    {
        k=0;l=0;m=0;p=0;
        fscanf(db3,"%s",str2);
        strcpy(tempo,str2);
        t1=strtok(str2,",");
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
                            t8=" ";
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
        while (t7[k]!='\0' )
        {
            if (t7[k]==';')
            {
                k++;
                l++;
            }
            else
            {
                k++;
            }
            
            
        }
        int dd;
        char* pp;
        if (l==0)
        {
            dd=atoi(t7);
            if (dd>x)
            {
                fprintf(db4,"\n%s,%s,%s,%s,%s,%s,%d,%s",t1,t2,t3,t4,t5,t6,dd-1,t8);
            }
            else
            {
                fprintf(db4,"\n%s",tempo);
            }
            
        }
        else if (l>0)
        {
            int tab[128];
            char collegue[128];
            int hh=0;
            pp=strtok(t7,";");
            char qq[128]="a";
            for (int gg = 0; gg < l+1; gg++)
            {
                dd=atoi(pp);
                if (dd>x)
                {
                    tab[hh]=dd-1;
                    hh++;
                }
                else
                {
                    tab[hh]=dd;
                    hh++;
                }
                pp=strtok(NULL,";");   
            }
            for (int gg = 0; gg < l+1; gg++)
            {
                m=0;
                if (gg==l)
                {
                    sprintf(collegue, "%d",tab[gg]);
                }
                else
                {
                    sprintf(collegue, "%d;",tab[gg]);
                }
                
                
                while(m<strlen(collegue)){
                    qq[p]=collegue[m];
                    m++;
                    p++;
                }
            }
            fprintf(db4,"\n%s,%s,%s,%s,%s,%s,%s,%s",t1,t2,t3,t4,t5,t6,qq,t8);
            
        }
        
        
        bb++;
    }
    fclose(db3);
    fclose(db4);
    
    remove("test/employe.csv");
    rename("test/tmp2.csv","test/employe.csv");

    fin2:
    return;
}
void Recherche_par_poste2(char nom[128], char prenom[128], int choix)
{
    char str1[128];
    char str2[128];
    char str3[128];
    int ok,okk,ok1,ok2,ok3,ok4,ok5,ok6;
    int m,n,nn;

    FILE *db1 = fopen("test/poste.csv", "r");
    FILE *db2 = fopen("test/entreprise.csv", "r");
    FILE* db3 = fopen("test/employe.csv", "r");
    m=nbrligne2(db1);
    n=nbrligne2(db2);
    nn=nbrligne2(db3);
    
   
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

            if (ii==strlen(nom) && ll==strlen(prenom) && ii==strlen(x2) && ll==strlen(x3))
            {
                ok1=1;
                okk++;
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

            if (ii==strlen(nom) && ll==strlen(prenom) && ii==strlen(x2) && ll==strlen(x3))
            {
                ok1=1;
                okk++;
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
void Rechercher_par_anciencollegue2(char nom[128], char prenom[128], char entreprise[128], int choix)
{
    char str1[128];
    char str2[128];
    char str3[128];
    char coll[128];
    char identrep[128];
    char compe[128];
    int a,b,c,pos;

    FILE *db1 = fopen("test/poste.csv", "r");
    FILE *db2 = fopen("test/entreprise.csv", "r");
    FILE* db3 = fopen("test/employe.csv", "r");
    a=nbrligne2(db1);
    b=nbrligne2(db2);
    c=nbrligne2(db3);
    
   
    fseek(db1,0,SEEK_SET);
    fseek(db2,0,SEEK_SET);
    fseek(db3,0,SEEK_SET);
    fscanf(db1,"%*s");
    fscanf(db2,"%*s");
    fscanf(db3,"%*s");

    char* v;
    char* v1,*v3;
    char* y1,*y2;
    char* w1,*w2,*w3,*w4,*w5;
    char* x2,*x3,*x4,*x5;
    int e,f,g,h;
    int ok,ok1,ok2,ok3,ok4,ok5,ok7,ok8;
    int x,y,z;
    
    e=0;
    ok1=0;
    if (choix==1)
    {
        x=0;ok=0;
        while (x<b-1)
        {
            y=0;z=0;
            fscanf(db2,"%s",str2);
            y1=strtok(str2,",");
            y2=strtok(NULL,",");

            while (y2[y]==entreprise[y] && y2[y]!='\0')
            {
                y++;
                z++;
            }
            if (z==strlen(y2) && z==strlen(entreprise))
            {
                ok=1;
                strcpy(identrep,y1);
                x=b-1;
            }
            else
            {
                x++;
            }
            if (x==b-1 && ok==0)
            {
                printf("on n'a pas pu trouver cette entreprise\n");
            }
            
                
        }
        while (e<c-1 && ok==1)
        {
            f=0;g=0;h=0;
            fscanf(db3,"%s",str3);
            x2=strtok(str3,",");
            x2=strtok(NULL,",");
            x3=strtok(NULL,",");
            x5=strtok(NULL,",");
            x5=strtok(NULL,",");
            x5=strtok(NULL,",");
            x5=strtok(NULL,",");
            // x6=strtok(NULL,",");

            while (x2[f]==nom[f] && x2[f]!='\0' && nom[f]!='\0')
            {
                f++;
                g++;
            }
            f=0;
            while (x3[f]==prenom[f] && x3[f]!='\0' && prenom[f]!='\0')
            {
                f++;
                h++;
            }
            if (g==strlen(x2) && g==strlen(nom) && h==strlen(x3) && h==strlen(prenom))
            {
                ok1++;
                strcpy(coll,x5);
                // strcpy(entrep,x6);
                pos=e;
                e=c-1;
            }
            else
            {
                goto next1;
            }
            int i,j,k,l;
            i=0;
            fseek(db3,0,SEEK_SET);
            fscanf(db3,"%*s");
            ok2=0;
            while (i<c-2 && ok1!=0)
            {
                j=0;k=0;l=0;ok3=0;
                if (i==pos)
                {
                    fscanf(db3,"%s",str3);
                }
                
                fscanf(db3,"%s",str3);
                w1=strtok(str3,",");
                w2=strtok(NULL,",");
                w3=strtok(NULL,",");
                w4=strtok(NULL,",");
                w5=strtok(NULL,",");
                w5=strtok(NULL,",");
                w5=strtok(NULL,",");
                w5=strtok(NULL,",");
                while (identrep[j]!='\0')
                {
                    if (identrep[j]==w5[k])
                    {
                        j++;
                        k++;
                        l++;
                    }
                    else
                    {
                        j++;
                        k=0;
                        l=0;
                    }
                    
                    if (l==strlen(w5))
                    {
                        ok3=1;
                    }
                    
                }
                j=0;k=0;l=0;
                while (coll[j]!='\0')
                {
                if (coll[j]==w1[k])
                {
                    j++;
                    k++;
                    l++;
                }
                else
                {
                    j++;
                    k=0;
                    l=0;
                }
                if (l==strlen(w1))
                {
                        ok2++;
                        if (ok2==1 && ok3==1)
                        {
                            printf("Voici les résultats de votre recherche:\n");
                        }
                        if (ok2>0 && ok3==1)
                        {
                            printf("Nom du (de la) collègue:%s\n",w2);
                            printf("Prénom du (de la) collègue:%s\n",w3);
                            printf("Adresse mail du (de la) collègue:%s\n",w4);
                            
                            printf("---------------------------------------------\n");
                        }
                        
                        

                    }
                    
                }
                i++;
                if (i==c-2 && ok2==0)
                {
                    printf("on a pas pu trouver des résultats pour votre recherche \n");
                }
                
            }
            
            next1:
            e++;
            if (e==c-1 && ok1==0)
            {
                printf("on a pas pu vous identifier\n");
            }
            
        }
    }
    
    else if (choix==2)
    {
        while (e<c-1)
        {
            f=0;g=0;h=0;
            fscanf(db3,"%s",str3);
            x2=strtok(str3,",");
            x2=strtok(NULL,",");
            x3=strtok(NULL,",");
            x4=strtok(NULL,",");
            x4=strtok(NULL,",");
            x4=strtok(NULL,",");
            x5=strtok(NULL,",");
            // x6=strtok(NULL,",");

            while (x2[f]==nom[f] && x2[f]!='\0' && nom[f]!='\0')
            {
                f++;
                g++;
            }
            f=0;
            while (x3[f]==prenom[f] && x3[f]!='\0' && prenom[f]!='\0')
            {
                f++;
                h++;
            }
            if (g==strlen(x2) && g==strlen(nom) && h==strlen(x3) && h==strlen(prenom))
            {
                ok1++;
                strcpy(coll,x5);
                // strcpy(entrep,x6);
                strcpy(compe,x4);
                pos=e;
                e=c-1;
            }
            else
            {
                goto next2;
            }

            int i,j,k,l,m,n,o,p;
            i=0;ok=0;
            while (i<a-1 && ok1!=0)
            {
                j=0;k=0;l=0;m=0;ok4=0;ok5=0;
                fscanf(db1,"%s",str1);
                v1=strtok(str1,",");
                v3=strtok(NULL,",");
                v3=strtok(NULL,",");

                while (v3[j]!='\0')
                {
                    if (v3[j]==';')
                    {
                        j++;
                        k++;
                    }
                    else
                    {
                        j++;
                    }    
                }
                j=0;
                if (k==0)
                {
                    while (compe[j]!='\0')
                    {
                        if (compe[j]==v3[l])
                        {
                            j++;
                            l++;
                            m++;
                        }
                        else
                        {
                            j++;
                            l=0;
                            m=0;
                        }
                        if (m==strlen(v3))
                        {
                            ok4=1;
                            compe[j]='\0';
                        }    
                    }
        
                }

                else
                {
                    v=strtok(v3,";");
                    for (int mm = 0; mm < k+1; mm++)
                    {
                        n=0;o=0;p=0;
                        while (compe[n]!='\0')
                        {
                            if (compe[n]==v[o])
                            {
                                n++;
                                o++;
                                p++;
                            }
                            else
                            {
                                o=0;
                                p=0;
                                n++;
                            }
                                        
                            if (p==strlen(v) && compe[n]==';')
                            {
                                compe[n]='\0';
                                ok4=1;   
                                mm=k+1;           
                            }
                                        
                            else if (p==strlen(v) && compe[n]=='\0')
                            {
                                compe[n]='\0';
                                ok4=1;
                                mm=k+1;
                            }
                                        
                        }
                        v=strtok(NULL,";");
                    }
                }
                if (ok4==1)
                {
                    ok5=1;
                }
                else
                {
                    goto next3;
                }
                
                fseek(db3,0,SEEK_SET);
                fscanf(db3,"%*s");
                int q,r,s,t;
                q=0;
                ok8=0;
                while (q<c-2 && ok5==1)
                {
                    r=0;s=0;t=0;ok7=0;
                    if (q==pos)
                    {
                        fscanf(db3,"%s",str3);
                    }
                    
                    fscanf(db3,"%s",str3);
                    w1=strtok(str3,",");
                    w2=strtok(NULL,",");
                    w3=strtok(NULL,",");
                    w4=strtok(NULL,",");
                    w5=strtok(NULL,",");
                    w5=strtok(NULL,",");
                    w5=strtok(NULL,",");
                    w5=strtok(NULL,",");
                    // while (entrep[r]!='\0')
                    // {
                    //     if (entrep[r]==w5[s])
                    //     {
                    //         r++;
                    //         s++;
                    //         t++;
                    //     }
                    //     else
                    //     {
                    //         r++;
                    //         s=0;
                    //         t=0;
                    //     }
                        
                    //     if (t==strlen(w5))
                    //     {
                    //         ok6=1;
                    //     }
                        
                    // }
                    // r=0;s=0;t=0;
                    while (w5[r]!='\0')
                    {
                        if (w5[r]==v1[s])
                        {
                            r++;
                            s++;
                            t++;
                        }
                        else
                        {
                            r++;
                            s=0;
                            t=0;
                        }
                        
                        if (t==strlen(v1))
                        {
                            ok7=1;
                        }
                        
                    }
                    r=0;s=0;l=0;
                    while (coll[r]!='\0')
                    {
                        if (coll[r]==w1[s])
                        {
                            r++;
                            s++;
                            l++;
                        }
                        else
                        {
                            r++;
                            s=0;
                            l=0;
                        }
                        if (l==strlen(w1))
                        {
                            ok8++;
                            if (ok8==1 && ok7==1)
                            {
                                printf("Voici les résultats de votre recherche:\n");
                            }
                                
                            if (ok7==1 && ok8>0)
                            {
                                ok++;
                                printf("Nom du (de la) collègue:%s\n",w2);
                                printf("Prénom du (de la) collègue:%s\n",w3);
                                printf("Adresse mail du (de la) collègue:%s\n",w4);
                                printf("---------------------------------------------\n");
                            }
                            
                            // if (ok7==1 && ok8>0 && ok6==1)
                            // {
                            //     printf("Nom du (de la) collègue:%s\n",w2);
                            //     printf("Prénom du (de la) collègue:%s\n",w3);
                            //     printf("Adresse mail du (de la) collègue:%s\n",w4);
                            //     printf("Actuellement cette personne travail pour la même entreprise que vous\n");
                            //     printf("---------------------------------------------\n");
                            // }
                        }
                        k=0;l=0;    
                        
                    }
                    q++;   
                    
                }
                
                
                next3:
                i++;
                if (i==a-1)
                {
                    fseek(db3,0,SEEK_SET);
                    fscanf(db3,"%*s");
                }
                
            }
            if (e==c-1 && ok==0) //???????
            {
                printf("Nous n'avons pas pu trouver des résultats pour votre recherche\n");
            }
            next2:
            e++;
            if (e==c-1 && ok1==0)
            {
                printf("Nous n'avons pas pu vous indentifier\n");
            }
                
        }
    }

    
    fclose(db1);
    fclose(db2);
    fclose(db3);
}
