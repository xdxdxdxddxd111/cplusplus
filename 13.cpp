#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

class Component {
public:
    virtual ~Component() = default;
    virtual void display(int depth = 0) const = 0;
    virtual bool remove(const std::string& name) = 0;
    virtual int count() const = 0;
    virtual std::string getName() const = 0;
    virtual bool find(const std::string& name) const = 0;
};
class Leaf : public Component {
protected:
    std::string name;

public:
    Leaf(const std::string& n) : name(n) {}
    
    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "└─ " << name << std::endl;
    }
    
    bool remove(const std::string&) override { return false; } // Листы не могут удалять детей
    
    int count() const override { return 1; }
    
    std::string getName() const override { return name; }
    
    bool find(const std::string& target) const override {
        return name == target;
    }
};

class Composite : public Component {
protected:
    std::string name;
    std::vector<std::shared_ptr<Component>> children;

public:
    Composite(const std::string& n) : name(n) {}
    
    void add(std::shared_ptr<Component> child) {
        children.push_back(child);
    }
    
    void display(int depth = 0) const override {
        if (depth == 0) {
            std::cout << name << std::endl;
        } else {
            std::cout << std::string((depth - 1) * 2, ' ') << "├── " << name << std::endl;
        }
        
        for (size_t i = 0; i < children.size(); ++i) {
            children[i]->display(depth + 1);
        }
    }
    
