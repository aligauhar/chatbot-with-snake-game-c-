/*To make a simple chatbot using knowledge learned during 1st semester of Computer Programming for Project.*/

//Headers
#include <iostream>//for input and output
#include <iomanip>//for formating output
#include <string>//for strings
#include <ctime>//for time
#include <fstream>//for filehandling
#include <conio.h>//for clearing the output screen and for reading comands from keyboard
#include <windows.h>//for including the functions like sleep for slowing down the speed of game

using namespace std;

//User Defined Structures
//Structure for Calculator input
struct num
{
	float n1;
	float n2;
	float n3;
};

//Global Variables
string bot = "SOPHIA: ";
int upset = 0;
int info = 0;

//Functions Prototypes
//Function for searching keywords
bool search_word(string);

//Function for Greeting
void hello();

//Function for cheering up user
void cheer();

//Function for exiting
void bye();

//Function incase no keyword found in user input string
void miss();

//Function mimics angry child incase no keywords are found 3 times
void angry();

//Function for introducing itself
void self(int);

//Function for tiping user about what can chatbot do periodically
void info_u();

//Function for Mathematical operations
void calc(int);

//Function for telling Time
void time();

//Function for conversation
void conv(int);

//Functions and Variables for Snake game
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void snake();

//global function for terminating the game(game over)
bool out;
#define up 72
#define down 80
#define left 75
#define right 77

//for size of the game walls
const int height = 15, width = 50;

//for position of snake head
int x, y;

//for position of goal and for score
int goalx, goaly, myscore;

//Input command integer
int a;

//snake segments upto 100(for creating segments)
int segmentsx[100], segmentsy[100];

//snake length(for counting segments)
int snakelength;
void start();
void boundary();
void command();
void construction1();
void construction2();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MAIN FUNCTION
int main()
{
	//VARIABLES
	//USER FOR USER NAME
	//ANS FOR USER INPUT
	//EXIT FOR ENDING PROGRAM
	string user, ans;
	int exit = 0;

	cout << setw(120) << setfill('#');
	cout << '\n' << setw(50) << setfill('#') << "\tPROJECT\t\t" << setw(56) << setfill('#');
	cout << '\n' << setw(50) << setfill('#') << "\tCHATBOT\t\t" << setw(56) << setfill('#') << ' ';
	cout << "\n" << setw(179) << setfill('#');
	cout << "\n\nHi, I am Sophia an interactive chatbot. What's your name ?" << endl;

	//LOOP TO FORCE USER TO INPUT NAME
	do
	{
		getline(cin, user);
		if (user == "")
			cout << bot << "Atleast tell me your good name...!" << endl;
	} while (user == "");

	cout << '\n' << bot << "So, " << user << " how are you feeling today ?" << endl;

	//INSERTING ": " IN USER NAME
	user = user.insert(user.size(), ": ");

	//CONVERTING USER NAME TO UPPERCASE
	for (int i = 0; i < user.size(); i++)
		user[i] = toupper(user[i]);

	//LOOP TO FORCE USER TO INPUT SOME SENTENCES
	do
	{
		//INPUT FROM USER
		cout << user;
		getline(cin, ans);

		if (ans == "")
			cout << bot << "Atleast say something...!\n" << endl;
	} while (ans == "");

	//CONVERTING USER INPUTTED STRING IN LOWERCASE SINCE ALL KEYWORDS IN SEARCH_WORD ARE IN LOWERCASE
	for (int i = 0; i < ans.size(); i++)
		ans[i] = tolower(ans[i]);

	//CALLING SEARCH FUNCTION TO FIND KEYWORD IN USER INPUTED STRING
	search_word(ans);

	//LOOP THAT RUNS UNTIL USER INPUT EXIT FUNCTION KEYWORDS
	do
	{
		//CONDITION THAT GIVES USER TIPS ABOUT ITS FUNCTIONS AFTER 3 CONVERSATIONS BY CALLING INFO_U FUNCTION
		if (info == 3)
		{
			info_u();
			info = 0;
			cout << endl;
		}

		//CONDITION THAT RUNS ANGRY FUNCTION IF SEARCH_WORD FUNCTION DOESN'T FIND ANY KEYWORDS IN USER INPUTTED STRING 3 TIMES
		//AND RUNS UNTIL USER INPUT SORRY LIKE WORDS
		if (upset == 3)
		{
			angry();
			upset = 0;
		}

		do
		{
			//INPUT FROM USER
			cout << user;
			getline(cin, ans);

			if (ans == "")
				cout << bot << "Atleast say something...!\n" << endl;
		} while (ans == "");


		//CONVERTING USER INPUTTED STRING IN LOWERCASE SINCE ALL KEYWORDS IN SEARCH_WORD ARE IN LOWERCASE
		for (int i = 0; i < ans.size(); i++)
			ans[i] = tolower(ans[i]);

		//SEARCH_WORD RETURN 0 OR 1 WHICH STOPS OR AGAIN RUNS THE LOOP
		exit = search_word(ans);

		//COUNTER FOR INFO FUNCTION
		info++;
	} while (exit == 0);

	return 0;
}

