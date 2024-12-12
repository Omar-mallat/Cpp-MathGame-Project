// MathGame Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;

// Enums for operation types and question levels
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
enum enQuestionLevel { EasyLevel = 1, MediumLevel = 2, HardLevel = 3, Mix = 4 };

// Structs for questions and quizzes
struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    int correctAnswer = 0;
    int playerAnswer = 0;
    bool AnswerResult = false;
};

struct StQuiz {
    stQuestion QuestionList[100];
    short NbOfQuestions;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    short NbOfWrongAnswer = 0;
    short NbOfRightAnswer = 0;
    bool isPass = false;
};

// Utility functions
string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
    string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestion() {
    short NbOfQuestion;
    do {
        cout << "How Many Questions Do You Want To Answer? ";
        cin >> NbOfQuestion;
    } while (NbOfQuestion < 1);
    return NbOfQuestion;
}

enQuestionLevel ReadQuestionLevel() {
    int QuestionLevel;
    do {
        cout << "Enter Question Level: Easy [1], Medium [2], Hard [3], Mix [4]: ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType() {
    int OpType;
    do {
        cout << "Enter The Operation Type: Add [1], Sub [2], Mul [3], Div [4], MixOp [5]: ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

void SetScreenColor(bool Right) {
    if (Right)
        system("color 2F"); // Turn screen green
    else {
        system("color 4F"); // Turn screen red
        cout << "\a";
    }
}

string GetOperationSymbol(enOperationType opType) {
    switch (opType) {
    case enOperationType::Add: return "+";
    case enOperationType::Sub: return "-";
    case enOperationType::Mul: return "x";
    case enOperationType::Div: return "/";
    default: return "Mix";
    }
}

int Calculator(int Number1, int Number2, enOperationType opType) {
    switch (opType) {
    case enOperationType::Add: return Number1 + Number2;
    case enOperationType::Sub: return Number1 - Number2;
    case enOperationType::Mul: return Number1 * Number2;
    case enOperationType::Div: return Number1 / Number2;
    default: return Number1 + Number2;
    }
}

enOperationType getRandomOperation() {
    return (enOperationType)RandomNumber(1, 4);
}

stQuestion GenerateQuestion(enOperationType opType, enQuestionLevel questionLevel) {
    stQuestion Question;

    if (questionLevel == enQuestionLevel::Mix) {
        questionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }

    if (opType == enOperationType::MixOp) {
        opType = getRandomOperation();
    }

    Question.OpType = opType;

    switch (questionLevel) {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionLevel::MediumLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.correctAnswer = Calculator(Question.Number1, Question.Number2, Question.OpType);
    Question.QuestionLevel = questionLevel;

    return Question;
}

void PrintTheQuestion(StQuiz& Quiz, short QuestionNumber) {
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quiz.NbOfQuestions << "]\n\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << " ";
    cout << GetOperationSymbol(Quiz.QuestionList[QuestionNumber].OpType) << " ";
    cout << Quiz.QuestionList[QuestionNumber].Number2 << "\n_________\n";
}

void GenerateQuiz(StQuiz& Quiz) {
    for (short i = 0; i < Quiz.NbOfQuestions; ++i) {
        Quiz.QuestionList[i] = GenerateQuestion(Quiz.OpType, Quiz.QuestionLevel);
    }
}

int getPlayerAnswer() {
    int playerAnswer;
    cin >> playerAnswer;
    return playerAnswer;
}

void CorrectTheQuestionAnswer(StQuiz& Quiz, short QuestionNumber) {
    if (Quiz.QuestionList[QuestionNumber].playerAnswer != Quiz.QuestionList[QuestionNumber].correctAnswer) {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NbOfWrongAnswer++;
        cout << "Wrong Answer :-( \n";
        cout << "The right answer is: " << Quiz.QuestionList[QuestionNumber].correctAnswer << "\n";
    }
    else {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NbOfRightAnswer++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(StQuiz& Quiz) {
    for (short i = 0; i < Quiz.NbOfQuestions; i++) {
        PrintTheQuestion(Quiz, i);
        Quiz.QuestionList[i].playerAnswer = getPlayerAnswer();
        CorrectTheQuestionAnswer(Quiz, i);
    }
    Quiz.isPass = (Quiz.NbOfRightAnswer >= Quiz.NbOfWrongAnswer);
}

string GetFinalResultsText(bool Pass) {
    return Pass ? "PASS :-)" : "FAIL :-(";
}

void PrintQuizResults(StQuiz Quiz) {
    cout << "\n______________________________\n\n";
    cout << "Final Results: " << GetFinalResultsText(Quiz.isPass) << "\n";
    cout << "______________________________\n\n";
    cout << "Number of Questions: " << Quiz.NbOfQuestions << "\n";
    cout << "Questions Level: " << GetQuestionLevelText(Quiz.QuestionLevel) << "\n";
    cout << "Operation Type: " << GetOperationSymbol(Quiz.OpType) << "\n";
    cout << "Number of Right Answers: " << Quiz.NbOfRightAnswer << "\n";
    cout << "Number of Wrong Answers: " << Quiz.NbOfWrongAnswer << "\n";
    cout << "______________________________\n";
}

// Main game logic
void PlayMathGame() {
    StQuiz Quiz;
    Quiz.NbOfQuestions = ReadHowManyQuestion();
    Quiz.QuestionLevel = ReadQuestionLevel();
    Quiz.OpType = ReadOperationType();
    GenerateQuiz(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResults(Quiz);
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain;
    do {
        ResetScreen();
        PlayMathGame();
        cout << "\nDo you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (tolower(PlayAgain) == 'y');
}

int main() {
    srand((unsigned)time(NULL)); // Seed the random number generator
    StartGame();
    return 0;
}
