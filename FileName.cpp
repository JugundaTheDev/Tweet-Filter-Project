#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;
const int WordSize = 10;

struct BannedWords
{
	string word[WordSize];
	int wordCount;
};

void ReadToFile(string Tweet) // function to send the Tweet to the file.
{
	string outfile = "tweets1Filtered.txt"; 
	ofstream myfile(outfile, ios::app); //opening the file and appending to the file and not rewriting.
	myfile << Tweet; //writes the string to the file.
	myfile.close();
}

void CensorWords(string Tweet, string BadWord, string censor) //Censorship function to replace each bad word wtih whatever word.
{
	
	size_t pos = Tweet.find(BadWord); //finds the first occurrence of the word.
	
	while (pos != std::string::npos) //repeats until the end of the string is met
	{
		
		Tweet.replace(pos, BadWord.size(), censor); //uses replacement string function to replace the word with the censorship string
		
		pos = Tweet.find(BadWord, pos + censor.size()); // carries on till end of the function.
	}
}


int MatchCounter(char* tweet, char* word) // Counts each time there is a match by matching the patterns in the char arrays. Invested for loops
{
	int count = 0;
	int stringLen = strlen(tweet); //stores length of the tweet
	int wordLen = strlen(word); //stores length of the current word
	int j;

	for (int i = 0; i <= stringLen; i++) // loops the whole tweet.
	{
		for (j = 0; j < wordLen; j++) // loops each word. through the array
		{
			if (tweet[i + j] != word[j]) // detects matches in the array - if tweet between i j index matches current word then it breaks to 
			{
				
				break;
				
			}
		}
		if (j == wordLen) // if the word matches the word length and also matches then it adds to the count.
		{
			count++;
		}
	}
	return count; //returns variable count
}

int main()
{
	BannedWords banned; //takes from struct and creates variable banned
	banned.wordCount = 0; //assigns 0 to variable wordCount.
	ifstream infile; //opens file to be readable
	infile.open("banned.txt"); 

	for (int i = 0; i < 10; ++i)
	{
		infile >> banned.word[i]; //setting the banned words into an array that holds 10 values. 
	}

	infile.close(); //closes file
	//=======================================================================================//
	
	
	string lineHolder; 
	string Tweet1S;
	infile.open("tweets1.txt"); // opens file.

	while (!infile.eof()) //loops until the pointer reaches of the file.
	{

		getline(infile, lineHolder); //gets each line in file and puts it into a temp string called lineHolder
		Tweet1S += lineHolder + "\n"; //puts each line of the text file into a string.


		
	}
	


	//=======================================================================================//

	const int Tweet1length = Tweet1S.length(); //stores the length of the string.
	char* tweet1_array = new char[Tweet1length + 1]; // creates a Char array based off the length of the string Tweet1S and adds 1 since arrays hold +1 data.
	strcpy(tweet1_array, Tweet1S.c_str()); //converts string to an array of chars

	///======================================================================================//

	for (string i : banned.word) //goes through every string in the banned.word array.
	{

		int length = i.length(); //gets length of the current word in the array.
		char* CurrentWord = new char[length + 1]; //creates a char array to hold these strings.

		strcpy(CurrentWord, i.c_str()); // converts string to an array of chars
		cout << "Amount of times " << i << " appears in these tweets is " << MatchCounter(tweet1_array, CurrentWord) << endl; 

	}
	
	int index;
	string Censor = "***"; //string for censorship
	
	for (int i = 0; i < WordSize; ++i) //loops through whole array.
	{
		while ((index = Tweet1S.find(banned.word[i])) != string::npos) {    //loops to find every location where the current word in the array is found
			Tweet1S.replace(index, banned.word[i].length(), Censor); //removes and replaces each word in the array.
		}
	}
	

	
	
	cout << "Censored Tweet :" << endl << Tweet1S; //outputs the cnesored tweet.
		infile.close();
		ReadToFile(Tweet1S); //calls function to send the tweet to the file.
		return 0;
	
}
