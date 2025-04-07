#include <stdio.h>
#include <stdbool.h>

// Constantes para o jogo
#define TAMANHO_TABULEIRO 10  // Tamanho do tabuleiro do jogo
#define TAMANHO_NAVIO 3       // Tamanho de cada navio
#define AGUA 0                // Valor representando água
#define NAVIO 3               // Valor representando partes do navio

// Estrutura para armazenar a posição decodificada
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
Posicao decodificarPosicao(char *posicaoNavio);
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal, bool ehDiagonal, bool ehDiagonalDecrescente);
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal, bool ehDiagonal, bool ehDiagonalDecrescente);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // Inicializa o tabuleiro do jogo
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    char *posicaoNavio1 = "C1"; // Horizontal
    char *posicaoNavio2 = "F8"; // Vertical
    char *posicaoNavio3 = "H5"; // Diagonal crescente
    char *posicaoNavio4 = "C6"; // Diagonal decrescente
    // Define as posições dos navios
    Posicao navios[4] = {
            decodificarPosicao(posicaoNavio1), // Horizontal
            decodificarPosicao(posicaoNavio2), // Vertical
            decodificarPosicao(posicaoNavio3), // Diagonal crescente
            decodificarPosicao(posicaoNavio4)  // Diagonal decrescente
    };

    // Valida e posiciona os navios
    if (posicaoValida(tabuleiro, navios[0].linha, navios[0].coluna, true, false, false)) {
        posicionarNavio(tabuleiro, navios[0].linha, navios[0].coluna, true, false, false);
        printf("Navio horizontal posicionado com sucesso na posição %s\n", posicaoNavio1);
    } else {
        printf("Erro: Posição inválida para o navio horizontal!\n");
        return 1;
    }

    if (posicaoValida(tabuleiro, navios[1].linha, navios[1].coluna, false, false, false)) {
        posicionarNavio(tabuleiro, navios[1].linha, navios[1].coluna, false, false, false);
        printf("Navio vertical posicionado com sucesso na posição %s\n", posicaoNavio2);
    } else {
        printf("Erro: Posição inválida para o navio vertical!\n");
        return 1;
    }

    if (posicaoValida(tabuleiro, navios[2].linha, navios[2].coluna, false, true, false)) {
        posicionarNavio(tabuleiro, navios[2].linha, navios[2].coluna, false, true, false);
        printf("Navio diagonal crescente posicionado com sucesso na posição %s\n", posicaoNavio3);
    } else {
        printf("Erro: Posição inválida para o navio diagonal crescente!\n");
        return 1;
    }

    if (posicaoValida(tabuleiro, navios[3].linha, navios[3].coluna, false, true, true)) {
        posicionarNavio(tabuleiro, navios[3].linha, navios[3].coluna, false, true, true);
        printf("Navio diagonal decrescente posicionado com sucesso na posição %s\n", posicaoNavio4);
    } else {
        printf("Erro: Posição inválida para o navio diagonal decrescente!\n");
        return 1;
    }

    // Exibe o tabuleiro
    printf("\nTabuleiro de Batalha:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Decodifica a posição do navio (ex: "D3" -> linha 2, coluna 3)
Posicao decodificarPosicao(char *posicaoNavio) {
    Posicao posicao;
    posicao.linha = posicaoNavio[1] - '1'; // Converte o caractere da linha para inteiro
    posicao.coluna = posicaoNavio[0] - 'A'; // Converte o caractere da coluna para inteiro
    return posicao;
}

// Verifica se a posição de um navio é válida
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal, bool ehDiagonal, bool ehDiagonalDecrescente) {
    // Verifica se a posição inicial está dentro dos limites
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return false;
    }

    // Verifica se o navio se estende além dos limites do tabuleiro
    if (ehHorizontal) {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;
        }
    } else if (ehDiagonal) {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;
        }
        if (ehDiagonalDecrescente) {
            if (coluna - TAMANHO_NAVIO + 1 < 0) {
                return false;
            }
        } else {
            if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return false;
            }
        }
    } else {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;
        }
    }

    // Verifica se há sobreposição com navios existentes
    if (ehHorizontal) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] == NAVIO) {
                return false;
            }
        }
    } else if (ehDiagonal) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (ehDiagonalDecrescente) {
                if (tabuleiro[linha + i][coluna - i] == NAVIO) {
                    return false;
                }
            } else {
                if (tabuleiro[linha + i][coluna + i] == NAVIO) {
                    return false;
                }
            }
        }
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] == NAVIO) {
                return false;
            }
        }
    }

    return true;
}

// Posiciona um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal, bool ehDiagonal, bool ehDiagonalDecrescente) {
    if (ehHorizontal) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    } else if (ehDiagonal) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (ehDiagonalDecrescente) {
                tabuleiro[linha + i][coluna - i] = NAVIO;  // Diagonal decrescente
            } else {
                tabuleiro[linha + i][coluna + i] = NAVIO;  // Diagonal crescente
            }
        }
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Exibe os índices das colunas
    printf("     A B C D E F G H I J\n");

    // Exibe a linha separadora
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("--");
    }
    printf("\n");

    // Exibe o tabuleiro com os índices das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        (i + 1 == 10) ? printf("%d | ", i + 1) : printf("%d  | ", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}