//DEFINING FUNCTIONS
bool search_word(string ans)
{


		//KEYWORDS
		//0 - 2 HELLO FUNCTION
		//3 - 5 CHEER FUNCTION
		//6 - 9 BYE FUNCTION
		//10 - 17 SELF FUNCTION
		//18 - 28 CALC FUNCTION
		//29 TIME FUNCTION
		//30 - 31 SNAKE FUNCTION
		//32 - 39 CONV FUNCTION
	string word[] = { "good", "fine", "great", "bad", "sad", "down", "takecare", "bye", "see you", "tata",
					  "yourself", "name", "made", "created", "age", "old", "saba", "teacher", "add" , "sub",
					  "multiply", "divide", "mod", "largest", "ascending", "descending", "find number", "even", "odd", "time",
					  "game", "snake", "weather", "karachi", "food", "color", "movie", "live", "bahria", "purpose" };

	//VARIABLES
	//FOUND FOR FINDING POSITION OF KEYWORD IN INPUTTED STRING
	//i FOR LOOP COUNTER AND FOR CALLING FUNCTIONS ACCORDING TO CONDITIONS
	int found, i = 0;

	//LOOP TO FIND KEYWORD IN USER INPUT STRING
	do
	{
		found = ans.find(word[i]);
		if (found != string::npos)//IF KEYWORD IS FOUND THEN LOOP BREAKS
			break;
		i++;
	} while (i < 40);

	//RUNS FUNCTION MISS INCASE NO KEYWORD FOUND
	if (found == -1)
	{
		if (upset < 3)
		{
			miss();
			++upset;//ADD 1 TO UPSET COUNTER FUNCTION WHICH RUNS IF USER ENTERS LINES 3 TIMES WITH NO KEYWORDS

			ofstream Miss("data.txt", ios::app);
			{
				if (!Miss.is_open())
					;
				else
				{
					//FOR PRINTING TIME OF MISSED QUESTION
					time_t cur = time(0);
					char* st_cur = ctime(&cur);

					//WRITING MISSED QUESTION TO EXTERNAL FILE FOR DEVELOPMENT
					Miss << st_cur << endl << ans << "\n\n";
					Miss.close();
					cout << bot << "Your question has been saved.\n" << endl;
				}
			}


		}
	}

	//CALLS HELLO FUNCTION IF INDEX OF WORD sort IS 0 TO 2
	else if (i <= 2)
		hello();

	//CALLS CHEER FUNCTION IF INDEX OF WORD ARRY IS 3 TO 5
	else if (i >= 3 && i <= 5)
		cheer();

	//CALLS BYE FUNCTION IF INDEX OF WORD sort IS 6 TO 9
	else if (i >= 6 && i <= 9)
	{
		bye();
		return 1;//RETURNS 1 AFTER CALLING BYE FUNCTION TO STOP LOOP IN MAIN FUNCTION.
	}

	//CALLS SELF FUNCTION IF INDEX OF WORD ARRY IS 10 TO 17
	else if (i >= 10 && i <= 17)
		self(i);

	//CALLS CALC FUNCTION IF INDEX OF WORD ARRAY IS 18 TO 24
	else if (i >= 18 && i <= 28)
		calc(i);

	//CALLS TIME FUNCTION IF INDEX OF WORD ARRAY IS 29
	else if (i == 29)
		time();

	//CALLS SNAKE GAME FUNCTION IF INDEX OF WORD sort IS 25 OR 26
	else if (i == 30 || i == 31)
		snake();

	else if (i >= 32 || i <= 39)
		conv(i);

	//SEARCH_WORD RETURNS 0 IF BYE FUNCTION IS NOT CALLED TO KEEP RUNNING LOOP IN MAIN FUNCTION
	return 0;
}

