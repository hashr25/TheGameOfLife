#ifndef TILE_H
#define TILE_H

#include <string>


//Enumerated Type for Function
enum tileFunction
{
    START,              //0
    PAYOUT,             //1
    PAYDAY,             //2
    PAY_RAISE,          //3
    LIFE_CARD,          //4
    STOP,               //5
    SPIN_TO_WIN,        //6
    LAWSUIT,            //7
    SPOUSE,             //8
    BOY,                //9
    GIRL,               //10
    TWINS,              //11
    RETURN_TO_SCHOOL,   //12
    PATH_OF_LIFE,       //13
    RISKY_OR_SAFE,      //14
    LOSE_TURN,          //15
    SHARE_THE_WEALTH,   //16
    SPIN_AGAIN,         //17
    CHOOSE_JOB,         //18
    CHOOSE_CAREER,      //19
    LOSE_JOB,           //20
    CHOOSE_CAREER_OR_PAY_RAISE, //21
    PAY_TAXES,          //22
    TAX_REFUND,         //23
    BUY_HOUSE,          //24
    BUY_HOME,           //25
    MOVE_TO_WEDDING,    //26
    FIVE_PER_KID,       //27
    FIFTY_PER_KID,      //28
    TWENTY_FIVE_PLUS_FIVE_PER_KID,//29
    DAY_CARE,           //30
    SPIN_FOR_MONEY,     //31
    END_OF_BOARD        //32
};

class tile
{
public:
    //Constructor
    tile();
    //Destructor
    ~tile();

    /*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ***********************************************************************************************************************************
    *//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Member Methods
    void createTile(std::string);

    /*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ***********************************************************************************************************************************
    *//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //Accessor Functions
    void setInfo(std::string);
    void setPayout(int);
    void setTilePurpose(tileFunction);
    void setXOne(int);
    void setYOne(int);
    void setXTwo(int);
    void setYTwo(int);
    void setXThree(int);
    void setYThree(int);
    void setNext(tile*);
    void setSplit(tile*);

    std::string getInfo();
    int getPayout();
    tileFunction getTilePurpose();
    int getXOne();
    int getYOne();
    int getXTwo();
    int getYTwo();
    int getXThree();
    int getYThree();
    tile* getNext();
    tile* getSplit();

//Private Data
private:
    std::string info;
    int payout;
    tileFunction tilePurpose;
    int xOne;
    int yOne;
    int xTwo;
    int yTwo;
    int xThree;
    int yThree;
    tile* next;
    tile* split;
};

#endif // TILE_H
