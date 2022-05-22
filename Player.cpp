// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include <cassert>
#include <vector>
#include <algorithm>
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
      return false;
  }

  void add_and_discard(const Card &upcard) {
    assert(false);
  }

  Card lead_card(const std::string &trump) {
      Card returnCard;
      return returnCard;
  }

  Card play_card(const Card &led_card, const std::string &trump) {
      Card returnCard;
      return returnCard;
  }
};
class Simple : public Player {
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

    void add_card(const Card& c) {
        hand.push_back(c);
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const {
        // 2nd round strategy
        // orderup if hand has face of opposite color to order_up_suit
        if (round == 2) {
            for (int handCount = 0; handCount < MAX_HAND_SIZE; handCount++) {
                if (upcard.get_suit() == SUIT_NAMES_BY_WEIGHT[0] &&
                    hand[handCount].is_face() &&
                    hand[handCount].get_suit() == SUIT_NAMES_BY_WEIGHT[2]) {
                    order_up_suit = SUIT_NAMES_BY_WEIGHT[2];
                    return true;
                }
                else if (order_up_suit == SUIT_NAMES_BY_WEIGHT[1] &&
                    hand[handCount].is_face() &&
                    hand[handCount].get_suit() == SUIT_NAMES_BY_WEIGHT[3]) {
                    order_up_suit = SUIT_NAMES_BY_WEIGHT[3];
                    return true;
                }
                else if (order_up_suit == SUIT_NAMES_BY_WEIGHT[2] &&
                    hand[handCount].is_face() &&
                    hand[handCount].get_suit() == SUIT_NAMES_BY_WEIGHT[0]) {
                    order_up_suit = SUIT_NAMES_BY_WEIGHT[0];
                    return true;
                }
                else if (order_up_suit == SUIT_NAMES_BY_WEIGHT[3] &&
                    hand[handCount].is_face() &&
                    hand[handCount].get_suit() == SUIT_NAMES_BY_WEIGHT[1]) {
                    order_up_suit = SUIT_NAMES_BY_WEIGHT[1];
                    return true;
                }
            }
        }

        // 1st round strategy
        // check for 2 or more trump face cards
        else {
            int trumpFace = 0;
            for (int handCount = 0; handCount < MAX_HAND_SIZE; handCount++) {
                if (hand[handCount].is_face() && hand[handCount].is_trump(upcard.get_suit())) {
                    trumpFace++;
                }
            }
            if (trumpFace >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        return false;
    }

    void add_and_discard(const Card& upcard) {
        Card min = hand[0];
        int index = 0;
        for (int handCount = 0; handCount < static_cast<int>(hand.size()); handCount++) {
            if (hand[handCount] < min) {
                min = hand[handCount];
                index = handCount;
            }
        }
        if (min < upcard) {
            hand[index] = upcard;
        }
    }

    Card lead_card(const std::string& trump) {
        int numTrump = 0;
        int nonTrump = 0;
        sort(hand.begin(), hand.end());
        Card returnCard;
        // for loop to count num trump and non trump
        //sort(hand.begin(), hand.end());
        for (int handCount = 0; handCount < static_cast<int>(hand.size()); handCount++) {
            if (hand[handCount].get_suit() == trump) {
                numTrump++;
            }
            else {
                nonTrump++;
            }
        }
        if (numTrump == static_cast<int>(hand.size()) || 
            nonTrump == static_cast<int>(hand.size())) {
            // play highest
            returnCard = hand[hand.size() - 1];
            hand.erase(hand.begin() + hand.size() - 1);
        }
        else {
           
            Card max = hand[0];
            int i = hand.size() - 1;
            // play highest non trump
            while (!hand[i].is_trump(trump)) {
                if (hand[i] > max) {
                    max = hand[i];
                }
                i--;
            }
            returnCard = max;
            
            //returnCard = hand[hand.size() - 1 - numTrump];
            hand.erase(hand.begin() + hand.size() - 1 - numTrump);         
        }
        return returnCard;
    }

    Card play_card(const Card& led_card, const std::string& trump) {

        Card returnCard;
        sort(hand.begin(), hand.end());
        int ledIndex = 0;
        for (int handCount = 0; handCount < static_cast<int>(hand.size()); handCount++) {
            if (hand[handCount].get_suit() == led_card.get_suit()) {
                ledIndex = handCount;
            }
        }
        if (ledIndex != 0) {
            returnCard = hand[ledIndex];
            hand.erase(hand.begin() + ledIndex);
        }
        else {
            returnCard = hand[0];
            hand.erase(hand.begin());
        }
        return returnCard;
    }
};
Player *Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Human")
  {
    return new Human(name);
  }
  else if (strategy == "Simple") {
    return new Simple(name);
  }
  else {
      return nullptr;
  }
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
