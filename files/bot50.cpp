
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<stdio.h>
#include <chrono> 
#include<stdlib.h>
#include<time.h>

#define maxD 3
#define infinity 1000000

using namespace std::chrono;
using namespace std;

string Players[2][11]={
    {"A4","A5","A6","A7","B3","B4","B5","B6","B7","C4","C5"},   //blue
    {"G1","G2","G3","G4","F1","F2","F3","F4","F5","E3","E4"}       //red
};

int Marbles[] = {11,11};

string directions[6] = {"EE","NE","NW","SE","SW","WW"};

class validation;
class bot;

void display();
void actualMove(validation,string,bool);
void play(bool);

class validation
{
    bool myColor;
    string players[2][11];
    int marbles[2];
    public:
        validation(bool pl = false)
        {
            for(int i = 0; i<2; i++)
            {
                for(int j=0; j<11; j++)
                    players[i][j] = Players[i][j];
                marbles[i] = Marbles[i];
            }
            myColor = pl;
        }

        bool isValid(string);
        bool isStringValid(string);
        bool inBoard(string);
        bool cornerPush(string, string);
        bool isPlayers(string, int); 
        void move(string);
        int isWin();
        string getDirection(string, string);
        string getNext(string, string);
        vector<int> convertDir(string);
        vector<string> getNeighbours(string,int);
        vector<string> getMoves();
        
        friend class bot;
};

class bot
{
	bool botPlayer;
    validation comp;
	public:
		bot(bool pl, validation v)
		{
			botPlayer = pl;
            comp = v;
		}
		string findBestMove();
		int clusterValue(vector<string>);
		int centreDist(string);
		int eval();
        	int mod(string);
        	int edgeValues(bool);
		int miniMax(bool, int, int, int);	
};



//---------------------validation class functions--------------------------

bool validation::isStringValid(string mov)
{
    if(mov.length() != 5) return false;
    if(mov[0]>='A' && mov[0]<='G' && mov[3]>='A' && mov[3]<='G')
        if(mov[1]>='1' && mov[1]<='7' && mov[4]>='1' && mov[4]<='7')
            return true;
        else
            return false;
    else
        return false;       
}

bool validation::isPlayers(string mar, int pl)
{
    for(int i = 0; i<11; i++)
        if(mar == players[pl][i])
            return true;
    return false;
}

