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
    assert(false);
}

bool Card::is_face()const{
    if(rank == RANK_ACE || rank == RANK_QUEEN || rank == RANK_KING ||
       rank == RANK_JACK){
        return true;
    }
    else{
        return false;
    }
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
    assert(false);
}

bool Card::is_trump(const std::string &trump) const{
    if(trump == suit || is_left_bower(trump)){
        return true;
    }
    else{
        return false;
    }
}


bool operator<(const Card& lhs, const Card& rhs) {
    assert(false);
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card& lhs, const Card& rhs) {
    assert(false);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card& lhs, const Card& rhs) {
    assert(false);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card& lhs, const Card& rhs) {
    assert(false);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card& lhs, const Card& rhs) {
    assert(false);
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card& lhs, const Card& rhs) {
    assert(false);
}

std::string Suit_next(const std::string &suit){
    assert(false);
}


//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream& operator<<(std::ostream& os, const Card& card) {
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    assert(false);
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