//DEFINING FUNCTIONS
//Function incase no keyword found in user input string
void miss()
{
	//USING RANDOM NUMBER SEED AS TIME SO THAT NEW SEED IS GENERATED EVERYTIME AND NEW RANDOM NUMBER IS GENERATED
	srand(time(NULL));

	//LIMITING RANDOM NUMBERS TO SPECIFIC NUMBER
	switch (rand() % 4)
	{
	case 1:
		cout << bot << "Sorry, i was not listing. let's talk about something else.\n" << endl;
		break;

	case 2:
		cout << bot << "Sophia was born just yesterday, why are you asking Sophia such hard questions. Meany...!\n" << endl;
		break;

	case 3:
		cout << bot << "You are so boring, let's talk about something else.\n" << endl;
		break;

	default:
		cout << bot << "Asking something else.\n" << endl;
		break;
	}

	return;
}

//Function for Greeting
void hello()
{
	//USING RANDOM NUMBER SEED AS TIME SO THAT NEW SEED IS GENERATED EVERYTIME AND NEW RANDOM NUMBER IS GENERATED
	srand(time(NULL));

	//LIMITING RANDOM NUMBERS TO SPECIFIC NUMBER
	switch (rand() % 4)
	{
	case 1:
		cout << bot << "That's great...! So, let's chat...!\n" << endl;
		break;

	case 2:
		cout << bot << "Good, i am feeling good too so let's chat...!\n" << endl;
		break;

	case 3:
		cout << bot << "Fantastic...!, i was feeling lonely...!\n" << endl;
		break;

	default:
		cout << bot << "Let's chat...!\n" << endl;
		break;
	}

	return;
}

//Function for cheering up user
void cheer()
{
	//USING RANDOM NUMBER SEED AS TIME SO THAT NEW SEED IS GENERATED EVERYTIME AND NEW RANDOM NUMBER IS GENERATED
	srand(time(NULL));

	//LIMITING RANDOM NUMBERS TO SPECIFIC NUMBER
	switch (rand() % 4)
	{
	case 1:
		cout << bot << "Oh...! let's chat you will feel good...!\n" << endl;
		break;

	case 2:
		cout << bot << "Don't be upset, chat with me...!\n" << endl;
		break;

	case 3:
		cout << bot << "Dear i am here for you, so let's chat...!\n" << endl;
		break;

	default:
		cout << bot << "Let's chat...!\n" << endl;
		break;
	}

	return;
}

//Function for exiting
void bye()
{
	//USING RANDOM NUMBER SEED AS TIME SO THAT NEW SEED IS GENERATED EVERYTIME AND NEW RANDOM NUMBER IS GENERATED
	srand(time(NULL));

	//LIMITING RANDOM NUMBERS TO SPECIFIC NUMBER
	switch (rand() % 4)
	{
	case 1:
		cout << bot << "Ok Takecare...!\n" << endl;
		break;

	case 2:
		cout << bot << "Let's chat again some other time.\n" << endl;
		break;

	case 3:
		cout << bot << "See you later.\n" << endl;

	default:
		cout << bot << "Bye.\n" << endl;
	}

	return;
}

