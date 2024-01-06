

EMPLOYE remplissage_employe(){
    EMPLOYE p;
    printf("donner les information de l'employe\n");
    printf("nom :");
    scanf("%s",p.nom);
    printf("prenom :");
    scanf("%s",p.prenom);
    printf("Le numero de telephone :");
    scanf("%s",p.tel);
    printf("Le poste :");
    scanf("%d",&(p.poste));
    printf("Le RIB de son compte bancaire :");
    scanf("%s",p.rib);
    printf("email de l'employe :");
    scanf("%s",p.email_address);
    return p;
}

void affichage_employe(int id,char *nom,char *prenom,char *tel,int poste,char *rib,char *email_address){
    printf("Les information de cet employe: \n");
    printf("\t\tID : %d\n",id);
    printf("\t\tNOM : %s\n",nom);
    printf("\t\tPRENOM : %s\n",prenom);
    printf("\t\tTEL : %s\n",tel);
    printf("\t\tPOSTE : %d\n",poste);
    printf("\t\tRIB : %s\n",rib);
    printf("\t\tEMAIL : %s\n",email_address);
}


