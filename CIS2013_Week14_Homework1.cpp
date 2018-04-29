#include<iostream>
#include<string>

using namespace std;

typedef unsigned char* ByteArray;

class Game 
{
private:
	string name;
	int score = 0;
public:
	//Constructor that sets the game name
	Game(string b)
	{		
		name = b;
	}

	void setName(string b)
	{
		name = b;
	}

	string getName()
	{
		return name;
	}
	void setScore()
	{
		score++;
	}
	int getScore()
	{
		return score;
	}

};

class MineSweeper : public Game
{ 
private:
	int board_size;
	int x, y;// width and heights
	ByteArray *selected_squares;
	int* bomb_sq;
	int mines_amount;
public:
	

	MineSweeper(string name, int width, int height, int mines_count) : Game(name) 
	{
		x = width;
		y = height;
		board_size = x*y;
		mines_amount = mines_count;
		selected_squares = new ByteArray[height];
		
		for (int i = 0; i < height; i++)
		{			
			unsigned char *t = new unsigned char[width];
			for (int j = 0; j < width; j++)
			{
				t[j] = ' ';
			}
			selected_squares[i] = t;
		}

		//generate bombs 
		bomb_sq = new int[mines_count * 2];// double, because we need 2 coordinates for each mine
		int mx, my; // generated coordinates
		for (int n = 0; n < mines_count * 2; n += 2)
		{
			mx = rand() % x;
			my = rand() % y;

			while (1) 
			{
				int i;
				for (i = 0; i < n; i += 2) 
				{
					//if mine already placed here -  randomize one more time
					if (bomb_sq[i] == mx && bomb_sq[i + 1] == my) // coordinates go after each other in the array
					{
						mx = rand() % x;
						my = rand() % y;
						break;
					}
				}
				if (i == n) //all mines are planted - get out of the loop
					break;
			}

			// coordinates of mines go after each other in the array
			bomb_sq[n] = mx;
			bomb_sq[n + 1] = my;
		}
	}


	
	void print() {

		cout << "  ";
		for (int a = 0; a < x; a++)
		{
			cout << a << ' ';
		}
		cout << endl;

		for (int i = 0; i < y; i++)
		{
			cout << i << ' ';
			for (int j = 0; j < x;j++)
			{
				cout << selected_squares[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}

	bool getSquare(int x, int y) 
	{
		 
		int n;
		for ( n = 0; n < mines_amount * 2; n += 2)
		{
			if (bomb_sq[n] == x && bomb_sq[n + 1] == y) //bomb!
			{
				//mark all bombs on the field with '*' and current bomb as '!'
				for (int i = 0; i < mines_amount * 2; i += 2)
				{
					int w = bomb_sq[i];
					int h = bomb_sq[i+1];
					selected_squares[h][w] = '*';
				}
				selected_squares[y][x] = '!';
				return true;
			}
		}

		selected_squares[y][x] = '.';
		setScore();
		return false;
	
	}
};


int main() {
	string name;
	int width, height;
	int x, y;
	int mines_count;
	//Game game;
	cout << "			********************************************************" << endl;
	cout << " 					What is the game you wanna play? 		";
	cin >> name;
	cout << "			********************************************************" << endl;
	cout << ' ' << endl;
	cout << "Enter the board size :\n";
	cout << "width: ";
	cin >> width;
	cout << endl;
	cout << "height: ";
	cin >> height;
	cout << "Enter amount of mines (not more than 10)for your field: " << endl;
	cin >> mines_count;
	cout << endl;
	
	MineSweeper minesweeper (name, width, height, mines_count);
	
	cout << "			********************************************************" << endl;
	cout << "					Playing " << minesweeper.getName () << endl;
	cout << "			********************************************************" << endl;
	minesweeper.print ();
	
	while (true)
	{
		cout << "Let's play! Enter coordinates : "<<endl; 
		cout << "x ="; 
		cin >> x;
		cout << endl;
		cout << "y =";
		cin >> y;
		cout << endl;
		
		
		if (y >  height || x >  width) {
			
			cout << "Values are not within the field, try again! " << endl;
		} else
	
		if (minesweeper.getSquare (x, y)) {	
				minesweeper.print();
				
				cout << "			********************************************************" << endl;
				cout << "					Game over! Your score " << minesweeper.getScore() << '.'<<  endl;
				cout << "			********************************************************" << endl;
				break;
			}
	
		minesweeper.print ();
	}
	//cin >> name;
	return 0;
}
