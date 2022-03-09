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
-Мы следуем главным парадигмам ООП
-Код является легко поддерживаемым, для создания нового окна мы просто:
--наследуемся от класса-родителя и переписываем стандартный метод, задающий окно,
