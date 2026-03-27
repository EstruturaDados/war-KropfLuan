#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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

    exercito war [TAM_COR];
    int totalExercito = 0;

    printf("Vamos cadastrar territórios!\n");

    for (int i = 0; i < TAM_COR; i++){

        printf("Território %d:\n", i + 1);

        printf("Digite o nome do território: \n");
        fgets(war[i].nome, TAM_STRING, stdin);

        printf("Digite a cor do exercito: \n");
        fgets(war[i].cor, TAM_STRING, stdin);

        printf("Digite a quantidade de tropas do exercito: \n");
        scanf("%d", &war[i].tropas);
        limparBuffer();

        totalExercito++;
    }
    printf("Cadastro concluído!\n");

    printf("------------------------------------\n");
    printf("------------MAPA DO MUNDO-----------\n");
    printf("------------------------------------\n");

    for(int i = 0; i < totalExercito; i++){
        printf("Território %d:\n",i + 1);
        printf("-Nome: %s", war[i].nome);
        printf("-Dominado por: Exercito %s", war[i].cor);
        printf("-Tropas: %d\n", war[i].tropas);
        printf("------------------------------------\n");
    }
}
