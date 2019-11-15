//Krieg bot (not pruned)(no sliding moves limit)
#include <iostream>
#include <string>
using namespace std;

class game
{
public:
    int r,c;
    game(int a=0, int b=0)
    {
        r=a;
        c=b;
    }
    game(const game &x)
    {
        r=x.r;
        c=x.c;
    }
};

char board[5][5];/*=
                  {        //use this for testing otherwise initBoard is called in main

                  {'B', '_', 'B', 'w', 'B'},
                  {'w', '_', 'W', 'B', 'b'},
                  {'w', 'W', '_', 'w', 'b'},
                  {'_', '_', '_', '_', '_'},
                  {'_', 'W', 'b', 'W', 'W'},

                  };*/

//GLOBAL MEMBERS
const int FBMdepth=5;
int Wm = 0, Wp = 0, Bm = 0, Bp = 0;
bool whosemove=1;
game pr2;
bool whoAmI;
game arr[10];

//FUNCTION DECLARATIONS
game findBestMove(int, int);
int mValidation(bool, game, game);
void makemove (bool, game, game, int, int);
void Elimination (bool, game, game, int);
void undoMove(bool, game, game, int);
int minimax(int, bool, game, game, int);
int evaluate(bool, game, game,int);
void displayboard ();
void makeOppMove(int, game, game);

game findBestMove(int x, int depth)
{
    char X,Y;
    if (x == 0)
    {
        X = 'W';            //X initialized to mantri
        Y = 'w';            //Y initialized to pawn
    }
    else
    {
        X = 'B';
        Y = 'b';
    }

    int i=0,j=0,k=0,l=0;
    game gsinput,gminput;
    int bestVal=-1000000000;
    game bestMove;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if (board[i][j] == '_')    //if place on board is blank then continue
            {
                continue;
            }
            else if (board[i][j] == X || board[i][j] == Y)
            {
                gsinput.r = i;
                gsinput.c = j;
                k=-2; l=0;
                int z=0;
                while(l<=2 && l>=0 && k<=2) //for moves excluding some non-eliminating moves of mantri
                {
                    int moveVal=0;
                    if(x==1)
                    {gminput.r = i + l;}
                    else
                    {gminput.r = i - l;}
                    gminput.c = j + k;
                    if (gminput.c < 5 && gminput.c >= 0 && gminput.r < 5  && gminput.r >= 0)
                    {
                        int goFlag = mValidation (x, gsinput, gminput);
                        if(goFlag==1 || goFlag==2 || goFlag==3)
                        {
                            //displayboard();//////////////////////////////
                            makemove(x, gsinput, gminput, depth, goFlag); //making the move
                            //displayboard();/////////////////////////////
                            moveVal += minimax(depth, x, gsinput, gminput, goFlag);    //checking the value of the move
                            undoMove(x, gsinput, gminput, goFlag); //undo the non-eliminating move

                            if(moveVal > bestVal)   //updating the bestMove and bestVal
                            {
                                bestVal=moveVal;
                                bestMove.r=gminput.r;
                                bestMove.c=gminput.c;
                                if(depth==FBMdepth)    //pr2.r=gsinput.r; pr2.c=gsinput.c;//change pr2 only for first depth iteration
                                {
                                    pr2.r=gsinput.r; pr2.c=gsinput.c;
                                }
                            }
                        }
                    }
                    if(l==2) z=1;
                    if(z==0) l++;
                    else l--;
                    k++;
                }
                if(board[i][j] == X)    //for some normal moves by mantri
                {
                    gsinput.r = i;
                    gsinput.c = j;
                    k=-1; l=0;
                    int z=0;
                    while(l<=1 && l>=0 && k<=1)
                    {
                        int moveVal=0;
                        if(x==1)
                        {gminput.r = i + l;}
                        else
                        {gminput.r = i - l;}
                        gminput.c = j + k;
                        if (gminput.c < 5 && gminput.c >= 0 && gminput.r < 5 && gminput.r >= 0)
                        {
                            int goFlag = mValidation (x, gsinput, gminput);
                            if (goFlag == 1)    //just the case of normal move here
                            {
                                //displayboard();////////////////////////////////////
                                makemove(x, gsinput, gminput, depth, goFlag); //making the move
                                //displayboard();////////////////////////////////////
                                moveVal += minimax(depth, x, gsinput, gminput, goFlag);    //checking the value of the move
                                undoMove(x, gsinput, gminput, goFlag); //undo the non-eliminating move
                                if(moveVal > bestVal)
                                {
                                    bestVal=moveVal;
                                    bestMove.r=gminput.r;
                                    bestMove.c=gminput.c;
                                    if(depth==FBMdepth)    //pr2.r=gsinput.r; pr2.c=gsinput.c;//change pr2 only for first depth iteration
                                    {
                                        pr2.r=gsinput.r; pr2.c=gsinput.c;
                                    }
                                }
                            }
                        }
                        if(l==1) z=1;
                        if(z==0) l++;
                        else l--;
                        k++;
                    }
                }
            }
        }
    }
    return bestMove;
}

