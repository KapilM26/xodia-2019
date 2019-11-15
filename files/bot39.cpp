/*
	Standard Bot (Depth 3 Grouping)
*/

#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define white 0
#define black 1
#define invalid 1000
#define infinity 1000000

class bot;

void playAgainstBot(bot b);

struct Marble
{
    int player;
    int grouping;
    float centralDistance;
    Marble(int p = 0, int g = 0, float cD = 0)
    {
        player = p;
        grouping = g;
        centralDistance = cD;
    }
};

typedef unordered_map<string, Marble> MarbleList;

class Board
{
	friend class bot;
	friend class bot;
	friend void playAgainstBot(bot b);

    // data members
    MarbleList marbles;
    int count[2];
    string limits[7][2];
    int active;

public:

    // member functions
    Board(int a);
    void display();
    bool validate(string move);
    string getDirection(string rdi, string rdf);
	bool inLimit(string rd);
	void move(string m);
	float calcCenterDistance(string pos);
	int calcGrouping(string pos);
	string getNeighbour(string pos, string dir);
	int winner();
	int getactive() { return active; }
};

Board::Board(int a = white)
{
    active = a;
	count[white] = count[black] = 11;

    marbles["A4"] = {white};marbles["A5"] = {white};marbles["A6"] = {white};marbles["A7"] = {white};
    marbles["B3"] = {white};marbles["B4"] = {white};marbles["B5"] = {white};marbles["B6"] = {white};marbles["B7"] = {white};
    marbles["C4"] = {white};marbles["C5"] = {white};

    marbles["E3"] = {black};marbles["E4"] = {black};  
    marbles["F1"] = {black};marbles["F2"] = {black};marbles["F3"] = {black};marbles["F4"] = {black};marbles["F5"] = {black};
    marbles["G1"] = {black};marbles["G2"] = {black};marbles["G3"] = {black};marbles["G4"] = {black};

    limits[0][0] = "A4";    limits[0][1] = "A7";
    limits[1][0] = "B3";    limits[1][1] = "B7";
    limits[2][0] = "C2";    limits[2][1] = "C7";
    limits[3][0] = "D1";    limits[3][1] = "D7";
    limits[4][0] = "E1";    limits[4][1] = "E6";
    limits[5][0] = "F1";    limits[5][1] = "F5";
    limits[6][0] = "G1";    limits[6][1] = "G4";

	for(MarbleList::iterator it = marbles.begin(); it != marbles.end(); it++)
	{
		it->second.centralDistance = calcCenterDistance(it->first);
	}
}

void Board::display()
{
    char row = 'A';
	int dia = 7;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2 - i; j >= 0; j--)
		{
			cout << " ";
		}
		cout << row << ". ";
		for (string j = limits[i][0]; j <= limits[i][1]; j[1]++)
		{
			if(marbles.count(j)) (marbles[j].player == black)?cout << "B ": cout << "W ";
            else cout << "_ ";
		}
		cout << endl;
		row++;
	}
	for (int i = 4; i < 7; i++)
	{
		for (int j = 0; j < i - 3; j++)
		{
			cout << " ";
		}
		cout << row << ". ";
		for (string j = limits[i][0]; j <= limits[i][1]; j[1]++)
		{
			if(marbles.count(j)) (marbles[j].player == black)?cout << "B ": cout << "W ";
            else cout << "_ ";
		}
		cout << dia << endl;
		row++;
		dia--;
	}
	cout << "       1 2 3 4" << endl;
}

string Board::getDirection(string rdi, string rdf)
{
	if (rdi[0] == rdf[0]) // along same row
	{
		if (rdi[1] < rdf[1]) return "EE"; // going east
		else return "WW"; // going west
	}
	else if (rdi[1] == rdf[1]) // along same diagonal
	{
		if (rdi[0] < rdf[0]) return "SE";
		else return "NW";
	}
	else // along NE direction
	{
		if (rdi[0] < rdf[0]) return "SW";
		else return "NE";
	}
}

bool Board::inLimit(string rd)
{
	int i = rd[0] - 65;
	if(i < 0 || i > 6) return false;
	if(rd >= limits[i][0] && rd <= limits[i][1]) return true;
	return false;
}

