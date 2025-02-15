#include "mainwindow.h"                     //includes the header file for the MainWindow class.
#include "ui_mainwindow.h"                  //include the desing generated by QT.
#include <QPixmap>                          //library to change the hangman picture.
#include <QLabel>                           //add text to the widget
#include <QGridLayout>                      //allignment of the objects in the window
#include <QMessageBox>                      //used in the flash messages after the game is over
#include <QRandomGenerator>


// Nour (launching GUI start window and parent widgets)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    connect(ui->guessLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_guessButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_startGameButton_clicked() {
    QString category = ui->categoryComboBox->currentText();
    QString word = getRandomWord(category);

    game.startNewGame(word);
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    updateUI();
}


//Omar Nagia (the lists of the word and categories)
QString MainWindow::getRandomWord(const QString &category) {
    QStringList fruits = {"apple", "banana", "cherry", "date", "fig","tomato","watermelon","orange","pomegranate","grapes","blueberry","pineapple"};
    QStringList animals = {"tiger", "elephant", "giraffe", "kangaroo", "penguin","lion","cat","dog","cheetah","dolphin","shark","whale","lobster","crab"};
    QStringList countries = {"canada", "brazil", "france", "germany", "japan","egypt","colombia","peru","venezuela","argentina","portugal","spain","china","denmark","southkorea","northkorea","philippines","chile","hongkong","thailand"};
    QStringList colors = {"red", "blue", "green", "yellow", "purple","orange"};
    QStringList randomWords = fruits + animals + countries + colors;

    if (category == "Fruits") {
        return fruits.at(QRandomGenerator::global()->bounded(fruits.size()));
    } else if (category == "Animals") {
        return animals.at(QRandomGenerator::global()->bounded(animals.size()));
    } else if (category == "Countries") {
        return countries.at(QRandomGenerator::global()->bounded(countries.size()));
    } else if (category == "Colors") {
        return colors.at(QRandomGenerator::global()->bounded(colors.size()));
    } else {
        return randomWords.at(QRandomGenerator::global()->bounded(randomWords.size()));
    }
}

void MainWindow::on_guessButton_clicked() {
    QString guess = ui->guessLineEdit->text();
    if (!guess.isEmpty()) {
        game.guess(guess[0].toLatin1());
        updateUI();
        ui->guessLineEdit->clear();
        checkGameOver();
    }
}


// Abdelrahman (letter borders)
void MainWindow::updateUI() {
    QString displayWord = game.getDisplayWord();
    QGridLayout *gridLayout = static_cast<QGridLayout*>(ui->wordGridLayout);

    // Clear previous letters
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Add the borders with the size of the word letters
    for (int i = 0; i < displayWord.length(); ++i) {
        QLabel *letterLabel = new QLabel(displayWord[i] == '_' ? "_" : QString(displayWord[i]));
        letterLabel->setStyleSheet(
            "border: 2px solid #700EE6; "
            "background-color: #DBA7E6; "
            "color: #000000; "
            "padding: 5px; "
            "font-size: 18px;"
            "min-width: 25px;"
            "min-height: 25px;"
            "max-width: 25px;"
            "max-height: 25px;"
            );
        letterLabel->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(letterLabel, 0, i);
    }

    ui->attemptsLabel->setText("Attempts left: " + QString::number(game.getAttemptsLeft()));
    ui->guessedLettersLabel->setText("Guessed letters: " + game.getGuessedLetters());
    updateHangmanImage();
}



//Bassel Hossam ( change hangman image function && game end)

void MainWindow::updateHangmanImage() {
    int attemptsLeft = game.getAttemptsLeft();
    QString imagePath = QString(":/img/img/hangman%0.png").arg(6 - attemptsLeft);
    QPixmap pixmap(imagePath);
    ui->hangmanImageLabel->setPixmap(pixmap);
}


// game over check function
void MainWindow::checkGameOver() {
    if (game.getAttemptsLeft() == 0 || game.getDisplayWord().replace(' ', "") == game.getWord()) {
        QString message;
        if (game.getDisplayWord().replace(' ', "") == game.getWord()) {
            message = "Congratulations, you won! The word was: " + game.getWord();
        } else {
            message = "Game over! The word was: " + game.getWord();
        }
        QMessageBox::information(this, "Game Over", message);
        ui->stackedWidget->setCurrentWidget(ui->startPage);
    }
}