    bool remove(const std::string& target) override {
        auto it = std::remove_if(children.begin(), children.end(),
            [&target](const std::shared_ptr<Component>& comp) {
                return comp->getName() == target;
            });
        
        if (it != children.end()) {
            children.erase(it, children.end());
            return true;
        }
        
        // Рекурсивно ищем в дочерних композитах
        for (auto& child : children) {
            if (auto composite = std::dynamic_pointer_cast<Composite>(child)) {
                if (composite->remove(target)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    int count() const override {
        int total = 1; // Сам композит
        for (const auto& child : children) {
            total += child->count();
        }
        return total;
    }
    
    std::string getName() const override { return name; }
    
    bool find(const std::string& target) const override {
        if (name == target) return true;
        
        for (const auto& child : children) {
            if (child->find(target)) {
                return true;
            }
        }
        return false;
    }
};
class File : public Leaf {
    size_t size;
public:
    File(const std::string& n, size_t s) : Leaf(n), size(s) {}
    
    size_t getSize() const { return size; }
};

class Folder : public Composite {
public:
    Folder(const std::string& n) : Composite(n) {}
    
    size_t getSize() const {
        size_t total = 0;
        for (const auto& child : children) {
            if (auto file = std::dynamic_pointer_cast<File>(child)) {
                total += file->getSize();
            } else if (auto folder = std::dynamic_pointer_cast<Folder>(child)) {
                total += folder->getSize();
            }
        }
        return total;
    }
};
class Button : public Leaf {
public:
    Button(const std::string& n) : Leaf(n) {}
};

class Label : public Leaf {
public:
    Label(const std::string& n) : Leaf(n) {}
};

class TextField : public Leaf {
public:
    TextField(const std::string& n) : Leaf(n) {}
};

class Panel : public Composite {
public:
    Panel(const std::string& n) : Composite(n) {}
};

class Window : public Composite {
public:
    Window(const std::string& n) : Composite(n) {}
};
class Player : public Leaf {
public:
    Player(const std::string& n) : Leaf(n) {}
};

class Enemy : public Leaf {
public:
    Enemy(const std::string& n) : Leaf(n) {}
};

class Item : public Leaf {
public:
    Item(const std::string& n) : Leaf(n) {}
};

class Scene : public Composite {
public:
    Scene(const std::string& n) : Composite(n) {}
};

class EnemyGroup : public Composite {
public:
    EnemyGroup(const std::string& n) : Composite(n) {}
};
class ButtonNode : public Leaf {
public:
    ButtonNode(const std::string& n) : Leaf(n) {}
};

class ImageNode : public Leaf {
public:
    ImageNode(const std::string& n) : Leaf(n) {}
};

class TextNode : public Leaf {
public:
    TextNode(const std::string& n) : Leaf(n) {}
};

class DivNode : public Composite {
public:
    DivNode(const std::string& n) : Composite(n) {}
};

class BodyNode : public Composite {
public:
    BodyNode(const std::string& n) : Composite(n) {}
};
class Employee : public Leaf {
public:
    Employee(const std::string& n) : Leaf(n) {}
};

class Department : public Composite {
public:
    Department(const std::string& n) : Composite(n) {}
};

class Company : public Composite {
public:
    Company(const std::string& n) : Composite(n) {}
};
class MenuItem : public Leaf {
public:
    MenuItem(const std::string& n) : Leaf(n) {}
};

class Menu : public Composite {
public:
    Menu(const std::string& n) : Composite(n) {}
};
void DFS(const std::shared_ptr<Component>& root, int depth = 0) {
    root->display(depth);
    if (auto composite = std::dynamic_pointer_cast<Composite>(root)) {
        for (const auto& child : composite->children) {
            DFS(child, depth + 1);
        }
    }
}

void BFS(const std::shared_ptr<Component>& root) {
    std::queue<std::pair<std::shared_ptr<Component>, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [current, depth] = q.front();
        q.pop();
        
        current->display(depth);
        
        if (auto composite = std::dynamic_pointer_cast<Composite>(current)) {
            for (const auto& child : composite->children) {
                q.push({child, depth + 1});
            }
        }
    }
}
int main() {
    // 1–5. Базовый пример Composite
    auto root = std::make_shared<Composite>("Root");
    auto leaf1 = std::make_shared<Leaf>("Leaf1");
    auto leaf2 = std::make_shared<Leaf>("Leaf2");
    auto composite = std::make_shared<Composite>("Composite");
    auto leaf3 = std::make_shared<Leaf>("Leaf3");
    auto leaf4 = std::make_shared<Leaf>("Leaf4");

    root->add(leaf1);
    root->add(leaf2);
    root->add(composite);
    composite->add(leaf3);
    composite->add(leaf4);

    std::cout << "=== Дерево объектов ===" << std::endl;
    root->display();

    std::cout << "\n=== Рекурсивный обход с отступами ===" << std::endl;
    DFS(root);

    std::cout << "\n=== Подсчёт количества объектов ===" << std::endl;
    std::cout << "Всего элементов: " << root->count() << std::endl;

    std::cout << "\n=== Удаление элемента ===" << std::endl;
    if (root->remove("Leaf2")) {
        std::cout << "Leaf2 удалён успешно" << std::endl;
    }
    root->display();

    // 6. Файловая система
    std::cout << "\n=== Файловая система ===" << std::endl;
    auto documents = std::make_shared<Folder>("Documents");
    auto photos = std::make_shared<Folder>("Photos");
    auto work = std::make_shared<Folder>("Work");
    auto file1 = std::make_shared<File>("report.docx", 1024);
    auto file2 = std::make_shared<File>("photo.jpg", 2048);
    auto file3 = std::make_shared<File>("code.cpp", 512);

    documents->add(photos);
    documents->add(work);
    photos->add(file2);
    work->add(file1);
    work->add(file3);

    documents->display();
    std::cout << "Общий размер папки Documents: " << documents->getSize() << " байт" << std::endl;

    // 7. GUI система
    std::cout << "\n=== GUI система ===" << std::endl;
    auto window = std::make_shared<Window>("Main Window");
    auto panel = std::make_shared<Panel>("Main Panel");
    auto button = std::make_shared<Button>("OK");
    auto label = std::make_shared<Label>("Status");
    auto textField = std::make_shared<TextField>("Input");

    window->add(panel);
    panel->add(button);
    panel->add(label);
    panel->add(textField);

    window->display();

    // 8. Игровая сцена
    std::cout << "\n=== Игровая сцена ===" << std::endl;
    auto scene = std::make_shared<Scene>("Main Scene");
    auto player = std::make_shared<Player>("Hero");
    auto enemyGroup = std::make_shared<EnemyGroup>("Goblin Group");
    auto goblin1 = std::make_shared<Enemy>("Goblin 1");
    auto goblin2 = std::make_shared<Enemy>("Goblin 2");
    auto item = std::make_shared<Item>("Health Potion");

    scene->add(player);
    scene->add(enemyGroup);
    scene->add(item);
    enemyGroup->add(goblin1);
    enemyGroup->add(goblin2);

    scene->display();

    // 9. HTML DOM
    std::cout << "\n=== HTML DOM ===" << std::endl;
    auto body = std::make_shared<BodyNode>("body");
    auto div1 = std::make_shared<DivNode>("header");
    auto div2 = std::make_shared<DivNode>("content");
    auto buttonNode = std::make_shared<ButtonNode>("Submit");
    auto imageNode = std::make_shared<ImageNode>("logo.png");
    auto textNode = std::make_shared<TextNode>("Welcome");

    body->add(div1);
    body->add(div2);
    div1->add(textNode);
    div2->add(imageNode);
    div2->add(buttonNode);

    body->display();

    // 10. Организационная структура
    std::cout << "\n=== Организационная структура ===" << std::endl;
    auto company = std::make_shared<Company>("Tech Corp");
    auto itDept = std::make_shared<Department>("IT Department");
    auto hrDept = std::make_shared<Department>("HR Department");
    auto employee1 = std::make_shared<Employee>("John Doe");
    auto employee2 = std::make_shared<Employee>("Jane Smith");
    auto employee3 = std::make_shared<Employee>("Bob Johnson");

    company->add(itDept);
    company->add(hrDept);
    itDept->add(employee1);
    itDept->add(employee2);
    hrDept->add(employee3);

    company->display();

    // 12. Поиск объекта
    std::cout << "\n=== Поиск объекта ===" << std::endl;
    if (company->find("John Doe")) {
        std::cout << "Сотрудник John Doe найден!" << std::endl;
    } else {
        std::cout << "Сотрудник не найден" << std::endl;
    }

    if (!company->find("Unknown")) {
        std::cout << "Сотрудник Unknown не найден" << std::endl;
    }

    // 13. Глубокая вложенность (5 уровней)
    std::cout << "\n=== Глубокая вложенность ===" << std::endl;
    auto world = std::make_shared<Composite>("World");
    auto region = std::make_shared<Composite>("Region");
    auto city = std::make_shared<Composite>("City");
    auto district = std::make_shared<Composite>("District");
    auto building = std::make_shared<Composite>("Building");
    auto room = std::make_shared<Leaf>("Room 101");

    world->add(region);
    region->add(city);
    city->add(district);
    district->add(building);
    building->add(room);

    world->display();

    // 14. Обход дерева
    std::cout << "\n=== DFS обход ===" << std::endl;
    DFS(world);

    std::cout << "\n=== BFS обход ===" << std::endl;
    BFS(world);

    // 20. Система меню приложения
    std::cout << "\n=== Система меню приложения ===" << std::endl;
    auto mainMenu = std::make_shared<Menu>("Main Menu");
    auto fileMenu = std::make_shared<Menu>("File");
    auto editMenu = std::make_shared<Menu>("Edit");
    auto newItem = std::make_shared<MenuItem>("New");
    auto openItem = std::make_shared<MenuItem>("Open");
    auto saveItem = std::make_shared<MenuItem>("Save");
    auto copyItem = std::make_shared<MenuItem>("Copy");
    auto pasteItem = std::make_shared<MenuItem>("Paste");

    mainMenu->add(fileMenu);
    mainMenu->add(editMenu);
    fileMenu->add(newItem);
    fileMenu->add(openItem);
    fileMenu->add(saveItem);
    editMenu->add(copyItem);
    editMenu->add(pasteItem);

    mainMenu->display();
    std::cout << "Количество элементов в меню: " << mainMenu->count() << std::endl;

    std::cout << "\nПоиск пункта 'Save': ";
    if (mainMenu->find("Save")) {
        std::cout << "Найден!" << std::endl;
    } else {
        std::cout << "Не найден" << std::endl;
    }

    std::cout << "Удаление пункта 'Open'..." << std::endl;
    if (mainMenu->remove("Open")) {
        std::cout << "Пункт 'Open' удалён" << std::endl;
    }
    mainMenu->display();

    return 0;
}

