
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
#define white_space  currentStreamCharacter == '\b' ||currentStreamCharacter == '\n' || currentStreamCharacter == '\r' || currentStreamCharacter == '\t' || currentStreamCharacter == '\"' || currentStreamCharacter == '\'' || currentStreamCharacter == ',' || currentStreamCharacter == ';' || currentStreamCharacter == '.' || currentStreamCharacter == ';' || currentStreamCharacter == ':' || currentStreamCharacter == '?' || currentStreamCharacter == '!' || currentStreamCharacter == '(' || currentStreamCharacter == ')' || currentStreamCharacter == '{' || currentStreamCharacter == '}'
using namespace std;
int promntUserForId();
const string getPath();
void handleInputFailure(fstream &in); //These functions might be used to handle input failture idk.
void handleInputFailure(fstream &in);
void openFile(string &path2, fstream &in);
void searchForId(int &id, fstream &in);



int main() 
{
	int id = promntUserForId();//It's the file name.
    string path = getPath();
    fstream file;//File header
	openFile(path, file); // Gets file name & opens file
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

const string getPath()
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');//Ignore any junk left from getting the id.
	//string var;
    //getline(cin, var);
	string path;//file path
	cout << "User please input your file here: ";//Promnt line
    cin >> ws;
    getline(cin, path);//Get path from user
    //path[path.end()+1]= ' ';
	return path;
}

void openFile(string & path, fstream& in) //Gets file from user
{
	in.open(path, ios::in | ios::out);
	if (!in)// Ask user to input file path again then exit if file can't open.
	{
		in.clear();
		in.ignore(numeric_limits<streamsize>::max(), '\n');
		openFile(path, in);
		return;
	}
}

void searchForId(int& id, fstream& in)
{
    int validId;
    //char currentStreamCharacter = in.get();
    string word;
    while (!in.eof()) {
        in >> validId;
        if (validId == id) // Gets the right word if id is correct
        {
            //   word += currentStreamCharacter;
            in >> word;
            break;
        }
    }

	if (validId != id)
	{
		cout << "ID doesn't exist, so what's the the name? : ";
		cin >> word;
		in.clear();
		in << '\n';
        in << id;
        in << "     " + word;
	}
	else
		cout << "The word " + word + " was assigned to this id " + to_string(id) + ".";
}