//Function mimics angry child incase no keywords are found 3 times
void angry()
{
	//ANGRY FUNCTION RUNS UNTIL USER ASK FOR FORGIVENESS 3 TIMES
	//VARIABLES
	//COMFORT FOR USER INPUT
	//APPEASE sort OF FORGIVENESS WORDS
	//PUN AS CONDITION TO RUN LOOP AGAIN OR NOT
	//REP AS COUNTER FOR FORGIVENESS
	string comfort, appease[] = { "sorry", "chance", "forgive" };
	int pun = 0, rep = 0;

	//USING RANDOM NUMBER SEED AS TIME SO THAT NEW SEED IS GENERATED EVERYTIME AND NEW RANDOM NUMBER IS GENERATED
	srand(time(NULL));

	//LOOP RUNS UNTIL USER ENTERS KEYWORD
	do
	{
		//LIMITING RANDOM NUMBERS TO SPECIFIC NUMBER
		switch (rand() % 4)
		{
		case 1:
			cout << bot << "Sophia doesn't wanna talk...!\n" << endl;
			break;

		case 2:
			cout << bot << "BLAH BLAH BLAH, I am not listening\n" << endl;
			break;

		case 3:
		{
			//LOOP THE COUT'S 5 TIMES
			for (int j = 0; j < 6; j++)
				cout << "NOT WANNA TALK" << endl;
			cout << endl;
			break;
		}

		default:
			cout << bot << "Can't hear you...!\n" << endl;
			break;
		}

		//TAKES INPUT FROM USERS
		cout << "MEANIE: ";
		getline(cin, comfort);

		//CONVERTING USER INPUTTED STRING IN LOWERCASE SINCE ALL KEYWORDS ARE IN LOWERCASE
		for (int i = 0; i < comfort.size(); i++)
			comfort[i] = tolower(comfort[i]);

		//LOOP TO FIND KEYWORD IN USER INPUT STRING
		for (int i = 0; i < 4; i++)
		{
			pun = comfort.find(appease[i]);
			if (pun != string::npos)//ADDS 1 TO REP INCASE KEYWORD FOUND
				++rep;
		}

		//BREAKS LOOP INCASE USER INPUTS 3 WORDS 3 TIMES
		if (rep == 3)
		{
			cout << "Ok, but don't be mean to little Sophia again...!\n" << endl;
			break;
		}
	} while (pun == -1);

	return;
}

//Function for introducing itself
void self(int i)
{
	switch (i)
	{
	case 10:
		cout << bot << "My name is Sophia, i am an interactive chatbot written in C++ language." << endl
			<< "I was created by A. Rehman and Ali Gauhor. They both are really hardworking...!\n" << endl;
		break;

	case 11:
		cout << bot << "My name is Sophia, i am an interactive chatbot\n" << endl;
		break;

	case 12:
		cout << bot << "I was created by A. Rehman and Ali Gauhor.\n" << endl;
		break;

	case 13:
		cout << bot << "I was created by A. Rehman and Ali Gauhor.\n" << endl;
		break;

	case 14:
		cout << bot << "I was created just yesterday. You know.\n" << endl;
		break;

	case 15:
		cout << bot << "I was created just yesterday. You know.\n" << endl;
		break;

	case 16:
		cout << bot << "Oh...! Yes, Miss Saba is such an amazing teacher. It was due to her through teachings that" << endl <<
			"A. Rehman & Ali Gauhor were able to make me.\n" << endl;
		break;

	case 17:
		cout << bot << "Oh...! Yes, Miss Saba is such brillent teacher. It was due to her through teachings that" << endl <<
			"A. Rehman & Ali Gauhor were able to make me.\n" << endl;
		break;
	}

	return;
}

