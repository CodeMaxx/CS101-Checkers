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
void remove_virt_piece(Centre cen,Centre end);
void check_result(int i);
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
Board virt_box[8][8];
//int turn=1; //Odd for User. Even for Computer
//int virt_turn=1;

class Pieces
{
	public:
	
	Circle* c;
	Centre cen;
	Centre aux;
	
	Pieces(int a,int b,int r)
	: cen(a,b)
	{
		aux=cen.convert();
		c = new Circle(aux.i,aux.j,r);
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
	
	void virt_move(Centre end)
	{	
		//double x=50*(end.i-cen.i);
		//double y=50*(end.j-cen.j);
				
		//for(int i=0;i<650;i++)
			//c->move(x/650,y/650);
			
			
		//c->moveTo(75+50*end.i,75+50*end.j);
		
		virt_box[end.i][end.j].toggle_state();
		if(virt_box[cen.i][cen.j].ocby==USER)
			virt_box[end.i][end.j].ocby=USER;
		else 
			virt_box[end.i][end.j].ocby=COMP;
			
		if(	(end.i-cen.i)%2==0 and (end.j-cen.j)%2==0 )
		{
			virt_box[cen.i+(end.i-cen.i)/2][cen.j+(end.j-cen.j)/2].ocby=NONE;
			virt_box[cen.i+(end.i-cen.i)/2][cen.j+(end.j-cen.j)/2].toggle_state();
			remove_virt_piece(cen,end);
		}
		virt_box[cen.i][cen.j].toggle_state();
		virt_box[cen.i][cen.j].ocby=NONE;
			
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
			
		
	bool is_valid(Centre end,int n)
	{
		
		if(box[end.i][end.j].is_occupied==true)
			return false;
			
		if((cen.j-end.j)*n<0)
			return false;
		
		if(end.i<0 or end.j<0 or end.i>7 or end.j>7)
			return false;
			
		if(	abs(cen.i-end.i)==2 and abs(cen.j-end.j)==2 and kill_possible(end))
				return true;
			
		if(abs(cen.i-end.i)!=1 or abs(cen.j-end.j)!=1)
			return false;
		
		return true;
		
			
	}
	
		
};



Pieces user_piece[12];
Pieces comp_piece[12];
Pieces virt_comp[12];
Pieces virt_user[12];

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

void remove_virt_piece(Centre cen,Centre end)
{
	for(int n=0;n<12;n++)
	{
		if(virt_box[cen.i][cen.j].ocby==COMP and virt_user[n].cen.i==cen.i+(end.i-cen.i)/2 and virt_user[n].cen.j==cen.j+1)
		{						
			virt_user[n].cen.i=-1;
			virt_user[n].cen.j=-1;		
			*(virt_user[n].c)=Circle(0,0,0);
			break;
		}
		else if(virt_box[cen.i][cen.j].ocby==USER and virt_comp[n].cen.i==cen.i+(end.i-cen.i)/2 and virt_comp[n].cen.j==cen.j-1)
		{
			*(virt_comp[n].c)=Circle(0,0,0);
			virt_comp[n].cen.i=-1;
			virt_comp[n].cen.j=-1;
			break;
		}
	}
}

void intel(Pieces &virt,Centre &cen,int &k,int n)
{
	k=k+n*20;
	
	virt.virt_move(cen);
	int m=2;
	
	while(m!=0)
	{
		m=0;
		Centre kill_end1(virt.cen.i+2,virt.cen.j+2);
		while(virt.is_valid(kill_end1,-1))
			{
				virt.virt_move(kill_end1);
				kill_end1=Centre(virt.cen.i-2,virt.cen.j+2);
				m=1;
				k=k+n*20;
				
			}
		
			
		Centre kill_end2(virt.cen.i-2,virt.cen.j+2);
		while(virt.is_valid(kill_end2,-1))
			{
				virt.virt_move(kill_end2);
				kill_end2=Centre(virt.cen.i-2,virt.cen.j+2);
				m=1;
				k=k+n*20;
			}	
	}
	
	if(virt.cen.j==7)
		k=k+n*50;
}
				
		
		
				
class Game
{
	public:													//?????
	void instructions()
	{
	
		Text inst0(250,10,"INSTRUCTIONS");
		inst0.setColor(COLOR("red"));
		Text inst1(250,50,"OBJECTIVE");
		inst1.setColor(COLOR(100,150,120));
		Text inst2(250,62,"The object of the game is to take 3 of your pieces to last line of your ");
		Text inst3(250,74," opponent's side or kill your opponents pieces until they are less than 3 ");
		Text inst4(250,86,"	or place him in a position where he or she can no longer make any moves."); 
		Text inst5(250,116,"TURNS");
		inst5.setColor(COLOR(100,150,120));
		Text inst6(250,128,"Players shall take turns.The User shall start the game");
		Text inst7(250,158,"OBLIGATION TO MOVE");
		inst7.setColor(COLOR(100,150,120));
		Text inst8(250,170,"A player has to move, a player who can no longer move loses.");
		Text inst9(250,200,"MOVING PIECES");
		inst9.setColor(COLOR(100,150,120));
		Text inst10(250,212,"All pieces can move only diagonally.");
		Text inst11(250,224,"Pieces can only move to adjacent unoccupied black squares except when");
		Text inst12(250,236,"making a jump (see below).");
		Text inst13(250,248,"Pieces may only move and jump forwards");
		Text inst15(250,278,"OBLIGATION TO JUMP");
		inst15.setColor(COLOR(100,150,120));
		Text inst16(250,290,"If one player's piece has the opposing player's piece as a diagonal");
		Text inst17(250,302,"neighbor and the square behind the opposing player's piece is unoccupied");
		Text inst18(250,314,"the player can make a jump and remove his opponent's piece from the board.");
		Text inst19(250,326,"If a player makes such jump he or she has an obligation to make another ");
		Text inst20(250,338,"jump if possible. This has been automated and the user need not click repeatedly.");
		Text inst21(250,370,"LET THE GAME BEGIN!");
		inst21.setColor(COLOR("blue"));
		Circle c(250,450,50);
		c.setColor(COLOR(100,150,120));
		c.setFill(1);
		Text inst22(250,450,"CLICK TO PLAY!!");
		inst22.setColor(COLOR("blue"));
		
		getClick();
	}


	void start()
	{
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
		
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				virt_box[i][j]=box[i][j];
			}
		}
		
		int k=0;
		for(int j=5;j<8;j++)
		{
			for(int i=0;i<8;i++)
			{
				if((j+i)%2==0)
				{
					user_piece[k]=Pieces(i,j,20);
					user_piece[k].c->setColor(COLOR("blue"));
					user_piece[k].c->setFill(1);
					comp_piece[k]=Pieces(7-i,7-j,20);
					comp_piece[k].c->setColor(COLOR("red"));
					comp_piece[k].c->setFill(1);
				
					k++;
				}
				
			}
		}
		
		k=0;
		
		for(int j=5;j<8;j++)
		{
			for(int i=0;i<8;i++)
			{
				if((j+i)%2==0)
				{
					virt_user[k]=Pieces(i,j,0);
					virt_comp[k]=Pieces(7-i,7-j,0);
				
					k++;
				}
				
			}
		}
		
		
		
		cout<<"Entering while"<<endl;
		while(true)
		{
			
			int user_moves=0;
			
			do
			{
				Text your(250,30,"YOUR TURN"); 
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
						
				if(m!=12 and user_piece[m].is_valid(end,1))							
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
							while(user_piece[m].is_valid(kill_end1,1))
								{
									user_piece[m].move(kill_end1);
									kill_end1=Centre(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
									n=1;
								}
							
								
							Centre kill_end2(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
							while(user_piece[m].is_valid(kill_end2,1))
								{
									user_piece[m].move(kill_end2);
									kill_end2=Centre(user_piece[m].cen.i-2,user_piece[m].cen.j-2);
									n=1;
								}	
						}
					}
					
								
					//	turn++;
					
					
					user_moves=1;
					if(user_piece[m].cen.j==0)
						user_piece[m].c->setColor(COLOR("green"));
				}
												
				else
				{
					Text t(250,15,"INVALID MOVE");
					wait(0.5);
			
				}
				
					
				if(user_moves==1)
					break;
					
			}while(true);
			
			check_result(1);
			cout<<"not dissapearing"<<endl;			
			for(int z=0;z<12;z++)
			{
				delete virt_user[z].c ;
				virt_user[z]=user_piece[z];
				virt_user[z].c=new Circle;
				*(virt_user[z].c)=Circle(virt_user[z].cen.i,virt_user[z].cen.j,0);
				
				delete virt_comp[z].c;
				virt_comp[z]=comp_piece[z];
				virt_comp[z].c=new Circle;
				*(virt_comp[z].c)=Circle(virt_comp[z].cen.i,virt_comp[z].cen.j,0);
			}
			
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
				virt_box[i][j]=box[i][j];
				}
			}
			
			//virt_turn=turn;
						
			
		{	
			Text your(250,30,"MY TURN");			 
			wait(1);
			int score[12];
			
			
			for(int i=0;i<12;i++)
			{
				
				if(virt_comp[i].cen.i!=-1)
				{					
					
					Centre kill_end1(virt_comp[i].cen.i+2,virt_comp[i].cen.j+2);
					Centre kill_end2(virt_comp[i].cen.i-2,virt_comp[i].cen.j+2);
					//Centre end1(virt_comp[i].cen.i+1,virt_comp[i].cen.j+1);
					//Centre edn2(virt_comp[i].cen.i-1,virt_comp[i].cen.j+1);
					
					int k1=0,k2=0;
					
					if(virt_comp[i].is_valid(kill_end1,-1))
					{	
						intel(virt_comp[i],kill_end1,k1,1);
						
						for(int z=0;z<12;z++)
						{
							delete virt_user[z].c ;
							virt_user[z]=user_piece[z];
							virt_user[z].c=new Circle;
							*(virt_user[z].c)=Circle(virt_user[z].cen.i,virt_user[z].cen.j,0);
							
							delete virt_comp[z].c;
							virt_comp[z]=comp_piece[z];
							virt_comp[z].c=new Circle;
							*(virt_comp[z].c)=Circle(virt_comp[z].cen.i,virt_comp[z].cen.j,0);
						}
						
						for(int i=0;i<8;i++)
						{
							for(int j=0;j<8;j++)
							{
							virt_box[i][j]=box[i][j];
							}
						}
					}
			
					if(virt_comp[i].is_valid(kill_end2,-1))
					{
						intel(virt_comp[i],kill_end2,k2,1);
						for(int z=0;z<12;z++)
						{
							delete virt_user[z].c ;
							virt_user[z]=user_piece[z];
							virt_user[z].c=new Circle;
							*(virt_user[z].c)=Circle(virt_user[z].cen.i,virt_user[z].cen.j,0);
							
							delete virt_comp[z].c;
							virt_comp[z]=comp_piece[z];
							virt_comp[z].c=new Circle;
							*(virt_comp[z].c)=Circle(virt_comp[z].cen.i,virt_comp[z].cen.j,0);
						}
						
						for(int i=0;i<8;i++)
						{
							for(int j=0;j<8;j++)
							{
							virt_box[i][j]=box[i][j];
							}
						}
					}
									
					cout<<k1<<" "<<k2<<endl;
					
					if(k1==0 and k2==0)
						score[i]=0;
					else if(k2>k1)
						score[i]=65536*k2+2;
					else
						score[i]=65536*k1+1;
							
				}
			}
					
			int l;
				
			for(l=0;l<12;l++)
			{
				if(comp_piece[l].cen.i!=-1 and score[l]!=0)
					break;
			}
			
			cout<<"cool1"<<endl;
			if(l==12)
			{
				int defeat[24];
				for(int i=0;i<24;i++)
					defeat[i]=0;
					
				for(int j=0;j<2;j++)
				{
					for(int i=0;i<12;i++)
					{
						if(virt_comp[i].cen.i!=-1)
						{
							Centre end;
							
							if(j==0)
								end=Centre(virt_comp[i].cen.i-1,virt_comp[i].cen.j+1);
							else
								end=Centre(virt_comp[i].cen.i+1,virt_comp[i].cen.j+1);
						
							if(end.j==7 and virt_comp[i].is_valid(end,-1))
							{
								defeat[12*j+i]=50;
								break;
							}
							
							if(end.i>0 and end.i<7 and virt_comp[i].is_valid(end,-1))
							{
								if(j==0)
									if((virt_box[end.i+1][end.j+1].ocby==USER and virt_box[end.i-1][end.j-1].ocby==NONE) or (virt_box[end.i-1][end.j+1].ocby==USER and virt_box[end.i+1][end.j-1].ocby==COMP))
										defeat[i]=-20;
									else
											defeat[i]=0;
								else
									if((virt_box[end.i+1][end.j+1].ocby==USER and virt_box[end.i-1][end.j-1].ocby==COMP) or (virt_box[end.i-1][end.j+1].ocby==USER and virt_box[end.i+1][end.j-1].ocby==NONE))
										defeat[12+i]=-20;
									else
										defeat[12+i]=0;
							}
							else if((end.i==0 or end.i==7) and virt_comp[i].is_valid(end,-1))
								defeat[12*j+i]=20;
							else
								defeat[12*j+i]=-100;
							
						}
					}
				}
				
				int max=-50;
				int index=-1;
				for(int i=0;i<24;i++)
				{
					if(comp_piece[i%12].cen.i!=-1 and defeat[i]>max)
					{
						max=defeat[i];
						index=i;
					}
				}
				cout<<max<< " "<<index<<endl;
				Centre end1(comp_piece[index%12].cen.i-1,comp_piece[index%12].cen.j+1);
				Centre end2(comp_piece[index%12].cen.i+1,comp_piece[index%12].cen.j+1);
				
				if(index<12)
				{
					comp_piece[index%12].move(end1);
				}
				else
				{
					comp_piece[index%12].move(end2);
				}
				
				if(comp_piece[index%12].cen.j==7)
					comp_piece[index%12].c->setColor(COLOR("yellow"));
									
					
				
				
				
				/*while(true)
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
						Centre end(comp_piece[choose_random].cen.i+t*1,comp_piece[choose_random].cen.j+1);
						
						if(comp_piece[choose_random].is_valid(end,-1))
						{
							comp_piece[choose_random].move(end);
							//turn++;
							if(comp_piece[choose_random].cen.j==7)
								comp_piece[choose_random].c->setColor(COLOR("yellow"));
								
								cout<<"cool1"<<endl;
								
							break;
						}
					}
					
				}*/
					
			}
			else				
			{
				int max=-1;
				int index=-1;
				for(int i=0;i<12;i++)
				{
					if(comp_piece[i].cen.i!=-1 and score[i]>max)
					{
						max=score[i];
						index=i;
					}
				}
				
				Centre kill_end1(comp_piece[index].cen.i+2,comp_piece[index].cen.j+2);
				Centre kill_end2(comp_piece[index].cen.i-2,comp_piece[index].cen.j+2);
				
				if(score[index]%65536==1)
					{
						comp_piece[index].move(kill_end1);
					//	wait(1);
					}
				else
					{
						comp_piece[index].move(kill_end2);
						//wait(1);
					}
				
				int n=2;
						
				while(n!=0)
				{
					n=0;
					Centre kill_end1(comp_piece[index].cen.i+2,comp_piece[index].cen.j+2);
					while(comp_piece[index].is_valid(kill_end1,-1))
					{
						comp_piece[index].move(kill_end1);
						kill_end1=Centre(comp_piece[index].cen.i-2,comp_piece[index].cen.j+2);
						n=1;
					}
					
						
					Centre kill_end2(comp_piece[index].cen.i-2,comp_piece[index].cen.j+2);
					while(comp_piece[index].is_valid(kill_end2,-1))
					{
						comp_piece[index].move(kill_end2);
						kill_end2=Centre(comp_piece[index].cen.i-2,comp_piece[index].cen.j+2);
						n=1;
					}	
				}
				
				if(comp_piece[index].cen.j==7)
				comp_piece[index].c->setColor(COLOR("yellow"));	
				
				cout<<"cool1"<<endl;
			
			}
			
			cout<<"cool1"<<endl;
			
			/*for(int z=0;z<12;z++)
			{
				delete virt_comp[z].c ;
				virt_comp[z]=comp_piece[z];    //requires operator overloading-pointer creating problem
				
				virt_comp[z].c=new Circle;  //might get rid of above requirement
				*(virt_comp[z].c)=Circle(virt_comp[z].cen.i,virt_comp[z].cen.j,0);
			}
			
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
				virt_box[i][j]=box[i][j];
				}
			}*/
			
			cout<<"cool1"<<endl;
			
		}
					
					//k1=comp_piece[i].intelligent(kill_end1)
					//k2=comp_piece[i].intelligent(kill_end2)
					//m1=comp_piece[i].intelligent()
					//m2=comp_piece[i].intelligent()
				
			
			
			/*while(true)
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
					
					if(comp_piece[choose_random].is_valid(kill_end1,-1))
					{
						comp_piece[choose_random].move(kill_end1);
						int n=2;
						
						while(n!=0)
						{
							n=0;
							Centre kill_end1(comp_piece[choose_random].cen.i+2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end1,-1))
								{
									comp_piece[choose_random].move(kill_end1);
									kill_end1=Centre(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
									n=1;
								}
							
								
							Centre kill_end2(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end2,-1))
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
					
					else if(comp_piece[choose_random].is_valid(kill_end2,-1))
					{
						comp_piece[choose_random].move(kill_end2);
						int n=2;
						
						while(n!=0)
						{
							n=0;
							Centre kill_end1(comp_piece[choose_random].cen.i+2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end1,-1))
								{
									comp_piece[choose_random].move(kill_end1);
									kill_end1=Centre(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
									n=1;
								}
							
								
							Centre kill_end2(comp_piece[choose_random].cen.i-2,comp_piece[choose_random].cen.j+2);
							while(comp_piece[choose_random].is_valid(kill_end2,-1))
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
					
					else if(comp_piece[choose_random].is_valid(end,-1))
					{
						comp_piece[choose_random].move(end);
						turn++;
						if(comp_piece[choose_random].cen.j==7)
							comp_piece[choose_random].c->setColor(COLOR("yellow"));
						break;
					}
					
				}
			}	
		}
		
		*/
		
			check_result(-1);
		
			for(int z=0;z<12;z++)
			{
				delete virt_user[z].c;
				virt_user[z]=user_piece[z];
				virt_user[z].c=new Circle;
				*(virt_user[z].c)=Circle(virt_user[z].cen.i,virt_user[z].cen.j,0);
				
				delete virt_comp[z].c;
				virt_comp[z]=comp_piece[z];
				virt_comp[z].c=new Circle;
				*(virt_comp[z].c)=Circle(virt_comp[z].cen.i,virt_comp[z].cen.j,0);
			}
			
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
				virt_box[i][j]=box[i][j];
				}
			}
		
								
		}
	}

	void result(bool win)
	{
		for(int i=0;i<12;i++)
		{
			delete comp_piece[i].c;
			delete user_piece[i].c;
		}
		
		if(win)
		{
			Text cong(250,15,"Congratulations");
			cong.setColor(COLOR("blue"));
			cong.imprint();
			Text res(250,30,"YOU WIN!!");
			res.setColor(COLOR("blue"));
			res.imprint();
			getClick();
			exit(0);
			
		}
		else
		{
			Text res(250,15,"YOU LOSE");
			res.setColor(COLOR("blue"));
			res.imprint();
			Text luck(250,30,"Better Luck Next Time");
			luck.setColor(COLOR("blue"));
			luck.imprint();
			getClick();
			exit(0);
		}

	}
	
};

