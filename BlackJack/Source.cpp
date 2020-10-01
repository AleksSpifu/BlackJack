//Written by Aleksander Furnes

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> //For random number.
#include <time.h> //For seed for the random number.
#include <stdio.h> //For NULL for the random number.
#include <conio.h> //For _getch
#include <Windows.h> //for Sleep

void populateDeckOfCards(std::vector <int>& deck, std::vector <int>& drawn, int deckSize);
void drawCard(std::vector <int>& deck, std::vector <int>& drawn, std::vector <int>& drawnValue);
std::string printCard(int cardInput);
int calculateValueOfHeldCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore);
int housePlays(std::vector <int>& deck, std::vector <int>& houseDrawn, std::vector <int>& houseDrawnValue, int playerScore);
int calculateValueOfHouseCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore);


int main() {

	//Declare a lot of variables.
	int moneyPot = 0;
	int playerMoney = 100;
	int houseMoney = 100;
	const int deckSize = 52;
	int lastScore = 0;
	std::vector <int> drawnCards;
	std::vector <int> houseDrawnCards;
	std::vector <int> houseDrawnCardsValue;
	std::vector <int> drawnCardsValue;
	std::vector <int> deckOfCards;
	bool gameover = false;
	bool playerFinished = false;

	//Run as long as there is money to win, either from house or in the pot, or until player runs out.
	while (playerMoney > 0 && (houseMoney > 0 || moneyPot > 0)) {

		//Make sure the game runs again after first win/loss
		playerFinished = false;
		gameover = false;

		//Reset the deck so all the cards go back to their original place.
		//Also reset the cards held by the house and player, as well as the values for the Aces.
		populateDeckOfCards(deckOfCards, drawnCards, deckSize);
		drawnCards.clear();
		houseDrawnCards.clear();
		houseDrawnCardsValue.clear();
		drawnCardsValue.clear();
		lastScore = 0;

		//This is the main game.
		while (!gameover) {
			system("cls");
			std::cout << "Welcome to BlackJack! \n\nPress D to draw a new card, S to stop, or Escape to exit.\n";
			std::cout << "Press 1 to bet $10, 2 to bet $20 and so on.\n\n";
			std::cout << "You have $" << playerMoney << " and the house has $" << houseMoney << ". The pot has $" << moneyPot << " in it.\n";
			if (drawnCards.size() == 0) {
				std::cout << "There is a $10 fee for starting a game.\n";
			}

			//Display all the cards held by the player. If there are none, dislay none.
			//Also display the value of all the cards combined. 
			std::cout << "\nYou are currently holding ";
			if (drawnCards.size() > 0) {
				for (int i = 0; i < drawnCards.size(); i++) {
					std::cout << printCard(drawnCards[i]);
					if (i == drawnCards.size() - 1) {
						std::cout << ".\n";
					}
					else {
						std::cout << ", ";
					}
				}

				//Calculate function will ask for clarification on wether or not Ace should be 1 or 11.
				//Then print the total value.
				lastScore = calculateValueOfHeldCards(drawnCards, drawnCardsValue, lastScore);
				std::cout << "With a combined value of " << lastScore << "\n";
				
			}
			else {
				std::cout << "no cards.\n";
			}

			//Force the player to quit if they hit or exceed 21.
			if (lastScore >= 21) {
				playerFinished = true;
			}

			//This handles all the input for playing, stopping or exiting the program.
			//It forces both while-loops to stop by setting all the money to 0.
			//It also handles input for the betting system, which is expanded upon below.
			if (!playerFinished) {
				int betamount = 0;
				switch (tolower(_getch())) {
				case 'd':
					if (lastScore == 0) {
						playerMoney -= 10;
					}
					drawCard(deckOfCards, drawnCards, drawnCardsValue);
					
					break;
				case 's':
					playerFinished = true;
					break;
				case 27:
					gameover = true;
					playerMoney = 0;
					houseMoney = 0;
					break;
				case '1':
					betamount = 1;
					break;
				case '2':
					betamount = 2;
					break;
				case '3':
					betamount = 3;
					break;
				case '4':
					betamount = 4;
					break;
				case '5':
					betamount = 5;
					break;
				case '6':
					betamount = 6;
					break;
				case '7':
					betamount = 7;
					break;
				case '8':
					betamount = 8;
					break;
				case '9':
					betamount = 9;
					break;

				default:
					break;
				}

				//Pretty self-explanatory. It just tries to put money in the pot, and if it can't, it'll just say can't afford.
				//Then the inner while-loop will run through and pick up where it left off, allowing the user to play or bet less.
				//there is nothing stopping the player from betting $10 several times, instead of one large sum.
				if (betamount > 0) {
					if (playerMoney >= (betamount * 10) && houseMoney >= (betamount * 10)) {
						playerMoney -= (betamount * 10);
						houseMoney -= (betamount * 10);
						moneyPot += (betamount * 20);
					}
					else {
						std::cout << "\nCan't afford that bet!\n";
						system("pause");
					}
				}
				
			}

			//This just figures out who won and if it's a tie. If it's a tie, the betting pot will remain.
			//I don't know blackjack but i couldn't find out who it goes to. Also to be kind to the player, 
			//rather than immediatly say they lost if they exceed 21, i let the AI try, and if it also fails, 
			//it counts as a draw, and the money can still be won.
			if (playerFinished) {
				int houseScore = housePlays(deckOfCards, houseDrawnCards, houseDrawnCardsValue, lastScore);
				if (houseScore > 21 && lastScore > 21) {
					std::cout << "Both parties lost. The money is still in the pot.\n";
				}
				else if (houseScore > 21 && lastScore <= 21) {
					std::cout << "The player wins! You recieve $" << moneyPot;
					playerMoney += moneyPot;
					moneyPot = 0;
					std::cout << " and you now have $" << playerMoney << "!\n";
				}
				else if (houseScore <= 21 && lastScore > 21) {
					houseMoney += moneyPot;
					moneyPot = 0;
					std::cout << "The house wins! house has  $" << houseMoney;
					std::cout << " and you now have $" << playerMoney << "!\n";
				}
				else {
					if (houseScore == lastScore) {
						std::cout << "It's a draw! the money is still in the pot.\n";
					}
					else if (houseScore < lastScore) {
						std::cout << "The player wins! You recieve $" << moneyPot;
						playerMoney += moneyPot;
						moneyPot = 0;
						std::cout << " and you now have $" << playerMoney << "!\n";
					}
					else if (houseScore > lastScore) {
						houseMoney += moneyPot;
						moneyPot = 0;
						std::cout << "The house wins! house has  $" << houseMoney;
						std::cout << " and you now have $" << playerMoney << "!\n";
					}
				}
				gameover = true;
			}

		}
		system("pause");
	}

}

