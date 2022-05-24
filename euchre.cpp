// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Card.h"
#include "Pack.h"
#include "Player.h"
using namespace std;

class Game {
private:
    int t1score;
    int t2score;
    int dealerCount;
    int turnCount;
    string trump;
    Card upcard;
    bool wantShuffle;
    Pack pack;
    vector<Player*> players;
public:
    Game() {
        turnCount = 0;
        dealerCount = 0;
        t1score = 0;
        t2score = 0;
        wantShuffle = true;       
    }
    Game(Pack pack_in, bool shuffle_in, vector<Player*> players_in) {
        turnCount = 0;
        dealerCount = 0;
        t1score = 0;
        t2score = 0;
        wantShuffle = shuffle_in;
        pack = pack_in;
        players = players_in;
    }
    int gett1score() {
        return t1score;
    }
    int gett2score() {
        return t2score;
    }
    int getTurn() {
        return turnCount;
    }
    Player* getPlayer(int playerIndex) {
        return players[playerIndex];
    }
    void shuffler() {
        if (wantShuffle) {
            pack.shuffle();
        }
        else {
            pack.reset();
        }
    }
    void nextTurn() {
        if (turnCount == 3) {
            turnCount = 0;
        }
        else {
            turnCount++;
        }
    }
    int nextPlayer(int player_Index) {
        if (player_Index == 3) {
            return 0;
        }
        else {
            return player_Index + 1;
        }
    }
    void cardDeal() {
        // start to left of dealer
        int pos = nextPlayer(dealerCount);
        // declare dealer
        cout << players[dealerCount] << " deals\n";
        // deal 3-2-3-2
        for (int j = 0; j < 4; j++) {
            if (pos % 2 == 0) {
                for (int i = 0; i < 3; i++) {
                    players[pos]->add_card(pack.deal_one());
                }
                pos = nextPlayer(pos);
            }
            if (pos % 2 != 0) {
                for (int i = 0; i < 2; i++) {
                    players[pos]->add_card(pack.deal_one());
                }
                pos = nextPlayer(pos);
            }
        }
        // deal 2-3-2-3
        for (int j = 0; j < 4; j++) {
            if (pos % 2 == 0) {
                for (int i = 0; i < 2; i++) {
                    players[pos]->add_card(pack.deal_one());
                }
                pos = nextPlayer(pos);
            }
            if (pos % 2 != 0) {
                for (int i = 0; i < 3; i++) {
                    players[pos]->add_card(pack.deal_one());
                }
                pos = nextPlayer(pos);
            }
        }
        // flip upcard
        upcard = pack.deal_one();
        cout << upcard << " turned up\n";
    }
	void makeTrump() {
		// start to left of dealer
		int pos = nextPlayer(dealerCount);
		for (int i = 0; i < 4; i++) {
			if (pos == dealerCount) {
				if (players[pos]->make_trump(upcard, true, 1, trump)) {
					cout << players[pos] << " orders up " << trump << endl;
					players[pos]->add_and_discard(upcard);
					break;
				}
				else {
					cout << players[pos] << " passes\n";
				}
			}
			else {
				if (players[pos]->make_trump(upcard, false, 1, trump)) {
					cout << players[pos] << " orders up " << trump << endl;
					players[pos]->add_and_discard(upcard);
					break;
				}
				else {
					cout << players[pos] << " passes\n";
				}
			}
			pos = nextPlayer(pos);
			// consider screw the dealer here
		}
        for (int i = 0; i < 4; i++) {
            if (players[pos]->make_trump(upcard, false, 2, trump)) {
                cout << players[pos] << " orders up " << trump << endl;
                break;
            }
            else {
                cout << players[pos] << " passes\n";
            }
            pos = nextPlayer(pos);
        }
	}

    Card trickWinner(Card cardLed, Card justPlayed, Player* curWin, Player* curPlayer) {
        Card curPlayed = curPlayer->play_card(cardLed, trump);
        cout << curPlayed << " played by " << curPlayer << endl;
        if (Card_less(justPlayed, curPlayed, trump)) {
            curWin = curPlayer;
            return curPlayed;
        }
        return justPlayed;
    }

    int playTrick(int indexStarter) {

        // initialize players from start position
        int index = indexStarter;
        Player* starter = players[index];  // Player 0
        index = nextPlayer(index);
        Player* player1 = players[index];  // Player 1
        index = nextPlayer(index);
        Player* player2 = players[index];  // Player 2
        index = nextPlayer(index);
        Player* player3 = players[index];  // Player 3
        index = nextPlayer(index);

        // variables needed for trickWinner function
        Card winningCard;
        Player* curWinner = players[indexStarter];
        Card cardLed = starter->lead_card(trump);

        // print led card
        cout << cardLed << " led by " << *starter << endl;
        winningCard = cardLed;

        // determine winning card
        winningCard = trickWinner(cardLed, winningCard, player1, curWinner);
        winningCard = trickWinner(cardLed, winningCard, player2, curWinner);
        winningCard = trickWinner(cardLed, winningCard, player3, curWinner);
        cout << *curWinner << " takes the trick \n\n"; 

        // index of curWinner
        int indexWinner = indexStarter;
        for (int i = 0; i < players.size(); i++) {
            if (curWinner = players[i]) {
                indexWinner = i;
            }
        }
        return indexWinner;      
    }

    void playRound(int declareIndex) {

    }

    void roundScoreCalculator(int declareIndex, int t1roundsWon, int t2roundsWon) {
        if (declareIndex == 0 || declareIndex == 2) { // t1 called trump
            if (t1roundsWon >= 3 && t1roundsWon < 5) { // 1 point win
                t1score++;
                cout << *players[0] << " and " << *players[2] << " win the hand\n";
            }
            else if (t1roundsWon == 5) { // sweep case
                t1score += 2;
                cout << *players[0] << " and " << *players[2] 
                     << " win the hand\n" << "march!\n";
            }
            else if (t2roundsWon >= 3) { // euched case
                t2score =+ 2;
                cout << *players[1] << " and " << *players[3] 
                    << " win the hand\n" << "euchred!\n";
            }
        }
        if (declareIndex == 1 || declareIndex == 3) { // t1 called trump
            if (t2roundsWon >= 3 && t2roundsWon < 5) { // 1 point win
                t2score++;
                cout << *players[1] << " and " << *players[3] << " win the hand\n";
            }
            else if (t2roundsWon == 5) { // sweep case
                t2score += 2;
                cout << *players[1] << " and " << *players[3] 
                     << " win the hand\n" << "march!\n";
            }
            else if (t1roundsWon >= 3) { // euched case
                t1score =+ 2;
                cout << *players[0] << " and " << *players[2] 
                    << " win the hand\n" << "euchred!\n";
            }
        }
    }

};
int main(){
    cout << "hello from main!" << endl;
    // Game
        // Rounds
            // Setup
                // Shuffle
                // Deal
            // Make trump
                // Round 1
                // Round 2
            // Trick taking
            // Scoring
}