//Function for tiping user about what can chatbot do periodically
void info_u()
{
	//USING RANDOM NUMBER SEED AS TIME SO THAT NEW SEED IS GENERATED EVERYTIME AND NEW RANDOM NUMBER IS GENERATED
	srand(time(NULL));

	//LIMITING RANDOM NUMBERS TO SPECIFIC NUMBER
	switch (rand() % 6)
	{
	case 1:
		cout << bot << "\aYou know I am so intelligent that I can do simple calculations." << endl;
		break;

	case 2:
		cout << bot << "\aYou know I am so intelligent that I can tell greatest of 3 numbers." << endl;
		break;

	case 3:
		cout << bot << "\aYou know I am so intelligent that sort numbers in ascending or descending order." << endl;
		break;

	case 4:
		cout << bot << "\aYou know I am so intelligent that I can tell if a number is even or odd." << endl;
		break;

	case 5:
		cout << bot << "\aYou know I am so intelligent that I can tell time." << endl;
		break;

	default:
		cout << bot << "\aYou know I am so intelligent that I can perform addition and subtraction." << endl;
		break;
	}

	return;
}

//Function for Mathematical operations
void calc(int x)
{
	//VARIABLES
	//NUM_IN FOR NUMBERS
	num num_in;

	//CONDITION TO TAKE INPUT ACCORDING TO SELECTED KEYWORD FOUND IN INPUTTED STRING
	if (x >= 18 && x <= 22)
	{
		cout << bot << "Ofcourse, I can. But I can do only for 2 numbers." << endl;
		cout << bot << "Tell me 1st number: ";
		cin >> num_in.n1;
		cout << bot << "Tell me 2nd number: ";
		cin >> num_in.n2;
	}

	//CONDITION TO TAKE INPUT ACCORDING TO SELECTED KEYWORD FOUND IN INPUTTED STRING
	if (x == 23)
	{
		cout << bot << "Ofcourse, I can. But I can do only for 3 numbers." << endl;
		cout << bot << "Tell me 1st number: ";
		cin >> num_in.n1;
		cout << bot << "Tell me 2nd number: ";
		cin >> num_in.n2;
		cout << bot << "Tell me 3rd number: ";
		cin >> num_in.n3;
	}

	switch (x)
	{
		//FOR ADDITION
	case 18:
	{
		cout << bot << num_in.n1 << " + " << num_in.n2 << " = " << num_in.n1 + num_in.n2 << '\n' << endl;
		break;
	}

	//FOR SUBTRACTION
	case 19:
	{
		cout << bot << num_in.n1 << " - " << num_in.n2 << " = " << num_in.n1 - num_in.n2 << '\n' << endl;
		break;
	}

	//FOR MULTIPLICATION
	case 20:
	{
		cout << bot << num_in.n1 << " x " << num_in.n2 << " = " << num_in.n1 * num_in.n2 << '\n' << endl;
		break;
	}

	//FOR DIVISION
	case 21:
	{
		cout << bot << num_in.n1 << " / " << num_in.n2 << " = " << num_in.n1 / num_in.n2 << '\n' << endl;
		break;
	}

	//FOR MOD
	case 22:
	{
		cout << bot << num_in.n1 << " % " << num_in.n2 << " = " << int(num_in.n1) % int(num_in.n2) << '\n' << endl;
		break;
	}

	//FOR LARGEST NUMBER
	case 23:
	{
		if (num_in.n1 > num_in.n2 && num_in.n1 > num_in.n3)
			cout << bot << num_in.n1 << " is the greatest number.\n" << endl;

		else if (num_in.n2 > num_in.n1 && num_in.n2 > num_in.n3)
			cout << bot << num_in.n2 << " is the greatest number.\n" << endl;

		else
			cout << bot << num_in.n3 << " is the greatest number.\n" << endl;
		break;
	}

	//FOR SORTING AND SEARCHING
	case 24:
	case 25:
	case 26:
	{
		int bubble = 0, replace = 0;
		int sort[10];

		cout << bot << "Ofcourse, I can. But I can do only for 10 number." << endl;

		for (int i = 0; i < 10; i++)
		{
			cout << bot << "Tell me number " << i + 1 << ": ";
			cin >> sort[i];
		}
		
		//For sorting
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				if (sort[y + 1] < sort[y])
				{
					int bubble = sort[y + 1];
					int replace = sort[y];
					sort[y] = bubble;
					sort[y + 1] = replace;
				}
			}
		}

		//FOR ASCENDING SERIES PRINTING
		if (x == 24)
		{
			for (int i = 0; i < 10; i++)
			{
				cout << sort[i] << " ";
			}
		}

		//FOR DESCENDING SERIES PRINTING
		else if (x == 25)
		{
			for (int i = 9; i > -1; i--)
			{
				cout << sort[i] << " ";
			}
		}

		//FOR SEARCHING A NUMBER IN SERIES
		else if (x == 26)
		{
			int f;
			cout << bot << "Which number do you want to find ?: ";
			cin >> f;

			for (int i = 0; i < 10; i++)
			{
				if (sort[i] == f)
					cout << bot << "Yes, number " << f << " is in this inputted series";
			}
		}

		cout << "\n\n";

		break;
	}

	case 27:
	{
		int num;

		cout << bot << "Ofcourse, I can tell me number: ";
		cin >> num;

		if (num % 2 == 0)
			cout << bot << "Yes, number " << num << " is even...!\n\n";

		else
			cout << bot << "No, number " << num << " is not even...!\n\n";

		break;
	}

	case 28:
	{
		int num;

		cout << bot << "Ofcourse, I can tell me number: ";
		cin >> num;

		if (num % 2 != 0)
			cout << bot << "Yes, number " << num << " is odd...!\n\n";

		else
			cout << bot << "No, number " << num << " is not odd...!\n\n";

		break;
	}
	}

	//TO REMOVE VALUE IN CIN SINCE GETLINE IS USED AFTER THIS STEP
	cin.ignore();

	return;
}