bool validation::inBoard(string pos)
{
    if(pos[0] >= 'A' and pos[0] <= 'D')
    {    
        if(pos[1] <= '7' and pos[1] >= '0' + ('D' - pos[0] +1))
            return true;
        else
            return false;
    }
    else if(pos[0] > 'D' and pos[0] <= 'G')
    {
        if(pos[1] >= '1' and pos[1] <= '0' + 'G'-pos[0] + 4)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool validation::cornerPush(string pos, string Dir)
{
        if(pos == "A7" and Dir == "NE")
            return true;
        else if(pos == "D7" and Dir == "EE")
            return true;
        else if(pos == "G4" and Dir == "SE")
            return true;
        else if(pos == "G1" and Dir == "SW")
            return true;
        else if(pos == "D1" and Dir == "WW")
            return true;
        else if(pos == "A4" and Dir == "NW")
            return true;
        else    
            return false;
}

string validation::getDirection(string ini, string fin)
{
    vector<int> vals;
    int deltax, deltay;
    deltax = int(fin[0]-ini[0]);
    deltay = int(fin[1]-ini[1]);
    if(deltax == -1)
    {
        if(deltay == 1) return "NE";
        if(deltay == 0) return "NW";
    }
    if(deltax == 0)
    {
        if(deltay == 1) return "EE";
        if(deltay == -1) return "WW";
    }
    if(deltax == 1)
    {
        if(deltay == 0) return "SE";
        if(deltay == -1) return "SW";
    }
    return "";
}

string validation::getNext(string pos, string dir)
{
    vector<int> deltas = convertDir(dir);
    string ret = "  ";
    ret[0] = pos[0] + deltas[0];
    ret[1] = pos[1] + deltas[1];
    return ret;
}

bool validation::isValid(string mov)
{
    if(!isStringValid(mov))  return false;

    string mar1, mar2;
    mar1 = mov.substr(0,2);
    mar2 = mov.substr(3,2);
    
    string dir = getDirection(mar1, mar2);

    if(dir == ""){ return false;}
    
    if(!isPlayers(mar1, myColor) || !isPlayers(mar2,myColor)) return false;
    
    string next = getNext(mar2, dir);
   
    if(isPlayers(next,myColor)) return false;

    if(isPlayers(next, !myColor))
    {
        string nextnext = getNext(next, dir);
        if(isPlayers(nextnext,myColor) || isPlayers(nextnext, !myColor))
            return false;
    }

    if(cornerPush(next, dir)) return false;

    if(!inBoard(next)) return false;

    return true;
}

vector<int> validation::convertDir(string Dir)
{
    if(Dir == "NE") return {-1,1};
    if(Dir == "EE") return {0,1};
    if(Dir == "SE") return {1,0};
    if(Dir == "SW") return {1,-1};
    if(Dir == "WW") return {0,-1};
    if(Dir == "NW") return {-1,0};
}

vector<string> validation::getNeighbours(string pos, int val)
{
    vector<string> retSt;
    for(int i = 0; i<6;i++)
    {
        string mar = getNext(pos,directions[i]);
        if(isPlayers(mar,val)) retSt.push_back(mar);
    }
    return retSt;
}

vector<string> validation::getMoves()
{
    vector<string> retMoves;
    for(int i = 0;i<11;i++)
        if(players[myColor][i] != "EE")
        {
            vector<string> neighs = getNeighbours(players[myColor][i],myColor);
            for(int j = 0; j<neighs.size(); j++)
            {
                string move = players[myColor][i];  
                move = move + " " + neighs[j];       
                if(isValid(move))
                    retMoves.push_back(move);
            }
        }
    return retMoves;
}

void validation::move(string mov)
{
    string mar1 = mov.substr(0,2);
    string mar2 = mov.substr(3,2);

    string dir = getDirection(mar1, mar2);
    string opp = getNext(mar2, dir);
    bool isPush = false;

    if(isPlayers(opp, !myColor)) isPush = true;
    string oppfin = getNext(opp, dir);
    bool outPush = true;

    if(inBoard(oppfin)) outPush = false;
    else outPush = isPush;
    if(isPush)
        for(int i=0; i<11; i++)
            if(players[!myColor][i] == opp)
                if(!outPush)
                    players[!myColor][i] = oppfin;
                else
                    players[!myColor][i] = "EE";
                
    if(outPush)
        marbles[!myColor]--;

    for(int i=0; i<11; i++)
        if(players[myColor][i] == mar1)
            players[myColor][i] = opp;

}

int validation::isWin()
{
    if(marbles[0]==7) return 1;
    else if(marbles[1]==7) return 0;
    else return -1;
    
}

//-------------------end of validation class functions-------------------












//----------------------bot class functions-------------------------------
int bot::eval()
{
    //botPlayer
    /*
        if botplayer wins then +infinity
        if botplayer loses then -infinity
        if botplayer pushes x marbles then +x*1000 to value
        if x of botplayer are pushed then -x*1000 to value
        https://issel.ee.auth.gr/wp-content/uploads/2016/04/Exploring-Optimization-Strategies-in-Board-Game-Abalone-for-Alpha-Beta-Search.pdf
    */
	//If game is Over :
    if(comp.marbles[botPlayer] == 7)
        return -infinity;
    if(comp.marbles[!botPlayer] == 7)
        return infinity;

    int value = 0;
    int pushVal = 0;
    int clusterVal = 0;
    int centreDistVal = 0;
    int onEdgeVal = 0;

    //----------Marble out of board-----------
    //When some marbles are pushed botPlayers or !botPlayers
    pushVal += (1500*(Marbles[!botPlayer] - comp.marbles[!botPlayer]));
    pushVal += (1500*(comp.marbles[botPlayer] - Marbles[botPlayer]));



    //-----------Cluster Values---------------

    //Finding cluster Values for botPlayer
    for(int i = 0;i<11;i++)
    {
    	if(comp.players[botPlayer][i] != "EE")
    	{
    		int clusVal;
    		vector<string> botNeighs = comp.getNeighbours(comp.players[botPlayer][i],botPlayer);
    		clusVal = clusterValue(botNeighs);
    		clusterVal += clusVal;
    		centreDistVal += centreDist(comp.players[botPlayer][i]);
    	}

    }

    //Finding cluster Values for !botPlayer
    for(int i = 0;i<11;i++)
    {
      	if(comp.players[!botPlayer][i] != "EE")
       	{
      		int clusVal;
       		vector<string> oppNeighs = comp.getNeighbours(comp.players[!botPlayer][i],!botPlayer);
       		clusVal = clusterValue(oppNeighs);
       		clusterVal -= clusVal;
       		centreDistVal -= centreDist(comp.players[!botPlayer][i]);
       	}
    }

    //--------------------On Edge Value---------------

	onEdgeVal += edgeValues(botPlayer);
	onEdgeVal -= edgeValues(!botPlayer);

    //return vals
    value += pushVal;
    value += clusterVal;
    value += centreDistVal;
    value += onEdgeVal;

    return value;
    
}

int bot::clusterValue(vector<string> neighs)
{
    if (neighs.size() == 0)
        return -300;
    else
    {
        int val = 10;
        val *= neighs.size();
        return val;
    }
}

int bot::centreDist(string pos)
{
    string mid = "D3";
    int mod = 0;
    if(pos[0] == mid[0])
        mod = abs(pos[1] - mid[1]);
    else if(pos[1] == mid[1])
        mod = abs(mid[0] - pos[0]);
    else if(mid[0] - pos[0] == pos[1] - mid[1])
        mod = abs(mid[1] - pos[1]) + 1;
    else if(pos[0] == 'C')
    {
        if(pos[1] == '2' || pos[1] == '7')
            mod = 3;
        else
            mod = 2;        
    }
    else if(pos[0] == 'E')
    {
        if(pos[1] == '1' || pos[1] == '6')
            mod = 3;
        else
            mod = 2;
    }
    else if(pos[0] == 'B')
    {
        if(pos[1] == '3' || pos[1] == '7')
            mod = 3;
        else
            mod = 2;
    }
    else if(pos[0] == 'F')
    {
        if(pos[1] == '1' || pos[1] == '5')
            mod = 3;
        else
            mod = 2;        
    }
    else
        mod = 4;
    
    return (4-mod)*100;
}

int bot::edgeValues(bool pl)
{
	int risky = 0;
	for(int i = 0; i<11; i++)
	{
		string pos = comp.players[pl][i];
		if(pos != "EE")
		{
			bool inB = true;
			for(int di = 0; di<6 && inB;di++)
			{
				string near1 = comp.getNext(pos, directions[di]);
				inB = inB && comp.inBoard(near1);
			}
			
			if(!inB)
			{
				for(int di = 0; di<6 && inB;di++)
				{
					string dir = directions[di];
					string oppD = directions[5-di];
					string near1 = comp.getNext(pos, dir);
					inB = comp.inBoard(near1);
					if(inB)
					{
						if(comp.isPlayers(near1,!pl))
						{
							string near2 = comp.getNext(near1,dir);
							if(comp.isPlayers(near2, !pl))
							{	
								near1 = comp.getNext(pos,oppD);
								if(!comp.inBoard(near1))
									risky+=2;
								else if(!comp.isPlayers(near1,pl) && !comp.isPlayers(near1,!pl))
									risky+=1;
							}
						}
					}
				}
			}
		}
	}
	return -risky*200;
}

string bot::findBestMove()
{
    vector<string> allMoves = comp.getMoves();
    //comp.show();
    int bestVal = -infinity;
    vector<string> bestMoves;
    for(int i = 0; i<allMoves.size();i++)
    {
        string move = allMoves[i];
        validation temp = comp;

        comp.move(move);
        
        int moveVal = miniMax(false, 0, -infinity, infinity);
        //cout<<move<<" "<<moveVal<<endl;
        if(moveVal > bestVal)
        {
            bestMoves.clear();
            bestMoves.push_back(move);
            bestVal = moveVal;
        }
        else if(moveVal == bestVal)
        {
            srand(time(0));
            int k = rand() % 2;
            bestMoves.push_back(move);
            string in = bestMoves[k];
            bestMoves.clear();
            bestMoves.push_back(in);       
        }
        comp = temp;
    }
    return bestMoves[0];
}

int bot::miniMax(bool isMax, int h, int alpha, int beta)
{
    if(h==maxD)
        return eval();
    if(comp.isWin() != -1)
        return eval();
    //cout<<isMax;
    if(isMax)
    {
        int best = -infinity;
        vector<string> allMoves = comp.getMoves();
        for(int i = 0; i<allMoves.size();i++)
        {
            string move = allMoves[i];
            validation temp = comp;

            comp.move(move);
            int val = miniMax(false, h+1, alpha, beta);
            best = max(best, val);
            alpha = max(alpha, best); 

            if (beta <= alpha) 
                break; 
            comp=temp;
        }
        return best;
    } 
    else
    {
        int best = infinity;
        vector<string> allMoves = comp.getMoves();
        for(int i = 0; i<allMoves.size();i++)
        {
            string move = allMoves[i];
            validation temp = comp;

            comp.move(move);
            int val = miniMax(true, h+1, alpha, beta);
            best = min(best, val);
            beta = min(beta, best); 
  
            if (beta <= alpha) 
                break; 

            comp=temp;
        }
        return best;
    }
    
}
//---------------end of bot class functions-----------------






//----------------General functions-------------------

vector<int> getCoordinate(string pos)
{
    int row = pos[0] - 'A';
    int col = 0;
    if (row<=3)
        col = row + pos[1] - '7' + 3;
    else
        col = pos[1] - '1';
    return {row, col};
}

vector<vector<int>> fromListToBoard()
{
    vector<vector<int>> board = {
        {-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1}
    };
    for(int j = 0; j < 2; j++)
        for(int i = 0;i < 11; i++)
        {
            vector<int> cood = getCoordinate(Players[j][i]);
            board[cood[0]][cood[1]] = j;
        }
    return board;
}

int isWin()
{
    if(Marbles[0]==7) return 1;
    else if(Marbles[1]==7) return 0;
    else return -1;
    
}

void display()
{
    vector<vector<int>> board = fromListToBoard();
    char row = 'A';
	int dia = 7;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2 - i; j >= 0; j--)
		{
			cout << " ";
		}
		cout << row << " ";
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == -1) cout << "+ ";
			else if (board[i][j] == 0) cout << "b ";
			else cout << "r ";
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
		cout << row << " ";
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == -1) cout << "+ ";
			else if (board[i][j] == 0) cout << "b ";
			else cout << "r ";
		}
		cout << dia << endl;
		row++;
		dia--;
	}
	for (int i = 0; i < 6; i++) cout << " ";
	for (int i = 0; i < 4; i++, dia--) cout << 5 - dia << " ";
	cout << endl;
}

