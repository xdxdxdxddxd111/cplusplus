#include <iostream>
#include <memory>
#include <stack>
#include <queue>
#include <unordered_map>
#include <string>

// 1. Минимальная команда
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class HelloCommand : public Command {
public:
    void execute() override {
        std::cout << "Hello, World!\n";
    }
};

// 2. Команда и исполнитель
class Light {
public:
    void turnOn() {
        std::cout << "Light is ON\n";
    }
    void turnOff() {
        std::cout << "Light is OFF\n";
    }
};

class TurnOnCommand : public Command {
private:
    Light& light;
public:
    TurnOnCommand(Light& l) : light(l) {}
    void execute() override {
        light.turnOn();
    }
};

class TurnOffCommand : public Command {
private:
    Light& light;
public:
    TurnOffCommand(Light& l) : light(l) {}
    void execute() override {
        light.turnOff();
    }
};

// 3. Invoker
class Button {
private:
    std::unique_ptr<Command> command;
public:
    void setCommand(std::unique_ptr<Command> cmd) {
        command = std::move(cmd);
    }
    void press() {
        if (command) {
            command->execute();
        }
    }
};
// 6. Игровое управление
class Player {
private:
    int x = 0, y = 0;
public:
    void moveUp() { y++; std::cout << "Player moved up to (" << x << ", " << y << ")\n"; }
    void moveDown() { y--; std::cout << "Player moved down to (" << x << ", " << y << ")\n"; }
    void moveLeft() { x--; std::cout << "Player moved left to (" << x << ", " << y << ")\n"; }
    void moveRight() { x++; std::cout << "Player moved right to (" << x << ", " << y << ")\n"; }
};

class MoveUpCommand : public Command {
private:
    Player& player;
public:
    MoveUpCommand(Player& p) : player(p) {}
    void execute() override { player.moveUp(); }
};

class MoveDownCommand : public Command {
private:
    Player& player;
public:
    MoveDownCommand(Player& p) : player(p) {}
    void execute() override { player.moveDown(); }
};

class MoveLeftCommand : public Command {
private:
    Player& player;
public:
    MoveLeftCommand(Player& p) : player(p) {}
    void execute() override { player.moveLeft(); }
};

class MoveRightCommand : public Command {
private:
    Player& player;
public:
    MoveRightCommand(Player& p) : player(p) {}
    void execute() override { player.moveRight(); }
};

// 7. Действия героя
class Hero {
public:
    void attack() { std::cout << "Hero attacks!\n"; }
    void heal() { std::cout << "Hero heals!\n"; }
    void defend() { std::cout << "Hero defends!\n"; }
};

class AttackCommand : public Command {
private:
    Hero& hero;
public:
    AttackCommand(Hero& h) : hero(h) {}
    void execute() override { hero.attack(); }
};

class HealCommand : public Command {
private:
    Hero& hero;
public:
    HealCommand(Hero& h) : hero(h) {}
    void execute() override { hero.heal(); }
};

class DefendCommand : public Command {
private:
    Hero& hero;
public:
    DefendCommand(Hero& h) : hero(h) {}
    void execute() override { hero.defend(); }
};

// 8. Умный дом
class SmartHome {
public:
    void turnOnLight() { std::cout << "Smart light is ON\n"; }
    void turnOffLight() { std::cout << "Smart light is OFF\n"; }
    void turnOnAC() { std::cout << "AC is ON\n"; }
    void openDoor() { std::cout << "Door is OPEN\n"; }
};

class SmartTurnOnLightCommand : public Command {
private:
    SmartHome& home;
public:
    SmartTurnOnLightCommand(SmartHome& h) : home(h) {}
    void execute() override { home.turnOnLight(); }
};

class SmartTurnOffLightCommand : public Command {
private:
    SmartHome& home;
public:
    SmartTurnOffLightCommand(SmartHome& h) : home(h) {}
    void execute() override { home.turnOffLight(); }
};

class SmartTurnOnACCommand : public Command {
private:
    SmartHome& home;
public:
    SmartTurnOnACCommand(SmartHome& h) : home(h) {}
    void execute() override { home.turnOnAC(); }
};

class OpenDoorCommand : public Command {
private:
    SmartHome& home;
public:
    OpenDoorCommand(SmartHome& h) : home(h) {}
    void execute() override { home.openDoor(); }
};

// 9. Файловые операции
class FileSystem {
public:
    void createFile(const std::string& name) {
        std::cout << "File '" << name << "' created\n";
    }
    void deleteFile(const std::string& name) {
        std::cout << "File '" << name << "' deleted\n";
    }
    void renameFile(const std::string& oldName, const std::string& newName) {
        std::cout << "File '" << oldName << "' renamed to '" << newName << "'\n";
    }
};

class CreateFileCommand : public Command {
private:
    FileSystem& fs;
    std::string filename;
public:
    CreateFileCommand(FileSystem& f, const std::string& name)
        : fs(f), filename(name) {}
    void execute() override { fs.createFile(filename); }
};

class DeleteFileCommand : public Command {
private:
    FileSystem& fs;
    std::string filename;
public:
    DeleteFileCommand(FileSystem& f, const std::string& name)
        : fs(f), filename(name) {}
    void execute() override { fs.deleteFile(filename); }
};

class RenameFileCommand : public Command {
private:
    FileSystem& fs;
    std::string oldName, newName;
public:
    RenameFileCommand(FileSystem& f, const std::string& old, const std::string& n)
        : fs(f), oldName(old), newName(n) {}
    void execute() override { fs.renameFile(oldName, newName); }
};

// 10. Очередь задач
void executeQueue(std::queue<std::unique_ptr<Command>>& queue) {
    while (!queue.empty()) {
        queue.front()->execute();
        queue.pop();
    }
}
// 11. Команда с отменой
class UndoableCommand : public Command {
public:
    virtual void undo() = 0;
};

class MoveRightUndoableCommand : public UndoableCommand {
private:
    Player& player;
    int prevX;
public:
    MoveRightUndoableCommand(Player& p) : player(p), prevX(0) {}
    
    void execute() override {
        prevX = player.getX();
        player.moveRight();
    }
    
    void undo() override {
        // Здесь нужно добавить метод getX() в класс Player
        std::cout << "Undo: move right\n";
        // Логика возврата позиции
    }
};

// Для работы undo нужно расширить класс Player
class PlayerWithUndo {
private:
    int x = 0, y = 0;
public:
    int getX() const { return x; }
    int getY() const { return y
