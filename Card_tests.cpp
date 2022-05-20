// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(is_left_bower){
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(jack_spades.is_left_bower("Clubs"));
}

// Add more test cases here

TEST_MAIN()
