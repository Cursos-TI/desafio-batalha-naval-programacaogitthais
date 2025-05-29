#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define OCUPADO 3
#define AGUA 0

// Função para verificar se a posição já está ocupada
int posicaoLivre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return tabuleiro[linha][coluna] == AGUA;
}

// Função para posicionar navio horizontal
int posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (coluna + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha, coluna + i)) return 0;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha][coluna + i] = OCUPADO;
    }
    return 1;
}

// Função para posicionar navio vertical
int posicionarVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna)) return 0;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha + i][coluna] = OCUPADO;
    }
    return 1;
}

// Função para posicionar navio na diagonal principal (↘)
int posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + NAVIO > TAM || coluna + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna + i)) return 0;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = OCUPADO;
    }
    return 1;
}

// Função para posicionar navio na diagonal secundária (↙)
int posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + NAVIO > TAM || coluna - NAVIO < -1) return 0;
    for (int i = 0; i < NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna - i)) return 0;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = OCUPADO;
    }
    return 1;
}

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa todas as posições com água
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;

    // Posiciona os 4 navios
    int sucesso = 1;

    // Navio horizontal
    sucesso &= posicionarHorizontal(tabuleiro, 1, 2);

    // Navio vertical
    sucesso &= posicionarVertical(tabuleiro, 4, 5);

    // Navio diagonal principal ↘
    sucesso &= posicionarDiagonalPrincipal(tabuleiro, 0, 0);

    // Navio diagonal secundária ↙
    sucesso &= posicionarDiagonalSecundaria(tabuleiro, 6, 8);

    if (sucesso) {
        exibirTabuleiro(tabuleiro);
    } else {
        printf("Erro ao posicionar navios. Verifique sobreposição ou limites.\n");
    }

    return 0;
}


