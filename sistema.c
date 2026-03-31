#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define ARQUIVOS_DADOS "alunos.txt"

//Dados que serão utilizados no sistema
typedef struct{
    int ra;
    char nome[MAX_NOME];
    float notas[3];
} Aluno;

//Função para evitar bug ao clicar ENTER, ou seja, sem pular leituras
void limparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

//Passagem por referência e Alocação Dinâmica
void cadastrarAluno(Aluno** alunos, int *total){

    //Redimensiona o array de alunos
    *alunos = realloc(*alunos, (*total + 1) * sizeof(Aluno));

    if(*alunos == NULL){
        printf("Erro de alocação de memória! \n");
        exit(1);
    }

    printf("\n--- Novo Cadastro ---\n");
    printf("RA do aluno: ");
    scanf("%d", &(*alunos)[*total].ra);
    limparBuffer();

    printf("Nome do aluno: ");
    fgets((*alunos)[*total].nome, MAX_NOME, stdin);
    (*alunos)[*total].nome[strcspn((*alunos)[*total].nome, "\n")] = '\0';

    for(int i = 0; i < 3; i++){
        printf("Nota %d:", i + 1);
        scanf("%f", &(*alunos)[*total].notas[i]);
    }

    (*total)++; //Aumentando a contagem de alunos
    printf("Alunos cadastrado com sucesso!\n");
}

void calcularMedia(const Aluno *a){
    
    float soma = 0;

    for(int i = 0; i < 3; i++){
        soma += a->notas[i];
    }

    float media = soma / 3.0;

    printf("RA: %d | Nome: %-20s | Media: %.2f - %s\n", a->ra, a->nome, media, (media >= 6.0) ? "Aprovado" : "Reprovado");
}

void listarAlunos(const Aluno *alunos, int total){

    if(total == 0){
        printf("\nNenhum aluno cadastrado no sistema\n");
        return;
    }

    printf("\n--- Lista de alunos matriculados ---\n");
    for(int i = 0; i < total; i++){
        //Passando o endereço de memória atual do aluno para a função
        calcularMedia(&alunos[i]);
    }
}

//Salvando os dados em um arquivo
void salvarDados(const Aluno *alunos, int total){

    FILE *arquivo = fopen(ARQUIVOS_DADOS, "w");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo\n");
        return;
    }

    //Salvando a quantidade total na primeira linha
    fprintf(arquivo, "%d\n", total);
    
    //Salvando os dados de cada aluno
    for(int i = 0; i < total; i++){
        fprintf(arquivo, "%d\n%s\n%.2f %.2f %.2f\n", alunos[i].ra, alunos[i].nome, alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2]);
    }

    fclose(arquivo);
    printf("\nDados salvos com sucesso no arquivo '%s'!\n", ARQUIVOS_DADOS);
}

//Carregando dados ao inicio do programa
void carregarDados(Aluno **alunos, int *total){

    FILE *arquivo = fopen(ARQUIVOS_DADOS, "r");
    if(arquivo == NULL){
        printf("Sistema vazio");
        return;
    }

    //Lê a primeira linha para ver quantos alunos existem
    fscanf(arquivo, "%d\n", total);

    //Alocando o espaço de memória de acorda com a quantidade de alunos
    *alunos = realloc(*alunos, (*total) * sizeof(Aluno));

    for (int i = 0; i < *total; i++) {
        fscanf(arquivo, "%d\n", &(*alunos)[i].ra);
        
        fgets((*alunos)[i].nome, MAX_NOME, arquivo);
        (*alunos)[i].nome[strcspn((*alunos)[i].nome, "\n")] = '\0';
        
        fscanf(arquivo, "%f %f %f\n", 
               &(*alunos)[i].notas[0], &(*alunos)[i].notas[1], &(*alunos)[i].notas[2]);
    }
    
    fclose(arquivo);
    printf("Dados carregados com sucesso! (%d alunos)\n", *total);

}

int main() {
    Aluno *alunos = NULL; //Ponteiro que vai atuar como array dinâmico
    int total_alunos = 0;
    int opcao;

    //Tenta carregar os dados assim que o programa abre
    carregarDados(&alunos, &total_alunos);

    //Menu Interativo (CRUD Base)
    do {
        printf("\n=== Sistema de Gerenciamento Academico ===\n");
        printf("1. Cadastrar Novo Aluno\n");
        printf("2. Listar Alunos e Medias\n");
        printf("3. Salvar Dados Manualmente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarAluno(&alunos, &total_alunos);
                break;
            case 2:
                listarAlunos(alunos, total_alunos);
                break;
            case 3:
                salvarDados(alunos, total_alunos);
                break;
            case 0:
                salvarDados(alunos, total_alunos); // Salva automaticamente ao sair
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    //Liberando a memória
    free(alunos); 
    
    return 0;
}