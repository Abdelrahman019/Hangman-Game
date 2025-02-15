#include "hangman.h"



// Shaheen (start new game)
void Hangman::startNewGame(const QString &word) {
    this->word = word;
    displayWord = QString(word.size(), '_');
    guessedLetters.clear();
    attemptsLeft = 6;
}

void Hangman::guess(QChar letter) {
    if (guessedLetters.contains(letter) || attemptsLeft == 0) {
        return;
    }

    guessedLetters.insert(letter);



    // yoyo (game loop)
    bool correctGuess = false;
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] == letter) {
            displayWord[i] = letter;
            correctGuess = true;
        }
    }

    if (!correctGuess) {
        attemptsLeft--;
    }
}

QString Hangman::getDisplayWord() const {
    return displayWord;
}

int Hangman::getAttemptsLeft() const {
    return attemptsLeft;
}
QString Hangman::getGuessedLetters() const {
    QString guessed;
    for (QChar letter : guessedLetters) {
        guessed.append(letter);
        guessed.append(' ');
    }
    return guessed.trimmed();
}

QString Hangman::getWord() const {
    return word;
}
