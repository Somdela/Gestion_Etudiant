/* Gestion d'une classe d'étudiant par les fichiers*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define Max 20

typedef struct Etudiant{
    char nom[Max];
    char prenom[Max];
    int matricule ;
    int an_int; /*Année d'integration de l'école*/
    char fil_prov[Max] ; /*Option de provenance*/
    int classement; /*Classement de l'étudiant au concours*/
    int age;
    char sexe;
    float moyenne;    
        }Etudiant;

/*Remplissage du fichier avec les infos des étudiants*/
int remplissage(Etudiant *e, int n){
    FILE *f;
    int prov;
    f = fopen("Etudiant.txt", "a+");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return 0;
    }
    for (int i = 0; i < n; i++){
        printf("Entrez les informations de l'étudiant %d :\n", i + 1);
        printf("Nom : ");
        scanf("%s", e[i].nom);
        printf("Prénom : ");
        scanf("%s", e[i].prenom);
        printf("Année d'intégration : ");
        scanf("%d", &e[i].an_int);
        printf("Option de provenance : ");
        scanf(" %s", e[i].fil_prov);
        printf("Classement au concours : ");
        scanf("%d", &e[i].classement);
        printf("Âge : ");
        scanf("%d", &e[i].age);
        printf("Sexe (M/F) : ");
        scanf(" %c", &e[i].sexe);
        printf("Moyenne : ");
        scanf("%f", &e[i].moyenne);
       do{
         if (strcmp(e[i].fil_prov, "MP") == 0){
            prov=1;
        }
        else if (strcmp(e[i].fil_prov, "PC") == 0){
            prov=2;
        }
        else if (strcmp(e[i].fil_prov, "TSI") == 0){
            prov=3;
        }
        else if (strcmp(e[i].fil_prov, "DEUST") == 0){
            prov=4;
        }
        else{
            prov=0;
        }
         } while (prov == 0);
        e[i].matricule= (e[i].an_int * 100000) + (prov * 10000) + (e[i].classement);

        fprintf(f, "%s %s %d %d %s %d %d %c %.2f\n",
                e[i].nom, e[i].prenom, e[i].matricule, e[i].an_int,
                e[i].fil_prov, e[i].classement, e[i].age, e[i].sexe,
                e[i].moyenne);
    }
    fclose(f);
    return 1;
}

/*Affichage du contenue du fichier*/
int affichage(){
    FILE *f;
    f = fopen("Etudiant.txt", "r");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return 0;
    }
    char nom[Max], prenom[Max];
    int matricule, an_int, classement, age;
    char fil_prov[Max], sexe;
    float moyenne;
    while(fscanf(f, "%s %s %d %d %c %d %d %c %f", nom, prenom, &matricule, &an_int,
                 &fil_prov, &classement, &age, &sexe, &moyenne) != EOF){
        printf("%s %s %d %d %c %f\n", nom, prenom, matricule, age, sexe, moyenne);
    }
    fclose(f);
    return 1;
}

/*Recherche d'un étudiant par son matricule*/
void recherche(){
    FILE *f;
    f = fopen("Etudiant.txt", "r");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    int matr, found = 0;
    printf("Entrez le matricule de l'étudiant à rechercher : ");
    scanf("%d", &matr);
    char nom[Max], prenom[Max];
    int an_int, classement, age, matricule;
    char fil_prov[Max], sexe;
    float moyenne;
    while(fscanf(f, "%s %s %d %d %c %d %d %c %f", nom, prenom, &matricule, &an_int,
                 &fil_prov, &classement, &age, &sexe, &moyenne) != EOF){
        if (matricule == matr){
            printf("Étudiant trouvé : %s %s %d %d %c %f\n", nom, prenom, matricule, age, sexe, moyenne);
            found = 1;
            break;
        }
    }
    if (!found){
        printf("Étudiant non trouvé.\n");
    }
    fclose(f);
}

