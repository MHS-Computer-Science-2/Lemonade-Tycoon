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
	cout << "Each cup of lemonade requires 2 lemons. You will lose 8% of your unused lemon supply each day due to spoileage." << endl << endl;
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

void displayNewsHeadline(int event) {

	SetConsoleTextAttribute(hConsole, 0x71);
	cout << "\n========= BREAKING NEWS =========\n";
	SetConsoleTextAttribute(hConsole, 0x1F);

	switch (event) {
	case 0:  cout << "Local man claims water is 'spicy lemonade.' Scientists concerned.\n"; break;
	case 1:  cout << "City Marathon Today. Thousands of exhausted runners incoming.\n"; break;
	case 2:  cout << "Citrus Blight Spreads! Lemons now considered a luxury item.\n"; break;
	case 3:  cout << "Teen influencer declares lemonade 'basic.' Internet divided.\n"; break;
	case 4:  cout << "National Lemon Glut! Farmers accidentally grew too many lemons.\n"; break;
	case 5:  cout << "Breaking: Study finds lemonade improves math test scores.\n"; break;
	case 6:  cout << "Sugar shipment delayed after driver stops for 'just one more donut.'\n"; break;
	case 7:  cout << "Local dentist warns: 'Too much lemonade may cause smiling.'\n"; break;
	case 8:  cout << "Mysterious lemon-themed flash mob scheduled downtown.\n"; break;
	case 9:  cout << "Health trend claims cold water is the new lemonade.\n"; break;
	case 10: cout << "International Lemon Summit collapses. Tariffs on citrus incoming.\n"; break;
	case 11: cout << "Underground lemon smuggling ring busted. Black market shaken.\n"; break;
	case 12: cout << "Community picnic announced. Hydration strongly encouraged.\n"; break;
	case 13: cout << "Local gym bans soda. Trainer recommends 'natural lemonade gains.'\n"; break;
	case 14: cout << "Breaking: Lemon-scented candles recalled after attracting bees.\n"; break;
	case 15: cout << "City council declares today 'Official Hydration Day.'\n"; break;
	case 16: cout << "Luxury chef features lemonade reduction sauce. Citrus demand spikes.\n"; break;
	case 17: cout << "Cargo ship overcorrects. Accidentally delivers 40 tons of lemons.\n"; break;
	case 18: cout << "Viral video claims lemonade cures boredom. Internet divided.\n"; break;
	case 19: cout << "Town installs 47 new water fountains. Hydration now free.\n"; break;
	case 20: cout << "Local celebrity spotted drinking lemonade downtown.\n"; break;
	case 21: cout << "Economists warn of 'Citrus Bubble' forming in markets.\n"; break;
	case 22: cout << "School fundraiser sells out of lemonade in record time.\n"; break;
	case 23: cout << "New energy drink launches. Teen loyalty tested.\n"; break;
	case 24: cout << "Farmers union announces temporary lemon export pause.\n"; break;
	case 25: cout << "Neighborhood block party scheduled. Large crowds expected.\n"; break;
	case 26: cout << "Investigative report questions 'artificial lemon flavor' industry.\n"; break;
	default: cout << "Nothing happened. News anchors visibly disappointed.\n"; break;
	}

	cout << "==================================\n\n";
}

void applyNewsEffects(int event, double& lemonPrice, double& demandModifier) {
	switch (event) {
	case 0:  demandModifier -= 0.08; break;
	case 1:  demandModifier += 0.18; break;
	case 2:  lemonPrice += 0.35; break;
	case 3:  demandModifier -= 0.10; break;
	case 4:  if (lemonPrice > 0.35) lemonPrice -= 0.25; break;
	case 5:  demandModifier += 0.12; break;
	case 6:  demandModifier -= 0.07; break;
	case 7:  demandModifier -= 0.05; break;
	case 8:  demandModifier += 0.20; break;   // big hype day
	case 9:  demandModifier -= 0.09; break;
	case 10: lemonPrice += 0.30; break;
	case 11: lemonPrice += 0.22; break;
	case 12: demandModifier += 0.15; break;
	case 13: demandModifier += 0.14; break;
	case 14: demandModifier -= 0.08; break;
	case 15: demandModifier += 0.18; break;
	case 16: lemonPrice += 0.25; break;
	case 17: if (lemonPrice > 0.40) lemonPrice -= 0.30; break;
	case 18: demandModifier += 0.16; break;
	case 19: demandModifier -= 0.18; break;
	case 20: demandModifier += 0.14; break;
	case 21: lemonPrice += 0.20; break;
	case 22: demandModifier += 0.16; break;
	case 23: demandModifier -= 0.12; break;
	case 24: lemonPrice += 0.28; break;
	case 25: demandModifier += 0.18; break;
	case 26: demandModifier -= 0.10; break;
	default: break;
	}
}

