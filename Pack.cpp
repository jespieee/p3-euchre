// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include "Pack.h"
#include <iostream>
using namespace std;


Pack::Pack() {
    //int index_nine = 7;
    int suit_count = 0;
    for(int num = 0; num < 24; num++){
        for(int rank_count = 7; rank_count < 12; rank_count++){
            cards[num] = Card(RANK_NAMES_BY_WEIGHT[rank_count],SUIT_NAMES_BY_WEIGHT[suit_count]);
            num++;
        }
        suit_count++;
        if(suit_count == 4){
            suit_count = 0;
        }
    }
    
}

Pack::Pack(std::istream& pack_input) {
    string rank_in;
    string hold;
    string suit_in;
    
    for(int num = 0; num < 24; num++){
        pack_input >> rank_in >> hold >> suit_in;
        cards[num] = Card(rank_in, suit_in);
    }
}

Card Pack::deal_one() {
    Card wanted = cards[next];
    next++;
    return wanted;
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    //in shuffle 7 times
    std::array<Card, PACK_SIZE> shuffled;
    shuffled[0] = cards[12];
    shuffled[1] = cards[0];
    int counter2nd = 12;
    int counter1st = 0;
    for(int i = 0; i < 7; i++){
        for (int j = 2; j < PACK_SIZE; j++) {
            if (j % 2 == 0) {
                shuffled[j] = cards[counter2nd];
                counter2nd++;
            }
            else {
                shuffled[j] = cards[counter1st];
                counter1st++;
            }
        }
        //go down each pile swapping positions of cards
    }
    for (int i = 0; i < PACK_SIZE; i++) {
        cards[i] = shuffled[i];
    }
    return;
}


bool Pack::empty() const {
    assert(false);
    assert(next);
}
