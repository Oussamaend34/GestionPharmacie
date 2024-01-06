
// Fonction pour écrire dans le fichier journal
void ecrireDansJournal(const char *message){
    FILE *fichierJournal = fopen("pharmacie.log", "a"); // "a" pour ajouter à la fin du fichier

    if (fichierJournal != NULL) {
        time_t t;
        struct tm *tm_info;

        time(&t);
        tm_info = localtime(&t);

        fprintf(fichierJournal, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
                tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
                tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, message);

        fclose(fichierJournal);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier journal.\n");
    }
}
