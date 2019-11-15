white = 0 black = 1 unoccupied = -1

								 board = {
	{0, 0, 0, 0},

	{0, 0, 0, 0, 0},

	{-1, -1, 0, 0, -1, -1},

	{-1, -1, -1, -1, -1, -1, -1},

	{-1, -1, 1, 1, -1, -1},

	{1, 1, 1, 1, 1},

	{1, 1, 1, 1}};

int main()
{
	// actual game board
	frostfire board;
	int botColor; // black or white

	scanf("%d", &botColor);
	char move[6], opponent_move[6];
	while (game has not ended)
	{
		// assuming player white starts
		if (bot is white)
		{
			move = botMove(board, botColor); // calculating the bot's move
			makeMove(board, move);			 // making the move on the actual board
			print(move);
			activePlayer = black;

			// user's turn
			scanf("%s", &opponent_move); // input of Opponents's move (assumed to be valid)

			makeMove(board, opponent_move);
			activePlayer = white;
		}
		else // if bot is black
		{
			// user's turn
			scanf("%s", opponent_move); // input of Opponents's move

			makeMove(board, &opponent_move);
			activePlayer = black;

			move = botMove(board, botColor); // calculating the bot's move
			makeMove(board, move);			 // making the move on the actual board
			print(move);
			activePlayer = white;
		}
	}
}
