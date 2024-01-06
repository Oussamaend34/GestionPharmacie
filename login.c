#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.c"

void login(UTILISATEUR *user){
    int logged = -1;
    WORD id;
    BYTE password[11];
    BYTE hash[SHA256_BLOCK_SIZE];
    while(logged == -1){
        printf("\t\tID = ");
        scanf("%d", &id);
        printf("\t\tMOT DE PASSE = ");
        scanf("%s", password);
        FILE *file = fopen("login.txt", "rt");
        if(file == NULL){
            perror("login.txt");
            exit(0);
        }
        hashing(password, hash);
        char hashedPasswordHex[SHA256_BLOCK_SIZE * 2 + 1];
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
            sprintf(&hashedPasswordHex[i * 2], "%02x", hash[i]);
        }
        WORD id_file;
        char hash_file[65];
        while(fscanf(file, "%d,%s", &id_file, hash_file) != EOF){
            if(id == id_file)
                if(strcmp(hash_file, hashedPasswordHex) == 0){
                    logged = 1;
                    break;
                }    
        }
        fclose(file);
        if(logged ==1){
            printf("\t\tvous etes connectees\n");
            user->id_utilisateur = id_file;
            user->privilege = 1;
            sleep(1);
            system("cls");
        }
        else{
            printf("\tIdentifiant ou mot de passe incorrect\n");
            sleep(2);
            system("cls");
            }
    }

}