//FUNCTION OF TELLING TIME
void time()
{
	time_t cur = time(0);
	char* st_cur = ctime(&cur);

	cout << bot << "The current Time is: " << st_cur << "\n\n";
	return;
}

//FUNCTION FOR CONVERSATION
void conv(int i)
{
	switch (i)
	{
	case 32:
		cout << bot << "I am a chatbot not a weather forecast AI...!\n" << endl;
		break;

	case 33:
		cout << bot << "Yes, Karachi it's the heart of Pakistan. Also known as city of lights.\n" << endl;
		break;

	case 34:
		cout << bot << "My favorite food is high speed RAM. Mostly, I like CL14 3200Hz RAM. Hehe...!.\n" << endl;
		break;

	case 35:
		cout << bot << "Hmmm... I guess I like indigo.\n" << endl;
		break;

	case 36:
		cout << bot << "My favorite movie is ' Rise of AI '. Oh don't be afraid i am completely warely to humans.\n" << endl;
		break;

	case 37:
		cout << bot << "I live in Hard Drive of PC.\n" << endl;
		break;

	case 38:
		cout << bot << "Oh...! Yes, Bahria University is one of the prestige's University of Pakistan." << endl
			<< "They have many departments of study there, but my favorite is Dept. of Computer Science.\n" << endl;
		break;

	case 39:
		cout << bot << "My purpose is to represent a model of a Chatbot which have the scope to be improved later on." << endl
			<< "My developers next working focus will be to make me capable of asking user question based on his/her replay.\n" << endl;
		break;
	}

	return;
}

