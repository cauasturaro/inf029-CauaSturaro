#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100

#define MAX_PROPRIETARIO 25
#define MAX_MODELO 20
#define MAX_MARCA 20
#define MAX_CHASSI 20

// MODEL CARRO
struct Carro
{
    char proprietario[MAX_PROPRIETARIO];
    char modelo[MAX_MODELO];
    char marca[MAX_MARCA];
    char chassi[MAX_CHASSI];
    int ano;
};
typedef struct Carro Carro;

// UTILITÁRIOS
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void limparTela()
{
    system("clear||cls");
}

void removerBL(char *str)
{
    int tamanho = strlen(str);
    if (tamanho > 0 && str[tamanho - 1] == '\n')
    {
        str[tamanho - 1] = '\0';
    }
}

void pausar()
{
    printf("Pressione Enter para continuar...");
    getchar();
}

// FUNÇÕES CARRO
Carro CriarCarro()
{
    Carro carro;
    printf("======= Adicionar Carro =======\n");

    printf("Proprietário do veículo: ");
    fgets(carro.proprietario, MAX_PROPRIETARIO, stdin);
    removerBL(carro.proprietario);

    printf("Marca do veículo: ");
    fgets(carro.marca, MAX_MARCA, stdin);
    removerBL(carro.marca);

    printf("Modelo do veículo: ");
    fgets(carro.modelo, MAX_MODELO, stdin);
    removerBL(carro.modelo);

    printf("Digite o chassi do carro: ");
    fgets(carro.chassi, MAX_CHASSI, stdin);
    removerBL(carro.chassi);

    printf("Digite o ano do carro: ");
    scanf("%d", &carro.ano);
    limparBuffer();

    return carro;
}

void ListarCarros(Carro carros[], int quantidade)
{
    limparTela();
    printf("============ Carros ==============\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("\n=== Carro %d ===\n", i + 1);
        printf("- Proprietário: %s \n - Marca: %s \n - Modelo: %s \n - Chassi: %s \n - Ano: %d\n", carros[i].proprietario, carros[i].marca, carros[i].modelo, carros[i].chassi, carros[i].ano);
    }
    printf("\n==================================\n");

    pausar();
}

void CriandoCarros(Carro carros[], int *qntCarros)
{
    limparTela();
    int continuar = 1;
    if (*qntCarros < MAX_CARROS)
    {
        for (int i = *qntCarros; i < MAX_CARROS; i++)
        {
            carros[i] = CriarCarro();
            (*qntCarros)++;

            printf("Deseja adicionar outro carro? 1 - Sim | 0 - Não: ");
            scanf("%d", &continuar);
            limparBuffer();

            if (continuar == 0)
                break;
        }
    }
    else
    {
        printf("Limite de carros atingido!\n");
        pausar();
    }
}

void RemoverCarro(Carro carros[], int *qntCarros)
{
    limparTela();
    if (*qntCarros == 0)
    {
        printf("Nenhum carro cadastrado!\n");
        return;
    }

    ListarCarros(carros, *qntCarros);

    int id;
    printf("Digite o ID do carro a ser removido: ");
    scanf("%d", &id);
    limparBuffer();

    int index = id - 1;
    if (id < 0 || id >= *qntCarros)
    {
        printf("ID inválido!\n");
        return;
    }

    for (int i = index; i < *qntCarros - 1; i++)
    {
        carros[i] = carros[i + 1];
        (*qntCarros)--;
    }
}

// TELAS
int menu(Carro carros[], int *qntCarros)
{
    int opcao = 0;

    do
    {
        limparTela();
        printf("========== Menu ==========\n");

        printf("1 - Adicionar Carro\n");
        printf("2 - Listar Carros\n");
        printf("3 - Remover Carro\n");
        printf("0 - Sair\n");

        printf("==========================\n");

        printf("> ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao < 0 || opcao > 3)
            printf("Opção inválida! Tente novamente.\n");

    } while (opcao < 0 || opcao > 3);

    switch (opcao)
    {
    case 1:
        CriandoCarros(carros, qntCarros);
        return 1;
        break;
    case 2:
        ListarCarros(carros, *qntCarros);
        return 1;
        break;
    case 3:
        RemoverCarro(carros, qntCarros);
        return 1;
        break;
    case 0:
        printf("Saindo...\n");
        return 0;
        break;
    default:
        printf("Opção inválida!\n");
        return 1;
        break;
    }
}

// MAIN
int main(void)
{
    limparTela();

    Carro carros[MAX_CARROS];
    int qntCarros = 0;

    int continuar;
    do
    {
        continuar = menu(carros, &qntCarros);
    } while (continuar != 0);

    return 0;
}