bool Board::validate(string move)
{
    string m1 = move.substr(0, 2);
    string m2 = move.substr(3, 2);
    string dir = getDirection(m1, m2);
	int deltaX = 0, deltaY = 0;
	/*
		deltaX and deltaY will indicate what to add to the current position
		for west, decrease col; for east increase col....
	*/
	if (dir == "WW") { deltaX = 0;	deltaY = -1; }
	else if (dir == "EE") { deltaX = 0;	deltaY = 1; }
	else if (dir == "NW") { deltaX = -1;	deltaY = 0; }
	else if (dir == "SE") { deltaX = 1;	deltaY = 0; }
	else if (dir == "NE") { deltaX = -1;	deltaY = 1; }
	else if (dir == "SW") { deltaX = 1;	deltaY = -1; }

    string x = m1;
    x[0] += deltaX; x[1] += deltaY;

	// more than two selected
    if(m2 != x) return false;

	// if blank space selected
	if(marbles.count(m1) == 0 || marbles.count(m2) == 0) return false;

	// opponent is selected or two different marbles are selected
	if(marbles[m1].player != marbles[m2].player || marbles[m1].player == !active) return false;

    string m3 = m2, m4 = m2;
    m3[0] += deltaX;    m3[1] += deltaY;
    m4[0] += 2*deltaX;  m4[1] += 2*deltaY;

	// if new position is not in board
	if(!inLimit(m3)) return false;

	// if three in a row
	if(marbles.count(m3))
	{
		if(marbles[m3].player == active || marbles.count(m4)) return false;
	}

	// corner push check
	if((m3 == "A4" && dir == "NW") || (m3 == "A7" && dir == "NE") || (m3 == "D1" && dir == "WW") || (m3 == "D7" && dir == "EE") || (m3 == "G1" && dir == "SW") || (m3 == "G4" && dir == "SE")) return false;

	return true;
}

void Board::move(string m)
{
	string m1 = m.substr(0, 2), m2 = m.substr(3, 2);
	int deltaX = m2[0] - m1[0], deltaY = m2[1] - m1[1];
	string m3 = m2, m4 = m2;
	m3[0] += deltaX;	m3[1] += deltaY;
	m4[0] += 2*deltaX;	m4[1] += 2*deltaY;

	
	// marble is being pushed
	if(marbles.count(m3))
	{
		if(!inLimit(m4)) // if marble is being KOed
		{
			marbles[m3].player = active;
			count[!active]--;
		}
		else { marbles[m4] = {!active}; marbles[m4].centralDistance = calcCenterDistance(m4); }
		marbles[m3].player = active;
		marbles[m2].player = active;
	}
	// marbles are being moved
	else
	{
		marbles[m3] = {active};
		marbles[m3].centralDistance = calcCenterDistance(m3);
	}
	marbles.erase(m1);

	active = !active;
}

float Board::calcCenterDistance(string pos)
{
	return sqrt((pos[0]-'D')*(pos[0]-'D') + (pos[1]-'4')*(pos[1]-'4'));
}

int Board::calcGrouping(string pos)
{
	int grouping = 0;
	string neighbours[6] = {pos, pos, pos, pos, pos, pos};
	neighbours[0][1]++;
	neighbours[1][1]--;
	neighbours[2][0]--; neighbours[2][1]++; 
	neighbours[3][0]++; neighbours[3][1]--; 
	neighbours[4][0]++;
	neighbours[5][0]--;
	for(int i = 0; i < 6; i++)
	{
		if(marbles.count(neighbours[i]) && marbles[neighbours[i]].player == marbles[pos].player)
			grouping++;
	}
	return grouping;
}

string Board::getNeighbour(string pos, string dir)
{
	if(dir == "EE")
	{
		pos[1]++;
	}
	else if(dir == "WW")
	{
		pos[1]--;
	}
	else if(dir == "NE")
	{
		pos[0]--;	pos[1]++;
	}
	else if(dir == "SW")
	{
		pos[0]++;	pos[1]--;
	}
	else if(dir == "SE")
	{
		pos[0]++;
	}
	else if(dir == "NW")
	{
		pos[0]--;
	}
	return pos;
}

int Board::winner()
{
	if(count[white] == 7) return black;
	else if(count[black] == 7) return white;
	else return -1;
}

