#include "header.h"
#include "menuGame.h"

void menuGame() {
	srand((unsigned int)time(NULL));
	int status = 1;
	int move = 0;
	// Khi khởi động game, mặc định size broad là 4, undo redo tắt
	defaultSetting();
	while (true) {
		system("cls");
		printMenuUI(move);
		char command = _getch();
		if (command == 'w' && move > 0) {
			move--;
		}
		else if (command == 's' && move < 4) {
			move++;
		}
		else if (command == 'j' && move % 5 == 0) {
			// chức năng tạo game mới
			newGame_Funtion(status);
		}
		else if (command == 'j' && move % 5 == 1) {
			// chức năng chơi tiếp
			resume_Funtion(status);
		}
		else if (command == 'j' && move % 5 == 2) {
			// chức năng tuỳ chỉnh size, undo redo
			gameSetting_Funtion(status);
		}
		else if (command == 'j' && move == 3) {
			// chức năng coi bảng xếp hạng
			top20List_Funtion(status);
		}
		else if (command == 'j' && move == 4) {
			return;
		}
	}
	return;
}