Game g;

void check_result(int i)
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
			if(comp_piece[i].is_valid(ckill_end1,-1))
				c_moves++;
			if(comp_piece[i].is_valid(ckill_end2,-1))
				c_moves++;
			if(comp_piece[i].is_valid(cend1,-1))
				c_moves++;
			if(comp_piece[i].is_valid(cend2,-1))
				c_moves++;
		}
		
		if(user_piece[i].cen.i!=-1)
		{			
			if(user_piece[i].is_valid(ukill_end1,1))
				u_moves++;		
			if(user_piece[i].is_valid(ukill_end2,1))
				u_moves++;
			if(user_piece[i].is_valid(uend1,1))
				u_moves++;
			if(user_piece[i].is_valid(uend2,1))
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
	
	if(u_moves==0 and i==-1)						
		g.result(false);
	
	if(c_moves==0 and i==1)
		g.result(true);
}


int main()
{
	int x;
	initCanvas("Checkers",500,500);
	{
		Rectangle r1(125,250,250,500);
		r1.setColor(COLOR(150,50,50));
		r1.setFill(1);
		Rectangle r2(375,250,250,500);
		r2.setColor(COLOR(50,150,50));
		r2.setFill(1);
		Text ins(125,250,"INSTRUCTIONS");
		Text play(375,250,"PLAY");
		x=getClick();
	}
	if(x/65536<250)
		g.instructions();
	g.start();
}
