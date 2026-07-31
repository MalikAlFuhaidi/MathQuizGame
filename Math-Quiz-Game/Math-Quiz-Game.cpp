#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4, };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5, };

struct stQuestions
{
    short Number1 = 0;
    short Number2 = 0;

    enOperationType OperationType;
    enQuestionsLevel QuizzLevel;

    short PlayerAnswer = 0;
    short CorrectAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestions QuestionList[100];

    short NumberOfQuestions = 0;
    short NumberOfRightAnswer = 0;
    short NumberOfWrongAnswer = 0;
    enOperationType OpType;
    enQuestionsLevel QuestionsLevel;
    bool IsPass = false;
};

short RandomNumber(short From, short To)
{
    // Function to generate Random Number 

    int RandomNum = rand() % (To - From + 1) + From;

    return RandomNum;
}

short ReadHowManyQuestions()
{
    short Number = 1;

    do
    {
        cout << "How Many Questions Do You Want to answer? ";
        cin >> Number;

    } while (Number < 1);

    return Number;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuesLevel = 1;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuesLevel;
    } while (QuesLevel < 1 || QuesLevel > 4);

    return (enQuestionsLevel)QuesLevel;
}

enOperationType ReadOpType()
{
    short OpType = 1;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

string GetOpTypeSymple(enOperationType OpType)
{
    string Op[5] = { "+", "-", "*", "/", "Max" };
    return Op[OpType - 1];
}

enOperationType GetRandomOpType()
{
    return (enOperationType)RandomNumber(1, 4);
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mul:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestions GenerateQuestion(enOperationType OpType, enQuestionsLevel QuestionLevel)
{
    stQuestions Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOpType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuizzLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuizzLevel = QuestionLevel;
        return Question;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(1, 100);
        Question.Number2 = RandomNumber(1, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuizzLevel = QuestionLevel;
        return Question;
    }
    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.OpType, Quizz.QuestionsLevel);
    }
}

void PrintTheQuestion(stQuizz Quizz, int QuestionNumber)
{
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymple(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
    cout << "------------------\n";

}

short ReadQuestionAnswer()
{
    short Number = 0;
    cin >> Number;

    return Number;
}

void SetScreenColor(bool AnswerResult)
{
    if (AnswerResult)
        system("color 2F");
    else
        system("color 4F");
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, int QuestionNumber)
{
    cout << '\n';
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "Wrong Answer :-(\n";
        cout << "The right answer is : ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;

        cout << "Right Answer :-)\n";
    }
    cout << '\n';

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswer > Quizz.NumberOfWrongAnswer);

    /*if (Quizz.NumberOfRightAnswer > Quizz.NumberOfWrongAnswer)
        Quizz.IsPass = true;
    else
        Quizz.IsPass = false;*/
}

string GetFinalResultsText(bool IsPass)
{
    if (IsPass)
    {
        return "Pass :-)";
    }
    else
    {
        return "Fail :-(";
    }
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "---------------------------\n\n";
    cout << " Final Results is " << GetFinalResultsText(Quizz.IsPass);
    cout << "\n---------------------------\n\n";

    //cout << "Number of Questions: " << Quizz.NumberOfQuestions << end
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);

    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    // Seeds the random number generator in C++, Called only once.
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
