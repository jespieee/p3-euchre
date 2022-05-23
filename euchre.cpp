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
