```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 1. Простая фабрика
class Animal {
public:
    virtual void makeSound() = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void makeSound() override { std::cout << "Woof!" << std::endl; }
};

class Cat : public Animal {
public:
    void makeSound() override { std::cout << "Meow!" << std::endl; }
};

class Bird : public Animal {
public:
    void makeSound() override { std::cout << "Tweet!" << std::endl; }
};

class AnimalFactory {
public:
    static Animal* create(int type) {
        switch (type) {
            case 1: return new Dog();
            case 2: return new Cat();
            case 3: return new Bird();
            default: return nullptr;
        }
    }
};

// 4. Ошибка без фабрики
Animal* createAnimalWithoutFactory(int type) {
    if (type == 1) return new Dog();
    else if (type == 2) return new Cat();
    else return nullptr;
}

// 6. Транспорт
class Transport {
public:
    virtual void move() = 0;
    virtual ~Transport() = default;
};

class Car : public Transport {
public:
    void move() override { std::cout << "Car drives" << std::endl; }
};

class Bike : public Transport {
public:
    void move() override { std::cout << "Bike rides" << std::endl; }
};

class TransportFactory {
public:
    static Transport* create(const std::string& type) {
        if (type == "car") return new Car();
        else if (type == "bike") return new Bike();
        else return nullptr;
    }
};

// 7. Оплата
class Payment {
public:
    virtual void pay(double amount) = 0;
    virtual ~Payment() = default;
};

class Card : public Payment {
public:
    void pay(double amount) override {
        std::cout << "Paid " << amount << " by card" << std::endl;
    }
};

class Cash : public Payment {
public:
    void pay(double amount) override {
        std::cout << "Paid " << amount << " in cash" << std::endl;
    }
};

class PaymentFactory {
public:
    static Payment* create(const std::string& type) {
        if (type == "card") return new Card();
        else if (type == "cash") return new Cash();
        else return nullptr;
    }
};

// 8. Документы
class Document {
public:
    virtual void open() = 0;
    virtual ~Document() = default;
};

class PDFDocument : public Document {
public:
    void open() override { std::cout << "Opening PDF document" << std::endl; }
};

class DOCDocument : public Document {
public:
    void open() override { std::cout << "Opening DOC document" << std::endl; }
};

class DocumentFactory {
public:
    static Document* create(const std::string& type) {
        if (type == "pdf") return new PDFDocument();
        else if (type == "doc") return new DOCDocument();
        else return nullptr;
    }
};

// 9. Усложнение логики
class A {
public:
    void doSomething() { std::cout << "Class A" << std::endl; }
};

class B {
public:
    void doSomething() { std::cout << "Class B" << std::endl; }
};

class RangeFactory {
public:
    static void* create(int value) {
        if (value < 10) return new A();
        else if (value == 10) return new B();
        else return nullptr;
    }
};

// 10. Несколько параметров
class LevelObject {
public:
    LevelObject(int level) : level_(level) {}
    void showLevel() { std::cout << "Level: " << level_ << std::endl; }
private:
    int level_;
};

class MultiParamFactory {
public:
    static LevelObject* create(int type, int level) {
        return new LevelObject(level);
    }
};

// 11–14. Абстрактная фабрика
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

class Creator {
public:
    virtual Product* create() = 0;
    virtual ~Creator() = default;
};

class DogProduct : public Product {
public:
    void use() override { std::cout << "Dog product used" << std::endl; }
};

class CatProduct : public Product {
public:
    void use() override { std::cout << "Cat product used" << std::endl; }
};

class DogFactory : public Creator {
public:
    Product* create() override { return new DogProduct(); }
};

class CatFactory : public Creator {
public:
    Product* create() override { return new CatProduct(); }
};

// 16. Враги в игре
class Enemy {
public:
    virtual void attack() = 0;
    virtual ~Enemy() = default;
};

class Zombie : public Enemy {
public:
    void attack() override { std::cout << "Zombie attacks!" << std::endl; }
};

class Vampire : public Enemy {
public:
    void attack() override { std::cout << "Vampire attacks!" << std::endl; }
};

class EnemyFactory {
public:
    static Enemy* create(const std::string& type) {
        if (type == "zombie") return new Zombie();
        else if (type == "vampire") return new Vampire();
        else return nullptr;
    }
};

// 17. UI элементы
class UIElement {
public:
    virtual void render() = 0;
    virtual ~UIElement() = default;
};

class Button : public UIElement {
public:
    void render() override { std::cout << "Button rendered" << std::endl; }
};

class TextBox : public UIElement {
public:
    void render() override { std::cout << "TextBox rendered" << std::endl; }
};

class UIFactory {
public:
    static UIElement* create(const std::string& type) {
        if (type == "button") return new Button();
        else if (type == "textbox") return new TextBox();
        else return nullptr;
    }
};

// 18. Сообщения
class Message {
public:
    virtual void send() = 0;
    virtual ~Message() = default;
};

class Email : public Message {
public:
    void send() override { std::cout << "Email sent" << std::endl; }
};

class SMS : public Message {
public:
    void send() override { std::cout << "SMS sent" << std::endl; }
};

class MessageFactory {
public:
    static Message* create(const std::string& type) {
        if (type == "email") return new Email();
        else if (type == "sms") return new SMS();
        else return nullptr;
    }
};

// 19. Работа с STL
class Container {
public:
    virtual void add(int value) = 0;
    virtual ~Container() = default;
};

class VectorContainer : public Container {
private:
    std::vector<int> data;
public:
    void add(int value) override { data.push_back(value); }
};

class ListContainer : public Container {
private:
    std::list<int> data;
public:
    void add(int value) override { data.push_back(value); }
};

class ContainerFactory {
public:
    static Container* create(const std::string& type) {
        if (type == "vector") return new VectorContainer();
        else if (type == "list") return new ListContainer();
        else return nullptr;
    }
};

// 20. Современный C++
class ModernAnimal {
public:
    virtual void speak() = 0;
    virtual ~ModernAnimal() = default;
};

class ModernDog : public ModernAnimal {
public:
    void speak() override { std::cout << "Modern Woof!" << std::endl; }
};
