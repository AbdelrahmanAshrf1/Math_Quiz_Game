#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOP = 5 };
enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

struct stQuestionList
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = true;
};

struct stQuizz
{
	stQuestionList QuestionList[100];
	short NumberOfQuestions;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool IaPass = true;
};

short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How many Questions do you want to Answer ?";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 100);
	return NumberOfQuestions;
}

enOperationType ReadOperationType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);
	return (enOperationType)OpType;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}

enOperationType GetRandomOperationType()
{
	short OpType = 0;

	OpType = RandomNumber(1, 4);

	return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case Add:
		return Number1 + Number2;
	case Sub:
		return Number1 - Number2;
	case Mult:
		return Number1 * Number2;
	case Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestionList GenerateQuestion( enQuestionLevel QuestionLevel,enOperationType OpType)
{
	stQuestionList Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOP)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(100, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;		
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Questions = 0; Questions < Quizz.NumberOfQuestions; Questions++)
	{
		Quizz.QuestionList[Questions] = GenerateQuestion( Quizz.QuestionLevel,Quizz.OperationType);
	}
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default :
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevel[4] = { "EasyLevel","MedLevel","HardLevel","Mix" };
	return arrQuestionLevel[QuestionLevel - 1];
}

void PrintQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_____________\n";
}

int ReadQuestionAnswer()
{
	int PlayerAnswer = 0;
	cin >> PlayerAnswer;
	return PlayerAnswer;
}

void SetScreenColor(bool IsRight)
{
	if (IsRight)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-(\n";
		cout << "The right Answer is : ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = true;
		Quizz.NumberOfRightAnswer++;

		cout << "Right Answer :-)\n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.IaPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n_______________________________________\n\n";
	cout << "Final Result is : " << GetFinalResultText(Quizz.IaPass);
	cout << "\n_______________________________________\n\n";

	cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level      : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType              : " << GetOpTypeSymbol(Quizz.OperationType) << endl;
	cout << "Number Of Right Answer : " << Quizz.NumberOfRightAnswer << endl;
	cout << "Number Of Wrong Answer : " << Quizz.NumberOfWrongAnswer << endl;
	cout << "_______________________________________\n\n";
}

void PlayMathGame()
{
	stQuizz	Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.OperationType = ReadOperationType();
	Quizz.QuestionLevel = ReadQuestionLevel();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);

	PrintQuizzResult(Quizz);
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

		cout << "Do you want to play again ? Y/N?\n";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}