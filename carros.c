#include <stdio.h>

#define MAX_CARROS 100

struct Carro
{
    int ano;
    char chassi[8];
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

int main(void)
{
    Carro carros[MAX_CARROS];

    int continuar = 1;

    for (int i = 0; i < MAX_CARROS; i++)
    {
        carros[i] = CriarCarro();

        printf("Deseja continuar? (1 - Sim / 0 - Não): ");
        scanf("%d", &continuar);

        if (continuar == 0)
        {
            if (i < MAX_CARROS - 1)
                carros[i + 1].ano = 0;
            break;
        }
    }

    printf("------------------\n");
    for (int i = 0; i < MAX_CARROS && carros[i].ano != "0"; i++)
    {
        printf("Carro %d: Ano: %d, Chassi: %d\n", i + 1, carros[i].ano, carros[i].chassi);
    }

    return 0;
}