class bot
{
	friend void playAgainstBot(bot b);

	Board comp;
	int botPlayer;
	int maxDepth;
public:
	bot(Board c, int mD, int bP);
	int evaluate();
	vector<int> minimax(int depth, bool isMax, int alpha, int beta);
	string botMove();
	void set(Board b);
	vector<string> getMarbles(int color);
	int getplayer() { return botPlayer; }
};

bot::bot(Board c, int mD, int bP)
{
	comp = c;
	maxDepth = mD;
	botPlayer = bP;
}

void bot::set(Board b)
{
	comp.marbles = b.marbles;
	comp.count[white] = b.count[white];
	comp.count[black] = b.count[black];
	comp.active = b.active;
}

int bot::evaluate()
{
	if(comp.winner() == botPlayer)
	{
		return infinity;
	}
	else if(comp.winner() == !botPlayer)
	{
		return -infinity;
	}
	
	int value = 0;

	// +1000 for each marble bot has extra, -1000 for each marble player has extra
	int centerDistance = 0, grouping = 0, profit;
	profit = comp.count[botPlayer] - comp.count[!botPlayer];
	value += profit * 1000;
	// value += profit * 2000;
	for(MarbleList::iterator it = comp.marbles.begin(); it != comp.marbles.end(); it++)
	{
		if(it->second.player == botPlayer)
		{
			centerDistance += it->second.centralDistance;
			grouping += comp.calcGrouping(it->first);
		}
	}

	if(centerDistance < 18) value += 400;
	else if(centerDistance < 23) value += 300;
	else if(centerDistance < 27) value += 200;
	else if(centerDistance < 32) value += 100;

	if(grouping > 35) value += 320;
	else if(grouping > 30) value += 240;
	else if(grouping > 25) value += 160;
	else if(grouping > 20) value += 80;

	/*if(grouping > 32) value += 420;
	else if(grouping > 27) value += 340;
	else if(grouping > 22) value += 250;
	else if(grouping > 19) value += 150;*/

	return value;
	
}

vector<string> bot::getMarbles(int color)
{
	vector<string> allMarbles;
	for(unordered_map<string, Marble>::iterator it = comp.marbles.begin(); it != comp.marbles.end(); it++)
	{
		if(it->second.player == color) allMarbles.push_back(it->first);
	}
	return allMarbles;
}

vector<int> bot::minimax(int depth, bool isMax, int alpha, int beta)
{
	if(depth == maxDepth) return {evaluate(), depth};
	else if(comp.winner() == botPlayer) return {infinity, depth};
	else if(comp.winner() == !botPlayer) return {-infinity, depth}; 

	vector<string> marbleList = getMarbles((isMax)?botPlayer:!botPlayer);
	
	if(isMax) // maximizer's move
	{
		int maxVal = -infinity;
		int leastDepth = 100;

		for(int i = 0; i < marbleList.size(); i++)
		{
			
			
			string marblePos = marbleList[i];
			string dirs[] = {"EE", "WW", "NW", "SE", "SW", "NE"};
			for(int i = 0; i < 6; i++)
			{
				string neighbour = comp.getNeighbour(marblePos, dirs[i]);

				string tempMove = marblePos + " " + neighbour;
				if(comp.validate(tempMove))
				{
					MarbleList temp = comp.marbles;
					int whites = comp.count[white], blacks = comp.count[black];

					comp.move(tempMove);

					vector<int> val = minimax(depth+1, false, alpha, beta);

					if(val[0] > maxVal)
					{
						maxVal = val[0];
						leastDepth = val[1];
					}
					else  if(val[0] >= maxVal && val[1] < depth)
					{
						maxVal = val[0];
						leastDepth = val[1];
					}
					else if(val[0] == maxVal && val[1] == depth)
					{
						int x = rand() % 2;
						if(x)
						{
							maxVal = val[0];
							leastDepth = val[1];
						}
					}

					// undo
					comp.marbles = temp;
					comp.count[white] = whites;
					comp.count[black] = blacks;
					comp.active = !comp.active;

					// alpha-beta pruning
					alpha = max(alpha, maxVal);
					if(beta <= alpha) break;
				}
			}
			
		}
		return {maxVal, leastDepth};
	}
	else // minimizer's move
	{
		int minVal = infinity;
		int leastDepth = 100;

		for(int i = 0; i < marbleList.size(); i++)
		{
			
			string marblePos = marbleList[i];
			string dirs[] = {"EE", "WW", "NW", "SE", "SW", "NE"};
			for(int i = 0; i < 6; i++)
			{
				string neighbour = comp.getNeighbour(marblePos, dirs[i]);

				string tempMove = marblePos + " " + neighbour;
				if(comp.validate(tempMove))
				{
					MarbleList temp = comp.marbles;
					int whites = comp.count[white], blacks = comp.count[black];

					comp.move(tempMove);

					vector<int> val = minimax(depth+1, true, alpha, beta);

					if(val[0] < minVal)
					{
						minVal = val[0];
						leastDepth = val[1];
					}
					else  if(val[0] <= minVal && val[1] < depth)
					{
						minVal = val[0];
						leastDepth = val[1];
					}
					else if(val[0] == minVal && val[1] == depth)
					{
						int x = rand() % 2;
						if(x)
						{
							minVal = val[0];
							leastDepth = val[1];
						}
					}

					// undo
					comp.marbles = temp;
					comp.count[white] = whites;
					comp.count[black] = blacks;
					comp.active = !comp.active;

					// alpha-beta pruning
					beta = min(beta, minVal);
					if(beta <= alpha) break;
				}
			}
		
		}
		return {minVal, leastDepth};
	}
}