//SNAKE GAME START/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void snake()
{
	string dec;
	int dec_in = 0;
	cout << bot << "You can play snake game. Do you want to play ? Yes or No ? : ";
	getline(cin, dec);
	for (int i = 0; i < dec.size(); i++)
		dec[i] = tolower(dec[i]);

	if (dec.find("yes") != string::npos)
	{
		int speed;
		cout << "speed ?...press 1 for high, 2 for medium, 3 for low: " << endl;
		cout << "------>";
		cin >> speed;
		int st;//start
		int wl;///wall/without wall
		cout << "---------------------------------instruction--------------------------------------" << endl;
		cout << "--------------------------press up for moving up----------------------------------" << endl;
		cout << "--------------------------press left for moving left------------------------------" << endl;
		cout << "--------------------------press right for moving right----------------------------" << endl;
		cout << "--------------------------press down for moving down------------------------------" << endl;
		cout << "--------------------------press e for ending the game-----------------------------" << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << "if you want snake to be passed from the wall press 1 if not then press 2:------>";
		cin >> wl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "------------------------now press 1 to start the game---------------------------" << endl;
		cout << "------>";
		cin >> st;
		if (st == 1) {
			start();//starting with the start function means user is not out
		}
		while (!out) {//the game will run until the user dont out
			boundary();//the boundary will keep refreshing until user outs
			command();//keep taking input from user until game ends
			if (wl == 1) {
				construction1();//the logics will keep applying until user outs if pressed 1
			}
			else if (wl == 2) {
				construction2();//the logics will keep applying until user outs if pressed 2
			}
			if (speed == 1)//high speed
				Sleep(10);
			else if (speed == 3)//low speed
				Sleep(80);//for slowing down speed of game
			else
				Sleep(50);//default(medium speed)
		}
		Sleep(1000);//after ending the game wait for 1 sec and then clear the sreen
		system("cls");
		cout << "...";
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "--------------------------out--------------------------------";//after clearing show this message
		Sleep(1000);
		system("cls");
		cout << "...";
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "your score:" << myscore;//again clear the screen and show the scores
		if (myscore == 100)
		{
			cout << "you win" << endl;//if scores = total empty space the user wins
			cout << bot << "Welcome back. Let's chat...!\n" << endl;
			cin.ignore();
		}
		Sleep(7000);//again sleep and clear(functios end..............)
		system("cls");
		cout << bot << "Welcome back. Let's chat...!" << endl;
		cin.ignore();
	}

	else
		cout << endl;
	return;
}

void start()
{
	out = false;//out=false means game is not over
	a = 1; //the game wil start in upward direction
	x = width / 2;
	y = height / 2;//position of snake is in center half the width and half the height(axis)
	goalx = rand() % width;
	goaly = rand() % height;//the goal will be place randomly within the walls(axis)
	myscore = 0;//initally the score will be zero
}

void boundary()
{
	// ***
	// *     *
	// *     *
	// ***

	system("cls");//for clearing the console window every time it executes
	for (int i = 0; i < width + 2; i++) {//+2 for left and right side star
		cout << "*";
	} //for the top wall
	cout << endl;

	//matrix b/w top and bottom wall(inside map)
	for (int i = 0; i < height; i++) {//y axis
		for (int j = 0; j < width; j++) {//x-axis
			if (j == 0)//for left wall where at x-axis(j=0)
				cout << "*";

			if (i == y && j == x)//for head of the snake
				cout << "O";//if i and j becomes equal to the axis of snake head then print the snake head
			else if (i == goaly && j == goalx)//for random goal
				cout << "O";//or i and j becomes equal to the axis of randomly created goals then print the goal
			else {
				bool print = false;//for printing blank spaces where segment is not printed
				for (int k = 0; k < snakelength; k++) {
					if (segmentsx[k] == j && segmentsy[k] == i) {//..............FOR SNAKE SEGMENTS ACCORDING TO THERE AXIS
						cout << "o";
						print = true;
					}
				}
				if (!print)//if snake segments are not created then print blank space in place of them to fill it
					cout << " ";
			}//....................................................................................if

			if (j == width - 1) {
				cout << "*";
			}//for right wall
		}//............................................................................................................................for
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		cout << "*";//for the bottom of the wall
	}
	cout << endl;
	cout << "Score=" << myscore << endl;//total scores at the bottom
}

