#ifndef PLAYER_H
#define PLAYER_H

#include <curses.h>
#include <vector>
#include <string>

//forward declarations for class
class tile;
int spinSpinner(WINDOW*&);

//Structures
struct career
{
    std::string type;
    std::string title;
    int salary;
    int maxSalary;
    int taxes;
};

struct house
{
    std::string name;
    int cost;
    int worth;
};


class player
{
public:
    //Constructor
    player();
    ~player();

    void printCar(WINDOW*&);
    void printPlayer(WINDOW*&);
    void clearPlayer(WINDOW*&);
    void makeUserPlayer(WINDOW*&);
    void makeAIPlayer();
    void getMarried();
    void haveKid(WINDOW*, char);
    void twins(WINDOW*);
    void startGame(WINDOW*&, bool userOrNot);
    void chooseJob(WINDOW*&, std::vector<career>&, bool);
    void chooseHouse(WINDOW*&, std::vector<house>&, bool);
    void payday();
    void payRaise();
    void applyPayout(int);
    void loseJob(WINDOW*&, std::vector<career>&, std::vector<career>&, bool);
    void payTaxes();
    void taxRefund();
    void spinToWin(WINDOW*&, WINDOW*&, bool);
    void spinForMoney(WINDOW*&);
    void lawsuit(player*&, player*&);
    void fivePerKid();
    void fiftyPerKid();
    void twentyFivePlusFivePerKid();
    void dayCare(player*&, player*&);
    void returnToSchool(bool);
    void pathOfLife(bool);
    void riskyOrSafe(bool);
    void chooseCareerOrPayRaise(WINDOW*&, bool, std::vector<career>);
    void totalFunds();

    //Accessor Methods
    void setName(std::string);
    void setLocation(tile*);
    void setGender(char);
    void setJob(career);
    void setHome(house);
    void setMissTurn(bool);
    void addMoney(int);
    void addToLifeCards();
    void setX(int xCoord);
    void setY(int yCoord);
    void setInterfaceX(int);
    void setInterfaceY(int);
    void setSpouse(char);
    void addKid();
    void setKid1(char);
    void setKid2(char);
    void setKid3(char);
    void setKid4(char);

    std::string getName();
    tile* getLocation();
    char getGender();
    career getJob();
    house getHome();
    bool getMissTurn();
    int getMoney();
    int getLifeCards();
    int getXCoord();
    int getYCoord();
    int getInterfaceXCoord();
    int getInterfaceYCoord();
    char getSpouse();
    int getKidCount();
    char getKid1 ();
    char getKid2 ();
    char getKid3 ();
    char getKid4 ();

//Private Data
private:
    std::string name;
    tile* location;
    char gender;
    career job;
    house home;
    bool missTurn;
    int money;
    int lifeCards;
    int xCoord;
    int yCoord;
    int interfaceX;
    int interfaceY;
    char spouse;
    int kidCount;
    char kid1;
    char kid2;
    char kid3;
    char kid4;
};

#endif // PLAYER_H