string bot::botMove()
{
	int bestVal = -infinity;
	int leastDepth = 100;
	string bestMove = "None";
	vector<string> marbleList = getMarbles(botPlayer);

	for(int i = 0; i < marbleList.size(); i++)
	{
		
		string marblePos = marbleList[i];
		string dirs[] = {"EE", "WW", "NW", "SE", "SW", "NE"};
		for(int i = 0; i < 6; i++)
		{
			string neighbour = comp.getNeighbour(marblePos, dirs[i]);

			string tempMove = marblePos + " " + neighbour;
			if(comp.validate(tempMove))
			{
				MarbleList temp = comp.marbles;
				int whites = comp.count[white], blacks = comp.count[black];

				comp.move(tempMove);

				vector<int> val = minimax(0, false, -infinity, infinity);

				if(val[0] > bestVal)
				{
					bestVal = val[0];
					leastDepth = val[1];
					bestMove = tempMove;
				}
				else  if(val[0] >= bestVal && val[1] < leastDepth)
				{
					bestVal = val[0];
					leastDepth = val[1];
					bestMove = tempMove;
				}
				else if(val[0] == bestVal && val[1] == leastDepth)
				{
					int x = rand() % 2;
					if(x)
					{
						bestVal = val[0];
						leastDepth = val[1];
						bestMove = tempMove;
					}
				}

				// undo
				comp.marbles = temp;
				comp.count[white] = whites;
				comp.count[black] = blacks;
				comp.active = !comp.active;
			}
		}
		
	}
	return bestMove;
}

void playAgainstBot(bot b)
{
	Board board(white);
	//board.display();
	string s;

	while (board.winner() == -1)
	{
		//cout << "Your Move: ";
		if (board.getactive() != b.getplayer())
		{
			getline(cin, s);
			board.move(s);
		}

		//if (s == "exit")
		//	return;

		// if (board.validate(s))
		// {
		// }
		// // else
		// {
		// 	cout << "Invalid Move!" << endl;
		// 	continue;
		// }

		if (board.winner() == white)
		{
			//cout << endl;
			return;
		}

		//board.display();

		b.set(board);
		string compMove = b.botMove();
		//auto stop = high_resolution_clock::now();
		//auto duration = duration_cast<milliseconds>(stop - start);
		cout << compMove << endl;
		// cout << "Counter: " << counter << endl;
		// counter = 0;
		// cout << "Time taken: " << duration.count() << "ms" << endl;
		board.move(compMove);

		//board.display();

		if (board.winner() == black)
		{
			//cout << "The Bot Wins!" << endl;
			return;
		}
	}
}

int main()
{
	Board board(white);
	int player;
	cin >> player;
	cin.get();
	bot b1(board, 3, player);
	playAgainstBot(b1);
}