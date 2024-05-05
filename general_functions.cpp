#include "Header.hpp"

void populate_deck(vector<Card>& deck)
{
	vector<string> face_values = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	vector<string> suits = { "Spades", "Clubs" , "Hearts", "Diamonds" };

	for (int i = 0; i < suits.size(); i++)
	{
		for (int j = 0; j < face_values.size(); j++)
		{
			deck.push_back({ face_values[j], suits[i] });
		}
	}
}

void shuffle_deck(vector<Card>& deck)
{
	random_shuffle(deck.begin(), deck.end());
}

void make_euchre_deck(vector<Card>& deck)
{
	for (vector<Card>::iterator it = deck.begin(); it != deck.end(); it++)
	{
		if (it->face_value == "2" ||
			it->face_value == "3" ||
			it->face_value == "4" ||
			it->face_value == "5" ||
			it->face_value == "6" ||
			it->face_value == "7" ||
			it->face_value == "8")
		{
			it = deck.erase(it);
			it--;
		}

	}
}

// deals 6 hands from deck and gives back the hands vector
vector<vector<Card>> deal_hands(vector<Card>& deck)
{

	// step 2 deal cards
	vector<vector<Card>> hands;

	// placeholder
	hands.push_back(vector<Card>{ {"", ""} });

	// deal 4 hands with the indices matching the players e.g. 1 to 4
	for (unsigned i = 0; i < 4; i++)
	{
		hands.push_back(deal_cards(deck, 5));
	}
	return hands;
}

vector<Card> deal_cards(vector<Card>& deck, unsigned num_cards)
{
	vector<Card> hand;

	for (unsigned i = 0; i < num_cards; i++)
	{
		hand.push_back(deck[i]);
	}
	deck.erase(deck.begin(), deck.begin() + num_cards);

	return hand;

}

string make_centered_text(string s, unsigned column_width)
{
	string centered_text;

	if (s.size() > column_width)
	{
		return "COLUMN TOO SMALL. MAKE COLUMN BIGGER";
	}

	unsigned num_spaces = column_width - s.size();


	for (unsigned i = 0; i < (num_spaces / 2); i++)
	{
		centered_text.push_back(' ');
	}
	centered_text.append(s);
	for (unsigned i = 0; i < (num_spaces / 2); i++)
	{
		centered_text.push_back(' ');
	}
	if (num_spaces % 2 == 1)
	{
		centered_text.push_back(' ');
	}

	return centered_text;

}

vector<string> get_card_drawing(Card card)
{
	constexpr unsigned CARD_WIDTH{ 12 };
	vector<string> card_drawing{};

	string straight_line{};
	for (int i = 0; i < CARD_WIDTH; i++)
		straight_line += "-";

	card_drawing.push_back(straight_line);
	card_drawing.push_back("|" + make_centered_text(card.face_value, CARD_WIDTH - 2) + "|");
	card_drawing.push_back("|" + make_centered_text("of", CARD_WIDTH - 2) + "|");
	card_drawing.push_back("|" + make_centered_text(card.suit, CARD_WIDTH - 2) + "|");
	card_drawing.push_back(straight_line);

	return card_drawing;
}

void draw_hand(vector<Card> hand)
{
	const string SPACE_BETWEEN{ "    " };
	const unsigned CARD_WIDTH{ 12 };

	// get all the card drawings
	vector<vector<string>> card_drawings;
	for (size_t i = 0; i < hand.size(); i++)
	{
		card_drawings.push_back(get_card_drawing(hand[i]));
	}

	//print the hand
	cout << "YOUR HAND: " << endl;
	for (size_t i = 0; i < card_drawings.size(); i++)
	{
		cout << "   Card " << i + 1 << "   " << SPACE_BETWEEN;
	}
	cout << "\n";

	for (size_t i = 0; i < card_drawings[0].size(); i++)
	{
		for (size_t j = 0; j < card_drawings.size(); j++)
		{
			cout << card_drawings[j][i] << SPACE_BETWEEN;
		}
		cout << "\n";
	}
}

