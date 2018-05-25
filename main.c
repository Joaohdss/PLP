#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * Grupo :
 * João
 * Redson
 * Hector
 * Matheus
 * Luan
 */
#define tamanho 12
#define true 1
#define false 0
int tabuleiro[tamanho][tamanho];
int tabuleiroCopia[tamanho][tamanho];
int estado = 5;
int pontuacao = 0;
int bombas = 50;
int vertical = 1;
int horizontal = 2;


/*
 A variavel estado pode ter 4 valores:
    * 0: quando a posição já foi bombardeada
    * 1: quando a jogada é válida
    * 2: posição inválida (quando o usuário informa uma posição que não existe)
    * 5: valor de inicialização
 */


// retorna um numero aleatorio dentro do intervalo estabelecido
int numeroRandom(int inicio, int fim) {
    int intervalo = (fim - inicio) + 1;
    srand(clock());
    return inicio + (rand() % intervalo);
}

//garante que as estruturas fiquem separadas na matriz
int verifica(int tabuleiro[tamanho][tamanho], int linha, int coluna, int direcao, int extensao) {
    if (direcao == vertical) {
        if (tabuleiro[linha-1][coluna] != 0 || tabuleiro[linha+extensao][coluna] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha-1][coluna+1] != 0 || tabuleiro[linha+extensao][coluna-1] != 0 || tabuleiro[linha+extensao][coluna+1] != 0) {
            return false;
        }
        for (int i=linha; i<linha+extensao; i++) {
            if(tabuleiro[i][coluna] != 0 || tabuleiro[i][coluna+1] != 0 || tabuleiro[i][coluna-1] != 0) {
                return false;
            }
        }
        return true;
    }
    else {
        if (tabuleiro[linha][coluna-1] != 0 || tabuleiro[linha][coluna+extensao] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha+1][coluna-1] != 0 || tabuleiro[linha-1][coluna+extensao] != 0 || tabuleiro[linha+1][coluna+extensao] != 0) {
            return false;
        }
        for (int i=coluna; i<coluna+extensao; i++) {
            if(tabuleiro[linha][i] != 0 || tabuleiro[linha+1][i] != 0 || tabuleiro[linha-1][i] != 0) {
                return false;
            }
        }
        return true;
    }
}

void alocarCT(int tabuleiro[tamanho][tamanho]) {
    int linha = numeroRandom(0, 11);
    int coluna = numeroRandom(0, 11);
    if (tabuleiro[linha][coluna] != 0 || tabuleiro[linha+1][coluna] != 0 || tabuleiro[linha-1][coluna] != 0 || tabuleiro[linha][coluna+1] != 0 || tabuleiro[linha][coluna-1] != 0 || tabuleiro[linha-1][coluna-1] != 0 || tabuleiro[linha+1][coluna-1] != 0 || tabuleiro[linha+1][coluna+1] != 0 || tabuleiro[linha-1][coluna+1] != 0) {
        alocarCT(tabuleiro);
    }
    else {
        tabuleiro[linha][coluna] = 1;
    }
}

