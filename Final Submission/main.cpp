#include "checkers.h"

Board box[8][8];	
Board virt_box[8][8];
Pieces user_piece[12];								
Pieces comp_piece[12];	
Pieces virt_comp[12];								
Pieces virt_user[12];
Game g;

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
