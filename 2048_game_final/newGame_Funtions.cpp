#include "coreGame.h"
#include "menuGame.h"


void printSrceen() {
	// in giao diện danh sách tài khoản
	system("cls");
	cout << endl << endl << endl << endl << endl;
	cout <<Orange_text << "\t\t\t\t\t\t\t\t         LOGIN PROCRESS" <<reset_text<< endl;
	cout << endl << "\t\t\t\t\t YOUR USERNAME MUST BE BETWEEN 1 TO 16 CHARACTERS "<<Red_text<< "EXCEPT"<<reset_text<<" SPACES AND SPECIAL CHARACTERS" << endl<<endl;
}

void addTail(AccountList& l, Account* tem) {
	// hàm này để thêm vào cuối danh sách
	if (l.head == NULL) {
		l.head = tem;
		l.size++;
	}
	else {
		Account* tam = l.head;
		while (tam->next != NULL) {
			tam = tam->next;
		}
		tam->next = tem;
		l.size++;
	}
}

void deleteList(AccountList& l) {
	// hàm này để xoá danh sách
	Account* tam = l.head;
	while (l.head != NULL) {
		l.head = l.head->next;
		delete tam;
		tam = l.head;
	}
	delete tam;
	l.head = NULL;
	return;
}

AccountList creatTopList() {
	// khởi tạo danh sách
	AccountList l;
	int size = 0;
	fstream filein;
	filein.open("top20List.bin", ios::in | ios::binary);
	if (filein) {
		// Đọc số lượng phần tử
		filein.read(reinterpret_cast<char*>(&size), sizeof(int));
		// nếu file rỗng tức là danh sách chưa có phần tử nào
		if (filein.eof()) return l;
		for (int i = 0; i < size; i++) {
			Account* current = new Account;
			filein.read(reinterpret_cast<char*>(current->username), 256);
			filein.read(reinterpret_cast<char*>(current->password), 256);
			filein.read(reinterpret_cast<char*>(&current->score), 4);
			filein.read(reinterpret_cast<char*>(&current->playTime), 4);
			filein.read(reinterpret_cast<char*>(&current->areStillPlaying), 4);
			current->next = NULL;
			// thêm vào cuối danh sách
			addTail(l, current);
		}
	}
	filein.close();
	return l;
}

GamePlay** creatAccountList() {
	int size = 0;
	GamePlay** list = new GamePlay * [5];
	fstream filein;
	// khởi tạo danh sách 5 tài khoản
	filein.open("accountListData.bin", ios::in | ios::binary);
	for (int i = 0; i < 5; i++) {
		list[i] = NULL;
	}
	if (filein) {
		// đọc số lượng phần tử
		filein.read(reinterpret_cast<char*>(&size), sizeof(size));
		// Nếu file rỗng tức là danh sách rỗng
		if (filein.eof()) {
			return list;
		}
		else {
			// nếu danh sách không rỗng thì đọc 5 lần tương ứng 5 tài khoản
			for (int i = 0; i < 5; i++) {
				int flag = 1;
				filein.read(reinterpret_cast<char*>(&flag), sizeof(int));
				// Nếu cờ bằng 1 tức là có tài khoản ở vị đó, ngược lại thì EMPTY
				if (flag == 1) {
					list[i] = new GamePlay;
					filein.read(reinterpret_cast<char*>(list[i]->currentAccount->username), 256);
					filein.read(reinterpret_cast<char*>(list[i]->currentAccount->password), 256);
					filein.read(reinterpret_cast<char*>(&list[i]->currentAccount->score), 4);
					filein.read(reinterpret_cast<char*>(&list[i]->currentAccount->playTime), 4);
					filein.read(reinterpret_cast<char*>(&list[i]->currentAccount->areStillPlaying), 4);
				}
			}
		}
	}
	else cout << " CANT OPEN" << endl;
	filein.close();
	return list;
}

