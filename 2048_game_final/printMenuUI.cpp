#include "header.h"
#include "menuGame.h"

void printMenuUI(int move) {
	cout << endl;
	//In giao diện màn hình chính

	// Vẽ màu 
	printf(Red_text"\t\t\t\t   222222222222222         000000000            444444444       888888888     \t\t\n");
	printf("\t\t\t\t  2:::::::::::::::22     00:::::::::00         4::::::::4     88:::::::::88   \t\t\n");
	printf(Orange_text"\t\t\t\t  2::::::222222:::::2  00:::::::::::::00      4:::::::::4   88:::::::::::::88 \t\t\n");
	printf("\t\t\t\t  2222222     2:::::2 0:::::::000:::::::0    4::::44::::4  8::::::88888::::::8\t\t\n");
	printf("\t\t\t\t              2:::::2 0::::::0   0::::::0   4::::4 4::::4  8:::::8     8:::::8\t\t\n");
	printf(Yellow_text"\t\t\t\t              2:::::2 0:::::0     0:::::0  4::::4  4::::4  8:::::8     8:::::8\t\t\n");
	printf("\t\t\t\t           2222::::2  0:::::0     0:::::0 4::::4   4::::4   8:::::88888:::::8 \t\t\n");
	printf("\t\t\t\t      22222::::::22   0:::::0     0:::::04::::444444::::444  8:::::::::::::8  \t\t\n");
	printf(Blue_text"\t\t\t\t    22::::::::222     0:::::0     0:::::04::::::::::::::::4 8:::::88888:::::8 \t\t\n");
	printf("\t\t\t\t   2:::::22222        0:::::0     0:::::04444444444:::::4448:::::8     8:::::8\t\t\n");
	printf("\t\t\t\t  2:::::2             0:::::0     0:::::0          4::::4  8:::::8     8:::::8\t\t\n");
	printf(Green_text"\t\t\t\t  2:::::2             0::::::0   0::::::0          4::::4  8:::::8     8:::::8\t\t\n");
	printf("\t\t\t\t  2:::::2       2222220:::::::000:::::::0          4::::4  8::::::88888::::::8\t\t\n");
	printf("\t\t\t\t  2::::::2222222:::::2 00:::::::::::::00         44::::::44 88:::::::::::::88 \t\t\n");
	printf(Violet_text"\t\t\t\t  2::::::::::::::::::2   00:::::::::00           4::::::::4   88:::::::::88   \t\t\n");
	printf("\t\t\t\t  22222222222222222222     000000000             4444444444     888888888     \t\t\n");
	cout << reset_text;
	cout << reset_backGround;
	cout << endl;
	// chỉ dẫn
	cout << "\t\t\t\t\t   'W' AND 'S' TO"<<Red_text <<" MOVE"<<reset_text<<" | 'A' AND 'D' TO "<<Red_text<<"CHANGE"<<reset_text<<" | 'J' TO "<<Red_text<<"ENTER"<<reset_text<< endl<<endl;
	//  vẽ các options trên menu
	if (move % 5 == 0) {
		//vẽ phần thanh đầu điên để mở hộp
		cout << "\t\t\t\t\t\t\t\t" << square_;
		for (int i = 0; i < 19; i++) cout<<line_;
		cout << square_2;
		cout << endl;
		// vẽ phần nội dung
		cout << "\t\t\t\t\t\t\t\t" << colum_ <<White_back<<Black_text<< "  1. NEW GAME      "<<reset_backGround<<reset_text << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   "<<colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  2. RESUME        " <<colum_<< endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " <<colum_<< endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  3. GAME SETTING  " <<colum_<< endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " <<colum_<< endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  4. TOP 20 LIST   " <<colum_<< endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  5. EXIT          " << colum_ << endl;
		// Vẽ phần thanh đóng
		cout << "\t\t\t\t\t\t\t\t" << square_3;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_4;
	}
	// Tương tự trên
	else if (move % 5 == 1) {
		cout << "\t\t\t\t\t\t\t\t" << square_;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_2;
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  1. NEW GAME      " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ <<White_back<<Black_text<< "  2. RESUME        " <<reset_backGround<<reset_text << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  3. GAME SETTING  " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  4. TOP 20 LIST   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  5. EXIT          " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << square_3;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_4;
	}
	// Tương tự trên
	else if (move % 5 == 2) {
		cout << "\t\t\t\t\t\t\t\t" << square_;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_2;
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  1. NEW GAME      " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  2. RESUME        " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ <<White_back<<Black_text<< "  3. GAME SETTING  " <<reset_backGround<<reset_text << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  4. TOP 20 LIST   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  5. EXIT          " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << square_3;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_4;
	}
	// Trương tự trên
	else if (move % 5 == 3) {
		cout << "\t\t\t\t\t\t\t\t" << square_;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_2;
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  1. NEW GAME      " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  2. RESUME        " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  3. GAME SETTING  " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ <<White_back<<Black_text<< "  4. TOP 20 LIST   " <<reset_backGround<<reset_text<< colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  5. EXIT          " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << square_3;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_4;
	}
	// Tương tự trên
	else if (move % 5 == 4) {
		cout << "\t\t\t\t\t\t\t\t" << square_;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_2;
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  1. NEW GAME      " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  2. RESUME        " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  3. GAME SETTING  " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "  4. TOP 20 LIST   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ << "                   " << colum_ << endl;
		cout << "\t\t\t\t\t\t\t\t" << colum_ <<White_back<<Black_text<< "  5. EXIT          " <<reset_backGround<<reset_text<< colum_<< endl;
		cout << "\t\t\t\t\t\t\t\t" << square_3;
		for (int i = 0; i < 19; i++) cout << line_;
		cout << square_4;
	}
}