#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>  // <--- add this for time()

#define TAM_STRING 30
#define TAM_COR 5

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} exercito;

typedef struct {
    int tipoMissao; // 0 a 4, para identificar o tipo de missão
    char descricao[TAM_STRING];
    int objetivo; // Pode ser usado para armazenar o número de territórios a conquistar ou tropas a eliminar, dependendo da missão
    int concluida; // 0 para não concluída, 1 para concluída
} missao;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    setlocale(LC_ALL,"Portuguese");


    // Parte 1 - Cadastro dos territórios e exércitos

    missao* missoes = calloc(TAM_COR, sizeof(missao));
    if (missoes == NULL){
        printf("Erro ao alocar memória para missões.\n");
        return 1;
    }

    // Inicializar descrições das missões uma vez
    strcpy(missoes[0].descricao, "Conquistar um territorio.");
        missoes[0].tipoMissao = 0;
        missoes[0].objetivo = 1; // Conquistar 1 território
        missoes[0].concluida = 0; // Missão inicialmente não concluída
    strcpy(missoes[1].descricao, "Eliminar o exercito inimigo.");
        missoes[1].tipoMissao = 1;
        missoes[1].objetivo = 1; // Eliminar 1 exército adversário
        missoes[1].concluida = 0;
    strcpy(missoes[2].descricao, "Controlar 2 territorios.");
        missoes[2].tipoMissao = 2;
        missoes[2].objetivo = 2;
        missoes[2].concluida = 0;
    strcpy(missoes[3].descricao, "Controlar 3 territorios.");
        missoes[3].tipoMissao = 3;
        missoes[3].objetivo = 3;
        missoes[3].concluida = 0;
    strcpy(missoes[4].descricao, "Eliminar um exercito adversario.");
        missoes[4].tipoMissao = 4;
        missoes[4].objetivo = 1;
        missoes[4].concluida = 0;

    exercito* war = calloc(TAM_COR, sizeof(exercito));
    if (war == NULL){
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    srand((unsigned)time(NULL)); // Inicializa a semente para rand() com o tempo atual

    int totalExercito = 0;
    int atacante, defensor;
    int indiceMissao = rand() % TAM_COR; // Gera um índice aleatório para a missão
    int indiceExercito = rand() % TAM_COR; // Índice para o próximo exército a ser cadastrado
    int opcao;
    int exercitoDestruidos = 0;
    int territoriosControlados = 1;

    printf("Vamos cadastrar territórios!\n");

    for (int i = 0; i < TAM_COR; i++){ // Loop para cadastrar os territórios, limitado a TAM_COR

        printf("Território %d:\n", i + 1);

        printf("Digite o nome do território: \n");
        fgets(war[i].nome, TAM_STRING, stdin);

        printf("Digite a cor do exercito: \n");
        fgets(war[i].cor, TAM_STRING, stdin);

        printf("Digite a quantidade de tropas do exercito: \n");
        scanf("%d", &war[i].tropas);

        war[i].cor[strcspn(war[i].cor, "\n")] = '\0'; // Remove a nova linha do final da string
        war[i].nome[strcspn(war[i].nome, "\n")] = '\0'; // Remove a nova linha do final da string

        limparBuffer();

        totalExercito++;
    }
    printf("Cadastro concluído!\n");
    
    // Parte 2 - Batalha


    srand((unsigned)time(NULL)); // só uma vez, antes de rand()
    
    do { // Loop principal do jogo, onde ocorrem as batalhas
        printf("------------------------------------\n");
        printf("------------MAPA DO MUNDO-----------\n");
        printf("------------------------------------\n");
    for(int i = 0; i < totalExercito; i++){
        printf("%d. %s (Exercito %s, Tropas: %d)\n", 1 + i, war[i].nome, war[i].cor, war[i].tropas);
    }
        printf("\n");
        printf("-----Sua missão (Exercito %s)-----\n", war[indiceExercito].cor);
        printf("%s\n", missoes[indiceMissao].descricao); // Atribui uma missão baseada no índice);
        printf("\n");

        printf("Menu de ações:\n");
        printf("1. Atacar\n");
        printf("2. Verificar Missão\n");
        printf("3. Sair\n");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: // Atacar
            printf("------------------------------------\n");
            printf("----------Fase de batalha!------------\n");
            printf("------------------------------------\n");
            printf("\n");

        printf("Escolha o território atacante(1 a %d): \n", totalExercito);
        scanf("%d", &atacante);
        if(atacante < 1 || atacante > totalExercito) { // Verifica se a opção é válida (entre 1 e totalExercito)
            printf("Opção inválida. Por favor, escolha um território válido.\n");
            printf("Pressione Enter para continuar...\n");
            limparBuffer();
            getchar(); // Espera o usuário pressionar Enter
            continue; // Volta para o início do loop para escolher novamente
        }
        
        if(war[atacante - 1].tropas <= 1) { // Verifica se o território atacante tem mais de 1 tropa para atacar
                printf("O território atacante deve ter mais de 1 tropa para atacar.\n");
                printf("Escolha novamente.\n");
                printf("Pressione Enter para continuar...\n");
                limparBuffer();
                getchar(); // Espera o usuário pressionar Enter
                continue; // Volta para o início do loop para escolher novamente
            }

        printf("Escolha o território defensor(1 a %d): ", totalExercito);
        scanf("%d", &defensor);
        if(defensor < 1 || defensor > totalExercito) { // Verifica se a opção é válida (entre 1 e totalExercito)
            printf("Opção inválida. Por favor, escolha um território válido.\n");
            printf("Pressione Enter para continuar...\n");
            limparBuffer();
            getchar(); // Espera o usuário pressionar Enter
            continue; // Volta para o início do loop para escolher novamente
        }

        
        if (atacante > 0 && atacante <= totalExercito && defensor > 0 && defensor <= totalExercito) { // Verifica se as opções são válidas (entre 1 e totalExercito)
            if(defensor == atacante) {
                printf("O território atacante e defensor não podem ser o mesmo.\n");
                printf("Escolha novamente.\n");
                printf("Pressione Enter para continuar...\n");
                limparBuffer();
                getchar(); // Espera o usuário pressionar Enter
                continue; // Volta para o início do loop para escolher novamente
            }
            if (atacante != defensor) { // Verifica se o atacante e defensor são diferentes
                int resultadoAtaque = rand() % 6 + 1;
                int resultadoDefesa = rand() % 6 + 1;
                printf("O atacante %s rolou um dado e tirou: %d\n", war[atacante - 1].nome, resultadoAtaque);
                printf("O defensor %s rolou um dado e tirou: %d\n", war[defensor - 1].nome, resultadoDefesa);

            if (resultadoAtaque > resultadoDefesa){ // Se o resultado do ataque for maior que o da defesa, o defensor perde uma tropa
                printf("Vitoria do Ataque! Defensor perdeu 1 tropa.\n");
                war[defensor - 1].tropas -= 1;
            } else if (resultadoDefesa >= resultadoAtaque){ // Se o resultado da defesa for maior ou igual ao do ataque, o atacante perde uma tropa
                printf("Vitoria da Defesa! Atacante perdeu 1 tropa.\n");
                war[atacante - 1].tropas -= 1;
            
            }
        } else { // Se as opções não forem válidas, exibe uma mensagem de erro
            printf("Opção inválida.\n");
        }

        if (war[defensor - 1].tropas <= 0) { // Se o defensor perder todas as tropas, o território é conquistado pelo atacante
            printf("O território %s foi conquistado pelo exército %s!\n", war[defensor - 1].nome, war[atacante - 1].cor);
            war[defensor - 1].tropas = war[atacante - 1].tropas - 1; // O novo território conquistado recebe as tropas restantes do atacante
            exercitoDestruidos++; // Incrementa o contador de exércitos destruídos
            territoriosControlados++; // Incrementa o contador de territórios controlados

            strcpy(war[defensor - 1].cor, war[atacante - 1].cor); // O território conquistado adota a cor do atacante
        }

        printf("Pressione Enter para o proximo turno...\n");
        limparBuffer();
        getchar();
        }
        break;

        case 2:{ // Verificar Missão
            if (exercitoDestruidos == 1 && missoes[indiceMissao].tipoMissao == 1) { // Missão de eliminar um exército adversário
                missoes[indiceMissao].concluida = 1; // Marca a missão como concluída
                printf("Parabéns! Você concluiu sua missão: %s\n", missoes[indiceMissao].descricao);
                printf("Você venceu o jogo! Obrigado por jogar!\n");
                opcao = 3; // Define a opção para sair do jogo
            } else if (exercitoDestruidos == 1 && missoes[indiceMissao].tipoMissao == 4) { // Missão de eliminar um exército adversário
                missoes[indiceMissao].concluida = 1; // Marca a missão como concluída
                printf("Parabéns! Você concluiu sua missão: %s\n", missoes[indiceMissao].descricao);
                printf("Você venceu o jogo! Obrigado por jogar!\n");
                opcao = 3; // Define a opção para sair do jogo
            } else if (territoriosControlados == 1 && missoes[indiceMissao].tipoMissao == 0) { // Missão de conquistar um território
                missoes[indiceMissao].concluida = 1; // Marca
                printf("Parabéns! Você concluiu sua missão: %s\n", missoes[indiceMissao].descricao);
                printf("Você venceu o jogo! Obrigado por jogar!\n");
                opcao = 3; // Define a opção para sair do jogo
            } else if (territoriosControlados == 2 && missoes[indiceMissao].tipoMissao == 2) { // Missão de controlar 2 territórios
                missoes[indiceMissao].concluida = 1; // Marca a missão como concluída
                printf("Parabéns! Você concluiu sua missão: %s\n", missoes[indiceMissao].descricao);
                printf("Você venceu o jogo! Obrigado por jogar!\n");
                opcao = 3; // Define a opção para sair do jogo
            } else if (territoriosControlados == 3 && missoes[indiceMissao].tipoMissao == 3) { // Missão de controlar 3 territórios
                missoes[indiceMissao].concluida = 1; // Marca a missão como concluída
                printf("Parabéns! Você concluiu sua missão: %s\n", missoes[indiceMissao].descricao);
                printf("Você venceu o jogo! Obrigado por jogar!\n");
                opcao = 3; // Define a opção para sair do jogo
            } else {
                printf("Missão atual: %s\n", missoes[indiceMissao].descricao);
                printf("Objetivo: %d\n", missoes[indiceMissao].objetivo);
                printf("Status: Em andamento\n");
                printf("Pressione Enter para continuar...\n");
                limparBuffer();
                }
        break;

        case 3:{ // Sair
            printf("Encerrando o jogo. Obrigado por jogar!\n");
            }
        break;

        default:
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
            printf("Pressione Enter para continuar...\n");
            limparBuffer();
        } 
    }

    } while (opcao != 3); // Loop infinito, o programa só termina quando o usuário escolher sair (atacante = 0)

    free(missoes);
    free(war);
    return 0;
} 
    