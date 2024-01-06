
void effacer_ecran() {
#ifdef _WIN32
    system("cls"); // Pour Windows
#else
    system("clear"); // Pour Linux/Unix
#endif
}


void gestion_des_employes(){
     int choix;

    // Initialiser les structures ou d'autres ressources nécessaires

    do {
        afficher_menu();
        dessiner_cadre();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                //affichage de la liste des employes
                effacer_ecran();
                afficher_tous_employes();
                getch();
                system("cls");
                ecrireDansJournal("Affichage des employes par le pharmacien");
                break;
            case 2:
                // Appeler la fonction pour ajouter un employé
                effacer_ecran();
                ajouter_employe();
                ecrireDansJournal("Ajout d'un employe par le pharmacien");
                break;

            case 3:
                // Appeler la fonction pour supprimer un employé
                effacer_ecran();
                int id_supp;
                dessiner_cadre_saisie();
                scanf("%d", &id_supp);
                supprimer_employe(id_supp);
                ecrireDansJournal("suppression d'un employe par le pharmacien");
                break;

            case 4:
                // Appeler la fonction pour modifier les informations d'un employé
                effacer_ecran();
                int id_modify;
                dessiner_cadre_saisie();
                scanf("%d", &id_modify);
                modifier_employe(id_modify);
                ecrireDansJournal("Modification des informatons d'un employe par le pharmacien");
                break;

            case 5:
                printf("\n%sProgramme terminé.%s\n", RED_COLOR, RESET_COLOR);
                // Libérer les ressources si nécessaire
                break;

            default:
                printf("\n%sChoix invalide. Veuillez entrer un nombre entre 1 et 4.%s\n", RED_COLOR, RESET_COLOR);
        }

    } while (choix != 5);

}

   