#pragma once
#include <iostream>
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

struct Card {
	string face_value;
	string suit;
};

constexpr int DECK_SIZE = 52;

// GENERAL NOTES FOR THE PROGRAM
// THe hand's index is zero-based
// The player's index is one-based


// function headers
void populate_deck(vector<Card>& deck);

void shuffle_deck(vector<Card>& deck);

void make_euchre_deck(vector<Card>& deck);
string make_centered_text(string s, unsigned column_width);
vector<string> get_card_drawing(Card card);
void draw_hand(vector<Card> hand);
Card user_move(vector<Card>& hand, vector<Card> trick);
void draw(vector<Card> trick, unsigned starting_player, string trump, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost);
void draw_v2(vector<Card> trick, unsigned starting_player, string trump, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost);
unsigned determine_who_won(vector<Card> trick, string trump, string leading_suit);

void print_cards(vector<Card>& deck);

vector<Card> deal_cards(vector<Card>& deck, unsigned num_cards);

Card computer_move(vector<Card>& hand, vector<Card>& trick, string trump);

void play_trick(unsigned starting_player, string trump, vector<vector<Card>>& hands, unsigned& tricks_won, unsigned& tricks_lost, unsigned team1_score, unsigned team2_score, vector<Card>& discard_deck);

void play_round(unsigned dealer, string trump, vector<Card>& deck, vector<vector<Card>>& hands, unsigned& team1_score, unsigned& team2_score, unsigned& tricks_won, unsigned& tricks_lost);

vector<vector<Card>> deal_hands(vector<Card>& deck);

pair<string, unsigned> first_decision_round(vector<Card>& deck, vector<vector<Card>>& hands, unsigned dealer, unsigned your_team_score, unsigned enemy_team_score, unsigned tricks_won, unsigned tricks_lost);


