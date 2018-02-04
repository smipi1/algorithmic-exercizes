#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>

#include "play_the_dragon.h"

//#define DEBUG

using namespace std;

struct Game {
public:
    Game(int Hd, int Ad, int Hk, int Ak, int B, int D)
    : Hd(Hd),
      Ad(Ad),
      Hk(Hk),
      Ak(Ak),
      Hd0(Hd),
      B(B),
      D(D)
    {
#ifdef DEBUG
        stringstream s;
        s << "Hd=" << Hd << " "
          << "Ad=" << Ad << " "
          << "Hk=" << Hk << " "
          << "Ak=" << Ak << " "
          << "B=" << B << " "
          << "D=" << D;
        play.push_back(s.str());
#endif
    }
    ~Game()
    {
    }
    typedef enum {
        GO_ON = 0,
        WON,
        LOST,
    } result;
    typedef enum {
        ATTACK = 0,
        BUFF,
        CURE,
        DEBUFF,
    } action;
    result turn(action a) {
#ifdef DEBUG
        string move = "Hd=" + to_string(Hd) + ": ";
#endif
        switch(a) {
        case ATTACK:
            Hk -= Ad;
#ifdef DEBUG
            move += "ATTACK(Hk=" + to_string(Hk) + ")";
#endif
            break;
        case BUFF:
            Ad += B;
#ifdef DEBUG
            move += "BUFF(Ad=" + to_string(Ad) + ")";
#endif
            break;
        case CURE:
            Hd = Hd0;
#ifdef DEBUG
            move += "CURE(Hd=" + to_string(Hd) + ")";
#endif
            break;
        case DEBUFF:
            Ak -= D;
            if(Ak < 0) {
                Ak = 0;
            }
#ifdef DEBUG
            move += "DEBUFF(Ak=" + to_string(Ak) + ")";
#endif
            break;
        }
#ifdef DEBUG
        play.push_back(move);
#endif
        if(Hk <= 0) {
#ifdef DEBUG
            cout << endl;
            for(auto p: play) {
                cout << p << endl;
            }
#endif
            return WON;
        }
        Hd -= Ak;
        if(Hd <= 0) {
            return LOST;
        }
        return GO_ON;
    }
    vector<int> state(void) {
        return {Hd, Ad, Hk, Ak};
    }
private:
    int Hd, Ad, Hk, Ak;
    int Hd0, B, D;
#ifdef DEBUG
    vector<string> play;
#endif
};

int find_fastest_win_game(Game& init) {
    vector<Game> games = {
            init,
    };
    map<vector<int>, bool> states;
    states[init.state()] = true;

    bool won = false;
    int turn = 0;
    while(!won && games.size() && turn < 200) {
        turn++;
        vector<Game>::size_type size = games.size();
        for(size_t i = 0; (i < size) && !won; i++) {
            for(int a = Game::ATTACK; a <= Game::DEBUFF; a++) {
                auto gn = games[i];
                switch(gn.turn(static_cast<Game::action>(a))) {
                case Game::GO_ON:
                    if(states.find(gn.state()) == states.end()) {
                        games.push_back(gn);
                        states[gn.state()] = true;
                    }
                    break;
                case Game::WON:
                    won = true;
                    break;
                case Game::LOST:
                    break;
                }
            }
        }
        games.erase(games.begin(), games.begin() + size);
    }
    if(won) {
        return turn;
    } else {
        return -turn;
    }
}

int main(int argc, char *argv[]) {
    int T;
    cin >> T;
    for(int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";

        int Hd, Ad, Hk, Ak, B, D;
        cin >> Hd >> Ad >> Hk >> Ak >> B >> D;

        auto init = Game(Hd, Ad, Hk, Ak, B, D);
        auto turns = find_fastest_win_game(init);
        if(turns < 0) {
            cout << "IMPOSSIBLE";
#ifdef DEBUG
            cout << ": " << -turns;
#endif
        } else {
            cout << turns;
        }
        cout << endl;
    }

    return 0;
}