//This function is the brains of the house. It will draw cards, and also display everything. 
//It returns the value of all it's cards back to main for checking who won, but all the cout's are from here.
int housePlays(std::vector <int>& deck, std::vector <int>& houseDrawn, std::vector <int>& houseDrawnValue, int playerScore) {
	int counter = 0;
	int houseScore = 0;
	
	//No matter what, it will keep drawing cards until it reaches 10.
	while (houseScore < 10) {
		drawCard(deck, houseDrawn, houseDrawnValue);
		std::cout << "House draws";

		//Add some suspensful waiting time.
		for (int i = 0; i < 4; i++) {
			Sleep(125);
			std::cout << ".";
			Sleep(125);
		}

		//Tell the player what card it got.
		std::cout << " " << printCard(houseDrawn[counter]);
		Sleep(1000);

		//Then tell the player the value of the cards.
		houseScore = calculateValueOfHouseCards(houseDrawn, houseDrawnValue, houseScore);
		std::cout << " Value: " << houseScore << "\n";
		counter++;
	}

	//If the player is closer than the house, it has nothing to lose, and will keep going.
	//If the house is closer to 21 than the player, it will happily stop after 10.
	//Then do the same as above, draw card, tell the player the card and value.
	while (houseScore < playerScore && playerScore <= 21) {
		drawCard(deck, houseDrawn, houseDrawnValue);
		std::cout << "House draws";
		for (int i = 0; i < 4; i++) {
			Sleep(125);
			std::cout << ".";
			Sleep(125);

		}

		std::cout << " " << printCard(houseDrawn[counter]);
		Sleep(1000);
		houseScore = calculateValueOfHouseCards(houseDrawn, houseDrawnValue, houseScore);
		std::cout << " Score: " << houseScore << "\n";
		counter++;
	}

	//Then send the total value back for comparison with the players score.
	return houseScore;
}

//This is just for printing the cards with fancy icons. Cards are stored as a 3 digit number, this just turns it into 
//a more user-friendly text.
std::string printCard(int cardInput) {
	std::string output;

	//See populateDeckOfCards for spesifics, but basically, every card has an ID of three digits, for example "203"
	//This means it is a 3 card, of the type '\4'. Therefore, i insert the correct type into the output string, 
	//and then remove the type-digit from the integer. This doesn't change the value of the original card, it's just for displaying.
	//Then I add the number or Icon (K for King, Q for Queen, etc.) and return that as a string.
	if (cardInput < 200 && output.size() == 0) {
		output.push_back('\3');
		cardInput = cardInput - 100;
	}
	else if (cardInput >= 200 && cardInput < 300 && output.size() == 0) {
		output.push_back('\4');
		cardInput = cardInput - 200;
	}
	else if (cardInput >= 300 && cardInput < 400 && output.size() == 0) {
		output.push_back('\5');
		cardInput = cardInput - 300;
	}
	else if (cardInput > 400 && output.size() == 0) {
		output.push_back('\6');
		cardInput = cardInput - 400;
	}
	switch (cardInput)
	{
	case 1:
		output.push_back('A');
		break;
	case 2:
		output.push_back('2');
		break;
	case 3:
		output.push_back('3');
		break;
	case 4:
		output.push_back('4');
		break;
	case 5:
		output.push_back('5');
		break;
	case 6:
		output.push_back('6');
		break;
	case 7:
		output.push_back('7');
		break;
	case 8:
		output.push_back('8');
		break;
	case 9:
		output.push_back('9');
		break;
	case 10:
		output.push_back('1');
		output.push_back('0');
		break;
	case 11:
		output.push_back('J');
		break;
	case 12:
		output.push_back('Q');
		break;
	case 13:
		output.push_back('K');
		break;
	default:
		break;
	}
	return output;
}

