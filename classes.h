

int spinSpinner(WINDOW*&);




class player
{
public:
    //Constructor
    player()
    {
        /*cout << "Creating a Player" << endl;*/

        job.salary = 0;money = 0;lifeCards = 0;kidCount = 0;
        interfaceX = 0;interfaceY=0;
        spouse = '_';kid1 = ' ';kid2 = '_';kid3 = ' ';kid4 = '_';
        location = NULL;
        missTurn = false;
    }

    //Destructor
    ~player() { /*cout << "Destroying a Player" << endl;*/ }

    /*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ***********************************************************************************************************************************
    *//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //Member Methods
    void printCar(WINDOW*& window)
    {
        //Draw Car
        mvwprintw(window, interfaceY + 0, interfaceX, "_________");
        mvwprintw(window, interfaceY + 1, interfaceX, "|        \\");
        mvwprintw(window, interfaceY + 2, interfaceX, "|         |");
        mvwprintw(window, interfaceY + 3, interfaceX, "|________/");

        //Print Information
        mvwprintw(window, interfaceY + 5, interfaceX, "                      ");
        mvwprintw(window, interfaceY + 5, interfaceX, "Name:       " );
        mvwprintw(window, interfaceY + 5, interfaceX + 12, name.c_str());

        mvwprintw(window, interfaceY + 6, interfaceX, "                      ");
        mvwprintw(window, interfaceY + 6, interfaceX, "Salary:     $");
        mvwprintw(window, interfaceY + 6, interfaceX + 13, "%d", job.salary);

        mvwprintw(window, interfaceY + 7, interfaceX, "                      ");
        mvwprintw(window, interfaceY + 7, interfaceX, "Money:      $");
        mvwprintw(window, interfaceY + 7, interfaceX + 13, "%d", money);

        mvwprintw(window, interfaceY + 8, interfaceX, "                      ");
        mvwprintw(window, interfaceY + 8, interfaceX, "Life Cards: ");
        mvwprintw(window, interfaceY + 8, interfaceX + 12, "%d", lifeCards);

        //Print Family
        if(gender == 'M')
        {
            mvwaddch(window, interfaceY + 1, interfaceX + 7, gender | COLOR_PAIR(4));
        }
        else if(gender =='F')
        {
            mvwaddch(window, interfaceY + 1, interfaceX + 7, gender | COLOR_PAIR(3));
        }
        /////////////////////////////////////////////
        if(spouse == 'M')
        {
            mvwaddch(window, interfaceY + 3, interfaceX + 7, spouse | COLOR_PAIR(4));
        }
        else if(spouse =='F')
        {
            mvwaddch(window, interfaceY + 3, interfaceX + 7, spouse | COLOR_PAIR(3));
        }
        /////////////////////////////////////////////
        if(kid1 == 'B')
        {
            mvwaddch(window, interfaceY + 1, interfaceX + 5, kid1 | COLOR_PAIR(4));
        }
        else if(kid1 =='G')
        {
            mvwaddch(window, interfaceY + 1, interfaceX + 5, kid1 | COLOR_PAIR(3));
        }
        //////////////////////////////////////////////
        if(kid2 == 'B')
        {
            mvwaddch(window, interfaceY + 3, interfaceX + 5, kid2 | COLOR_PAIR(4));
        }
        else if(kid2 =='G')
        {
            mvwaddch(window, interfaceY + 3, interfaceX + 5, kid2 | COLOR_PAIR(3));
        }
        //////////////////////////////////////////////
        if(kid3 == 'B')
        {
            mvwaddch(window, interfaceY + 1, interfaceX + 3, kid3 | COLOR_PAIR(4));
        }
        else if(kid3 =='G')
        {
            mvwaddch(window, interfaceY + 1, interfaceX + 3, kid3 | COLOR_PAIR(3));
        }
        //////////////////////////////////////////////
        if(kid4 == 'B')
        {
            mvwaddch(window, interfaceY + 3, interfaceX + 3, kid4 | COLOR_PAIR(4));
        }
        else if(kid4 =='G')
        {
            mvwaddch(window, interfaceY + 3, interfaceX + 3, kid4 | COLOR_PAIR(3));
        }
        //////////////////////////////////////////////
    }

