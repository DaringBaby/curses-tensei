#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

class Character {
private:
    std::string name;
    int level;
    int exp;
    int exp_to_next_level;

    std::string status;

    int hp;
    int max_hp;
    int mp;
    int max_mp;

    int attack;
    int defense;
    int magic_attack;
    int magic_resistance;
    int speed;
    int luck;

    std::string weapon;
    std::string gun;
    std::string head;
    std::string helmet;
    std::string gloves;
    std::string legs;

public:
    Character(std::string char_name = "Hero", int start_level = 1)
        : name(char_name), level(start_level), exp(0), exp_to_next_level(100),
          hp(50), max_hp(50), mp(20), max_mp(20),
          attack(10), defense(10), magic_attack(10), magic_resistance(10),
          speed(10), luck(10), status("None"),
          weapon("None"), gun("None"), head("None"), helmet("None"),
          gloves("None"), legs("None") {}

    std::string get_name() const { return name; }
    int get_level() const { return level; }
    int get_exp() const { return exp; }
    int get_exp_to_next_level() const { return exp_to_next_level; }

    std::string get_status() const { return status; }

    int get_hp() const { return hp; }
    int get_max_hp() const { return max_hp; }
    int get_mp() const { return mp; }
    int get_max_mp() const { return max_mp; }

    int get_attack() const { return attack; }
    int get_defense() const { return defense; }
    int get_magic_attack() const { return magic_attack; }
    int get_magic_resistance() const { return magic_resistance; }
    int get_speed() const { return speed; }
    int get_luck() const { return luck; }

    std::string get_weapon() const { return weapon; }
    std::string get_gun() const { return gun; }
    std::string get_head() const { return head; }
    std::string get_helmet() const { return helmet; }
    std::string get_gloves() const { return gloves; }
    std::string get_legs() const { return legs; }

    void set_name(const std::string& new_name) { name = new_name; }
    void set_status(const std::string& new_status) { status = new_status; }
    void set_attack(int val) { attack = val; }
    void set_defense(int val) { defense = val; }
    void set_magic_attack(int val) { magic_attack = val; }
    void set_magic_resistance(int val) { magic_resistance = val; }
    void set_speed(int val) { speed = val; }
    void set_luck(int val) { luck = val; }

    void set_weapon(const std::string& item) { weapon = item; }
    void set_gun(const std::string& item) { gun = item; }
    void set_head(const std::string& item) { head = item; }
    void set_helmet(const std::string& item) { helmet = item; }
    void set_gloves(const std::string& item) { gloves = item; }
    void set_legs(const std::string& item) { legs = item; }


    bool is_alive() const {
        return hp > 0;
    }

    void take_damage(int dmg) {
        hp = std::max(0, hp - dmg);
    }

    void heal(int amount) {
        hp = std::min(max_hp, hp + amount);
    }

    bool use_mp(int amount) {
        if (mp < amount) return false;
        mp -= amount;
        return true;
    }

    void restore_mp(int amount) {
        mp = std::min(max_mp, mp + amount);
    }

    void gain_exp(int amount) {
        exp += amount;
        while (exp >= exp_to_next_level) {
            exp -= exp_to_next_level;
            level_up();
        }
    }

    void level_up() {
        level++;
        exp_to_next_level = static_cast<int>(exp_to_next_level * 1.5f);
        max_hp += 10;
        max_mp += 5;
        hp = max_hp;
        mp = max_mp;
        attack += 2;
        defense += 2;
        magic_attack += 2;
        magic_resistance += 2;
        speed += 1;
        luck += 1;
    }
};

inline std::vector<Character> create_random_party() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string names[4] = {"Kazuya", "Aleph", "Hiroko", "Beth"};
    std::string weapons[4] = {"Survival Knife", "Machete", "Katana", "Stun Rod"};
    std::string guns[4] = {"Beretta 92F", "Glock 17", "MP5", "Shotgun"};
    std::string helmets[4] = {"Visor", "Tactical Helm", "Headband", "Gas Mask"};
    std::string gloves[4] = {"Leather Gloves", "Gauntlets", "Cyber Grip", "Knuckles"};
    std::string legs[4] = {"Combat Boots", "Greaves", "Sneakers", "Metal Boots"};

    std::vector<Character> party;

    for (int i = 0; i < 4; i++) {
        Character c(names[i], 1);

        c.set_attack(8 + std::rand() % 8);
        c.set_defense(8 + std::rand() % 8);
        c.set_magic_attack(8 + std::rand() % 8);
        c.set_magic_resistance(8 + std::rand() % 8);
        c.set_speed(8 + std::rand() % 8);
        c.set_luck(8 + std::rand() % 8);

        c.set_weapon(weapons[std::rand() % 4]);
        c.set_gun(guns[std::rand() % 4]);
        c.set_helmet(helmets[std::rand() % 4]);
        c.set_gloves(gloves[std::rand() % 4]);
        c.set_legs(legs[std::rand() % 4]);

        party.push_back(c);
    }

    return party;
}
