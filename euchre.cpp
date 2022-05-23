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
        for (int round = 1; round < 3; round++) {
            int pos = nextPlayer(dealerCount);
            for (int i = 0; i < 4; i++) {
                if (pos == dealerCount && round == 1) {
                    if (players[pos]->make_trump(upcard, true, round, trump)) {
                        cout << players[pos] << " orders up " << trump << endl;
                        players[pos]->add_and_discard(upcard);
                        break;
                    }
                    else {
                        cout << players[pos] << " passes\n";
                    }
                }
                else {
                    if (players[pos]->make_trump(upcard, false, round, trump)) {
                        cout << players[pos] << " orders up " << trump << endl;
                        if (round == 1) {
                            players[pos]->add_and_discard(upcard);
                        }
                        break;
                    }
                    else {
                        cout << players[pos] << " passes\n";
                    }
                }
                pos = nextPlayer(pos);
                // consider screw the dealer here
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
