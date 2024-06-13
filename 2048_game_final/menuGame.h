#pragma once
#include "header.h"
struct Account {
	char* username;
	char* password;
	int score;
	int playTime;
	int areStillPlaying;
	Account* next;
	Account() {
		this->username = new char[256];
		this->password = new char[256];
		this->score = 0;
		this->playTime = 0;
		this->next = NULL;
		this->areStillPlaying = 1;
	}
};

struct AccountList {
	Account* head;
	int size;
	AccountList() {
		this->head = NULL;
		this->size = 0;
	}
};

struct Broad
{
	int** matrix;
	int sizeBroad;
	int undoRedoMode;
	Broad() {
		this->matrix = NULL;
		this->sizeBroad = -1;
		this->undoRedoMode = 0;
	}
};

struct GamePlay
{
	Account* currentAccount;
	Broad* broad;
	GamePlay() {
		this->broad = new Broad;
		this->currentAccount = new Account;
	}
};


void printMenuUI(int move);
void menuGame();
void newGame_Funtion(int& status);
void gameSetting_Funtion(int status);
void top20List_Funtion(int status);
void resume_Funtion(int& status);
void defaultSetting();
