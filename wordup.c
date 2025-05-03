//Project 10
//Gavin Martins
//Friday May 2nd

#include <stdio.h>
#include <stdbool.h>

#define length 5
#define maxGuesses 6

// declaring function prototypes
void loadWord(char word[]);
bool validateGuess(char guess[]);
void lowercase(char str[]);
bool alphabet(char temp);
bool stringsEqual(char display[], char pointer[]);
void processGuess(char guess[], char word[], char board[maxGuesses][length + 1], char hints[maxGuesses][length + 1], int turn);
void printBoard(char board[maxGuesses][length + 1], char hints[maxGuesses][length + 1], int turnsUsed);

int main() {
    char word[length + 1];
    loadWord(word);
    char board[maxGuesses][length + 1];
    char hints[maxGuesses][length + 1];
    int turns;
    turns = 0;

    while (turns < maxGuesses) {
        char guess[100];

        printf("Enter guess %d: ", turns ++);
        scanf("%s", guess);

//validates if the guess is 5 letters, and if not gives back invalid
        if (validateGuess(guess)) {
        //running functions that compare the guess to the word, and give feedback to the user
        lowercase(guess);
        processGuess(guess, word, board, hints, turns);
        printBoard(board, hints, turns ++);
        //if the guess string is equal to the word string, that means they guessed right
        if (stringsEqual(guess, word)) {
            printf("You guessed correctly!\n");
            return 0;
        }
        turns++;
    } else {
     printf("Invalid guess, must be only 5 letters\n");
     }
     }
printf("Out of guesses, The word was %s\n", word);
return 0;
}
// loads word from mystery.txt
void loadWord(char word[]) {
    FILE *file = fopen("mystery.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open word.txt\n");
        word[0] = '\0';
        return;
    }

    for (int i = 0; i < length; i++) {
        int ch = fgetc(file);
        if (ch == EOF || ch == '\n') break;
        word[i] = ch;
    }
    word[length] = '\0';
    fclose(file);
}

// Checks guess is exactly 5 letters
bool validateGuess(char guess[]) {
    int len = 0;
    while (guess[len] != '\0') {
        if (!alphabet(guess[len])) return false;
        len++;
    }
    return len == length;
}

// Converts all characters to lowercase
void lowercase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
        i++;
    }
}

// function to check if the letters are within the alphabet range
bool alphabet(char temp) {
    return (temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z');
}

// Check if two 5-letter strings are the same
bool stringsEqual(char display[], char pointer[]) {
    for (int i = 0; i < length; i++) {
        if (display[i] != pointer[i]) return false;
    }
    return true;
}

// Processes the guess, capital letters for correct spot, ^ for correct letter in wrong spot
void processGuess(char guess[], char word[], char board[maxGuesses][length + 1], char hints[maxGuesses][length + 1], int turn) {
    bool matched[length] = {false};

    // copies guess into board and initialize hints
    for (int i = 0; i < length; i++) {
        board[turn][i] = guess[i];
        hints[turn][i] = ' ';
    }
    board[turn][length] = '\0';
    hints[turn][length] = '\0';

    // shows correct letters in correct position
    for (int i = 0; i < length; i++) {
        if (guess[i] == word[i]) {
            if (guess[i] >= 'a' && guess[i] <= 'z') {
                board[turn][i] = guess[i] - 'a' + 'A';
            }
            matched[i] = true;
        }
    }

    // shows correct letters, wrong position
    for (int i = 0; i < length; i++) {
        if (board[turn][i] == guess[i]) {
            for (int j = 0; j < length; j++) {
                if (!matched[j] && guess[i] == word[j]) {
                    hints[turn][i] = '^';
                    matched[j] = true;
                    break;
                }
            }
        }
    }
}

// Prints all previous guesses and hints
void printBoard(char board[maxGuesses][length + 1], char hints[maxGuesses][length + 1], int turnsUsed) {
    for (int i = 0; i < turnsUsed; i++) {
        printf("%s\n", board[i]);
        printf("%s\n", hints[i]);
    }
}

