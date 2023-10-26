#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define GREEN_COLOR "\033[0;32m"
#define RED_COLOR "\033[0;31m"
#define CYAN_COLOR "\033[0;36m"
#define YELLOW_COLOR "\033[0;33m"
#define WHITE_COLOR "\033[0;37m"

// Structs
typedef struct
{
    int line;
    int column;
} Board;

typedef struct
{
    char *name;
    char piece;
    int score;
    Board board;

} Player;

// Functions prototype

void ClearBuffer(char *buffer);

void MaxNumberAttempts(int attempts, int total);

void ChooseStone(char *buffer_option, Player *player);

void RenderBoard(char board[][7], Player player);

void StartGame(char board[][7], Player *player);

void GetLine(char board[][7], Player *player);

void GetColumn(char board[][7], Player *player);

int main()
{

    system("chcp 65001");

    Player player[2];

    player[0].name = "Jogador - 1";
    player[1].name = "Jogador - 2";

    char buf_option[5];

    char board[4][7] = {{' ', ' ', 'A', ' ', 'B', ' ', 'C'},
                        {'1', ' ', '-', '|', '-', '|', '-'},
                        {'2', ' ', '-', '|', '-', '|', '-'},
                        {'3', ' ', '-', '|', '-', '|', '-'}};

    int run = 1;

    int score = 0;

    printf(GREEN_COLOR "\n>> *[¬º-°]¬* Desafio Octótropo *[¬º-°]¬* <<\n\n" WHITE_COLOR);

    system("pause");

    ChooseStone(buf_option, player);

    StartGame(board, player);

    return 0;
}

// functions definition

void ClearBuffer(char *buffer)
{
    int i = 0;

    /*limpa o buffer de entrada*/
    while ((buffer[i] = fgetc(stdin)) != '\n' && buffer[i] != EOF)
        i++;

    buffer[i] = '\0';
}

void MaxNumberAttempts(int attempts, int max)
{
    if (attempts >= max)
    {
        printf("Número máximo de tentativas excedido, partida cancelada!!!\n\n");
        system("pause");
        exit(-1);
    }
}

void ChooseStone(char *buffer_option, Player *player)
{
    int run = 1;
    int attempts = 0;

    while (run)
    {
        system("cls");

        printf("Informe uma peça:_");

        ClearBuffer(buffer_option);

        switch (toupper(buffer_option[0]))
        {
        case 'X':
            player[0].piece = 'X';
            player[1].piece = 'O';
            run = 0;
            break;

        case 'O':
            player[0].piece = 'O';
            player[1].piece = 'X';
            run = 0;
            break;

        default:
            MaxNumberAttempts(attempts, 5);

            printf(RED_COLOR ">>Opção inválida, tente novamente!\n" WHITE_COLOR);

            attempts++;

            system("pause");
        }
    }
}

void GetLine(char board[][7], Player *player)
{
    int run = 1;
    char buffer[5];
    int attempts = 0;

    while (run)
    {
        RenderBoard(board, *player);

        if (attempts > 0)
        {
            printf("Total tentativas: %i\n", attempts);
        }

        printf("Informe uma linha entre (1 - 3):_");

        ClearBuffer(buffer);

        switch (toupper(buffer[0]))
        {
        case '1':
        case 'A':
            player->board.line = 1;
            run = 0;
            break;

        case '2':
        case 'B':
            player->board.line = 2;
            run = 0;
            break;
        case '3':
        case 'C':
            player->board.line = 3;
            run = 0;
            break;

        default:
            MaxNumberAttempts(attempts, 5);

            printf(RED_COLOR ">>Opção inválida, tente novamente!\n" WHITE_COLOR);

            attempts++;

            system("pause");
        }
    }
}

