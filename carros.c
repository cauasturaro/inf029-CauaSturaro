#include <stdio.h>

#define MAX_CARROS 100

struct Carro
{
    int ano;
    int chassi;
};
typedef struct Carro Carro;

Carro CriarCarro()
{
    Carro carro;
    printf("Digite o ano do carro: ");
    scanf("%d", &carro.ano);
    printf("Digite o chassi do carro: ");
    scanf("%d", &carro.chassi);
    return carro;
}

void ListarCarros(Carro carros[], int quantidade)
{
    printf("------------------\n");
    for (int i = 0; i < quantidade; i++)
    {
        printf("Carro %d: Ano: %d, Chassi: %d\n", i + 1, carros[i].ano, carros[i].chassi);
    }
    printf("------------------\n");
}

void criandoCarros(Carro carros[], int *qntCarros)
{
    int continuar = 1;
    if (*qntCarros < MAX_CARROS)
    {
        for (int i = *qntCarros; i < MAX_CARROS; i++)
        {
            carros[i] = CriarCarro();
            (*qntCarros)++;

            printf("Deseja continuar? (1 - Sim / 0 - Não): ");
            scanf("%d", &continuar);
            if (continuar == 0)
                break;
        }
    }
    else
    {
        printf("Limite de carros atingido!\n");
    }
}

int menu(Carro carros[], int *qntCarros)
{
    int opcao = 0;

    do
    {
        printf("1. Adicionar Carro\n");
        printf("2. Listar Carros\n");
        printf("3. Sair\n");

        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 3)
        {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao < 1 || opcao > 3);

    switch (opcao)
    {
    case 1:
        criandoCarros(carros, qntCarros);
        return 1;
        break;
    case 2:
        ListarCarros(carros, *qntCarros);
        return 1;
        break;
    case 3:
        printf("Saindo...\n");
        return 0;
        break;
    default:
        printf("Opção inválida!\n");
        return 1;
        break;
    }
}

int main(void)
{
    Carro carros[MAX_CARROS];
    int qntCarros = 0;

    int continuar;
    do
    {
        continuar = menu(carros, &qntCarros);
    } while (continuar != 0);

    return 0;
}