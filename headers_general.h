#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef HEADERS_GENERAL_H
#define HEADERS_GENERAL_H

#define MAX_LINE_SIZE 1024

// Macros pour les codes de couleur ANSI
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define YELLOW_COLOR "\033[0;33m"
#define BLUE_COLOR "\033[0;34m"
#define WHITE_COLOR "\033[0;37m"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Macros pour les caractères ASCII de quadrillage
#define HORIZONTAL_LINE "─"
#define VERTICAL_LINE "│"
#define TOP_LEFT_CORNER "┌"
#define TOP_RIGHT_CORNER "┐"
#define BOTTOM_LEFT_CORNER "└"
#define BOTTOM_RIGHT_CORNER "┘"

// Prototypes de fonctions
void afficher_menu();
void dessiner_cadre();
void afficher_tous_employes();
void dessiner_cadre_saisie();
int obtenir_dernier_id_utilisateur();
void ajouterUser(int id_utilisateur);
void supprimerUser(int id_utilisateur);
EMPLOYE remplissage_employe();
//void affichage_employe(EMPLOYE p);
void affichage_employe(int id, const char *nom, const char *prenom, const char *tel, int poste, const char *rib, const char *email_address);
void ajouter_employe();
void supprimer_employe(int id);
void modifier_employe(int id);
void ecrireDansJournal(const char *message);
void gestion_des_employes();
void afficher_menu_principal();
void effacer_ecran() ;
//int login();

#endif