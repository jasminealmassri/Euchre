#include "Header.hpp"


// This function is contextual to the rest of the hand
// The index is the index of the card that is currently being looked at
double get_card_probability_win_based_on_hand(vector<Card> hand, int index, string trump)
{
	// holds the rank, the lower the index the higher the winning power of the card
	vector<Card> card_ranks{};

	const int TOTAL_NUM_CARDS = 24;

	// figure out which suit is offsuit based ont trump
	string offsuit{};
	if (trump == "Spades")
		offsuit = "Clubs";
	else if (trump == "Clubs")
		offsuit = "Spades";
	else if (trump == "Hearts")
		offsuit = "Diamonds";
	else if (trump == "Diamonds")
		offsuit = "Hearts";

	int num_cards_that_can_beat_this_card = 0;

	// Add trump card in order of winning rank
	card_ranks.push_back({ "Jack", trump });
	card_ranks.push_back({ "Jack", offsuit });
	card_ranks.push_back({ "Ace", trump });
	card_ranks.push_back({ "King", trump });
	card_ranks.push_back({ "Queen", trump });
	card_ranks.push_back({ "10", trump });
	card_ranks.push_back({ "9", trump });
	// Add leading suit cards in order of winning rank
	card_ranks.push_back({ "Ace", hand[index].suit });
	card_ranks.push_back({ "King", hand[index].suit });
	card_ranks.push_back({ "Queen", hand[index].suit });
	card_ranks.push_back({ "Jack", hand[index].suit });
	card_ranks.push_back({ "10", hand[index].suit });
	card_ranks.push_back({ "9", hand[index].suit });



	for (int i = 0; i < card_ranks.size(); i++)
	{
		if (card_ranks[i] == hand[index])
		{
			num_cards_that_can_beat_this_card += i;

			break;
		}
	}

	int ceiling = num_cards_that_can_beat_this_card;
	// Subtract HIGHER RANK cards that are already in your hand
	for (int i = 0; i < hand.size(); i++)
	{
		for (int j = 0; j < ceiling; j++)
		{
			if (hand[i] == card_ranks[j])
			{
				num_cards_that_can_beat_this_card--;
			}
		}
	}

	// If the card isnt trump it should only be considered against its own suit
	// e.g. the 9 of spades can't win anything if spades not trump
	// theres better ways to do this but this will work for now
	Card left_bower = { "Jack", offsuit };
	if (hand[index].suit != trump && hand[index] != left_bower)
	{
		num_cards_that_can_beat_this_card += 14;
	}

	return ((double)TOTAL_NUM_CARDS - num_cards_that_can_beat_this_card) / TOTAL_NUM_CARDS;

}

bool computer_decision_pick_it_up(vector<Card> hand, unsigned dealer, Card flipped_card)
{
	// for now lets just have to be random
	//unsigned random_selection = rand() % 2;

	//return random_selection == '1' ? true : false;
	// for now I will just make them not decide

	// If at least 3 cards have a 60% chance or over of winning, pick it up
	int num_tricks_projected_win = 0;

	for (int i = 0; i < hand.size(); i++)
	{
		if (get_card_probability_win_based_on_hand(hand, i, flipped_card.suit) > 0.6)
		{
			num_tricks_projected_win++;
		}
	}
	return num_tricks_projected_win >= 3;
}


bool computer_decision_make_it_trump(vector<Card> hand)
{
	int random_choice = rand() % 2;
	return random_choice == 1 ? true : false;
}

Card computer_dealer_pick_up(vector<Card> hand, Card flipped_card)
{
	// Random for now
	unsigned discard_choice = (rand() % 5) + 1;

	// Erases card from hand
	Card discard_card;
	discard_card = hand[discard_choice];
	hand.erase(hand.begin() + discard_choice);

	// Returns discarded card
	return discard_card;

}

pair<string, unsigned> computer_chooses_trump(vector<Card> hand)
{
	unordered_map<string, unsigned> eligible_suits;
	unsigned choice_counter{ 1 };
	for (Card const& c : hand)
	{
		auto insert_took_place = eligible_suits.insert({ c.suit, choice_counter });
		if (insert_took_place.second)
			choice_counter++;
	}


	int choice;
	// just random for now
	choice = rand() % choice_counter + 1;

	for (pair<string, unsigned> p : eligible_suits)
	{
		if (p.second == choice)
		{
			//debug
			cout << "Computer chose " << p.first << endl;
			return { p.first, 1 };

		}
	}
}

Card computer_move(vector<Card>& hand, vector<Card>& trick, string trump)
{
	if (hand.size() == 0)
	{
		return { "ERROR", "ERROR" };
	}
	// these tuples hold the suit as a string, number of cards, and whether or not it is trump
	tuple<string, unsigned, bool> spades{ "Spades", 0, false };
	tuple<string, unsigned, bool> hearts{ "Hearts", 0, false };
	tuple<string, unsigned, bool> diamonds{ "Diamonds", 0, false };
	tuple<string, unsigned, bool> clubs{ "Clubs", 0, false };

	// Assign trump
	if (trump == get<0>(spades))
		get<2>(spades) = true;
	else if (trump == get<0>(hearts))
		get<2>(hearts) = true;
	else if (trump == get<0>(diamonds))
		get<2>(diamonds) = true;
	else if (trump == get<0>(clubs))
		get<2>(clubs) = true;

	// unsigned num_trump_cards{};

	// count the cards in each suit
	for (vector<Card>::iterator it = hand.begin(); it != hand.end(); it++)
	{
		if (it->suit == get<0>(spades))
			get<1>(spades)++;
		else if (it->suit == get<0>(hearts))
			get<1>(hearts)++;
		else if (it->suit == get<0>(diamonds))
			get<1>(diamonds)++;
		else if (it->suit == get<0>(clubs))
			get<1>(clubs)++;
	}

	// Put em in a vector I can loop over
	vector<tuple<string, unsigned, bool>> suits{ spades,hearts,diamonds,clubs };


	// ok for now let's just play a random card, i'll write my logic for playing cards after
	unsigned random_selection = rand() % hand.size();

	// play a card
	Card random_card = hand[random_selection];
	hand.erase(hand.begin() + random_selection);
	return random_card;

	// First play
	/*if (trick.size() < 1)
	{
		for (unsigned i = 0; i < suits.size(); i++)
		{
			if (get<0>(suits[i]) == trump)
			{

			}
		}
	}
	else
	{

	}*/
	// It should play a card

	// The card should be returned, being added to the flop and subtracted from the hand
}
