// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    Player* john = Player_factory("John", "Human");
    ASSERT_EQUAL("Alice", alice->get_name());
    ASSERT_EQUAL("John", john->get_name());
    delete john;
    delete alice;
}

TEST(test_make_trump) {

    // does NOT have 2 or more face cards on round 1
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    string trump;
    bool orderup = alice->make_trump(
        nine_hearts,  
        true,
        1,             
        trump           
    );

    ASSERT_FALSE(orderup);

    delete alice;
}

TEST(test_make_trump2) {
    // round 2 case orderup true
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = alice->make_trump(
        nine_spades,    
        true,           
        2,              
        trump           
    );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

    delete alice;
}

TEST(test_make_trump3) {
    // round 2 case orderup false
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump;
    bool orderup = alice->make_trump(
        nine_spades,
        false,
        2,
        trump
    );

    ASSERT_FALSE(orderup);


    delete alice;
}

TEST(test_lead_card) {

    // all trump or non trump case
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    Card card_led = alice->lead_card(Card::SUIT_SPADES);

    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, jack_spades); //check led card

    delete alice;
}

TEST(test_lead_card2) {

    // has both bowers case
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));

    Card card_led = alice->lead_card(Card::SUIT_CLUBS);

    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, jack_clubs); //check led card

    delete alice;
}

TEST(test_lead_card3) {

    // has trump and non trump
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

    Card card_led = alice->lead_card(Card::SUIT_CLUBS);

    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, queen_hearts); //check led card

    delete alice;
}
TEST(test_lead_card4) {

    // has no trump
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

    Card card_led = alice->lead_card(Card::SUIT_SPADES);

    Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, ace_hearts); //check led card

    delete alice;
}

TEST(test_play_card) {

    // only rank considered
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));


    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card card_played = alice->play_card(
        nine_diamonds,  
        "Hearts"      
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    delete alice;
}

TEST(test_play_card2) {

    // no led suit
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));


    Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card card_played = alice->play_card(
        queen_hearts,
        "Hearts"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    delete alice;
}

TEST(test_play_card3) {

    // mix of led suit and others
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));


    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card card_played = alice->play_card(
        jack_spades,
        "Spades"
    );

    ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_SPADES));
    delete alice;
}

TEST(test_add_and_discard_add){
    Player* p1 = Player_factory("Rico", "Simple");
    p1->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    p1->add_and_discard(Card(Card::RANK_KING, Card::SUIT_SPADES));
    Card played = p1->play_card(Card(Card::RANK_TEN, Card::SUIT_SPADES), Card::SUIT_HEARTS);
    
    ASSERT_EQUAL(played, Card(Card::RANK_KING, Card::SUIT_SPADES));
    delete p1;
}

TEST(test_add_and_discard_not){
    Player* p1 = Player_factory("Rico", "Simple");
    p1->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    p1->add_and_discard(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    Card played = p1->play_card(Card(Card::RANK_TEN, Card::SUIT_SPADES), Card::SUIT_HEARTS);
    
    ASSERT_EQUAL(played, Card(Card::RANK_KING, Card::SUIT_SPADES));
    delete p1;
}

TEST_MAIN()
