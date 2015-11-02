#include<simplecpp>



class Centre
{
	public:
	
	int i,j;
	
	Centre(int a,int b)
	{
		i=a;
		j=b;
	}
	
	Centre()
	{
		i=0;
		j=0;
	}
	
	Centre convert()
	{
		Centre c(i*50+75,j*50+75);

		return c;
	}
};


void remove_piece(Centre cen,Centre end);
void check_result();
enum occupied_by{USER,COMP,NONE};

class Board
{
	public:
	
	Centre cen;
	bool is_occupied;
	occupied_by ocby;
	
	Board(int a,int b,bool isoc,occupied_by oc)
	: cen(a,b)
	{
		is_occupied=isoc;
		ocby=oc;
	}
	
	Board()
	{
	}	
	
	void toggle_state()
	{
		if(is_occupied)
			is_occupied=false;
		else
			is_occupied=true;
	} 
	
};

Board box[8][8];
int turn=1; //Odd for User. Even for Computer

class Pieces
{
	public:
	
	Circle* c;
	Centre cen;
	Centre aux;
	
	Pieces(int a,int b)
	: cen(a,b)
	{
		aux=cen.convert();
		c = new Circle(aux.i,aux.j,20);
	}
	
	Pieces()
	{
	}
	
	void move(Centre end)
	{	
		double x=50*(end.i-cen.i);
		double y=50*(end.j-cen.j);
		
		for(int i=0;i<650;i++)
			c->move(x/650,y/650);
			
			
		//c->moveTo(75+50*end.i,75+50*end.j);
		
		box[end.i][end.j].toggle_state();
		if(box[cen.i][cen.j].ocby==USER)
			box[end.i][end.j].ocby=USER;
		else 
			box[end.i][end.j].ocby=	COMP;
			
		if(	(end.i-cen.i)%2==0 and (end.j-cen.j)%2==0 )
		{
			box[cen.i+(end.i-cen.i)/2][cen.j+(end.j-cen.j)/2].ocby=NONE;
			box[cen.i+(end.i-cen.i)/2][cen.j+(end.j-cen.j)/2].toggle_state();
			remove_piece(cen,end);
		}
		box[cen.i][cen.j].toggle_state();
		box[cen.i][cen.j].ocby=NONE;
			
		cen=end;
	}
	
	bool kill_possible(Centre end)
	{
		if(box[cen.i+(end.i-cen.i)/2][cen.j+(end.j-cen.j)/2].ocby==COMP and box[cen.i][cen.j].ocby==USER)
			return true;
		else if(box[cen.i+(end.i-cen.i)/2][cen.j+(end.j-cen.j)/2].ocby==USER and box[cen.i][cen.j].ocby==COMP)
			return true;
			
		return false;	
	}
			
		
	bool is_valid(Centre end,int n,int m)
	{
		if(m!=0)		
			if((turn%2==1 and box[cen.i][cen.j].ocby==COMP) or (turn%2==0 and box[cen.i][cen.j].ocby==USER))
				return false;
			
		if(box[end.i][end.j].is_occupied==true)
			return false;
			
		if((cen.j-end.j)*n<0)
			return false;
		
		if(end.i<0 or end.j<0 or end.i>7 or end.j>7)
			return false;
			
		if(	abs(cen.i-end.i)==2 and abs(cen.j-end.j)==2 and kill_possible(end))
			{
				if(m!=0)
					turn++;
				return true;
			}
			
		if(abs(cen.i-end.i)!=1 or abs(cen.j-end.j)!=1)
			return false;
		
		if(m!=0)
			turn++;	
		
		return true;
		
			
	}
		
};



Pieces user_piece[12];
Pieces comp_piece[12];

