// Lemonde Stand.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

HANDLE hConsole; // Used for color changing
int day = 0;	 // Number of days of selling

void buyLemons(int lemons, double money, double price) {
	//Display current lemon proce
	cout << endl << "The price of lemons today is $" << price << endl;
	//Ask user to enter how many they want
	cout << "Each cup of lemonade requires 2 lemons. You will lose 10% of your unused lemon supply each day due to spoileage." << endl << endl;
	cout << "How many do you want to buy? ";
	int number;
	cin >> number;

	//Verify there is enough money and that the user is buying a valid number
	if (number * price <= money && number >= 0) {
		//Subtract cost
		money = money - number * price;
		//Add the lemons
		lemons = lemons + number;
	}
	else
	{
		cout << "You don't have enough money." << endl;
	}
}

void runDay(double& money, int& lemons, double& sugar, int temp, double rain, double price) {
	system("cls");
	srand(time(NULL)); //Prepares random numbers
	day++;



	//Compute probability that a customer will purchase
	double chance = .2; //initial chance

	//Factor temp
	int actualTemp = temp;
	int tempChange = rand() % 2;
	if (tempChange == 0) {
		actualTemp += rand() % 7;
	}
	else {
		actualTemp -= rand() % 7;
	}
	chance = chance + (actualTemp - 70) * .01;

	//Factor rain
	bool raining = rand() % 10 < rain * 10;
	if (raining) {
		chance -= .15;
	}

	//Factor price
	chance += (1.75 - price) * .20;

	//Simulate
	int totalCustomers = 0;
	double sales = 0.0;
	int hour = 9;

	for (int customer = 0; customer < 100; customer++) {
		this_thread::sleep_for(chrono::milliseconds(25));
		bool purchased = rand() % 100 < chance * 100;
		if (purchased && lemons >= 1 && sugar >= .05) {
			lemons -= 2;
			sugar -= .05;
			totalCustomers++;
			sales += price;
			money += price;
		}

		//Sales report           
		system("cls");

		//Display the day's weather
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "\n\n  Today's Temperature: ";
		if (actualTemp > 85) SetConsoleTextAttribute(hConsole, 0x0C);
		else if (actualTemp > 70) SetConsoleTextAttribute(hConsole, 0x06);
		else SetConsoleTextAttribute(hConsole, 0x0B);
		cout << actualTemp << " degrees  ";
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "   |   Skies: ";

		if (!raining) {
			SetConsoleTextAttribute(hConsole, 0x06);
			cout << "Sunny";
		}
		else {
			SetConsoleTextAttribute(hConsole, 0x0B);
			cout << "Raining";
		}

		//Time of day
		if (customer % 15 == 0) {
			hour++;
			if (hour == 13) hour = 1;
		}

		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "   |   TIME: ";

		SetConsoleTextAttribute(hConsole, 0x0A);
		cout << hour << ":00 ";
		if (hour >= 9 && hour <= 11) {
			cout << "AM  " << endl;
		}
		else {
			cout << "PM  " << endl;
		}
		cout << endl << endl;

		//Displays sales
		SetConsoleTextAttribute(hConsole, 0x71);
		cout << "--------- SALES REPORT DAY " << day << "---------" << endl;
		SetConsoleTextAttribute(hConsole, 0x1F);
		cout << "Customers Served:\t";
		SetConsoleTextAttribute(hConsole, 0x16);
		cout << totalCustomers << endl;
		SetConsoleTextAttribute(hConsole, 0x1F);
		cout << "Remaining Lemons:   \t";
		SetConsoleTextAttribute(hConsole, 0x1E);
		cout << lemons << endl;
		SetConsoleTextAttribute(hConsole, 0x1F);
		cout << "Remaining Sugar:   \t";
		SetConsoleTextAttribute(hConsole, 0x1E);
		cout << sugar << endl;
		SetConsoleTextAttribute(hConsole, 0x1F);
		cout << "Total Revenue:   \t";
		SetConsoleTextAttribute(hConsole, 0x1A);
		cout << "$" << sales << endl;


		if (lemons < 2) {
			SetConsoleTextAttribute(hConsole, 0x74);
			cout << endl << " OUT OF LEMONS " << endl;
			break;
		}
		if (sugar < .05) {
			SetConsoleTextAttribute(hConsole, 0x74);
			cout << endl << " OUT OF SUGAR " << endl;
			break;
		}

	}

	SetConsoleTextAttribute(hConsole, 0x1F);
	cout << endl << "< END OF DAY " << day << " >" << endl << endl;

	if (lemons > 2) {
		//Spoileage
		int loss = ceil(lemons * .1);
		SetConsoleTextAttribute(hConsole, 0x16);
		cout << endl << loss << " lemon(s) lost due to spoileage." << endl;
		lemons -= loss;
	}
}


