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
public:
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

int attacks_to_kill(int Hk, int Ad) {
    return (Hk + Ad - 1) / Ad;
}

int cure_pitch(int Hd, int Ak) {
    return (Hd - 1) / Ak;
}

int cures_to_survive(int Ak, int Hd_start, int Hd_cured, int N) {
    if(Ak == 0) {
        return 0;
    }
    int Nc = 0;
    if(Hd_start < Hd_cured) {
        Nc += 1;
        N -= cure_pitch(Hd_start, Ak);
    }
    auto Pc = cure_pitch(Hd_cured, Ak);
    if(Pc <= 0) {
        return -1;
    }
    Nc += (N - 1) / Pc;
    return Nc;
}

int buffs_to_kill_with_1_blow(int Ad, int B, int Hk) {
    return (Hk - Ad + B - 1) / B;
}

int optimal_buff_and_attack_game_number_of_turns(int Hd_start, int Hd_cured, int Ad, int Hk, int Ak, int B) {
    int Nb = 0;
    int Na = attacks_to_kill(Hk, Ad);
    if(B > 0) {
        int Nb_max = buffs_to_kill_with_1_blow(Ad, B, Hk);
        int Nb_a_min = Na;
        for(int Nb_next = 0; Nb_next <= Nb_max; Nb_next++) {
            int Ad_buff = Ad + Nb_next * B;
            int Na_rem = attacks_to_kill(Hk, Ad_buff);
            int Nb_a = Nb_next + Na_rem;
            if(Nb_a_min < Nb_a) {
                Nb_a_min = Nb_a;
                Nb = Nb_next;
                Na = Na_rem;
            }
        }
    }
    auto Nc = cures_to_survive(Ak, Hd_start, Hd_cured, Na + Nb);
    if(Nc <= 0) {
        return -1;
    }
#ifdef DEBUG
    cout << "Nb=" << Nb << ", "
         << "Na=" << Na << ", "
         << "Nc=" << Nc << endl;
#endif
    return Nb + Na + Nc;
}

int debuffs_to_disarm_knight(int Ak, int D) {
    return (Ak + D - 1) / D;
}

int min_game_number_of_turns(int const Hd, int const Ad, int const Hk, int const Ak, int const B, int const D) {
    if(Hd - (Ak - D) < 1) {
        return -1;
    }
    int N_min = optimal_buff_and_attack_game_number_of_turns(Hd, Hd, Ad, Hk, Ak, B);
    if(D > 0) {
        int Nd_max = debuffs_to_disarm_knight(Ak, D);
        for(int Nd = 0; Nd <= Nd_max; Nd++) {
            int Hd_rem = Hd;
            int Ak_rem = Ak;
            int Nc_d = 0;
            for(int i = 0; i < Nd; i++) {
                if(Hd_rem - Ak < 1) {
                    Nc_d++;
                    Hd_rem = Hd;
                }
                Ak_rem -= D;
            }
            auto N_rem = optimal_buff_and_attack_game_number_of_turns(Hd_rem, Hd, Ad, Hk, Ak_rem, B);
            auto N = Nd + Nc_d + N_rem;
            if(N_min > N) {
                N_min = N;
            }
        }
    }
    return N_min;
}

int main(int argc, char *argv[]) {
    int T;
    cin >> T;
    for(int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";

        int Hd, Ad, Hk, Ak, B, D;
        cin >> Hd >> Ad >> Hk >> Ak >> B >> D;

//        auto init = Game(Hd, Ad, Hk, Ak, B, D);
        auto turns = min_game_number_of_turns(Hd, Ad, Hk, Ak, B, D);
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