bool isAccountValid(pair<string,string> loginAccount) {
	// Nếu độ dài tài khoản hoặc mật khẩu bé hơn 1 hoặc lớn hơn 16 kí tự thì không hợp lệ
	if (loginAccount.first.size() > 16 || loginAccount.second.size() > 16||loginAccount.first.size()<1||loginAccount.second.size()<1) {
		system("cls");
		printSrceen();
		cout <<endl<<Yellow_text<<"\t\t\t\t\t\t\tYOUR USERNAME OR PASSWORD IS NOT PASS THE REQUEST"<<reset_text << endl;
		_getch();
		return 0;
	}
	// Nếu tên hoặc mật khẩu có chứa kí tự đặc biệt hoặc khoảng trắng thì không hợp lệ
	for (int i = 0; i < loginAccount.first.size(); i++) {
		if (loginAccount.first[i] == ' ' || !(isdigit(loginAccount.first[i]) || isalpha(loginAccount.first[i]))) {
			system("cls");
			printSrceen();
			cout <<endl << Yellow_text<< "\t\t\t\t\t\t\tYOUR USERNAME HAS SPACE KEY OR SPECIAL CHARACTER" << reset_text << endl;
			_getch();
			return 0;
		}
	}

	for (int i = 0; i < loginAccount.second.size(); i++) {
		if (loginAccount.second[i] == ' ' || !(isdigit(loginAccount.second[i]) || isalpha(loginAccount.second[i]))) {
			system("cls");
			printSrceen();
			cout <<endl << Yellow_text << "\t\t\t\t\t\t\tYOUR PASSWORD HAS SPACE KEY OR SPECIAL CHARACTER" << reset_text << endl;
			_getch();
			return 0;
		}
	}
	// Tạo danh sách top 20 để kiểm tra xem có trên top 20 hay không
	AccountList topList = creatTopList();
	Account* tam = topList.head;
	while (tam != NULL) {
		// néu có trong top 20 thì sai mật khẩu thì không hợp lệ
		if (tam->username == loginAccount.first&&tam->password!=loginAccount.second) {
			system("cls");
			printSrceen();
			cout <<endl<< Yellow_text << "\t\t\t\t\t\t\tYOUR PASSWORD IS NOT CORRECT" << reset_text << endl;
			_getch();
			return 0;
		}
		tam = tam->next;
	}
	// giải phóng top 20
	deleteList(topList);
	// Tạo danh sách 5 tài khoản 
	GamePlay** accountList = creatAccountList();
	pair<char*, char*> account = formatString(loginAccount);
	// Nếu trùng tên tài khoản và tài khoản đó đang ở chế độ đang chơi thì không hợp lệ
	for (int i = 0; i < 5; i++) {
		if (accountList[i]!=NULL && strcmp(accountList[i]->currentAccount->username,account.first)==0 && accountList[i]->currentAccount->areStillPlaying == 1) {
			system("cls");
			printSrceen();
			cout << endl << Yellow_text << "\t\t\t\t\t\tYOUR ACCOUNT ARE STILL PLAYING, YOU CAN PLAY BY USING RESUME IN MENU " << reset_text << endl;
			releaseList(accountList);
			_getch();
			return 0;
		}
	}
	// giải phóng tên tên tài khoản và mật khẩu
	delete[] account.first;
	delete[] account.second;
	// giải phóng  danh sách 5 tài khoản
	releaseList(accountList);
	return 1;
}

void doYouWantToGoBack(int& loginProcess) {
	// hàm để hỏi xem có muốn quay về màn hình chính nếu đăng nhập thất bại hay không
	int move = 0;
	int command;
	while (true) {
		system("cls");
		printSrceen();
		cout << endl;
		cout << "\t\t\t\t\t\t\tYOUR LOGIN IS UNSUCCESSFULL, DO YOU WANT TO GO TO MENU GAME ?" << endl;
		cout << endl;
		if (move % 2 == 0) {
			cout << Black_text << White_back << "\t\t\t\t\t\t\t\t\t---> YES" << reset_backGround << reset_text << endl;
			cout << "\t\t\t\t\t\t\t\t\t     NO " << endl;
		}
		else {
			cout << "\t\t\t\t\t\t\t\t\t     YES" << endl;
			cout << Black_text << White_back << "\t\t\t\t\t\t\t\t\t---> NO " << reset_backGround << reset_text << endl;
		}
		command = _getch();
		if (command == 'j' && move % 2 == 0) {
			loginProcess = 0;
			break;
		}
		else if (command == 'j' && move % 2 != 0) {
			break;
		}
		else if (command == 'w' || command == 's') {
			move++;
		}
	}
}

