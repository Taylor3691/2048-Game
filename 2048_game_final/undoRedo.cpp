#include "undoRedo.h"
#include "coreGame.h"

Stack* pop_backStack(StackList& l) {
	//hàm xoá node đầu và trả về node đó
	if (l.head != NULL) {
		Stack* res = l.head;
		l.head = l.head->next;
		res->next = NULL;
		l.size--;
		return res;
	}
	return NULL;
}

void push_frontStack(StackList& l, Stack* st) {
	// hàm thêm đàu vào thùng
	if (l.head == NULL) {
		l.head = st;
		l.size++;
	}
	else {
		st->next = l.head;
		l.head = st;
		l.size++;
	}
}

void printStackList(StackList l) {
	// hàm in những thứ có trung thùng
	if (l.head != NULL) {
		Stack* tam = l.head;
		int size = tam->prevGame->broad->sizeBroad;
		while (tam != NULL) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					cout << tam->prevGame->broad->matrix[i][j] << " ";
				}
				cout << endl;
			}
			tam = tam->next;
			cout << endl << endl;
		}
	}
}

GamePlay* creatPrevGame(GamePlay* game) {
	// hàm tạo một bản sao của trạng thái game hiện tại
	GamePlay* res = new GamePlay;
	strcpy_s(res->currentAccount->username, 256, game->currentAccount->username);
	strcpy_s(res->currentAccount->password, 256, game->currentAccount->password);
	res->currentAccount->score = game->currentAccount->score;
	res->currentAccount->playTime = game->currentAccount->playTime;
	res->currentAccount->areStillPlaying = game->currentAccount->areStillPlaying;
	res->broad->sizeBroad = game->broad->sizeBroad;
	int size = game->broad->sizeBroad;
	res->broad->undoRedoMode = game->broad->undoRedoMode;
	int** broad = new int* [size];
	for (int i = 0; i < size; i++) {
		broad[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			broad[i][j] = game->broad->matrix[i][j];
		}
	}
	res->broad->matrix = broad;
	return res;
}

Stack* creatStack(GamePlay* game) {
	// hàm tạo một node bản sao 
	Stack* current = new Stack;
	current->prevGame = creatPrevGame(game);
	int size = current->prevGame->broad->sizeBroad;
	return current;
}

bool isStackListEmpty(StackList list) {
	// hàm kiểm tra xem thùng có rỗng không
	if (list.head == NULL || list.size == 0) {
		return 1;
	}
	return 0;
}

void releaseStackList(StackList& l) {
	// giải phóng thùng 
	if (l.head != NULL) {
		Stack* current = l.head;
		while (l.head != NULL) {
			l.head = l.head->next;
			deleteStack(current);
			current = l.head;
		}
	}
	return;
}


void deleteStack(Stack* current) {
	// xoá node
	deleteGame(current->prevGame);
	delete current;
	current = NULL;
}

void updateGame(Stack* currenStack, GamePlay* game, int& winFlag, int& loseFlag) {
	// hàm này cập nhật trạng thái game mới bằng các sao chép dữ liệu
	int size = game->broad->sizeBroad;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			game->broad->matrix[i][j] = currenStack->prevGame->broad->matrix[i][j];
		}
	}
	game->currentAccount->areStillPlaying = currenStack->prevGame->currentAccount->areStillPlaying;
	game->currentAccount->score = currenStack->prevGame->currentAccount->score;
	winFlag = currenStack->winFlag;
	loseFlag = currenStack->loseFlag;
	// sau khi sao chép xong thì xoá cái node đó
	deleteStack(currenStack);
	return;
}

void doUndoRedo_Funtion(StackList& undoList, StackList& redoList, Stack* currentStack, GamePlay*& game,int& winFlag,int& loseFlag, char command) {
	if (command == 'u') {
		// kiêm tra thùng có rỗng không
		if (isStackListEmpty(undoList)) {
			// nếu rỗng thì không undo được
			cout << " YOU CAN NOT UNDO ANYMORE... PRESS ANY KEY TO CONTINUE " << endl;
			_getch();
			return;
		}
		// nếu không rỗng thì
		else {
			// lấy node trên cùng của undoList
			Stack* prevStack = pop_backStack(undoList);
			// đẩy node hiện tại vào redoList
			push_frontStack(redoList, currentStack);
			// cật nhập trạng thái game mới
			updateGame(prevStack,game,winFlag,loseFlag);
		}
	}
	else if (command == 'r') {
		// kiêm tra thùng có rỗng không
		if (isStackListEmpty(redoList)) {
			// nếu rỗng thì không redo được
			cout << " YOU CAN NOT REDO ANYMORE... PRESS ANY KEY TO CONTINUE...." << endl;
			_getch();
			return;
		}
		else {
			// lấy node trên cùng của redoList
			Stack* nextStack = pop_backStack(redoList);
			// đẩy node hiện tại vào undoList
			push_frontStack(undoList, currentStack);
			// cật nhập trạng thái game mới
			updateGame(nextStack, game, winFlag, loseFlag);
		}
	}
}