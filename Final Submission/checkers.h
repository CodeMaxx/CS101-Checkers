#include<simplecpp>

class Centre      
{
	public:
	int i,j;     //store the centre of Game Pieces and Game Board. i and j both range from (0-7) across the board
	
	Centre(int a,int b);	//Constructor
	Centre();				//Constructor
	Centre convert();		//Converts the co-ordinates from i-j to x-y system 
};

void remove_virt_piece(Centre cen,Centre end); //Helper Function-Removes Virtual pieces form virtual board
void remove_piece(Centre cen,Centre end); //Helper Function-Removes the killed pieces from the board
void check_result(int i);				  //Helper Function-Checks after every move if the game has ended and declares the winner
enum occupied_by{USER,COMP,NONE};		  //It stores the information of which Game Piece is present in a Box on the board.

class Board                  //Represents the Boxes on the Game Board and their State
{
	public:
	Centre cen;             //Centre of the box
	bool is_occupied;		//True if a piece is present on the Box
	occupied_by ocby;		//stores Type of piece present on the Box
	
	Board(int a,int b,bool isoc,occupied_by oc);		//Constructor
	Board();										//Constructor
	void toggle_state();							//Change the state from Occupied to Not Occupied and vice-versa.
};

extern Board box[8][8];									//2D array representing the Boxes on the Game Board

extern Board virt_box[8][8];								//2D array representing the Virtual Boxes on the Virtual Game Board

class Pieces										//Represents the User and Computer Pieces
{
	public:	
	Circle* c;										//Pointer to the circle visible as the User or Comp piece
	Centre cen;										//Stores the co-ordinates of the centre in i-j format
	Centre aux;										//Stores the co-ordinates of centre in x-y format
	
	Pieces(int a,int b,int r);						//Constructor
	Pieces();										//Constructor
	void move(Centre end);							//Moves the Pieces
	void virt_move(Centre end);						//Moves the Virtual Pieces
	bool kill_possible(Centre end);					//Checks if another piece can be killed simultaneously
	bool is_valid(Centre end,int n);				//Checks if a move is valid or not	
};

extern Pieces user_piece[12];								//Pieces controlled by the user	
extern Pieces comp_piece[12];								//Pieces controlled by the computer
extern Pieces virt_comp[12];								//Virtual comp pieces used in AI
extern Pieces virt_user[12];								//Virtual user pieces used in AI

void intel(Pieces &virt,Centre &cen,int &k);		//Helper Function-Tells the INTELLIGENT move
							
class Game											//Represents the overall working of the Game
{
	public:							
	void instructions();							//Provide playing instructions on startup
	void start();									//Contains the whole funtioning of the Game
	void result(bool win);							//Shows the result of the game and closes the Game
	
};

extern Game g;												//Object of Game class.			
