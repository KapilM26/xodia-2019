/*
	Repitition draw functionality added
*/
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define white 0
#define black 1
#define invalid 1000
#define infinity 1000000

int maxDepth = 4;

class bot;

void playAgainstBot(bot b);
void botvsbot(bot b1, bot b2);
void play();

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

typedef map<string, Marble> MarbleList;

class Board
{
	friend class bot;
	friend void playAgainstBot(bot b);
	friend void botvsbot(bot b1, bot b2);
	friend void play();

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
	string getNeighbour(string pos, string dir);
	int winner();
	vector<string> getMarbles(int color);
	bool movesLeft();
};

Board::Board(int a = white)
{
	active = a;
	count[white] = count[black] = 11;

	marbles["A4"] = {white};
	marbles["A5"] = {white};
	marbles["A6"] = {white};
	marbles["A7"] = {white};
	marbles["B3"] = {white};
	marbles["B4"] = {white};
	marbles["B5"] = {white};
	marbles["B6"] = {white};
	marbles["B7"] = {white};
	marbles["C4"] = {white};
	marbles["C5"] = {white};

	marbles["E3"] = {black};
	marbles["E4"] = {black};
	marbles["F1"] = {black};
	marbles["F2"] = {black};
	marbles["F3"] = {black};
	marbles["F4"] = {black};
	marbles["F5"] = {black};
	marbles["G1"] = {black};
	marbles["G2"] = {black};
	marbles["G3"] = {black};
	marbles["G4"] = {black};

	limits[0][0] = "A4";
	limits[0][1] = "A7";
	limits[1][0] = "B3";
	limits[1][1] = "B7";
	limits[2][0] = "C2";
	limits[2][1] = "C7";
	limits[3][0] = "D1";
	limits[3][1] = "D7";
	limits[4][0] = "E1";
	limits[4][1] = "E6";
	limits[5][0] = "F1";
	limits[5][1] = "F5";
	limits[6][0] = "G1";
	limits[6][1] = "G4";
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
			if (marbles.count(j))
				(marbles[j].player == black) ? cout << "B " : cout << "W ";
			else
				cout << "_ ";
		}
		cout << "\n";
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
			if (marbles.count(j))
				(marbles[j].player == black) ? cout << "B " : cout << "W ";
			else
				cout << "_ ";
		}
		cout << dia << "\n";
		row++;
		dia--;
	}
	cout << "       1 2 3 4"
		 << "\n";
}

string Board::getDirection(string rdi, string rdf)
{
	if (rdi[0] == rdf[0]) // along same row
	{
		if (rdi[1] < rdf[1])
			return "EE"; // going east
		else
			return "WW"; // going west
	}
	else if (rdi[1] == rdf[1]) // along same diagonal
	{
		if (rdi[0] < rdf[0])
			return "SE";
		else
			return "NW";
	}
	else // along NE direction
	{
		if (rdi[0] < rdf[0])
			return "SW";
		else
			return "NE";
	}
}

bool Board::inLimit(string rd)
{
	int i = rd[0] - 65;
	if (i < 0 || i > 6)
		return false;
	if (rd >= limits[i][0] && rd <= limits[i][1])
		return true;
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
	if (dir == "WW")
	{
		deltaX = 0;
		deltaY = -1;
	}
	else if (dir == "EE")
	{
		deltaX = 0;
		deltaY = 1;
	}
	else if (dir == "NW")
	{
		deltaX = -1;
		deltaY = 0;
	}
	else if (dir == "SE")
	{
		deltaX = 1;
		deltaY = 0;
	}
	else if (dir == "NE")
	{
		deltaX = -1;
		deltaY = 1;
	}
	else if (dir == "SW")
	{
		deltaX = 1;
		deltaY = -1;
	}

	string x = m1;
	x[0] += deltaX;
	x[1] += deltaY;

	// more than two selected
	if (m2 != x)
		return false;

	// if blank space selected
	if (marbles.count(m1) == 0 || marbles.count(m2) == 0)
		return false;

	// opponent is selected or two different marbles are selected
	if (marbles[m1].player != marbles[m2].player || marbles[m1].player == !active)
		return false;

	string m3 = m2, m4 = m2;
	m3[0] += deltaX;
	m3[1] += deltaY;
	m4[0] += 2 * deltaX;
	m4[1] += 2 * deltaY;

	// if new position is not in board
	if (!inLimit(m3))
		return false;

	// if three in a row
	if (marbles.count(m3))
	{
		if (marbles[m3].player == active || marbles.count(m4))
			return false;
	}

	// corner push check
	if ((m3 == "A4" && dir == "NW") || (m3 == "A7" && dir == "NE") || (m3 == "D1" && dir == "WW") || (m3 == "D7" && dir == "EE") || (m3 == "G1" && dir == "SW") || (m3 == "G4" && dir == "SE"))
		return false;

	return true;
}

