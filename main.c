#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// include time.h per funzioni srand e rand
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

bool checkWholeWord(char controlWord[40], char playerWord[40]);
bool checkSingleChar(char controlWord[40], char myChar);
char suggestWord[40];
//bool checkSingleChar();
int tentativi = 7;

int main(void) {
    // stampa cartella di lavoro
    char *cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    printf("\n\nBENVENUTO!\nIn questo gioco dovrai trovare la parola nascosta.\nBuon divertimento!\n\n");

    //genera un numero casuale per scegliere la parola da indovinare
    srand(time(NULL));
    int scelta = 1 + rand()%30;

    //variabile per contenere il file
    FILE *file;

    //variabile array a capienza massima
    char str[1000];

    //variabile Array stringhe
    char arrayMain[40];
    // variabile percorso file con puntatore
    char *filepath;
    filepath = cwd;
    strcat(cwd, "/parole");
    //printf("\n%s\n", cwd);

    file = fopen(cwd, "r");
    if (file == NULL){
        printf("\n\nCould not open file %s",cwd);
        return 1;
    }

    srand(time(NULL));
    int randN = 1 + rand()%30;
    //printf("\n%d\n\n", randN);

    int i = 0;
    while (fgets(str, 30, file) != NULL) {
        if(i == randN){
            strcpy(arrayMain, str);
            //printf("\nword to guess is: %s\n", str);
            break;
        } else {i++;}
    }
    fclose(file);

    printf("\nScrivi la parola intera, oppure prova a chiamare una lettera alla volta.\nAttenzione, non puoi fare piu' di %d errori\n\n", tentativi);

    char parolaIntera[40];
    // check per tentativo parola intera
    scanf("%s", parolaIntera);
    //printf("%s", parolaIntera);

    // set to true to keep game going
    bool playGame = true;
    // loop for game
    while(playGame) {

        // controllo lunghezza stringa
        int counter = 0;
        for(int i = 0; i < 40; i++){

            if (parolaIntera[i] != '\0'){
                counter++;
                continue;
            } else {
                break;
            }
        }

        if (counter == 0) {
            printf("string is empty\nabort program");
        } else if (counter > 1) {
            //printf("____________string is an actual string\n");
            printf("your word is: %s\n", parolaIntera);
            // funzioni per il gioco qui
            //printf("\n\ncheck if your word is equal to the misterious word:\n");
            bool result = checkWholeWord(arrayMain, parolaIntera);
            printf(result ? "esatto!\n" : "sbagliato, mi spiace...\n");
            if (result){
                playGame = false;
                printf("\ncongratulazioni, hai indovinato!");
                break;
            } else {
                if (tentativi < 1){
                    printf("\nhai finito i tentativi: game over!\n");
                    playGame = false;
                    break;
                }
                printf("tentativo andato a vuoto: hai sbagliato.\nTi rimangono %d tentativi.", tentativi);
                printf("\nInserisci una nuova parola o una lettera per riprovare\n");
                printf("-> ");
                scanf("%s", parolaIntera);
                continue;
            }

        } else {
            //printf("____________string is actually a single char: \n");
            // funzioni per il gioco qui
            // usa variabile char per tenere singolo carattere
            char singleChar = parolaIntera[0];
            //printf("\n\ncheck how many times it appears into the misterious word:\n", singleChar);

            //printf("\ncheck if your char appears in the misterious word:\n");
            bool result = checkSingleChar(arrayMain, singleChar);
            printf(result ? "\ncarattere presente!\n" : "\nnessuna corrispondenza, mi spiace\n");
            if (result){
                playGame = false;
            } else {
                if (tentativi < 1){
                    printf("\nhai finito i tentativi: game over!\n");
                    playGame = false;
                    break;
                }
                printf("\ntentativo andato a vuoto: hai sbagliato.\nTi rimangono %d tentativi.", tentativi);
                printf("\nInserisci una nuova parola o una lettera per riprovare\n");
                printf("-> ");
                scanf("%s", parolaIntera);
                continue;
            }
        }
    }

    return 0;
}

bool checkSingleChar(char controlWord[40], char myChar) {
    char sign = "_";
    //bool presence = false;
    printf("\n");
    for (int i = 0; i < strlen(controlWord); i++){
        if (controlWord[i] == myChar && controlWord[i] != '\0'){
            suggestWord[i] = myChar;
            //printf("%s\n", suggestWord);
        } else if(controlWord[i] == '\0'|| controlWord[i] == '\n'){
            ;
        } else {
            if(isalpha(suggestWord[i])){
                ;
            } else {
                suggestWord[i] = sign;
            }
            //printf("%s\n", suggestWord);
        }
    }
    printf("%s\n", suggestWord);
    printf("\n");
    tentativi--;
    return false;
}

bool checkWholeWord(char controlWord[40], char playerWord[40]){
    /*printf("\n__________\ncontrol word: %s: \n_______\n", controlWord);
    printf("\n__________\nplayer word: %s: \n_______\n", playerWord);*/
    if(!strcmp(controlWord, strcat(playerWord, "\n"))){
        return true;
    } else {
        tentativi--;
        return false;
    }

}