void GetColumn(char board[][7], Player *player)
{
    char buffer[5];
    int run = 1;
    int attempts = 0;

    while (run)
    {
        RenderBoard(board, *player);

        printf("Linha selecionada: %i\n", player->board.line);

        if (attempts > 0)
        {
            printf("Total tentativas: %i\n", attempts);
        }

        printf("Informe uma coluna entre (A - C):_");

        ClearBuffer(buffer);

        switch (toupper(buffer[0]))
        {
        case '1':
        case 'A':
            player->board.column = 2;
            run = 0;
            break;

        case '2':
        case 'B':
            player->board.column = 4;
            run = 0;
            break;
        case '3':
        case 'C':
            player->board.column = 6;
            run = 0;
            break;

        default:
            MaxNumberAttempts(attempts, 5);

            printf(RED_COLOR ">>Opção inválida, tente novamente!\n" WHITE_COLOR);

            attempts++;

            system("pause");
        }
    }
}

void LoadBoard(char board[][7])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ('X' == board[i][j])
            {
                printf(CYAN_COLOR "%c", board[i][j]);
                continue;
            }

            if ('O' == board[i][j])
            {
                printf(WHITE_COLOR "%c", board[i][j]);
                continue;
            }

            printf(YELLOW_COLOR "%c", board[i][j]);
        }
        printf(WHITE_COLOR "\n");
    }
}

void GetInput(char board[][7], Player player)
{
    int run = 1;
    int attempts = 0;

    while (run)
    {

        GetLine(board, &player);

        GetColumn(board, &player);

        if (board[player.board.line][player.board.column] != '-')
        {
            MaxNumberAttempts(attempts, 5);
            printf(">> Ação incorreta, linha e coluna já ocupadas.\n");
            attempts++;
            continue;
        }

        board[player.board.line][player.board.column] = player.piece;

        run = 0;
    }
}

void RenderBoard(char board[][7], Player player)
{
    system("cls");

    LoadBoard(board);

    printf("\n%s [ %c ]\n", player.name, player.piece);
}

void CheckBoard(char board[][7], Player *player)
{
    // horizontal validation
    for (int i = 1; i < 4; i++)
    {
        for (int j = 2; j < 7; j++)
        {
            if (player->piece == board[i][j])
                player->score++;
        }

        if (player->score == 3)
        {
            printf(YELLOW_COLOR "\n PARTIDA CONQUISTADA - ATAQUE NA HORIZONTAL \n" WHITE_COLOR);
            exit(0);
        }

        player->score = 0;
    }

    // vertical validation
    for (int j = 2; j < 7; j++)
    {
        for (int i = 1; i < 4; i++)
        {
            if (player->piece == board[i][j])
                player->score++;
        }

        if (player->score == 3)
        {
            printf(YELLOW_COLOR "\n PARTIDA CONQUISTADA - ATAQUE NA VERTICAL \n" WHITE_COLOR);
            exit(0);
        }

        player->score = 0;
    }

    /*
        Validate Diagonal
        Movimento diagonal da esquerda para direita
    */
    // inicializa contador coluna
    int j = 2;

    for (int i = 1; i < 4; i++)
    {
        if (player->piece == board[i][j])
            player->score++;

        j += 2;
    }

    if (player->score == 3)
    {
        printf(YELLOW_COLOR "\n PARTIDA CONQUISTADA - ATAQUE DIAGONAL DA ESQUERDA PARA DIREITA \n" WHITE_COLOR);
        exit(0);
    }

    player->score = 0;

    /*
        Validate Diagonal
        Movimento diagonal da direita para esquerda
    */

    // inicializa pontuação e contador coluna
    player->score = 0;
    j = 6;

    for (int i = 1; i < 4; i++)
    {
        if (player->piece == board[i][j])
        {
            player->score++;
        }

        j -= 2;
    }

    if (player->score == 3)
    {
        printf(YELLOW_COLOR "\n PARTIDA CONQUISTADA - ATAQUE DIAGONAL DA DIREITA PARA ESQUERDA \n" WHITE_COLOR);
        exit(0);
    }

    player->score = 0;
}

void StartGame(char board[][7], Player *player)
{
    int counter = 0;

    while (1)
    {
        GetInput(board, player[counter]);

        RenderBoard(board, *player);

        CheckBoard(board, &player[counter]);

        counter = (counter > 0) ? 0 : 1;

        system("pause");
    }
}
