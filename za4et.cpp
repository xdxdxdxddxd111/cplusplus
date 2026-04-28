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

6 Написание программ (Базовый класс и подклассы, Расширение поведения)

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

abstract class Shape
{
    public abstract double GetArea();
}

class Circle : Shape
{
    private double radius;

    public Circle(double radius)
    {
        this.radius = radius;
    }

    public override double GetArea()
    {
        return Math.PI * radius * radius;
    }
}

class Rectangle : Shape
{
    private double width;
    private double height;

    public Rectangle(double width, double height)
    {
        this.width = width;
        this.height = height;
    }

    public override double GetArea()
    {
        return width * height;
    }
}

class Program
{
    static void Main(string[] args)
    {
        Shape circle = new Circle(5);
        Shape rectangle = new Rectangle(4, 6);
      
        Console.WriteLine($"Площадь круга: {circle.GetArea():F2}");
        Console.WriteLine($"Площадь прямоугольника: {rectangle.GetArea():F2}");
    }
}

--- Задача 2 ---

using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using System.Text.Encodings.Web;
using System.Text.Unicode;

namespace LoggingSystem
{
    public class LogEntry
    {
        public DateTime Time { get; set; }
        public string Level { get; set; }
        public string Message { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string filePath = "log.json";

            var logEntries = new List<LogEntry>
            {
                new LogEntry { Time = DateTime.Now, Level = "INFO", Message = "Приложение запущено." },
                new LogEntry { Time = DateTime.Now.AddSeconds(2), Level = "WARNING", Message = "Низкий заряд батареи." },
                new LogEntry { Time = DateTime.Now.AddSeconds(5), Level = "ERROR", Message = "Не удалось подключиться к базе данных." }
            };

            WriteLogsToJson(logEntries, filePath);

            Console.WriteLine($"Логи успешно записаны в {Path.GetFullPath(filePath)}");
        }

        static void WriteLogsToJson(List<LogEntry> logs, string filePath)
        {
            var options = new JsonSerializerOptions
            {
                WriteIndented = true,
                Encoder = JavaScriptEncoder.Create(UnicodeRanges.All)
            };

            string jsonString = JsonSerializer.Serialize(logs, options);

            File.WriteAllText(filePath, jsonString);
        }
    }
}