    void printPlayer(WINDOW*& window)
    {
        char firstLetter = name.at(0);
        init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(8, COLOR_BLUE, COLOR_BLACK);
        if(getGender() == 'M')
        {
            mvwaddch(window, getYCoord(), getXCoord(), firstLetter | COLOR_PAIR(8));
        }
        else if(getGender() == 'F')
        {
            mvwaddch(window, getYCoord(), getXCoord(), firstLetter | COLOR_PAIR(7));
        }
        wrefresh(window);
    }

    void clearPlayer(WINDOW*& window)
    {
        mvwaddch(window, getYCoord(), getXCoord(), ' ');
        wrefresh(window);
    }

    void makeUserPlayer(WINDOW*& window)
    {
        bool goodInput = false;
        setX(73);
        setY(21);

        //gender
        while(goodInput != true)
        {
            mvwprintw(window, 0, 0, "Are you (M)ale or (F)emale: ");
            char userGender;
            wmove(window, 0, 28);
            userGender = wgetch(window);
            userGender = toupper(userGender);

            if(userGender == 'M' || userGender == 'F')
            {
                goodInput = true;
                gender = userGender;
            }
            else
            {
                goodInput = false;
            }
        }


        goodInput = false;

        //name
        while(goodInput != true)
        {
            werase(window);
            mvwprintw(window, 0, 0, "What is your name: ");
            string userName;

            int x = 19; int y = 0; wmove(window, y, x);
            int letterCounter = 0;
            char ch;
            echo();
            while(letterCounter < 12 && ch != '\n')
            {
                ch = wgetch(window);
                if(ch == '\n')
                {
                    break;
                }
                else
                {
                    userName.push_back(ch);
                    mvwaddch(window, y, x, ch);
                }
                letterCounter++;
                x++;
            }

            //userName = string(charName);



            if(userName.size() > 12)
            {
                goodInput = false;
            }
            else
            {
                goodInput = true;
                name = userName;
                name = name.substr(0, letterCounter);
            }
        }
        noecho();
        werase(window);
    }

    void makeAIPlayer()
    {
        int testInt;

        //gender
        testInt = rand() % 2;
        char compGender;
        if(testInt == 0)
        {
            compGender = 'M';
        }
        else
        {
            compGender = 'F';

        }
        setGender(compGender);

        //name
        string boyNames[3] = {"Terry", "Bill", "Alex"};
        string girlNames[3] = {"Nicole", "Lisa", "Aphrodite"};
        testInt = rand() % 3;
        if(compGender == 'M')
        {
            setName(boyNames[testInt]);
        }
        else
        {
            setName(girlNames[testInt]);
        }
    }

    void getMarried()
    {//Sorry, for simplicity of code design there will be no Gay/Lesbian Marriage.
        if(gender == 'M')
        {
            setSpouse('F');
        }
        else
        {
            setSpouse('M');
        }
    }

    void haveKid(WINDOW* window, char kidGender)
    {
        int interfacePrintX = 77;
        int interfacePrintY = 5;
        if(kid1 == ' ')
        {
            kid1 = kidGender;
            addKid();
        }
        else if(kid2 == '_')
        {
            kid2 = kidGender;
            addKid();
        }
        else if(kid3 == ' ')
        {
            kid3 = kidGender;
            addKid();
        }
        else if(kid4 == '_')
        {
            kid4 = kidGender;
            addKid();
        }
        else
        {
            mvwprintw(window, interfacePrintY, interfacePrintX, "You can't have anymore kids.");
            wrefresh(window);
            getch();
            mvwprintw(window, interfacePrintY, interfacePrintX, "                            ");
            wrefresh(window);
        }
    }

