
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
    file.close();
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
		cerr << "Invalid input please input integer id\n\n";
		return promntUserForId(); //Promnt user for input again
	}
	cout << " \n\nThanks! ";
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
    //  char currentStreamCharacter = in.get();
    string word, dummy;
    char choice = 'y';// This is the choice for if the user wants to continue.
    while (tolower(choice) == 'y') // Regulates possible user choices
    {
        while (!in.eof())
        {
            in >> validId;
            bool n = !in;
            if (!in)
                in.clear();
            if (validId == id) // Gets the right word if id is correct
            {
                //   word += currentStreamCharacter;
                in >> word;
                if (!in) {
                    in.clear();
                    in.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            in >> dummy;
            //  currentStreamCharacter = in.get();
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
        bool choosing = true;//Represents the time when someone is choosing y or n.
        while(choosing)
        {
            cout << "\n\nDo you want to continue searching (y/n)?";
            cin >> choice;
            tolower(choice);
            if (choice != 'y' && choice != 'n' || !cin || cin.peek() != '\n') // If user inputs invalid choice...
            {
                cerr << "Invalid input please input either y or n." << endl << endl;
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if(choice == 'y')
            {
                choosing = false;
            }

            else if(choice == 'n')
            {
                return;
            }
        }
        in.clear();
        in.seekg(ios::beg);
        id = promntUserForId();
    }
}
