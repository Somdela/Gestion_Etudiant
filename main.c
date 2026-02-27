/* Gestion d'une classe d'étudiant par les fichiers */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STR 50
#define MAX_ETUDIANTS 100

typedef struct Etudiant {
    char nom[MAX_STR];
    char prenom[MAX_STR];
    long matricule;
    int an_int;          /* Année d'integration de l'école */
    char fil_prov[MAX_STR]; /* Option de provenance */
    int classement;      /* Classement de l'étudiant au concours */
    int age;
    char sexe;
    float moyenne;    
} Etudiant;

/* Remplissage du fichier avec les infos des étudiants */
int remplissage(Etudiant *e, int n) {
    FILE *f = fopen("Etudiant.txt", "a+");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return 0;
    }
    
    int prov;
    for (int i = 0; i < n; i++) {
        printf("\n--- Entrez les informations de l'étudiant %d ---\n", i + 1);
        printf("Nom (sans espace, ex: DE_LA_RUE) : ");
        scanf("%s", e[i].nom);
        printf("Prénom : ");
        scanf("%s", e[i].prenom);
        printf("Année d'intégration : ");
        scanf("%d", &e[i].an_int);
        
        // CORRECTION : Le scanf doit être DANS la boucle pour éviter la boucle infinie !
        do {
            printf("Option de provenance (MP, PC, TSI, DEUST) : ");
            scanf("%s", e[i].fil_prov);
            if (strcmp(e[i].fil_prov, "MP") == 0) prov = 1;
            else if (strcmp(e[i].fil_prov, "PC") == 0) prov = 2;
            else if (strcmp(e[i].fil_prov, "TSI") == 0) prov = 3;
            else if (strcmp(e[i].fil_prov, "DEUST") == 0) prov = 4;
            else {
                prov = 0;
                printf("Erreur : Filière invalide. Réessayez.\n");
            }
        } while (prov == 0);

        printf("Classement au concours : ");
        scanf("%d", &e[i].classement);
        printf("Âge : ");
        scanf("%d", &e[i].age);
        printf("Sexe (M/F) : ");
        scanf(" %c", &e[i].sexe);
        printf("Moyenne : ");
        scanf("%f", &e[i].moyenne);
       
        e[i].matricule = (e[i].an_int * 100000) + (prov * 10000) + e[i].classement;

        // Ecriture propre
        fprintf(f, "%s %s %ld %d %s %d %d %c %.2f\n",
                e[i].nom, e[i].prenom, e[i].matricule, e[i].an_int,
                e[i].fil_prov, e[i].classement, e[i].age, e[i].sexe,
                e[i].moyenne);
    }
    fclose(f);
    return 1;
}

/* Affichage du contenu du fichier */
int affichage() {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) {
        printf("Aucun étudiant enregistré pour le moment.\n");
        return 0;
    }
    
    Etudiant e;
    printf("\n--- Liste des étudiants ---\n");
    // CORRECTION : On s'assure que fscanf lit bien les 9 éléments pour éviter les décalages
    while(fscanf(f, "%s %s %ld %d %s %d %d %c %f", e.nom, e.prenom, &e.matricule, &e.an_int,
                 e.fil_prov, &e.classement, &e.age, &e.sexe, &e.moyenne) == 9) {
        printf("%s %s | Mat: %ld | Age: %d | Fil: %s | Moy: %.2f\n", 
               e.nom, e.prenom, e.matricule, e.age, e.fil_prov, e.moyenne);
    }
    fclose(f);
    return 1;
}

/* Recherche d'un étudiant par son matricule */
void recherche() {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) {
        printf("Aucun fichier trouvé.\n");
        return;
    }
    
    long matr; // CORRECTION : long au lieu de int
    int found = 0;
    printf("\nEntrez le matricule de l'étudiant à rechercher : ");
    scanf("%ld", &matr); // CORRECTION : %ld
    
    Etudiant e;
    while(fscanf(f, "%s %s %ld %d %s %d %d %c %f", e.nom, e.prenom, &e.matricule, &e.an_int,
                 e.fil_prov, &e.classement, &e.age, &e.sexe, &e.moyenne) == 9) {
        if (e.matricule == matr) {
            printf(">> Étudiant trouvé : %s %s | Moyenne: %.2f | Filière: %s\n", 
                   e.nom, e.prenom, e.moyenne, e.fil_prov);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Étudiant non trouvé.\n");
    }
    fclose(f);
}

