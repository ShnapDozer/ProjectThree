# ProjectThree
Некий 2D игровой движок, работающий под фреймворком SFML. Воспринемает isometric и ortogonal карты, созданные в Tiled map editor.
Для реализации интерфейса движка используется библиотека [ImGUI](https://github.com/eliasdaler/imgui-sfml), а данные сохраняются и читаются в xml формате с помощью библиотеки [TinyXML2](https://github.com/leethomason/tinyxml2).

![image](https://user-images.githubusercontent.com/57567072/157476781-ce84073d-d0e6-449b-9af3-ba689a18a808.png)

### Цель проекта:
Главная задача данного проекта - развитие навыков программирования и применение полученых знаний на практике. 
Проект разрабатывается периодами "когда есть время и желания", из-за этого маловероятно что он вообще получит стату завершонного.
Поэтому на данный момент не вижу смысла создавать какую-то обширную документацию или описание на проект.
Хочется только показать те вещи, чьей реализацией я действительно доволен.

### Красивые реализации:
Проект начинался писаться по [туториулу](https://kychka-pc.ru/sfml/urok-1-podklyuchenie-biblioteki-k-srede-razrabotki-visual-studio-2013.html) с сайта, который даже сейчас дает некое понимание как работает игровой цикл и т.д..

Поэтому структура проекта в большинстве своем построена на классе какого-то объекта (например анимации) и классе менеджера данного объекта, в котором реализованны главные методы работы с объектом. 
Структура в некоторых случаях не самая хорошая, но рабочая, поэтому пока мною не придуманно ничего другого, будет использоваться именно она.
Также в проекте активно используются так называемые умные указатели, которые в разы упращают работу с памятью в проекте. 

Ну и наконец к красивым реализациям:

### ImGUI:
Сама библиотека ImGUI не предназначена для работы в окне sfml, поэтому в проекте использованна адаптированная библиотека именно для нашего фреймворка.
ImGUI построен на окнах и виджетах в них, которые задаются парой строк кода. Но сам код окон в примере использования нам предлагается размещать в теле главного игрового цикла, что в корне неудобно.

Вскоре я понял, что можно создать родительский виртуальный класс окна и от него наследовать нужные мне окна.
Родительский класс необходим для сущности ImGUI manager, т.к. у всех окон надо вызывать общие функции отрисовки о обновления, из чего следует, что сущности разных окон нужно хранить в одном контейнере (лучше всего в векторе), а такое возможно только когда мы создаем контейнер из родительского класса. 
Красота реализации данной задачи очень проста:
- Мы следуем главным парадигмам ООП
- Код является легко поддерживаемым, для создания нового окна мы просто:
  - Наследуемся от класса-родителя и переписываем стандартный метод, задающий окно
  - Вставляем объект нашего окна в вектор окон
- Также везде используются умные указатели, не дающие и шанса памяти утечь
##### Класс-родитель и его функции:
```c++
class AnotherWindow // Parent class for all windows
{
public:

	AnotherWindow(const std::string& name, ImVec2& Size, ImVec2& Pos) : name_Windows(name), WinSize(Size), WinPos(Pos) {}
  // a standard constructor that accepts the name, size, and position of the window

	virtual void inWork() = 0; // virtual function which implements the functionality of the window
...Other methods and variables...
};
```
##### Добавление в менеджер окон нового окна:
```c++
IMG_Manager::IMG_Manager(...some...) // constructor of the window manager class
{
  All_Window.push_back(std::make_shared<Example_Window>(...some...)); // adding a new window to the window vector
}
```
##### Работа менеджара окон в главном игровом цикле:
```c++
while(true)// The main game cycle
{
...Some game code....

// - Part of the cycle data update:
  ImGUI_Manager->update(Main_Window, deltaClock);
  ImGUI_Manager->Work();
  
// - Part of the cycle render:
  ImGUI_Manager->Render(*Main_Window);
}
```

Подробные примеры (если понадобиться) того как надо работать с данными классами можете увидеть в файлах ImGui_Mg.h и ImGui_Mg.cpp, не думаю что будет сложно понять что к чему. 
В итоге после создания данного менеджера кода в главном игровом цикле стало в разы меньше, а работа по созданию новых окон упрастилась.
Считаю данные классы самыми удачными в плане реализации поставленной задачи .

### Остальные приколы опишу чуть позже....(устал)

