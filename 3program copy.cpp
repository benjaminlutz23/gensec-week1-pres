//Benjamin Lutz
//November 3, 2022
//CS 162

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std; 

//The purpose of this program is to help the user create a list of key
//information about useful social media posts.

const int SIZE {10}; //Size the for the list
const int TITLE {31}; //Size for the title and name
const int LINK{51}; //Size for website link
const int TEXT {201}; //Size for the body of the post

struct social //Structure containing data types for various aspects of posts
{
	char author[TITLE]; //Array for the author
	char title[TITLE]; //Array for the title
	char website[LINK]; //Array for the website link
	char postText[TEXT]; //Array for the text from the post
	int numLikes {0}; //Variable for the number of likes
	int numComments {0}; //Variable for the number of coments
};

void welcome(); //Function to welcome the user
void menu(char & fResponse); //Displays a menu and gets user input
void readAPost(social & fNewPost); //Function to read in a post
void readOne(social fNewPost[], int & fNumPosts); //Reads one post
void readAll(social fNewPost[], int & fNumPosts); //Reads as many posts as user wants
void displayAPost(social & fPost); //Function to display a post
void displayAll(social fNewPost[], int & fNumPosts); //Function disp all pos
void loadFromFile(char fFileName[], social fNewPost[], int & fNumPosts); //Loads from file 
void readFileName(char fFileName[]); //Function to get the file name
//Saves everything in the array to an external file
void saveToFile(char fFileName[], social fNewPost[], int & fNumPosts);
//Calls the appropriate function
void decision(char fFileName[], social fNewPost[], int & fNumPosts);
//Displays all posts related to a particular author
void displayAuthor(social fNewPost[], int & fNumPosts);


int main()
{
	social newPost[SIZE]; //Create and array of 10 posts
	char fileName[LINK]; //Array for the file name
	char response {'\0'}; //Variable for response to menu
	int numPosts {0}; //Variable to keep track of how many posts have been ent
	
	welcome(); //Call the welcome function

	//Task 1: Read in a post
	readOne(newPost, numPosts); 

	//Task 2: Save current list to a file
	readFileName(fileName);
	saveToFile(fileName, newPost, numPosts); 

	//Task 3: Display all items
	displayAll(newPost, numPosts); 

	//Task 4: Load items from the file previously stored
	loadFromFile(fileName, newPost, numPosts); 
	
	//Task 5: Create a menu to allow the user to select from
	decision(fileName, newPost, numPosts); 

	//Task 6: Display all posts by a particular author
	displayAuthor(newPost, numPosts);
	
	return 0;
}

void welcome()
{
	cout << endl << "Welcome! This program will help you create a "
		<< "collection of important social media posts that are not spam "
		<< "or advertisements." << endl << endl;
	
	return;
}


void menu(char & fResponse)
{
	//Here's the menu
	cout << "##############################################################"
		<< endl;
	cout << "Please choose from the following list of options: " << endl;
	cout << "(a) Add a new item to the list." << endl;
	cout << "(b) Display all items in your list." << endl;
	cout << "(c) Loads items from and external file." << endl;
	cout << "(d) Quit." << endl;
	cout << "##############################################################"
		<< endl << endl << endl;

	cout << "Enter 'a', 'b', 'c', or 'd': ";
	cin >> fResponse;
	cin.ignore(100, '\n');

	return;
}


void readAPost(social & fNewPost)
{
	//Get the author
	cout << "Please enter the author of the post: ";
	cin.get(fNewPost.author, TITLE, '\n');
	cin.ignore(100, '\n'); 

	//Get the title
	cout << "Please enter the title: "; 
	cin.get(fNewPost.title, TITLE, '\n');
	cin.ignore(100, '\n'); 

	//Get the link
	cout << "Please enter a link to the website or video: ";
	cin.get(fNewPost.website, LINK, '\n'); 
	cin.ignore(100, '\n'); 
	
	//Get the text of the post
	cout << "Please enter the text of the post: ";
	cin.get(fNewPost.postText, TEXT, '\n'); 
	cin.ignore(100, '\n'); 

	//Get the number of likes
	cout << "Please enter the number of likes: ";
	cin >> fNewPost.numLikes;
	cin.ignore(100, '\n'); 

	//Get the number of comments
	cout << "Please enter the number of comments: ";
	cin >> fNewPost.numComments; 
	cin.ignore(100, '\n'); 

	return;
}

void readOne(social fNewPost[], int & fNumPosts)
{
	cout << "The number of posts in readOne is " << fNumPosts << endl;

    readAPost(fNewPost[fNumPosts]); //Call function to append to the array

	++fNumPosts; //Update the number of posts

    return;
} 



