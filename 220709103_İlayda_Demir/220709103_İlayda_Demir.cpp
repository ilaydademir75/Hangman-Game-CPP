#include <iostream>
#include <cstdlib> // Required for srand function.
#include <string>
#include <ctime>

using namespace std;

string myWords[] = {
    // Word List
    "Ataturk",
    "Universitesi",
    "Bilgisayar",
    "Muhendisligi",
    "Bolumu",
    "Erzurum",
    "Nesne",
    "Yonelimli",
    "Programlama",
    "Dersi"
};

// Man Drawing Functions
void headDraw() {
    cout << "--------------" << endl;
    cout << "|             " << endl;
    cout << "|         ( ) " << endl;
    cout << "|             " << endl;
    cout << "|" << endl;
    cout << "|" << endl << endl;
}

void bodyDraw() {
    cout << "--------------" << endl;
    cout << "|             " << endl;
    cout << "|         ( ) " << endl;
    cout << "|          |  " << endl;
    cout << "|" << endl;
    cout << "|" << endl << endl;
}

void armDraw() {
    cout << "--------------" << endl;
    cout << "|             " << endl;
    cout << "|         ( ) " << endl;
    cout << "|         /|\\" << endl; // "\" is an escape character so two of them must be used side by side.
    cout << "|" << endl;
    cout << "|" << endl << endl;
}

void footDraw() {
    cout << "--------------" << endl;
    cout << "|             " << endl;
    cout << "|         ( ) " << endl;
    cout << "|         /|\\" << endl;
    cout << "|         / \\" << endl;
    cout << "|" << endl << endl;
}

// Function required to show the latest status of the man
void aLatestStatusShow(int numberOfErrors) {
    cout << "\n [Man's Condition]: " << endl;
    if (numberOfErrors == 0)
        cout << endl << endl << endl << endl; // He does not draw the man because no mistake was made.
    else if (numberOfErrors == 1)
        headDraw(); // In the Hangman game, when a mistake is made, the headDraw() function is called to draw the head.
    else if (numberOfErrors == 2)
        bodyDraw(); // When 2 mistakes are made in the Hangman game, the body is drawn by calling the bodyDraw() function.
    else if (numberOfErrors == 3)
        armDraw(); // When 3 mistakes are made in the Hangman game, the arms are drawn by calling the armDraw() function.
    else if (numberOfErrors == 4)
        footDraw(); // When 4 mistakes are made in the Hangman game, the feet are drawn by calling the footDraw() function.
}

// Function required to show the final state of the word
void kLatestStatusShow(string word, bool correctLetters[]) {
    cout << "\n [Latest Status of the Word]: ";
    for (int i = 0; i < word.length(); i++) {
        if (correctLetters[i]) { // If the condition is met, that letter comes to the relevant index of the word.
            cout << word[i] << ' ';
        }
        else {
            cout << "_ "; // If the condition is not met, a "_" sign is printed on the screen.
        }
    }
    cout << endl;
}

// Function to display all entered letters
void letterShow(char enteredLetters[], int numberOfLetters) {
    cout << " \n [Entered Letters]: ";
    for (int i = 0; i < numberOfLetters; i++) {
        cout << enteredLetters[i] << ' ';
    }
    cout << endl;
}

// I added this function myself. Because C++ is case sensitive and even if I entered the correct letter, it would give an error. To prevent this, I wrote a function that converts all letters to uppercase.
string convertToUppercase(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - 32;
        }
    }
    return word;
}

