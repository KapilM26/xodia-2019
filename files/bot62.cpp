//  white = 0=blue   ; black = 1=red unoccupied = -1
#include<iostream>
#include<string.h>
#include<cmath>

using namespace std;

class Board
{

public:

Board();
void CopyBoard(const Board );
char board[9][9];
bool MoveValidation(std::string Move);
void AllValidMoves(string (&)[25]);
void makeMove(string);
bool MyBotColour;
string botMove();
int Move_Weight(string);
void Mini_Max_0(int (&)[25],string (&)[25] );
int Mini_Max_0_1(int (&)[25],string (&)[25]);
int Mini_Max_1(Board ,string );
int Mini_Max_2(Board ,string )  ;
void display();
};

Board b;

int main()
{
	string move;
    string opponent_move;
    	
    
	cin >> b.MyBotColour;
    cin.ignore();
	fflush(stdin);
		
		if( b.MyBotColour==1  )
	   	goto X1;

	while (1)
    {
       
	move = b.botMove(); // calculating the bot's move
            
	cout<<move;          //printing the bot's move
	
	b.makeMove(move); // making the move on the actual board

X1:// b.display();
	
	getline(cin,opponent_move);
	
	
	fflush(stdin);

    b.makeMove(opponent_move);

    }

}

string Board::botMove()
{   
     
	string validMoves[25];
	int Move_value[25];
	int Z,max=0;

	AllValidMoves(validMoves);
	
	Mini_Max_0(Move_value,validMoves);
		
	for (Z=1;validMoves[Z]!="fuh";Z++)
	{
		if(Move_value[max]<Move_value[Z])
		max=Z;
	}
	
	return validMoves[max];
	
}

void Board:: Mini_Max_0(int (&Move_value)[25],string (&validmoves)[25])
{
	int y;
    
	for(y=0;y<25;y++)
    {
	if(validmoves[y]=="fuh")
    break;
	}
	
	Board b1[y];
	for(int u=0;u<y;u++)
	{
		Move_value[u]=this->Mini_Max_1(b1[u],validmoves[u]);
	}

}

int Board::Mini_Max_1(Board x,string ryan)
{
	
 	x.CopyBoard(b);
 	x.makeMove(ryan);
 
 	string validMoves[25];
	int Move_value[25];
	int Z,max=0;
	int y;
		
	x.MyBotColour=!b.MyBotColour;
 	x.AllValidMoves(validMoves);
 			
	for(y=0;y<25;y++)
    if(validMoves[y]=="fuh")
    break;
		
	Board b2[y];
	for(int u=0;u<y;u++)
	{
		Move_value[u]=x.Mini_Max_2(b2[u],validMoves[u]);
	}
 	
	 for (Z=1;Z<y;Z++)
		{
		if(Move_value[max]<Move_value[Z])
		max=Z;
		}
	 		
 	return Move_Weight(ryan)-Move_value[max];

}

int Board::Mini_Max_2(Board t,string ryan)
{
	
	
	t.CopyBoard(*this);
	t.makeMove(ryan);
	t.MyBotColour=b.MyBotColour;
	
	string validMoves[25];
	int Move_value[25];
	
	t.AllValidMoves(validMoves);
	
	return Move_Weight(ryan);//-Mini_Max_0_1(Move_value,validMoves);
	
	
	
}

int Board:: Mini_Max_0_1(int (&Move_value)[25],string (&validmoves)[25])
{
	
	int y,max=0;
    
	for(y=0;y<25;y++)
    if(validmoves[y]=="fuh")
    break;
	
	Board b1[y];
	
	
	for(int u=0;u<y;u++)
	{
		Move_value[u]=Mini_Max_1(b1[u],validmoves[u]);
	}
	
	for(int g=1;g<y;g++)
	{
	if(Move_value[max]<Move_value[g])
	max=g;
	}
	return Move_value[max];
}

