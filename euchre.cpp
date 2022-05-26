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

/* Play game (shuffle, points to win, pack_in)
        play round
            make trump
            play tricks
            */
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
    void setPlayers(vector<Player*> players_in) {
        for (int i = 0; i < static_cast<int>(players_in.size()); i++) {
            players[i] = players_in[i];
        }
    }

    void playRound(int declareIndex) {
        int t1roundScore = 0;
        int t2roundScore = 0;
        int firstWinner = playTrick(nextPlayer(dealerCount));
        if (firstWinner == 0 || firstWinner == 2) {
            t1roundScore++;
        }
        else if (firstWinner == 1 || firstWinner == 3) {
            t2roundScore++;
        }
        int nextPos = firstWinner;
        for (int i = 1; i < 5; i++) {

            int winnersAfter = playTrick(nextPos);
            if (winnersAfter == 0 || winnersAfter == 2) {
                t1roundScore++;
            }
            else if (winnersAfter == 1 || winnersAfter == 3) {
                t2roundScore++;
            }
            nextPos = winnersAfter;
        }
        dealerCount = nextPlayer(dealerCount);
        roundScoreCalculator(declareIndex, t1roundScore, t2roundScore);
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
    
        // declare dealer
        cout << *players[dealerCount] << " deals\n";
        // start to left of dealer
        int pos = nextPlayer(dealerCount);
        // deal 3-2-3-2
        for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 3; i++) {
				players[pos]->add_card(pack.deal_one());
			}
			pos = nextPlayer(pos);
			for (int i = 0; i < 2; i++) {
				players[pos]->add_card(pack.deal_one());
			}
			pos = nextPlayer(pos);
        }
        pos = nextPlayer(dealerCount);
        // deal 2-3-2-3
        for (int j = 0; j < 2; j++) {
			for (int i = 0; i < 2; i++) {
				players[pos]->add_card(pack.deal_one());
			}
			pos = nextPlayer(pos);
			for (int i = 0; i < 3; i++) {
				players[pos]->add_card(pack.deal_one());
			}
			pos = nextPlayer(pos);
        }
        // flip upcard
        upcard = pack.deal_one();
        cout << upcard << " turned up\n";
    }
    
	int makeTrump() {
		// start to left of dealer
		int pos = nextPlayer(dealerCount);
		for (int i = 0; i < 4; i++) {
			if (pos == dealerCount) {
				if (players[pos]->make_trump(upcard, true, 1, trump)) {
                    cout << *players[pos] << " orders up " << trump << endl << endl;
					players[dealerCount]->add_and_discard(upcard);
                    return pos;
				}
				else {
					cout << *players[pos] << " passes\n";
				}
			}
			else {
				if (players[pos]->make_trump(upcard, false, 1, trump)) {
                    cout << *players[pos] << " orders up " << trump << endl << endl;
					players[dealerCount]->add_and_discard(upcard);
                    return pos;
				}
				else {
					cout << *players[pos] << " passes\n";
				}
			}
			pos = nextPlayer(pos);
			// consider screw the dealer here
		}
        for (int i = 0; i < 4; i++) {
            if (players[pos]->make_trump(upcard, false, 2, trump)) {
                cout << *players[pos] << " orders up " << trump << endl << endl;
                return pos;
                break;
            }
            else {
                cout << *players[pos] << " passes\n";
            }
            pos = nextPlayer(pos);
        }
        dealerCount = nextPlayer(dealerCount);
        return pos;
	}

    int playTrick(int indexStarter) {
        // initialize players from start position
        Player* starter = players[indexStarter];  // Player 0      
        Player* curWinner = starter;
        Card cardLed = starter->lead_card(trump);
        Card winningCard = cardLed;
        Card compareCard;
        // print led card
        cout << cardLed << " led by " << *starter << endl;
        // determine winning card
        int index = nextPlayer(indexStarter);
        int indexWinner = indexStarter;
        for (int i = 0; i < 3; i++) {
            compareCard = players[index]->play_card(cardLed, trump);
            cout << compareCard << " played by " << *players[index] << endl;
            if (Card_less(winningCard, compareCard, cardLed, trump)) {
                curWinner = players[index];
                winningCard = compareCard;
                indexWinner = index;
            }
            index = nextPlayer(index);
        }
        cout << *curWinner << " takes the trick\n\n"; 
        return indexWinner;      
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
                t2score += 2;
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
                t1score += 2;
                cout << *players[0] << " and " << *players[2] 
                    << " win the hand\n" << "euchred!\n";
            }
        }
    }

    void declareWinner() {
        if (t1score > t2score) {
            cout << *players[0] << " and " << *players[2] << " win!\n";
        }
        else {
            cout << *players[1] << " and " << *players[3] << " win!\n";
        }
    }

};

void playGame(Game game, int points_to_win, vector<Player*> players_in) {
    // remain in point limit
    int handNumber = 0;
    while (game.gett1score() < points_to_win &&
           game.gett2score() < points_to_win) {
        // shuffle and deal
        cout << "Hand " << handNumber << endl;
        handNumber++;
        game.shuffler();
        game.cardDeal();
        // print hand number and begin round
        game.playRound(game.makeTrump());
        cout << *players_in[0] << " and " << *players_in[2] 
             << " have " << game.gett1score() << " points\n";
        cout << *players_in[1] << " and " << *players_in[3] 
             << " have " << game.gett2score() << " points\n\n";
             
    }
    game.declareWinner();
}

int main(int argc, char** argv){
    int scoreLimit = atoi(argv[3]);
    string fileName = argv[1];
    string shuffleType = argv[2], player1Type = argv[5], player2Type = argv[5];
    string player3Type = argv[9], player4Type = argv[11];
    string player1Name = argv[4], player2Name = argv[6], player3Name = argv[8];
    string player4Name = argv[10];
    bool validShuffle = true, isPlayer = true, wantShuffle = false;
    if (shuffleType == "shuffle") {
        wantShuffle = true;
    }
    if (shuffleType == "noshuffle") {
        wantShuffle = false;
    }
    if (shuffleType != "shuffle" && shuffleType != "noshuffle") {
        validShuffle = false;
    }
    if (player1Type != "Simple" && player1Type != "Human") {
        isPlayer = false;
    }
    if (player2Type != "Simple" && player1Type != "Human") {
        isPlayer = false;
    }
    if (player3Type != "Simple" && player1Type != "Human") {
        isPlayer = false;
    }
    if (player4Type != "Simple" && player1Type != "Human") {
        isPlayer = false;
    }
    if (argc != 12 || scoreLimit < 1 || scoreLimit > 100 ||
        !validShuffle || !isPlayer) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
             return 1;
    }
    cout << "./euchre.exe " << fileName << " "
        << shuffleType << " " << scoreLimit << " " <<
        player1Name << " " << player1Type << " " <<
        player2Name << " " << player2Type << " " <<
        player3Name << " " << player3Type << " " <<
        player4Name << " " << player4Type << " " << endl;

    
    ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        cout << "Error opening " << fileName << endl;
        return 1;
    }
    
    Pack pack = Pack(file);
    vector<Player*> players = {Player_factory(string(argv[4]), player1Type),
                               Player_factory(string(argv[6]), player2Type), 
                               Player_factory(string(argv[8]), player3Type), 
                               Player_factory(string(argv[10]), player4Type)};
    Game game = Game(pack, wantShuffle, players);

    playGame(game, scoreLimit, players);
    
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        delete players[i];
    }
    
    return 1;
}