void remove_piece(Centre cen,Centre end)
{
	for(int n=0;n<12;n++)
	{
		if(box[cen.i][cen.j].ocby==COMP and user_piece[n].cen.i==cen.i+(end.i-cen.i)/2 and user_piece[n].cen.j==cen.j+1)
		{						
			user_piece[n].cen.i=-1;
			user_piece[n].cen.j=-1;		
			*(user_piece[n].c)=Circle(0,0,0);
			break;
		}
		else if(box[cen.i][cen.j].ocby==USER and comp_piece[n].cen.i==cen.i+(end.i-cen.i)/2 and comp_piece[n].cen.j==cen.j-1)
		{
			*(comp_piece[n].c)=Circle(0,0,0);
			comp_piece[n].cen.i=-1;
			comp_piece[n].cen.j=-1;
			break;
		}
	}
}
				
class Game
{
	public:													//?????
	void instructions()
	{
		initCanvas("Checkers",500,500);
		
		Text inst0(250,10,"INSTRUCTIONS");
		Text inst1(250,50,"OBJECTIVE");
		Text inst2(250,62,"The object of the game is to take all your opponents pieces or place him in a ");
		Text inst3(250,74,"position where he or she can no longer make any moves."); 
		Text inst4(250,104,"TURNS");
		Text inst5(250,116,"Players shall take turns at starting the game.The visitor shall start the ");
		Text inst6(250,128,"first game.");
		Text inst7(250,158,"OBLIGATION TO MOVE");
		Text inst8(250,170,"A player has to move, a player who can no longer move loses.");
		Text inst9(250,200,"MOVING PIECES");
		Text inst10(250,212,"All pieces, men and kings, can move only diagonally.");
		Text inst11(250,224,"Pieces can only move to adjacent unoccupied black squares except when");
		Text inst12(250,236,"making a jump (see below).");
		Text inst13(250,248,"Men may only move and jump forwards while kings may move and jump");
		Text inst14(250,260,"forwards as well as backwards.");
		Text inst15(250,290,"OBLIGATION TO JUMP");
		Text inst16(250,302,"If one player's piece has the opposing player's piece as a diagonal");
		Text inst17(250,314,"neighbor and the square behind the opposing player's piece is unoccupied");
		Text inst18(250,326,"the player can make a jump and remove his opponent's piece from the board.");
		Text inst19(250,338,"If a player can make a jump such player has an obligation to make a jump.");
		Text inst20(250,350,"If after making a jump another jump is possible the player must jump again");
		Text inst21(250,362,"(with the exception of pieces that have just been crowned).");
		Text inst22(250,450,"CLICK TO PLAY!!");
		
		getClick();
	}