int Board::Move_Weight(string temp)
{
	
	char x1,y1,x2,y2;
	x1=temp[0]-'@';
	y1=temp[1]-'0';
	x2=temp[3]-'@';
	y2=temp[4]-'0';
	
	
	if(x1==x2)
		{
			if(y1<y2)
				{
					if(board[x2][y2+1]==((!MyBotColour)+'0'))
						{
							if(board[x2][y2+2]=='X')
								{
									if(x2==1 || x2==7 || x2==4 )
										return 900000 ;
									return 1000000;
								}
						if(board[x2][y2+3]=='X')
							{	
								if(x2==1 || x2==7 || x2==4 )
									return 8000 ;
								return 9000;
							}
						if(board[x2][y2+4]=='X')
							{
								if(x2==1 || x2==7 || x2==4 )
									return 6000;
								return 7000;
							}
						return 2500;	
						}
				if(board[x2][y2+1]=='_')
					{
						if(board[x2][y2+2]==(!MyBotColour+'0'))
							{
									if(board[x2][y2+3]=='X')
									{	
										if(x2==1 || x2==7 || x2==4 )
											return 4000 ;
										return 1800 ;
									}
									if(board[x2][y2+4]=='X')
									{
										if(x2==1 || x2==7 || x2==4 )
											return 1200   ;
										return 1400;
									}
						
							
							if(board[x2][y2+4]=='O')
									return 200 ;
								
								if(board[x2][y2+3]=='O')
									return 100;
									
							
							}
					if(board[x2][y2+3]==(!MyBotColour+'0'))
							{
							
								if(board[x2][y2+4]=='X')
									{
										if(x2==1 || x2==7 || x2==4 )
											return 600 ;
										return 700;
									}
							if(board[x2][y2+4]=='O')
									return 300;
							}
				
				return 500 ;
					}
				return  50;	
				}
			else if(y1>y2)
				{
					if(board[x2][y2-1]==((!MyBotColour)+'0'))
					{
							if(board[x2][y2-2]=='X')
								{
									if(x2==1 || x2==7 || x2==4 )
										return 900000 ;
									return 1000000;
								}
							if(board[x2][y2-3]=='X')
								{
									if(x2==1 || x2==7 || x2==4 )
										return 8000;	
									return 9000;
								}
							if(board[x2][y2-4]=='X')
								{
									if(x2==1 || x2==7 || x2==4 )
										return 6000;
									return 7000;
								}
					return 2500 ;
					}
			
					if(board[x2][y2-1]=='_')
						{
							
							if(board[x2][y2-2]==(!MyBotColour+'0'))
									{
										if(board[x2][y2-3]=='X')
											{
													if(x2==1 || x2==7 || x2==4 )
														return 4000;
													return 1800;
											}
										
											if(board[x2][y2-4]=='X')
											{
													if(x2==1 || x2==7 || x2==4 )
													return 1200 ;
												return 1400;
											}
										if(board[x2][y2-4]=='O')
											return 200;
										
										if(board[x2][y2-3]=='O')
											return 100;
										
										return 50 ;
											
									}
									if(board[x2][y2-3]==(!MyBotColour+'0'))
									{
									
									if(board[x2][y2-4]=='X')
											{
													if(x2==1 || x2==7 || x2==4 )
													return 600 ;
												return 700;
											}
									if(board[x2][y2-4]=='O')
											return 300;
												
									return 500;	
									}
						return 50;			
						}
			
			}

		}
	else if(y1==y2)
		{
			if(x1<x2)
				{
					if(board[x2+1][y2]==((!MyBotColour)+'0'))
						{
							if(board[x2+2][y2]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
										return 900000;
									return 1000000;
								}
							if(board[x2+3][y2]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
										return 8000;
									return 9000;
								}
							if(board[x2+4][y2]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
										return 6000;
									return  7000;
								}
						return 2500;
						}
					if(board[x2+1][y2]=='_')
					{
						if(board[x2+2][y2]==!MyBotColour+'0')
						{
						
						if(board[x2+3][y2]=='X' && MyBotColour ==0)
							{
								if(y2==1 || y2==4 || y2==7)
									return 4500 ;
								return  5000;
								
							}
							
							if(board[x2+4][y2]=='X' && MyBotColour ==0  )
							{
								if(y2==1 || y2==4 || y2==7)
										return 3800;
								return 4000;
							}							
							
							if(board[x2+3][y2]=='X' && MyBotColour ==1)
							{
								if(y2==1 || y2==4 || y2==7)
									return  1200;
								return  1400;	
							}
							
							if(board[x2+4][y2]=='X' && MyBotColour ==1)
							{
								if(y2==1 || y2==4 || y2==7)
								return 1000;
								return	1100 ;
								
							}
						
							if(board[x2+4][y2]=='O')
							return 200;
						
						if(board[x2+3][y2]=='O')
							return 100;
						
							
						}
					
						if(board[x2+3][y2]==!MyBotColour+'0')
						{
							if(board[x2+4][y2]=='X' && MyBotColour ==0  )
							{
								if(y2==1 || y2==4 || y2==7)
									return 800 ;
								return 900;
								
							}
							
						if(board[x2+4][y2]=='X' && MyBotColour ==1  )
							{
								if(y2==1 || y2==4 || y2==7)
									return 600 ;
								return 700;
								
							}
							
							if(board[x2+4][y2]=='O')
							return 300;
						
						
						return 500;
						}	
											
					}
					
				}
			else if(x1>x2)
				{
					
					if(board[x2-1][y2]==(!MyBotColour+'0'))
							{
								
								if(board[x2-2][y2]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
										return 900000;
									return 1000000;
								}
								if(board[x2-3][y2]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
									return 8000;
								return 9000;
								}
								if(board[x2-4][y2]=='X')
								{
								if(y2==1 || y2==4 || y2==7)
								return 6000;
								return 7000 ;
								}
							
							return 2500;
							
							}
					if(board[x2-1][y2]=='_')
						{
							if(board[x2-2][y2]==!MyBotColour+'0')		
						{
							if(board[x2-4][y2]=='X'&& MyBotColour==1)
									{
										if(y2==1 || y2==4 || y2==7)
											return 4500;
										return 5000 ;
									}
									if(board[x2-3][y2]=='X'&& MyBotColour==1)
									{
									if(y2==1 || y2==4 || y2==7)
										return 3800;
									return 4000;
									}
									
							if(board[x2-4][y2]=='X' && MyBotColour==0)
									{
										if(y2==1 || y2==4 || y2==7)
											return 1200;
										return 1400;
									}
								if(board[x2-3][y2]=='X' && MyBotColour==0)
									{
									if(y2==1 || y2==4 || y2==7)
										return 1000;
									return 1100;
									}
								
								
						if(board[x2-4][y2]=='O')
						return 200;
						
						if(board[x2-3][y2]=='O')
						return 100;
								return 50;	
								}
								
							if(board[x2-3][y2]==!MyBotColour+'0')		
									{
							
									if(board[x2-4][y2]=='X' && MyBotColour==1)
									{
										if(y2==1 || y2==4 || y2==7)
											return 800;
										return 900;
									}
								
								
								if(board[x2-4][y2]=='X'&& MyBotColour==0)
									{
										if(y2==1 || y2==4 || y2==7)
											return 600;
										return 700;
									}
									
						if(board[x2-4][y2]=='O')
						return 300;
						
									
								return 500 ;	
								}
						
						}
				
				}
		}
	else 
		{
		  if(x2>x1 )
		  	{
		  		if(y2<y1)
		  			{
						if(board[x2+1][y2-1]==(!MyBotColour+'0'))
							{
							if(board[x2+2][y2-2]=='X')
							{
							if(x2==1 || x2==7 || x2==4 )
								return  900000;
							return 1000000 ;
							}
							if(board[x2+3][y2-3]=='X')
							{
							if(x2==1 || x2==7 || x2==4 )
								return 8000;	
							return  9000;
							}
							if(board[x2+4][y2-4]=='X')
							{
							if(x2==1 || x2==7 || x2==4 )
								return 6000;
							return 7000;
							}
					return 2500;
					}
					if(board[x2+1][y2-1]=='_')
						{
							 if(board[x2+2][y2-2]==!MyBotColour+'0')
								{
							
											if(board[x2+3][y2-3]=='X' && MyBotColour==0)
											{
													if(x2==1 || x2==7 || x2==4 )
													return 4500;
												return 5000;
											}
											
											if(board[x2+4][y2-4]=='X' && MyBotColour==0)
											{
													if(x2==1 || x2==7 || x2==4 )
													return 3800;
												return 4000;
											}
											if(board[x2+3][y2-3]=='X' && MyBotColour==1)
											{
													if(x2==1 || x2==7 || x2==4 )
													return 1300;
												return 1400;
											}
											
											if(board[x2+4][y2-4]=='X' && MyBotColour==1)
											{
													if(x2==1 || x2==7 || x2==4 )
													return 1000;
												return 1100;
											}
											
											if(board[x2+4][y2-4]=='O')
											{
											return 200;
											}
											
											if(board[x2+3][y2-3]=='O')
											{
											return 100;
											}
											
									return 100 ;		
							}
								
								if(board[x2+3][y2-3]==!MyBotColour+'0')
								{
										if(board[x2+4][y2-4]=='X' && MyBotColour==0)
											{
													if(x2==1 || x2==7 || x2==4 )
													return 800 ;
												return 900;
											}
											
											if(board[x2+4][y2-4]=='X'&& MyBotColour==1)
											{
													if(x2==1 || x2==7 || x2==4 )
													return 600 ;
												return 700;
											}
											
											if(board[x2+4][y2-4]=='O')
											return 300;
											
									return 500 ;	
							return 50 ;}						
					
						}
					}
						
			
			}
			else if(x2<x1)
		  	{
				if(y2>y1)
				  		{
			 	if(board[x2-1][y2+1]==((!MyBotColour)+'0'))
							{
								if(board[x2-2][y2+2]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
									return 900000;
								return 1000000;
								}
								if(board[x2-3][y2+3]=='X')
								{
									if(y2==1 || y2==4 || y2==7)
									return 8000;
								return 9000 ;
								}
								if(board[x2-4][y2+4]=='X')
								{
								if(y2==1 || y2==4 || y2==7)
								return 6000;
								return 7000;
								}
							
							return 2500;
							}
					if(board[x2-1][y2+1]=='_')
						{
							if(board[x2-2][y2+2]==(!MyBotColour)+'0')
							{
							
						if(board[x2-3][y2-3]=='X' && MyBotColour==1 )
								{
								if(y2==1 || y2==4 || y2==7)
								return 4500;
								return 5000;
								}
								if(board[x2-4][y2+4]=='X' && MyBotColour==1 )
								{
								if(y2==1 || y2==4 || y2==7)
								return 3800;
								return  4000;
								}
								
								if(board[x2-3][y2-3]=='X'&& MyBotColour==0)
								{
								if(y2==1 || y2==4 || y2==7)
								return 1200;
								return 1400;
								}
								if(board[x2-4][y2+4]=='X'&& MyBotColour==0)
								{
								if(y2==1 || y2==4 || y2==7)
								return 1000;
								return 1100 ;
								}
								
								if(board[x2-4][y2+4]=='O')
								return 200;
								
								if(board[x2-3][y2+3]=='O')
								return 100;
								
								
							
						return 50 ;
						}
						if(board[x2-3][y2+3]==(!MyBotColour)+'0')
							{
							
								
								if(board[x2-4][y2+4]=='X' && MyBotColour==1 )
								{
								if(y2==1 || y2==4 || y2==7)
									return 800;
								return 900;
								}
								
								
								if(board[x2-4][y2+4]=='X'&& MyBotColour== 0)
								{
								if(y2==1 || y2==4 || y2==7)
									return 600 ;
								return 700;
								}
								
								if(board[x2-4][y2+4]=='O')
								return 300;
								
							return 500;
						}
						
					
					}
					
			}
		}
			 
		}
	return 0;
}


