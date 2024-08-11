#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QTimer>
#include <QWidget>
#include <SFML/Graphics.hpp>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSFMLCanvas(QWidget* parent = nullptr, uint frameTime = 50);
    virtual ~QSFMLCanvas() {}

private :
    void onInit();
    void onUpdate();
    virtual QPaintEngine* paintEngine() const override;
    virtual void showEvent(QShowEvent*) override;
    virtual void paintEvent(QPaintEvent*) override;

private slots:
    void onTimeout();

private:
    QTimer m_timer;
    bool   m_initialized;

    RenderWindow m_window;

    sf::Texture  m_texture;
    sf::Sprite   m_sprite;
};

#endif // QSFMLCANVAS_H
