#include "millionaire.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

millionaire::millionaire(void)
{
	int tier = 1;
	int round = 1;
	int score = 0;
	int life1 = 0 ;
	int life2 = 0;
	bool lifeline = false;
	
	return;
}

void millionaire::play(void)
{
	welcome();
	create_question_pool();
	while(1);
	question_read();
	final_screen();
	while(1);
	return;
}

void millionaire::welcome(void)
{
	std::string response;

	cout << "Welcome to Who Wants to be a Millionaire?" << endl;
	cout << "Are you ready to play? (Type yes or no)" << endl;
	
	while(1)
	{
		getline(std::cin, response, '\n' );
		if (response == "yes")
			{
				cout << "Let's begin!" << endl << endl;
				return;
			}
		else if (response == "no")
			{
				cout << "Maybe next time!" << endl;
				cin.get();
				exit(1);
			}
		else cout << "You must type yes or no" << endl;
	}
}

void millionaire::question_read(void)
{
	std::string response;
	ifstream questions ("Flowers_Questions");
	string question, A, B, C, D, answer;

	tier = 1;
	round = 1;
	lifeline = false;

	if (questions.is_open())
		{
			while ( questions.good() )
				{
					getline (questions, question);
					getline (questions, A);
					getline (questions, B);
					getline (questions, C);
					getline (questions, D);
					getline (questions, answer);

					while(1)
					{
					cout << question << endl << A << endl << B << endl << C << endl << D << endl;
					cout << endl;
					cout << "Enter an answer or type Lifeline to get some help" << endl;
					getline(std::cin, response, '\n' );
					if (response == "Lifeline")
					{
						cout << "Do you want to use your Lifeline to eliminate half the answer choices?" << endl;
						getline(std::cin, response, '\n' );
						if (response == "yes")
						{
							if (!lifeline)
							{
							cout << endl;
							cout << question << endl;
							life_line(A, B, C, D, answer);
							cout << endl << "Enter an answer" << endl;
							getline(std::cin, response, '\n' );
							lifeline = true;
							break;
							}
						else
							{
								cout << endl << "You have no more Lifelines! Here are the question and answer choices again:" << endl << endl;
							}
						}
						else cout << endl << "Here the question and answer choices again:" << endl << endl;
					}
					else break;
					}
					if (check_answer(answer, response)) adjust_score();
					else return;
					if (round == 16) break;
					else
						{
							cout << "Press Enter to proceed to the next question" << endl;
							cin.get();
						}
				}
			questions.close();
		}
	return;
}

bool millionaire::check_answer(string answer, string response)
{
	if (answer == response)
		{
			cout << "You got it right!" << endl;

			return true;
		}	
	else
		{
			cout << "You got it wrong!" << endl;

			return false;
		}
}

void millionaire::adjust_score(void)
{
	switch (round)
		{
			case 1:
				score = 100;
				break;
			case 2:
				score = 200;
				break;
			case 3:
				score = 300;
				break;
			case 4:
				score = 500;
				break;
			case 5:
				score = 1000;
				tier++;
				break;
			case 6:
				score = 2000;
				break;
			case 7:
				score = 4000;
				break;
			case 8:
				score = 8000;
				break;
			case 9:
				score = 16000;
				break;
			case 10:
				score = 32000;
				tier++;
				break;
			case 11:
				score = 64000;
				break;
			case 12:
				score = 125000;
				break;
			case 13:
				score = 250000;
				break;
			case 14:
				score = 500000;
				break;
			case 15:
				score = 1000000;
				tier++;
				break;
			default:
				
				break;
		}

	round++;
	cout << "Your total sum is $" << score << endl;
	return;
}

void millionaire::final_screen(void)
{
	cout << endl << "The game is over, thanks for playing!" << endl;
	switch (tier)
		{
			case 1:
				cout << "You have won first tier money!" << endl;
				break;
			case 2:
				cout << "You have won second tier money!" << endl;
				break;
			case 3:
				cout << "You have won third tier money!" << endl;
				break;
			default: ;
		}
	return;
}

void millionaire::life_line(string A, string B, string C, string D, string answer)
{
	int answer_;
	if (answer == "A") answer_ = 1;
	else if (answer == "B") answer_ = 2;
	else if (answer == "C") answer_ = 3;
	else answer_ = 4;

	while(1)
	{
	life1 = rand () % 4 + 1;
	while(1)
	{
		life2 = rand() % 4 + 1;
		if (life2 != life1) break;
	}
	if (life1 == answer_) break;
	else if (life2 == answer_) break;
	}

	if (life1 < life2)
	{
		if (life1 == 1) cout << A << endl;
		else if (life1 == 2) cout << B << endl;
		else if (life1 == 3) cout << C << endl;
		else cout << D << endl;
		if (life2 == 1) cout << A << endl;
		else if (life2 == 2) cout << B << endl;
		else if (life2 == 3) cout << C << endl;
		else cout << D << endl;
	}
	else
	{
		if (life2 == 1) cout << A << endl;
		else if (life2 == 2) cout << B << endl;
		else if (life2 == 3) cout << C << endl;
		else cout << D << endl;
		if (life1 == 1) cout << A << endl;
		else if (life1 == 2) cout << B << endl;
		else if (life1 == 3) cout << C << endl;
		else cout << D << endl;
	}
	
	return;
}

void millionaire::create_question_pool(void)
{
	ifstream questions ("Flowers_Questions");
	question_node temp, question;
	list<question_node> temp_list;
	list<question_node>::iterator temp_it;

	int random_question;

	if (questions.is_open())
		{
			while ( questions.good() )
				{
					getline(questions, temp.question);
					getline(questions, temp.A);
					getline(questions, temp.B);
					getline(questions, temp.C);
					getline(questions, temp.D);
					getline(questions, temp.answer);
					temp.used = false;
					temp_list.push_front(temp);
				}
			questions.close();
		}
//	for (it = question_pool.begin(); it != question_pool.end(); it++ );

	for (int i = 0; i <= 14; i++)
	{
		while(1)
		{
		random_question = rand () % temp_list.size() + 1;
		temp_it = temp_list.begin();
		for (int i = 1; i < random_question ; i++) temp_it++;
		if (temp_it->used == false)
		{
			temp_it-> used = true;
			break;
		}
		}
		question_pool.push_back(*temp_it);
	}
	return;
}