//This will get a random number, attempt to take that card from the deck, and if it's taken, it will take another.
//if the player somehow draws 52 cards, it will stop. This is to prevent it from going on an infinite loop if something goes wrong.
void drawCard(std::vector <int>& deck, std::vector <int>& drawn, std::vector <int>& drawnValue) {
	srand(time(NULL));
	bool selectionAccepted = false;
	while (!selectionAccepted && drawn.size() < 52) {
		int selection = rand() % 52;
		if (deck[selection] != 0) {
			drawn.push_back(deck[selection]);
			drawnValue.push_back(0);
			deck[selection] = 0;
			selectionAccepted = true;
		}
	}
}

//This is where the deck gets reset. It will give every card it's unique ID of 3 digits, and put them all in the deck vector. 
//The deck is in the same order as a normal deck, and doesn't get shuffled, however the cards chosen are randomized so i don't
//think that will be an issue. 
void populateDeckOfCards(std::vector <int>& deck, std::vector <int>& drawn, int deckSize) {
	deck.clear();
	drawn.clear();
	for (int i = 1; i <= deckSize; i++) {
		int type = 0;
		if (i > 13) {
			type = 1;
		}
		if (i > 26) {
			type = 2;
		}
		if (i > 39) {
			type = 3;
		}
		deck.push_back(100 * (type + 1) + (i - 13 * type));
	}
	
}

//This will strip away the type-digit from a cards ID, and add it to the total value. If the card is an Ace,
//The player will get the option to either select 1 or 11. It will be stored in drawnValue, so the player doesn't
//have to answer every turn. the same goes for the house.
int calculateValueOfHeldCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore) {
	int cardValue = 0;
	int totalValue = 0;
	if (drawn.size() > 0) {
		for (int i = 0; i < drawn.size(); i++) {
			cardValue = drawn[i];
			int type = 0;

			//remove the type-digit.
			while (cardValue > 100) {
				cardValue -= 100;
				type++;
			}

			//if it's a regular number card, just add it's number to the totalvalue.
			if (cardValue >= 2 && cardValue < 11) {
				totalValue += cardValue;
			}

			//If it's a jack, queen or king, add 10.
			else if (cardValue >= 11) {
				totalValue += 10;
			}

			//if its an Ace, ask the player what they want to do.
			else if (cardValue == 1 && drawnValue[i] == 0) {
				std::cout << "So far you have " << lastScore << ". Would you like ";
				std::cout << printCard(100 * type + cardValue);
				std::cout << " to count as one or ten?\n1. One\n2. Eleven\n";
				bool acceptedInput = false;
				while (!acceptedInput) {
					switch (_getch())
					{
					case '1':
						totalValue += 1;
						drawnValue[i] = 1;
						acceptedInput = true;
						break;
					case '2':
						totalValue += 11;
						drawnValue[i] = 11;
						acceptedInput = true;
						break;
					default:
						std::cout << "Please choose between 1 and 2.\n";
						break;
					}
				}
			}

			//or if the player has already answered for that particular ace, just add whatever they chose to totalvalue.
			else if (cardValue == 1 && drawnValue[i] != 0) {
				totalValue += drawnValue[i];
			}
		}
		return totalValue;
	}
	else {
		return 0;
	}
}

//This pretty much does the same as for the player except it chooses automatically.
int calculateValueOfHouseCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore) {
	int cardValue = 0;
	int totalValue = 0;
	if (drawn.size() > 0) {
		for (int i = 0; i < drawn.size(); i++) {
			cardValue = drawn[i];
			int type = 0;
			while (cardValue > 100) {
				cardValue -= 100;
				type++;
			}
			if (cardValue >= 2 && cardValue < 11) {
				totalValue += cardValue;
			}
			else if (cardValue >= 11) {
				totalValue += 10;
			}
			else if (cardValue == 1 && drawnValue[i] == 0) {

				//if it has 10 or less, it will take 11, but if it has more, it has to take 1.
				if (lastScore <= 10) {
					drawnValue[i] = 11;
					totalValue += drawnValue[i];
					std::cout << " House selected 11.";
				}
				else {
					drawnValue[i] = 1;
					totalValue += drawnValue[i];

					std::cout << " House selected 1.";
				}
			}
			else if (cardValue == 1 && drawnValue[i] != 0) {
				totalValue += drawnValue[i];
			}
		}
		return totalValue;
	}
	else {
		return 0;
	}
}
