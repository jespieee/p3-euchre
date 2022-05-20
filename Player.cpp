// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include <cassert>
using namespace std;
class Human : public Player
{
private:
  string name;
  std::vector<Card> hand;

public:
  Human() {
    name = "Default";
  }
  Human(const string& in_name) {
    name = in_name;
  }
  const std::string &get_name() const {
    return name;
  }

  void add_card(const Card &c) {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                                 int round, std::string &order_up_suit) const {
    assert(false);
  }

  void add_and_discard(const Card &upcard) {
    assert(false);
  }

  Card lead_card(const std::string &trump) {
    assert(false);
  }

  Card play_card(const Card &led_card, const std::string &trump) {
    assert(false);
  }
};
class Simple : public Player
{
private:
  string name;
  std::vector<Card> hand;

public:
  Simple() {
  name = "Default";
  }
  Simple(const string& in_name) {
  name = in_name;
  }
  const std::string& get_name() const {
    return name;
  }

  void add_card(const Card &c) {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
    // 2nd round strategy
    // orderup if hand has face of opposite color to order_up_suit
    if (round == 2) {
      for (int handCount = 0; handCount < MAX_HAND_SIZE; handCount++) {

      }
    }
    // 1st round strategy
    // check for 2 or more trump face cards
    int trumpFace = 0;
    for (int handCount = 0; handCount < MAX_HAND_SIZE; handCount++) {
      if (hand[handCount].is_face() && hand[handCount].is_trump(order_up_suit)) {
        trumpFace++;
      }
    }
    if (trumpFace >= 2) {
      if (is_dealer) {
        // call add and discard here
        return true;
      }
      else {
        return true;
      }
      }
      return false;
  }

  void add_and_discard(const Card &upcard) {
    assert(false);
  }

  Card lead_card(const std::string &trump) {
    assert(false);
  }

  Card play_card(const Card &led_card, const std::string &trump) {
    assert(false);
  }
};
Player *Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Human")
  {
    return new Human(name);
  }
  else {
    return new Simple(name);
  }
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
