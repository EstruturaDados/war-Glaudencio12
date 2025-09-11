#include <stdio.h>     
#include <strings.h>

#define TOTAL_TERRITORIOS 5   // Quantidade fixa de territórios (vetor estático com 5 elementos)
#define TAM_NOME 50           // Tamanho máximo do nome do território
#define TAM_COR 20            // Tamanho máximo da cor

// Definição da struct Territorio
typedef struct {
    char nome[TAM_NOME];  // Nome do território
    char cor[TAM_COR];    // Cor do exército
    int tropas;           // Número de tropas
} Territorio;

// Vetor estático que armazena todos os territórios
Territorio territorios[TOTAL_TERRITORIOS];

// Função para cadastrar os territórios
void cadastrarTerritorios(){
    for (size_t i = 0; i < TOTAL_TERRITORIOS; i++){   // Loop para os 5 territórios
        printf("------ Cadastrando território número %d ------\n", i + 1);

        // Leitura do nome do território
        printf("==== Nome do território: ");
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o \n que fgets adiciona

        // Leitura da cor do território
        printf("==== Cor do território (Ex: verde, amarela): ");
        fgets(territorios[i].cor, TAM_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';  

        // Leitura do número de tropas
        printf("==== Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o \n que o scanf deixa no buffer

        printf("\n");
    }
}

// Função para exibir todos os territórios cadastrados
void exibirMapa(){
     printf("===========Mapa construído==========\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Número de Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }
}

int main(){
    cadastrarTerritorios();  // Chama a função para cadastrar os territórios
    exibirMapa();            // Mostra os territórios cadastrados

    return 0; 
}