void draw(vector<Card> trick, unsigned starting_player, string trump, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost)
{
	// Organize the trick here so it knows which one to print
	vector<Card> organized_trick1;
	vector<Card> organized_trick2;

	// Push placeholder for 0 so that all the indices match the players 
	organized_trick1.push_back({ "", "" });

	// Add empty strings where there is missing cards in the trick
	for (size_t i = 0; i < trick.size(); i++)
	{
		organized_trick1.push_back(trick[i]);
	}
	for (size_t i = 0; i <= (4 - trick.size()); i++)
	{
		organized_trick1.push_back({ "","" });
	}

	organized_trick2.push_back(organized_trick1[0]);
	// Order so that 0 is just empty, 1 is in front of player 1, 2 is 2, 3 is 3, etc.
	for (unsigned i = starting_player; i < organized_trick1.size(); i++)
	{
		organized_trick2.push_back(organized_trick1[i]);
	}
	for (unsigned i = 1; i < starting_player; i++)
	{
		organized_trick2.push_back(organized_trick1[i]);
	}

	// first column is 11 spaces, second is 13, second is 13, second is 13, 4th is 11
	unsigned column_1 = 14, column_2 = 13, column_3 = 13, column_4 = 13, column_5 = 14;
	unsigned total_canvas_size = column_1 + column_2 + column_3 + column_4 + column_5;

	// All hyphens
	string filled((total_canvas_size), '-');

	// two pipes and nothing between
	string empty_whole_line{};
	empty_whole_line.push_back('|');
	for (size_t i = 0; i < total_canvas_size - 2; i++)
	{
		empty_whole_line.push_back(' ');
	}
	empty_whole_line.push_back('|');


	// empty columns
	string empty_1(column_1 - 1, ' ');
	string empty_2(column_2, ' ');
	string empty_3(column_3, ' ');
	string empty_4(column_4, ' ');
	string empty_5(column_5 - 1, ' ');

	// filled columns
	string filled_1(column_1 - 1, '-');
	string filled_2(column_2, '-');
	string filled_3(column_3, '-');
	string filled_4(column_4, '-');
	string filled_5(column_5 - 1, '-');



	// Draw
	// Header
	cout << "    ----------------------------------------------------------\n";
	cout << "    |    Your Team:   " << your_team_score << "       |       Enemy Team: " << enemy_team_score << "          | \n";
	cout << "    ----------------------------------------------------------\n";
	cout << "                                                              \n";
	cout << "                 ---------------------------                  \n";
	cout << "                 |   " << make_centered_text("Trump is: " + trump, 21) << " | \n";
	cout << "                 ---------------------------                  \n";
	cout << "                                                              \n";

	cout << "\n     Tricks won: " << tricks_won << "                            " << "Tricks lost: " << tricks_lost << "        \n\n";

	// For debug purposes
	// Empty 1st card
	// organized_trick2[1] = { "","" };
	// Empty 2nd card
	// organized_trick2[2] = { "","" };
	// Empty 3rd card
	// organized_trick2[3] = { "","" };
	// Empty 4th card
	//organized_trick2[4] = { "","" };


	cout << filled << endl;
	cout << empty_whole_line << endl;
	cout << '|' << empty_1 << empty_2 << make_centered_text("Player 3", column_3) << empty_4 << empty_5 << "|\n";
	cout << empty_whole_line << endl;
	// If player 3 has played a card
	if (organized_trick2[3].face_value != "")
	{
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(organized_trick2[3].face_value, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text("of", column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(organized_trick2[3].suit, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
	}
	else
	{
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
	}
	cout << empty_whole_line << endl;

	// If player 2 and player 4 have a card
	if (organized_trick2[2].face_value != "" && organized_trick2[4].face_value != "")
	{
		cout << '|' << empty_1 << filled_2 << empty_3 << filled_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(organized_trick2[2].face_value, column_2 - 2) + '|' << empty_3 << '|' + make_centered_text(organized_trick2[4].face_value, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << '|' + make_centered_text("of", column_2 - 2) + '|' << empty_3 << '|' + make_centered_text("of", column_4 - 2) + '|' << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(organized_trick2[2].suit, column_2 - 2) + '|' << empty_3 << '|' + make_centered_text(organized_trick2[4].suit, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << empty_1 << filled_2 << empty_3 << filled_4 << empty_5 << "|\n";
	}
	// If player 2 has a card but not player 4
	else if (organized_trick2[2].face_value != "" && organized_trick2[4].face_value == "")
	{
		cout << '|' << empty_1 << filled_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(organized_trick2[2].face_value, column_2 - 2) + '|' << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << '|' + make_centered_text("of", column_2 - 2) + '|' << empty_3 << empty_4 << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(organized_trick2[2].suit, column_2 - 2) + '|' << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << filled_2 << empty_3 << empty_4 << empty_5 << "|\n";
	}
	// If player 2 has no card and player 4 has a card
	else if (organized_trick2[2].face_value == "" && organized_trick2[4].face_value != "")
	{
		cout << '|' << empty_1 << empty_2 << empty_3 << filled_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << '|' + make_centered_text(organized_trick2[4].face_value, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << empty_2 << empty_3 << '|' + make_centered_text("of", column_4 - 2) + '|' << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << '|' + make_centered_text(organized_trick2[4].suit, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << filled_4 << empty_5 << "|\n";
	}
	// If both players don't have cards
	else
	{
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << empty_2 << empty_3 << empty_4 << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
	}
	cout << empty_whole_line << endl;
	// If player 1 has played a card
	if (organized_trick2[1].face_value != "")
	{
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(organized_trick2[1].face_value, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text("of", column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(organized_trick2[1].suit, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
	}
	else
	{
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
	}
	cout << empty_whole_line << endl;
	cout << '|' << empty_1 << empty_2 << make_centered_text("You", column_3) << empty_4 << empty_5 << "|\n";
	cout << empty_whole_line << endl;
	cout << filled << endl;

}

// I made this one because I dont want it to reshuffle, I want it to just print each position
void draw_v2(vector<Card> trick, unsigned starting_player, string trump, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost)
{

	// first column is 11 spaces, second is 13, second is 13, second is 13, 4th is 11
	unsigned column_1 = 14, column_2 = 13, column_3 = 13, column_4 = 13, column_5 = 14;
	unsigned total_canvas_size = column_1 + column_2 + column_3 + column_4 + column_5;

	// All hyphens
	string filled((total_canvas_size), '-');

	// two pipes and nothing between
	string empty_whole_line{};
	empty_whole_line.push_back('|');
	for (size_t i = 0; i < total_canvas_size - 2; i++)
	{
		empty_whole_line.push_back(' ');
	}
	empty_whole_line.push_back('|');


	// empty columns
	string empty_1(column_1 - 1, ' ');
	string empty_2(column_2, ' ');
	string empty_3(column_3, ' ');
	string empty_4(column_4, ' ');
	string empty_5(column_5 - 1, ' ');

	// filled columns
	string filled_1(column_1 - 1, '-');
	string filled_2(column_2, '-');
	string filled_3(column_3, '-');
	string filled_4(column_4, '-');
	string filled_5(column_5 - 1, '-');



	// Draw
	// Header
	cout << "    ----------------------------------------------------------\n";
	cout << "    |    Your Team:   " << your_team_score << "       |       Enemy Team: " << enemy_team_score << "          | \n";
	cout << "    ----------------------------------------------------------\n";
	cout << "                                                              \n";
	cout << "                 ---------------------------                  \n";
	cout << "                 |   " << make_centered_text("Trump is: " + trump, 21) << " | \n";
	cout << "                 ---------------------------                  \n";
	cout << "                                                              \n";

	cout << "\n     Tricks won: " << tricks_won << "                            " << "Tricks lost: " << tricks_lost << "        \n\n";

	cout << filled << endl;
	cout << empty_whole_line << endl;
	cout << '|' << empty_1 << empty_2 << make_centered_text("Player 3", column_3) << empty_4 << empty_5 << "|\n";
	cout << empty_whole_line << endl;
	// If player 3 has played a card
	if (trick[3].face_value != "")
	{
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(trick[3].face_value, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text("of", column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(trick[3].suit, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
	}
	else
	{
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
	}
	cout << empty_whole_line << endl;

	// If player 2 and player 4 have a card
	if (trick[2].face_value != "" && trick[4].face_value != "")
	{
		cout << '|' << empty_1 << filled_2 << empty_3 << filled_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(trick[2].face_value, column_2 - 2) + '|' << empty_3 << '|' + make_centered_text(trick[4].face_value, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << '|' + make_centered_text("of", column_2 - 2) + '|' << empty_3 << '|' + make_centered_text("of", column_4 - 2) + '|' << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(trick[2].suit, column_2 - 2) + '|' << empty_3 << '|' + make_centered_text(trick[4].suit, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << empty_1 << filled_2 << empty_3 << filled_4 << empty_5 << "|\n";
	}
	// If player 2 has a card but not player 4
	else if (trick[2].face_value != "" && trick[4].face_value == "")
	{
		cout << '|' << empty_1 << filled_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(trick[2].face_value, column_2 - 2) + '|' << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << '|' + make_centered_text("of", column_2 - 2) + '|' << empty_3 << empty_4 << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << '|' + make_centered_text(trick[2].suit, column_2 - 2) + '|' << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << filled_2 << empty_3 << empty_4 << empty_5 << "|\n";
	}
	// If player 2 has no card and player 4 has a card
	else if (trick[2].face_value == "" && trick[4].face_value != "")
	{
		cout << '|' << empty_1 << empty_2 << empty_3 << filled_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << '|' + make_centered_text(trick[4].face_value, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << empty_2 << empty_3 << '|' + make_centered_text("of", column_4 - 2) + '|' << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << '|' + make_centered_text(trick[4].suit, column_4 - 2) + '|' << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << filled_4 << empty_5 << "|\n";
	}
	// If both players don't have cards
	else
	{
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << make_centered_text("Player 2", column_1 - 1) << empty_2 << empty_3 << empty_4 << make_centered_text("Player 4", column_5 - 1) << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << empty_3 << empty_4 << empty_5 << "|\n";
	}
	cout << empty_whole_line << endl;
	// If player 1 has played a card
	if (trick[1].face_value != "")
	{
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(trick[1].face_value, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text("of", column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << '|' + make_centered_text(trick[1].suit, column_3 - 2) + '|' << empty_4 << empty_5 << "|\n";
		cout << '|' << empty_1 << empty_2 << filled_3 << empty_4 << empty_5 << "|\n";
	}
	else
	{
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
		cout << empty_whole_line << endl;
	}
	cout << empty_whole_line << endl;
	cout << '|' << empty_1 << empty_2 << make_centered_text("You", column_3) << empty_4 << empty_5 << "|\n";
	cout << empty_whole_line << endl;
	cout << filled << endl;

}

unsigned determine_who_won(vector<Card> trick, string trump, string leading_suit)
{
	// holds the rank, the lower the index the higher the winning power of the card
	vector<Card> card_ranks{};

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

	// Add trump card in order of winning rank
	card_ranks.push_back({ "Jack", trump });
	card_ranks.push_back({ "Jack", offsuit });
	card_ranks.push_back({ "Ace", trump });
	card_ranks.push_back({ "King", trump });
	card_ranks.push_back({ "Queen", trump });
	card_ranks.push_back({ "10", trump });
	card_ranks.push_back({ "9", trump });
	// Add leading suit cards in order of winning rank
	card_ranks.push_back({ "Ace", leading_suit });
	card_ranks.push_back({ "King", leading_suit });
	card_ranks.push_back({ "Queen", leading_suit });
	card_ranks.push_back({ "Jack", leading_suit });
	card_ranks.push_back({ "10", leading_suit });
	card_ranks.push_back({ "9", leading_suit });

	// highest card index means the player that is winning so far
	unsigned highest_card_index{ 14 };
	// highest rank card means the highest card so far
	unsigned highest_rank_card{ 14 };

	// loop over every card in the trick
	for (unsigned i = 0; i < trick.size(); i++)
	{
		// loop over the card ranks
		for (unsigned j = 0; j < card_ranks.size(); j++)
		{
			// if you find a match in the winning ranks
			if ((trick[i].suit == card_ranks[j].suit) && (trick[i].face_value == card_ranks[j].face_value))
			{
				// if the current matching card is a higher rank card
				// than the highest seen so far
				if (j < highest_rank_card)
				{
					// update winning player's index to this one
					highest_card_index = i;
					// update highest rank card seen so far
					highest_rank_card = j;
				}
			}
		}
	}
	return highest_card_index;

}

void print_cards(vector<Card>& deck)
{
	for (int i = 0; i < deck.size(); i++)
	{
		//cout <<  i + 1  "."s) << setw(10) << v[i].face_value + " of " + v[i].suit << endl;
		printf("%-7d %-20s\n", i + 1, (deck[i].face_value + " of " + deck[i].suit).c_str());
	}
	cout << endl;
}

void play_trick(unsigned starting_player, string trump, vector<vector<Card>>& hands, unsigned& tricks_won, unsigned& tricks_lost, unsigned team1_score, unsigned team2_score, vector<Card>& discard_deck)
{
	vector<Card> trick(5, Card({ "","" }));
	unsigned current_player = starting_player;
	for (unsigned i = 0; i < 4; i++)
	{
		if (current_player == 1)
		{
			draw_v2(trick, starting_player, trump, team1_score, team2_score, tricks_won, tricks_lost);
			trick[current_player] = user_move(hands[1], trick);
		}
		else
		{
			trick[current_player] = computer_move(hands[current_player], trick, trump);
		}
		current_player++;
		if (current_player == 5)
		{
			current_player = 1;

		}
	}

	unsigned winning_player = determine_who_won(trick, trump, trick[starting_player].suit);

	if (winning_player == 1 || winning_player == 3)
	{
		tricks_won++;
	}
	else if (winning_player == 2 || winning_player == 4)
	{
		tricks_lost++;
	}

	for (int i = 0; i < trick.size(); i++)
	{
		discard_deck.push_back(trick[i]);
	}
	draw_v2(trick, starting_player, trump, team1_score, team2_score, tricks_won, tricks_lost);
}

void play_round(unsigned dealer, string trump, vector<Card>& deck, vector<vector<Card>>& hands, unsigned& team1_score, unsigned& team2_score, unsigned& tricks_won, unsigned& tricks_lost)
{


	vector<Card> discard_deck;



	unsigned starting_player = dealer == 4 ? 1 : dealer + 1;

	// step 3 play 5 tricks
	for (unsigned i = 0; i < 5; i++)
	{
		play_trick(starting_player, trump, hands, tricks_won, tricks_lost, team1_score, team2_score, discard_deck);
		if (i < 3)
		{
			cout << "enter any key to play next trick: ";
			string s;
			cin >> s;
		}
	}
	// Ill have to cover going alone as well when I add that to the game
	if (tricks_won == 5)
	{
		team1_score += 2;
	}
	else if (tricks_won >= 3)
	{
		// euchred
		if (starting_player == 2 || starting_player == 4)
		{
			team1_score += 2;
		}
		else
		{
			team1_score++;
		}
	}
	else if (tricks_lost == 5)
	{
		team2_score += 2;
	}
	else if (tricks_lost >= 3)
	{
		// euchred
		if (starting_player == 1 || starting_player == 3)
		{
			team2_score += 2;
		}
		else
		{
			team2_score++;
		}
	}

	// give back the cards
	for (int i = 0; i < discard_deck.size(); i++)
	{
		deck.push_back(discard_deck[i]);
	}
	tricks_won = 0;
	tricks_lost = 0;

	// I have to put the cards back at the end

}

pair<string, unsigned> first_decision_round(vector<Card>& deck, vector<vector<Card>>& hands, unsigned dealer, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost)
{

	// does shuffling need to happen here? 
	// Makes a vector for the purpose of using draw, it contains only one card but puts it in front of dealer
	vector<Card> decision_table(5, Card({ "","" }));

	// flip top card
	Card flipped_card = deck[0];
	decision_table[dealer] = flipped_card;
	draw_v2(decision_table, dealer, "", your_team_score, enemy_team_score, tricks_won, tricks_lost);

	// Ask each player if they want dealer to pick it up
	unsigned starting_player = dealer == 4 ? 1 : dealer + 1;
	unsigned current_player = starting_player;

	bool pick_it_up = false;
	// unsigned player_who_decided_trump = 0;

	Card discarded_card;

	for (int i = 0; i < 4; i++)
	{
		if (current_player == 1)
		{
			draw_hand(hands[1]);
			pick_it_up = player_prompt_pick_it_up(hands[1], dealer);

			if (pick_it_up)
			{
				if (dealer == 1)
				{
					discarded_card = player_dealer_pick_up(hands[1], flipped_card);
				}
				else
				{
					discarded_card = computer_dealer_pick_up(hands[dealer], flipped_card);
				}


				// I have to return the card here before I move on
				deck.erase(deck.begin());
				deck.push_back(discarded_card);

				// return trump
				return { flipped_card.suit, 1 };
			}
		}
		else
		{
			pick_it_up = computer_decision_pick_it_up(hands[current_player], dealer, flipped_card);

			if (pick_it_up)
			{
				if (dealer == 1)
				{
					discarded_card = player_dealer_pick_up(hands[1], flipped_card);
				}
				else
				{
					discarded_card = computer_dealer_pick_up(hands[dealer], flipped_card);
				}

				// I have to return the card here before I move on
				deck.erase(deck.begin());
				deck.push_back(discarded_card);

				return { flipped_card.suit, current_player };
			}
		}

		// advance player cursor
		current_player = current_player == 4 ? 1 : current_player + 1;
	}
	// If this makes it through all the players and no one picked up
	return { "all_passed" , 0 };

	// REMOVE ONCE FINISHED
	// return { "", 0 };
}

pair<string, unsigned> second_decision_round(vector<Card>& deck, vector<vector<Card>>& hands, unsigned dealer, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost)
{
	vector<Card> decision_table(5, Card({ "","" }));

	// flip top card
	//Card flipped_card = deck[0];
	// decision_table[dealer] = flipped_card;
	draw_v2(decision_table, dealer, "", your_team_score, enemy_team_score, tricks_won, tricks_lost);

	// Ask each player if they want dealer to pick it up
	unsigned starting_player = dealer == 4 ? 1 : dealer + 1;
	unsigned current_player = starting_player;
	bool picked_trump = false;
	pair<string, unsigned> trump_and_chooser;
	// unsigned player_who_decided_trump = 0;

	//Card discarded_card;

	for (int i = 0; i < 4; i++)
	{
		if (current_player == 1)
		{
			draw_hand(hands[1]);

			picked_trump = player_prompt_make_it_trump(hands[1]);

			if (picked_trump)
			{
				return player_chooses_trump(hands[1]);
			}
		}
		else
		{
			picked_trump = computer_decision_make_it_trump(hands[current_player]);

			if (picked_trump)
			{
				pair<string, unsigned> trump_and_player = computer_chooses_trump(hands[current_player]);

				cout << "Player #" << current_player << " chose " << trump_and_player.first << " as trump" << endl;
				return { trump_and_player };
			}
		}

		// advance player cursor
		current_player = current_player == 4 ? 1 : current_player + 1;
	}
	// If this makes it through all the players and no one picked up
	return { "all_passed" , 0 };
}
