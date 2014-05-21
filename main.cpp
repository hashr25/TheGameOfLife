/*
The Game of Life
Originally by Milton Bradley
Program Written by Randy Hash
CS202
Final Project
*/

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************************************
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

//Included Libraries
#include <curses.h>     //Curses
#include <cstdlib>      //Random
#include <fstream>      //files                //MAKE SURE YOU NEED ALL THESE WHEN YOU ARE DONE
#include <ctime>        //Seed for random
#include "tile.h"       //tile class
#include "player.h"     //player class
//#include <iostream>             //can remove after debugging

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Forward Declarations
void makeBoard(WINDOW*&);
void printRoll(WINDOW*&, int);
int spinSpinner(WINDOW*&);
vector<house> getHouses(string);
vector<career> getJobs(string, string);
void makeBaseTiles(tile*&);
void makeSplit(tile*&, string, string);
void deleteTiles(tile*&);
void playerTurn(player*&, WINDOW*&, WINDOW*&, WINDOW*&, player*&, player*&, vector<house>&, vector<house>&, vector<career>&, vector<career>&, tile*, bool);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************************************
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(time(NULL));//random seed

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Curses Setup

    initscr();//initialize the screen
    curs_set(0);//set the cursor to be invisible
    noecho();//Don't put user input on the screen

    start_color();
    init_pair(0, COLOR_RED, COLOR_BLACK);//color for Stops
    init_pair(1, COLOR_GREEN, COLOR_BLACK);//color for Paydays
    init_pair(2, COLOR_BLUE, COLOR_BLACK);//color for Lawsuits
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);//color for girls
    init_pair(4, COLOR_BLUE, COLOR_BLACK);//color for boys
    init_pair(5, COLOR_BLACK, COLOR_GREEN);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Board Setup

    int boardHeight = 40;
    int boardWidth = 160;
    int spinnerHeight = 6;
    int spinnerWidth = 10;
    int interfaceHeight = 15;
    int interfaceWidth = 160;

    WINDOW * gameBoard = NULL;
    gameBoard = newwin(boardHeight,boardWidth, 3, 0);
    WINDOW * spinner = NULL;
    spinner = newwin(spinnerHeight,spinnerWidth, 17, 70);
    WINDOW * interface = NULL;
    interface = newwin(interfaceHeight, interfaceWidth, 37, 0);
    wrefresh(stdscr);

    makeBoard(gameBoard);
    wrefresh(gameBoard);

    vector<house> starterHouses = getHouses("starterHouses.txt");
    vector<house> homes = getHouses("houses.txt");

    vector<career> jobs = getJobs("careers.txt", "JOB");
    vector<career> collegeJobs = getJobs("collegeCareers.txt", "CAREER");

    tile* startTile = new tile;
    tile* split1Head = new tile;
    tile* split2Head = new tile;
    tile* split3Head = new tile;
    tile* split4Head = new tile;

    makeBaseTiles(startTile);
    makeSplit(split1Head, "split1.txt", "split1Info.txt");
    makeSplit(split2Head, "split2.txt", "split2Info.txt");
    makeSplit(split3Head, "split3.txt", "split3Info.txt");
    makeSplit(split4Head, "split4.txt", "split4Info.txt");

    //setup of splits
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //first split
    startTile -> setSplit(split1Head);

    tile* temp = startTile;
    tile* backTemp = split1Head;
    for(int i = 0; i < 11; i++)
    {
        temp = temp -> getNext();
    }
    for(int i = 0; i < 2; i++)
    {
        backTemp = backTemp -> getNext();
    }
    backTemp -> setNext(temp);



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //second split
    temp = startTile;
    for(int i = 0; i < 48; i++)
    {
        temp = temp -> getNext();
    }
    temp -> setSplit(split2Head);

    temp = startTile;
    backTemp = split2Head;
    for(int i = 0; i < 55; i++)
    {
        temp = temp -> getNext();
    }
    for(int i = 0; i < 6; i++)
    {
        backTemp = backTemp -> getNext();
    }
    backTemp -> setNext(temp);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //third split
    temp = startTile;
    for(int i = 0; i < 78; i++)
    {
        temp = temp -> getNext();
    }
    temp -> setSplit(split3Head);
    temp = startTile;
    backTemp = split3Head;
    for(int i = 0; i < 85; i++)
    {
        temp = temp -> getNext();
    }
    for(int i = 0; i < 3; i++)
    {
        backTemp = backTemp -> getNext();
    }

    backTemp -> setNext(temp);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //fourth split
    temp = startTile;
    for(int i = 0; i < 103; i++)
    {
        temp = temp -> getNext();
    }
    temp -> setSplit(split4Head);
    temp = startTile;
    backTemp = split4Head;
    for(int i = 0; i < 112; i++)
    {
        temp = temp -> getNext();
    }
    for(int i = 0; i < 3; i++)
    {
        backTemp = backTemp -> getNext();
    }
    backTemp -> setNext(temp);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Setup Players
    player * user = new player;
    user -> makeUserPlayer(interface);
    user -> setLocation(startTile);

    player * computer = new player;
    computer -> makeAIPlayer();
    computer -> setY(21);
    computer -> setX(74);
    computer -> setInterfaceX(25);
    computer -> setLocation(startTile);

    bool isSame = true;
    player * computer2 = new player;
    while(isSame == true)
    {
        computer2 -> makeAIPlayer();
        computer2 -> setY(21);
        computer2 -> setX(75);
        computer2 -> setInterfaceX(50);
        computer2 -> setLocation(startTile);
        if(computer -> getName() != computer2 -> getName())
        {
            isSame = false;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Print Everything commands
    user -> printCar(interface);
    user -> printPlayer(gameBoard);

    computer -> printCar(interface);
    computer -> printPlayer(gameBoard);

    computer2 -> printCar(interface);
    computer2 -> printPlayer(gameBoard);


    wrefresh(gameBoard);
    wrefresh(spinner);
    wrefresh(interface);

    int interfaceUserX = 80;
    int interfaceUserY = 2;

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GAME LOOP
    v v v v v
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/



bool gameOver = false;

while(gameOver != true)
{
    mvwprintw(interface, interfaceUserY, interfaceUserX-5, "                                                                                     ");
    mvwprintw(interface, interfaceUserY, interfaceUserX, user -> getName().c_str());
    mvwprintw(interface, interfaceUserY, interfaceUserX + user -> getName().size(), "'s turn.");
    wrefresh(interface);
    playerTurn(user, spinner, interface, gameBoard, computer, computer2, starterHouses, homes, jobs, collegeJobs, startTile, true);
    getch();

    mvwprintw(interface, interfaceUserY, interfaceUserX-5, "                                                                                     ");
    mvwprintw(interface, interfaceUserY, interfaceUserX, computer -> getName().c_str());
    mvwprintw(interface, interfaceUserY, interfaceUserX + computer -> getName().size(), "'s turn.");
    wrefresh(interface);
    playerTurn(computer, spinner, interface, gameBoard, user, computer2, starterHouses, homes, jobs, collegeJobs, startTile, false);
    getch();

    mvwprintw(interface, interfaceUserY, interfaceUserX-5, "                                                                                     ");
    mvwprintw(interface, interfaceUserY, interfaceUserX, computer2 -> getName().c_str());
    mvwprintw(interface, interfaceUserY, interfaceUserX + computer2 -> getName().size(), "'s turn.");
    wrefresh(interface);
    playerTurn(computer2, spinner, interface, gameBoard, user, computer, starterHouses, homes, jobs, collegeJobs, startTile, false);
    getch();

    if(user -> getLocation() -> getTilePurpose() == END_OF_BOARD        &&
       computer -> getLocation() -> getTilePurpose() == END_OF_BOARD    &&
       computer2 -> getLocation() -> getTilePurpose() == END_OF_BOARD)
    {
        gameOver = true;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//End Game

user -> totalFunds();
computer -> totalFunds();
computer2 -> totalFunds();

user -> printCar(interface);
user -> printPlayer(gameBoard);

computer -> printCar(interface);
computer -> printPlayer(gameBoard);

computer2 -> printCar(interface);

computer2 -> printPlayer(gameBoard);

mvwprintw(interface, interfaceUserY+2, interfaceUserX-10, "                                                                                     ");

if(user -> getMoney() > computer -> getMoney() && user -> getMoney() > computer2 -> getMoney())
{
    mvwprintw(interface, interfaceUserY, interfaceUserX-5, "                                                                                     ");
    mvwprintw(interface, interfaceUserY, interfaceUserX, "You win the game!!!");
    wrefresh(interface);
}

else if(computer -> getMoney() > user -> getMoney() && computer -> getMoney() > computer2 -> getMoney())
{
    mvwprintw(interface, interfaceUserY, interfaceUserX-5, "                                                                                     ");
    mvwprintw(interface, interfaceUserY, interfaceUserX, computer -> getName().c_str());
    mvwprintw(interface, interfaceUserY, interfaceUserX + computer -> getName().size(), " wins the game!");
    wrefresh(interface);
}

else if(computer2 -> getMoney() > user -> getMoney() && computer2 -> getMoney() > computer -> getMoney())
{
    mvwprintw(interface, interfaceUserY, interfaceUserX-5, "                                                                                     ");
    mvwprintw(interface, interfaceUserY, interfaceUserX, computer2 -> getName().c_str());
    mvwprintw(interface, interfaceUserY, interfaceUserX + computer2 -> getName().size(), " wins the game!");
    wrefresh(interface);
}

getch();getch();getch();
wclear(interface);
wclear(spinner);
wrefresh(interface);
wrefresh(spinner);

mvwprintw(spinner,1,1, " Thanks ");
mvwprintw(spinner,3,1, "   for  ");
mvwprintw(spinner,5,1, "Playing!");
wrefresh(spinner);

mvwprintw(interface, 5, 35, "Press Enter to Exit!");
wrefresh(interface);
getch();

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ^ ^ ^ ^ ^
    GAME LOOP

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Closing Program
    delete user;
    delete computer;
    delete computer2;

    deleteTiles(startTile);
    deleteTiles(split1Head);
    deleteTiles(split2Head);
    deleteTiles(split3Head);
    deleteTiles(split4Head);

    delwin(gameBoard);
    delwin(spinner);
    delwin(interface);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************************************
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//Function Declarations
void makeBoard(WINDOW*& window)
{
    ifstream boardFile;
    boardFile.open("gameBoard.txt");
    string line = "";
    int lineCounter = 0;
    while(getline(boardFile, line))
    {
        for(int i = 0; i < line.size(); i++)
        {
            wmove(window, lineCounter, i);
            if(line.at(i) == 'S')
            {
                waddch(window, line.at(i) | COLOR_PAIR(6));
            }
            else if(line.at(i) == 'P')
            {
                waddch(window, line.at(i) | COLOR_PAIR(1));
            }
            else if(line.at(i) == 'L')
            {
                waddch(window, line.at(i) | COLOR_PAIR(2));
            }
            else if(line.at(i) == '#')
            {
                waddch(window, line.at(i) | COLOR_PAIR(5));
            }
            else if(line.at(i) == 'I')
            {
                waddch(window, line.at(i) | COLOR_PAIR(6));
            }
            else if(line.at(i) == 'F')
            {
                waddch(window, line.at(i) | COLOR_PAIR(7));
            }
            else if(line.at(i) == 'E')
            {
                waddch(window, line.at(i) | COLOR_PAIR(1));
            }
            else
            {
                waddch(window, line.at(i));
            }
        }
        lineCounter++;
        line = "";
    }
    boardFile.close();

    wrefresh(window);//first screen refresh
}

void printRoll(WINDOW*& window, int roll)
{
    werase(window);

    if(roll == 1)
    {
        mvwprintw(window, 0, 5, "1");
        mvwprintw(window, 1, 5, "1");
        mvwprintw(window, 2, 5, "1");
        mvwprintw(window, 3, 5, "1");
        mvwprintw(window, 4, 5, "1");
        mvwprintw(window, 5, 5, "1");
    }
    else if(roll == 2)
    {
        mvwprintw(window, 0, 2, " 222 ");
        mvwprintw(window, 1, 2, "2   2");
        mvwprintw(window, 2, 2, "   2 ");
        mvwprintw(window, 3, 2, "  2  ");
        mvwprintw(window, 4, 2, " 2   ");
        mvwprintw(window, 5, 2, "22222");
    }
    else if(roll == 3)
    {
        mvwprintw(window, 1, 3, "333 ");
        mvwprintw(window, 2, 3, "   3");
        mvwprintw(window, 3, 3, " 33");
        mvwprintw(window, 4, 3, "   3");
        mvwprintw(window, 5, 3, "333");
    }
    else if(roll == 4)
    {
        mvwprintw(window, 0, 2, "4   4");
        mvwprintw(window, 1, 2, "4   4");
        mvwprintw(window, 2, 2, "44444");
        mvwprintw(window, 3, 2, "    4");
        mvwprintw(window, 4, 2, "    4");
        mvwprintw(window, 5, 2, "    4");
    }
    else if(roll == 5)
    {
        mvwprintw(window, 1, 3, "55555");
        mvwprintw(window, 2, 3, "5    ");
        mvwprintw(window, 3, 3, "5555 ");
        mvwprintw(window, 4, 3, "    5");
        mvwprintw(window, 5, 3, "5555 ");
    }
    else if(roll == 6)
    {
        mvwprintw(window, 0, 3, "  6 ");
        mvwprintw(window, 1, 3, " 6  ");
        mvwprintw(window, 2, 3, "6   ");
        mvwprintw(window, 3, 3, "666 ");
        mvwprintw(window, 4, 3, "6  6");
        mvwprintw(window, 5, 3, " 66 ");
    }
    else if(roll == 7)
    {
        mvwprintw(window, 1, 2, "77777");
        mvwprintw(window, 2, 2, "    7");
        mvwprintw(window, 3, 2, "   7 ");
        mvwprintw(window, 4, 2, "  7  ");
        mvwprintw(window, 5, 2, " 7   ");
    }
    else if(roll == 8)
    {
        mvwprintw(window, 1, 3, " 888");
        mvwprintw(window, 2, 3, "8   8");
        mvwprintw(window, 3, 3, " 888");
        mvwprintw(window, 4, 3, "8   8");
        mvwprintw(window, 5, 3, " 888");
    }
    else if(roll == 9)
    {
        mvwprintw(window, 0, 3, " 99 ");
        mvwprintw(window, 1, 3, "9  9");
        mvwprintw(window, 2, 3, " 999");
        mvwprintw(window, 3, 3, "   9");
        mvwprintw(window, 4, 3, "  9 ");
        mvwprintw(window, 5, 3, " 9  ");
    }
    else if(roll == 10)
    {
        mvwprintw(window, 0, 2, "1  000");
        mvwprintw(window, 1, 2, "1 0   0");
        mvwprintw(window, 2, 2, "1 0   0");
        mvwprintw(window, 3, 2, "1 0   0");
        mvwprintw(window, 4, 2, "1 0   0");
        mvwprintw(window, 5, 2, "1  000");
    }

    wrefresh(window);
}

int spinSpinner(WINDOW*& window)
{
    int randomSpin;

    for(int i = 0; i < 4000; i++)
    {
        randomSpin = rand() % 10 + 1;
        printRoll(window, randomSpin);
    }

    return randomSpin;
}

vector<house> getHouses(string fileName)
{
    vector<house> houseVector;

    ifstream houseFile;
    houseFile.open(fileName.c_str());
    string houseName = "";
    int houseCost;
    int houseWorth;

    while(houseFile >> houseName >> houseCost >> houseWorth)
    {
        house temp;
        temp.name = houseName;
        temp.cost = houseCost;
        temp.worth = houseWorth;
        houseVector.push_back(temp);
    }

    houseFile.close();

    return houseVector;
}

vector<career> getJobs(string fileName, string typeOfCareer)
{
    vector<career> jobVector;

    ifstream jobFile;
    jobFile.open(fileName.c_str());

    string jobName;
    int baseSalary;
    int topSalary;
    int jobTaxes;

    while(jobFile >> jobName >> baseSalary >> topSalary >> jobTaxes)
    {
        career temp;
        temp.type = typeOfCareer;
        temp.title = jobName;
        temp.salary = baseSalary;
        temp.maxSalary = topSalary;
        temp.taxes = jobTaxes;
        jobVector.push_back(temp);
    }

    jobFile.close();

    return jobVector;
}

void makeBaseTiles(tile*& startPoint)
{
    ifstream baseTiles;
    baseTiles.open("baseTiles.txt");

    /*if(baseTiles.fail())
    {
        std::cout << "baseTiles f'ed up." << std::endl;
    }*/

    string tileInfo = "";

    tile* temp = startPoint;
    tile* newTemp = NULL;

    while(getline(baseTiles, tileInfo))
    {
        temp -> setInfo(tileInfo);
        newTemp = new tile;
        temp -> setNext(newTemp);
        temp = newTemp;
    }

    baseTiles.close();

    ifstream baseTilesInfo;
    baseTilesInfo.open("baseTilesInfo.txt");

    /*if(baseTilesInfo.fail())
    {
        std::cout << "baseTilesInfo f'ed up." << std::endl;
    }*/

    int tempFunction;
    tileFunction convFunction;
    int tempPayout;
    int xOneTemp;
    int yOneTemp;
    int xTwoTemp;
    int yTwoTemp;
    int xThreeTemp;
    int yThreeTemp;

    temp = startPoint;

    while(baseTilesInfo >> tempFunction >> tempPayout >> xOneTemp >> yOneTemp >> xTwoTemp >> yTwoTemp >> xThreeTemp >> yThreeTemp)
    {
        convFunction = (tileFunction) tempFunction;
        temp -> setTilePurpose(convFunction);
        temp -> setPayout(tempPayout);
        temp -> setXOne(xOneTemp);
        temp -> setYOne(yOneTemp);
        temp -> setXTwo(xTwoTemp);
        temp -> setYTwo(yTwoTemp);
        temp -> setXThree(xThreeTemp);
        temp -> setYThree(yThreeTemp);

        temp = temp -> getNext();
    }

    baseTilesInfo.close();
}

void deleteTiles(tile*& startPoint)
{
    tile* temp = NULL;
    while(startPoint != NULL)
    {
        temp = startPoint;
        startPoint = startPoint -> getNext();
        delete temp;
    }
    startPoint = NULL;
}

void makeSplit(tile*& splitStart, string fileName, string fileNameInfo)
{
    ifstream splitTiles;
    splitTiles.open(fileName.c_str());

    /*if(splitTiles.fail())
    {
        std::cout << fileName <<" f'ed up." << std::endl;
    }*/

    string tileInfo = "";

    tile* temp = splitStart;
    tile* newTemp = NULL;

    while(getline(splitTiles, tileInfo))
    {
        temp -> setInfo(tileInfo);
        newTemp = new tile;
        temp -> setNext(newTemp);
        temp = newTemp;
    }

    splitTiles.close();

    ifstream splitTilesInfo;
    splitTilesInfo.open(fileNameInfo.c_str());

    /*if(splitTilesInfo.fail())
    {
        std::cout << fileNameInfo << " f'ed up." << std::endl;
    }*/

    int tempFunction;
    tileFunction convFunction;
    int tempPayout;
    int xOneTemp;
    int yOneTemp;
    int xTwoTemp;
    int yTwoTemp;
    int xThreeTemp;
    int yThreeTemp;

    temp = splitStart;

    while(splitTilesInfo >> tempFunction >> tempPayout >> xOneTemp >> yOneTemp >> xTwoTemp >> yTwoTemp >> xThreeTemp >> yThreeTemp)
    {
        convFunction = (tileFunction) tempFunction;
        temp -> setTilePurpose(convFunction);
        temp -> setPayout(tempPayout);
        temp -> setXOne(xOneTemp);
        temp -> setYOne(yOneTemp);
        temp -> setXTwo(xTwoTemp);
        temp -> setYTwo(yTwoTemp);
        temp -> setXThree(xThreeTemp);
        temp -> setYThree(yThreeTemp);

        temp = temp -> getNext();
    }

    splitTilesInfo.close();
}

void setTileInformation(tile*& startTile) // needs finished
{
    ifstream tileInformation;
    tileInformation.open("baseTileData.txt");
}

void playerTurn(player*& playerName,
              WINDOW*& spinnerWindow,
              WINDOW*& interfaceWindow,
              WINDOW*& gameWindow,
              player*& opponent1,
              player*& opponent2,
              vector<house>& houses,
              vector <house>& homes,
              vector<career>& jobs,
              vector<career>& careers,
              tile* startOfGame,
              bool userOrNot)
    {
        if(playerName -> getLocation() -> getTilePurpose() == END_OF_BOARD)
        {
            playerName -> setMissTurn(true);
        }

        if(playerName -> getMissTurn() == true)
        {
            //skips turn
        }

        else
        {
            int interfacePrintX = 77;
            int interfacePrintY = 5;


            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX-1, "                                                                     ");
            wrefresh(interfaceWindow);

            if(userOrNot == true)
            {
                mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "Press Enter to SPIN!");
                wrefresh(interfaceWindow);
                getch();
            }

            wrefresh(gameWindow);
            wrefresh(interfaceWindow);
            int spinnerValue = spinSpinner(spinnerWindow);

            if(playerName -> getLocation() -> getTilePurpose() == START)
            {
                if(spinnerValue > 1)
                {
                    spinnerValue--;
                }

                playerName -> startGame(interfaceWindow, userOrNot);

                if(playerName -> getLocation() == startOfGame -> getSplit())
                {
                    playerName -> chooseJob(interfaceWindow, jobs, userOrNot);
                }
            }


            //userLocation = playerName -> getLocation();

            for(int i = 0; i < spinnerValue; i++)
            {
                //userLocation = userLocation -> getNext();

                playerName -> setLocation(playerName -> getLocation() -> getNext());

                string locationInfo = playerName -> getLocation() -> getInfo();
                tileFunction tempTilePurpose = playerName -> getLocation() -> getTilePurpose();

                mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                                                                   ");
                mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX-1, "                                                                                   ");
                mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX-1, locationInfo.c_str());
                wrefresh(interfaceWindow);wrefresh(gameWindow);

                playerName -> clearPlayer(gameWindow);
                if(userOrNot == true)
                {
                    playerName -> setX(playerName -> getLocation() -> getXOne());
                    playerName -> setY(playerName -> getLocation() -> getYOne());
                }
                else if(userOrNot == false)
                {
                    playerName -> setX(playerName -> getLocation() -> getXTwo());
                    playerName -> setY(playerName -> getLocation() -> getYTwo());
                }
                playerName -> printPlayer(gameWindow);
                playerName -> printCar(interfaceWindow);

                playerName -> printPlayer(gameWindow);

                //This is the actual iterator through the tiles


                if(tempTilePurpose == RETURN_TO_SCHOOL              ||      //This happens if there is a choice
                   tempTilePurpose == PATH_OF_LIFE                  ||
                   tempTilePurpose == RISKY_OR_SAFE)
                {
                    //Split functions go here
                    if(tempTilePurpose == RETURN_TO_SCHOOL)
                    {
                        playerName -> returnToSchool(userOrNot);
                    }
                    else if(tempTilePurpose == PATH_OF_LIFE)
                    {
                        playerName -> pathOfLife(userOrNot);
                    }
                    else if(tempTilePurpose == RISKY_OR_SAFE)
                    {
                        playerName -> riskyOrSafe(userOrNot);
                    }
                }

                else if(tempTilePurpose == SPOUSE                       ||      //This happens if the user stops
                        tempTilePurpose == CHOOSE_CAREER                ||
                        tempTilePurpose == BUY_HOUSE                    ||
                        tempTilePurpose == BUY_HOME                     ||
                        tempTilePurpose == CHOOSE_CAREER_OR_PAY_RAISE   ||
                        tempTilePurpose == END_OF_BOARD)
                {
                    spinnerValue = i;

                    //Stop functions go here
                    if(tempTilePurpose == SPOUSE)
                    {
                        playerName -> getMarried();
                    }
                    else if(tempTilePurpose == CHOOSE_CAREER)
                    {
                        playerName -> chooseJob(interfaceWindow, careers, userOrNot);
                    }
                    else if(tempTilePurpose == BUY_HOUSE)
                    {
                        playerName -> chooseHouse(interfaceWindow, houses, userOrNot);
                    }
                    else if(tempTilePurpose == BUY_HOME)
                    {
                        playerName -> chooseHouse(interfaceWindow, homes, userOrNot);
                    }
                    else if(tempTilePurpose == CHOOSE_CAREER_OR_PAY_RAISE)
                    {
                        playerName -> chooseCareerOrPayRaise(interfaceWindow, userOrNot, careers);
                    }
                    else if(tempTilePurpose == END_OF_BOARD)
                    {
                        if(opponent1 -> getLocation() -> getTilePurpose() != END_OF_BOARD   &&
                           opponent2 -> getLocation() -> getTilePurpose() != END_OF_BOARD)
                        {
                            for(int i = 0; i < 5; i++)
                            {
                                playerName -> addToLifeCards();
                            }
                        }
                    }
                }

                else if(i == spinnerValue - 1) // last iteration
                {
                    string locationInfo = playerName -> getLocation() -> getInfo();

                    playerName -> printPlayer(gameWindow);

                    playerName -> clearPlayer(gameWindow);

                    if(userOrNot == true)
                    {
                        playerName -> setX(playerName -> getLocation() -> getXOne());
                        playerName -> setY(playerName -> getLocation() -> getYOne());
                    }
                    else if(userOrNot == false)
                    {
                        playerName -> setX(playerName -> getLocation() -> getXTwo());
                        playerName -> setY(playerName -> getLocation() -> getYTwo());
                    }
                    playerName -> printPlayer(gameWindow);
                    playerName -> printCar(interfaceWindow);

                    mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                                                               ");
                    mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX-1, locationInfo.c_str());
                    wrefresh(interfaceWindow);
                    wrefresh(gameWindow);
                    getch();

                    if(tempTilePurpose == PAYOUT)
                    {
                        playerName -> applyPayout(playerName -> getLocation() -> getPayout());
                    }

                    else if(tempTilePurpose == LIFE_CARD)
                    {
                        playerName -> addToLifeCards();
                    }

                    else if(tempTilePurpose == PAYDAY)
                    {
                        playerName -> payday();
                    }

                    else if(tempTilePurpose == PAY_RAISE)
                    {
                        playerName -> payRaise();
                    }

                    else if(tempTilePurpose == SPIN_TO_WIN)
                    {
                        playerName -> spinToWin(interfaceWindow, spinnerWindow, userOrNot);
                    }

                    else if(tempTilePurpose == LAWSUIT)
                    {
                        playerName -> lawsuit(opponent1, opponent2);
                    }

                    else if(tempTilePurpose == BOY)
                    {
                        playerName -> haveKid(interfaceWindow, 'B');
                    }

                    else if(tempTilePurpose == GIRL)
                    {
                        playerName -> haveKid(interfaceWindow, 'G');
                    }

                    else if(tempTilePurpose == TWINS)
                    {
                        playerName -> twins(interfaceWindow);
                    }

                    else if(tempTilePurpose == LOSE_TURN)
                    {
                        playerName -> setMissTurn(true);
                    }

                    else if(tempTilePurpose == SHARE_THE_WEALTH)
                    {
                        //This feature is not implemented
                    }

                    else if(tempTilePurpose == SPIN_AGAIN)
                    {
                        playerTurn(playerName, spinnerWindow, interfaceWindow, gameWindow, opponent1, opponent2, houses, homes, jobs, careers, startOfGame, userOrNot);
                    }

                    else if(tempTilePurpose == LOSE_JOB)
                    {
                        playerName -> loseJob(interfaceWindow, jobs, careers, userOrNot);
                    }

                    else if(tempTilePurpose == PAY_TAXES)
                    {
                        playerName -> payTaxes();
                    }

                    else if(tempTilePurpose == TAX_REFUND)
                    {
                        playerName -> taxRefund();
                    }

                    else if(tempTilePurpose == MOVE_TO_WEDDING)
                    {
                        tile* temp = startOfGame;
                        for(int i = 0; i < 20; i ++)
                        {
                            temp = temp -> getNext();
                        }

                        playerName-> setLocation(temp);
                        playerName -> getMarried();
                    }

                    else if(tempTilePurpose == FIVE_PER_KID)
                    {
                        playerName -> fivePerKid();
                    }

                    else if(tempTilePurpose == FIFTY_PER_KID)
                    {
                        playerName -> fiftyPerKid();
                    }

                    else if(tempTilePurpose == TWENTY_FIVE_PLUS_FIVE_PER_KID)
                    {
                        playerName -> twentyFivePlusFivePerKid();
                    }

                    else if(tempTilePurpose == DAY_CARE)
                    {
                        playerName -> dayCare(opponent1, opponent2);
                    }

                    else if(tempTilePurpose == SPIN_FOR_MONEY)
                    {
                        playerName -> spinForMoney(spinnerWindow);
                    }
                }

                else                                                            //Just passing by
                {
                    if(tempTilePurpose == PAYDAY)
                    {
                        playerName -> payday();
                    }
                    else if(tempTilePurpose == PAY_RAISE)
                    {
                        playerName -> payRaise();
                    }
                }

            }//end of for spinner int loop

            string locationInfo = playerName -> getLocation() -> getInfo();

            playerName -> clearPlayer(gameWindow);
            if(userOrNot == true)
            {
                playerName -> setX(playerName -> getLocation() -> getXOne());
                playerName -> setY(playerName -> getLocation() -> getYOne());
            }
            else if(userOrNot == false)
            {
                playerName -> setX(playerName -> getLocation() -> getXTwo());
                playerName -> setY(playerName -> getLocation() -> getYTwo());
            }
            playerName -> printPlayer(gameWindow);
            playerName -> printCar(interfaceWindow);

            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                                                                   ");
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX-1, locationInfo.c_str());
            wrefresh(interfaceWindow);
            wrefresh(gameWindow);

            wrefresh(interfaceWindow);
            wrefresh(gameWindow);
        }

        playerName -> setMissTurn(false);
    }
