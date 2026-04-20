#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <memory>

// Интерфейс наблюдателя
class Observer {
public:
    virtual void update(int data) = 0;
    virtual ~Observer() = default;
};

// Субъект с управлением подписками
class Subject {
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        // Запрет дублирования подписок
        if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }

    void detach(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void clearObservers() {
        observers.clear();
    }

    void notify(int data) {
        for (auto* observer : observers) {
            observer->update(data);
        }
    }
};

// Простой наблюдатель
class SimpleObserver : public Observer {
private:
    std::string name;

public:
    SimpleObserver(const std::string& n) : name(n) {}

    void update(int data) override {
        std::cout << name << " получил данные: " << data << "\n";
    }
};

// Класс данных с автоматическим уведомлением
class Data {
private:
    int value;
    Subject subject;

public:
    Data(int initialValue = 0) : value(initialValue) {}

    void setValue(int newValue) {
        if (value != newValue) {
            value = newValue;
            subject.notify(value); // Уведомление при изменении
        }
    }

    int getValue() const { return value; }

    void attachObserver(Observer* observer) {
        subject.attach(observer);
    }

    void detachObserver(Observer* observer) {
        subject.detach(observer);
    }
};

// Цепочный наблюдатель (несколько действий)
class ChainObserver : public Observer {
private:
    std::string name;

public:
    ChainObserver(const std::string& n) : name(n) {}

    void update(int data) override {
        std::cout << "=== " << name << " обрабатывает данные: " << data << " ===\n";
        action1();
        action2();
        action3();
    }

private:
    void action1() { std::cout << name << ": действие 1 - подготовка\n"; }
    void action2() { std::cout << name << ": действие 2 - обработка\n"; }
    void action3() { std::cout << name << ": действие 3 - завершение\n"; }
};

// Кнопка с обработчиками
class Button {
private:
    Subject subject;
    std::string label;

public:
    Button(const std::string& text) : label(text) {}

    void click() {
        std::cout << "Кнопка '" << label << "' нажата!\n";
        subject.notify(0);
    }

    void subscribe(Observer* handler) {
        subject.attach(handler);
    }
};

class SaveHandler : public Observer {
public:
    void update(int) override { std::cout << "[ОБРАБОТЧИК] Сохранение данных...\n"; }
};

class PrintHandler : public Observer {
public:
    void update(int) override { std::cout << "[ОБРАБОТЧИК] Печать документа...\n"; }
};

class LogHandler : public Observer {
public:
    void update(int) override { std::cout << "[ОБРАБОТЧИК] Запись в лог...\n"; }
};

// Система логирования
class ConsoleLogger : public Observer {
public:
    void update(int data) override {
        std::cout << "[CONSOLE] Событие: " << data << " - записано в консоль\n";
    }
};

class FileLogger : public Observer {
public:
    void update(int data) override {
        std::cout << "[FILE] Событие: " << data << " - имитация записи в файл\n";
    }
};

// Датчик температуры
class TemperatureSensor {
private:
    double temperature;
    Subject subject;

public:
    TemperatureSensor(double temp = 20.0) : temperature(temp) {}

    void setTemperature(double newTemp) {
        temperature = newTemp;
        subject.notify(static_cast<int>(temperature));
    }

    void attachDisplay(Observer* display) { subject.attach(display); }
    void attachWarningSystem(Observer* warning) { subject.attach(warning); }
};

class Display : public Observer {
public:
    void update(int temp) override {
        std::cout << "[ДИСПЛЕЙ] Температура = " << temp << "°C\n";
    }
};

class WarningSystem : public Observer {
public:
    void update(int temp) override {
        if (temp > 80) {
            std::cout << "[СИСТЕМА ПРЕДУПРЕЖДЕНИЯ] ОПАСНОСТЬ: Температура " << temp << "°C!\n";
        } else if (temp < 0) {
            std::cout << "[СИСТЕМА ПРЕДУПРЕЖДЕНИЯ] ОПАСНОСТЬ: Температура " << temp << "°C! (заморозка)\n";
        }
    }
};

// Чат-комната
class ChatRoom : public Subject {
private:
    std::string roomName;

public:
    ChatRoom(const std::string& name) : roomName(name) {}

    void sendMessage(const std::string& message, const std::string& sender) {
        std::cout << "[" << roomName << "] " << sender << ": " << message << "\n";
        notify(0); // Можно расширить для передачи сообщения
    }
};

class User : public Observer {
private:
    std::string username;

public:
    User(const std::string& name) : username(name) {}

    void update(int) override {
        std::cout << username << ": Получено новое сообщение!\n";
    }
};

// Игровая система событий
class GameEventManager : public Subject {};

class HealthSystem : public Observer {
private:
    int hp = 100;

public:
    void update(int damage) override {
        hp -= damage;
        std::cout << "[ЗДОРОВЬЕ] HP уменьшен до: " << hp << "\n";
    }
};

class SoundSystem : public Observer {
public:
    void update(int) override {
        std::cout << "[ЗВУК] Звук урона воспроизведён!\n";
    }
};

class EffectSystem : public Observer {
public:
    void update(int) override {
        std::cout << "[ЭФФЕКТ] Визуальный эффект урона показан!\n";
    }
};

// EventManager с подписками по имени события
class EventManager {
private:
    std::unordered_map<std::string, std::vector<std::function<void(int)>>> eventHandlers;

public:
    void subscribe(const std::string& eventName, std::function<void(int)> handler) {
        eventHandlers[eventName].push_back(handler);
    }

    void emit(const std::string& eventName, int data = 0) {
        auto it = eventHandlers.find(eventName);
        if (it != eventHandlers.end()) {
            for (const auto& handler : it->second) {
                handler(data);
            }
        }
    }
};

// Фабрика наблюдателей
class ObserverFactory {
public:
    static std::unique_ptr<Observer> createObserver(const std::string& type) {
        if (type == "console") return std::make_unique<ConsoleLogger>();
        if (type == "file") return std::make_unique<FileLogger>();
        if (type == "health") return std::make_unique<HealthSystem>();
        return nullptr;
    }
};

// === ГЛАВНАЯ ФУНКЦИЯ ДЛЯ ТЕСТИРОВАНИЯ ===
