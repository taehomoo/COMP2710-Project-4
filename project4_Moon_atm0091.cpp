/**
 * Andrew Moon
 * atm0091
 * project4_Moon_atm0091.cpp
 * g++ project4_Moon_atm0091.cpp
 *
 * I used the project 4 outline on canvas a lot to help set up the structure of my code. I also
 * used online resources, such as stackexchange, especially to help a lot regarding
 * thinking through how nodes are being implemented in this project. Also used it to
 * help determine how to receive input, when I'm using getline or scanning something in.
 */

#include <iostream>
#include <string>
using namespace std;

int questionCount;

struct TriviaNode {
    std::string triviaQ;
    std::string triviaA;
    int points;
    TriviaNode *next;
};

void initializeList(TriviaNode*& list);
void add(TriviaNode*& list);
void ask(TriviaNode*& list, int numQuestions);
void unitTestFunct();

#define UNIT_TESTING
#define GAME_VERSION
int main() {
#ifdef UNIT_TESTING
    unitTestFunct();
#endif
#ifdef GAME_VERSION
    bool check = true;
    string continueCheck;
    int valueY;
    int valueN;
    TriviaNode* linkList = nullptr;
    initializeList(linkList);
    std::cout << "\n*** Welcome to Andrew's trivia quiz game ***\n";
    TriviaNode* current = linkList;
    while(check) {
        add(linkList);
        cout << "Continue? (Y/N): ";
        getline(cin, continueCheck);
        valueY = continueCheck.compare("Y");
        valueN = continueCheck.compare("N");
        while (valueY != 0 && valueN != 0) {
                cout << "Please enter either Y or N to continue: ";
                getline(cin, continueCheck);
                valueY = continueCheck.compare("Y");
                valueN = continueCheck.compare("N");
        }
        if (valueY != 0) {
            check = false;
        }
    }
    ask(linkList, questionCount);
#endif
    return 0;
}


void initializeList(TriviaNode*& list) {
    questionCount = 3;
    TriviaNode* Node = new TriviaNode;
    Node->triviaQ = "How long was the shortest war on record? (Hint: how many minutes)";
    Node->triviaA = "38";
    Node->points = 100;
    Node->next = new TriviaNode;

    list = Node;
    Node = list->next;
    Node->triviaQ = "What was Bank of America's original name? (Hint: Bank"
                           "of Italy or Bank of Germany)";
    Node->triviaA = "Bank of Italy";
    Node->points = 50;
    Node->next = new TriviaNode;

    Node = Node->next;
    Node->triviaQ = "What is the best-selling video game of all time? (Hint: "
                           "Call of Duty or Wii Sports)?";
    Node->triviaA = "Wii Sports";
    Node->points = 20;
    Node->next = nullptr;
}

void add(TriviaNode*& list) {
    std::string stringCheck;
    TriviaNode* newNode = new TriviaNode;
    std::cout << "Enter a question: ";
    getline(std::cin, newNode->triviaQ);
    std::cout << "Enter an answer: ";
    std::getline (std::cin, newNode->triviaA);
    std::cout << "Enter award points: ";
    cin >> newNode->points;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    TriviaNode* temp = list;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = nullptr;
    questionCount++;
}

void ask (TriviaNode*& list, int numQuestions) {
    string answerQ;
    int totalPoints = 0;
    if (list == nullptr) {
        return;
    }
    if (numQuestions <= 0) {
        cout << "Warning - the number of trivia to be asked must equal to or be larger"
                "than 1.\n";
        return;
    }
    else if (questionCount < numQuestions) {
        cout << "Warning - there is only " << questionCount << " trivia in the list.\n";
        return;
    }
    for (int i = 0; i < numQuestions; i++) {
        cout << "Question: " << list->triviaQ;
        cout << "\nAnswer: ";
        getline(cin, answerQ);
        if (answerQ.compare(list->triviaA) == 00) {
            cout << "Your answer is correct. You receive " << list->points << " points.";
            totalPoints += list->points;
            cout << "\nYour total points: " << totalPoints;
            cout << "\n\n";
        } else {
            cout << "Your answer is wrong. The correct answer is: " << list->triviaA;
            cout << "\nYour total points: " << totalPoints;
            cout << "\n\n";
        }
        list = list->next;
    }
}

void unitTestFunct() {
    TriviaNode* Node = new TriviaNode;
    initializeList(Node);
    cout << "*** This is a debugging version ***\n";
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message.\n";
    ask(Node, 0);
    cout << "\nCase 1 Passed\n\n";

    TriviaNode* Node1 = new TriviaNode;
    initializeList(Node1);
    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an "
            "incorrect answer.\n";
    ask(Node1, 1);
    cout << "\nCase 2.1 passed\n\n";

    TriviaNode* Node2 = new TriviaNode;
    initializeList(Node2);
    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a "
            "correct answer.\n";
    ask(Node2, 1);
    cout << "\nCase 2.2 passed\n\n";

    TriviaNode* Node3 = new TriviaNode;
    initializeList(Node3);
    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list.\n";
    ask(Node3, 3);
    cout << "\nCase 3 passed\n\n";

    TriviaNode* Node4 = new TriviaNode;
    initializeList(Node4);
    cout << "Unit Test Case 4: Ask 5 questions in the linked list.\n";
    ask(Node4, 5);
    cout << "\nCase 4 passed\n\n";

    cout << "*** End of the Debugging Version ***";
    return;
}

