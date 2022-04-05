#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpio.h"
#include "gpio_config.h"

#include <lgpio.h>
#include <QTimer>

int TSLEEP = 500 ;// milliseconds   don't forget to add the const next time

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
   ,m_timer(new QTimer(this))
{
    setupUi(this);

    m_gpio= new Gpio(this);

    connect(m_timer, &QTimer::timeout, this, &MainWindow::on_timeout);
    frequencyLabel->setNum(frequencySlider->value());
   // m_status = false;

}

MainWindow::~MainWindow()
{
    delete m_timer;
}

void MainWindow::on_startButton_clicked()
{
   // int frequencyconst int OUT = 18;

    m_timer->start(TSLEEP);
}

void MainWindow::on_stopButton_clicked()
{
    m_timer->stop();
}

void MainWindow::on_frequencySlider_valueChanged(int value)
{
    TSLEEP = 1000/value;
    MainWindow::restart();

}

void MainWindow::restart()
{
    MainWindow::on_stopButton_clicked();
    MainWindow::on_startButton_clicked();
}
void MainWindow::on_timeout()
{
    m_gpio->set(LEDS[0], m_status);
    m_status = !m_status;
    led->toggle();
}
