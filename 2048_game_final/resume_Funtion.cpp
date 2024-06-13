#include "undoRedo.h"
#include "coreGame.h"
GamePlay* readOneAccount(int index) {
	// hàm dọc thông tin bao gòm chế độ undo redo, bảng cũ, điểm cũ, tên , mật khẩu
	GamePlay* game = NULL;
	string filename = "account" + to_string(index) + ".bin";
	fstream filein;
	filein.open(filename, ios::in | ios::binary);
	int size = 0;
	if (filein) {
		// Đọc cờ để biết xem file có rỗng ko
		filein.read(reinterpret_cast<char*>(&size), 4);
		if (filein.eof()) {
			// nếu file rỗng trả về game NULL tức là không thể resume
			return game;
		}
		else {
			// nếu file ko rỗng
			game = new GamePlay;
			// size của bảng
			game->broad->sizeBroad = size;
			// đọc chế độ undo redo
			filein.read(reinterpret_cast<char*>(&game->broad->undoRedoMode), 4);
			// cấp phát bảng
			game->broad->matrix = new int* [size];
			for (int i = 0; i < size; i++) {
				game->broad->matrix[i] = new int[size];
			}
			// đọc bảng cũ 
			for (int i = 0; i < size; i++) {
				filein.read(reinterpret_cast<char*>(game->broad->matrix[i]), 4 * size);
			}
			// đọc tài khoản, điểm, thời gian chơi,...
			filein.read(reinterpret_cast<char*>(game->currentAccount->username), 256);
			filein.read(reinterpret_cast<char*>(game->currentAccount->password), 256);
			filein.read(reinterpret_cast<char*>(&game->currentAccount->score), 4);
			filein.read(reinterpret_cast<char*>(&game->currentAccount->playTime), 4);
			filein.read(reinterpret_cast<char*>(&game->currentAccount->areStillPlaying), 4);
			return game;
		}
	}
	else cout << "CANT OPEN" << endl;
	return game;
}

void enterGameResumeVer2(GamePlay* game, int& status) {
	//Giống hàm enterGameVer2
	int winFlag = 0;
	int loseFlag = 0;
	AccountList l = creatTopList();
	StackList undoList, redoList;
	Stack* currentStack = NULL;
	// Lấy thời gian chơi cũ ra
	auto extraTime = chrono::seconds(game->currentAccount->playTime);
	// reset thời gian chơi
	game->currentAccount->playTime = 0;
	auto timeStart = high_resolution_clock::now();
	// làm như vậy để có thể khi chơi cộng thời gian chơi cũ với thời gian chơi mới
	while (status) {
		currentStack = creatStack(game);
		system("cls");
		printScreenGame2(game);
		cout << endl << endl;
		char command = _getch();
		if (command == 'w' || command == 's' || command == 'a' || command == 'd') {
			applyMove(command, game, timeStart,extraTime);
			if (isBroadChanged(currentStack->prevGame->broad->matrix, game->broad->matrix, game->broad->sizeBroad)) {
				releaseStackList(redoList);
				push_frontStack(undoList, currentStack);
			}
			updateRank(l, game);
			checkWin2(game, status, winFlag,timeStart,0s);
			checkLose2(game, status, loseFlag,timeStart,0s);
			if (status == 0) {
				releaseStackList(undoList);
				releaseStackList(redoList);
			}
		}
		else if (command == 'e') {
			exitGame2(status, game);
		}
		else if (command == 'u' || command == 'r') {
			doUndoRedo_Funtion(undoList, redoList, currentStack, game, winFlag, loseFlag, command);
			game->currentAccount->playTime = getTimePlay(timeStart, 0s);
			updateRank(l, game);
		}
	}
	deleteGame(game);
	deleteList(l);
}

void enterGameResumeVer1(GamePlay* game, int& status) {
	// Giống hàm enterGameVer1
	int winFlag = 0;
	int loseFlag = 0;
	game->broad = creatBroad(game);
	AccountList l = creatTopList();
	// Lấy thời gian chơi cũ ra
	auto extraTime = chrono::seconds(game->currentAccount->playTime);
	// reset thời gian chơi
	game->currentAccount->playTime = 0;
	auto timeStart = high_resolution_clock::now();
	// làm như vậy để có thể khi chơi cộng thời gian chơi cũ với thời gian chơi mới
	Stack* currentStack = NULL;
	while (status) {
		system("cls");
		printScreenGame1(game);
		cout << endl << endl;
		char command = _getch();
		if (command == 'w' || command == 's' || command == 'a' || command == 'd') {
			applyMove(command, game, timeStart, extraTime);
			updateRank(l, game);
			checkWin1(game, status, winFlag,timeStart,0s);
			checkLose1(game, status, loseFlag,timeStart,0s);
		}
		else if (command == 'e') {
			exitGame1(status, game);
		};
	}
	deleteGame(game);
	deleteList(l);
	return;
}




void resume_Funtion(int& status) {
	// Đọc file lấy danh sách 5 tài khoản đang trong resume
	GamePlay** list = creatAccountList();
	// Khởi tạo Game
	GamePlay* game = NULL;
	int move = 0;
	int flag = 1;
	while (flag) {
		system("cls");
		// In danh sách tài khoản
		printAccountList(list, move);
		char command = _getch();
		if (command == 'w' && move > 0) {
			move--;
		}
		else if (command == 's' && move < 4) {
			move++;
		}
		else if (command == 'j') {
			// Nếu chọn vào chỗ EMPTY thì sẽ ko thể resune
			if (list[move % 5] == NULL) {
				cout << "THIS ACCOUNT CAN NOT RESUME !!!" << endl;
				_getch();
			}
			else {
				int step = 0;
				while (true) {
					system("cls");
					printAccountList(list, move);
					// Xác nhận xem có thực sự muốn chọn không
					cout << endl << "\t\t\t\t\t\t" << Red_text << "ARE YOU SURE ABOUT CONTINUE PLAYING THIS ACCOUNT ? " << reset_text << endl << endl;
					if (step % 2 == 0) {
						cout << "\t\t\t\t\t\t\t\t--->"<<White_back<<Black_text<<" YES " <<reset_text<<reset_backGround<< endl;
						cout << "\t\t\t\t\t\t\t\t     NO " << endl;
					}
					else {
						cout << "\t\t\t\t\t\t\t\t     YES " << endl;
						cout << "\t\t\t\t\t\t\t\t--->"<< White_back << Black_text <<"  NO " << reset_text << reset_backGround << endl;
					}
					char command = _getch();
					if (command == 'w' || command == 's') {
						step++;
					}
					else if (command == 'j' && step % 2 == 0) {
						// Nếu đã xác nhận xong, đọc thông tin tài khoản và thông tin game đã chơi trước để set up chuẩn bị chơi game
						game = readOneAccount(move % 5 + 1);
						cout << "\t\t\t\t\t\t"<<Yellow_text<<"YOUR GAME WILL BE SET UP, PRESS ANY KEY TO CONTINUE...."<<reset_text<< endl;
						_getch();
						if (game->broad->undoRedoMode == 1) {
							// Vào game chế độ undo bật
							enterGameResumeVer2(game, status);
						}
						else {
							// vào game chế độ undo tắt
							enterGameResumeVer1(game,status);
						}
						
						flag = 0;
						break;
					}
					else if (command == 'j' && step % 2 != 0) {
						break;
					}
				}
			}
		}
	}
	status = 1;
	return;
}