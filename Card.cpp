// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these

constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS; 

Card::Card(){
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

Card::Card(const std::string &rank_in, const std::string &suit_in){
    rank = rank_in;
    suit = suit_in;
}

std::string Card::get_rank()const{
    return rank;
}

std::string Card::get_suit()const{
    return suit;
}

std::string Card::get_suit(const std::string &trump)const{
    if (trump == SUIT_DIAMONDS) {
        if(is_left_bower(trump)){
            return SUIT_DIAMONDS;
        }
        return suit;
    }
    else if (trump == SUIT_HEARTS) {
        if(is_left_bower(trump)){
            return SUIT_HEARTS;
        }
        return suit;
    }
    else if (trump == SUIT_CLUBS) {
        if(is_left_bower(trump)){
            return SUIT_CLUBS;
        }
        return suit;
    }
    else {
        if(is_left_bower(trump)){
            return SUIT_SPADES;
        }
        return suit;
    }
}

bool Card::is_face()const{

    if (rank == RANK_JACK || rank == RANK_QUEEN || 
        rank == RANK_KING || rank == RANK_ACE) {
        return true;
    }
    return false;
}


bool Card::is_right_bower(const std::string &trump)const{
    if(rank == RANK_JACK && suit == trump){
        return true;
    }
    else{
        return false;
    }

}

bool Card::is_left_bower(const std::string &trump)const{
    if (rank == RANK_JACK && get_suit(trump) == trump) {
        
        return true;
    }
    return false;
}

bool Card::is_trump(const std::string &trump) const{

    if(trump == suit || is_left_bower(trump)){
        return true;
    }
    else{

        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card& lhs, const Card& rhs) {
    int lhs_rank = 0;
    int rhs_rank = 0;
    for (int j = 0; j < 13; j++) {       
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhs_rank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhs_rank = j;
        }
    }
    if (lhs_rank < rhs_rank) {
        return true;
    }
    else if (lhs_rank > rhs_rank) {
        return false;
    }
    else {
        int lhs_suit = 0;
        int rhs_suit = 0;
        for (int i = 0; i < 4; i++ ){
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhs_suit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhs_suit = i;
            }
        }
        if (lhs_suit < rhs_suit) {
            return true;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card& lhs, const Card& rhs) {
    int lhs_rank = 0;
    int rhs_rank = 0;
    for (int j = 0; j < 13; j++) {       
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhs_rank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhs_rank = j;
        }
    }
    if (lhs_rank < rhs_rank) {
        return true;
    }
    else if (lhs_rank > rhs_rank) {
        return false;
    }
    else if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        int lhs_suit = 0;
        int rhs_suit = 0;
        for (int i = 0; i < 4; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhs_suit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhs_suit = i;
            }
        }
        if (lhs_suit < rhs_suit) {
            return true;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card& lhs, const Card& rhs) {
    int lhs_rank = 0;
    int rhs_rank = 0;
    for (int j = 0; j < 13; j++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhs_rank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhs_rank = j;
        }
    }
    if (lhs_rank > rhs_rank) {
        return true;
    }
    else if (lhs_rank < rhs_rank) {
        return false;
    }
    else {
        int lhs_suit = 0;
        int rhs_suit = 0;
        for (int i = 0; i < 4; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhs_suit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhs_suit = i;
            }
        }
        if (lhs_suit > rhs_suit) {
            return true;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card& lhs, const Card& rhs) {
    int lhs_rank = 0;
    int rhs_rank = 0;
    for (int j = 0; j < 13; j++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhs_rank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhs_rank = j;
        }
    }
    if (lhs_rank > rhs_rank) {
        return true;
    }
    else if (lhs_rank < rhs_rank) {
        return false;
    }
    else if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        int lhs_suit = 0;
        int rhs_suit = 0;
        for (int i = 0; i < 4; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhs_suit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhs_suit = i;
            }
        }
        if (lhs_suit > rhs_suit) {
            return true;
        }
    }
    return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card& lhs, const Card& rhs) {
    return (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit());
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs.get_rank() == rhs.get_rank() || lhs.get_suit() == rhs.get_suit());
}

std::string Suit_next(const std::string &suit){
    if (suit == Card::SUIT_DIAMONDS){
        return Card::SUIT_HEARTS;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else {
        return Card::SUIT_CLUBS;
    }
}


//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    //both trump
    if(a.get_suit() == trump && b.get_suit() == trump){
        if(a.get_rank() >= b.get_rank()){
            return false;
        }
    }
    //a trump
    else if(a.get_suit() == trump && b.get_suit() != trump){
        return false;
    }
    //btrump
    else if(b.get_suit() == trump && a.get_suit() != trump){
        return true;
    }
    else{
        if(a.get_rank() >= b.get_rank()){
            return false;
        }
    }
    return true;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if(a.get_suit() == trump && b.get_suit() == trump){
        if(a.get_rank() >= b.get_rank()){
            return false;
        }
    }
    //a trump
    else if(a.get_suit() == trump && b.get_suit() != trump){
        return false;
    }
    //btrump
    else if(b.get_suit() == trump && a.get_suit() != trump){
        return true;
    }
    //a led card suit but b not
    else if(a.get_suit() == led_card.get_suit() && b.get_suit()
                                                != led_card.get_suit()){
        //maybe check if b is not trump
        return false;
    }
    //b led card suit but a not
    else if(a.get_suit() == led_card.get_suit() && b.get_suit() == led_card.get_suit()){
        if(a.get_rank() >= b.get_rank()){
            return false;
        }
    }
    //both led card suit
    return true;
}
// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


