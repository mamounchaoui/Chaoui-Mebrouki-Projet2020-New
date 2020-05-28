![](https://github.com/mamounchaoui/Chaoui-Mebrouki-Projet2020-New/workflows/Test%20master/badge.svg)



# Table des matières

- [But du programme](#But du programme)
- [Fonctionnalités](#sp%C3%A9cifications-fonctionelles)
    - [Fonctionnalités pour une entreprise](#fonctionalit%C3%A9s-pour-une-entreprise)
    - [Fonctionnalités pour un chercheur d'emploi](#fonctionalit%C3%A9s-pour-un-chercheur-demploi)
    - [Fonctionnalités pour un employé](#fonctionalit%C3%A9-pour-un-employ%C3%A9)

# But du programme

Ce programme est un simulateur de plateforme LinkekIn , elle contient plusieurs fonctionalités qui permettent de mettre en contacts les entreprise , les employés et les chercheurs d'emploi.

## Fonctionalités pour une entreprise

Une entreprise annonce des postes à pourvoir, spécifiant les compétences requises.
Elle peut aussi rechercher parmi les chercheurs d'emploi ceux qui correspondent à ses besoins.

- [ ] Créer un profil
    - [ ] Nom
    - [ ] Code postal
    - [ ] Adresse mail
- [ ] Supprimer un profil
    - [ ] Supprime automatiquement les postes à pourvoir existant
- [ ] Créer le profil d'un poste à pourvoir
    - [ ] Titre
    - [ ] Compétences requises
- [ ] Supprimer le profil d'un poste pourvu
- [ ] Rechercher parmi les chercheurs d'emploi pour des profils qui correspondent à un poste à pourvoir
    - [ ] Recherche par compétences
    - [ ] Recherche par compétences et code postal
    - [ ] Résultats
        - [ ] Nom
        - [ ] Prénom
        - [ ] Adresse mail

## Fonctionalités pour un chercheur d'emploi


- [ ] Créer un profil
    L'utilistateur devra saisir: 
    - Nom (avec la première lettre en majscule, ex:Dupont)
    - Prénom (avec la première lettre en majscule, ex:Michel)
    - Adresse mail
    - Code postal
    - Compétence(s) (si l'utilisateur veut saisir plusieurs compétences , les séparer par des ";")
    - Ancien(ne) collègue de travail parmi les personne employés (bien réspecter la forme suivante Nom,Prénom  ex:Deritsh,Gaetan)
- [ ] Modifier un profil
    L'utilisateur peut modifier différentes information , selon son choix:
    - choix=1:Ajouter des compétences (si l'utilisateur veut saisir plusieurs compétences , les séparer par des ";")
    - choix=2:Ajouter un(e) ancien(ne) collègue de travail (bien réspecter la forme suivante Nom,Prénom  ex:Deritsh,Gaetan
    - choix=3:Modifier le code postal
- [ ] Transitionner le profil de «chercheur d'emploi» à un profil «employé» 
    Cette fonctionalité concerne les utilisateurs ayant trouvé un emploi et doivent saisir le nom de l'entreprise qui viennent d'intégrer.
- [ ] Supprimer un profil
- [ ] Rechercher parmi les les postes à pourvoir qui correspondent à son profil 
Il existe deux façons de recherche, selon le choix de l'utilisateur:
    - choix=1:Recherche par compétences (compétences saisies lors de la création du profil)
    - choix=2:Recherche par compétences et code postal (compétences et code postal saisis lors de la création du profil)
- [ ] Rechercher parmi les anciens collègues
Il existe deux façons de recherche, selon le choix de l'utilisateur:
    - choix=1:Recherche par entreprise
    - choix=2:Recherche par compétences 

## Fonctionalités pour un employé


- [ ] Créer un profil
    L'utilistateur devra saisir: 
    - Nom (avec la première lettre en majscule, ex:Dupont)
    - Prénom (avec la première lettre en majscule, ex:Michel)
    - Adresse mail
    - Code postal
    - Compétence(s) (si l'utilisateur veut saisir plusieurs compétences , les séparer par des ";")
    - Ancien(ne) collègue de travail parmi les personne employés (bien réspecter la forme suivante Nom,Prénom  ex:Deritsh,Gaetan)
    - Entreprise (le nom de l'entreprise pour laquelle il travail)
- [ ] Modifier un profil
    L'utilisateur peut modifier différentes information , selon son choix:
    - choix=1:Ajouter des compétences (si l'utilisateur veut saisir plusieurs compétences , les séparer par des ";")
    - choix=2:Ajouter un(e) ancien(ne) collègue de travail (bien réspecter la forme suivante Nom,Prénom  ex:Deritsh,Gaetan
    - choix=3:Modifier le code postal
    - choix=4:Modifier l'entreprise
- [ ] Transitionner le profil «employé» vers «chercheur d'emploi»
    Cette fonctionalité concerne les utilisateurs ayant quitté leur entreprise et son pour le moment à la recherche d'un nouveau emploi.
- [ ] Supprimer le profil
- [ ] Rechercher parmi les les postes à pourvoir qui correspondent au profil de l'employé
    - [ ] Recherche par compétences
    Il existe deux façons de recherche, selon le choix de l'utilisateur:
    - choix=1:Recherche par compétences (compétences saisies lors de la création du profil)
    - choix=2:Recherche par compétences et code postal (compétences et code postal saisis lors de la création du profil)
- [ ] Rechercher parmi les anciens collègues
    Il existe deux façons de recherche, selon le choix de l'utilisateur:
    - choix=1:Recherche par entreprise
    - choix=2:Recherche par compétences 
