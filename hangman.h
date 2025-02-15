#ifndef HANGMAN_H
#define HANGMAN_H
#include <QString>
#include <QSet>
// nour (classes)
class Hangman {
public:
    void startNewGame(const QString &word);
    void guess(QChar letter);
    QString getDisplayWord() const;
    int getAttemptsLeft() const;
    QString getGuessedLetters() const;
    QString getWord() const;

private:
    QString word;
    QString displayWord;
    QSet<QChar> guessedLetters;
    int attemptsLeft;
};

#endif
