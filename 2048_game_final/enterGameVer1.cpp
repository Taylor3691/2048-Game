#include "coreGame.h"
#include "undoRedo.h"
void checkWin1(GamePlay* game, int& status, int& winFlag, high_resolution_clock::time_point& timeStart, chrono::seconds extraTime) {
	// Nếu đã win rôi thì không cần check win nữa
	if (winFlag == 1) return;
	int size = game->broad->sizeBroad;
	int move = 0;
	// tạo danh sách top 20
	AccountList l = creatTopList();
	// cập nhật thời gian chơi lần cuối
	game->currentAccount->playTime = getTimePlay(timeStart, extraTime);
	// cập nhật bxh lần cuối nếu thắng
	updateRank(l, game);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// nếu có ô đạt 2048, tức là bạn thắng
			if (game->broad->matrix[i][j] == 2048) {
				while (true) {
					system("cls");
					printScreenGame1(game);
					// in ra bảng xếp hạng nếu trong top 20
					if (areYouInTop20(l, game))printTopRank();
					// hỏi xem có tiếp tục chơi tiếp hay không
					cout << Yellow_text << "CONGRATULATION, YOU HAVE WON THE GAME, DO YOU WANT TO CONTINUE GAME" << reset_text << endl;
					if (move % 2 == 0) {
						cout << "-->" << White_back << Black_text << " YES" << reset_text << reset_backGround << endl;
						cout << "    NO" << endl;
					}
					else {
						cout << "    YES" << endl;
						cout << "-->" << White_back << Black_text << " NO" << reset_text << reset_backGround << endl;
					}
					char command = _getch();
					if (command == 'w' || command == 's') {
						move++;
					}
					else if (command == 'j' && move % 2 == 0) {
						// nếu đồng ý chơi tiếp thì đổi cờ
						winFlag = 1;
						return;
					}
					else if (command == 'j' && move % 2 != 0) {
						// nếu không đồng ý chơi tiếp thì tắt trạng thái game xoá khỏi resume vì đã xong game
						status = 0;
						saveRecord(game);
						return;
					}
				}
			}
		}
	}
}

void checkLose1(GamePlay* game, int& status, int& loseFlag, high_resolution_clock::time_point& timeStart, chrono::seconds extraTime) {
	int move = 0;
	// tạo danh sách top 20
	AccountList l = creatTopList();
	// cập nhạp thời gian chơi lần cuối
	game->currentAccount->playTime = getTimePlay(timeStart, extraTime);
	// update rank lần cuối trước khi thua
	updateRank(l, game);
	// Nếu thua game thì in ra bxh nếu trên bxh còn không thì phải trở về menu
	if (isGameLose(game)) {
		system("cls");
		printScreenGame1(game);
		cout <<Red_text<< "   GAME OVER !!! PRESS ANY KEY TO GO BACK TO MENU "<<reset_text << endl;
		status = 0;
		game->currentAccount->areStillPlaying = 0;
		if (areYouInTop20(l, game)) {
			saveRecord(game);
			printTopRank();
			_getch();
			return;
		}
		_getch();
	}
}

void exitGame1(int& status, GamePlay* game) {
	// hàm này giống hàm exit2
	GamePlay** list = creatAccountList();
	int index = -1;
	int move = 0;
	for (int i = 0; i < 5; i++) {
		if (list[i] != NULL && strcmp(list[i]->currentAccount->username, game->currentAccount->username) == 0) {
			index = i + 1;
			break;
		}
	}
	while (true) {
		system("cls");
		printScreenGame1(game);
		cout << endl << Green_46 << "ARE YOU SURE ABOUT QUIT GAME ? YOUR GAME WILL BE SAVED..." <<reset_text<< endl;
		if (move % 2 == 0) {
			cout << "--->" << White_back << Black_text << " YES" << reset_text << reset_backGround << endl;
			cout << "     NO" << endl;
		}
		else {
			cout << "     YES" << endl;
			cout << "--->" << White_back << Black_text << " NO " << reset_text << reset_backGround << endl;
		}
		char commnad = _getch();
		if (move % 2 == 0 && commnad == 'j') {
			saveGame(game, index);
			status = 0;
			break;
		}
		else if (move % 2 != 0 && commnad == 'j') {
			break;
		}
		else if (commnad == 'w' || commnad == 's') {
			move++;
		}
	}
	return;
}

void enterGameVer1(GamePlay* game, int& status) {
	// đặt 2 cờ hiệu win và lose để tiếp tục chơi nếu thắng và tiếp tục chơi khi thua
	int winFlag = 0;
	int loseFlag = 0;
	// khởi tạo bảng mới
	game->broad = creatBroad(game);
	// Lấy danh sách top 29
	AccountList l = creatTopList();
	// đặt thời gian bắt đầu chơi
	auto timeStart = high_resolution_clock::now();
	while (status) {
		system("cls");
		//in giao diện
		printScreenGame1(game);
		cout << endl << endl;
		char command = _getch();
		// thực hiện thao tác di chuyển
		if (command == 'w' || command == 's' || command == 'a' || command == 'd') {
			applyMove(command, game, timeStart,0s);
			// cập nhật bxh
			updateRank(l, game);
			// kiểm tra thắng chưa
			checkWin1(game, status, winFlag,timeStart,0s);
			// kiểm tra thua chưa
			checkLose1(game, status, loseFlag,timeStart,0s);
		}
		else if (command == 'e') {
			// thoát nếu như không muốn chơi
			exitGame1(status, game);
		};
	}
	// giải phóng game
	deleteGame(game);
	// giải phóng top 20
	deleteList(l);
	return;
}