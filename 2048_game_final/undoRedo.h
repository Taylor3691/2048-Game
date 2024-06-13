#pragma once
#include "menuGame.h"

struct  Stack
{
	GamePlay* prevGame;
	int winFlag;
	int loseFlag;
	Stack* next;
	Stack() {
		this->prevGame = NULL;
		this->winFlag = 0;
		this->loseFlag = 0;
		this->next = NULL;
	}
};

struct StackList
{
	Stack* head;
	int size;
	StackList() {
		this->head = NULL;
		this->size = 0;
	}
};

void doUndoRedo_Funtion(StackList& undoList, StackList& redoList, Stack* currentStack, GamePlay*& game, int& winFlag, int& loseFlag, char command);
bool isStackListEmpty(StackList list);
Stack* creatStack(GamePlay* game);
void push_frontStack(StackList& l, Stack* st);
void printStackList(StackList l);
void updateGame(Stack* currenStack, GamePlay* game, int& winFlag, int& loseFlag);
void releaseStackList(StackList& l);
void deleteStack(Stack* current);