void runDay(double& money, int& lemons, double& sugar, int temp, double rain, double price, double demandModifier) {
	system("cls");
	srand(time(0)); //Prepares random numbers
	day++;



	//Compute probability that a customer will purchase
	double chance = .25; //initial chance

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
		chance -= .12;
	}

	//Factor price
	double priceFactor = 1.0 - (price - 1.75) * .25;
	if (priceFactor > 1.25) priceFactor = 1.25;  // small bonus for cheap pricing
	if (priceFactor < 0.0)  priceFactor = 0.0;
	chance = chance * priceFactor;

	//Factor news event
	chance += demandModifier;

	//Final demand clamp
	if (priceFactor <= 0) chance = 0; //prevent high pricing exploit
	else if (chance < 0.05) chance = 0.05;
	else if (chance > 0.85) chance = 0.85;

	//Simulate
	int totalCustomers = 0;
	double sales = 0.0;
	int hour = 9;

	for (int customer = 0; customer < 120; customer++) {
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

		// cout << chance << endl;


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
		int loss = ceil(lemons * .08);
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


	double money = 10;									//Total money, starts at $10
	int lemons = 30;									//Number of lemons
	double sugarBags = 2;								//Number of bags of sugar
	int predictedTemp = 70;								//Predicted temperature
	double rainChance = .1;								//% chance of rain
	double pricePerCup = 1.75;							//What we charge per cup of lemonade
	double lemonPrice = .75;							//Initial price of one lemon
	bool gameOver = false;
	double demandModifier = 0.0;
	int eventType = rand() % 35;

	//SHOW THE TITLE SCREEN
	SetConsoleTextAttribute(hConsole, 0xE0);
	cout << "==============================================================\n";
	cout << "                  L E M O N A D E   T Y C O O N               \n";
	cout << "==============================================================\n";
	cout << "                   A Retro Business Simulation                \n";
	cout << "==============================================================\n\n";

	SetConsoleTextAttribute(hConsole, 0x1F);
	cout << "Welcome, Entrepreneur.\n\n";
	cout << "You have 14 days to build your lemonade empire.\n";
	cout << "Buy ingredients. Set prices. Outsmart the market.\n\n";

	cout << "Before each day you may:\n\n";

	SetConsoleTextAttribute(hConsole, 0x12);
	cout << "   1) View the weather forecast\n";
	cout << "   2) Check the news\n";
	cout << "   3) Change the price per cup\n";
	cout << "   4) Purchase ingredients\n";

	SetConsoleTextAttribute(hConsole, 0x1F);
	cout << "\nSales depend on:\n\n";

	SetConsoleTextAttribute(hConsole, 0x16);
	cout << "   - Weather\n";
	cout << "   - News Events\n";
	cout << "   - Your Pricing Strategy\n";
	cout << "   - Inventory Management\n\n";

	SetConsoleTextAttribute(hConsole, 0x1F);
	system("pause");
	system("cls");
	//END TITLE SCREEN


	string menuChoice = "";

	while (menuChoice != "7" && !gameOver) {
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
		cout << "  2. Check the news" << endl;
		cout << "  3. Change the lemonade price" << endl;
		cout << "  4. Buy lemons" << endl;
		cout << "  5. Buy sugar" << endl;
		cout << "  6. Begin the day" << endl;
		cout << "  7. Retire from the lemonade business" << endl << endl;
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
			displayNewsHeadline(eventType);
		}
		else if (menuChoice == "3") {
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
		else if (menuChoice == "4") {
			//BUY LEMONS
			buyLemons(lemons, money, lemonPrice);
		}
		else if (menuChoice == "5") {
			//BUY SUGAR	
		}
		else if (menuChoice == "6") {
			//RUN THE NEXT DAY
			runDay(money, lemons, sugarBags, predictedTemp, rainChance, pricePerCup);

			//Next day's weather
			rainChance = rand() % 100 / 100.0;
			predictedTemp = rand() % 40 + 60;

			//Next day's lemon price
			lemonPrice = (rand() % 61) / 100.0 + .30;

			//Next day's news
			demandModifier = 0;
			eventType = rand() % 27;
			applyNewsEffects(eventType, lemonPrice, demandModifier);
		}
		else if (menuChoice == "7") {
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




