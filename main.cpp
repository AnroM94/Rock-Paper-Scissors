/**********************************************************
	Cumulative Rock, Paper, Scissor Game
	Version: 1.0.0
	Author: Anro Myburgh 

	Project Desc:
	

	Limitations: 


**********************************************************/

/********************* INCLUDES *************************/
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>               
/********************* NAMESPACE ************************/
using namespace std;

/********************* GLOBALS *************************/
bool glb_Debug = false; 

/********************* DEFINES *************************/
#define MENU        0
#define PLAY        1
#define END         2
#define STOP        3

#define MAX_SCORE   3

/********************* CLASSES ************************/
class Player
{
    private:
        int score;
        string choice; 
        vector<string> previousChoices;
        int iterator;

    public:
        Player() //constructor - set to default values
        { 
            if(glb_Debug == true)
            {
                cout << "\n[DEBUG] Player Constructor Executed" << endl;
            }
            
            score = 0; 
            choice = "no Choice"; 
        } 
    
        void printPreviousPlays(void)
        {
            if(choice != "no Choice")
            {
                cout << "Player's Previous Choices: " << endl;
            
        
                for(auto i = previousChoices.end() - 1; i >= previousChoices.begin(); i--)
                {
                    cout << *i << " ";
                }
            }
            
            if(choice != "no Choice")
            {
                cout << endl;
            }
        }
        void setChoice(void) 
        {
            cout << "Human, please type in your weapon of choice:" << endl; 
            cout << "Rock\n" << "Paper\n" << "Scissors\n" << endl;
            getline(cin >> ws, choice);

            if (choice == "Rock" || choice == "Paper" || choice == "Scissors")
            {
                previousChoices.push_back(choice);
            }
            else
            {
                cout << choice <<" is not a weapon of choice." << endl;
                choice = "error"; 
            }
        }
        void clearPrevPlayed(void) { previousChoices.clear(); choice = "no Choice"; }
        void increaseScore(void) {score++;}
        string getChoice(void) { return choice; }
        int getScore(void) { return score; }
        void setScore(int score) { this->score = score; }

        ~Player()
        {
            if(glb_Debug == true)
            {
                cout << "\n[DEBUG] Player Deconstructor Executed" << endl; 
            }
            previousChoices.clear();
        }
};

class Cpu 
{
    private:
        vector<string> previousChoices; 
        string choice;
        int randNum; 
        int score; 

    public:  
        Cpu()   //constructor 
        {
            if(glb_Debug == true)
            {
                cout << "\n[DEBUG] CPU Constructor Executed" << endl;
            }
            choice = "no Choice";
            score = 0;
            randNum = 0;
            srand(time(0));     //set seed for rand 
        } 
        void printPreviousPlays(void)
        {
            if(choice != "no Choice")
            {
                cout << "Computer's Previous Choices: " << endl;
            
            
                for(auto i = previousChoices.end() - 1; i >= previousChoices.begin(); i--)
                {
                    cout << *i << " ";
                }
            }
            if(choice != "no Choice")
            {
                cout << endl;
            }
        }
        void clearPrevPlayed(void) { previousChoices.clear(); choice = "no Choice";}
        void increaseScore(void) {score++;}
        int getScore(void) { return score; }
        void setScore(int score) { this->score = score; }
        string getChoice(void) { return choice; }
        void setChoice(void)
        {
            randNum = rand() % 100; //generate a random number between 0 and 100
            if(glb_Debug == true)
            {
                cout << "[DEBUG] RAND: " << randNum << endl; 
            }

            if (randNum >= 0 && randNum <= 33)
            {
                choice = "Rock";
            }
            else if(randNum >= 34 && randNum <= 66)
            {
                choice = "Paper";
            }
            else if (randNum >= 67 && randNum <= 100)
            {
                choice = "Scissors";
            }
            else
            {
                choice = "error"; 
            }   
            
            previousChoices.push_back(choice);
        }

