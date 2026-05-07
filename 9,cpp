#include <iostream>
#include <memory>
#include <stdexcept>

// 1. Минимальный Facade
class CPU {
public:
    void start() { std::cout << "CPU started\n"; }
    void shutdown() { std::cout << "CPU shutdown\n"; }
};

class Memory {
public:
    void load() { std::cout << "Memory loaded\n"; }
    void clear() { std::cout << "Memory cleared\n"; }
};

class Disk {
public:
    void read() { std::cout << "Disk reading\n"; }
    void write() { std::cout << "Disk writing\n"; }
};

class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    Disk disk;
public:
    // 2. Упрощение вызова
    void start() {
        std::cout << "Starting computer...\n";
        cpu.start();
        memory.load();
        disk.read();
    }

    // 5. Расширение Facade
    void shutdown() {
        std::cout << "Shutting down computer...\n";
        disk.write();
        memory.clear();
        cpu.shutdown();
    }
};

// 3. Без Facade vs с Facade
void withoutFacade() {
    std::cout << "=== Without Facade ===\n";
    CPU cpu;
    Memory memory;
    Disk disk;

    cpu.start();
    memory.load();
    disk.read();
}

void withFacade() {
    std::cout << "\n=== With Facade ===\n";
    ComputerFacade computer;
    computer.start();
}

// 4. Повторяющийся код
void repeatedCode() {
    std::cout << "\n=== Repeated code ===\n";

    // Без фасада — дублирование
    {
        CPU cpu1; Memory mem1; Disk disk1;
        cpu1.start(); mem1.load(); disk1.read(); // первый вызов
        cpu1.start(); mem1.load(); disk1.read(); // второй вызов — дубликат
    }

    // С фасадом — нет дублирования
    {
        ComputerFacade computer;
        computer.start(); // первый вызов
        computer.start(); // второй вызов
    }
}
// 6. Компьютер (уже реализован выше)

// 7. Игровая система
class Graphics {
public:
    void init() { std::cout << "Graphics initialized\n"; }
    void render() { std::cout << "Rendering graphics\n"; }
};

class Sound {
public:
    void init() { std::cout << "Sound initialized\n"; }
    void play() { std::cout << "Playing sound\n"; }
};

class Physics {
public:
    void init() { std::cout << "Physics initialized\n"; }
    void simulate() { std::cout << "Simulating physics\n"; }
};

class GameFacade {
private:
    Graphics graphics;
    Sound sound;
    Physics physics;
public:
    void startGame() {
        std::cout << "Starting game...\n";
        graphics.init();
        sound.init();
        physics.init();
    }
    void runGame() {
        graphics.render();
        sound.play();
        physics.simulate();
    }
};

// 8. Пользовательский сервис
class Validator {
public:
    bool validate(const std::string& user) {
        std::cout << "Validating user: " << user << "\n";
        return true; // упрощённо
    }
};

class Database {
public:
    void save(const std::string& user) {
        std::cout << "Saving user: " << user << " to database\n";
    }
};

class EmailService {
public:
    void sendWelcome(const std::string& user) {
        std::cout << "Sending welcome email to: " << user << "\n";
    }
};

class UserService {
private:
    Validator validator;
    Database db;
    EmailService email;
public:
    void registerUser(const std::string& user) {
        if (validator.validate(user)) {
            db.save(user);
            email.sendWelcome(user);
        }
    }
};

// 9. Домашний кинотеатр
class TV {
public:
    void on() { std::cout << "TV turned on\n"; }
    void off() { std::cout << "TV turned off\n"; }
};

class AudioSystem {
public:
    void on() { std::cout << "Audio system on\n"; }
    void setVolume(int v) { std::cout << "Volume set to " << v << "\n"; }
};

class DVD {
public:
    void insert() { std::cout << "DVD inserted\n"; }
    void play() { std::cout << "DVD playing\n"; }
};

class HomeTheaterFacade {
private:
    TV tv;
    AudioSystem audio;
    DVD dvd;
public:
    void watchMovie() {
        std::cout << "Preparing for movie...\n";
        tv.on();
        audio.on();
        audio.setVolume(5);
        dvd.insert();
        dvd.play();
    }
    void endMovie() {
        std::cout << "Ending movie...\n";
        dvd.play(); // стоп
        audio.off();
        tv.off();
    }
};

// 10. Логирование
class LoggingFacade : public ComputerFacade {
public:
    void start() override {
        std::cout << "[LOG] Starting computer at " << __TIME__ << "\n";
        ComputerFacade::start();
        std::cout << "[LOG] Computer started successfully\n";
    }
    void shutdown() override {
        std::cout << "[LOG] Shutting down computer at " << __TIME__ << "\n";
        ComputerFacade::shutdown();
        std::cout << "[LOG] Computer shutdown completed\n";
    }
};
// 11. Параметры
class UserFacade {
private:
    UserService userService;
public:
    void createUser(const std::string& name, const std::string& email) {
        std::cout << "Creating user: " << name << " (" << email << ")\n";
        userService.registerUser(name);
    }
};

// 12. Частичный доступ
class AdvancedComputerFacade : public ComputerFacade {
public:
    void init() {
        std::cout << "Initializing components...\n";
        // только часть операций
    }
    void fullStart() {
        start(); // полный старт
    }
};

// 13. Скрытие сложности
class SmartFacade {
private:
    int internalState = 0;
public:
    void doSomething() {
        // Сложная внутренняя логика скрыта от клиента
        internalState++;
        if (internalState % 2 == 0) {
            std::cout << "Even state: doing A\n";
        } else {
            std::cout << "Odd state: doing B\n";
        }
    }
};

// 14. Обработка ошибок
class SafeFacade : public ComputerFacade {
public:
    void safeStart() {
        try {
            start();
            std::cout << "System started safely\n";
        } catch (...) {
            std::cout << "Error during startup!\n";
            shutdown(); // аварийное отключение
        }
    }
};

// 15. Несколько Facade
class BasicFacade : public ComputerFacade {
public:
    void quickStart() {
        cpu.start(); // только CPU
    }
};

class FullFacade : public ComputerFacade {
public:
    void completeStart() {
        start(); // полный старт
    }
};
