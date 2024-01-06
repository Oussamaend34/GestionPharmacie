

void ajouterUser(int id_utilisateur){
    FILE *f=NULL;
    while (f== NULL){
        f=fopen("login.txt","a+");
    }
    

    int id;
    char hashedPassword1[SHA256_BLOCK_SIZE * 2 + 1];
    BYTE password[11];
    BYTE hash[SHA256_BLOCK_SIZE];
    printf("Entrez le mot de passe : ");
    scanf("%s", password);
    hashing(password, hash);
    char hashedPasswordHex[SHA256_BLOCK_SIZE * 2 + 1];
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        sprintf(&hashedPasswordHex[i * 2], "%02x", hash[i]);
    }
    
    //cryptage du mot de passe de l'utilisateur avant de l'enregistrer dans le fichier

    //génération d'un sel 
   
    fprintf(f,"%d,%s\n",id_utilisateur,hashedPasswordHex);
    fclose(f);
}

// supprimer les informations d'un utilisateur dans le fichier loggin
void supprimerUser(int id_utilisateur){
    FILE *f1;
    FILE *f2;
    int id;
    char hashedPassword[SHA256_BLOCK_SIZE * 2 + 1];
    do{
        f1=fopen("login.txt","rt");
        f2=fopen("login1.txt","wt");
    }while(f1==NULL || f2==NULL);

    while(fscanf(f1,"%d,%s",&id,hashedPassword)==2){
        if(id==id_utilisateur){
            continue;
        }
        fprintf(f2,"%d,%s\n",id,hashedPassword);

    }
   
    remove("login.txt");
    rename("login1.txt","login.txt");
    fclose(f1);
    fclose(f2);
}