        ~Cpu()  //destructor
        {
            if(glb_Debug == true)
            {
                cout << "\n[DEBUG] Base Deconstructor Executed" << endl; 
            }
            previousChoices.clear();
        }


};
/********************* Sart Menu Function ****************************/
void printStartMenu (void)
{
    cout << "################## ROCK PAPER SCISSORS ####################" << endl; 
    cout << "# This is a simple game of rock paper scissors.           #" << endl; 
    cout << "#                                                         #" << endl; 
    cout << "# Chose your weapon carefully, and see if you can beat    #" << endl; 
    cout << "# the computer ;-). Game is best of 3.                    #" << endl; 
    cout << "#                                                         #" << endl; 
    cout << "###########################################################" << endl; 

}
/********************* Update Score ****************************/
void printScore(int playerScore, int computerScore)
{
    cout << "Human Score: " << playerScore << " Computer Score: " << computerScore << "\n" <<endl; 
}
/********************* Wait for computer function ****************************/
void waitForCpu(void)
{
    float progress = 0.0;
    
    cout << "Computer is calculating it's choice." << endl;
    //Won't take credit for this, added in for coolness factor - https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
    while (progress < 1.0) 
    {
        int barWidth = 36;
        
        cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) 
        {
            if (i < pos) 
            {
                cout << "=";
            }
            else if (i == pos) 
            {
                cout << ">";
            }
            else 
            {
                cout << " ";
            }
        }
        cout << "] " << int(progress * 100.0) << " %\r";
        cout.flush();
        
        progress += 0.20; // for demonstration only
        sleep(1);
    }
    cout << std::endl;
}
/********************* Determine winner ****************************/
string determineWinner(string userChoice, string computerChoice)
{
    if(userChoice == "Rock" && computerChoice == "Scissors")
    {
        return "user";
    }
    else if(userChoice == "Paper" && computerChoice == "Rock")
    {
        return "user";
    }
    else if(userChoice == "Scissors" && computerChoice == "Paper")
    {
        return "user";
    }
    else if (userChoice == "Rock" && computerChoice == "Paper")
    {
        return "cpu";
    }
    else if (userChoice == "Paper" && computerChoice == "Scissors")
    {
        return "cpu";
    }
    else if (userChoice == "Scissors" && computerChoice == "Rock")
    {
        return "cpu";
    }
    else
    {
        return "tie"; 
    }
}
/********************* MAIN ****************************/
int main(int argc, char *argv[]) 
{
	Cpu computer; 
    Player human; 

    string winner;
    string playAgain;

    char gamePhase; 
    int gameNum;

    gamePhase = 0;
    gameNum = 1; 

    while(1)
    {
        switch(gamePhase)
        {
            case MENU:
                printStartMenu();
                gamePhase = PLAY; 
            break;

            case PLAY:
                cout << "------------- Start of game: " << gameNum << " -------------" << endl;
                computer.printPreviousPlays();
                human.printPreviousPlays();
                
                cout << endl;
                
                human.setChoice();
                
                if(human.getChoice() == "error")
                {
                    cout << "Please choose rock, paper or scissors" << endl;
                    human.setChoice();
                } 
                cout << "---------------- Good luck! ---------------" << endl; 
                waitForCpu(); 
                computer.setChoice();
                
                if(computer.getChoice() == "error") 
                {
                    cout << "[ERROR] Computer returned error from RAND generator. Exiting..." << endl;
                    return 0;
                }
                
                cout << "\nPlayer: " << human.getChoice() << " vs." << " Computer: " << computer.getChoice() << endl; 

                winner = determineWinner(human.getChoice() , computer.getChoice()); 

                if(winner == "user")
                {
                    cout << "\x1B[32mYou Won!\033[0m\t\t" << endl;
                    human.increaseScore();
                }
                else if (winner == "cpu")
                {
                    cout << "\x1B[31mComputer Won!\033[0m\t\t" << endl;
                    computer.increaseScore();
                }
                else
                {
                    cout << "\x1B[33mTie! Try again\033[0m\t\t" << endl;
                }

                printScore(human.getScore(), computer.getScore());
                cout << "-------------- End of game: " << gameNum << " --------------" << endl;
                gameNum++; 

                if(human.getScore() == MAX_SCORE || computer.getScore() == MAX_SCORE)
                {
                    if(human.getScore() == MAX_SCORE)
                    {
                        cout << "\x1B[32mYou WON the game, congrats!\033[0m\t\t" << endl;
                    }   
                    else
                    {
                        cout << "\x1B[31mComputer WON the game, sorry!\033[0m\t\t" << endl; 
                    }

                    gamePhase = END; 
                } 
            break;

            case END:
                cout << "Would you like to play again?" << endl;
                getline(cin >> ws, playAgain); 
                
                if(playAgain == "Yes")
                {
                    gamePhase = MENU; 
                    
                    human.setScore(0);
                    human.clearPrevPlayed();
                    
                    computer.setScore(0);
                    computer.clearPrevPlayed();
                    
                    gameNum = 1;
                }
                else
                {
                    gamePhase = STOP; 
                }
            break;
            default:
                cout << "Thanks for playing!" << endl;
                return 0;
        }
        
 
    }
    
}