    void twins(WINDOW* interfaceWindow)
    {
        int interfacePrintX = 77;
        int interfacePrintY = 5;

        if(kidCount <= 2)
        {
            int randomTwins = rand() % 4;

            if(randomTwins == 0)
            {
                haveKid(interfaceWindow, 'B');
                haveKid(interfaceWindow, 'B');
            }
            else if(randomTwins == 1)
            {
                haveKid(interfaceWindow, 'G');
                haveKid(interfaceWindow, 'G');
            }
            else if(randomTwins == 2)
            {
                haveKid(interfaceWindow, 'B');
                haveKid(interfaceWindow, 'G');
            }
            else if(randomTwins == 3)
            {
                haveKid(interfaceWindow, 'G');
                haveKid(interfaceWindow, 'B');
            }
        }

        else
        {
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "You can't possibly have twins!");
            wrefresh(interfaceWindow);
            getch();
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                ");
            wrefresh(interfaceWindow);
        }
    }

    void startGame(WINDOW*& interfaceWindow, bool userOrNot)
    {
        int interfacePrintX = 77;
        int interfacePrintY = 5;
        bool goodInput = false;

        if(userOrNot == true)
        {
            mvwprintw(interfaceWindow, interfacePrintY + 1, interfacePrintX, "                                      ");
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "Would you like to go to (C)ollege or start your (L)ife?");
            wrefresh(interfaceWindow);

            while(goodInput != true)
            {
                char startDecision = getch();
                startDecision = toupper(startDecision);

                if(startDecision == 'C' || startDecision == 'L')
                {
                    goodInput = true;

                    if(startDecision == 'C')
                    {
                        setLocation(location -> getNext());
                        addMoney(-100000);
                    }
                    if(startDecision == 'L')
                    {
                        setLocation(location -> getSplit());
                    }
                }
                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 2;

            if(randChoice == 0)
            {
                setLocation(location -> getNext());
                addMoney(-100000);
            }
            else if(randChoice == 1)
            {
                setLocation(location -> getSplit());
            }
        }

        mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                                       ");
        wrefresh(interfaceWindow);
    }

    void chooseJob(WINDOW*& interfaceWindow, vector<career>& careerList, bool userOrNot)
    {
        int interfacePrintX = 77;
        int interfacePrintY = 5;

        mvwprintw(interfaceWindow, interfacePrintY-2, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                            ");
        wrefresh(interfaceWindow);

        bool loopFinish = false;

        career jobOne;
        career jobTwo;
        career jobThree;

        int randomOne;
        int randomTwo;
        int randomThree;

        while(loopFinish != true)
        {
            randomOne = rand() % careerList.size();
            randomTwo = rand() % careerList.size();
            randomThree = rand() % careerList.size();
            if(randomOne == randomTwo || randomTwo == randomThree || randomOne == randomThree)
            {
                loopFinish = false;
            }
            else
            {
                loopFinish = true;
            }
        }

        jobOne = careerList.at(randomOne);
        jobTwo = careerList.at(randomTwo);
        jobThree = careerList.at(randomThree);

        if(userOrNot == true)
        {
            mvwprintw(interfaceWindow, interfacePrintY-2, interfacePrintX, "Choose a Career: ");

            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX, "(1) ");
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX+4, jobOne.title.c_str());
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX+22, "Salary: $");
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX+31, "%d", jobOne.salary);

            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "(2) ");
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX+4, jobTwo.title.c_str());
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX+22, "Salary: $");
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX+31, "%d", jobTwo.salary);

            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "(3) ");
            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX+4, jobThree.title.c_str());
            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX+22, "Salary: $");
            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX+31, "%d", jobThree.salary);

            wrefresh(interfaceWindow);

            bool goodInput = false;

            while(goodInput != true)
            {
                char jobDecision = getch();
                if(jobDecision == '1' || jobDecision == '2' || jobDecision == '3')
                {
                    goodInput = true;

                    if(jobDecision == '1')
                    {
                        setJob(jobOne);
                        careerList.erase(careerList.begin() + randomOne);
                    }
                    else if(jobDecision == '2')
                    {
                        setJob(jobTwo);
                        careerList.erase(careerList.begin() + randomTwo);
                    }
                    else if(jobDecision == '3')
                    {
                        setJob(jobThree);
                        careerList.erase(careerList.begin() + randomThree);
                    }
                }
                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 3;

            if(randChoice == 0)
            {
                setJob(jobOne);
                careerList.erase(careerList.begin() + randomOne);
            }

            else if(randChoice == 1)
            {
                setJob(jobTwo);
                careerList.erase(careerList.begin() + randomTwo);
            }

            else if(randChoice == 2)
            {
                setJob(jobThree);
                careerList.erase(careerList.begin() + randomThree);
            }
        }



        mvwprintw(interfaceWindow, interfacePrintY-2, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                            ");
        wrefresh(interfaceWindow);
    }

    void chooseHouse(WINDOW*& interfaceWindow, vector<house>& houseList, bool userOrNot)
    {
        int interfacePrintX = 77;
        int interfacePrintY = 5;

        if(home.name.size() > 1)
        {
            money = money + home.worth; // for buying second house and selling other
        }

        mvwprintw(interfaceWindow, interfacePrintY-2, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                            ");
        wrefresh(interfaceWindow);

        bool loopFinish = false;

        house houseOne;
        house houseTwo;
        house houseThree;

        int randomOne;
        int randomTwo;
        int randomThree;

        while(loopFinish != true)
        {
            randomOne = rand() % houseList.size();
            randomTwo = rand() % houseList.size();
            randomThree = rand() % houseList.size();
            if(randomOne == randomTwo || randomTwo == randomThree || randomOne == randomThree)
            {
                loopFinish = false;
            }
            else
            {
                loopFinish = true;
            }
        }

        houseOne = houseList.at(randomOne);
        houseTwo = houseList.at(randomTwo);
        houseThree = houseList.at(randomThree);

        if(userOrNot == true)
        {
            mvwprintw(interfaceWindow, interfacePrintY-2, interfacePrintX, "Choose a House: ");

            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX, "(1) ");
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX+4, houseOne.name.c_str());
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX+22, "Cost: $");
            mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX+28, "%d", houseOne.cost);

            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "(2) ");
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX+4, houseTwo.name.c_str());
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX+22, "Cost: $");
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX+28, "%d", houseTwo.cost);

            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "(3) ");
            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX+4, houseThree.name.c_str());
            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX+22, "Cost: $");
            mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX+28, "%d", houseThree.cost);

            wrefresh(interfaceWindow);

            bool goodInput = false;

            while(goodInput != true)
            {
                char houseDecision = getch();
                if(houseDecision == '1' || houseDecision == '2' || houseDecision == '3')
                {
                    goodInput = true;

                    if(houseDecision == '1')
                    {
                        setHome(houseOne);
                        houseList.erase(houseList.begin() + randomOne);
                    }
                    else if(houseDecision == '2')
                    {
                        setHome(houseTwo);
                        houseList.erase(houseList.begin() + randomTwo);
                    }
                    else if(houseDecision == '3')
                    {
                        setHome(houseThree);
                        houseList.erase(houseList.begin() + randomThree);
                    }

                    money = money - home.cost;
                }
                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 3;

            if(randChoice == 0)
            {
                setHome(houseOne);
                houseList.erase(houseList.begin() + randomOne);
            }

            else if(randChoice == 1)
            {
                setHome(houseTwo);
                houseList.erase(houseList.begin() + randomTwo);
            }

            else if(randChoice == 2)
            {
                setHome(houseThree);
                houseList.erase(houseList.begin() + randomThree);
            }
        }

        mvwprintw(interfaceWindow, interfacePrintY-2, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY-1, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                            ");
        mvwprintw(interfaceWindow, interfacePrintY+1, interfacePrintX, "                                            ");
        wrefresh(interfaceWindow);
    }

    void payday()
    {
        money = money + job.salary;
    }

    void payRaise()
    {
        if(job.salary + 10000 <= job.maxSalary)
        {
            job.salary = job.salary + 10000;
        }
        payday();
    }

    void applyPayout(int payout)
    {
        money = money + payout;
    }

    void loseJob(WINDOW*& interfaceWindow, vector<career>& jobs, vector<career>& careers, bool userOrNot)
    {
        career tempJob = getJob();

        chooseJob(interfaceWindow, jobs, userOrNot);

        if(tempJob.type == "JOB")
        {
            jobs.push_back(tempJob);
        }
        else if(tempJob.type == "CAREER")
        {
            careers.push_back(tempJob);
        }
    }

    void payTaxes()
    {
        money = money - job.taxes;
    }

    void taxRefund()
    {
        money = money + job.taxes;
    }

    void spinToWin(WINDOW*& interfaceWindow, WINDOW*& spinnerWindow, bool userOrNot)
    {
        int interfacePrintX = 77;
        int interfacePrintY = 5;
        bool goodInput = false;
        char charChoice;
        char charBet;
        int numChoice;
        int numBet;

        if(userOrNot == true)
        {
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "Choose a number to bet on: 1 - 9 and 0 for 10: ");
            wrefresh(interfaceWindow);
            while(goodInput != true)
            {
                charChoice = getch();
                numChoice = charChoice - 48;

                if(numChoice > 9 || numChoice < 0)
                {
                    goodInput = false;
                }
                else
                {
                    goodInput = true;
                }
            }
            goodInput = false;

            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "Choose an amount(ten thousands): 1 - 9 and 0 for 10: ");
            wrefresh(interfaceWindow);
            while(goodInput != true)
            {
                charBet = getch();
                numBet = charBet - 48;

                if(numBet > 9 || numBet < 0)
                {
                    goodInput = false;
                }
                else
                {
                    goodInput = true;
                }
            }
        }

        else if(userOrNot == false)
        {
            numChoice = rand() % 10;
            numBet = rand() % 10;
        }

        if(userOrNot == true)
        {
            mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                                       ");
            wrefresh(interfaceWindow);

            int spin = spinSpinner(spinnerWindow);
            if(spin == numChoice)
            {
                mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "You won!");
                wrefresh(interfaceWindow);
                money = money + (numBet * 10000);
            }
            else
            {
                mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "You lose!");
                wrefresh(interfaceWindow);
                money = money - (numBet * 10000);
            }
        }

        else if(userOrNot == false)
        {
            int spin = spinSpinner(spinnerWindow);
            if(spin == numChoice)
            {
                money = money + (numBet * 10000);
            }
            else
            {
                money = money - (numBet * 10000);
            }
        }

        mvwprintw(interfaceWindow, interfacePrintY, interfacePrintX, "                                                       ");
        wrefresh(interfaceWindow);

    }

    void spinForMoney(WINDOW*& spinnerWindow)
    {
        int spin = spinSpinner(spinnerWindow);
        money = money + (spin * 10000);
    }

    void lawsuit(player*& opponent1, player*& opponent2)
    {
        int randomOpponentChoice = rand() % 2;

        money = money + 100000;

        if(randomOpponentChoice == 0)
        {
            opponent1 -> addMoney(-100000);
        }
        else if(randomOpponentChoice == 1)
        {
            opponent2 -> addMoney(-100000);
        }
    }

    void fivePerKid()
    {
        money = money - (kidCount * 5000);
    }

    void fiftyPerKid()
    {
        money = money - (kidCount * 50000);
    }

    void twentyFivePlusFivePerKid()
    {
        money = money - 25000 - (kidCount * 5000);
    }

    void dayCare(player*& opponent1, player*& opponent2)
    {
        money = money + (opponent1 -> getKidCount() * 5000) + (opponent2 -> getKidCount() * 5000);
        opponent1 -> addMoney(-(opponent1 -> getKidCount() * 5000));
        opponent2 -> addMoney(-(opponent2 -> getKidCount() * 5000));
    }

    void returnToSchool(bool userOrNot)
    {
        if(userOrNot == true)
        {
            bool goodInput = false;

            while(goodInput != true)
            {
                char userInput = getch();
                userInput = toupper(userInput);

                if(userInput == 'S')
                {
                    goodInput = true;
                    money = money - 50000;
                    setLocation(getLocation() -> getSplit());
                }

                else if(userInput == 'C')
                {
                    goodInput = true;
                    setLocation(getLocation() -> getNext());
                }

                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 2;

            if(randChoice == 0)
            {
                setLocation(getLocation() -> getSplit());
            }
            else if(randChoice == 1)
            {
                setLocation(getLocation() -> getNext());
            }
        }
    }

    void pathOfLife(bool userOrNot)
    {
        if(userOrNot == true)
        {
            bool goodInput = false;

            while(goodInput != true)
            {
                char userInput = getch();
                userInput = toupper(userInput);

                if(userInput == 'C')
                {
                    goodInput = true;
                    setLocation(getLocation() -> getSplit());
                }

                else if(userInput == 'F')
                {
                    goodInput = true;
                    setLocation(getLocation() -> getNext());
                }

                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 2;

            if(randChoice == 0)
            {
                setLocation(getLocation() -> getSplit());
            }
            else if(randChoice == 1)
            {
                setLocation(getLocation() -> getNext());
            }
        }
    }

    void riskyOrSafe(bool userOrNot)
    {
        if(userOrNot == true)
        {
            bool goodInput = false;

            while(goodInput != true)
            {
                char userInput = getch();
                userInput = toupper(userInput);

                if(userInput == 'S')
                {
                    goodInput = true;
                    setLocation(getLocation() -> getSplit());
                }

                else if(userInput == 'R')
                {
                    goodInput = true;
                    setLocation(getLocation() -> getNext());
                }

                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 2;

            if(randChoice == 0)
            {
                setLocation(getLocation() -> getSplit());
            }
            else if(randChoice == 1)
            {
                setLocation(getLocation() -> getNext());
            }
        }
    }

    void chooseCareerOrPayRaise(WINDOW*& interfaceWindow, bool userOrNot, vector<career> collegeCareers)
    {
        if(userOrNot == true)
        {
            bool goodInput = false;

            while(goodInput != true)
            {
                char userInput = getch();
                userInput = toupper(userInput);

                if(userInput == 'C')
                {
                    goodInput = true;
                    chooseJob(interfaceWindow, collegeCareers, userOrNot);
                }

                else if(userInput == 'P')
                {
                    goodInput = true;
                    if(job.salary + 20000 <= job.maxSalary)
                    {
                        job.salary = job.salary + 20000;
                    }
                }

                else
                {
                    goodInput = false;
                }
            }
        }

        else if(userOrNot == false)
        {
            int randChoice = rand() % 2;

            if(randChoice == 0)
            {
                chooseJob(interfaceWindow, collegeCareers, userOrNot);
            }
            else if(randChoice == 1)
            {
                if(job.salary + 20000 <= job.maxSalary)
                {
                    job.salary = job.salary + 20000;
                }
            }
        }
    }

    void totalFunds()
    {
        money = money + home.worth;

        for(int i = 0; i < lifeCards; i++)
        {
            int lifeCardValue = (rand() % 10 + 1) * 10000;
            money = money + lifeCardValue;
        }
    }

    //Accessor Methods
    void setName(string name) { this -> name = name; }
    void setLocation(tile* location) { this -> location = location; }
    void setGender(char gender) { this -> gender = gender; }
    void setJob(career job) { this -> job = job; }
    void setHome(house home) { this -> home = home; }
    void setMissTurn(bool missTurn) { this -> missTurn = missTurn; }
    void addMoney(int moneyToAdd) { money = money + moneyToAdd; }
    void addToLifeCards() { lifeCards++; }
    void setX(int xCoord) { this -> xCoord = xCoord; }
    void setY(int yCoord) { this -> yCoord = yCoord; }
    void setInterfaceX(int interfaceX) { this -> interfaceX = interfaceX; }
    void setInterfaceY(int interfaceY) { this -> interfaceY = interfaceY; }
    void setSpouse(char spouseGender) { spouse = spouseGender; }
    void addKid() { if(kidCount < 4) { kidCount++; } }
    void setKid1(char gender) { kid1 = gender; }
    void setKid2(char gender) { kid2 = gender; }
    void setKid3(char gender) { kid3 = gender; }
    void setKid4(char gender) { kid4 = gender; }

    string getName() { return name; }
    tile* getLocation() { return location; }
    char getGender() { return gender; }
    career getJob() { return job; }
    house getHome() { return home; }
    bool getMissTurn() { return missTurn; }
    int getMoney() { return money; }
    int getLifeCards() { return lifeCards; }
    int getXCoord() { return xCoord; }
    int getYCoord() { return yCoord; }
    int getInterfaceXCoord() { return interfaceX; }
    int getInterfaceYCoord() { return interfaceY; }
    char getSpouse() { return spouse; }
    int getKidCount() { return kidCount; }
    char getKid1 () { return kid1; }
    char getKid2 () { return kid2; }
    char getKid3 () { return kid3; }
    char getKid4 () { return kid4; }

//Private Data
private:
    string name;
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

