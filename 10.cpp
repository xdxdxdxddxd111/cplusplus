#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <string>

// 1. Клонирование врага
class Enemy {
private:
    int hp;
    int damage;
    float speed;
public:
    Enemy(int h, int d, float s) : hp(h), damage(d), speed(s) {}

public:
    Enemy* clone() const {
        return new Enemy(hp, damage, speed);
    }

    void print() const {
        std::cout << "Enemy: HP=" << hp << ", Damage=" << damage << ", Speed=" << speed << "\n";
    }

    // Сеттеры для изменения полей
    void setHP(int newHP) { hp = newHP; }
    int getHP() const { return hp; }
};

// 2. Независимые копии
void demoIndependentCopies() {
    std::cout << "=== 2. Независимые копии ===\n";
    Enemy original(100, 20, 5.0f);
    std::cout << "Original: ";
    original.print();

    Enemy* copy1 = original.clone();
    copy1->setHP(50);

    std::cout << "Original after copy modification: ";
    original.print();
    std::cout << "Copy: ";
    copy1->print();

    delete copy1;
}

// 3. Prototype без интерфейса
// В данном случае подход с методом clone() в классе Enemy уже является реализацией
// Prototype без отдельного интерфейса — сравниваем с классическим подходом ниже

// Классический подход с интерфейсом Prototype
class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual ~Prototype() = default;
};

class EnemyWithInterface : public Prototype {
private:
    int hp;
    int damage;
    float speed;
public:
    EnemyWithInterface(int h, int d, float s) : hp(h), damage(d), speed(s) {}

    Prototype* clone() const override {
        return new EnemyWithInterface(hp, damage, speed);
    }

    void print() const {
        std::cout << "EnemyWithInterface: HP=" << hp << ", Damage=" << damage << ", Speed=" << speed << "\n";
    }
};

// 4. Шаблон оружия
class Weapon {
private:
    std::string name;
    int damage;
    double price;
public:
    Weapon(const std::string& n, int d, double p) : name(n), damage(d), price(p) {}

    Weapon* clone() const {
        return new Weapon(name, damage, price);
    }

    void setDamage(int d) { damage = d; }
    void setPrice(double p) { price = p; }
    void setName(const std::string& n) { name = n; }

    void print() const {
        std::cout << "Weapon: " << name << ", Damage=" << damage << ", Price=" << price << "\n";
    }
};

void demoWeaponCloning() {
    std::cout << "\n=== 4. Клонирование оружия ===\n";
    Weapon legendarySword("Legendary Sword", 100, 1000.0);

    for (int i = 0; i < 5; ++i) {
        Weapon* copy = legendarySword.clone();
        copy->setDamage(100 + i * 10);
        copy->setPrice(1000.0 + i * 50.0);
        copy->setName("Cloned Sword " + std::to_string(i + 1));
        copy->print();
        delete copy;
    }
}

// 5. Копирование NPC
class NPC {
private:
    std::string name;
    int level;
    std::string faction;
public:
    NPC(const std::string& n, int l, const std::string& f) : name(n), level(l), faction(f) {}

    NPC* clone() const {
        return new NPC(name, level, faction);
    }

    void print() const {
        std::cout << "NPC: " << name << ", Level=" << level << ", Faction=" << faction << "\n";
    }
};

void demoNPCCloning() {
    std::cout << "\n=== 5. Армия клонов NPC ===\n";
    NPC original("Guard", 5, "City Watch");

    std::vector<NPC*> army;
    for (int i = 0; i < 3; ++i) {
        army.push_back(original.clone());
    }

    for (size_t i = 0; i < army.size(); ++i) {
        army[i]->print();
    }

    // Очистка памяти
    for (auto* npc : army) {
        delete npc;
    }
}
// 6. Ошибка shallow copy
class ShallowCopyExample {
private:
    int* data;
public:
    ShallowCopyExample(int value) {
        data = new int(value);
    }

    ShallowCopyExample* clone() const {
        // ОШИБКА: просто копируем указатель
        return new ShallowCopyExample(*data);
    }

    ~ShallowCopyExample() {
        delete data;
    }

    void print() const {
        std::cout << "Data: " << *data << " at " << data << "\n";
    }
};

// 7. Исправление через deep copy
class DeepCopyExample {
private:
    int* data;
public:
    DeepCopyExample(int value) {
        data = new int(value);
    }

    DeepCopyExample(const DeepCopyExample& other) {
        data = new int(*other.data); // Глубокое копирование
    }

    DeepCopyExample* clone() const {
        return new DeepCopyExample(*this);
    }

    ~DeepCopyExample() {
        delete data;
    }

    void print() const {
        std::cout << "Deep Data: " << *data << " at " << data << "\n";
    }
};

void demoDeepCopy() {
    std::cout << "\n=== 7. Глубокое копирование ===\n";
    DeepCopyExample original(42);
    DeepCopyExample* copy = original.clone();

    original.print();
    copy->print();

    delete copy;
}

// 8. Инвентарь персонажа
class Character {
private:
    std::string name;
    std::vector<std::string> inventory;
public:
    Character(const std::string& n) : name(n) {}

    void addItem(const std::string& item) {
        inventory.push_back(item);
    }

    Character* clone() const {
        Character* newChar = new Character(name);
        newChar->inventory = inventory; // Вектор автоматически копируется глубоко
        return newChar;
    }

    void print() const {
        std::cout << "Character: " << name << ", Inventory: ";
        for (const auto& item : inventory) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
};

void demoInventoryCopy() {
    std::cout << "\n=== 8. Копирование инвентаря ===\n";
    Character player("Hero");
    player.addItem("Sword");
    player.addItem("Potion");

    Character* clone = player.clone();
    clone->addItem("Shield");

    player.print();
    clone->print();

    delete clone;
}

// 9. Сложный объект
class WeaponItem {
private:
    std::string name;
public:
    WeaponItem(const std::string& n) : name(n) {}
    WeaponItem* clone() const {
        return new WeaponItem(name);
    }
    void print() const { std::cout << name; }
};

class Player {
private:
    std::string name;
    int hp;
    std::vector<std::string> inventory;
    WeaponItem* weapon;
public:
    Player(const std::string& n, int h,
