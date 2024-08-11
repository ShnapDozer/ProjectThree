#include "QSFMLCanvas.h"

#include <string>

#include <QPixmap>
#include <QByteArray>
#include <QBuffer>

QSFMLCanvas::QSFMLCanvas(QWidget *parent, uint frameTime) :
    QWidget(parent),
    // Инициализируем базовый конструктор окна отрисовки SFML
    sf::RenderWindow(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(24)),
    m_initialized(false)
{
    // Произведём настройку для непосредственной отрисовки изображения в виджет
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Установим строгую фокусировку для включения событий клавиатуры
    setFocusPolicy(Qt::StrongFocus);

    // Настроим период сработки таймера перерисовки
    m_timer.setInterval(frameTime);
}

void QSFMLCanvas::onInit()
{
    // Загрузка изображения из ресурсных файлов Qt
    // Довольно интересный момент в том плане, что
    // SFML не может загрузить изображение из ресурсов, как это делают QPixmap или QImage
    QPixmap pixmap(":/QtCreator.png");  // Но если создать объект QPixmap
    QByteArray bArray;                  // Создать объект массива байтов
    QBuffer buffer(&bArray);            // Поместить его в буфер
    buffer.open(QIODevice::WriteOnly);  // Сохранить изображение в этот буфер, то есть в память
    pixmap.save(&buffer, "PNG");

    // А потом забрать сырые данные из буффера, с указанием количества забираемых данных
    m_texture.loadFromMemory(buffer.data().data(), buffer.data().size());
    // Эту процедуру понадобится произвести один раз при создании текстуры SFML

    // Далее устанавливаем изображения в sprite
    m_sprite.setTexture(m_texture);
    float xScale = 200. / m_sprite.getTextureRect().width;
    float yScale = 200. / m_sprite.getTextureRect().height;
    m_sprite.setScale(xScale, yScale);     // Масштабируем изображение
    m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2); // Устанавливаем центр изображения
    m_sprite.setPosition(200, 200);        // Устанавливаем позицию изображения
}

void QSFMLCanvas::onUpdate()
{
    // Очищаем экран
    clear(sf::Color(128, 0, 0));

    // Поворачиваем изображение
    m_sprite.rotate(1);

    // Отрисовываем это изображение
    draw(m_sprite);
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    // Возвращаем nullptr вместо движка отрисовки Qt, чтобы Qt не пытался что либо рисовать сам
    return nullptr;
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    // Первичная инициализация виджета SFML
    if (m_initialized) { return; }

    sf::VideoMode mode;
    mode.height = 1000;
    mode.width = 1000;

    // Создаём SFML окно для отрисовки с указанием Id окна, в котором будет производиться отрисовка
    sf::RenderWindow::create(mode, "ProjectThree");

    // Инициализация объектов отрисовки
    onInit();

    // Настройка таймера для перезапуска отрисовки виджета
    connect(&m_timer, &QTimer::timeout, this, &QSFMLCanvas::onTimeout);
    m_timer.start();

    m_initialized = true;

}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // Обновление отрисовки объектов
    onUpdate();

    // Отображение отрисованного окна
    display();
}

void QSFMLCanvas::onTimeout()
{
    // Запуск перерисовки
    repaint();
}
