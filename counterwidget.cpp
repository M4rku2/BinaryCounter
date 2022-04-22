#include <QHBoxLayout>
#include "counterwidget.h"
#include "config.h"

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent), m_count(0), m_timer(this), m_gpio(this)
{
    setWindowTitle("BinaryCounter");
    resize(300, 200);
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);

    // QLCDNumber zur Anzeige des Zaehlerstandes dezimal:

        m_LCD = new QLCDNumber(3);
        layout->addWidget(m_LCD);
        m_LCD->display(m_number);

    connect(&m_timer, &QTimer::timeout, this, &CounterWidget::updateCounter);
    m_timer.start(T_UPDATE);
}

CounterWidget::~CounterWidget()
{

}

void CounterWidget::refreshLED()
{
    for(int i = 0; i < 4; i++)
        m_gpio.set(LEDS[i], (m_number >> i) & 0b1);
}

// Zaehlerstand im Widget und dual ueber LEDs anzeigen:
void CounterWidget::updateCounter()
{


        if(m_gpio.isActivated(BUTTONS[2]))
            m_number = (m_number + 1) & 0xF;

        if(m_gpio.isActivated(BUTTONS[0]))
            m_number = (m_number - 1) & 0xF;

        if(m_gpio.isActivated(BUTTONS[1]))
            m_number = 0;

        m_LCD->display(m_number);
        refreshLED();


}


