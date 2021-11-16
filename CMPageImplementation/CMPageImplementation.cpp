// CMPageImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Connor Michael Page
//G Number: 20849645

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
The code has been layed out in order of:
openfile function              - This function checks if the input files will open
readfile function              - This reads the file into the program inserting the text into a vector 
readfromvector function        - This function outputs the contents of the vectors
toLower function               - This function changes all the uppercase letters to lowercase
vectorCompare function         - This function checks if any words from the ban list is present in any text 
readbancountvector function    - Stores the amount of times each banned word is found
writetofile function           - This writes the contents of the filtered vector into a new file

within the main:
variable declaration 
analysing all of the text file and sorting them into the correct locations
the code for adding a user interface
*/


//---------------------------------------------------------
bool openFile(ifstream& infile )//this function checks that the txt files are available to be opened
{
    if (!infile)//if file not available
    {
        cout << "error\n";
        return false;//sets the bool as false
    }
    return true;//sets the bool as true
}

//---------------------------------------------------------

void readFile(vector<string>& wordList, ifstream& infile)//this function reads the txt files into a vector
{
    const char wordSpace = ' ';
    const char newLine = '\n';
    infile >> noskipws;//this makes the file check every character and white space eg: a space or new line
    char characters;//char characters is each character within the file
    string word;//the word is a string produced by adding character to word until a the full word is created 
   
    do
    {
            infile >> characters; 
            if (characters == wordSpace || characters == newLine || infile.eof())//checks if a space, new line or the end of file is reached
            {
                
                wordList.push_back(word);//adds the finished word to the array
                
                word.clear();//clears the variable to prepare for the next word
               
            }
            else
            {
                word += characters;//this adds each character to the word
            }
           
    } while (!infile.eof());//repteats the loop until the end of file is reached
    infile.close();//closes the file as it is no longer needed
    

}

//'-----------------------------------------------------------
void readFromVector(vector<string> fileText, int index)//outputs all text from vector
{
    const string wordSpace = " ";
    const string newLine = "\n";
    while (index < (int)fileText.size())//this will loop until index is equivelant to vector size
    {
        
        cout << fileText[index];
        cout << wordSpace;
        index++;//increases index by 1
    }
    cout << newLine;//adds an empty line after vector is printed
}

//---------------------------------------------------------
//this will convert any lower case to  
string ToLower(string word)
{
    //in function variable declaration 
    const int startValue = 0;
    const int asciiUpperLimit = 90;
    const int asciiLowerLimit = 65;
    const int asciiAdditionValue = 32;

    for (int index = startValue; index < word.size(); ++index)
        //loops through each character within the string
    {
        if (word[index] >= asciiLowerLimit && word[index] <= asciiUpperLimit)
            //if the characters ascii value is between the uppercase limits then...
        {
            word[index] += asciiAdditionValue;
            //value is increased by 32 to make it lowercase
        }
    }



    return word;
    //returns the lowercase word
}

//-------------------------------------------------------
void vectorCompare(vector<string> banList, vector<string> textList, vector<int>& wordCounter, int index, vector<string>& filteredList)
{
    //in function variable declaration
    const char banned = '*';//defined a constant for the * used in banning a word
    const int noMatchIndex = -1;//this is the value if banned word isnt found
    filteredList = textList;//copies the textlist to the filtered list
    int currentIndex;//int for finding the current index of the text file
    int banWordCount;//


    for (int banLoopIndex = index;banLoopIndex < (int)banList.size(); banLoopIndex++)
        //goes through each value within the banlist until it reaches the final string
    {
        banWordCount = index;//resets the banword count to 0

        for (int txtloopindex = index; txtloopindex < (int)textList.size(); txtloopindex++)
            //loops through each value of textlist until it gets to the final string
        {
            currentIndex = txtloopindex;//sets the value of current index to the same as txtloopindex
            int startOfBanIndex = ToLower(textList[txtloopindex]).find(banList[banLoopIndex]);
            // this checks if the banned word can be found within the string or substring of the contents of textlist
            if (startOfBanIndex != noMatchIndex)
                //if there is a location then this code is executed
            {
                banWordCount++;// the counter of the amount of times the banned word has been found increases by 1
                for (int withinStringIndex = startOfBanIndex; withinStringIndex < banList[banLoopIndex].size() + startOfBanIndex; ++withinStringIndex)
                    //this starts at the starting index of the ban and runs through until the full length of the ban word is changed
                {
                    filteredList[currentIndex][withinStringIndex] = banned;
                    // changes the index value to an *
                }
            
            }
        }

        wordCounter.push_back(banWordCount);
        // saves the banwordcount within a vector
        
    }
}

