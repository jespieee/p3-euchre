// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include <cassert>
Player * Player_factory(const std::string &name, const std::string &strategy) {
  assert(false);
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

/*const std::string & Player::get_name() const = 0;{
    assert(false);
}

void Player::add_card(const Card &c) = 0{
    assert(false);
  }

virtual bool Player::make_trump(const Card &upcard, bool is_dealer,
                        int round, std::string &order_up_suit) const = 0{
    assert(false);
  }


virtual void Player::add_and_discard(const Card &upcard) = 0{
    assert(false);
  }

virtual Card Player::lead_card(const std::string &trump) = 0{
    assert(false);
  }

virtual Player::Card play_card(const Card &led_card, const std::string &trump) = 0{
    assert(false);
  }
*/

