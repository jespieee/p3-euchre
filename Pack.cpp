// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include "Pack.h"
#include <iostream>
using namespace std;


Pack::Pack() {
    //int index_nine = 7;
    int suit_count = 0;
    for(int num = 0; num < 24; num++){
        for(int rank_count = 7; rank_count <= 12; rank_count++){
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
    int hold = next;
    ++next;
    return cards[hold];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    //in shuffle 7 times
    for(int i = 0; i < 7; i++) {
        std::array<Card, 12> half2;
        std::array<Card, 12> half1;
        for (int j = 0; j < 12; j++) {
            half1[j] = cards[j];
        }
        for (int k = 0; k < 12; k++) {
            half2[k] = cards[k + 12];
        }
        for (int l = 0; l < 23; l += 2) {
            cards[l] = half2[l / 2];
            cards[l + 1] = half1[l / 2];
        }
        //go down each pile swapping positions of cards
    }
    reset();
}


bool Pack::empty() const {
    assert(false);
    assert(next);
}
