A Наследование
1 Наследование - механизм объектно-ориентированного программирования, позволяющий создать новый класс на 
основе существующего (Назначение = Повторное использование кода, Иерархия классов, Полиморфизм)

2 Базовые классы - класс, от которого наследуются другие классы, передавая им свои члены, за исключением 
конструкторов.
Производные классы - классы, наследующие члены от базового класса, что позволяет повторно использовать и 
расширять функциональность

3 Ключевое слово base используется в производных классах для доступа к членам их непосредственного базового 
класса

4 Переопределение методов позволяет производному классу предоставить специфическую реализацию метода, 
уже определенного в базовом классе ( для этого используются ключевые слова virtual u override)

5 Основное отличие override от new заключается в поведении при полиморфизме: override переопределяет 
виртуальный метод, изменяя его поведение для всех вызовов, а new скрывает метод базового класса, создавая 
новый метод с тем же именем, но не меняя поведение базового типа

6 Написание программ

B Интерфейсы 
1 Интерфейс — это ссылочный тип данных, представляющий собой «контракт», который определяет набор методов, 
свойств, событий или индексаторов без их реализации.

2 интерфейсы описывают только поведение и позволяют реализовывать несколько штук сразу,
а абстрактные классы могут содержать готовую логику, поля данных, конструкторы и поддерживают только одиночное 
наследование.

3 Реализует несколько интерфейсов, перечисляя их через запятую после двоеточия.

4 Программирование через интерфейсы — принцип проектирования, при котором код взаимодействует с абстрактным 
контрактом, а не с конкретной реализацией.

5 (Интерфейсы репозиториев) Бизнес-логика работает с интерфейсами доступа к данным
(Интерфейсы сервисов) Пользовательский интерфейс взаимодействуют с бизнес-логикой через интерфейсы

C Сериализация объектов и логирование 
1 Сериализация - процесс преобразования объекта в поток байтов для хранения или передачи, 
  Десериализация — обратный процесс восстановления объекта.

2 JSON используют пространства имён System.Text.Json, а 
  XML — System.Xml и System.Xml.Serialization

3 public class User
{
    public string Name { get; set; }
    public int Age { get; set; }
}

public class Program
{
    public static void Main()
    {
        var user = new User { Name = "Ivan", Age = 18 };
        // Сериализация объекта в JSON-строку
        string jsonString = JsonSerializer.Serialize(user);
        Console.WriteLine(jsonString); 
        // Вывод: {"Name":"Ivan","Age":30}
    }
}

4 Логирование нужно для отслеживания хода выполнения программы, фиксации ошибок и диагностики проблем в процессе разработки и эксплуатации.

5 Info — информация о штатном выполнении программы
  Warning — предупреждения о потенциальных проблемах, не нарушающих работу
  Error — ошибки, нарушающие выполнение операции

6 третье задание


Задача 1 

using System;

// 1. Базовый абстрактный класс Shape
abstract class Shape
{
    public abstract double GetArea();
}

// 2. Производный класс Circle (круг)
class Circle : Shape
{
    private double radius;

    // Конструктор для установки радиуса
    public Circle(double radius)
    {
        this.radius = radius;
    }

    // Переопределение метода GetArea() для круга
    public override double GetArea()
    {
        return Math.PI * radius * radius; // Формула площади круга: π * r²
    }
}

// 3. Производный класс Rectangle (прямоугольник)
class Rectangle : Shape
{
    private double width;
    private double height;

    // Конструктор для установки ширины и высоты
    public Rectangle(double width, double height)
    {
        this.width = width;
        this.height = height;
    }

    // Переопределение метода GetArea() для прямоугольника
    public override double GetArea()
    {
        return width * height; // Формула площади прямоугольника: ширина × высота
    }
}

// Основной класс программы для демонстрации работы
class Program
{
    static void Main(string[] args)
    {
        // Создаём экземпляры фигур
        Shape circle = new Circle(5);          // Круг с радиусом 5
        Shape rectangle = new Rectangle(4, 6); // Прямоугольник 4×6

        // Выводим площади каждой фигуры
        Console.WriteLine($"Площадь круга: {circle.GetArea():F2}");
        Console.WriteLine($"Площадь прямоугольника: {rectangle.GetArea():F2}");
    }
}

Задача 2 

using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

// 1. Класс LogEntry согласно требованиям
class LogEntry
{
    public DateTime Time { get; set; }
    public string Level { get; set; }
    public string Message { get; set; }
}

class Logger
{
    private string _logFilePath = "log.json";
    
    // Метод для добавления новой записи лога и записи в файл
    public void Log(string level, string message)
    {
        // Создаём объект лога
        var logEntry = new LogEntry
        {
            Time = DateTime.Now,
            Level = level,
            Message = message
        };

        // Получаем существующие записи или создаём новый список
        var logEntries = File.Exists(_logFilePath)
            ? ReadExistingLogs()
            : new List<LogEntry>();

        // Добавляем новую запись
        logEntries.Add(logEntry);

        // Сериализуем в JSON и записываем в файл
        SerializeAndSave(logEntries);
    }

    // Чтение существующих логов из файла
    private List<LogEntry> ReadExistingLogs()
    {
        string json = File.ReadAllText(_logFilePath);
        return JsonSerializer.Deserialize<List<LogEntry>>(json) ?? new List<LogEntry>();
    }

    // Сериализация в JSON и запись в файл с форматированием
    private void SerializeAndSave(List<LogEntry> logEntries)
    {
        var options = new JsonSerializerOptions
        {
            WriteIndented = true // Красивый вывод (форматирование)
        };
        
        string json = JsonSerializer.Serialize(logEntries, options);
        File.WriteAllText(_logFilePath, json);
    }
}

// Основной класс программы
class Program
{
    static void Main(string[] args)
    {
        var logger = new Logger();

        // 3. Добавляем минимум 3 записи разных уровней
        logger.Log("INFO", "Приложение успешно запущено");
        logger.Log("WARNING", "Обнаружено медленное соединение с базой данных");
        logger.Log("ERROR", "Не удалось выполнить запрос к API: ошибка аутентификации");

        Console.WriteLine("Логи успешно записаны в файл log.json");
    }
}