/* Tri par ordre alphabetique */
void tri_alpha() {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    
    Etudiant etudiants[MAX_ETUDIANTS];
    int count = 0;
    while(fscanf(f, "%s %s %ld %d %s %d %d %c %f", etudiants[count].nom, etudiants[count].prenom,
                 &etudiants[count].matricule, &etudiants[count].an_int,
                 etudiants[count].fil_prov, &etudiants[count].classement,
                 &etudiants[count].age, &etudiants[count].sexe,
                 &etudiants[count].moyenne) == 9) {
        count++;
    }
    fclose(f);
    
    // Tri à bulle
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(etudiants[j].nom, etudiants[j + 1].nom) > 0) {
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
    
    f = fopen("Etudiant_trie.txt", "w");
    if (f == NULL) return;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %ld %d %s %d %d %c %.2f\n",
                etudiants[i].nom, etudiants[i].prenom, etudiants[i].matricule,
                etudiants[i].an_int, etudiants[i].fil_prov, etudiants[i].classement,
                etudiants[i].age, etudiants[i].sexe, etudiants[i].moyenne);
    }
    printf("Fichier trié sauvegardé dans Etudiant_trie.txt\n");
    fclose(f);
}

/* Trie par la moyenne */
void tri_moy() {
    // (Même logique corrigée que tri_alpha)
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) return;
    
    Etudiant etudiants[MAX_ETUDIANTS];
    int count = 0;
    while(fscanf(f, "%s %s %ld %d %s %d %d %c %f", etudiants[count].nom, etudiants[count].prenom,
                 &etudiants[count].matricule, &etudiants[count].an_int,
                 etudiants[count].fil_prov, &etudiants[count].classement,
                 &etudiants[count].age, &etudiants[count].sexe,
                 &etudiants[count].moyenne) == 9) {
        count++;
    }
    fclose(f);
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (etudiants[j].moyenne < etudiants[j + 1].moyenne) { // Décroissant
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
    
    f = fopen("Etudiant_trie_moy.txt", "w");
    if (f == NULL) return;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %ld %d %s %d %d %c %.2f\n",
                etudiants[i].nom, etudiants[i].prenom, etudiants[i].matricule,
                etudiants[i].an_int, etudiants[i].fil_prov, etudiants[i].classement,
                etudiants[i].age, etudiants[i].sexe, etudiants[i].moyenne);
    }
    printf("Fichier trié sauvegardé dans Etudiant_trie_moy.txt\n");
    fclose(f);
}

/* Ajout d'un étudiant à la fois */
int ajout() {
    Etudiant e;
    int prov;
    FILE *f = fopen("Etudiant.txt", "a+");
    if (f == NULL) return 0;
    
    printf("\n--- Ajout d'un étudiant ---\n");
    printf("Nom : ");
    scanf("%s", e.nom);
    printf("Prénom : ");
    scanf("%s", e.prenom);
    printf("Année d'intégration : ");
    scanf("%d", &e.an_int);
    
    // CORRECTION : scanf dans la boucle
    do {
        printf("Option de provenance (MP, PC, TSI, DEUST) : ");
        scanf("%s", e.fil_prov);
        if (strcmp(e.fil_prov, "MP") == 0) prov = 1;
        else if (strcmp(e.fil_prov, "PC") == 0) prov = 2;
        else if (strcmp(e.fil_prov, "TSI") == 0) prov = 3;
        else if (strcmp(e.fil_prov, "DEUST") == 0) prov = 4;
        else {
            prov = 0;
            printf("Erreur : Filière invalide.\n");
        }
    } while (prov == 0);

    printf("Classement au concours : ");
    scanf("%d", &e.classement);
    printf("Âge : ");
    scanf("%d", &e.age);
    printf("Sexe (M/F) : ");
    scanf(" %c", &e.sexe);
    printf("Moyenne : ");
    scanf("%f", &e.moyenne);
    
    e.matricule = (e.an_int * 100000) + (prov * 10000) + e.classement;

    fprintf(f, "%s %s %ld %d %s %d %d %c %.2f\n",
            e.nom, e.prenom, e.matricule, e.an_int,
            e.fil_prov, e.classement, e.age, e.sexe,
            e.moyenne);
    
    fclose(f);
    printf("Étudiant ajouté avec succès !\n");
    return 1;
}

