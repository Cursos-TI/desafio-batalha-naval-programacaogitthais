#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define OCUPADO 3
#define AGUA 0

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Coordenadas iniciais dos navios (pré-definidas)
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;

    int linhaVertical = 5;
    int colunaVertical = 7;

    // Verifica se os navios estão dentro dos limites do tabuleiro
    if (colunaHorizontal + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaVertical + TAM_NAVIO <= TAM_TABULEIRO) {

        // Verifica se há sobreposição entre os navios
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaHorizontal][colunaHorizontal + i] == OCUPADO ||
                tabuleiro[linhaVertical + i][colunaVertical] == OCUPADO) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posiciona o navio horizontal
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaHorizontal][colunaHorizontal + i] = OCUPADO;
            }

            // Posiciona o navio vertical
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaVertical + i][colunaVertical] = OCUPADO;
            }

            // Exibe o tabuleiro
            printf("Tabuleiro Batalha Naval:\n\n");
            for (int i = 0; i < TAM_TABULEIRO; i++) {
                for (int j = 0; j < TAM_TABULEIRO; j++) {
                    printf("%d ", tabuleiro[i][j]);
                }
                printf("\n");
            }

        } else {
            printf("Erro: os navios se sobrepõem.\n");
        }

    } else {
        printf("Erro: coordenadas inválidas para o tamanho do navio.\n");
    }

    return 0;
}

