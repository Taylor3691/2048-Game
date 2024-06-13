#include "header.h"
#include "menuGame.h"

string undoRedoMode[] = { "NO","YES" };

void defaultSetting() {
	// hàm này để ghi vào file chế độ mặc định là size broad = 4 và chế độ undo redo tắt
	fstream fileout;
	int sizeBroad = 4;
	int undoRedoMode = 0;
	fileout.open("gameSetting.bin", ios::out | ios::binary);
	if (fileout) {
		fileout.write(reinterpret_cast<char*>(&sizeBroad), sizeof(sizeBroad));
		fileout.write(reinterpret_cast<char*>(&undoRedoMode), sizeof(undoRedoMode));
	}
	else cout << " CAN NOT OPEN\n";
	fileout.close();
}

void printScreen(int move, int &size, int mode) {
	// in giao diện setting
	cout << endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout << "\t\t\t\t\t\t\t\t\t"<<Blue_27<<" GAME SETTING"<<reset_text<< endl;
	cout << endl;
	cout << "\t\t\t\t\t\t   'W' AND 'S' TO" << Red_text << " MOVE" << reset_text << " | 'A' AND 'D' TO " << Red_text << "CHANGE" << reset_text << " | 'J' TO " << Red_text << "ENTER" << reset_text << endl;
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t    " << square_;
	for (int i = 0; i < 19; i++) cout << line_;
	cout << square_2 << endl;
	if (move % 3 == 0) {
		cout << "\t\t\t\t\t\t\t\t      BROAD SIZE : " <<White_back<<Black_text<<size<<reset_text<<reset_backGround<<endl;
		cout << "\t\t\t\t\t\t\t\t      UNDO REDO MODE: " << undoRedoMode[mode] << endl;
		cout << "\t\t\t\t\t\t\t\t      BACK TO MENU" << endl;
	}
	else if(move%3==1) {
		cout << "\t\t\t\t\t\t\t\t      BROAD SIZE : "<<size << endl;
		cout << "\t\t\t\t\t\t\t\t      UNDO REDO MODE: " <<White_back << Black_text <<undoRedoMode[mode] << reset_text << reset_backGround << endl;
		cout << "\t\t\t\t\t\t\t\t      BACK TO MENU" << endl;
	}
	else if (move % 3 == 2) {
		cout << "\t\t\t\t\t\t\t\t      BROAD SIZE : " << size << endl;
		cout << "\t\t\t\t\t\t\t\t      UNDO REDO MODE: " << undoRedoMode[mode] << endl;
		cout << "\t\t\t\t\t\t\t\t      "<< White_back << Black_text <<"BACK TO MENU" << reset_text << reset_backGround << endl;
	}
	cout << "\t\t\t\t\t\t\t\t    " << square_3;
	for (int i = 0; i < 19; i++) cout << line_;
	cout << square_4;
}

void gameSetting_Funtion(int status) {
	fstream filein;
	int sizeBroad = 0;
	int undoRedoMode = 0;
	int move = 0;
	filein.open("gameSetting.bin", ios::in | ios::binary);
	if (filein) {
		// đọc size và chế độ undo redo từ file
		filein.read(reinterpret_cast<char*>(&sizeBroad), sizeof(sizeBroad));
		filein.read(reinterpret_cast<char*>(&undoRedoMode), sizeof(undoRedoMode));
		while (true) {
			system("cls");
			printScreen(move,sizeBroad,undoRedoMode);
			char command = _getch();
			if (command == 'w' && move>0) {
				move--;
			}
			else if (command=='s'&&move<2) {
				move++;
			}
			// tăng size trong khoảng từ 4 đến 10, không thể vượt qua khoảng này
			else if (move % 3 == 0 && command == 'd'&& sizeBroad>=4 &&sizeBroad<10) {
				sizeBroad++;
			}
			else if (move % 3 == 0 && command == 'a' && sizeBroad > 4 && sizeBroad <= 10) {
				sizeBroad--;
			}
			// Bật tắt chế độ undo redo
			else if (move % 3 == 1 && (command == 'a' || command == 'd')) {
				if (undoRedoMode == 0) undoRedoMode = 1;
				else if(undoRedoMode==1) undoRedoMode = 0;
			}
			else if (command=='j'&&move%3==2) {
				break;
			}
		}
	}
	else cout << "CAN NOT READ\n";
	filein.close();
	// Sau khi đã set up xong hết, lưu lại vào file 
	fstream fileout;
	fileout.open("gameSetting.bin", ios::binary | ios::out);
	if (fileout) {
		fileout.write(reinterpret_cast<char*>(&sizeBroad), sizeof(sizeBroad));
		fileout.write(reinterpret_cast<char*>(&undoRedoMode), sizeof(undoRedoMode));
	}
	else cout << "CAN NOT WRITE" << endl;
	fileout.close();
}