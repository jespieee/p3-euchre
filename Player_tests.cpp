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

TEST(test_add_card) {
    Player* alice = Player_factory("Alice", "Simple");
    Player* john = Player_factory("John", "Human");
    Card c = Card();
    alice->add_card(c);
    
    delete john;
    delete alice;
}
// Add more tests here

TEST_MAIN()