bool Board:: MoveValidation(string Move)
{
	char x1,y1,x2,y2;
	x1=Move[0]-'@';
	y1=Move[1]-'0';
	x2=Move[3]-'@';
	y2=Move[4]-'0';
	
			
			if(x1==x2 && y1==y2)
			return false;
			
			if( x1==x2 && abs(y1-y2)==1  )
			goto down;
			
			if( y1==y2 && abs(x1-x2)==1)
			goto down;
			
			if( (x2-x1)==(y1-y2) )
			goto down;
			
			return false;
			
			
down:	if(MyBotColour==0)
		{
			if(board[x1][y1]!='0' || board[x2][y2]!='0'  )
			return false;
			
			if ( x1==x2 )
			{
					if( y1<y2)
					{
						if( board[x2][y2+1]=='_'  ) 
							return true;
						else	
				        {
							if (board[x2][y2+1]=='1' ) 
							{
								if(board[x2][y2+2]=='_' )
									return true;
								else if(board[x2][y2+2]=='X' )
									return true;		    
							}
							else 
							return false;
						}
					return false;
					}
					
					if(y1>y2)
					{
						if(  board[x2][y2-1]=='_' ) 
							return true;
						else	
				        {
							if ( board[x2][y2-1]=='1') 
							{		
								if( board[x2][y2-2]=='_')
									return true;
								else if( board[x2][y2-2]=='X')
									return true;		    
							}
							return false;
						}
					return false;	
					}
					return false;
			}
			else if (y1==y2 )
			{
			   if(x1<x2)
			   {
					if( board[x2+1][y2]=='_'  ) 
						return true;
					else	
			        {
						if (board[x2+1][y2]=='1' ) 
						{
							if(board[x2+2][y2]=='_' )
								return true;
							else if(board[x2+2][y2]=='X' )
								return true;
							
								return false;		    
						}
						 
							return false;
					}
				}		
				if(x1>x2)
				{	
					if(  board[x2-1][y2]=='_' )  
						return true;
					else	
			        {
						if ( board[x2-1][y2]=='1') 
						{
							 if( board[x2-2][y2]=='_')
								return true;
										else if( board[x2-2][y2]=='X')
										return true;
										else
										return false;		    
								}
							
							return false;
					}
				return false; 
				}
			}
			else 
			{
				if(x1<x2)
				{
					
					if(y1>y2)
					{
						if(  board[x2+1][y2-1]=='_' ) 
								return true;
							else	
				                {
								
									if ( board[x2+1][y2-1]=='1') 
										{
									
											  if( board[x2+2][y2-2]=='_')
											  	return true;
											else if( board[x2+2][y2-2]=='X')
												return true;		    
												
												return false;
										}
									 
									return false;
							}
						return false;	
			
							
					}		
				}
				else if(x2<x1)
				{
					if(y1<y2)
					{
						if( board[x2-1][y2+1]=='_'  ) 
								return true;
							else	
				                {
								
								if (board[x2-1][y2+1]=='1' ) 
									{
								
										  if(board[x2-1][y2+2]=='_' )
										  	return true;
											else if(board[x2-1][y2+2]=='X' )
											return true;		    
										return false;
									}
								else 
								
								return false;
								}
					
					}	
					
				}	
			}
	
		return false;	
		}
		
		if(MyBotColour==1)
		{
			if(board[x1][y1]!='1' || board[x2][y2]!='1'  )
			return false;
			
			if ( x1==x2 )
			
			{
				if(y1<y2)
				{
				
				if( board[x2][y2+1]=='_'  ) 
					return true;
				else	
	                {
					
					if (board[x2][y2+1]=='0' ) 
						{
							if( board[x2][y2+2]=='_' )
							  	return true;
								else if(board[x2][y2+2]=='X' )
								return true;
								
								return false;		    
						}
					else 
					return false;
				 }
				 return false;
				}
				
				if(y1>y2)
					{
			
				if ( board[x2][y2-1]=='_' )  
					return true;
				else	
		                {
								if (board[x2][y2-1]=='0') 
							{
								  if( board[x2][y2-2]=='_' )
								  	return true;
								  	
									else if( board[x2][y2-2]=='X' )
									
									return true;
									
									return false;		    
							}
							return false;
					}
			}
			return false;	
		}
			else if (y1==y2 )
			
			{
			
			if(x1<x2)
			{
			
			if (board[x2+1][y2]=='_'  ) 
					
					return true;
					
					else	
	                {
					
					if ( board[x2+1][y2]=='0' ) 

						{
					
							  if(board[x2+2][y2]=='_' )
								
								return true;
								
								else if(board[x2+2][y2]=='X')
								
								return true;
								
								return false;		    
						
						}
					return false;
					}
			return false;
			}
			
			if(x1>x2)
			{
				if(  board[x2-1][y2]=='_' ) 
					
					return true;
					
					else	
	                
					{
					
					if ( board[x2-1][y2]=='0' ) 
					
						{
					
							  if( board[x2-2][y2]=='_' )
							  
							  	return true;
							
								else if( board[x2-2][y2]=='X' )
					
								return true;
					
								else
								return false;		    
						}
						return false;
				}
			}
			}
		else 
			{
				if(x1<x2)
				{
					
					if(y1>y2)
					{
						if(  board[x2+1][y2-1]=='_' ) 
								return true;
							else	
				                {
								
									if ( board[x2+1][y2-1]=='0') 
										{
									
											  if( board[x2+2][y2-2]=='_')
											  	return true;
											else if( board[x2+2][y2-2]=='X')
												return true;		    
										return false;
										}
										
									 
									return false;
							}
						return false;	
					}
					return false;
							
				}
				else if(x2<x1)
				{
					if(y1<y2)
					{
						if( board[x2-1][y2+1]=='_'  ) 
								return true;
							else	
				                {
								
								if (board[x2-1][y2+1]=='0' ) 
									{
								
										  if(board[x2-2][y2+2]=='_' )
										  	return true;
											else if(board[x2-2][y2+2]=='X' )
											return true;		    
										return false;
									}
								else 
								
								return false;
								}
					
					}	
					return false;
				
				}
					
							 
		}
			
	return false;
	
	}	
return false;
}

