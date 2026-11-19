#pragma once
#include <string>
#include <vector>

enum class ItemType {
    HEALING, DAMAGING, REVIVE, BUFF, CURE_STATUS, PUT_STATUS, EQUIP, KEY
};

enum class EquipType {
    NONE, WEAPON, GUN, BULLET, HELMET, BODY, GLOVES, LEGS
};

enum class TargetNumber {
    SINGLE, ALL
};

enum class TargetType {
    PLAYER, ENEMY
};

enum class StatusEffect {
    NONE, POISON, PARALYSIS, SLEEP, CHARM, MUTE
};

struct Item {
    int id = 0;
    std::string name = "";
    std::string desc = "";

    ItemType type = ItemType::HEALING;
    EquipType equip_type = EquipType::NONE;
    TargetNumber target_number = TargetNumber::SINGLE;
    TargetType target_type = TargetType::PLAYER;
    StatusEffect status = StatusEffect::NONE;

    int amount = 0;
    bool activable_in_battle = false;
    bool activable_outside_battle = false;

    int buy_cost = 0;
    int sell_cost = 0;

    int attack_boost = 0;
    int defense_boost = 0;
    int magic_attack_boost = 0;
    int magic_resistance_boost = 0;
    int speed_boost = 0;
    int luck_boost = 0;
};

