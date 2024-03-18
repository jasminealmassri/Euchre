#include "Header.hpp"



void play_trick(vector<Card> hand1, vector<Card> hand2, vector<Card> hand3, vector<Card> hand4)
{

}



int main()
{
	// Seed random
	srand(static_cast<unsigned int>(time(nullptr)));
	
	vector<Card> deck;

	// Populate deck
	populate_deck(deck);

	make_euchre_deck(deck);

	// print_cards(deck);
	
	//random_shuffle(deck.begin(), deck.end());

	// print_cards(deck);

	// Deal 5 cards
	//vector<Card> hand1 = deal_cards(deck, 5);

	//cout << "\n\nAfter dealing 5 cards:\n";

	//cout << "Hand is:\n";
	// print_cards(hand1);

	//cout << "Deck is:\n";
	// print_cards(deck);

	/*vector<Card> hand2 = deal_cards(deck, 5);
	vector<Card> hand3 = deal_cards(deck, 5);
	vector<Card> hand4 = deal_cards(deck, 5);*/

	//cout << "Hand2 is:\n";
	//print_cards(hand2);
	//cout << "Hand3 is:\n";
	//print_cards(hand3);
	//cout << "Hand4 is:\n";
	//print_cards(hand4);

	// string trump = "Spades";

	//vector<Card> trick;
	// vector<Card> trick(5, Card({"",""}));
	//trick.push_back(computer_move(hand1, trick, trump));

	//cout << "\nTrick is:\n";
	// print_cards(trick);

	//cout << "\nHand1 is: \n";
	// print_cards(hand1);
	/*unsigned starting_player = 2;
	unsigned dealer = 1;

	trick[starting_player] = (computer_move(hand2, trick, trump));*/
	//cout << "\nTrick is:\n";
	// print_cards(trick);

	//cout << "\nHand1 is: \n";
	// print_cards(hand1);

	//trick.push_back(computer_move(hand3, trick, trump));
	//cout << "\nTrick is:\n";
	// print_cards(trick);

	//cout << "\nHand1 is: \n";
	// print_cards(hand1);


	//trick.push_back(computer_move(hand4, trick, trump));
	//cout << "\nTrick is:\n";
	// print_cards(trick);

	//cout << "\nHand1 is: \n";
	// print_cards(hand1);

	

	//draw_v2(trick, 2, trump, 5, 5, 1, 2);
	//cout << "The player that won this trick is " << determine_who_won(trick, trump, trick[starting_player].suit) << "\n";
	//

	////draw_hand(hand1);
	//trick[1] = user_move(hand1, trick);
	//cout << "user chose: " << trick[1].face_value << " of " << trick[1].suit << endl;
	//
	//draw_v2(trick, 1, trump, 5, 5, 1, 2);
	//cout << "The player that won this trick is " << determine_who_won(trick, trump, trick[starting_player].suit) << "\n";

	unsigned team1_score = 0;
	unsigned team2_score = 0;
	unsigned tricks_won = 0;
	unsigned tricks_lost = 0;
	unsigned dealer = 4;

	vector<vector<Card>> placeholder( 5, vector<Card>{{"",""}} );

	// step 1 shuffle deck
	shuffle_deck(deck);

	// step 2 deal hands
	vector<vector<Card>> hands = deal_hands(deck);

	// first pass decision
	pair<string, unsigned> decision = first_decision_round(deck, hands, dealer, team1_score, team2_score, tricks_won, tricks_lost);

	if (decision.first == "all_passed")
	{
		decision = second_decision_round(deck, hands, dealer, team1_score, team2_score, tricks_won, tricks_lost);
		// TO DO
		// second_decision_round(deck, hands, dealer, team1_score, team2_score, tricks_won, tricks_lost);
	}
	if (decision.first == "all_passed")
	{
		cout << "Everyone passed, play again" << endl;
		// Just gonna make it exit for now
		return EXIT_SUCCESS;
		// second_decision_round(deck, hands, dealer, team1_score, team2_score, tricks_won, tricks_lost);
	}

	string trump = decision.first;

	// gotta put this in a loop where it keeps playing until the end of the game
	play_round(dealer, trump, deck, hands, team1_score, team2_score, tricks_won, tricks_lost);



}