pair<char*, char*> formatString(pair<string, string> login) {
	// hàm chuyển từ string sang char*
	int nameSize = (int)login.first.size();
	int passSize = (int)login.second.size();
	char* username = new char[256];
	char* password = new char[256];
	for (int i = 0; i < nameSize; i++) {
		username[i] = login.first[i];
	}
	username[nameSize] = '\0';
	for (int i = 0; i < passSize; i++) {
		password[i] = login.second[i];
	}
	password[passSize] = '\0';
	return make_pair(username, password);
}

Account* getInforAccount(pair<string, string> login) {
	//hàm để tạo danh sách top 20
	AccountList list = creatTopList();
	// hàm chuyển string sang char*
	pair<char*, char*> temp = formatString(login);
	Account* tam = list.head;
	int flag = 1;
	// Kiểm tra xem tài khoản đã ở trên top 20 hay chưa
	while (tam != NULL) {
		if (tam->username == temp.first && tam->password == temp.second) {
			flag = 0;
			break;
		}
		tam = tam->next;
	}
	// nếu không ở trên top thì tại tài khoản mới
	if (flag == 1) {
		Account* res = new Account;
		delete res->username;
		delete res->password;
		res->password = temp.second;
		res->username = temp.first;
		return res;
	}
	// giải phóng danh sách
	deleteList(list);
	return tam;
}

void printAccountList(GamePlay** list,int move) {
	// hàm hiển thị giao diện khi chọn tài khoản
	cout << endl << endl << endl << endl << endl << endl;
	cout <<Green_46<< "\t\t\t\t\t\t\t\tYOUR ACCOUNT LIST" <<reset_text<< endl << endl;
	cout << "\t\t\t\t\t\t\t    " << square_;
	for (int i = 0; i < 25; i++) cout << line_;
	cout << square_2 << endl;
	if (move % 5 == 0) {
		for (int i = 0; i < 5; i++) {
			if (i == 0) {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t--> " <<White_back<<Black_text<< i + 1 <<". " <<"EMPTY" <<reset_text<<reset_backGround<< endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 <<". " << list[i]->currentAccount->username << reset_text << reset_backGround << endl;
				}
			}
			else {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 <<". " << "EMPTY" << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 <<". " << list[i]->currentAccount->username << endl;
				}
			}
		}
	}
	else if (move % 5 == 1) {
		for (int i = 0; i < 5; i++) {
			if (i == 1) {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << "EMPTY" << reset_text << reset_backGround << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << list[i]->currentAccount->username << reset_text << reset_backGround << endl;
				}
			}
			else {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << "EMPTY" << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << list[i]->currentAccount->username << endl;
				}
			}
		}
	}
	else if (move % 5 == 2) {
		for (int i = 0; i < 5; i++) {
			if (i == 2) {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << "EMPTY" << reset_text << reset_backGround << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << list[i]->currentAccount->username << reset_text << reset_backGround << endl;
				}
			}
			else {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << "EMPTY" << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << list[i]->currentAccount->username << endl;
				}
			}
		}
	}
	else if (move % 5 == 3) {
		for (int i = 0; i < 5; i++) {
			if (i == 3) {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << "EMPTY" << reset_text << reset_backGround << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << list[i]->currentAccount->username << reset_text << reset_backGround << endl;
				}
			}
			else {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << "EMPTY" << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << list[i]->currentAccount->username << endl;
				}
			}
		}
	}
	else if (move % 5 == 4) {
		for (int i = 0; i < 5; i++) {
			if (i == 4) {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << "EMPTY" << reset_text << reset_backGround << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t--> " << White_back << Black_text << i + 1 << ". " << list[i]->currentAccount->username << reset_text << reset_backGround << endl;
				}
			}
			else {
				if (list[i] == NULL) {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << "EMPTY" << endl;
				}
				else {
					cout << "\t\t\t\t\t\t\t\t    " << i + 1 << ". " << list[i]->currentAccount->username << endl;
				}
			}
		}
	}
	cout << "\t\t\t\t\t\t\t    " << square_3;
	for (int i = 0; i < 25; i++) cout << line_;
	cout << square_4;
	cout << endl;
}