int mValidation(bool x, game sinput, game minput)    //returns 0->Invalid, 1->Normal, 2->Mantri elimination, 3->Soldier elimination
{
    char X,Y;
    if (x == 0)
    {
        X = 'W';            //X initialized to mantri
        Y = 'w';            //Y initialized to pawn
    }
    else
    {
        X = 'B';
        Y = 'b';
    }

    int d1, d2;
    d1 = minput.r - sinput.r;    // difference between initial and final row position
    d2 = minput.c - sinput.c;    //difference between initial and final cols position

    if(sinput.r<0 || sinput.r>4 || sinput.c<0 || sinput.c>4 ||minput.r<0 || minput.r>4 || minput.c<0 || minput.c>4
            || board[minput.r][minput.c]!='_' || (board[sinput.r][sinput.c]!=X && board[sinput.r][sinput.c]!=Y))
    {
        return 0;
    }
    else
    {
        if(board[sinput.r][sinput.c]==X)    //moveset for mantri
        {
            if((d1 == (2 * x - 1) || d1 == 0) && (d2 == (2 * x - 1) || d2 == -(2 * x - 1) || d2 == 0))    //normal move
            {
                return 1;
            }
            else if(((d1 == 2 * (2 * x - 1) && d2 == 0) || (d1 == 0 && (d2 == 2 * (2 * x - 1) || d2 == -2 * (2 * x - 1))))
            		&& (sinput.r!=0 && sinput.r!=4))
            {
                char t1;

                if(d1 == 2 * (2 * x - 1) && d2 == 0)    //vertical elimination
                {
                    t1 = board[sinput.r+2*x-1][sinput.c]; //target piece
                }
                else if(d1 == 0 && (d2 == 2 * (2 * x - 1) || d2 == -2 * (2 * x - 1)))    //horizontal elimination
                {
                    t1 = board[sinput.r][(sinput.c+minput.c)/2]; //target piece
                }

                if(x==1)
                {
                    if(t1=='W') return 2;
                    else if(t1 == 'w') return 3;
                }
                else
                {
                    if(t1=='B') return 2;
                    else if(t1 == 'b') return 3;
                }
            }
        }
        else if(board[sinput.r][sinput.c]==Y)    //moveset for pawn
        {
            if ((d1 == (2 * x - 1) && d2 == (2 * x - 1)) || (d1 == (2 * x - 1) && d2 == -(2 * x - 1)))    //normal move
            {
                return 1;
            }
            else if(((d1 == 2 * (2 * x - 1) && d2 == 0) || (d1 == 0 && (d2 == 2 * (2 * x - 1) || d2 == -2 * (2 * x - 1))))
            		&& (sinput.r!=0 && sinput.r!=4))
            {
                char t1;

                if(d1 == 2 * (2 * x - 1) && d2 == 0)    //vertical elimination
                {
                    t1 = board[sinput.r+2*x-1][sinput.c]; //target piece
                }
                else if(d1 == 0 && (d2 == 2 * (2 * x - 1) || d2 == -2 * (2 * x - 1)))    //horizontal elimination
                {
                    t1 = board[sinput.r][(sinput.c+minput.c)/2]; //target piece
                }

                if(x==1)
                {
                    if(t1=='W') return 2;
                    else if(t1 == 'w') return 3;
                }
                else
                {
                    if(t1=='B') return 2;
                    else if(t1 == 'b') return 3;
                }
            }
        }
    }
    return 0;    //if none of the cases are satisfied
}
void makemove (bool x, game sinput, game minput, int depth, int goFlag)
{
    if (goFlag == 1)
    {
        board[minput.r][minput.c] = board[sinput.r][sinput.c];
        board[sinput.r][sinput.c] = '_';
    }
    else if (goFlag == 2 || goFlag==3)
    {
        board[minput.r][minput.c] = board[sinput.r][sinput.c];
        board[sinput.r][sinput.c] = '_';
        Elimination (x, sinput, minput, goFlag);
    }
}
void Elimination (bool x, game sinput, game minput, int goFlag)
{
    x=!x;
    if (x == 0)
    {
        if(goFlag == 2)
        {
            Wm++;            //increment count for dead mantri
        }
        else if(goFlag == 3)
        {
            Wp++;            //increment count for dead pawn
        }
    }
    else
    {
        if(goFlag == 2)
        {
            Bm++;            //increment count for dead mantri
        }
        else if(goFlag == 3)
        {
            Bp++;            //increment count for dead pawn
        }
    }

    board[(sinput.r + minput.r) / 2][(sinput.c + minput.c) / 2] = '_';
}
void undoMove(bool x, game sinput, game minput, int goFlag)
{
    char X,Y;
    board[sinput.r][sinput.c] = board[minput.r][minput.c];
    board[minput.r][minput.c] = '_';

    if(goFlag==2 || goFlag==3)   //for elimination and injury
    {
        x=!x;
        if (x == 0)
        {
            X = 'W';            //X initialized to mantri
            Y = 'w';            //Y initialized to pawn
            if(goFlag==2)
            {
                Wm--;            //decrement count for dead mantri
            }
            else if(goFlag==3)
            {
                Wp--;            //decrement count for dead pawn
            }
        }
        else if (x == 1)
        {
            X = 'B';
            Y = 'b';
            if(goFlag==2)
            {
                Bm--;            //decrement count for dead mantri
            }
            else if(goFlag==3)
            {
                Bp--;            //decrement count for dead pawn
            }
        }

        if(goFlag==2)    board[(sinput.r + minput.r) / 2][(sinput.c + minput.c) / 2] = X;   //replacing the eliminated piece
        else if(goFlag==3)    board[(sinput.r + minput.r) / 2][(sinput.c + minput.c) / 2] = Y;
    }
}

