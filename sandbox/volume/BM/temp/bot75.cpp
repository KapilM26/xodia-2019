#include<bits/stdc++.h>

using namespace std;
     
bool whoAmI;	//if whoAmI = 1, you are Sentinels
//if whoAmI = 0, you are Scourges
bool turn;
int F=0;
bool Q;
//FUNCTIONS:
int MINIMAX(const char(*)[5][5]);
int algorithm(const string,const int,string[15],const char(*)[5][5]);		//your game's algorithm
string evaluate(const char(*)[5][5]);			//evaluation for your move
void initBoard (char(*)[5][5]);
void makethemove(string,char(*)[5][5]);
int mValidation(bool,string,const char(*)[5][5]); 		//validates your sample move according to the  rules 
void AllValidMoves(bool,string(*)[15],int *,const char(*)[5][5]);
void SegMoves(const int,const char(*)[5][5],string[15],string(*)[15],string(*)[15],string(*)[15],string(*)[15],string(*)[15]);
void copyboard(char(*)[5][5],const char(*)[5][5]);
int WeightOfTheMove(string,string[15],string[15],string[15],string[15],string[15]);
int MINIMAX(bool,const char(*)[5][5]);

int main(int argc, char *argv[])
{
  static char MainBoard[5][5]; 
  initBoard(&MainBoard);
  string input,output2,output;
  cin>>turn;
  whoAmI=turn;
  while(1)
    {
      input="       ";
      output="       ";
      output2="       ";
      fflush(stdin);
      if(turn!=1)
	{
	  getline(cin,input);
	  makethemove(input,&MainBoard);
	}
      turn=0;	
      output2=evaluate(&MainBoard);
      for(int z=0;z<7;z+=2)
        {
	  output[z]=output2[z];
	}
      makethemove(output,&MainBoard);
      cout<<output;
		
    }
}
void initBoard(char (*Iboard)[5][5])		//Function to initialize the Board
{
  for (int i = 0; i < 5; i++)
    {
      *Iboard[0][i] = 'B';
      *Iboard[1][i] = 'b';
      *Iboard[2][i] = '_';
      *Iboard[3][i] = 'r';
      *Iboard[4][i] = 'R';
    }
}