int main()
{
	system("color 1F"); //Initial screen color
	cout << setprecision(2) << fixed; //2 decimal palces for currency
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Used for changing colors


	double money = 10;									//Total money, starts at $50
	int lemons = 30;									//Number of lemons
	double sugarBags = 2;								//Number of bags of sugar
	int predictedTemp = 70;								//Predicted temperature
	double rainChance = .1;								//% chance of rain
	double pricePerCup = 1.75;							//What we charge per cup of lemonade
	double lemonPrice = .75;							//Initial price of one lemon
	bool gameOver = false;

	//SHOW THE TITLE SCREEN
	SetConsoleTextAttribute(hConsole, 0x16);
	cout << "************************************************\n";
	cout << "*             LEMONADE TYCOON 1.0              *\n";
	cout << "************************************************\n\n";
	SetConsoleTextAttribute(hConsole, 0x1F);
	cout << "The object of this game is to make as much money as possible." << endl;
	cout << "Before each day begins you may:" << endl;
	SetConsoleTextAttribute(hConsole, 0x16);
	cout << "  -> View the weather forcast" << endl;
	cout << "  -> Change the price of a cup" << endl;
	cout << "  -> Purchase ingredients" << endl;
	SetConsoleTextAttribute(hConsole, 0x1F);
	cout << "\nSeveral factors will impact sales including:" << endl;
	SetConsoleTextAttribute(hConsole, 0x16);
	cout << "  -> The weather" << endl;
	cout << "  -> The price of a cup" << endl;
	cout << "  -> Having enough ingredients to meet the demand" << endl << endl;
	SetConsoleTextAttribute(hConsole, 0x1F);
	system("pause");
	system("cls");
	//END TITLE SCREEN
	

	string menuChoice = "";

	while (menuChoice != "6" && !gameOver) {
		//DISPLAY CURRENT STATS
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << endl << "     CURRENT CASH: ";
		SetConsoleTextAttribute(hConsole, 0x0A);
		cout << "$" << money;
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "   |   LEMONS: ";
		SetConsoleTextAttribute(hConsole, 0x06);
		cout << lemons;
		SetConsoleTextAttribute(hConsole, 0x0F);
		cout << "   |   BAGS OF SUGAR: ";
		SetConsoleTextAttribute(hConsole, 0x0B);
		cout << sugarBags << "     " << endl << endl;
		SetConsoleTextAttribute(hConsole, 0x0F);
		//END DISPLAY CURRENT STATS


		//MENU CHOICES AND USER INPUT
		SetConsoleTextAttribute(hConsole, 0x1B);
		cout << endl << "WHAT WOULD YOU LIKE TO DO?" << endl;
		cout << "--------------------------" << endl;
		SetConsoleTextAttribute(hConsole, 0x1F);
		cout << "  1. See the weather forcast" << endl;
		cout << "  2. Change pricing" << endl;
		cout << "  3. Buy lemons" << endl;
		cout << "  4. Buy sugar" << endl;
		cout << "  5. Begin the day" << endl;
		cout << "  6. Retire from the lemonade business" << endl << endl;
		SetConsoleTextAttribute(hConsole, 0x1A);
		cout << "Enter an option: ";
		cin >> menuChoice;
		//END MENU CHOICES AND USER INPUT

		if (menuChoice == "1") {
			//Tomorrow's forcast
			SetConsoleTextAttribute(hConsole, 0x61);
			cout << "\n\nTOMORROW'S WEATHER - > ";

			//DISPLAY THE WEATHER FORECAST
			cout << rainChance << " " << predictedTemp << endl;
			//END WEATHER FORECAST		

			SetConsoleTextAttribute(hConsole, 0x1F);
		}
		else if (menuChoice == "2") {
			//SET PRICE PER CUP
			SetConsoleTextAttribute(hConsole, 0xF1);
			cout << "The current price of a cup is: ";
			SetConsoleTextAttribute(hConsole, 0xFA);
			cout << "$" << pricePerCup << endl;
			SetConsoleTextAttribute(hConsole, 0x1F);
			SetConsoleTextAttribute(hConsole, 0x1A);
			cout << "What should the new price be? $";
			cin >> pricePerCup;
			SetConsoleTextAttribute(hConsole, 0x1F);
		}
		else if (menuChoice == "3") {
			//BUY LEMONS
			buyLemons(lemons, money, lemonPrice); 
		}
		else if (menuChoice == "4") {
			//BUY SUGAR	
		}
		else if (menuChoice == "5") {
			//RUN THE NEXT DAY
			runDay(money, lemons, sugarBags, predictedTemp, rainChance, pricePerCup);
			
			//Next day's weather
			rainChance = rand() % 100 / 100.0;
			predictedTemp = rand() % 40 + 60;
			//Next day's lemon price
			lemonPrice = (rand() % 75) / 100.0 + .25;
		}
		else if (menuChoice == "6") {
			//RETIRE
			break;
		}
		else {
			//INVALID CHOICE
			SetConsoleTextAttribute(hConsole, 0x14);
			cout << "Invalid menu choice." << endl;
		}

	
		//END OF GAME
		if (day == 14) {
			gameOver = true;
			SetConsoleTextAttribute(hConsole, 0xFA);
			cout << " YOU HAVE REACHED THE END OF THE GAME. YOU RETIRE WITH $" << money << " " << endl << endl;
		}
		else if (lemons < 2 && money < lemonPrice) {
			gameOver = true;
			cout << "YOU LOSE. YOU RAN OUT OF LEMONS AND DON'T HAVE ENOUGH MONEY TO BUY MORE." << endl << endl;
		}
		else if (sugarBags < .05 && money < 5) {
			gameOver = true;
			cout << "YOU LOSE. YOU RAN OUT OF SUGAR AND DON'T HAVE ENOUGH MONEY TO BUY MORE." << endl << endl;
		}

		SetConsoleTextAttribute(hConsole, 0x1F);
		system("pause");
		system("cls");
	}
	system("pause");
}
