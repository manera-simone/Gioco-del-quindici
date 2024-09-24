#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LEN 16
#define ROWS 4
#define COLS 4

void scambiaElementi (int numeri[ROWS][COLS], int x1, int y1, int x2, int y2) {
    int temp = numeri[y1][x1];
    numeri[y1][x1] = numeri[y2][x2];
    numeri[y2][x2] = temp;
}

void popola (int numeri[ROWS][COLS]) {
    // NOTA: lo 0 in numeri rappresenta la caselle vuota
    int c = 0;
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++) {
            numeri[i][j] = c;
            c++;
        }
}

void mischia (int numeri[ROWS][COLS]) {
    for(int i = 0; i < 50; i++) {
        // genera prime coordinate 
        int x1 = rand () % 4;
        int y1 = rand () % 4;

        // genera seconde coordinate
        int x2 = rand () % 4;
        int y2 = rand () % 4;

        // scambia elemento di coordinate 1 con elemento di coordinate 2
        scambiaElementi(numeri, x1, y1, x2, y2);
    }
}

void stampaScacchiera (int numeri[ROWS][COLS]) {
    printf("\n\n");
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            if(numeri[row][col] == 0)
                printf("    ", numeri[row][col]);
            else if(numeri[row][col] < 10)
                printf(" %d  ", numeri[row][col]);
            else
                printf(" %d ", numeri[row][col]);
            if(col != 3)
                printf("|");
        }
        if(row != 3)
            printf("\n-------------------\n");
    }
    printf("\n\n");
}

void trovaCoordinate (int numeri[ROWS][COLS], int *x, int *y, int target) {
    for(int row = 0; row < 4; row++)
        for(int col = 0; col < 4; col++) 
            if(numeri[row][col] == target) {
                *x = col;
                *y = row;
            }
}

void trovaMosse(int numeri[ROWS][COLS], int *mossePossibili) {
    int colonnaSpazioVuoto, rigaSpazioVuoto;

    // trova coordinate (riga e colonna) dello spazio vuoto (e quindi dello 0)
    trovaCoordinate(numeri, &colonnaSpazioVuoto, &rigaSpazioVuoto, 0);

    int k = 0; // contatore

    // se la riga soprastante a quella dove si trova la casella vuota è compresa tra 0 e 3
    if(rigaSpazioVuoto + 1 <= 3 && rigaSpazioVuoto + 1 >= 0) {
        // allora è una riga esistente della scacchiera
        mossePossibili[k] = numeri[rigaSpazioVuoto + 1][colonnaSpazioVuoto];
        k++;
    }
    // se la riga sottostante a quella dove si trova la casella vuota è compresa tra 0 e 3
    if(rigaSpazioVuoto - 1 <= 3 && rigaSpazioVuoto - 1 >= 0) {
        // allora è una riga esistente della scacchiera
        mossePossibili[k] = numeri[rigaSpazioVuoto - 1][colonnaSpazioVuoto];
        k++;
    }
    // se la colonna a destra a quella dove si trova la casella vuota è compresa tra 0 e 3
    if(colonnaSpazioVuoto + 1 <= 3 && colonnaSpazioVuoto + 1 >= 0) {
        // allora è una colonna esistente della scacchiera
        mossePossibili[k] = numeri[rigaSpazioVuoto][colonnaSpazioVuoto + 1];
        k++;
    }
    // se la colonna a sinistra a quella dove si trova la casella vuota è compresa tra 0 e 3
    if(colonnaSpazioVuoto - 1 <= 3 && colonnaSpazioVuoto - 1 >= 0) 
        // allora è una colonna esistente della scacchiera
        mossePossibili[k] = numeri[rigaSpazioVuoto][colonnaSpazioVuoto - 1];
}

void stampaMosse (int *mosse) {
    printf("\nMosse possibili: ");
    for(int i = 0; i < 4 && mosse[i] != 0; i++)
        printf("%d  ", mosse[i]);
    printf("\n");
}

int controllaMossa (int mossa, int *mosse) {
    for(int i = 0; i < 4 && mosse[i] != 0; i++) 
        if(mossa == mosse[i])
            return 0;
    return 1;
}

void controllaVittoria (int numeri[ROWS][COLS], int *gioco_in_corso) {
    int c = 0;
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++) {
            c++;
            if(c == 16)
                c = 0;
            if(numeri[i][j] != c)
                return;
        }
    *gioco_in_corso = 0;
}

void aggiornaScacchiera (int numeri[ROWS][COLS], int mossa) {
    int colonnaSpazioVuoto, rigaSpazioVuoto; // coordinate dello 0
    int colonnaMossa, rigaMossa; // cordinate della mossa

    // trova coordinate (riga e colonna) dello spazio vuoto (e quindi dello 0)
    trovaCoordinate(numeri, &colonnaSpazioVuoto, &rigaSpazioVuoto, 0);

    // trova coordinate (riga e colonna) della mossa scelta
    trovaCoordinate(numeri, &colonnaMossa, &rigaMossa, mossa);

    // scambia la casella vuota (quindi lo zero) con la mossa scelta
    scambiaElementi(numeri, colonnaSpazioVuoto, rigaSpazioVuoto, colonnaMossa, rigaMossa);
}

void resettaMosse(int *mosse) {
    for(int i = 0; i < 4; i++)
        mosse[i] = 0;
}

int main () {
    srand(time(0));
    int numeri[ROWS][COLS];
    int mossePossibili[4] = {0};
    int gioco_in_corso = 1;
    int flag = 0;
    int mossa;
    int numeroMosse = 0;
    popola(numeri);
    mischia(numeri);

    while(gioco_in_corso) {
        stampaScacchiera(numeri);
        trovaMosse(numeri, mossePossibili);
        stampaMosse(mossePossibili);
        do {
            printf("\nInserisci mossa: ");
            scanf("%d", &mossa);
            flag = controllaMossa(mossa, mossePossibili);
            if(flag == 1)
                printf("Errore: mossa invalida!\n");
        } while (flag == 1);
        aggiornaScacchiera(numeri, mossa);
        resettaMosse(mossePossibili);
        controllaVittoria(numeri, &gioco_in_corso);
        numeroMosse++;
    }

    printf("\n\nHai vinto!");
    printf("Mosse impiegate: %d", numeroMosse);

    return 0;
}