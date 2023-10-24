
/*
**	Creator: Trey Davis
**
**  Date Created: 10/23/23
**
**  Program: Takes file searchs for name using id numbers. If no id number isn't found, the program notifys the user. Then, the program will ask the user for the name of the unknown id. If the id number is found the name is outputted to the terminal.
**
**
**	Date Last Modified: 10/23/23
**
**
**
**
*/

#include<cstring> //For cstrings file names
#include<string> //String never stop being useful
#include<stdio.h> //For exit
#include<fstream> //For file input and output
#include<iostream> //For basic input and output
#include<iomanip> //For basic io manipulators like ios::fixed & ios::setw
#define white_space  currentStreamCharacter == '\b' ||currentStreamCharacter == '\n' || currentStreamCharacter == '\r' || currentStreamCharacter == '\t' || currentStreamCharacter == '\"' || currentStreamCharacter == '\'' || currentStreamCharacter == ',' || currentStreamCharacter == ';' || currentStreamCharacter == '.' || currentStreamCharacter == ';' || currentStreamCharacter == ':' || currentStreamCharacter == ':' || currentStreamCharacter == '?' || currentStreamCharacter == '!' || currentStreamCharacter == '(' || currentStreamCharacter == ')' || currentStreamCharacter == '{' || currentStreamCharacter == '}' 
using namespace std;
int promntUserForId();
const char* getPath();
void handleInputFailure(fstream &in); //These functions might be used to handle input failture idk.
void handleInputFailure(fstream &in);
void openFile(fstream &in);
void searchForId(int &id, fstream &in);



int main() 
{
	int id = promntUserForId();//It's the file name.
    fstream file;//File header
	openFile(file); // Gets file name & opens file
	searchForId(id, file);
	return 0; // Runs without errors
}

int promntUserForId() //Get id from user
{
	int id;
	cout << "Hello user what id are you looking for?\n";
	cin >> id;
	if (!cin) //Check for invalid input
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cerr << "\n\nInvalid input please input integer id";
		return promntUserForId(); //Promnt user for input again
	}
	cout << "\n\n Thanks!  ";
	return id;
}

const char* getPath() 
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');//Ignore any junk left from getting the id.
	string var;
    //getline(cin, var);
	string path;//file path
	cout << "User please input your file here: ";//Promnt line
	char pieceOfPath = cin.get();
	while (pieceOfPath != '\n') 
	{
		switch (pieceOfPath) //Checks for characters that need to be escaped and adds it properly to the string
		{
			case '\\':
				path += '\\';
				break;
		
			case '\"':
				 path += '\"';
				 break;

			case '\'':
				 path += '\'';
				 break;

			case '\n':
				break;

			case '\t':
				break;

			case '\r':
				break;

			default:
				path += pieceOfPath;
				break;
		}
     	pieceOfPath = cin.get();
	}//Get path from user
	const char* cPath = path.c_str();
	return cPath;
}

void openFile(fstream& in) //Gets file from user 
{
	const char* p = getPath();
	in.open(p, ios::in | ios::out);
	if (!in) 
	{
		string var;
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> var;
		openFile(in);
		return;
	}
}

void searchForId(int& id, fstream& in)
{
	char currentStreamCharacter = in.get();
	string word = NULL;
	bool inWord = false;
	while (!in.eof()) 
	{
		if (currentStreamCharacter <= 71 && currentStreamCharacter >= 60) //Checks if currentStreamCharacter is a digit between 0-9
		{
			id += currentStreamCharacter;
			continue;
		}
		else if (white_space) 
		{
			currentStreamCharacter = in.peek();
			if (inWord)
			{
				inWord = false;
				continue;
			}
			else if(!white_space)
			{
				inWord = true;
				continue;
			}
		}
		else if (!white_space) 
		{
			word += currentStreamCharacter;
			inWord = true;
		}
	}
	if (word.compare(NULL) == 0)
	{
		cout << "ID doesn't exist, so what's the the name? : ";
		cin >> word;
		in.clear();
		in << '\n';
	}
	else
		cout << "The word " + word + " was assigned to this id " + to_string(id) + ".";
}