inline std::vector<Item> item_db = {
    {
        .id = 1, .name = "Medicine", .desc = "Restores 50 HP to one ally.",
        .type = ItemType::HEALING, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .amount = 50, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 50, .sell_cost = 25
    },
    {
        .id = 2, .name = "Life Stone", .desc = "Restores 100 HP to one ally.",
        .type = ItemType::HEALING, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .amount = 100, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 150, .sell_cost = 75
    },
    {
        .id = 3, .name = "Bead", .desc = "Fully restores HP to one ally.",
        .type = ItemType::HEALING, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .amount = 9999, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 600, .sell_cost = 300
    },
    {
        .id = 4, .name = "Bead Chain", .desc = "Fully restores HP to the whole party.",
        .type = ItemType::HEALING, .target_number = TargetNumber::ALL, .target_type = TargetType::PLAYER,
        .amount = 9999, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 1500, .sell_cost = 750
    },
    {
        .id = 10, .name = "Balm of Rising", .desc = "Revives a fallen ally with 50% HP.",
        .type = ItemType::REVIVE, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .amount = 50, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 400, .sell_cost = 200
    },
    {
        .id = 15, .name = "Dis-Poison", .desc = "Cures Poison on one ally.",
        .type = ItemType::CURE_STATUS, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .status = StatusEffect::POISON, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 60, .sell_cost = 30
    },
    {
        .id = 16, .name = "Dis-Paralyze", .desc = "Cures Paralysis on one ally.",
        .type = ItemType::CURE_STATUS, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .status = StatusEffect::PARALYSIS, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 80, .sell_cost = 40
    },
    {
        .id = 17, .name = "Dis-Charm", .desc = "Cures Charm on one ally.",
        .type = ItemType::CURE_STATUS, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .status = StatusEffect::CHARM, .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 80, .sell_cost = 40
    },
    {
        .id = 18, .name = "Dis-Mute", .desc = "Cures Mute on one ally.",
        .type = ItemType::CURE_STATUS, .target_number = TargetNumber::SINGLE, .target_type = TargetType::PLAYER,
        .status = StatusEffect::MUTE, .activable_in_battle = true, .activable_outside_battle = true,
        .buy_cost = 70, .sell_cost = 35
    },
    {
        .id = 25, .name = "Fire Shard", .desc = "Deals 45 fire damage to one enemy.",
        .type = ItemType::DAMAGING, .target_number = TargetNumber::SINGLE, .target_type = TargetType::ENEMY,
        .amount = 45, .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 120, .sell_cost = 60
    },
    {
        .id = 26, .name = "Ice Shard", .desc = "Deals 45 ice damage to one enemy.",
        .type = ItemType::DAMAGING, .target_number = TargetNumber::SINGLE, .target_type = TargetType::ENEMY,
        .amount = 45, .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 120, .sell_cost = 60
    },
    {
        .id = 27, .name = "Shock Grenade", .desc = "Deals 30 damage to all enemies.",
        .type = ItemType::DAMAGING, .target_number = TargetNumber::ALL, .target_type = TargetType::ENEMY,
        .amount = 30, .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 220, .sell_cost = 110
    },
    {
        .id = 28, .name = "Poison Dart", .desc = "Inflicts Poison on one enemy.",
        .type = ItemType::PUT_STATUS, .target_number = TargetNumber::SINGLE, .target_type = TargetType::ENEMY,
        .status = StatusEffect::POISON, .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 100, .sell_cost = 50
    },
    {
        .id = 29, .name = "Sleep Gas", .desc = "Inflicts Sleep on all enemies.",
        .type = ItemType::PUT_STATUS, .target_number = TargetNumber::ALL, .target_type = TargetType::ENEMY,
        .status = StatusEffect::SLEEP, .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 180, .sell_cost = 90
    },
    {
        .id = 40, .name = "Attack Booster", .desc = "Raises party Attack in battle.",
        .type = ItemType::BUFF, .target_number = TargetNumber::ALL, .target_type = TargetType::PLAYER,
        .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 250, .sell_cost = 125, .attack_boost = 5
    },
    {
        .id = 41, .name = "Guard Booster", .desc = "Raises party Defense in battle.",
        .type = ItemType::BUFF, .target_number = TargetNumber::ALL, .target_type = TargetType::PLAYER,
        .activable_in_battle = true, .activable_outside_battle = false,
        .buy_cost = 250, .sell_cost = 125, .defense_boost = 5
    },
    {
        .id = 50, .name = "Survival Knife", .desc = "Standard military combat knife.",
        .type = ItemType::EQUIP, .equip_type = EquipType::WEAPON,
        .buy_cost = 150, .sell_cost = 75, .attack_boost = 6, .speed_boost = 1
    },
    {
        .id = 51, .name = "Machete", .desc = "Heavy blade with high cutting power.",
        .type = ItemType::EQUIP, .equip_type = EquipType::WEAPON,
        .buy_cost = 280, .sell_cost = 140, .attack_boost = 10
    },
    {
        .id = 52, .name = "Katana", .desc = "Sharp forged blade. High speed.",
        .type = ItemType::EQUIP, .equip_type = EquipType::WEAPON,
        .buy_cost = 500, .sell_cost = 250, .attack_boost = 15, .speed_boost = 3
    },
    {
        .id = 53, .name = "Stun Rod", .desc = "Electrified baton. May inflict Paralysis.",
        .type = ItemType::EQUIP, .equip_type = EquipType::WEAPON,
        .status = StatusEffect::PARALYSIS,
        .buy_cost = 420, .sell_cost = 210, .attack_boost = 9, .magic_attack_boost = 4
    },
    {
        .id = 60, .name = "Beretta 92F", .desc = "Reliable 9mm semi-automatic pistol.",
        .type = ItemType::EQUIP, .equip_type = EquipType::GUN,
        .buy_cost = 300, .sell_cost = 150, .attack_boost = 8, .luck_boost = 1
    },
    {
        .id = 61, .name = "MP5", .desc = "Submachine gun. Fast bursts.",
        .type = ItemType::EQUIP, .equip_type = EquipType::GUN,
        .buy_cost = 650, .sell_cost = 325, .attack_boost = 14, .speed_boost = 2
    },
    {
        .id = 62, .name = "Shotgun", .desc = "Devastating close-range firepower.",
        .type = ItemType::EQUIP, .equip_type = EquipType::GUN,
        .buy_cost = 800, .sell_cost = 400, .attack_boost = 20, .speed_boost = -2
    },
    {
        .id = 64, .name = "Normal Bullet", .desc = "Standard lead ammunition.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BULLET,
        .buy_cost = 40, .sell_cost = 20, .attack_boost = 2
    },
    {
        .id = 65, .name = "Poison Bullet", .desc = "Toxic rounds. May inflict Poison.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BULLET,
        .status = StatusEffect::POISON,
        .buy_cost = 120, .sell_cost = 60, .attack_boost = 3
    },
    {
        .id = 66, .name = "Nerve Bullet", .desc = "Paralyzing rounds. May inflict Paralysis.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BULLET,
        .status = StatusEffect::PARALYSIS,
        .buy_cost = 180, .sell_cost = 90, .attack_boost = 4
    },
    {
        .id = 67, .name = "Sleep Bullet", .desc = "Tranquilizer rounds. May inflict Sleep.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BULLET,
        .status = StatusEffect::SLEEP,
        .buy_cost = 150, .sell_cost = 75, .attack_boost = 3
    },
    {
        .id = 68, .name = "Charm Bullet", .desc = "Pheromone rounds. May inflict Charm.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BULLET,
        .status = StatusEffect::CHARM,
        .buy_cost = 220, .sell_cost = 110, .attack_boost = 4
    },
    {
        .id = 69, .name = "Magic Bullet", .desc = "Anti-magic rounds. May inflict Mute.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BULLET,
        .status = StatusEffect::MUTE,
        .buy_cost = 200, .sell_cost = 100, .attack_boost = 5
    },
    {
        .id = 70, .name = "Tactical Helm", .desc = "Reinforced combat helmet.",
        .type = ItemType::EQUIP, .equip_type = EquipType::HELMET,
        .buy_cost = 200, .sell_cost = 100, .defense_boost = 5
    },
    {
        .id = 71, .name = "Gas Mask", .desc = "Protects against toxic fumes.",
        .type = ItemType::EQUIP, .equip_type = EquipType::HELMET,
        .buy_cost = 240, .sell_cost = 120, .defense_boost = 3, .magic_resistance_boost = 4
    },
    {
        .id = 75, .name = "Kevlar Vest", .desc = "Bulletproof tactical body armor.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BODY,
        .buy_cost = 450, .sell_cost = 225, .defense_boost = 12
    },
    {
        .id = 76, .name = "Cyber Suit", .desc = "High-tech suit with magic shielding.",
        .type = ItemType::EQUIP, .equip_type = EquipType::BODY,
        .buy_cost = 900, .sell_cost = 450, .defense_boost = 14, .magic_resistance_boost = 10, .speed_boost = 2
    },
    {
        .id = 80, .name = "Cyber Grip", .desc = "Servo-assisted combat gloves.",
        .type = ItemType::EQUIP, .equip_type = EquipType::GLOVES,
        .buy_cost = 220, .sell_cost = 110, .attack_boost = 2, .defense_boost = 4
    },
    {
        .id = 85, .name = "Combat Boots", .desc = "Sturdy military boots.",
        .type = ItemType::EQUIP, .equip_type = EquipType::LEGS,
        .buy_cost = 180, .sell_cost = 90, .defense_boost = 4, .speed_boost = 2
    },
    {
        .id = 100, .name = "Terminal Keycard", .desc = "Unlocks restricted mall sectors.",
        .type = ItemType::KEY, .buy_cost = 0, .sell_cost = 0
    }
};

inline Item get_item_by_id(int id) {
    for (const auto& item : item_db) {
        if (item.id == id) return item;
    }
    return Item{};
}
