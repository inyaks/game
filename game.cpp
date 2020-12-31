#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Deck
{
public:

    int draw_card()
    {
        return rand() % 10 + 1;
    };
};

class Player
{
    string _name;
    vector<int> _cards;
    Deck _deck;

public:

    Player()
    {
    };

    Player(const Deck& deck, string name = "Dealer")
    {
        _deck = deck;
        _name = string(name);
    };

    int draw_from_deck()
    {
        int card = _deck.draw_card();
        _cards.push_back(card);

        return card;
    };

    const char* get_name() const
    {
        return _name.c_str();
    };

    int get_total() const
    {
        int total = 0;
        for (int card : _cards)
        {
            total += card;
        }

        return total;
    };

    friend ostream& operator<<(ostream& os, const Player& player)
    {
        os << player._name << " : ";
        for (int card : player._cards)
        {
            os << card << " ";
        }

        return os;
    }
};

class Game
{
    vector<Player> _players;
    Player _dealer;
    int _rounds;

    void initialize(const vector<string>& players)
    {
        _players.clear();

        Deck deck;
        _dealer = Player(deck);

        for (string player : players)
        {
            _players.push_back(Player(deck, player));
        }
    };

public:

    void play(const vector<string>& players, int rounds)
    {
        initialize(players);
        _rounds = rounds;

        srand(time(NULL));

        _dealer.draw_from_deck();

        for (int i = 0; i < _rounds; i++)
        {
            for (auto player = _players.begin(); player != _players.end(); player++)
            {
                player->draw_from_deck();
            }

            _dealer.draw_from_deck();
        }
    };

    void print()
    {
        Player* winner = &_dealer;
        int max = _dealer.get_total();

        cout << _dealer << endl;

        for (auto player = _players.begin(); player != _players.end(); player++)
        {
            cout << *player << endl;
            int player_total = player->get_total();

            if (player_total > max)
            {
                max = player_total;
                *winner = *player;
            }
        }

        cout << "Winner : " << winner->get_name() << endl;
    }
};

int main()
{
    Game game;

    vector<string> players = { "Player 1",  "Player 2" ,  "Player 3" };
    game.play(players, 3);
    
    game.print();
}