//----------------------------------------------------------

void readBanCountVector(vector<string> fileText, vector<int> banCount, int index)//outputs all text from vector
{
    //in function variable declaration
    const string newLine = "\n";//new line
    const string wordSpace = ": ";//adds colon and space

    while (index < (int)fileText.size())//this will loop until index is equivelant to vector size
    {
        cout << fileText[index];
        //outputs the banned word
        cout << wordSpace;
        //adds : 
        cout << banCount[index];
        // outputs the amount of times
        cout << newLine;
        //creates a new line
        index++;
        //increases index by 1
    }
    cout << newLine;
    //adds an empty line after vectors is printed
}

//---------------------------------------------------------
//read to file function
void writeToFile(ofstream& outfile, vector<string> filteredList, int index)
{
    const char wordSpace = ' ';//adds a spacw
    if (!outfile)
        //checks if outfile is created and opened
    {
        cout << "unable to create file";
        return;
    }
    else
    {
        while (index < (int)filteredList.size())
            //this will loop until index is equivelant to vector size
        {

            outfile << filteredList[index];
            //inserts the string from vector
            outfile << wordSpace;
            //adds a space
            index++;
            //increases index by 1
        }
    }
    outfile.close();
    //closes the file
}
int main()
{
    //----------------------------------------------------------
    //Variable declaration
    const int indexStartValue = 0;//this will always be the starting index
    //the index will start at 0 because vectors are being used instead of arrays
    const string newLine = "\n";
    const string sectionDivider = "-----------------------------------------\n";
    int index = indexStartValue;//the integer index will be declared with the value of 0
    
    //menu repsonses
    const string menuresponse1 = "1";
    const string menuresponse2 = "2";
    const string menuresponse3 = "3";
    const string menuresponse4 = "4";
    const string menuresponse5 = "5";
    string userResponse;
    
                                
    //----------------------------------------------------------
    //infile declaration
    ifstream bannedTextIn("banned.txt");//this defines the infile and gets the file name
    ifstream text1Input("text1.txt");//this defines the infile and gets the file name
    ifstream text2Input("text2.txt");//this defines the infile and gets the file name
    ifstream text3Input("text3.txt");//this defines the infile and gets the file name
    ifstream text4Input("text4.txt");//this defines the infile and gets the file name
    

    //------------------------------------------------------------
    //outfile declaration
    ofstream text1Filtered("text1Filtered.txt");
    ofstream text2Filtered("text2Filtered.txt");
    ofstream text3Filtered("text3Filtered.txt");
    ofstream text4Filtered("text4Filtered.txt");
     
   
    //------------------------------------------------------------
    //vector declaration
    //vectors for inputted files
    vector<string> bannedTextList;
    vector<string> text1WordList;
    vector<string> text2WordList;
    vector<string> text3WordList;
    vector<string> text4WordList;

   //vectors for counting the amount of banned word appearances 
    vector<int> text1BanCounter;
    vector<int> text2BanCounter;
    vector<int> text3BanCounter;
    vector<int> text4BanCounter;
  
    //vectors for filtered text
    vector<string> text1filteredList;
    vector<string> text2filteredList;
    vector<string> text3filteredList;
    vector<string> text4filteredList;

    //-----------------------------------------------------------
    //bool for if file complete 
    bool file1Read = false;
    bool file2Read = false;
    bool file3Read = false;
    bool file4Read = false;
    bool exitProgram = false;
    //checking all the text files
    //banned word list 
   
    if (openFile(bannedTextIn))//runs the open file function with the banned text list as the parameter if true then it executes the code within
    {
        readFile(bannedTextList, bannedTextIn);//reads the file into the appropriate vector
    }

    //textfile 1
    if (openFile(text1Input))//runs the open file function with text file 1 as the parameter if true then it executes the code within
    {
        readFile(text1WordList, text1Input);//reads the file into the appropriate vector
        vectorCompare(bannedTextList, text1WordList, text1BanCounter, indexStartValue, text1filteredList);
        //vector compare will check if theres a match between the ban list and txtfile, this will filter the words out
        writeToFile(text1Filtered, text1filteredList, indexStartValue);
        //write to file will then write the vector storing the filtered list into the the filtered file 
        file1Read = true;//all proccess to do with file 1 is complete
    }

    //textfile 2
    if (openFile(text2Input))//runs the open file function with text file 1 as the parameter if true then it executes the code within
    {
        readFile(text2WordList, text2Input);//reads the file into the appropriate vector
        vectorCompare(bannedTextList, text2WordList, text2BanCounter, indexStartValue, text2filteredList);
        //vector compare will check if theres a match between the ban list and txtfile, this will filter the words out
        writeToFile(text2Filtered, text2filteredList, indexStartValue);
        //write to file will then write the vector storing the filtered list into the the filtered file 
        file2Read = true;//all proccess to do with file 2 is complete
    }

    //textfile 3
    if (openFile(text3Input))//runs the open file function with text file 1 as the parameter if true then it executes the code within
    {
        readFile(text3WordList, text3Input);//reads the file into the appropriate vector
        vectorCompare(bannedTextList, text3WordList, text3BanCounter, indexStartValue, text3filteredList);
        //vector compare will check if theres a match between the ban list and txtfile, this will filter the words out
        writeToFile(text3Filtered, text3filteredList, indexStartValue);
        //write to file will then write the vector storing the filtered list into the the filtered file
        file3Read = true;//all proccess to do with file 3 is complete
    }

    //textfile 4
    if (openFile(text4Input))//runs the open file function with text file 1 as the parameter if true then it executes the code within
    {
        readFile(text4WordList, text4Input);//reads the file into the appropriate vector
        vectorCompare(bannedTextList, text4WordList, text4BanCounter, indexStartValue, text4filteredList);
        //vector compare will check if theres a match between the ban list and txtfile, this will filter the words out
        writeToFile(text4Filtered, text4filteredList, indexStartValue);
        //write to file will then write the vector storing the filtered list into the the filtered file 
        file4Read = true;//all proccess to do with file 4 is complete
    }
    //--------------------------------------------------------------------------------

    cout << "Written By: Connor Michael Page\n" ;
    cout << "G Number: 20849645\n";
    cout << sectionDivider;
    cout << "Welcome to the file filtration software.\n";
    if (file1Read == true && file2Read == true && file3Read == true && file4Read == true)
    {
        cout << "all input files have been read into the system\n";
        system("pause");//the system will pause
        cout << "The filtration proceess is complete\n The filtered files have been created \n";
        while (!exitProgram)
        {
            cout << "To look at the filtered text within the console then press:\n";
            cout << "text file 1:  1\ntext file 2:  2\ntext file 3:  3\ntext file 4:  4\nExit Program: 5\n";
            cin >> userResponse;
            if (userResponse == menuresponse1)//file1
            {
                
                readFromVector(text1filteredList, indexStartValue);
                //this will read the entire file into the console
                system("pause");//the system will pause
                cout << "List of the amount of times each banned word was used\n";
                readBanCountVector(bannedTextList, text1BanCounter, indexStartValue);
                //reads the amount of times each banned word was used
                system("pause");//the system will pause
            }
            else if (userResponse == menuresponse2)//file2
            {
                
                readFromVector(text2filteredList, indexStartValue);
                //this will read the entire file into the console
                system("pause");//the system will pause
                cout << "List of the amount of times each banned word was used\n";
                readBanCountVector(bannedTextList, text2BanCounter, indexStartValue);
                //reads the amount of times each banned word was used
                system("pause");//the system will pause
            }
            else if (userResponse == menuresponse3)//file3
            {
                
                readFromVector(text3filteredList, indexStartValue);
                //this will read the entire file into the console
                system("pause");//the system will pause
                cout << "List of the amount of times each banned word was used\n";
                readBanCountVector(bannedTextList, text3BanCounter, indexStartValue);
                //reads the amount of times each banned word was used
                system("pause");//the system will pause
            }
            else if (userResponse == menuresponse4)//file4
            {
                
                readFromVector(text4filteredList, indexStartValue);
                //this will read the entire file into the console
                system("pause");//the system will pause
                cout << "List of the amount of times each banned word was used\n";
                readBanCountVector(bannedTextList, text4BanCounter, indexStartValue);
                //reads the amount of times each banned word was used
                system("pause");//the system will pause
            }
            else if (userResponse == menuresponse5)//exit program
            {
                exit(1);//exits the program
            }
            else
            {
                cout << "ERROR!!!   Please input a valid value\n";
            }
        }
        
    }
    
    
    
    
    
    
    
    
}

