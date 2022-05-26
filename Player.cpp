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
  vector<Card> hand;

public:
  Human() {
    name = "Default";
  }
  Human(const string& in_name) {
    name = in_name;
  }
  const string &get_name() const {
    return name;
  }

  void add_card(const Card &c) {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                                 int round, std::string &order_up_suit) const {
      for (int i = 0; i < static_cast<int>(hand.size()); i++) {
          cout << "Human player " << name << "'s hand: [" << i <<
              "] " << hand[i] << endl;
      }
      string choice;
      bool decision = true;
      cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
      cin >> choice;
      if (choice == "pass") {
          decision = false;
      }
      else {
          order_up_suit = choice;
      }
      return decision;
  }

  void add_and_discard(const Card &upcard) {
      cout << "Discard upcard: [-1]\n";
      cout << "Human player " << name << ", please select a card to discard:\n";
      int indexChosen;
      cin >> indexChosen;
      if (indexChosen == -1) {
          return;
      }
      else {
          hand[indexChosen] = upcard;
      }
      return;
  }

  Card lead_card(const std::string &trump) {
      sort(hand.begin(), hand.end());
      for (int i = 0; i < static_cast<int>(hand.size()); i++) {
          cout << "Human player " << name << "'s hand: [" << i <<
              "] " << hand[i] << endl;
      }
      cout << "Human player " << name << ", please select a card:\n";
      int indexChosen;
      cin >> indexChosen;
      return hand[indexChosen];
  }

  Card play_card(const Card &led_card, const std::string &trump) {
      sort(hand.begin(), hand.end());
      for (int i = 0; i < static_cast<int>(hand.size()); i++) {
          cout << "Human player " << name << "'s hand: [" << i <<
              "] " << hand[i] << endl;
      }
      cout << "Human player " << name << ", please select a card:\n";
      int indexChosen;
      cin >> indexChosen;
      return hand[indexChosen];
  }
};
class Simple : public Player {
private:
    string name;
    vector<Card> hand;

public:
    Simple() {
        name = "Default";
    }
    Simple(const string& in_name) {
        name = in_name;
    }
    const string& get_name() const {
        return name;
    }

    void add_card(const Card& c) {
        hand.push_back(c);
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const {

        string oppSuit = Suit_next(upcard.get_suit());
        if (round == 2 && is_dealer) {
            order_up_suit = oppSuit;
            return true;
        }
        else if (round == 1) {
            int trumpFace = 0;
            for (int i = 0; i < static_cast<int>(hand.size()); i++) {
                if (hand[i].is_face() &&
                    hand[i].is_trump(upcard.get_suit())) {
                    trumpFace++;
                }
            }
            if (trumpFace >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        else if (round == 2) {
            int count = 0;
            for (int i = 0; i < static_cast<int>(hand.size()); i++) {
                if (hand[i].is_left_bower(oppSuit) || hand[i].is_right_bower(oppSuit)) {
                    count++;
                }
                if (hand[i].is_face() && hand[i].get_suit() == oppSuit) {
                    count++;
                }
            }
            if (count >= 1) {
                order_up_suit = oppSuit;
                return true;
            }
        }
        return false;
    }

    void add_and_discard(const Card& upcard) {
        Card min = hand[0];
        int index = 0;
        for (int handCount = 0; handCount < static_cast<int>(hand.size()); handCount++) {
            if (Card_less(hand[handCount], min, upcard.get_suit(upcard.get_suit()))) {
                min = hand[handCount];
                index = handCount;
            }
        }
        if (Card_less(min, upcard, upcard.get_suit(upcard.get_suit()))) {
            hand[index] = upcard;
        }
    }

    Card lead_card(const std::string& trump) {
        sort(hand.begin(), hand.end());
        Card returnCard;
        bool hasRight = false, hasLeft = false;
        int leftIndex = 0, rightIndex = 0, numTrump = 0, nonTrump = 0;
        // for loop to count num trump and non trump
        for (int handCount = 0; handCount < static_cast<int>(hand.size()); handCount++) {
            if (hand[handCount].is_trump(trump)) {
                numTrump++;
                if (hand[handCount].is_left_bower(trump)) {
                    hasLeft = true;
                    leftIndex = handCount;
                }
                if (hand[handCount].is_right_bower(trump)) {
                    hasRight = true;
                    rightIndex = handCount;
                }
            }
            else {
                nonTrump++;
            }
        }
        if (numTrump == static_cast<int>(hand.size()) || 
            nonTrump == static_cast<int>(hand.size())) {
            if (hasRight) {
                returnCard = hand[rightIndex];
                hand.erase(hand.begin() + rightIndex);
            }
            else if (hasLeft && !hasRight) {
                returnCard = hand[leftIndex];
                hand.erase(hand.begin() + leftIndex);
            }
            else {
                returnCard = hand[hand.size() - 1];
                hand.erase(hand.begin() + hand.size() - 1);
            }
        }
        else {           
            for (int i = static_cast<int>(hand.size() - 1); i >= 0; i--) {
                if (!hand[i].is_trump(trump)) {
                    returnCard = hand[i];
                    hand.erase(hand.begin() + i);
                    return returnCard;
                }
            }        
        }
        return returnCard;
    }

    Card play_card(const Card& led_card, const std::string& trump) {

        Card returnCard;
        Card max;
        int index = 0;
        bool canFollow = false;
        for (int i = 0; i < static_cast<int>(hand.size()); i++) {
			if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                canFollow = true;
                max = hand[i];
                index = i;
			}
        }
        if (canFollow) {
            for (int i = 0; i < static_cast<int>(hand.size()); i++) {
                if (hand[i].get_suit(trump) == led_card.get_suit(trump) &&
					(Card_less(max, hand[i], trump))) {
					max = hand[i];
					index = i;
				}
            }
            hand.erase(hand.begin() + index);
            return max;
        }
        else {
            Card min = hand[0];
            int indexHolder = 0;
            for (int i = 0; i < static_cast<int>(hand.size()); i++) {
				if (Card_less(hand[i], min, trump)) {
					min = hand[i];
					indexHolder = i;
				}
            }
            hand.erase(hand.begin() + indexHolder);
            return min;
        }
        return returnCard;
    }
};
Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Human")
  {
    return new Human(name);
  }
  else if (strategy == "Simple") {
    return new Simple(name);
  }
  else {
      assert(false);
      return nullptr;
  }
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