void alocarIAPA(int tabuleiro[tamanho][tamanho]) {
    int extensao = 2;
    int direcao = numeroRandom(vertical, horizontal);
    if (direcao == vertical) {
        int linha = numeroRandom(0, 10);
        int coluna = numeroRandom(0, 11);
        if(verifica(tabuleiro, linha, coluna, direcao, extensao) == true) {
            for (int i=linha; i<linha+extensao; i++) {
                tabuleiro[i][coluna] = 2;
            }
        }
        else {
            alocarIAPA(tabuleiro);
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(0, 10);
        if(verifica(tabuleiro, linha, coluna, direcao, extensao) == true) {
            for (int i=coluna; i<coluna+extensao; i++) {
                tabuleiro[linha][i] = 2;
            }
        }
        else {
            alocarIAPA(tabuleiro);
        }
    }
}

void alocarBMT(int tabuleiro[tamanho][tamanho]) {
    int extensao = 3;
    int direcao = numeroRandom(vertical, horizontal);
    if (direcao == vertical) {
        int linha = numeroRandom(0, 9);// gera uma valor aleatorio para a linha
        int coluna = numeroRandom(0, 11);// gera um valor aleatorio para a coluna
        if(verifica(tabuleiro, linha, coluna, direcao, extensao) == true) {
            for (int i=linha; i<linha+extensao; i++) {// alocação da estrutura na matriz
                tabuleiro[i][coluna] = 3;
            }
        }
        else {
            alocarBMT(tabuleiro);// chamada recursiva caso a estrutura não seja alocada na matriz
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(0, 9);
        if(verifica(tabuleiro, linha, coluna, direcao, extensao) == true) {
            for (int i=coluna; i<coluna+extensao; i++) {
                tabuleiro[linha][i] = 3;
            }
        }
        else {
            alocarBMT(tabuleiro);
        }
    }
}

void alocarBPC(int tabuleiro[12][12]){
    int extensao = 4;
    int direcao = numeroRandom(vertical, horizontal);
    if (direcao == vertical) {
        int linha = numeroRandom(0, 8);
        int coluna = numeroRandom(0, 11);
        for (int i=linha; i<linha+extensao; i++) {
            tabuleiro[i][coluna] = 4;
        }
    }
    else {
        int linha = numeroRandom(0, 11);
        int coluna = numeroRandom(0, 8);
        for (int i=coluna; i<coluna+extensao; i++) {
            tabuleiro[linha][i] = 4;
        }
    }
}


// alocação automática de estruturas na matriz
void alocar() {
    alocarBPC(tabuleiro);
    alocarBMT(tabuleiro);
    alocarBMT(tabuleiro);
    alocarIAPA(tabuleiro);
    alocarIAPA(tabuleiro);
    alocarCT(tabuleiro);
    alocarCT(tabuleiro);
    alocarCT(tabuleiro);
    alocarCT(tabuleiro);
}

void desenharInterface (int mostrarTerreno){
    int i, j;
    if( mostrarTerreno == 0){
        printf("####################################################\n");
        printf("########      bombardment of the virus      ########\n");
        printf("####################################################\n");
        printf("     A   B   C   D   E   F   G   H   I   J   L   M\n");
        printf("----------------------------------------------------\n");
        for(i = 0; i <= 11 ; i++){
            if (i > 9) {
                printf("%i |", i);
            }
            else {
                printf("%i  |", i);
            }
            for(j = 0; j <= 11; j++){
                if(tabuleiroCopia[i][j] == 0) printf(" . |");
                if(tabuleiroCopia[i][j] == 1) printf(" @ |");
                if(tabuleiroCopia[i][j] == 2) printf(" # |");
                if(tabuleiroCopia[i][j] == 3) printf(" o |");
                if(tabuleiroCopia[i][j] == 4) printf(" * |");
                if(tabuleiroCopia[i][j] == 5) printf(" X |");
            }
            printf("\n");
        }
        printf("\nx = Bomba perdida\n");
        printf("@ = CT (tamanho 1)              Bombas restantes: %d\n", bombas);
        printf("# = IAPA (tamanho 2)\n");
        printf("o = BMT (tamanho 3)\n");
        printf("* = BPC (tamanho 4)\n\n");
        if(estado == 2) {
            printf("  ====> AVISO : COLUNA OU LINHA, FORA DO PADRÃO \n");
        }
    }else {
        printf("################################################################\n");
        printf("#############       bombardment of the virus       #############\n");
        printf("################################################################\n\n");
        printf("      A    B    C    D    E    F    G    H    I    J    L    M\n");
        printf("----------------------------------------------------------------\n");
        for(i = 0; i <= 11 ; i++){
            if (i > 9) {
                printf("%i |", i);
            }
            else {
                printf("%i  |", i);
            }
            for(j = 0; j <= 11; j++){
                if(tabuleiro[i][j] == 0) printf("    |");
                if(tabuleiro[i][j] == 1) printf("  1 |");
                if(tabuleiro[i][j] == 2) printf("  2 |");
                if(tabuleiro[i][j] == 3) printf("  3 |");
                if(tabuleiro[i][j] == 4) printf("  4 |");
                if(tabuleiro[i][j] == 5) printf("  X |");

            }
            printf("\n");
        }
        printf("\n");
    }
}
int jogadas(char coluna, int linha){
    int colunaID;
    bombas--;
    if((coluna != 'A' && coluna != 'B' && coluna != 'C'
            && coluna != 'D' && coluna != 'E' && coluna != 'F' && coluna != 'G' && coluna != 'H' && coluna != 'I' && coluna != 'J' && coluna != 'L' && coluna != 'M')) {
        return 2 ; // Caso a coluna seria invalida
    }else if((linha != 0 && linha != 1 && linha != 2 && linha != 3 && linha != 4 && linha != 5 && linha !=6 && linha != 7 && linha != 8 && linha != 9 && linha != 10 && linha != 11)) {
        return 2; // Caso de linha invalida
    }else {
        // posição valida
        if(coluna == 'A') colunaID = 0;
        if(coluna == 'B') colunaID = 1;
        if(coluna == 'C') colunaID = 2;
        if(coluna == 'D') colunaID = 3;
        if(coluna == 'E') colunaID = 4;
        if(coluna == 'F') colunaID = 5;
        if(coluna == 'G') colunaID = 6;
        if(coluna == 'H') colunaID = 7;
        if(coluna == 'I') colunaID = 8;
        if(coluna == 'J') colunaID = 9;
        if(coluna == 'L') colunaID = 10;
        if(coluna == 'M') colunaID = 11;
        //posicao ja bombardeada
        if(tabuleiroCopia[linha][colunaID] != 0){
            return 0;
        }else {
        // Se existir base
            if(tabuleiro[linha][colunaID] != 0) {
                pontuacao ++;

                if(tabuleiro[linha][colunaID] == 1) {
                    tabuleiroCopia[linha][colunaID] = 1;
                }
                if(tabuleiro[linha][colunaID] == 2) {
                     tabuleiroCopia[linha][colunaID] = 2;
                }
                if(tabuleiro[linha][colunaID] == 3) {
                     tabuleiroCopia[linha][colunaID] = 3;
                }
                if(tabuleiro[linha][colunaID] == 4) {
                     tabuleiroCopia[linha][colunaID] = 4;

                }
            }else {
                tabuleiroCopia[linha][colunaID] = 5; // Tiro no terreno
            }
            return 1;
        }
     }
}
void menuGrafico(){
	printf(" No ano de 2046, um grupo de cientista conseguem terminar o maior feito da humanidade “um botão de reiniciar” uma máquina do tempo. Motivo para ser comemorado pois a única salvação da terra é voltar no tempo e destruir todas as bases que contém o vírus que acabou com quase toda a população do planeta. Irineu foi o soldado qualificado para essa missão , voltando para o ano de 2014, após 5 anos preso nas instalações secretas da CIA conseguiu convencer o diretor da CIA alertando de diversos desastres antes mesmo de ter acontecido. Só que a arma biológica irá ser usada no ano de 2019 no dia 5 de março e faltando apenas um dia para impedir esses ataques , vão bombardear pontos exatos para a destruição dessas instalações e assim salvando a humanidade. \n  Você deve escolher uma posição dada pelas letras e pelos numeros de 0 a 11. Se acertar uma base é retornado o número da base, se não será retornado um X. O jogo acaba quando a base de todas as bases do inimigo forem destruidas \n\n");

}
int main() {
	menuGrafico();
    printf("SALVE O MUNDO \n\n");
    int i;
    int j;
    int linha;
    char coluna;
    alocar();
    while(pontuacao != 18 && bombas > 0) {
        desenharInterface(0);
        printf("COLUNA => ");
        scanf("%c", &coluna);
        char colunaUpperCase = (toupper(coluna));
        printf("\nLINHA => ");
        scanf("%i", &linha);
        getchar();
        estado = jogadas(colunaUpperCase,linha);
        system("clear");
    }
    desenharInterface(1); // Quando terminar mostra o campo original
    return 0;
}
