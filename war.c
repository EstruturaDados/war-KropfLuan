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

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
    setlocale(LC_ALL,"Portuguese");

    exercito* war = calloc(TAM_COR, sizeof(exercito));
    if (war == NULL){
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    int totalExercito = 0;
    int atacante, defensor;

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


    srand((unsigned)time(NULL)); // só uma vez, antes de rand()

    do { // Loop principal do jogo, onde ocorrem as batalhas
        printf("------------------------------------\n");
        printf("------------MAPA DO MUNDO-----------\n");
        printf("------------------------------------\n");
    for(int i = 0; i < totalExercito; i++){
        printf("%d. %s (Exercito %s, Tropas: %d)\n", 1 + i, war[i].nome, war[i].cor, war[i].tropas);
    }
        printf("------------------------------------\n");
        printf("----------Fase de batalha!------------\n");

        printf("Escolha o território atacante(1 a %d, ou zero para sair): \n", totalExercito);
        scanf("%d", &atacante);
        if(atacante < 0 || atacante > totalExercito) { // Verifica se a opção é válida (entre 1 e totalExercito, ou zero para sair)
            printf("Opção inválida. Por favor, escolha um território válido ou zero para sair.\n");
            printf("Pressione Enter para continuar...\n");
            limparBuffer();
            getchar(); // Espera o usuário pressionar Enter
            continue; // Volta para o início do loop para escolher novamente
        }
        if(atacante == 0) {
            printf("Encerrando o jogo. Obrigado por jogar!\n");
            break; // Sai do loop e encerra o programa
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
            war[atacante - 1].tropas = 1; // O território atacante fica com apenas 1 tropa
            strcpy(war[defensor - 1].cor, war[atacante - 1].cor); // O território conquistado adota a cor do atacante
        }

        printf("Pressione Enter para o proximo turno...\n");
        limparBuffer();
        getchar();
        }
    } while (atacante != 0); // Loop infinito, o programa só termina quando o usuário escolher sair (atacante = 0)

    free(war);
    return 0;
} 
    