void Board::move(string m)
{
	string m1 = m.substr(0, 2), m2 = m.substr(3, 2);
	int deltaX = m2[0] - m1[0], deltaY = m2[1] - m1[1];
	string m3 = m2, m4 = m2;
	m3[0] += deltaX;
	m3[1] += deltaY;
	m4[0] += 2 * deltaX;
	m4[1] += 2 * deltaY;

	// marble is being pushed
	if (marbles.count(m3))
	{
		if (!inLimit(m4)) // if marble is being KOed
		{
			marbles[m3].player = active;
			count[!active]--;
		}
		else
			marbles[m4] = {!active};
		marbles[m3].player = active;
		marbles[m2].player = active;
	}
	// marbles are being moved
	else
	{
		marbles[m3].player = {active};
	}
	marbles.erase(m1);

	active = !active;
}

float Board::calcCenterDistance(string pos)
{
	return sqrt((pos[0] - 'D') * (pos[0] - 'D') + (pos[1] - '4') * (pos[1] - '4'));
}

string Board::getNeighbour(string pos, string dir)
{
	if (dir == "EE")
	{
		pos[1]++;
	}
	else if (dir == "WW")
	{
		pos[1]--;
	}
	else if (dir == "NE")
	{
		pos[0]--;
		pos[1]++;
	}
	else if (dir == "SW")
	{
		pos[0]++;
		pos[1]--;
	}
	else if (dir == "SE")
	{
		pos[0]++;
	}
	else if (dir == "NW")
	{
		pos[0]--;
	}
	return pos;
}

int Board::winner()
{
	if (count[white] == 7)
		return black;
	else if (count[black] == 7)
		return white;
	else
		return -1;
}

vector<string> Board::getMarbles(int color)
{
	vector<string> allMarbles;
	for (map<string, Marble>::iterator it = marbles.begin(); it != marbles.end(); it++)
	{
		if (it->second.player == color)
			allMarbles.push_back(it->first);
	}
	return allMarbles;
}

bool Board::movesLeft()
{
	vector<string> marbleList = getMarbles(active);
	for (int i = 0; i < marbleList.size(); i++)
	{
		string marblePos = marbleList[i];
		string dirs[] = {"EE", "WW", "NW", "SE", "SW", "NE"};
		for (int i = 0; i < 6; i++)
		{
			string neighbour = this->getNeighbour(marblePos, dirs[i]);

			string tempMove = marblePos + " " + neighbour;
			if (this->validate(tempMove))
			{
				return true;
			}
		}
	}
	return false;
}

void play()
{
	Board board(white);
	string s;
	vector<string> drawCheck;
	while (board.winner() == -1)
	{

		if (board.movesLeft() == false)
		{
			cout << "DRAW\n";
			cout << s << endl;
			return;
		}
		getline(cin, s);

		if (board.validate(s))
		{
			cout << "VALID\n";
			cout << s << "\n";
			board.move(s);
		}
		else
		{
			cout << "INVALID MOVE!\n";
			return;
		}

		if (board.winner() == white)
		{
			cout << "WIN\n";
			cout << s << "\n";
			cout << "0" << endl;
			cout << "4 dragons knocked off the board!\n";
			return;
		}

		drawCheck.push_back(s);
		if (drawCheck.size() == 9)
		{
			if ((drawCheck[0] == drawCheck[4] && drawCheck[4] == drawCheck[8]) && (drawCheck[1] == drawCheck[5]) && (drawCheck[2] == drawCheck[6]) && (drawCheck[3] == drawCheck[7]))
			{
				cout << "DRAW\n";
				cout << s << endl;
				return;
			}
			else
			{
				drawCheck.erase(drawCheck.begin());
			}
		}

		getline(cin, s);

		if (board.validate(s))
		{
			board.move(s);
			cout << "VALID\n";
			cout << s << "\n";
		}
		else
		{
			cout << "INVALID MOVE!\n";
			return;
		}

		if (board.winner() == black)
		{
			cout << "WIN\n";
			cout << s << "\n";
			cout << "1" << endl;
			cout << "4 dragons knocked off the board\n";
			return;
		}

		drawCheck.push_back(s);
		if (drawCheck.size() == 9)
		{
			if ((drawCheck[0] == drawCheck[4] && drawCheck[4] == drawCheck[8]) && (drawCheck[1] == drawCheck[5]) && (drawCheck[2] == drawCheck[6]) && (drawCheck[3] == drawCheck[7]))
			{
				cout << "DRAW\n";
				cout << s << endl;
				return;
			}
			else
			{
				drawCheck.erase(drawCheck.begin());
			}
		}
	}
}

int main()
{
	play();
	usleep(1000);
}
