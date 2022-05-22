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

TEST(test_card_defctor) {
    Card c = Card();
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_suit_functional) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit("Spades"));
}

TEST(test_is_left_bower) {
    Card c = Card();
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_left_bower(Card::SUIT_CLUBS));
}

TEST(test_is_face) {
    Card c = Card();
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c3(Card::RANK_KING, Card::SUIT_SPADES);
    Card c4(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_face());
    ASSERT_TRUE(c1.is_face());
    ASSERT_TRUE(c2.is_face());
    ASSERT_TRUE(c3.is_face());
    ASSERT_TRUE(c4.is_face());

}

TEST(test_is_right_bower) {
    Card c = Card();
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_SPADES));
    ASSERT_TRUE(c1.is_right_bower(Card::SUIT_SPADES));
}

TEST(test_is_trump) {
    Card c = Card();
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    // basic case
    ASSERT_TRUE(c.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(c.is_trump(Card::SUIT_CLUBS));
    // left bower case
    ASSERT_TRUE(c1.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(c1.is_trump(Card::SUIT_CLUBS));
}

TEST(test_less_operator ) {
    
    // rank less/more
    Card left(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card right(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(left < right); // less
    Card right1(Card::RANK_FIVE, Card::SUIT_CLUBS);
    ASSERT_FALSE(left < right1); // more

    // rank same suit less/more
    Card sameRank(Card::RANK_THREE, Card::SUIT_CLUBS);
    Card sameRank1(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(sameRank < sameRank1);
    ASSERT_FALSE(sameRank1 < sameRank);
}

TEST(test_less_equal_operator) {
    Card left(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card right(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card greater(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(left <= right);
    ASSERT_TRUE(right <= left);
    ASSERT_TRUE(left <= greater);
    ASSERT_FALSE(greater <= left);
}

TEST(test_greater_operator) {

    Card left(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card right(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card left1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(left > right);
    ASSERT_FALSE(right > left);
    ASSERT_FALSE(left > left1);
    ASSERT_TRUE(left1 > left);

}

TEST(test_greater_equal_operator) {

    Card left(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card right(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card right1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(left >= right);
    ASSERT_TRUE(right >= left);
    ASSERT_TRUE(right1 >= left);
    ASSERT_FALSE(left >= right1);

}

TEST(test_equal_operator) {
    Card left(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card right(Card::RANK_FOUR, Card::SUIT_CLUBS);
    Card left1(Card::RANK_SIX, Card::SUIT_HEARTS);
    ASSERT_TRUE(left == right);
    ASSERT_FALSE(left == left1);
}

TEST(test_unequal_operator) {
    Card left(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card right(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card left1(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_FALSE(left != right);
    ASSERT_TRUE(left != left1);
}

TEST(test_suit_next) {
    string d = Suit_next(Card::SUIT_HEARTS);
    string h = Suit_next(Card::SUIT_DIAMONDS);
    string c = Suit_next(Card::SUIT_SPADES);
    string s = Suit_next(Card::SUIT_CLUBS);
    ASSERT_EQUAL(d, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(h, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c, Card::SUIT_CLUBS);
    ASSERT_EQUAL(s, Card::SUIT_SPADES);

}

TEST(test_output_operator) {
    Card c = Card();
    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Two of Spades");

}

TEST(test_card_less1) {
    Card c(Card::RANK_TWO, Card::SUIT_SPADES);
    Card c1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c4(Card::RANK_JACK, Card::SUIT_HEARTS);

    // both trump
    ASSERT_TRUE(Card_less(c3, c4, Card::SUIT_HEARTS));
    // rank less
    ASSERT_TRUE(Card_less(c, c1, Card::SUIT_HEARTS));
    // rank less but trump
    ASSERT_FALSE(Card_less(c, c1, Card::SUIT_SPADES));
    // same card
    ASSERT_FALSE(Card_less(c1, c2, Card::SUIT_HEARTS));
    // rank same suit less
    ASSERT_TRUE(Card_less(c3, c1, Card::SUIT_SPADES));
    // rank less suit same
    ASSERT_TRUE(Card_less(c4, c1, Card::SUIT_SPADES));
    // left bower
    ASSERT_FALSE(Card_less(c4, c1, Card::SUIT_DIAMONDS));
}


TEST(test_card_less2) {

    // both trump

}
// Add more test cases here

TEST_MAIN()
