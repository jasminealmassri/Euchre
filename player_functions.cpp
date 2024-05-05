#include "Header.hpp"



bool player_prompt_pick_it_up(vector<Card> hand, unsigned dealer)
{
	char decision;
	bool pick_it_up;
	if (dealer == 1)
	{
		cout << "Want to pick it up? (y/n): ";
	}
	else if (dealer == 3)
	{
		cout << "Want your partner to pick it up (you play alone)? (y/n): ";
	}
	else
	{
		cout << "Want dealer to pick it up? (y/n): ";
	}
	cin >> decision;
	decision = (char)tolower(decision);
	while (decision != 'y' && decision != 'n')
	{
		cout << "Invalid entry, please enter y or n: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> decision;
		decision = (char)tolower(decision);

	}
	// flush anything remaining
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	pick_it_up = decision ==  'y' ? true : false;

	
	return pick_it_up;
	
}

Card player_dealer_pick_up(vector<Card> hand, Card flipped_card)
{
	unsigned discard_choice;
	// Takes card new card
	cout << "Choose a card to discard (1-5): ";
	cin >> discard_choice;
	while (discard_choice < 1 || discard_choice > 5)
	{
		cout << "Invalid card choice, please enter a number from 1 to 5: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> discard_choice;
	}

	// Make discard_choice correspond to zero based hand index
	discard_choice -= 1;


	// Erases card from hand and adds new card to hand
	Card discard_card;
	discard_card = hand[discard_choice];

	// DEBUG
	cout << "You chose " << hand[discard_choice].face_value << " of " << hand[discard_choice].suit << " to discard\n";
	

	hand.erase(hand.begin() + discard_choice);
	hand.push_back(flipped_card);

	// DEBUG
	draw_hand(hand);
	cout << "The card discarded is the " << discard_card.face_value << " of " << discard_card.suit << endl;
	

	// Returns discarded card
	return discard_card;
}

bool player_prompt_make_it_trump(vector<Card> hand)
{
	char choice;
	cout << "Do you want to choose trump? Y/N" << endl;
	cin >> choice;
	choice = toupper(choice);
	while (choice != 'Y' && choice != 'N')
	{
		cout << "Invalid choice, please enter 'Y' to choose trump, or 'N' to pass: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
	}
	// if they entered anything extra in the strem
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	bool decision = choice == 'Y' ? true : false;
	return decision;

}

pair<string, unsigned> player_chooses_trump(vector<Card> const& hand)
{
	unordered_map<string, unsigned> eligible_suits;
	unsigned choice_counter{1};
	for (Card const& c : hand)
	{
		auto insert_took_place = eligible_suits.insert({ c.suit, choice_counter });
		if (insert_took_place.second)
			choice_counter++;
	}
	cout << "Please choose a suit to make it: " << endl;
	
	for (pair<string,unsigned> const& p : eligible_suits)
	{
		cout << p.second << ": " << p.first << endl;
	}
	
	int choice;
	cin >> choice;
	while (!cin || choice < 1 || choice >= eligible_suits.size())
	{
		cout << "Invalid choice. Please choose a number between 1 and " << eligible_suits.size() << ": ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
	}
	for (pair<string, unsigned> p : eligible_suits)
	{
		if (p.second == choice)
		{
			//debug
			cout << "You chose " << p.first << endl;
			return { p.first, 1 };

		}
			
	}

	// Debug
	//set<string>::iterator it = eligible_suits.begin();
	//advance(it, choice - 1);
	//return {*it, 1};
	

}

Card user_move(vector<Card>& hand, vector<Card> trick)
{
	unsigned choice{};
	draw_hand(hand);
	cout << "CHOOSE A CARD: ";
	cin >> choice;
	while ((!cin) || choice < 1 || choice > hand.size())
	{
		cout << "Invalid input. please enter a number between 1 and " << hand.size() << ": ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
	}

	Card chosen_card = hand[choice - 1];
	hand.erase(hand.begin() + choice - 1);
	//trick.push_back(chosen_card);
	return chosen_card;
}