int minimax(int depth, bool x, game initial, game final, int goFlag)
{
    int score = evaluate(x, initial, final, goFlag);
    if(depth<=0) return score;

    int bestVal=-1000000000;
    x=!x;
    char X,Y;
    if (x == 0)
    {
        X = 'W';            //X initialized to mantri
        Y = 'w';            //Y initialized to pawn
    }
    else
    {
        X = 'B';
        Y = 'b';
    }
    int i=0,j=0,k=0,l=0;
    game gsinput,gminput;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if (board[i][j] == '_')    //if place on board is blank then continue
            {
                continue;
            }
            else if (board[i][j] == X || board[i][j] == Y)
            {
                gsinput.r = i;
                gsinput.c = j;
                k=-2; l=0;
                int z=0;
                while(l<=2 && l>=0 && k<=2) //for moves excluding some non-eliminating moves of mantri
                {
                    int moveVal=0;
                    if(x==1)
                    {gminput.r = i + l;}
                    else
                    {gminput.r = i - l;}
                    gminput.c = j + k;
                    if (gminput.c < 5 && gminput.c >= 0 && gminput.r < 5  && gminput.r >= 0)
                    {
                        int goFlag = mValidation (x, gsinput, gminput);
                        if(goFlag==1 || goFlag==2 || goFlag==3)
                        {
                            //displayboard();////////////////////////////////////
                            makemove(x, gsinput, gminput, depth, goFlag); //making the move
                            //displayboard();////////////////////////////////////
                            moveVal += -minimax(depth-1, x, gsinput, gminput, goFlag);    //checking the value of the move
                            undoMove(x, gsinput, gminput, goFlag); //undo the non-eliminating move

                            if(moveVal > bestVal)   //updating the bestMove and bestVal
                            {
                                bestVal=moveVal;
                            }
                            /*if(moveVal>alpha)
                            {
                            	alpha=moveVal;
                            }
                            if(alpha>=beta)	return score+alpha;*/
                        }
                    }
                    if(l==2) z=1;
                    if(z==0) l++;
                    else l--;
                    k++;
                }
                if(board[i][j] == X)    //for some normal moves by mantri
                {
                    gsinput.r = i;
                    gsinput.c = j;
                    k=-1; l=0;
                    int z=0;
                    while(l<=1 && l>=0 && k<=1)
                    {
                        int moveVal=0;
                        if(x==1)
                        {gminput.r = i + l;}
                        else
                        {gminput.r = i - l;}
                        gminput.c = j + k;
                        if (gminput.c < 5 && gminput.c >= 0 && gminput.r < 5 && gminput.r >= 0)
                        {
                            int goFlag = mValidation (x, gsinput, gminput);
                            if (goFlag == 1)    //just the case of normal move here
                            {
                                //displayboard();////////////////////////////////////
                                makemove(x, gsinput, gminput, depth, goFlag); //making the move
                                //displayboard();////////////////////////////////////
                                moveVal += -minimax(depth-1, x, gsinput, gminput, goFlag);    //checking the value of the move
                                undoMove(x, gsinput, gminput, goFlag); //undo the non-eliminating move
                                if(moveVal > bestVal)
                                {
                                    bestVal=moveVal;
                                }
                                /*if(moveVal>alpha)
                                {
                                	alpha=moveVal;
                                }
                                if(alpha>=beta)	return score+alpha;*/
                            }
                        }
                        if(l==1) z=1;
                        if(z==0) l++;
                        else l--;
                        k++;
                    }
                }
            }
        }
    }
    score += bestVal;
    return score;
}

