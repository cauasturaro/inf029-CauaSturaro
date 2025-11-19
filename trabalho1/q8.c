#include <stdio.h>
#include <stdlib.h>

void printMenu()
{
    printf(" ===== Menu ===== \n");
    printf(" Digite qualquer coisa e pressione Enter para começar \n");
    printf(" Digite 0 para sair \n");
}

void criarTabuleiro(char tabuleiro[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tabuleiro[i][j] = '-';
        }
    }
}

int placeTabuleiro(char value, char tabuleiro[3][3], int x, int y)
{
    if (tabuleiro[y][x] != '-')
        return 0;

    tabuleiro[y][x] = value;

    return 1;
}

void flushInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

char handleElementTabuleiro(int turn)
{
    switch (turn)
    {
    case 1:
        return 'X';
        break;
    case 2:
        return 'O';
        break;

    default:
        break;
    }
}

int handleCelula(int turn, char tabuleiro[3][3], char local[])
{
    if (local[0] < 49 || local[0] > 51)
        return 0;
    if (local[1] < 65 || local[1] > 67)
        return 0;

    int x, y;

    switch (local[0])
    {
    case 49:
        x = 0;
        break;
    case 50:
        x = 1;
        break;
    case 51:
        x = 2;
        break;

    default:
        break;
    }

    switch (local[1])
    {
    case 65:
        y = 0;
        break;
    case 66:
        y = 1;
        break;
    case 67:
        y = 2;
        break;

    default:
        break;
    }

    char value = handleElementTabuleiro(turn);

    int localValido = placeTabuleiro(value, tabuleiro, x, y);
    if (localValido == 0)
        return 0;

    return 1;
}

void printTabuleiro(char tabuleiro[3][3])
{
    printf("   1   2   3 \n");
    printf("A  %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("  ------------\n");
    printf("B  %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("  ------------\n");
    printf("C  %c | %c | %c \n\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

int tabuleiroCheio(char tabuleiro[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tabuleiro[i][j] == '-')
                return 0;
        }
    }

    return 1;
}

int checkTabuleiro(char tabuleiro[3][3]) // 0: nada, 1: jogador 1 ganhou, 2: jogador 2 ganhou, 3: empate
{
    char venceu = '-';
    // Linhas e colunas
    for (int i = 0; i < 3; i++)
    {
        if (tabuleiro[i][0] == '-')
            continue;
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
            venceu = tabuleiro[i][0];
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i])
            venceu = tabuleiro[0][i];
    }

    // Diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[2][2] != '-')
        venceu = tabuleiro[0][0];
    if (tabuleiro[2][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][0] && tabuleiro[0][0] != '-')
        venceu = tabuleiro[0][0];

    int cheio = tabuleiroCheio(tabuleiro);
    if (cheio == 1 && venceu == '-')
        return 3;

    switch (venceu)
    {
    case '-':
        return 0;
        break;

    case 'X':
        return 1;
        break;

    case 'O':
        return 2;
        break;

    default:
        return 0;
    }
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void game(char tabuleiro[3][3])
{
    int winner = 0;
    int turn = 1;

    while (winner == 0)
    {
        clearScreen();
        printTabuleiro(tabuleiro);
        int valida = 0;
        while (valida == 0)
        {
            printf("Jogador %d digite a posição (ex: 1A): ", turn);
            char local[3];
            fgets(local, 3, stdin);
            flushInput();

            valida = handleCelula(turn, tabuleiro, local);
            if (valida == 0)
                printf("LOCAL INVÁLIDO!\n");
        }
        winner = checkTabuleiro(tabuleiro);
        turn = (turn == 1) ? 2 : 1;
    }

    if (winner == 3)
        printf("O JOGO DEU VELHA!!");
    else
        printf("O ganhador foi o jogador %d\n\n", winner);

    printTabuleiro(tabuleiro);

    printf("\nDigite aqualquer coisa e pressione ENTER para continuar");
    flushInput();
    fgets((char[3]){0}, 3, stdin);
}

int main(void)
{
    char tabuleiro[3][3];

    int option = -1;

    while (option != 0)
    {
        printMenu();
        scanf("%d", &option);
        flushInput();
        criarTabuleiro(tabuleiro);
        game(tabuleiro);
    }

    return 0;
}