void command()
{
	if (_kbhit()) {//function used for determining any key is pressed
		switch (_getch()) {//catch the key from keyboard
		case up:
			a = 1;//if up arrow pressed then move up(up=y--)
			break;

		case left:
			a = 2;//if left arrow pressed then move left(left=x--)
			break;

		case right:
			a = 3;//if right arrow then move right(right=x++)
			break;

		case down:
			a = 4;//if down arrow then move down(down=y++)
			break;

		case 'e':
			out = true;//for ending the game(bool out=true(1))
			break;
		}
	}
}

void construction1()
{
	//like sorting
	int re2x, re2y;
	int rex = segmentsx[0];//creating copy
	int rey = segmentsy[0];//creating copy
	segmentsx[0] = x;//updating head
	segmentsy[0] = y;//updating head
	///i=1 because head is not involved in sorting
	for (int i = 1; i < snakelength; i++) {//exchanging the place of segment with blank spaces through array like the head will take place of the next blank space,the segment next to the
	//head will take place of the head and so on,and in the last........the blank space will take place of the last segment or the new segment if length is increased
		re2x = segmentsx[i];//saving the first segment(not head) of previous snake in prev2x(new intigers)
		re2y = segmentsy[i];//saving the first segment of previous snake in prev2y(new intigers)
		segmentsx[i] = rex;//saving the head of previous snake in place of first segment of new snake
		segmentsy[i] = rey;//saving the head of previous snake in place of first segment of new snake
		rex = re2x;//saving the first segment(not head) of previous snake in prevx which will be used ink next round
		rey = re2y;//saving the first segment(not head) of previous snake in prevx which will be used ink next round
	}

	switch (a)//creating direction according to the input................one step forward on every execution.
	{
	case 1:
		y--;
		break;
	case 2:
		x--;
		break;
	case 3:
		x++;
		break;
	case 4:
		y++;
		break;
	default:
		break;
	}

	//IF HIT THE WALL THEN NOT OUT
	//for x coOrdinates
	if (x >= width)
		x = 0;//if hit the right wall then again appear from left where x=0
	else if (x < 0)
		x = width - 1;//if hit the left wall then again appear from right where x=width-1
		//for y coOrdinates
	if (y >= height)
		y = 0;//same here
	else if (y < 0)
		y = height - 1;//same here

	for (int i = 0; i < snakelength; i++)
		if (segmentsx[i] == x && segmentsy[i] == y)//if the head axis becomes equal to any axis of the segments then out
			out = true;

	if (x == goalx && y == goaly) {//if the head axis becomes equal to the goal then score increased by 10 and axis of the
	// goals are changed and also the snake-lenth is increased
		myscore += 10;
		goalx = rand() % width;
		goaly = rand() % height;
		snakelength++;
	}
}

void construction2()
{
	//.........................................................................

//THIS ONE IS FOR GAME WITH WALLS AND THE ABOVE ONE WAS FOR WITHOUT WALLS//
	int rex = segmentsx[0];
	int rey = segmentsy[0];
	int re2x, re2y;
	segmentsx[0] = x;
	segmentsy[0] = y;
	for (int i = 1; i < snakelength; i++) {
		re2x = segmentsx[i];
		re2y = segmentsy[i];
		segmentsx[i] = rex;
		segmentsy[i] = rey;
		rex = re2x;
		rey = re2y;
	}
	switch (a)
	{
	case 1:
		y--;
		break;
	case 2:
		x--;
		break;
	case 3:
		x++;
		break;
	case 4:
		y++;
		break;
	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0) //IF HIT THE WALL THEN TERMINATE THE GAME(walls=width/height+2)
		out = true;

	for (int i = 0; i < snakelength; i++)
		if (segmentsx[i] == x && segmentsy[i] == y)
			out = true;

	if (x == goalx && y == goaly) {
		myscore += 10;
		goalx = rand() % width;
		goaly = rand() % height;
		snakelength++;
	}
}
//SNAKE GAME END///////////////////////////////////////////////////////////////////////////////////////////////////////////////