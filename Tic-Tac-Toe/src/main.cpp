#include <iostream>
#include "functions.h"
#include "config.h"

int main()
{
    constexpr char PLAYER_ONE_CHAR = 'X';
    constexpr char PLAYER_TWO_CHAR = 'O';
    mode game_mode;
    
    int spot;
    int turn;
    char board[9] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
    };

    std::cout << "Welcome to Tic Tac Toe" << std::endl;
    game_mode = prompt_mode();
    print_board(board);

    while (true)
    {
        std::cout << "----------------------------------------------------" << std::endl;
        // Player one's turn
        number_input(board, spot, PLAYER_ONE_CHAR, PLAYER_TWO_CHAR);
        print_board(board);
        if (check_win(board, turn, PLAYER_ONE_CHAR)) {
            if (check_replay(board)) {
                prompt_mode();
                print_board(board);
                continue;
            }
            else
                break;
        }

        std::cout << "----------------------------------------------------" << std::endl;
        // Player two's turn
        if (game_mode == PLAYERVBOT)
            bot_input(board, PLAYER_TWO_CHAR, PLAYER_ONE_CHAR);
        else if (game_mode == PLAYERVPLAYER)
            number_input(board, spot, PLAYER_TWO_CHAR, PLAYER_ONE_CHAR);
        print_board(board);
        turn++;
        if (check_win(board, turn, PLAYER_TWO_CHAR))
            if (check_replay(board)) {
                turn = 0;
                game_mode = prompt_mode();
                print_board(board);
                continue;
            }
            else
                break;
    }
    std::cout << "Goodbye!" << std::endl;
}