void doCommand(char commnad,int& move, GamePlay** list,GamePlay* currentGame,int& process) {
	// hàm di chuyển
	if (commnad == 'w' || commnad == 's') {
		if (commnad == 'w' && move > 0) {
			move--;
		}
		else if (commnad == 's' && move < 4) {
			move++;
		}
	}
	else if (commnad == 'j') {
		int step = 0;
		while (true) {
			system("cls");
			printAccountList(list, move);
			// Hiển thị thông báo chắc chắn chưa
			cout << "\t\t\t\t\t\t\t\t"<<Red_text<<"ARE YOU SURE ABOUT REPLACE THIS ACCOUNT ?"<<reset_text << endl;
			if (step % 2 == 0) {
				cout <<"\t\t\t\t\t\t\t\t-->"<<White_back<<Black_text<<" YES " <<reset_text<<reset_backGround<<endl;
				cout << "\t\t\t\t\t\t\t\t" <<"     NO " << endl;
			}
			else {
				cout << "\t\t\t\t\t\t\t\t"<< "    YES "<< endl;
				cout << "\t\t\t\t\t\t\t\t-->" << White_back << Black_text << "  NO " << reset_text << reset_backGround << endl;
			}
			char request = _getch();
			if (request == 'j'&&step%2==0) {
				// Thay thế tài khoản vào chỗ được chỉ định và xoá tài khoản thay thế
				GamePlay* tam = list[move % 5];
				list[move % 5] = currentGame;
				process = 0;
				system("cls");
				printAccountList(list, move);
				cout <<Yellow_text<< "\t\t\t\t\t\t\t\tYOUR ACCOUNT HAS BEEN ADDED" <<reset_text<< endl;
				_getch();
				break;
			}
			else if (request == 'w' || request == 's') {
				step++;
			}
			else if (request == 'j' && step % 2 != 0) {
				break;
			}
		}
	}
}

void saveAccountList(GamePlay** list, int size) {
	// hàm lưu danh sách 5 tài khoản vào file
	fstream fileout;
	fileout.open("accountListData.bin", ios::binary | ios::out);
	if (fileout) {
		fileout.write(reinterpret_cast<char*>(&size), sizeof(int));
		for (int i = 0; i < 5; i++) {
			if (list[i] == NULL) {
				int flag = 0;
				fileout.write(reinterpret_cast<char*>(&flag), sizeof(int));
			}
			else {
				int flag = 1;
				fileout.write(reinterpret_cast<char*>(&flag), sizeof(int));
				fileout.write(reinterpret_cast<char*>(list[i]->currentAccount->username), 256);
				fileout.write(reinterpret_cast<char*>(list[i]->currentAccount->password), 256);
				fileout.write(reinterpret_cast<char*>(&list[i]->currentAccount->score), 4);
				fileout.write(reinterpret_cast<char*>(&list[i]->currentAccount->playTime), 4);
				fileout.write(reinterpret_cast<char*>(&list[i]->currentAccount->areStillPlaying), 4);
			}
		}
	}
	else cout << "CANT WRITE" << endl;
	fileout.close();
}

void releaseList(GamePlay** list) {
	// hàm giải phóng danh sách 5 tài khoản
	for (int i = 0; i < 5; i++) {
		if (list[i] != NULL) {
			delete[] list[i]->currentAccount->username;
			delete[] list[i]->currentAccount->password;
			delete list[i]->currentAccount;
			delete list[i]->broad;
		}
	}
	//delete[] list;
}

void releaseList(GamePlay** list,int move) {
	// hàm giải phóng danh sách 5 tài khoản
	for (int i = 0; i < 5; i++) {
		if (list[i] != NULL&&i!=(move%5)){
			delete[] list[i]->currentAccount->username;
			delete[] list[i]->currentAccount->password;
			delete list[i]->currentAccount;
			delete list[i]->broad;
		}
	}
	//delete[] list;
}

