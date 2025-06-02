#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define NAVIO 3
#define OCUPADO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HAB 5
#define RAIO 2 // Centro da matriz 5x5

// -------------------------- Funções de Navio ------------------------------

int posicaoLivre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return tabuleiro[linha][coluna] == AGUA;
}

int posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (coluna + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linha, coluna + i)) return 0;

    for (int i = 0; i < NAVIO; i++)
        tabuleiro[linha][coluna + i] = OCUPADO;
    return 1;
}

int posicionarVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linha + i, coluna)) return 0;

    for (int i = 0; i < NAVIO; i++)
        tabuleiro[linha + i][coluna] = OCUPADO;
    return 1;
}

int posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + NAVIO > TAM || coluna + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linha + i, coluna + i)) return 0;

    for (int i = 0; i < NAVIO; i++)
        tabuleiro[linha + i][coluna + i] = OCUPADO;
    return 1;
}

int posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha + NAVIO > TAM || coluna - NAVIO < -1) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linha + i, coluna - i)) return 0;

    for (int i = 0; i < NAVIO; i++)
        tabuleiro[linha + i][coluna - i] = OCUPADO;
    return 1;
}

// --------------------- Funções de Habilidade -------------------------

void criarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= RAIO - i && j <= RAIO + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

void criarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == RAIO || j == RAIO)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

void criarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - RAIO) + abs(j - RAIO) <= RAIO)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (matriz[i][j] == 1) {
                int linhaReal = origemLinha + (i - RAIO);
                int colunaReal = origemColuna + (j - RAIO);
                if (linhaReal >= 0 && linhaReal < TAM && colunaReal >= 0 && colunaReal < TAM) {
                    if (tabuleiro[linhaReal][colunaReal] == AGUA)
                        tabuleiro[linhaReal][colunaReal] = HABILIDADE;
                }
            }
        }
    }
}

// ------------------------ Exibir Tabuleiro ----------------------------

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// ----------------------------- Main ----------------------------------

int main() {
    int tabuleiro[TAM][TAM];
    int habilidade[TAM_HAB][TAM_HAB];

    // Inicializar o tabuleiro com água
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;

    // Posicionar navios
    int sucesso = 1;
    sucesso &= posicionarHorizontal(tabuleiro, 1, 2);          // Horizontal
    sucesso &= posicionarVertical(tabuleiro, 4, 5);            // Vertical
    sucesso &= posicionarDiagonalPrincipal(tabuleiro, 0, 0);   // ↘
    sucesso &= posicionarDiagonalSecundaria(tabuleiro, 6, 8);  // ↙

    if (!sucesso) {
        printf("Erro ao posicionar navios.\n");
        return 1;
    }

    // Exibe tabuleiro inicial
    printf("Tabuleiro inicial com navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    // Aplicar habilidade Cone em (2,2)
    criarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 2, 2);
    printf("\nApós aplicar Cone em (2,2):");
    exibirTabuleiro(tabuleiro);

    // Aplicar habilidade Cruz em (5,5)
    criarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 5, 5);
    printf("\nApós aplicar Cruz em (5,5):");
    exibirTabuleiro(tabuleiro);

    // Aplicar habilidade Octaedro em (7,7)
    criarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 7, 7);
    printf("\nApós aplicar Octaedro em (7,7):");
    exibirTabuleiro(tabuleiro);

    return 0;
}