void readAll(social fNewPost[], int & fNumPosts)
{
	cout << "The number of posts in readAll is " << fNumPosts << endl;

	bool done {false}; //Variable for wether the user is done adding posts
    char response {'Y'}; //Provides for the user's answer of Y or N
    int i {0}; //Number of posts
    for (i = fNumPosts; i < SIZE && !done; ++i)
    {
        readAPost(fNewPost[i]); //Call function to read a new post
        cout << "Another? ";
        cin >> response;
        cin.ignore(100, '\n');
        if (toupper(response) != 'Y')
            done = true;
    }
    return;
} 


void readFileName(char fFileName[])
{
	cout << "Please enter the name of the file you would like to store "
		<< "your list of posts in: ";
	cin.width(LINK); //Ensure we don't go outside the array bounds
	cin >> fFileName;
	cin.ignore(100, '\n');
}

void saveToFile(char fFileName[], social fNewPost[], int & fNumPosts)
{
	cout << "The number of posts in saveToFile is " << fNumPosts << endl;

	ofstream fileOut;
    fileOut.open(fFileName, ios::app); //keep adding to the file
    if (fileOut) //Did it properly connect
    {
		cout << "you're in the file." << endl;
		for (int i {0}; i < fNumPosts; ++i) 
		{
			//Get the info from the file
			fileOut << fNewPost[i].author << ':' << fNewPost[i].title << ':'
				<< fNewPost[i].website << ':' << fNewPost[i].postText << ':'
				<< fNewPost[i].numLikes << ':' << fNewPost[i].numComments 
				<< endl;
		}
        fileOut.close(); //Close the file
    }

	return;
}

void displayAPost(social & fPost)
{
	//Output the stuff
	cout << "The stuff you entered is: " << endl;
	cout << fPost.author << endl;
	cout << fPost.title << endl;
	cout << fPost.website << endl;
	cout << fPost.postText << endl;
	cout << fPost.numLikes << endl;
	cout << fPost.numComments << endl;
}


void displayAll(social fNewPost[], int & fNumPosts)
{
	cout << "The number of posts in displayAll is " << fNumPosts << endl;

	for (int i {0}; i < fNumPosts; ++i)
	{
		displayAPost(fNewPost[i]); //Call the function to display individual posts
	}
}
	
	
void loadFromFile(char fFileName[], social fNewPost[], int & fNumPosts)
{	
	cout << "The number of posts in loadFromFile is " << fNumPosts << endl;

	ifstream fileIn;
    int i {fNumPosts}; //Used for an index into the social array
    fileIn.open(fFileName);
    if (fileIn) //Are we connected
    {
        while (fileIn && !fileIn.eof() && i <= (SIZE - fNumPosts))
        {
			//Read in everything
			fileIn.get(fNewPost[i].author, TITLE, ':');
            fileIn.ignore(100, ':');

			fileIn.get(fNewPost[i].title, TITLE, ':');
            fileIn.ignore(100, ':');

			fileIn.get(fNewPost[i].website, LINK, ':');
            fileIn.ignore(100, ':');

			fileIn.get(fNewPost[i].postText, TEXT, ':');
            fileIn.ignore(100, ':');

            fileIn >> fNewPost[i].numLikes;
            fileIn.ignore(100, ':');

            fileIn >> fNewPost[i].numComments;
            fileIn.ignore(100, '\n');

            ++i;
			++fNumPosts;
        }
        fileIn.close(); //we are done reading from the file
	}
    return;
}


void decision(char fFileName[], social fNewPost[], int & fNumPosts)
{
	char response {'\0'}; //Variable to help simplifiy the writing

	cout << "The number of posts in decision is " << fNumPosts << endl;
					  
	do
	{
		menu(response); 

		response = toupper(response); 

		if (response == 'A')
			readAll(fNewPost, fNumPosts); //Enter new posts
		else if (response == 'B')
			displayAll(fNewPost, fNumPosts); //Display everything
		else if (response == 'C')
			loadFromFile(fFileName, fNewPost, fNumPosts); //Load from the file
		else if (response == 'D')
			cout << endl;
		else
			cout << "Invalid response.  Please try again." << endl;
	} while (response != 'D');
}


void displayAuthor(social fNewPost[], int & fNumPosts)
{
	char usrAuth[TITLE]; //Variable for the author the user wants

	cout << "The number of posts in displayAuthor is " << fNumPosts << endl;
	
	cout << "Who's posts would you like to see? Please enter the name of the author: ";
	cin.get(usrAuth, TITLE, '\n'); //Read in the author
	cin.ignore(100, '\n'); 

	//Loop through and test for matches
	for (int j {0}; j < fNumPosts; j++)
	{
		if (strcmp(fNewPost[j].author, usrAuth) == 0)
		{
			displayAPost(fNewPost[j]); //Display the post the author wants
		}
	}

	cout << "Thank you for using this program." << endl; //Say goodbye

	return;
}