	void start()
	{
		srand(time(NULL));
		
		for (int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				Rectangle board(75+50*i,75+50*j,50,50);
				
				if(!((i%2==0 and j%2==1) or(i%2==1 and j%2==0)))
					{
						board.setColor(COLOR(0,0,0));
						board.setFill(1);
					}	
				board.imprint();	
			}
		}
		
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if((i+j)%2==0)
				{
					if(j<3)
						box[i][j]=Board(i,j,true,COMP);
					else if(j>4)
						box[i][j]=Board(i,j,true,USER);
					else
						box[i][j]=Board(i,j,false,NONE);
				}
				else
					box[i][j]=Board(i,j,false,NONE);
			}
		}
		
		
		int k=0;
		for(int j=5;j<8;j++)
		{
			for(int i=0;i<8;i++)
			{
				if((j+i)%2==0)
				{
					user_piece[k]=Pieces(i,j);
					user_piece[k].c->setColor(COLOR("blue"));
					user_piece[k].c->setFill(1);
					comp_piece[k]=Pieces(7-i,7-j);
					comp_piece[k].c->setColor(COLOR("red"));
					comp_piece[k].c->setFill(1);
					
					cout<<user_piece[k].cen.i<<" "<<user_piece[k].cen.j<<endl;
					cout<<comp_piece[k].cen.i<<" "<<comp_piece[k].cen.j<<endl;
					k++;
					cout<<k<<endl;
				}
				cout<<"LOOP OVER"<<endl;
				
			}
		}
		
		cout<<"Entering while"<<endl;
		while(true)
		{
			
			int user_moves=0;
			
			do
			{
				Text your(250,470,"YOUR TURN"); 
				int start=getClick();
				int start_i=(start/65536)/50-1;
				int start_j=(start%65536)/50-1;
				cout<<"got click"<<endl;
				int stop,stop_i,stop_j;
				int m=0;
				
				for(m=0;m<12;m++)
				{
					if(user_piece[m].cen.i==start_i and user_piece[m].cen.j==start_j )
						break;
				}
				
				
				if(m!=12)
				{
					Rectangle r=Rectangle(start_i*50+75,start_j*50+75,50,50);
					r.setColor(COLOR(0,100,100));
					r.setFill(1);
					Circle c=Circle(start_i*50+75,start_j*50+75,20);
					c.setColor(COLOR("blue"));
					c.setFill(1);
				
				
				stop=getClick();
				cout<<"got end click"<<endl;
				cout<<start_i<<" "<<start_j<<endl;
				stop_i=(stop/65536)/50-1;
				stop_j=(stop%65536)/50-1;
				
				}
				Centre end(stop_i,stop_j);		
						
				if(m!=12 and user_piece[m].is_valid(end,1,0))							
				{
					Centre c=user_piece[m].cen;
					user_piece[m].move(end);
					if(abs(user_piece[m].cen.i-c.i)==2)
					{
						Centre kill_end1(user_piece[m].cen.i+2,user_piece[m].cen.j-2);
						Centre kill_end2(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
									
						int n=2;
						
						while(n!=0)
						{
							n=0;
							Centre kill_end1(user_piece[m].cen.i+2,user_piece[m].cen.j-2);
							while(user_piece[m].is_valid(kill_end1,1,0))
								{
									user_piece[m].move(kill_end1);
									kill_end1=Centre(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
									n=1;
								}
							
								
							Centre kill_end2(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
							while(user_piece[m].is_valid(kill_end2,1,0))
								{
									user_piece[m].move(kill_end2);
									kill_end2=Centre(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
									n=1;
								}	
							}
						}
					
								
						turn++;
					
					
					user_moves=1;
					if(user_piece[m].cen.j==0)
						user_piece[m].c->setColor(COLOR("green"));
				}
												
				else
				{
					Text t(250,485,"INVALID MOVE");
					wait(0.5);
			
				}
				
					
				if(user_moves==1)
					break;
					
			}while(true);
			
			check_result();
			
		{	
			Text your(250,475,"MY TURN");
			wait(1);			 
			
			while(true)
			{
				
				int choose_random=rand()%12;
				int move_random=rand()%2;
				int t;
				if(move_random==0)
					t=-1;
				else
					t=1;
						
			//	cout<<choose_random<<" "<<move_random<<endl;
				
				if(comp_piece[choose_random].cen.i!=-1)
				{
					Centre kill_end1(comp_piece[choose_random].cen.i+2,comp_piece[choose_random].cen.j+2);
					Centre kill_end2(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
					Centre end(comp_piece[choose_random].cen.i+t*1,comp_piece[choose_random].cen.j+1);
					
					if(comp_piece[choose_random].is_valid(kill_end1,-1,0))
					{
						comp_piece[choose_random].move(kill_end1);
						int n=2;
						
						while(n!=0)
						{
							n=0;
							Centre kill_end1(comp_piece[choose_random].cen.i+2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end1,-1,0))
								{
									comp_piece[choose_random].move(kill_end1);
									kill_end1=Centre(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
									n=1;
								}
							
								
							Centre kill_end2(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end2,-1,0))
								{
									comp_piece[choose_random].move(kill_end2);
									kill_end2=Centre(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
									n=1;
								}	
						}
						
						turn++;
							
						if(comp_piece[choose_random].cen.j==7)
							comp_piece[choose_random].c->setColor(COLOR("yellow"));
						break;
						
					}
					
					else if(comp_piece[choose_random].is_valid(kill_end2,-1,0))
					{
						comp_piece[choose_random].move(kill_end2);
						int n=2;
						
						while(n!=0)
						{
							n=0;
							Centre kill_end1(comp_piece[choose_random].cen.i+2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end1,-1,0))
								{
									comp_piece[choose_random].move(kill_end1);
									kill_end1=Centre(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
									n=1;
								}
							
								
							Centre kill_end2(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end2,-1,0))
								{
									comp_piece[choose_random].move(kill_end2);
									kill_end2=Centre(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
									n=1;
								}	
						}
						
						turn++;
													
						if(comp_piece[choose_random].cen.j==7)
							comp_piece[choose_random].c->setColor(COLOR("yellow"));
						break;
					}
					
					else if(comp_piece[choose_random].is_valid(end,-1,1))
					{
						comp_piece[choose_random].move(end);
						if(comp_piece[choose_random].cen.j==7)
							comp_piece[choose_random].c->setColor(COLOR("yellow"));
						break;
					}
					
				}
			}	
		}
		
		
		check_result();
									
		}
	}

	void result(bool win)
	{
		if(win)
		{
			Text cong(250,465,"Congratulations");
			cong.imprint();
			Text res(250,480,"YOU WIN!!");
			res.imprint();
			getClick();
			exit(0);
			
		}
		else
		{
			Text res(250,465,"YOU LOSE");
			res.imprint();
			Text luck(250,480,"Better Luck Next Time");
			luck.imprint();
			getClick();
			exit(0);
		}

	}
	
};

Game g;

void check_result()
{
	int user=0;								
	int comp=0;
	int u_king=0;
	int c_king=0;
	int u_moves=0;
	int c_moves=0;
	
	for(int i=0;i<12;i++)
	{
		if(user_piece[i].cen.i!=-1)
			user++;
		if(comp_piece[i].cen.i!=-1)
			comp++;
		if(user_piece[i].cen.j==0)
			u_king++;
		if(comp_piece[i].cen.j==7)
			c_king++;
		
		Centre ckill_end1(comp_piece[i].cen.i+2,comp_piece[i].cen.j+2);
		Centre ckill_end2(comp_piece[i].cen.i-2,comp_piece[i].cen.j+2);
		Centre cend1(comp_piece[i].cen.i+1,comp_piece[i].cen.j+1);
		Centre cend2(comp_piece[i].cen.i-1,comp_piece[i].cen.j+1);
		Centre ukill_end1(user_piece[i].cen.i+2,user_piece[i].cen.j-2);
		Centre ukill_end2(user_piece[i].cen.i-2,user_piece[i].cen.j-2);
		Centre uend1(user_piece[i].cen.i+1,user_piece[i].cen.j-1);
		Centre uend2(user_piece[i].cen.i-1,user_piece[i].cen.j-1);
	
		if(comp_piece[i].cen.i!=-1)
		{
			if(comp_piece[i].is_valid(ckill_end1,-1,0))
				c_moves++;
			if(comp_piece[i].is_valid(ckill_end2,-1,0))
				c_moves++;
			if(comp_piece[i].is_valid(cend1,-1,0))
				c_moves++;
			if(comp_piece[i].is_valid(cend2,-1,0))
				c_moves++;
		}
		
		if(user_piece[i].cen.i!=-1)
		{			
			if(user_piece[i].is_valid(ukill_end1,1,0))
				u_moves++;		
			if(user_piece[i].is_valid(ukill_end2,1,0))
				u_moves++;
			if(user_piece[i].is_valid(uend1,1,0))
				u_moves++;
			if(user_piece[i].is_valid(uend2,1,0))
				u_moves++;
		}
		
	}
	
	cout<<c_moves<<" "<<u_moves<<endl;
	
	if(user<=2 or c_king==3)	
		g.result(false);
									/*In case someone is left with 2 coins and simultaneously the opponent runs out of moves, 
									  The opponent wins.*/
	if(comp<=2 or u_king==3)		
		g.result(true);
	
	if(u_moves==0 and c_moves==0)
	{
		Text draw1(250,465,"ITS A DRAW!");
		Text draw2(250,480,"Well Played");
		getClick();
		exit(0);
	}
	
	if(u_moves==0)						
		g.result(false);
	
	if(c_moves==0)
		g.result(true);
}


int main()
{
	g.instructions();
	g.start();
}
