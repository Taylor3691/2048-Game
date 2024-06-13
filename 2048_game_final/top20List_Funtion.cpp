#include "coreGame.h"

void top20List_Funtion(int status) {
	// hàm này để in danh sách top 20
	system("cls");
	cout << endl;
	cout <<White_back<<Blue_27<< "\t\t\t\t\t\t\t\t TOP 20 LIST " <<reset_backGround<<reset_text<< endl;
	cout << endl;
	printTopRank();
	_getch();
	return;
}