void addGamePlay(GamePlay* currentGame,int& accountNumber) {
	int size = 0;
	int move = 0;
	fstream filein;
	// Đọc file để tạo danh sách 5 tài khoản
	filein.open("accountListData.bin", ios::in | ios::binary);
	GamePlay** list = new GamePlay * [5];
	for (int i = 0; i < 5; i++) {
		list[i] = NULL;
	}
	// Nếu file tồn tại
	if (filein) {
		// Đọc size số lượng phần tử có trong file
		filein.read(reinterpret_cast<char*>(&size), sizeof(size));
		// Nếu đọc size xong mà file hết, chứng tỏ danh sách trống
		if (filein.eof()) {
			size = 1;
			int process = 1;
			while (process) {
				system("cls");
				printAccountList(list, move);
				char command = _getch();
				// chọn một trong 5 chỗ để thêm tài khoản game mới vào
				doCommand(command, move, list,currentGame,process);
			}
		}
		// Nếu danh sách đang có các tài khoản có sẵn
		else {
			// đọc từng phần từ trong danh sách
			for (int i = 0; i < 5; i++) {
				int flag = 1;
				filein.read(reinterpret_cast<char*>(&flag), sizeof(int));
				// Đặt 1 cờ hiệu, nếu cờ hiệu bằng 1 tức là đang có người, nếu cờ hiệu bằng 0 tức là chỗ đó trống
				if (flag == 1) {
					list[i] = new GamePlay;
					filein.read(reinterpret_cast<char*>(list[i]->currentAccount->username), 256);
					filein.read(reinterpret_cast<char*>(list[i]->currentAccount->password), 256);
					filein.read(reinterpret_cast<char*>(&list[i]->currentAccount->areStillPlaying), 4);
					filein.read(reinterpret_cast<char*>(&list[i]->currentAccount->playTime), 4);
					filein.read(reinterpret_cast<char*>(&list[i]->currentAccount->score), 4);
				}
			}
			int process = 1;
			while (process) {
				system("cls");
				printAccountList(list, move);
				char command = _getch();
				//Thêm tài khoản hoặc thay thế vào chỗ được chỉ định
				doCommand(command, move, list, currentGame, process);
			}
		}
	}
	else cout << " CANT OPEN" << endl;
	filein.close();
	// đánh dấu chỉ số tài khoản
	accountNumber = move % 5 + 1;
	// lưu danh sách 5 tài khoản vào file
	saveAccountList(list,size);
	// giải phóng danh sách trừ tài khoản đang được chơi
	releaseList(list,move);
}

GamePlay* setUpGame(Account* currentAccount) {
	// khởi tạo Game mới
	GamePlay* res = new GamePlay;
	res->broad = new Broad;
	res->currentAccount = currentAccount;
	fstream filein;
	// Đọc file để lấy setting từ file 
	filein.open("gameSetting.bin", ios::binary | ios::in);
	if (!filein.is_open()) cout << "CAN NOT OPEN" << endl;
	filein.read(reinterpret_cast<char*>(&res->broad->sizeBroad), sizeof(res->broad->sizeBroad));
	filein.read(reinterpret_cast<char*>(&res->broad->undoRedoMode), sizeof(res->broad->undoRedoMode));
	filein.close();
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t"<<Yellow_text<<"YOUR GAME IS READY....."<<reset_text<< endl;
	_getch();
	return res;
}

void newGame_Funtion(int& status) {
	Account* currentAcount = NULL;
	pair<string, string> loginAccount;
	int accountNumber = 1;
	int loginProcess = 1;
	while(loginProcess&&status) {
		printSrceen();
		cout << "\t\t\t\t\t\t\tPLEASE ENTER USERNAME: ";
		getline(cin, loginAccount.first);
		cout << "\t\t\t\t\t\t\tPLEASE ENTER PASSWORD: ";
		getline(cin, loginAccount.second);
		// kiểm tra xem tài khoản có hợp lệ hoặc không bị trùng
		if (isAccountValid(loginAccount)) {
			// hàm để lấy chuyển thông tin từ string qua char*
			currentAcount = getInforAccount(loginAccount);
			// hàm để set up trước để chơi game
			GamePlay* game = setUpGame(currentAcount);
			// hàm để thêm tài khoản chơi game vào danh sách 5 tài khoản
			addGamePlay(game,accountNumber);
			if (game->broad->undoRedoMode == 0) {
				// chơi game ở chế độ undo redo tắt
				enterGameVer1(game, status);
			}
			else {
				//chơi game ở chế độ undo redo bật
				enterGameVer2(game, status);
			}
		}
		else {
			//khi đăng nhập thất bại, bạn có thể quay về menu
			doYouWantToGoBack(loginProcess);
		}
	}
	status = 1;;
	return;
}