#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que define o território
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército
    int tropas;     // Quantidade de tropas
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do exército (Ex: vermelho, azul): ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o \n
    }
}

// Função para exibir todos os territórios
void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n========== MAPA ==========\n");
    for (int i = 0; i < qtd; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("----------------------------\n");
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n[ERRO] Você não pode atacar um território da mesma cor!\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("\n[ERRO] O atacante precisa de mais de 1 tropa para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1; // de 1 a 6
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- ATAQUE ---\n");
    printf("%s (Cor: %s) lança dado: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("%s (Cor: %s) lança dado: %d\n", defensor->nome, defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // transfere metade das tropas
        atacante->tropas = atacante->tropas - defensor->tropas; // atacante mantém o resto
    } else {
        printf("Resultado: %s resistiu ao ataque!\n", defensor->nome);
        atacante->tropas--; // perde 1 tropa
    }
}

// --------- SISTEMA DE MISSÕES ---------

// Sorteia e atribui missão a um jogador
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    *destino = (char*) malloc((strlen(missoes[sorteio]) + 1) * sizeof(char));
    if (*destino != NULL) {
        strcpy(*destino, missoes[sorteio]);
    }
}

// Exibe a missão do jogador
void exibirMissao(const char* missao) {
    printf("\nSua missão é: %s\n", missao);
}

// Verifica se missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "Conquistar 3 territórios") != NULL) {
        int conquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) conquistados++;
        }
        return (conquistados >= 3);
    }
    else if (strstr(missao, "Eliminar cor vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) {
                return 0; // ainda existe vermelho
            }
        }
        return 1;
    }
    return 0;
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// ---------------- MAIN ----------------
int main() {
    srand(time(NULL)); // aleatoriedade

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar(); // limpa \n

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirMapa(mapa, qtd);

    // Missoes pré-definidas
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 2 territórios",
        "Ter mais de 10 tropas no total",
        "Conquistar qualquer território azul"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Atribui missão ao jogador
    char* missaoJogador = NULL;
    atribuirMissao(&missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    int opcao;
    do {
        printf("\nMenu:\n1 - Atacar\n2 - Exibir mapa\n0 - Sair\nOpção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int iAtacante, iDefensor;
            printf("Escolha o território atacante (1 a %d): ", qtd);
            scanf("%d", &iAtacante);
            printf("Escolha o território defensor (1 a %d): ", qtd);
            scanf("%d", &iDefensor);
            getchar();

            if (iAtacante < 1 || iAtacante > qtd || iDefensor < 1 || iDefensor > qtd) {
                printf("Opção inválida!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);

                // Após ataque, verifica se missão foi cumprida
                if (verificarMissao(missaoJogador, mapa, qtd)) {
                    printf("\n>>> PARABÉNS! Você cumpriu sua missão: %s <<<\n", missaoJogador);
                    break; // encerra o jogo
                }
            }
        } else if (opcao == 2) {
            exibirMapa(mapa, qtd);
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);
    return 0;
}