int main() {

    srand(time(0)); // The srand function was used for random word selection. Srand was chosen so that the same word would not be produced but a different word would be produced each time.

    int totalKnownWords = 0; // Initially the number of known words is 0.
    bool playGame = true;

    while (playGame) {
        string word = myWords[rand() % 10]; // It generates random numbers between 0 and 9. Because there are 10 words in total.
        word = convertToUppercase(word); // The word is converted to capital letters to avoid errors.

        bool correctLetters[15] = {}; // Since words consist of at most 12 letters, I created a 15-dimensional array so that I could give plenty of space to all the words.
        char enteredLetters[26]; // Since there are 26 letters in the English alphabet, a 26-dimensional array was created.
        int numberOfLetters = 0; // Initially, the number of letters is assumed to be 0.
        int numberOfErrors = 0; // The number of errors is initially assumed to be 0.
        bool wordKnown = false; // It will become true when the word is known. Initially it is considered false.

        cout << "\n\n~Welcome to the Hangman Game! Here comes your word. Good Luck!!!~\n\n";

        while (numberOfErrors < 4 && !wordKnown) { // To win the game, the number of errors must be less than 4 and the word must be known.
            kLatestStatusShow(word, correctLetters); // The function is called to show the latest state of the word. Known letters will be shown.
            letterShow(enteredLetters, numberOfLetters); // The function is called to show which letters have been entered so far.

            cout << "\n *Enter A Letter To Find The Word Or Press 1 And Try To Guess The Word:";
            string guess; // The user is asked to enter a letter or the number 1.
            cin >> guess;

            if (guess == "1") { // If the user enters the number 1, he or she must enter the entire word.
                cout << "\n Write Your Word Guess:";
                string wordPrediction; // A word prediction is taken from the user.
                cin >> wordPrediction;

                wordPrediction = convertToUppercase(wordPrediction); // Word Prediction is converted to uppercase.

                string bigWord = convertToUppercase(word); // The word has also been converted to be written in capital letters.

                if (wordPrediction == bigWord) { // It is checked whether the user's guess is correct or not.
                    cout << "\n Congratulations, You Are Amazing! You Got the Word Right:" << word << endl;
                    totalKnownWords = totalKnownWords + 1; // Since the word is known correctly, the total number of known words has been increased.
                    wordKnown = true; // The word was updated to "true" because it was known.
                    break;
                }
                else { // If the user guesses the word incorrectly, this code block is executed.
                    cout << "\n Sorry :( Your Guess Is Wrong.";
                    numberOfErrors = 4;
                    aLatestStatusShow(numberOfErrors);
                    break;
                }
            }
            else if (guess.size() == 1) { // Now we check if the user has entered a single letter.
                char letterPrediction = toupper(guess[0]); // Capitalize the entered letter, capitalize if it is small.
                bool previouslyEntered = false;  // A variable is defined to prevent entering the same letters.

                for (int i = 0; i < numberOfLetters; i++) { // To remember and warn when the user enters the same letters
                    if (enteredLetters[i] == letterPrediction) {
                        previouslyEntered = true;
                        break;
                    }
                }
                if (previouslyEntered) {
                    cout << "\n You Have Entered This Letter Before!" << endl; // When you enter the same letter, you will be warned like this.
                    continue;
                }
                enteredLetters[numberOfLetters] = letterPrediction;
                numberOfLetters = numberOfLetters + 1;

                bool letterFound = false;
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] == letterPrediction) {
                        correctLetters[i] = true;
                        letterFound = true;
                    }
                }

                if (!letterFound) {
                    numberOfErrors = numberOfErrors + 1;
                    cout << "\n\n Your Guess Is Unfortunately Wrong. Your Remaining Right:" << (4 - numberOfErrors) << endl; // If one of the correct letters is not found, the user will be given a message like this and the user's right will be reduced.
                    aLatestStatusShow(numberOfErrors);
                }
                else {
                    cout << "\n\n Congratulations! Your Guess Is Correct." << endl; // When the letter is guessed correctly, a message will be given like this.
                }

                bool lettersAllCorrect = true;
                for (int i = 0; i < word.length(); i++) {
                    if (!correctLetters[i]) {
                        lettersAllCorrect = false;
                        break;
                    }
                }

                if (lettersAllCorrect) {
                    cout << "\n Congratulations!!! You Guessed The Word:" << word << endl; // The message that will be displayed on the screen if the user guesses all the letters correctly.
                    totalKnownWords++;
                    wordKnown = true; // We make it "true" because the word is known correctly.
                    break;
                }
            }
            else {
                cout << "\n Login Invalid."; // If anything other than a letter and 1 is entered, the user will be given an error message.
            }
        }
        if (!wordKnown) {
            cout << "\n Sorry! You Lost. Correct Word:" << word << endl; // If the word is unknown it will show the correct word.
        }

        cout << "\n\n Total Number Of Known Words:" << totalKnownWords << endl; // The total number of known words will be shown on the screen.
        cout << "\n *If You Want To Continue Press 2, If You Want To Exit Press Any Key:";
        string input;
        cin >> input;

        if (input != "2") {
            playGame = false; // If 2 is not pressed, the game is exited.
        }
    }

    cout << "Game Over! Thanks For Playing." << endl;

    return 0;
}