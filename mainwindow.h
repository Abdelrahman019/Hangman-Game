#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "hangman.h"

//Nour (classes)
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_guessButton_clicked();
    void on_startGameButton_clicked();

private:
    Ui::MainWindow *ui;
    Hangman game;
    void updateUI();
    void updateHangmanImage();
    void checkGameOver();
    QString getRandomWord(const QString &category);
};

#endif