/*Tri par ordre alphabetique*/
//je veux que la liste des etudiants soit triée aussi dans le fichier Etudiant.txt
void tri_alpha(){
    FILE *f;
    f = fopen("Etudiant.txt", "r");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    Etudiant etudiants[Max];
    int count = 0;
    while(fscanf(f, "%s %s %d %d %s %d %d %c %f", etudiants[count].nom, etudiants[count].prenom,
                 &etudiants[count].matricule, &etudiants[count].an_int,
                 etudiants[count].fil_prov, &etudiants[count].classement,
                 &etudiants[count].age, &etudiants[count].sexe,
                 &etudiants[count].moyenne) != EOF){
        count++;
    }
    fclose(f);
    
    // Tri à bulle
    for (int i = 0; i < count - 1; i++){
        for (int j = 0; j < count - i - 1; j++){
            if (strcasecmp(etudiants[j].nom, etudiants[j + 1].nom) > 0){
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
    
    // ecriture dans un fichier appélé Etudiant_trie.txt les étudiants triés par ordre alphabetique
    f = fopen("Etudiant_trie.txt", "w");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    for (int i = 0; i < count; i++){
        fprintf(f, "%s %s %d %d %s %d %d %c %.2f\n",
                etudiants[i].nom, etudiants[i].prenom, etudiants[i].matricule,
                etudiants[i].an_int, etudiants[i].fil_prov, etudiants[i].classement,
                etudiants[i].age, etudiants[i].sexe, etudiants[i].moyenne);
    }
    printf("Fichier trié sauvegardé dans Etudiant_trie.txt\n");
    fclose(f);
}

/*Trie par la moyenne*/
void tri_moy(){
    FILE *f;
    f = fopen("Etudiant.txt", "r");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    Etudiant etudiants[Max];
    int count = 0;
    while(fscanf(f, "%s %s %d %d %c %d %d %c %f", etudiants[count].nom, etudiants[count].prenom,
                 &etudiants[count].matricule, &etudiants[count].an_int,
                 &etudiants[count].fil_prov, &etudiants[count].classement,
                 &etudiants[count].age, &etudiants[count].sexe,
                 &etudiants[count].moyenne) != EOF){
        count++;
    }
    fclose(f);
    
    // Tri à bulle
    for (int i = 0; i < count - 1; i++){
        for (int j = 0; j < count - i - 1; j++){
            if (etudiants[j].moyenne < etudiants[j + 1].moyenne){
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
    
    // ecriture dans un fichier appélé Etudiant_trie_moy.txt les étudiants triés par ordre de moyenne
    f = fopen("Etudiant_trie_moy.txt", "w");
    if (f == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    for (int i = 0; i < count; i++){
        fprintf(f, "%s %s %d %d %s %d %d %c %.2f\n",
                etudiants[i].nom, etudiants[i].prenom, etudiants[i].matricule,
                etudiants[i].an_int, etudiants[i].fil_prov, etudiants[i].classement,
                etudiants[i].age, etudiants[i].sexe, etudiants[i].moyenne);
    }
    printf("Fichier trié sauvegardé dans Etudiant_trie_moy.txt\n");
    fclose(f);
}

/*Ajout d'un étudiant*/
//int ajout()

/*Suppression d'un étudiant sachant son matricule*/
//int suppression()

/* Modification des infos d'un étudiant sachant son matricule*/
//int modification()

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int n;
    do{
         printf("Entrez le nombre d'étudiants (entre 1 et 20) : ");
         scanf("%d", &n);
    } while (n < 1 || n > Max);
    Etudiant *etudiants = (Etudiant*)malloc(n * sizeof(Etudiant));
    etudiants->matricule = 0;
    
    if (etudiants == NULL){
        printf("Erreur d'allocation mémoire\n");
        return 0;
    }
    if (remplissage(etudiants, n) == 0){
        printf("Erreur de remplissage du fichier\n");
        free(etudiants);
        return 0;
    }
    if (affichage() == 0){
        printf("Erreur d'affichage du fichier\n");
        free(etudiants);
        return 0;
    }
    recherche();
    tri_alpha();
    tri_moy();
    free(etudiants);
    return 1;
}