void Board:: AllValidMoves(string (&ValidMoves)[25])
{
	string sample;
	sample="     \n";
	int k=0;
	
	for(int g=0;g<25;g++)
		ValidMoves[g]="fuh";
	
	for(char q='A';q<='G';q++)
	{
		for(char w='1';w<='7';w++)
		{
			for(char e=q-1;e<=q+1;e++)
			{
				for(char r=w-1;r<=w+1;r++)
				{
				
				sample[0]=q;
				sample[1]=w;
				sample[3]=e;
				sample[4]=r;
				
				if(MoveValidation(sample))	
					{
					ValidMoves[k++]=sample;
					/*cout<<"\n"<<sample<<"\n";*/
					}
				}
				
			}
		}
	}
}

void Board::makeMove(string move)
{

char x1=move[0]-'@';
char y1=move[1]-'0';
char x2=move[3]-'@';
char y2=move[4]-'0';


	if( x1==x2 )
	{
		  if( y2>y1 )
		 	{
			 	if(board[x2][y2+1]=='_')
					{
				 	board[x2][y2+1]=board[x2][y1];
				 	board[x2][y1]='_';
					 } 
				else
					{	
						if(board[x2][y2+2]=='_')
							{
							board[x2][y2+2]=board[x2][y2+1];
							board[x2][y2+1]=board[x2][y1];
							board[x2][y1]='_';
							 }	 
						else if( board[x2][y2+2]=='X' )
							{
							board[x2][y2+1]=board[x2][y1];
							board[x2][y1]='_';
							}
					}	 
			}
			else if( y2<y1 )
			{
				if(board[x2][y2-1]=='_')
					{
				 	board[x2][y2-1]=board[x2][y1];
				 	board[x2][y1]='_';
					 } 
				else
					{
						if(board[x2][y2-2]=='_')
							{	
							board[x2][y2-2]=board[x2][y2-1];
							board[x2][y2-1]=board[x2][y1];
							board[x2][y1]='_';
							}	 
						else if( board[x2][y2-2]=='X' )
						  { 
							board[x2][y2-1]=board[x2][y1];
							board[x2][y1]='_';
		                	}
					}	
			}
	}
		
		
	else if( y1==y2 )
		{
			if( x2>x1 )
		 	{
			 	if(board[x2+1][y2]=='_')
					{
				 	board[x2+1][y2]=board[x1][y2];
				 	board[x1][y2]='_';
					 } 
				else
				{
					if(board[x2+2][y2]=='_')
						{
						board[x2+2][y2]=board[x2+1][y2];
						board[x2+1][y2]=board[x1][y2];
						board[x1][y2]='_';
						}	 
					else if( board[x2+2][y2]=='X' )
						{
						board[x2+1][y2]=board[x1][y1];
						board[x1][y1]='_';
						}
				}	 
					 
			}
			else if( x2<x1 )
			{
				if(board[x2-1][y2]=='_')
					{
				 	board[x2-1][y2]=board[x1][y2];
				 	board[x1][y2]='_';
					 } 
				else
				{
					if(board[x2-2][y2]=='_')
						{
						board[x2-2][y2]=board[x2-1][y2];
						board[x2-1][y2]=board[x1][y1];
						board[x1][y1]='_';
						}	 
					else if( board[x2-2][y2]=='X' )
						{
						board[x2-1][y2]=board[x1][y1];
						board[x1][y1]='_';		
						}
				}	
			}
	  }
	  else
	  {
	  		if(x2>x1)
			  {
			  	if(y2<y1)
			  	{
				if(board[x2+1][y2-1]=='_')
					{
				 	board[x2+1][y2-1]=board[x1][y1];
				 	board[x1][y1]='_';
					 } 
				else
					{
						if(board[x2+2][y2-2]=='_')
							{	
							board[x2+2][y2-2]=board[x2+1][y2-1];
							board[x2+1][y2-1]=board[x1][y1];
							board[x1][y1]='_';
							}	 
						else if( board[x2+2][y2-2]=='X' )
						  { 
							board[x2+1][y2-1]=board[x1][y1];
							board[x1][y1]='_';
		                	}
					}
				  
				}
			  }
			 else if (x2<x1)
			 {
				if(y2>y1)
				{
					if(board[x2-1][y2+1]=='_')
					{
				 	board[x2-1][y2+1]=board[x1][y1];
				 	board[x1][y1]='_';
					 } 
				else
					{	
						if(board[x2-2][y2+2]=='_')
							{
							board[x2-2][y2+2]=board[x2-1][y2+1];
							board[x2-1][y2+1]=board[x1][y1];
							board[x1][y1]='_';
							 }	 
						else if( board[x2-2][y2+2]=='X' )
							{
							board[x2-1][y2+1]=board[x1][y1];
							board[x1][y1]='_';
							}
					}
			 	}	 	
			 }	
	  }
}

