#include "tile.h"

//Constructor
tile::tile()
{
    /*cout << "Constructing a tile." << endl;*/
    next = NULL;
    split = NULL;
    info = "";
    payout = 0;
}
//Destructor
tile::~tile()
{
    /*cout << "Destroying a tile." << endl;*/
    delete next;
    delete split;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************************************
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Member Methods
void tile::createTile(string tileInfo)
{
    setInfo(tileInfo);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***********************************************************************************************************************************
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Accessor Functions
void tile::setInfo(string info)
{
    this -> info = info;
}

void tile::setPayout(int payout)
{
    this -> payout = payout;
}

void tile::setTilePurpose(tileFunction tilePurpose)
{
    this -> tilePurpose = tilePurpose;
}

void tile::setXOne(int xOne)
{
    this -> xOne = xOne;
}

void tile::setYOne(int yOne)
{
    this -> yOne = yOne;
}

void tile::setXTwo(int xTwo)
{
    this -> xTwo = xTwo;
}

void tile::setYTwo(int yTwo)
{
    this -> yTwo = yTwo;
}

void tile::setXThree(int xThree)
{
    this -> xThree = xThree;
}

void tile::setYThree(int yThree)
{
    this -> yThree = yThree;
}

void tile::setNext(tile* next)
{
    this -> next = next;
}

void tile::setSplit(tile* split)
{
    this -> split = split;
}

////////////////////////////////////////////////////////////

string tile::getInfo()
{
    return info;
}

int tile::getPayout()
{
    return payout;
}

tileFunction tile::getTilePurpose()
{
    return tilePurpose;
}

int tile::getXOne()
{
    return xOne;
}

int tile::getYOne()
{
    return yOne;
}

int tile::getXTwo()
{
    return xTwo;
}

int tile::getYTwo()
{
    return yTwo;
}

int tile::getXThree()
{
    return xThree;
}

int tile::getYThree()
{
    return yThree;
}

tile* tile::getNext()
{
    return next;
}

tile* tile::getSplit()
{
    return split;
}
