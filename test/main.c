
#include "chercheurdemploi.h"
#include "employe.h"
#include "entreprise.h"
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int tests_executes = 0;

int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)


#define TEST(x) tests_executes += 1;    \
                if(x)                   \
                {                       \
                    tests_reussis += 1; \
                    printf("[SUCCES] ");\
                }                       \
                else                    \
                {                       \
                    printf("[ECHEC ] ");\
                }                       \
                printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");


void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("[SEGFAULT]\n");
    printf("%d/%d\n", tests_reussis, tests_executes);
    exit(tests_reussis - tests_executes);
}

int main()
{
    FILE *db1 = fopen("test/chercheurdemploi.csv", "r");
    FILE *db3 = fopen("test/employe.csv", "r");
    FILE *db4 = fopen("test/entreprise.csv", "r");
    FILE *db5 = fopen("test/poste.csv", "r");
    // tests pour 'entreprise'

    // tests pour 'chercheurdemploi'
    // tests nbrligne

    TEST(nbrligne(db1) == 4);
    TEST(nbrligne(db3) == 4);
    TEST(nbrligne(db4) == 5);
    TEST(nbrligne(db5) == 5);

    // // tests Creer_profil
    {
    int a;
    char nom[128]="Balança";
    char prenom[128]="Maxime";
    char mail[128]="maxbalança65@gmail.com";
    char code_postal[128]="33003";
    char competence[128]="theatre";
    char ancien_collegue[128]="Bartaire,Adrien";
    char str[128];
    // char* v1,*v2,*v3,*v4,*v5,*v6,*v7;
    Creer_profil(nom, prenom, mail, code_postal, competence, ancien_collegue);
     
    a=nbrligne(db1);
    fseek(db1,0,SEEK_SET);
    fscanf(db1,"%*s");
    for (int i = 0; i <= a+1; i++)
    {
        fscanf(db1,"%s",str);
    }

    TEST(strcmp(str, "4,Balança,Maxime,maxbalança65@gmail.com,33003,theatre,1") == 0); 
    char nom1[128]="Ngueuga";
    char prenom1[128]="Franck";
    char mail1[128]="franckngueuga@yahoo.fr";
    char code_postal1[128]="33783";
    char competence1[128]="Anglais";
    char ancien_collegue1[128]="Betbeder,Bruno";

    Creer_profil(nom1, prenom1, mail1, code_postal1, competence1, ancien_collegue1);
    fscanf(db1,"%s",str);
    TEST(strcmp(str, "5,Ngueuga,Franck,franckngueuga@yahoo.fr,33783,Anglais,") == 0); 

    char nom2[128]="Vidal";
    char prenom2[128]="Hugo";
    char mail2[128]="vid_hugo_98@outlook.fr";
    char code_postal2[128]="37634";
    char competence2[128]="SQL";
    char ancien_collegue2[128]="Robbin,Bruno";

    Creer_profil(nom2, prenom2, mail2, code_postal2, competence2, ancien_collegue2);
    fscanf(db1,"%s",str);
    TEST(strcmp(str, "6,Vidal,Hugo,vid_hugo_98@outlook.fr,37634,SQL,") == 0);
    fclose(db1);
    }

    // test de Modifier_profil
    {
        int x,y,z;
        char n3[128]="Dupont";
        char p3[128]="Michel";
        char n4[128]="Devathaire";
        char p4[128]="Emannuel";
        char n5[128]="Defritsh";
        char p5[128]="Gaetan";
        char n6[128]="Vidal";
        char p6[128]="Hugo";
        char compe[128]="Java";
        char col[128]="Bartaire,Adrien";
        char code[128]="12345";
        char str[128];
        x=1;
        y=2;
        z=3;

        Modifier_profil(n3, p3, compe, col, code, z);
        Modifier_profil(n4, p4, compe, col, code, x);
        Modifier_profil(n5, p5, compe, col, code, y);
        Modifier_profil(n6, p6, compe, col, code, y);
        FILE *db9 = fopen("test/chercheurdemploi.csv", "r");

        fscanf(db9,"%*s");
        fscanf(db9,"%s",str);
        TEST(strcmp(str, "1,Dupont,Michel,dup.michel@gmail.com,12345,bureatique,2;1") == 0);

        fscanf(db9,"%s",str);
        TEST(strcmp(str, "2,Devathaire,Emannuel,emannueldev@yahoo.fr,13005,CSS;HTML;JS;Java,1") == 0);

        fscanf(db9,"%s",str);
        TEST(strcmp(str, "3,Defritsh,Gaetan,defgaetan98@hotmail.fr,33003,theatre,3;1") == 0);

        fscanf(db9,"%s",str);
        fscanf(db9,"%s",str);
        TEST(strcmp(str, "5,Ngueuga,Franck,franckngueuga@yahoo.fr,33783,Anglais,") == 0);

        fscanf(db9,"%s",str);
        TEST(strcmp(str, "6,Vidal,Hugo,vid_hugo_98@outlook.fr,37634,SQL,1") == 0);
        fclose(db9);
    }
     
    // test de Supprimer_profil
    {
    char n[128]="Dupont";
    char p[128]="Michel";
    char str[128];
    char* w1,*w2;
    int b;
     
    Supprimer_profil(n, p);
    FILE *db2 = fopen("test/chercheurdemploi.csv", "r");

    b=nbrligne(db2);
    fseek(db2,0,SEEK_SET);
    fscanf(db2,"%*s");
    for (int i = 0; i < b-1; i++)
    {
        fscanf(db2,"%s",str);
        w1=strtok(str,",");
        w1=strtok(NULL,",");
        w2=strtok(NULL,",");
        TEST(strcmp(w1, "Dupont") != 0);
        TEST(strcmp(w2, "Michel") != 0);
    }
    fclose(db2);

    char n1[128]="Devathaire";
    char p1[128]="Emannuel";

    Supprimer_profil(n1, p1);
    FILE *db6 = fopen("test/chercheurdemploi.csv", "r");

    b=nbrligne(db6);
    fseek(db6,0,SEEK_SET);
    fscanf(db6,"%*s");
    for (int i = 0; i < b-1; i++)
    {
        fscanf(db6,"%s",str);
        w1=strtok(str,",");
        w1=strtok(NULL,",");
        w2=strtok(NULL,",");
        TEST(strcmp(w1, "Devathaire") != 0);
        TEST(strcmp(w2, "Emannuel") != 0);
    }
    fclose(db6);
    char n2[128]="Devathaire";
    char p2[128]="Patrick";
    Supprimer_profil(n2, p2);// affiche:on arrive pas à vous identifier
    }

    // tests de Transitionner_profil
    {
    int c ,d;
    char n2[128]="Defritsh";
    char p2[128]="Gaetan";
    char entrep[128]="Disney";
    char* w1,*w2;
    char str[128];

    Transitionner_profil(n2, p2, entrep);

    FILE *db7 = fopen("test/chercheurdemploi.csv", "r");
    FILE *db8 = fopen("test/employe.csv", "r");
    c=nbrligne(db7);
    d=nbrligne(db8);
    fseek(db7,0,SEEK_SET);
    fseek(db8,0,SEEK_SET);

    fscanf(db7,"%*s");
    for (int i = 0; i < c-1; i++)
    {
        fscanf(db7,"%s",str);
        w1=strtok(str,",");
        w1=strtok(NULL,",");
        w2=strtok(NULL,",");
        TEST(strcmp(w1, "Defritsh") != 0);
        TEST(strcmp(w2, "Gaetan") != 0);
    }

    fscanf(db8,"%*s");
    for (int i = 0; i <d-3; i++)
    {
        fscanf(db8,"%s",str);
    }
    TEST(strcmp(str, "2,Buisson,Hugo,Buisson1999@saliege.fr,99023,bureautique,3;4,1") == 0);
    
    fscanf(db8,"%s",str);
    fscanf(db8,"%s",str);
    TEST(strcmp(str, "4,Defritsh,Gaetan,defgaetan98@hotmail.fr,33003,theatre,3;1;2,1") == 0);
    fclose(db7);
    fclose(db8);
    }

     
    {

        char nom[128]="Dupont";
        char prenom[128]="Michel";
        char mail[128]="dup.michel@gmail.com";
        char code_postal[128]="67940";
        char competence[128]="bureatique";
        char ancien_collegue[128]="Buisson,Hugo";

        char nom1[128]="Devathaire";
        char prenom1[128]="Emannuel";
        char mail1[128]="eannueldev@yahoo.fr";
        char code_postal1[128]="13005";
        char competence1[128]="CSS;HTML;JS";
        char ancien_collegue1[128]="Bartaire,Adrien";
        // 3,Defritsh,Gaetan,defgaetan98@hotmail.fr,33003,theatre,3
        char nom2[128]="Defritsh";
        char prenom2[128]="Gaetan";
        char mail2[128]="defgaetan98@hotmail.fr";
        char code_postal2[128]="77700";
        char competence2[128]="theatre;comedie";
        char ancien_collegue2[128]="Bouvier,Rodolphe";
        Creer_profil(nom, prenom, mail, code_postal, competence, ancien_collegue);
        Creer_profil(nom1, prenom1, mail1, code_postal1, competence1, ancien_collegue1);
        Creer_profil(nom2, prenom2, mail2, code_postal2, competence2, ancien_collegue2);
    }

    // test Recherche_par_poste
    {
        char nom[128]="Dupont";
        char prenom[128]="Michel";
        int a,b;
        a=1;
        b=2;

        Recherche_par_poste(nom, prenom, a);
        // résultat obtenu:aucun résultat obtenu (résultat voulu)
        printf("========================================================\n");

        char nom1[128]="Devathaire";
        char prenom1[128]="Emannuel";
        Recherche_par_poste(nom1, prenom1, a);
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        printf("========================================================\n");

        char nom2[128]="Defritsh";
        char prenom2[128]="Gaetan";
        Recherche_par_poste(nom2, prenom2, a);
        // résultat obtenu: (corresspont au résultat voulu)
        // Voici le(s) résultat(s) de votre recherche
        // le titre du poste est:acteur
        // le nom de l'entreprise:Disney
        // l'adresse mail de l'entreprise est:walt@disney.com
        // le code postal de l'entreprise est:77700
        // ---------------------------------------
        // le titre du poste est:comedien
        // le nom de l'entreprise:Twitter
        // l'adresse mail de l'entreprise est:emps@google.com
        // le code postal de l'entreprise est:75029
        // ---------------------------------------
        // le titre du poste est:humouriste
        // le nom de l'entreprise:Comedieclub
        // l'adresse mail de l'entreprise est:comclub@yahoo.fr
        // le code postal de l'entreprise est:77700
        // ---------------------------------------
        printf("========================================================\n");

        Recherche_par_poste(nom2, prenom2, b);
        // résultat obtenu: (corresspont au résultat voulu)
        // Voici le(s) résultat(s) de votre recherche
        // le titre du poste est:acteur
        // le nom de l'entreprise:Disney
        // l'adresse mail de l'entreprise est:walt@disney.com
        // le code postal de l'entreprise est:77700
        // ---------------------------------------
        // le titre du poste est:humouriste
        // le nom de l'entreprise:Comedieclub
        // l'adresse mail de l'entreprise est:comclub@yahoo.fr
        // le code postal de l'entreprise est:77700
        // ---------------------------------------
        printf("========================================================\n");
        Recherche_par_poste(nom, prenom, b);
        // résultat obtenu: (corresspont au résultat voulu)
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        printf("========================================================\n");

        char nom3[128]="Vidal";
        char prenom3[128]="Hugo";
        Recherche_par_poste(nom3, prenom3, a);
        // résultat obtenu: (corresspont au résultat voulu)
        // Voici le(s) résultat(s) de votre recherche
        // le titre du poste est:developpeur
        // le nom de l'entreprise:Google
        // l'adresse mail de l'entreprise est:emplois@google.com
        // le code postal de l'entreprise est:75009
        // ---------------------------------------
        printf("========================================================\n");

        Recherche_par_poste(nom3, prenom3, b);
        // résultat obtenu: (corresspont au résultat voulu)
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        printf("========================================================\n");

        char nom4[128]="Ngueuga";
        char prenom4[128]="Franck";
        Recherche_par_poste(nom4, prenom4, a);
        // résultat obtenu: (corresspont au résultat voulu)
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        printf("========================================================\n");
    }

    // test Rechercher_par_anciencollegue
    // {
        char nom[128]="Balança";
        char prenom[128]="Maxime";
        char entreprise[128]="Google";
        int a,b;
        a=1;b=2;
        Rechercher_par_anciencollegue(nom, prenom, entreprise, a);
        // voici le(s) résultat(s) de votre recherche:
        // Nom du (de la) collègue:Bartaire
        // Prénom du (de la) collègue:Adrien
        // Adresse mail du (de la) collègue:a_bartaire@google.com
        // ---------------------------------------------

        printf("========================================================\n");
        Rechercher_par_anciencollegue(nom, prenom, entreprise, b);
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        printf("========================================================\n");

        char nom1[128]="Defritsh";
        char prenom1[128]="Gaetan";
        char entreprise1[128]="Google";

        Rechercher_par_anciencollegue(nom1, prenom1, entreprise1, a);
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        // voici le(s) résultat(s) de votre recherche:
        // Nom du (de la) collègue:Bouvier
        // Prénom du (de la) collègue:Rodolphe
        // Adresse mail du (de la) collègue:Bouvierrodolphe@gmail.com
        printf("========================================================\n");

        char nom2[128]="Ngueuga";
        char prenom2[128]="Franck";
        char entreprise2[128]="Google";

        Rechercher_par_anciencollegue(nom2, prenom2, entreprise2, b);
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        printf("========================================================\n");

        char nom3[128]="Vidal";
        char prenom3[128]="Hugo";
        char entreprise3[128]="Google";

        Rechercher_par_anciencollegue(nom3, prenom3, entreprise3, a);
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        // voici le(s) résultat(s) de votre recherche:
        // voici le(s) résultat(s) de votre recherche:
        // Nom du (de la) collègue:Bartaire
        // Prénom du (de la) collègue:Adrien
        // Adresse mail du (de la) collègue:a_bartaire@google.com
        // ---------------------------------------------
        printf("========================================================\n");

        Rechercher_par_anciencollegue(nom3, prenom3, entreprise3, b);
        // résultat obtenu:aucun résultat obtenu (corresspont au résultat voulu)
        // voici le(s) résultat(s) de votre recherche:
        // voici le(s) résultat(s) de votre recherche:
        // Nom du (de la) collègue:Bartaire
        // Prénom du (de la) collègue:Adrien
        // Adresse mail du (de la) collègue:a_bartaire@google.com
        // ---------------------------------------------
        printf("========================================================\n");
    // }
    // tests pour 'employe'

     
    fclose(db3);
    fclose(db4);
    fclose(db5);

    printf("%d/%d\n", tests_reussis, tests_executes);

    return tests_executes - tests_reussis;
    
}

