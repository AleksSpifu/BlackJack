#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void populateDeckOfCards(std::vector <int>& deck, std::vector <int>& drawn, int deckSize);
void drawCard(std::vector <int>& deck, std::vector <int>& drawn, std::vector <int>& drawnValue);
std::string printCard(int cardInput);
int calculateValueOfHeldCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore);
int housePlays(std::vector <int>& deck, std::vector <int>& houseDrawn, std::vector <int>& houseDrawnValue, int playerScore);
int calculateValueOfHouseCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore);


int main() {
	int playerMoney = 100;
	int houseMoney = 100;
	int deckSize = 52;
	int lastScore = 0;
	std::vector <int> drawnCards;
	std::vector <int> houseDrawnCards;
	std::vector <int> houseDrawnCardsValue;
	std::vector <int> drawnCardsValue;
	std::vector <int> deckOfCards;

	
	bool gameover = false;
	bool playerFinished = false;
	while (playerMoney > 0 && houseMoney > 0) {
		playerFinished = false;
		gameover = false;
		populateDeckOfCards(deckOfCards, drawnCards, deckSize);
		drawnCards.clear();
		houseDrawnCards.clear();
		houseDrawnCardsValue.clear();
		drawnCardsValue.clear();
		lastScore = 0;
		while (!gameover) {
			system("cls");
			std::cout << "Welcome to BlackJack! Press D to draw a new card, S to stop, or Escape to exit.\n";
			std::cout << "You are currently holding ";
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
				lastScore = calculateValueOfHeldCards(drawnCards, drawnCardsValue, lastScore);
				std::cout << "With a combined value of " << lastScore << "\n";
			}
			else {
				std::cout << "no cards.\n";
			}
			if (lastScore >= 21) {
				playerFinished = true;
			}
			if (!playerFinished) {
				switch (tolower(_getch())) {
				case 'd':
					drawCard(deckOfCards, drawnCards, drawnCardsValue);
					break;
				case 's':
					playerFinished = true;
					break;
				case 27:
					gameover = true;
					break;
				default:
					break;
				}
			}
			if (playerFinished) {
				int houseScore = housePlays(deckOfCards, houseDrawnCards, houseDrawnCardsValue, lastScore);
				if (houseScore > 21 && lastScore > 21) {
					std::cout << "Both parties lost.";
				}
				else if (houseScore > 21 && lastScore <= 21) {
					std::cout << "The player wins!";
				}
				else if (houseScore <= 21 && lastScore > 21) {
					std::cout << "The house wins!";
				}
				else {
					if (houseScore == lastScore) {
						std::cout << "It's a draw!";
					}
					else if (houseScore < lastScore) {
						std::cout << "The player wins!";
					}
					else if (houseScore > lastScore) {
						std::cout << "The house wins!";
					}
				}
				gameover = true;
			}

		}
		system("pause");
	}

}

int housePlays(std::vector <int>& deck, std::vector <int>& houseDrawn, std::vector <int>& houseDrawnValue, int playerScore) {
	int counter = 0;
	int houseScore = 0;
	while (houseScore < 18) {
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
	if (houseScore < playerScore && playerScore != 21 && houseScore < 21) {
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
	}
	return houseScore;
}

std::string printCard(int cardInput) {
	std::string output;
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

int calculateValueOfHeldCards(std::vector <int>& drawn, std::vector <int>& drawnValue, int lastScore) {
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
				std::cout << "So far you have " << lastScore << ". Would you like ";
				std::cout << printCard(100 * type + cardValue);
				std::cout << " to count as one or ten?\n1. One\n2. Ten\n";
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
						totalValue += 10;
						drawnValue[i] = 10;
						acceptedInput = true;
						break;
					default:
						std::cout << "Please choose between 1 and 2.\n";
						break;
					}
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
				if (lastScore <= 11) {
					drawnValue[i] = 10;
					totalValue += drawnValue[i];
					std::cout << " House selected 10.";
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