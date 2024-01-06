

int obtenir_dernier_id_utilisateur() {
    FILE *f = fopen("config_u.txt", "r");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier de configuration");
        return -1; // Une valeur d'erreur, si nécessaire
    }

    int dernier_id = -1;
    int id;
    
    while (fscanf(f, "%d\n", &id) == 1) {
        dernier_id = id;
    }

    fclose(f);

    return dernier_id;
}


void afficher_tous_employes() {
    FILE *fichier = fopen("employe.txt", "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char ligne[MAX_LINE_SIZE];
    EMPLOYE p;

    // Ignorer la première ligne (entête)
    if (fgets(ligne, MAX_LINE_SIZE, fichier) == NULL) {
        fprintf(stderr, "Avertissement : Le fichier semble être vide ou la première ligne est incorrecte.\n");
        fclose(fichier);
        return;
    }

    printf("\nListe des Employés :\n");

    // EXTRAIRE LES INFORMATIONS DES EMPLOYES ET AFFICHAGE
    while (fgets(ligne, MAX_LINE_SIZE, fichier) != NULL) {

        if (sscanf(ligne, "%d,%49[^,],%49[^,],%19[^,],%d,%49[^,],%99[^,\n]", &p.id_employe, p.nom, p.prenom, p.tel, &p.poste, p.rib, p.email_address) == 7) {
            // Afficher les informations de l'employé
            affichage_employe(p.id_employe, p.nom, p.prenom, p.tel, p.poste, p.rib, p.email_address);
        } else {
            fprintf(stderr, "Erreur de lecture de la ligne : %s", ligne);
        }
    }
    fclose(fichier);
}


void ajouter_employe(){
    EMPLOYE p=remplissage_employe();
    p.id_employe=obtenir_dernier_id_utilisateur()+1;
    FILE *f1=NULL;
    FILE *f2=NULL;
    //f1=fopen("employe.txt","a+");
    do{
        f1=fopen("employe.txt","a+");
        f2=fopen("config_u.txt","a");
    }while(f1==NULL || f2==NULL);
  
    //enregistrer le nouveau id du nouveau utilisateur dans le fichier confi_u.txt
    fprintf(f2,"\n%d",p.id_employe);
    //processus pour enregistrer les informations du nouveau utilisateur
    int id_employe;
    char nom[20];
    char prenom[20];
    char tel[11];
    int poste;
    char rib[25];
    char email_address[100];
    
    //chequer voir si l'utilisateur n'est pas déjà enregistré
    int deja_enregistre=0;
    while(fscanf(f1,"%d,%s,%s,%s,%d,%s,%s",&id_employe,nom,prenom,tel,&poste,rib,email_address)!=EOF){
        if(id_employe==p.id_employe){
            deja_enregistre=1;
            break;
        }
    }
    if(deja_enregistre){
        printf("L'utilisateur est déjà enregistre\n");
    }
    else{
        fprintf(f1,"%d,%s,%s,%s,%d,%s,%s\n",p.id_employe,p.nom,p.prenom,p.tel,p.poste,p.rib,p.email_address);
        ajouterUser(p.id_employe);
    }

    fclose(f1);
    fclose(f2);
}


void supprimer_employe(int id){
    int id_existe=0;
    FILE *f1;
    FILE *f2;
    FILE *f3;
    int id_employe;
    char nom[20];
    char prenom[20];
    char tel[11];
    int poste;
    char rib[25];
    char email_address[100];
    int id_root=1000;
    do{
        f1=fopen("employe.txt","rt");
        f2=fopen("employe1.txt","wt");
        f3=fopen("config_u.txt","wt");
    }while(f1==NULL || f2==NULL || f3==NULL);
    fprintf(f3,"%d\n",id_root);

    while(fscanf(f1,"%d,%s,%s,%s,%d,%s,%s",&id_employe,nom,prenom,tel,&poste,rib,email_address)!=EOF){
        if(id==id_employe){
            id_existe=1;
            continue;
        }

        fprintf(f2,"%d,%s,%s,%s,%d,%s,%s\n",id_employe,nom,prenom,tel,poste,rib,email_address);
        fprintf(f3,"%d\n",id_employe);
    }
    supprimerUser(id);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    remove("employe.txt");
    rename("employe1.txt","employe.txt");
    if(id_existe){
        printf("Suppression des informations de l'utilisateur réussi \n");

    }
    else{
        printf("L'id saisi correspond aucun utilisateur");
    }
    
}

void modifier_employe(int id) {
    FILE *f1;
    FILE *f2;
    int id_employe;
    char nom[20];
    char prenom[20];
    char tel[11];
    int poste;
    char rib[25];
    char email_address[100];
    int modification_effectuee = 0;  // Variable pour indiquer si une modification a été effectuée

    do {
        f1 = fopen("employe.txt", "rt");
        f2 = fopen("employe1.txt", "wt");
    } while (f1 == NULL || f2 == NULL);

    while (fscanf(f1, "%d,%s,%s,%s,%d,%s,%s", &id_employe, nom, prenom, tel, &poste, rib, email_address) != EOF) {
        if (id == id_employe ) {
            // Afficher les informations actuelles de l'employé
            printf("Les informations actuelles de l'employé :\n");
            printf("Le nom : %s\n",nom);
            printf("Le prenom : %s\n",prenom);
            printf("Le numero de telephone : %s\n",tel);
            printf("Le poste ocuppe : %d\n",poste);
            printf("Le RIB : %s\n",rib);
            printf("L'adress mail de l'emloye : %s\n",email_address);
            
            // Saisir les nouvelles informations
            printf("Entrez les nouvelles informations de l'employé :\n");
            printf("Nom : ");
            scanf("%s", nom);
            printf("Prenom : ");
            scanf("%s", prenom);
            printf("Le numero de telephone : ");
            scanf("%s", tel);
            printf("Le poste : ");
            scanf("%d", &poste);
            printf("Le RIB de son compte bancaire : ");
            scanf("%s", rib);
            printf("Email de l'employé : ");
            scanf("%s", email_address);

            // Indiquer que la modification a été effectuée
            modification_effectuee = 1;
        }

        fprintf(f2, "%d,%s,%s,%s,%d,%s,%s\n", id_employe, nom, prenom, tel, poste, rib, email_address);
    }

    fclose(f1);
    fclose(f2);
    remove("employe.txt");
    rename("employe1.txt", "employe.txt");

    if (modification_effectuee) {
        printf("Modification des informations de l'employé réussie.\n");
    } else {
        printf("Aucun employé trouvé avec l'identifiant spécifié.\n");
    }
}

void afficher_menu() {
    
    draw_head(45);
    printf("\n");
    printf("\t\t%c           Menu Gestion des Employes         %c\n",186,186);
    draw_dvider(45);
    printf("\t\t%c            1. Affichage des Employes        %c\n",186,186);
    printf("\t\t%c             2. Ajouter un employe           %c\n",186,186);
    printf("\t\t%c            3. Supprimer un employe          %c\n",186,186);
    printf("\t\t%c  4. Modifier les informations d'un employe  %c\n",186,186);
    printf("\t\t%c                    5-QUIT                   %c\n",186,186);
    draw_bottom(45);

}

void dessiner_cadre() {
    printf( "\nEntrez votre choix (1-5) : ");
}

void dessiner_cadre_saisie() {
    printf("Saisissez l'identifiant : ");
}

