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
  const std::string &get_name() const
  {
    assert(false);
  }

  void add_card(const Card &c)
  {
    assert(false);
  }

  virtual bool Human::make_trump(const Card &upcard, bool is_dealer,
                                 int round, std::string &order_up_suit) const
  {
    assert(false);
  }

  virtual void add_and_discard(const Card &upcard)
  {
    assert(false);
  }

  virtual Card lead_card(const std::string &trump)
  {
    assert(false);
  }

  virtual Card play_card(const Card &led_card, const std::string &trump)
  {
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
  const std::string &Simple::get_name() const {
    return name;
  }

  void add_card(const Card &c) {
    hand.push_back(c);
  }

  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
    assert(false);
  }

  virtual void add_and_discard(const Card &upcard)
  {
    assert(false);
  }

  virtual Card lead_card(const std::string &trump)
  {
    assert(false);
  }

  virtual Card play_card(const Card &led_card, const std::string &trump)
  {
    assert(false);
  }
};
Player *Player_factory(const std::string &name, const std::string &strategy)
{
  if (strategy == "Human")
  {
    return new Human(name);
  }
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
  assert(false);
}