void actualMove(validation v, string mov, bool turn)
{
    string mar1 = mov.substr(0,2);
    string mar2 = mov.substr(3,2);

    string dir = v.getDirection(mar1, mar2);
    string opp = v.getNext(mar2, dir);
    bool isPush = false;

    if(v.isPlayers(opp, !turn)) isPush = true;
    string oppfin = v.getNext(opp, dir);
    bool outPush = isPush;

    if(v.inBoard(oppfin)) outPush = false;

    if(isPush)
        for(int i=0; i<11; i++)
            if(Players[!turn][i] == opp)
                if(!outPush)
                    Players[!turn][i] = oppfin;
                else
                    Players[!turn][i] = "EE";
                
    if(outPush && isPush)
        Marbles[!turn]--;

    for(int i=0; i<11; i++)
        if(Players[turn][i] == mar1)
            Players[turn][i] = opp;

}

//submission on website

void play(bool botP)
{
    string s;
    bool turn = false;
    validation v(turn);
    do
    {
    	validation v(turn);
        
        //display();
        if(!turn)
        {
            bot b(turn, v);
            //cout<<"Blue's Turn : "; //getline(cin,s);
            auto start = high_resolution_clock::now();
            if(botP == turn)
            {
                s = b.findBestMove(); 
                cout<<s<<endl;
            } 
            else
                getline(cin,s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            float time = duration.count()/1000000.0;
            //cout<<s<<" ----Time : "<<time<<"s----"<<endl;
        }
        else
        {
            bot b(turn, v);
            //cout<<"Red's Turn : "; //getline(cin,s);
            auto start = high_resolution_clock::now();
            if(botP == turn)
            {
                s = b.findBestMove();  
                cout<<s<<endl;
            }
            else
                getline(cin,s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            float time = duration.count()/1000000.0;
            //cout<<s<<" ----Time : "<<time<<"s----"<<endl;
        }
        actualMove(v,s,turn);
        v.move(s);
        turn = !turn;
    }while(isWin()==-1);
}

//bot vs bot
/*
void play(bool botP)
{
    string s;
    bool turn = false;
    validation v(turn);
    do
    {
    	validation v(turn);
        
        display();
        if(!turn)
        {
            bot b(turn, v);
            cout<<"Blue's Turn : "; //getline(cin,s);
            auto start = high_resolution_clock::now();
            //if(botP == turn)
            {
                s = b.findBestMove(); 
                cout<<s<<endl;
            } 
            //else
              //  getline(cin,s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            float time = duration.count()/1000000.0;
            cout<<s<<" ----Time : "<<time<<"s----"<<endl;
        }
        else
        {
            bot b(turn, v);
            cout<<"Red's Turn : "; //getline(cin,s);
            auto start = high_resolution_clock::now();
            //if(botP == turn)
            {
                s = b.findBestMove();  
                cout<<s<<endl;
            }
            //else
              //  getline(cin,s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            float time = duration.count()/1000000.0;
            cout<<s<<" ----Time : "<<time<<"s----"<<endl;
        }
        actualMove(v,s,turn);
        v.move(s);
        turn = !turn;
    }while(isWin()==-1);
    
    if(isWin()==1)
        cout<<"Red wins\n";
    else
        cout<<"Blue wins\n";   
}*/

//bot vs player
/*
void play(bool botP)
{
    string s;
    bool turn = false;
    validation v(turn);
    do
    {
    	validation v(turn);
        
        display();
        if(!turn)
        {
            bot b(turn, v);
            cout<<"Blue's Turn : "; //getline(cin,s);
            auto start = high_resolution_clock::now();
            if(botP == turn)
            {
                s = b.findBestMove(); 
                cout<<s<<endl;
            } 
            else
                getline(cin,s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            float time = duration.count()/1000000.0;
            cout<<"/n ----Time : "<<time<<"s----"<<endl;
        }
        else
        {
            bot b(turn, v);
            cout<<"Red's Turn : "; //getline(cin,s);
            auto start = high_resolution_clock::now();
            if(botP == turn)
            {
                s = b.findBestMove();  
                cout<<s<<endl;
            }
            else
                getline(cin,s);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            float time = duration.count()/1000000.0;
            cout<<"/n ----Time : "<<time<<"s----"<<endl;
        }
        actualMove(v,s,turn);
        v.move(s);
        turn = !turn;
    }while(isWin()==-1);
    
    if(isWin()==1)
        cout<<"Red wins\n";
    else
        cout<<"Blue wins\n";  
}*/


int main()
{
    int botP;
    cin>>botP;
    cin.ignore(1);
    if(botP == 1)
        play(true);
    else
        play(false);
    return 0;
}