void makethemove(string line, char (*Mboard)[5][5])  //Function to make the given move in passed board
{  
  if(line[4]==line[0] && (line[2]-line[6]==2 || line[6]-line[2]==2))
    {
      *Mboard[line[4]-'0'][(line[2]+line[6])/2-'0']='_';
    }
  if(line[2]==line[6] && (line[4]-line[0]==2 || line[0]-line[4]==2))
    {
      *Mboard[(line[4]+line[0])/2-'0'][line[2]-'0']='_';
    }
  *Mboard[line[4]-'0'][line[6]-'0']=*Mboard[line[0]-'0'][line[2]-'0'];
  *Mboard[line[0]-'0'][line[2]-'0']='_';
}
void AllValidMoves(bool Q,string (*allvalidmoves)[15],int *TotalMoves,const char (*temp)[5][5]) //Returns set of valid moves with total moves
{
  static char temp2[5][5];
  copyboard(&temp2,temp);
  char t='\0';
  string trial="------------";
  for(char i='0';i<'5';i++)
    {
      for(char j='0';j<'5';j++)  
	{
	  for(char k=i-2;k<=i+2;k++)
	    {
	      if(k>='0' && k<='4')
		{
		  for(char l=j-2;l<=j+2;l++)
		    {
		      if(l>='0' && l<='4')
			{
			  trial[0]=i;
			  trial[2]=j;
			  trial[4]=k;
			  trial[6]=l;
			  if(mValidation(Q,trial,&temp2)!=0)
			    {
			      (*allvalidmoves)[t]=trial;
			      t++;		
			    }
			}
		    }
		}
	    }
	}
    }
  *TotalMoves=t; 
}
int mValidation(bool Q,const string in,const char (*board)[5][5])   //checks legality of move passed is valid in given board      
{
  if((in[4]-in[0]==2 || in[0]-in[4]==2 ) && (in[2]-in[6]!=0 )) 
    return 0;
  if((in[2]-in[6]==2 || in[6]-in[2]==2) && in[4]-in[0]!=0)	 
    return 0;
  if(*board[in[4]-'0'][in[6]-'0']!='_')
    return 0;
  if(Q)
    {    
      if(in[0]=='4')
	return 0;	
      if(*board[in[0]-'0'][in[2]-'0']!='b' && *board[in[0]-'0'][in[2]-'0']!='B' || *board[in[4]-'0'][in[6]-'0']!='_')
	return 0;
      if(*board[in[0]-'0'][in[2]-'0']=='b')
	{   
	  if(in[0]>in[4])
	    return 0;
	  if((in[4]-in[0])>2)
	    return 0;
	  if(in[4]==in[0]+1)
	    { int x ,y;
	      x=in[6]-'0';
	      y=in[2]-'0';
	      if((x-y)!=1 && (y-x)!=1)
		return 0;
	    }
	  else if(in[4]==in[0])
	    {
	      if(*board[in[4]-'0'][(in[2]+in[6])/2-'0']!='r' && *board[in[0]-'0'][(in[2]+in[6])/2-'0']!='R')
		return 0;
	    }
	  else if(in[2]==in[6])
	    {
	      if((in[4]-in[0])!=2)
		return 0;
	      if(*board[(in[0]+in[4])/2-'0'][in[2]-'0']!='r' && *board[(in[0]+in[4])/2-'0'][in[2]-'0']!='R')
		return 0;
	    }
	  return 1;
	}
      else if(*board[in[0]-'0'][in[2]-'0']=='B')
	{
	  if(in[0]>in[4])
	    return 0;
	  if((in[4]-in[0])>2 || in[6]-in[2]>2 || in[2]-in[6]>2)
	    return 0;
	  if((in[4]-in[0]==2 && in[6]-in[2]!=0) && (*board[(in[4]+in[0])/2-'0'][in[2]-'0']!='R' && *board[(in[4]+in[0])/2-'0'][in[2]-'0']!='r'))
	    return 0;
	  if(((in[6]-in[2]==2 || in[2]-in[6]==2) && in[4]-in[0]!=0) && (*board[in[0]-'0'][(in[2]+in[6])/2-'0']!='R' && *board[in[4]-'0'][(in[6]+in[2])/2-'0']!='r'))
	    return 0;
	  if(in[4]-in[0]==1)
	    {
	      if(in[6]-in[2]>1)
		return 0;
	      if(in[2]-in[6]>1)
		return 0;
	    }
	  if((in[6]-in[2]==1 || in[2]-in[6]==1) && in[4]-in[0]>1)
	    return 0;
	  if(in[4]==in[0])
	    {
	      if(*board[in[4]-'0'][(in[2]+in[6])/2-'0']!='r' && *board[in[0]-'0'][(in[2]+in[6])/2-'0']!='R')
		return 0;
	    }
	  else if(in[2]==in[6])
	    {
	      if((in[4]-in[0])!=2 && (in[4]-in[0])!= 1)
		return 0;
	      if((in[4]-in[0])==2)
		{
		  if(*board[(in[0]+in[4])/2-'0'][in[2]-'0']!='r' && *board[(in[0]+in[4])/2-'0'][in[2]-'0']!='R')
		    return 0;
		}
	    }
	}
      return 1;		
    }
  else
    {
      if(in[0]=='0')
	return 0;
      if(*board[in[0]-'0'][in[2]-'0']!='r' && *board[in[0]-'0'][in[2]-'0']!='R' || *board[in[4]-'0'][in[6]-'0']!='_')
	return 0;
      if(*board[in[0]-'0'][in[2]-'0']=='r')
	{
	  if(in[0]<in[4])
	    return 0;
	  if((in[0]-in[4])>2)
	    return 0;
	  if(in[4]==in[0]-1)
	    {
	      if(in[6]!=in[2]+1 && in[6]!=in[2]-1)
		return 0;
	    }
	  else if(in[4]==in[0])
	    {
	      if(*board[in[4]-'0'][(in[2]+in[6])/2-'0']!='b' && *board[in[0]-'0'][(in[2]+in[6])/2-'0']!='B')
		return 0;
	    }
	  else if(in[2]==in[6])
	    {
	      if((in[0]-in[4])!=2)
		return 0;
	      if(*board[(in[0]+in[4])/2-'0'][in[2]-'0']!='b' && *board[(in[0]+in[4])/2-'0'][in[2]-'0']!='B')
		return 0;
	    }
	  return 1;
	}
      else if(*board[in[0]-'0'][in[2]-'0']=='R')
	{
	  if(in[0]<in[4])
	    return 0;
	  if((in[0]-in[4])>2 || in[6]-in[2]>2 || in[2]-in[6]>2)
	    return 0;
	  if((in[0]-in[4]==2 && in[6]-in[2]!=0) && (*board[(in[4]+in[0])/2-'0'][in[2]-'0']!='B' && *board[(in[4]+in[0])/2-'0'][in[2]-'0']!='b'))
	    return 0;
	  if(((in[6]-in[2]==2 || in[2]-in[6]==2) && in[4]-in[0]!=0) && (*board[in[0]-'0'][(in[2]+in[6])/2-'0']!='B' && *board[in[4]-'0'][(in[6]+in[2])/2-'0']!='b'))
	    return 0;
	  if(in[0]-in[4]==1)
	    {
	      if(in[6]-in[2]>1)
		return 0;
	      if(in[2]-in[6]>1)
		return 0;
	    }
	  if((in[6]-in[2]==1 || in[2]-in[6]==1) && in[0]-in[4]>1)
	    return 0;
	  if(in[4]==in[0])
	    {
	      if(*board[in[4]-'0'][(in[2]+in[6])/2-'0']!='b' && *board[in[0]-'0'][(in[2]+in[6])/2-'0']!='B')
		return 0;
	    }
	  else if(in[2]==in[6])
	    {
	      if((in[0]-in[4])>2)
		return 0;
	      if((in[0]-in[4])==2)
		if(*board[(in[0]+in[4])/2-'0'][in[2]-'0']!='b' && *board[(in[0]+in[4])/2-'0'][in[2]-'0']!='B')
		  return 0;
	    }
	  return 1;	    
	}	
    }
}
void copyboard(char (*A)[5][5],const char (*B)[5][5]) // copy 1 board's state to another new board
{
  for(int i=0;i<5;i++)
    {
      for(int j=0;j<5;j++)
	{
	  *A[i][j]=*B[i][j];
	}
    }
}
string evaluate(const char (*KBoard)[5][5]) // return next strategy move
{
  static char temp[5][5];
  copyboard(&temp,KBoard);
  int TotalMoves,score[15]={'T','T','T','T','T','T','T','T','T','T','T','T','T','T','T'};
  string LINE,allvalidmoves[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
  AllValidMoves(whoAmI,&allvalidmoves,&TotalMoves,&temp);
  for(int i=0;allvalidmoves[i]!="-";i++)
    {
      Q=whoAmI;
      F=0;    
      score[i]=algorithm(allvalidmoves[i],TotalMoves,allvalidmoves,&temp);
    } 
  int max=0;
    
  for(int j=0;score[j]!='T';j++)
    {
      if(score[max]<=score[j])
    	max=j;
    }
  LINE=allvalidmoves[max];
  return LINE;
}
void SegMoves(const int TotalMoves,const char (*Sboard)[5][5],string allvalidmoves[15],string (*killS)[15],string (*killB)[15],string (*frwdS)[15],string (*frwdB)[15],string (*sideB)[15])// segregate moves
{
  string temp;
  int a=0,b=0,d=0,e=0,f=0,i=0;
  for(i=0;i<TotalMoves;i++)
    {
      temp=allvalidmoves[i];
      if(temp[0]-temp[4]==2 || temp[4]-temp[0]==2 || temp[6]-temp[2]==2 || temp[2]-temp[6]==2)
	{	
	  if(*Sboard[(temp[0]+temp[4])/2-'0'][(temp[2]+temp[6])/2-'0']=='B'||*Sboard[(temp[0]+temp[4])/2-'0'][(temp[2]+temp[6])/2-'0']=='R')
	    (*killB)[a++]=temp;
	  else
	    (*killS)[b++]=temp;	
	}
      else if(temp[0]-temp[4]==1 || temp[4]-temp[0]==1)
	{
	  if(*Sboard[temp[0]-'0'][temp[2]-'0']=='b' || *Sboard[temp[0]-'0'][temp[2]-'0']=='r')
	    (*frwdS)[d++]=temp;
	  else
	    (*frwdB)[e++]=temp;
	}
      else
	{
	  (*sideB)[f++]=temp;
	
	}
    }        
}
int WeightOfTheMove(string MOVE,string killS[15],string killB[15],string frwdS[15],string frwdB[15],string sideB[15])//add weight to moves
{
  string lead;
  {
    for(int i=0;( killS[i]!="-" || killB[i]!="-" || frwdS[i]!="-" || frwdB[i]!="-" || sideB[i]!="-" || i<15 );i++)
      {
	if(MOVE==killB[i])
	  return 30;
	if(MOVE==killS[i])
	  return 20;
	if(MOVE==frwdB[i])
	  {
	    lead=frwdB[i];
	    if(lead[6]=='0' || lead[6]=='4' )
	      return 17;
	    return 15;	
	  }
	
	if(MOVE==frwdS[i])
	  { 
	    lead=frwdS[i];
	    if(lead[6]=='0' || lead[6]=='4' )
	      return 12;
	    return 10;
	  } 
	if(MOVE==sideB[i])
	  return	10;
      }
  }
}
int algorithm(const string MOVE,const int TotalMoves,string allvalidmoves[15],const char (*TBoard)[5][5])//algorithm to forelook board's status 
{
  string line;
  line=MOVE;
  if ((line[4]=='0' || line[4]=='4') )
    {
      return 100;
    }
  int W=0;
  {
    string killS[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
    string killB[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
    string frwdS[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
    string frwdB[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
    string sideB[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
    SegMoves(TotalMoves,TBoard,allvalidmoves,&killS,&killB,&frwdS,&frwdB,&sideB);
    W=WeightOfTheMove(MOVE,killS,killB,frwdS,frwdB,sideB);
  }
  if(Q==0)
    Q=1;
  else
    Q=0;
		       
  if(F==0)
    {
      static char RYAN[5][5];
      copyboard(&RYAN,TBoard);
      makethemove(line,&RYAN);
      return W - MINIMAX(Q,&RYAN);
    }
  else 
    return W;
}
int MINIMAX(bool Q,const char(*KBoard)[5][5])
{
  {
    if(F==1)
      return 0;
    if(F==0)
      { 
	F=1;
      }  
  }
  static char temp[5][5];
  copyboard(&temp,KBoard);
  int TotalMoves,score1[15]={'T','T','T','T','T','T','T','T','T','T','T','T','T','T','T'},
    score2[15]={'T','T','T','T','T','T','T','T','T','T','T','T','T','T','T'};
  string allvalidmoves1[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
  AllValidMoves(Q,&allvalidmoves1,&TotalMoves,&temp);
  for(int i=0;allvalidmoves1[i]!="-";i++)
    {    
      score1[i]=algorithm(allvalidmoves1[i],TotalMoves,allvalidmoves1,&temp);
    } 
  int max1=0,max2=0;    
  for(int j=0;score1[j]!='T';j++)
    {
      if(score1[max1]<=score1[j])
    	max1=j;
    }
  string slip=allvalidmoves1[max1];
  makethemove(slip,&temp);
  if(Q==0)
    Q=1;
  else
    Q=0;
  string allvalidmoves2[15]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
  AllValidMoves(Q,&allvalidmoves2,&TotalMoves,&temp);
  for(int i=0;allvalidmoves2[i]!="-";i++)
    {    
      score2[i]=algorithm(allvalidmoves2[i],TotalMoves,allvalidmoves2,&temp);
    }
  for(int j=0;score2[j]!='T';j++)
    {
      if(score2[max2]<=score2[j])
    	max2=j;
    }
  return score1[max1]-score2[max2];
}