int gameover(bool x)
{
	if(Bm==5 || Wm==5) return 1;	//All mantri dead

	for (int i = 0; i < 5; i++)		//Mantri reached home
	{
		if (board[0][i] == 'W')
		{
			return 1;
		}
		if (board[4][i] == 'B')
		{
			return 1;
		}
	}
	//Considering the case of no moves available
    char X,Y;
    if (x == 0)
    {
        X = 'W';            //X initialized to mantri
        Y = 'w';            //Y initialized to pawn
    }
    else
    {
        X = 'B';
        Y = 'b';
    }

    int i=0,j=0,k=0,l=0;
    game gsinput,gminput;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if (board[i][j] == '_')    //if place on board is blank then continue
            {
                continue;
            }
            else if(board[i][j]==X || board[i][j]==Y)
            {
            	/*int x;
            	if(board[i][j] == 'B' || board[i][j] == 'b') x=1;
            	else x=0;*/
                gsinput.r = i;
                gsinput.c = j;
                k=-2; l=0;
                int z=0;
                while(l<=2 && l>=0 && k<=2) //for moves excluding some non-eliminating moves of mantri
                {
                    if(x==1)
                    {gminput.r = i + l;}
                    else
                    {gminput.r = i - l;}
                    gminput.c = j + k;
                    if (gminput.c < 5 && gminput.c >= 0 && gminput.r < 5  && gminput.r >= 0)
                    {
                        int goFlag = mValidation (x, gsinput, gminput);
                        if(goFlag==1 || goFlag==2 || goFlag==3)
                        {
                        	return 0;
                        }
                    }
                    if(l==2) z=1;
                    if(z==0) l++;
                    else l--;
                    k++;
                }
                if(board[i][j] == X)    //for some normal moves by mantri
				{
					gsinput.r = i;
					gsinput.c = j;
					k=-1; l=0;
					int z=0;
					while(l<=1 && l>=0 && k<=1)
					{
						if(x==1)
						{gminput.r = i + l;}
						else
						{gminput.r = i - l;}
						gminput.c = j + k;
						if (gminput.c < 5 && gminput.c >= 0 && gminput.r < 5 && gminput.r >= 0)
						{
							int goFlag = mValidation (x, gsinput, gminput);
							if(goFlag == 1)    //just the case of normal move here
							{
								return 0;
							}
						}
                        if(l==1) z=1;
                        if(z==0) l++;
                        else l--;
                        k++;
					}
				}
            }
        }
    }

    return 2;	//Draw condition
}
int evaluate(bool x, game sinput, game minput, int goFlag)
{
	int veryBigValue;
	if(gameover(!x))
		veryBigValue=10000000;
	else veryBigValue=0;

    char X,Y;
    if (x == 0)
    {
        X = 'W';            //X initialized to mantri
        Y = 'w';            //Y initialized to pawn
    }
    else
    {
        X = 'B';
        Y = 'b';
    }

    int p,q;
    if(x==1)
    {
        p=0;
        q=100000;
    }
    else
    {
        p=100000;
        q=0;
    }

    int MPvalueTable[5][5]={

        {p,p,p,p,p},
        {1500,1000,1500,1000,1500},
        {500,250,500,250,500},
        {200,300,200,300,200},
        {q,q,q,q,q},


    };

    int SPvalueTable[5][5]={

        {-5,5,-5,5,-5},
        {0,20,0,20,0},
        {100,50,75,50,100},
        {30,50,30,50,30},
        {15,20,15,20,15},

    };

    int MSPvalue;
    int Mvalue;
    int NoM;
    int ElimVal;


    if(board[minput.r][minput.c]==X)
    {
        if(x==1)
            MSPvalue=MPvalueTable[minput.r][minput.c];
        else if(x==0)    MSPvalue=MPvalueTable[minput.r][minput.c];

        if(minput.r==2)
        {
            Mvalue=5000;
        }
        else if(minput.r==2*x+1)
        {
            Mvalue=10000;
        }
        else if(minput.r==3-2*x)
        {
            Mvalue=2000;
        }
    }
    else
    {
        if(x==1)
            MSPvalue=SPvalueTable[minput.r][minput.c];
        else if(x==0)    MSPvalue=SPvalueTable[minput.r][minput.c];
    }

    if(x==1)
    {
        if(Bm==1)    NoM=10000;
        else if(Bm==2)    NoM=5000;
        else if(Bm==3)    NoM=1000;
        else if(Bm==4)    NoM=750;
        else if(Bm==5)    NoM=500;

    }
    else
    {
        if(Wm==1)    NoM=10000;
        else if(Wm==2)NoM=5000;
        else if(Wm==3)    NoM=1000;
        else if(Wm==4)    NoM=750;
        else if(Wm==5)    NoM=500;
    }

    if(goFlag==2)
    {
        if(minput.r==2)
        {
            ElimVal=50000;
        }
        else if(minput.r==3-2*x)    //careful, looking for opponents Mantri's row
        {
            ElimVal=100000;
        }
        else if(minput.r==2*x+1)
        {
            ElimVal=20000;
        }
    }

    return veryBigValue+MSPvalue+Mvalue+NoM+ElimVal;
}
void displayboard ()
{
    int i, j;
    cout << "    0 1 2 3 4\n";
    cout << "  -----------\n";
    for (i = 0; i < 5; i++)
    {
        cout << i << "|  ";
        for (j = 0; j < 5; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout<<endl;
    }
}
void initBoard ()
{
    for (int i = 0; i < 5; i++)    // Initialize the Board
    {
        board[0][i] = 'B';
        board[1][i] = 'b';
        board[2][i] = '_';
        board[3][i] = 'w';
        board[4][i] = 'W';
    }
}

void makeOppMove(int x, game sinput, game minput)
{
    board[minput.r][minput.c] = board[sinput.r][sinput.c];
    board[sinput.r][sinput.c] = '_';

    int d1 = minput.r - sinput.r;    // difference between initial and final row position
    int d2 = minput.c - sinput.c;    //difference between initial and final cols position

    if(d1>1 || d1<-1 || d2>1 || d2<-1)
    {
        char t1 = board[(sinput.r + minput.r) / 2][(sinput.c + minput.c) / 2];
        if(x==0)
        {
            if(t1=='W') Wm++;
            else if(t1 == 'w') Wp++;
        }
        else
        {
            if(t1=='B') Bm++;
            else if(t1 == 'b') Bp++;
        }

        board[(sinput.r + minput.r) / 2][(sinput.c + minput.c) / 2] = '_';
    }
}

int main()
{
    initBoard();

    bool turn;
    string input, output;
    //cout<<"Enter 1/0:";
    cin>>turn;
    cin.ignore();
    whoAmI=turn;
    while(1)
    {
        if(turn!=1)
        {
            //cout<<"Enter input:";
            getline(cin, input);
            game s(input[0]-48, input[2]-48), m(input[4]-48, input[6]-48);
            makeOppMove(whoAmI, s, m);
            input="\0";
            /*displayboard();
            if(gameover(!whosemove))
            {
                cout<<"You win!";    return 0;
            }*/
        }
        turn=0;    //after first iteration, (turn!=1) is always true
        //i.e. turn is always 0
        game bestMove=findBestMove(whoAmI, FBMdepth);
        makeOppMove(!whoAmI,pr2, bestMove);
        output += pr2.r+48;
        output += " ";
        output += pr2.c+48;
        output += " ";
        output += bestMove.r+48;
        output += " ";
        output += bestMove.c+48;
        //your logic to make the next move
        //output your move string
        cout<<output<<endl;
        output="\0";
        /*displayboard();
        if(gameover(!whosemove))
        {
            cout<<"Computer wins!";    return 0;
        }*/
    }
}