void Board::CopyBoard(const Board b0)
{
	
//	b0.display();
	
	int i=0,j=0;
	
	for(i=0;i<9;i++)
	{
	for(j=0;j<9;j++)
	board[i][j]=b0.board[i][j];
	}
	
}

Board::Board()
{
	board[0][0]=' ';
	board[0][1]=' ';
	board[0][2]=' ';
	board[0][3]='@';
	board[0][4]='O';
	board[0][5]='X';
	board[0][6]='X';
	board[0][7]='X';
	board[0][8]='O';
	
	board[1][0]=' ';
	board[1][1]=' ';
	board[1][2]='A';
	board[1][3]='X';
	board[1][4]='0';
	board[1][5]='0';
	board[1][6]='0';
	board[1][7]='0';
	board[1][8]='X';
	
	board[2][0]=' ';
	board[2][1]='B';
	board[2][2]='X';
	board[2][3]='0';
	board[2][4]='0';
	board[2][5]='0';
	board[2][6]='0';
	board[2][7]='0';
	board[2][8]='X';

	board[3][0]='C';
	board[3][1]='X';
	board[3][2]='_';
	board[3][3]='_';
	board[3][4]='0';
	board[3][5]='0';
	board[3][6]='_';
	board[3][7]='_';
	board[3][8]='X';
	
	board[4][0]='O';
	board[4][1]='_';
	board[4][2]='_';
	board[4][3]='_';
	board[4][4]='_';
	board[4][5]='_';
	board[4][6]='_';
	board[4][7]='_';
	board[4][8]='O';

	board[5][0]='X';
	board[5][1]='_';
	board[5][2]='_';
	board[5][3]='1';
	board[5][4]='1';
	board[5][5]='_';
	board[5][6]='_';
	board[5][7]='X';
	board[5][8]=' ';


	board[6][0]='X';
	board[6][1]='1';
	board[6][2]='1';
	board[6][3]='1';
	board[6][4]='1';
	board[6][5]='1';
	board[6][6]='X';
	board[6][7]='7';
	board[6][8]=' ';
	
	board[7][0]='X';
	board[7][1]='1';
	board[7][2]='1';
	board[7][3]='1';
	board[7][4]='1';
	board[7][5]='X';
	board[7][6]='6';
	board[7][7]=' ';
	board[7][8]=' ';
	
	board[8][0]='O';
	board[8][1]='X';
	board[8][2]='X';
	board[8][3]='X';
	board[8][4]='X';
	board[8][5]='O';
	board[8][6]=' ';
	board[8][7]=' ';
	board[8][8]=' ';
	
}
void Board::display()
{
cout<<"\n";	
		for(int i=0;i<9;i++)
	{
			if(i==0)
		cout<<"   ";
		
		if(i==1)
		cout<<"    ";
		
		if(i==2)
		cout<<"      ";
		
			if(i==3)
		cout<<"        ";
		
			if(i==4)
		cout<<"        D ";
		
			if(i==5)
		 cout<<"          E ";
		 	
			if(i==6)
		 cout<<"            F ";	
		
		if(i==7)
		 cout<<"               G ";	
		
		if(i==8)
		 cout<<"                   ";	
		
		
			for(int j=0;j<9;j++)
			{
				cout<<board[i][j]<<"   ";
			}
		cout<<"\n\n";
			
	}
    
	cout<<"                        1   2   3   4      5\n";
	
	}
	