/* Suppression d'un étudiant sachant son matricule */
int suppression() {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) return 0;
    
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        return 0;
    }
    
    long matr; // CORRECTION : long
    int found = 0;
    printf("\nEntrez le matricule de l'étudiant à supprimer : ");
    scanf("%ld", &matr); // CORRECTION : %ld
    
    Etudiant e;
    while(fscanf(f, "%s %s %ld %d %s %d %d %c %f", e.nom, e.prenom, &e.matricule, &e.an_int,
                 e.fil_prov, &e.classement, &e.age, &e.sexe, &e.moyenne) == 9) {
        if (e.matricule == matr) {
            found = 1;
            continue; // On ne l'écrit pas dans le nouveau fichier
        }
        fprintf(temp, "%s %s %ld %d %s %d %d %c %.2f\n",
                e.nom, e.prenom, e.matricule, e.an_int,
                e.fil_prov, e.classement, e.age, e.sexe, e.moyenne);
    }
    
    fclose(f);
    fclose(temp);
    remove("Etudiant.txt");
    rename("temp.txt", "Etudiant.txt");
    
    if (found) printf("Étudiant supprimé avec succès\n");
    else printf("Étudiant non trouvé\n");
    
    return 1;
}

/* Modification des infos d'un étudiant */
int modification() {
    FILE *f = fopen("Etudiant.txt", "r");
    if (f == NULL) return 0;
    
    Etudiant etudiants[MAX_ETUDIANTS];
    int count = 0;
    while(fscanf(f, "%s %s %ld %d %s %d %d %c %f", etudiants[count].nom, etudiants[count].prenom,
                 &etudiants[count].matricule, &etudiants[count].an_int,
                 etudiants[count].fil_prov, &etudiants[count].classement,
                 &etudiants[count].age, &etudiants[count].sexe,
                 &etudiants[count].moyenne) == 9) {
        count++;
    }
    fclose(f);
    
    long matr; // CORRECTION : long
    int found = 0;
    printf("\nEntrez le matricule de l'étudiant à modifier : ");
    scanf("%ld", &matr);
    
    for (int i = 0; i < count; i++) {
        if (etudiants[i].matricule == matr) {
            found = 1;
            printf("--- Nouvelles informations ---\n");
            printf("Nom : "); scanf("%s", etudiants[i].nom);
            printf("Prénom : "); scanf("%s", etudiants[i].prenom);
            printf("Année : "); scanf("%d", &etudiants[i].an_int);
            printf("Filière : "); scanf("%s", etudiants[i].fil_prov);
            printf("Classement : "); scanf("%d", &etudiants[i].classement);
            printf("Age : "); scanf("%d", &etudiants[i].age);
            printf("Sexe : "); scanf(" %c", &etudiants[i].sexe);
            printf("Moyenne : "); scanf("%f", &etudiants[i].moyenne);
            break; // On a trouvé, on sort de la boucle
        }
    }
    
    if (!found) {
        printf("Étudiant non trouvé\n");
        return 0;
    }
    
    f = fopen("Etudiant.txt", "w");
    if (f == NULL) return 0;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %s %ld %d %s %d %d %c %.2f\n",
                etudiants[i].nom, etudiants[i].prenom, etudiants[i].matricule,
                etudiants[i].an_int, etudiants[i].fil_prov, etudiants[i].classement,
                etudiants[i].age, etudiants[i].sexe, etudiants[i].moyenne);
    }
    fclose(f);
    printf("Modification effectuée.\n");
    return 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int choix, n;

    do {
        printf("\n====================================\n");
        printf("               MENU                 \n");
        printf("====================================\n");
        printf("1. Remplissage pour une première fois\n");  
        printf("2. Affichage du fichier\n");
        printf("3. Recherche d'un étudiant par son matricule\n");
        printf("4. Tri par ordre alphabétique\n");
        printf("5. Tri par ordre de moyenne\n");
        printf("6. Ajout d'un étudiant\n");
        printf("7. Suppression d'un étudiant\n");
        printf("8. Modification des infos d'un étudiant\n");
        printf("9. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                do {
                    printf("Entrez le nombre d'étudiants (entre 1 et %d) : ", MAX_ETUDIANTS);
                    scanf("%d", &n);
                } while (n < 1 || n > MAX_ETUDIANTS);
                
                // CORRECTION : L'allocation et la libération se font proprement dans le même bloc
                Etudiant *etudiants = (Etudiant*)malloc(n * sizeof(Etudiant));
                if (etudiants == NULL) {
                    printf("Erreur d'allocation mémoire\n");
                    break;
                }
                
                if (remplissage(etudiants, n) == 1) {
                    printf("Enregistrement réussi !\n");
                }
                free(etudiants); // On libère la mémoire tout de suite
                break;
            case 2:
                affichage();
                break;
            case 3:
                recherche();
                break;
            case 4:
                tri_alpha();
                break;
            case 5:
                tri_moy();
                break;
            case 6:
                ajout();
                break;
            case 7:
                suppression();
                break;
            case 8:
                modification();
                break;
            case 9:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide\n");
                break;
        }
    } while (choix != 9);

    return 0;
}