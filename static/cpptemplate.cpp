white = 0 black = 1 unoccupied = -1

                                 boardPattern = {
    {0, 0, 0, 0},

    {0, 0, 0, 0, 0},

    {-1, -1, 0, 0, -1, -1},

    {-1, -1, -1, -1, -1, -1, -1},

    {-1, -1, 1, 1, -1, -1},

    {1, 1, 1, 1, 1},

    {1, 1, 1, 1}};

int main()
{
    cin >> botColor;
    // actual game board
    frostfire board;
    // bot object
    bot b(board, botColor);
    b.setBoard(board); // setting bot's board to the current one

    string move;
    string opponent_move;
    while (game has not ended)
    {
        // player white starts
        if (bot is white)
        {
            // BOT'S TURN
            move = b.botMove(); // calculating the bot's move
            // validity of the move must be checked

            board.makeMove(move); // making the move on the actual board
            print(move);          //printing the bot's move

            activePlayer = black;

            // OPPONENT'S TURN
            // input opponents move, assume that it's valid
            cin >> opponent_move;
            board.makeMove(move);

            activePlayer = white;
        }
        else // if bot is black
        {
            // OPPONENT'S TURN
            // input opponents move, assume that it's valid
            cin >> opponent_move;
            board.makeMove(move);

            activePlayer = black;

            b.setBoard(board); // setting bot's board to the current one

            // BOT'S TURN
            move = b.botMove(); // calculating the bot's move
            // validity of the move must be checked

            board.makeMove(move); // making the move on the actual board
            print(move);          //printing the bot's move
            activePlayer = white;
        }
    }
}
