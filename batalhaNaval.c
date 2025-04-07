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
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal);
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // Inicializa o tabuleiro do jogo
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Define as posições dos navios
    char *posicaoNavioHorizontal = "D3";
    char *posicaoNavioVertical = "H6";
    Posicao posicaoHorizontal = decodificarPosicao(posicaoNavioHorizontal);
    Posicao posicaoVertical = decodificarPosicao(posicaoNavioVertical);

    // Valida e posiciona o navio horizontal
    if (posicaoValida(tabuleiro, posicaoHorizontal.linha, posicaoHorizontal.coluna, true)) {
        posicionarNavio(tabuleiro, posicaoHorizontal.linha, posicaoHorizontal.coluna, true);
        printf("Navio horizontal posicionado com sucesso na posição %s\n",
               posicaoNavioHorizontal);
    } else {
        printf("Erro: Posição inválida para o navio horizontal!\n");
        return 1;
    }

    // Valida e posiciona o navio vertical
    if (posicaoValida(tabuleiro, posicaoVertical.linha, posicaoVertical.coluna, false)) {
        posicionarNavio(tabuleiro, posicaoVertical.linha, posicaoVertical.coluna, false);
        printf("Navio vertical posicionado com sucesso na posição %s\n",
               posicaoNavioVertical);
    } else {
        printf("Erro: Posição inválida para o navio vertical!\n");
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
bool posicaoValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal) {
    // Verifica se a posição inicial está dentro dos limites
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return false;
    }
    // Verifica se o navio se estende além dos limites do tabuleiro
    if (ehHorizontal) {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false;
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
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, bool ehHorizontal) {
    if (ehHorizontal) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
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