#include <iostream>
#include <ctime>
#include <string>

// Function prototypes
void printCard1(int num1, int num2, int num3, int sum); // Added earlier
void printCard2(int num1, int num2, int sum);           // Added earlier

// Base class for a card player
class CardPlayer {
protected:
    int num1, num2, sum, extraCard;
public:
    // Virtual function for drawing cards, will be overridden in derived classes
    virtual void drawCards() = 0;

    int getSum() const {
        return sum;
    }

    virtual void printCards() const = 0; // Polymorphic card printing
};

// Derived class for Banker
class Banker : public CardPlayer {
public:
    // Overriding the drawCards function for Banker
    void drawCards() override {
        num1 = rand() % 10 + 1;
        num2 = rand() % 10 + 1;
        sum = (num1 + num2) % 10;

        if (sum != 9 && sum != 8) {
            extraCard = rand() % 10 + 1;
            sum = (sum + extraCard) % 10;
        }
    }

    // Overriding the print function
    void printCards() const override {
        std::cout << "\n==============================\n";
        std::cout << "      =" << " BANKER'S CARD " << "=\n";
        std::cout << "==============================\n";

        if (sum == 9 || sum == 8) {
            printCard2(num1, num2, sum);
        } else {
            printCard1(num1, num2, extraCard, sum);
        }
    }
};

// Derived class for Player
class Player : public CardPlayer {
public:
    // Overriding the drawCards function for Player
    void drawCards() override {
        num1 = rand() % 10 + 1;
        num2 = rand() % 10 + 1;
        sum = (num1 + num2) % 10;

        if (sum != 9 && sum != 8) {
            extraCard = rand() % 10 + 1;
            sum = (sum + extraCard) % 10;
        }
    }

    // Overriding the print function
    void printCards() const override {
        std::cout << "\n==============================\n";
        std::cout << "      =" << " PLAYER'S CARD " << "=\n";
        std::cout << "==============================\n";

        if (sum == 9 || sum == 8) {
            printCard2(num1, num2, sum);
        } else {
            printCard1(num1, num2, extraCard, sum);
        }
    }
};

// Global function implementations
void printCard1(int num1, int num2, int num3, int sum) {
    std::cout << "=======\n";
    std::cout << "|     |\n";
    std::cout << "|  " << sum << "  |\n";
    std::cout << "|     |\n";
    std::cout << "=======\n";
    std::cout << "First Card " << num1 << "\n";
    std::cout << "Second Card " << num2 << "\n";
    std::cout << "Extra Card " << num3;
}

void printCard2(int num1, int num2, int sum) {
    std::cout << "=======\n";
    std::cout << "|     |\n";
    std::cout << "|  " << sum << "  |\n";
    std::cout << "|     |\n";
    std::cout << "=======\n";
    std::cout << "This is a natural win 8/9 \n";
    std::cout << "First Card " << num1 << "\n";
    std::cout << "Second Card " << num2;
}

// Other function prototypes and implementations
bool playAgain(char x, int money);
int winnerFunction(int bankerCard, int playerCard);
int declareWinner(int winner, int decision, int bet);

int main() {
    system("Color 2F"); // CLI color changer
    srand(time(NULL));   // Random number initialization

    // Variable declaration
    std::string name;
    int bet, decision, winner, prize;
    char play;
    bool logic = true;
    int money = 10000;

    std::cout << "==============================\n";
    std::cout << "To Start, please enter your card\n";
    std::cout << "Enter your name: ";
    getline(std::cin, name);

    std::cout << "\nGood evening, " << name << "\n";
    std::cout << "WELCOME TO VIRTUAL CASINO TABLE\n";
    std::cout << "=================================\n";

    do {
        std::cout << "Current balance, RS " << money << std::endl;
        std::cout << "1-BANKER \n2-PLAYER \n";
        std::cout << "Choose your bet: ";

        // Ensures valid input for bet
        while (!(std::cin >> decision) || (decision < 1 || decision > 2)) {
            std::cin.clear();
            std::cout << "\nChoose your bet ";
            std::cout << "\n1-BANKER \n2-PLAYER \n";
        }

        do {
            std::cout << "Place your bet, RS: ";
            std::cin >> bet;
        } while (bet > money);

        // Create Banker and Player objects
        CardPlayer* banker = new Banker();
        CardPlayer* player = new Player();

        // Draw cards for Banker and Player
        banker->drawCards();
        banker->printCards();

        player->drawCards();
        player->printCards();

        // Declaration of winner
        winner = winnerFunction(banker->getSum(), player->getSum());

        // Awards prize for winner, 1:1 for winner
        prize = declareWinner(winner, decision, bet);
        std::cout << "RS " << prize << std::endl;
        money += prize;
        std::cout << "Current Money, RS " << money << "\n\n";

        // Asks the user if they want to play again
        std::cout << "PLAY AGAIN? Y/N ";
        std::cin >> play;
        logic = playAgain(play, money);

        delete banker;
        delete player;

    } while (logic);

    return 0;
}

bool playAgain(char x, int money) {
    if (money > 0) {
        if (x == 'Y' || x == 'y') {
            return true;
        } else if (x == 'N' || x == 'n') {
            std::cout << "THANK YOU FOR PLAYING!\n";
            return false;
        }
    } else {
        std::cout << "Insufficient funds!\n";
        return false;
    }
}

int winnerFunction(int bankerCard, int playerCard) {
    std::cout << "\n==================================\n";
    if (bankerCard > playerCard) {
        std::cout << "\nBANKER WINS\n";
        return 1;
    } else if (bankerCard < playerCard) {
        std::cout << "\nPLAYER WINS\n";
        return 2;
    } else {
        std::cout << "\nDRAW\n";
        return 3;
    }
}

int declareWinner(int winner, int decision, int bet) {
    if (winner == decision) {
        std::cout << "YOU WIN!\n";
        return bet;
    } else if (winner == 3) {
        std::cout << "Tie Game!\n";
        return 0;
    } else {
        std::cout << "YOU LOSE!\n";
        return -bet;
    }
}
