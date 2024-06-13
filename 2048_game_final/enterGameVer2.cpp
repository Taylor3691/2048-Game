#include "coreGame.h"
#include "undoRedo.h"

pair<int, int> generateRandomPosition(Broad* broad) {
	// hàm hàm sẽ random vị trí còn trống trong bảng để thêm giá trị mới vào
	int line = rand() % broad->sizeBroad;
	int colum = rand() % broad->sizeBroad;
	while (broad->matrix[line][colum] != 0) {
		line = rand() % broad->sizeBroad;
		colum = rand() % broad->sizeBroad;
	}
	return make_pair(line, colum);
}

void addNewUnit(Broad* broad) {
	// hàm này để random giá trị 2 hoặc 4 vào chỗ đc chỉ định
	pair<int, int> pos = generateRandomPosition(broad);
	int value = rand() % 100;
	if (value > 96) {
		broad->matrix[pos.first][pos.second] = 4;
	}
	else {
		broad->matrix[pos.first][pos.second] = 2;
	}
}

Broad* creatBroad(GamePlay* game) {
	// hàm này để khởi tạo 1 bảng có 2 giá trị ngẫy nhiên 2 2  2 4 hoặc  4 4
	int size = game->broad->sizeBroad;
	int** p = new int* [size];
	for (int i = 0; i < size; i++) {
		p[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			p[i][j] = 0;
		}
	}
	game->broad->matrix = p;
	addNewUnit(game->broad);
	addNewUnit(game->broad);
	return game->broad;
}

void setColorText(int n, int scale, int j) {
	// hàm này dùng để vẽ một ô và tô màu con số trong ô đó
	int count = scs(n);
	if (j == 0) {
		if (n == 0) {
			cout << colum_;
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << " ";
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
			return;
		}
		if (n % 128 == 0) {
			cout << colum_;
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Yellow_214 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 64 == 0) {
			cout << colum_;
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Violet_128 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 32 == 0) {
			cout << colum_;
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Blue_21 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 16 == 0) {
			cout << colum_;
			for (int i = 0; i < scale-count+1; i++) cout << " ";
			cout << Green_28 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 8 == 0) {
			cout << colum_;
			for (int i = 0; i < scale; i++) cout << " ";
			cout<< Yellow_94 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 4 == 0) {
			cout << colum_;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << Red_text << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if(n%2==0) {
			cout << colum_;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << n;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
	}
	else {
		if (n == 0) {
			for (int i = 0; i < scale; i++) cout << " ";
			cout << " ";
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
			return;
		}
		if (n % 128 == 0) {
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Yellow_214 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 64 == 0) {
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Violet_128 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;;
		}
		else if (n % 32 == 0) {
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Blue_21 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 16 == 0) {
			for (int i = 0; i < scale - count + 1; i++) cout << " ";
			cout << Green_28 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 8 == 0) {
			for (int i = 0; i < scale; i++) cout << " ";
			cout << Yellow_94 << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if (n % 4 == 0) {
			for (int i = 0; i < scale; i++) cout << " ";
			cout << Red_text << n << Black_text;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
		else if(n%2==0) {
			for (int i = 0; i < scale; i++) cout << " ";
			cout << n;
			for (int i = 0; i < scale; i++) cout << " ";
			cout << colum_;
		}
	}
	return;
}

void printScreenGame1(GamePlay* game) {
	// hàm này để in giao diện bảng chơi game của chế độ undo redo tắt
	int bestScore = findHighestScore();
	int scale = 1;
	int size = game->broad->sizeBroad;
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		for (int j = 0; j < game->broad->sizeBroad; j++) {
			scale = max(scale,scs(game->broad->matrix[i][j]));
		}
	}
	cout << Skin_224<<Black_text;
	cout << square_;
	for (int i = 0; i < (scale + 2) * size + scale * size-1; i++) {
		cout << line_;
	}
	cout << square_2 << endl;
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		for (int j = 0; j < size; j++) {
			int space = scs(game->broad->matrix[i][j]);
			if (j == 0) {
				setColorText(game->broad->matrix[i][j],scale,j);
			}
			else {
				setColorText(game->broad->matrix[i][j],scale,j);
			}
		}
		cout << endl;
		if (i != size - 1) {
			cout << colum_;
			for (int i = 0; i < (scale + 2) * size + scale * size - 1; i++) {
				cout << line_;
			}
			cout << colum_ << endl;
		}
	}
	cout << square_3;
	for (int i = 0; i < (scale + 2) * size + scale * size - 1; i++) cout << line_;
	cout << square_4 << endl;
	cout << reset_backGround<<reset_text;
	cout << "SCORE: " << game->currentAccount->score << "      BESTSCORE: " << bestScore << endl;
	cout << "S: DOWN  ||  W: UP  ||  D: RIGHT  ||  A: LEFT  ||  E: EXIT " << endl;
}

void printScreenGame2(GamePlay* game) {
	// hàm này để in giao diện bảng của chế độ undo rede bật
	int bestScore = findHighestScore();
	int scale = 1;
	int size = game->broad->sizeBroad;
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		for (int j = 0; j < game->broad->sizeBroad; j++) {
			scale = max(scale, scs(game->broad->matrix[i][j]));
		}
	}
	cout << Skin_224 << Black_text;
	cout << square_;
	for (int i = 0; i < (scale + 2) * size + scale * size - 1; i++) {
		cout << line_;
	}
	cout << square_2 << endl;
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		for (int j = 0; j < size; j++) {
			int space = scs(game->broad->matrix[i][j]);
			if (j == 0) {
				setColorText(game->broad->matrix[i][j], scale, j);
			}
			else {
				setColorText(game->broad->matrix[i][j], scale, j);
			}
		}
		cout << endl;
		if (i != size - 1) {
			cout << colum_;
			for (int i = 0; i < (scale + 2) * size + scale * size - 1; i++) {
				cout << line_;
			}
			cout << colum_ << endl;
		}
	}
	cout << square_3;
	for (int i = 0; i < (scale + 2) * size + scale * size - 1; i++) cout << line_;
	cout << square_4 << endl;
	cout << reset_backGround << reset_text;
	cout << "SCORE: " << game->currentAccount->score << "      BESTSCORE: " << bestScore << endl;
	cout << "S: DOWN  ||  W: UP  ||  D: RIGHT  ||  A: LEFT  ||  U: UNDO  ||  R: REDO  ||  E: EXIT " << endl;
}

int findHighestScore() {
	// hàm này để tìm điểm của người top 1 trong file
	int size = 0;
	Account* top1Player = new Account;
	fstream filein;
	filein.open("top20List.bin", ios::binary | ios::in);
	filein.read(reinterpret_cast<char*>(&size), sizeof(size));
	filein.read(reinterpret_cast<char*>(top1Player->username), 256);
	filein.read(reinterpret_cast<char*>(top1Player->password), 256);
	filein.read(reinterpret_cast<char*>(&top1Player->score), 4);
	filein.read(reinterpret_cast<char*>(&top1Player->playTime), 4);
	filein.read(reinterpret_cast<char*>(&top1Player->areStillPlaying), 4);
	filein.close();
	int res = 0;
	res = top1Player->score;
	deleteAccount(top1Player);
	return res;
}

void goUp(GamePlay* game) {
	// dồn tất cả lên phía trên
	int size = game->broad->sizeBroad;
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (game->broad->matrix[j][i] != 0) {
				int index = 0;
				for (index; index < j; index++) {
					if (game->broad->matrix[index][i] == 0) break;
				}
				if (index != j) {
					swap(game->broad->matrix[j][i], game->broad->matrix[index][i]);
				}
			}
		}
	}
	// nếu có 2 ô nào có giá trị bằng nhau thì hợp nhất
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (game->broad->matrix[j-1][i] == game->broad->matrix[j][i]) {
				game->broad->matrix[j-1][i] *= 2;
				game->broad->matrix[j][i] = 0;
				game->currentAccount->score += game->broad->matrix[j - 1][i];//
			}
		}
	}
	// dồn lên trên 1 lần nữa
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (game->broad->matrix[j][i] != 0) {
				int index = 0;
				for (index; index < j; index++) {
					if (game->broad->matrix[index][i] == 0) break;
				}
				if (index != j) {
					swap(game->broad->matrix[j][i], game->broad->matrix[index][i]);
				}
			}
		}
	}
}

void goDown(GamePlay* game) {
	// dồn tất cả xuống dưới
	int size = game->broad->sizeBroad;
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 0; j--) {
			if (game->broad->matrix[j][i]!=0) {
				int index = size - 1;
				for (index; index > j; index--) {
					if (game->broad->matrix[index][i] == 0) break;
				}
				if (index != j) {
					swap(game->broad->matrix[index][i], game->broad->matrix[j][i]);
				}
			}
		}
	}
	// khi có 2 giá trị nào bằng nhau thì hợp nhất
	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (game->broad->matrix[j + 1][i] == game->broad->matrix[j][i]) {
				game->broad->matrix[j + 1][i] *= 2;
				game->broad->matrix[j][i] = 0;
				game->currentAccount->score += game->broad->matrix[j + 1][i];//
			}
		}
	}
	// dồn xuống dưới 1 lần nữa
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 0; j--) {
			if (game->broad->matrix[j][i]!=0) {
				int index = size - 1;
				for (index; index > j; index--) {
					if (game->broad->matrix[index][i] == 0) break;
				}
				if (index != j) {
					swap(game->broad->matrix[index][i], game->broad->matrix[j][i]);
				}
			}
		}
	}
	return;
}

void goRight(GamePlay* game) {
	// dồn tất cả qua bên phải
	int size = game->broad->sizeBroad;
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 0; j--) {
			if (game->broad->matrix[i][j] != 0) {
				int index = size - 1;
				for (index; index > j; index--) {
					if (game->broad->matrix[i][index] == 0) {
						break;
					}
				}
				if (index != j) {
					swap(game->broad->matrix[i][index], game->broad->matrix[i][j]);
				}
			}
		}
	}
	// nếu có 2 giá trị nào bằng nhau thì hợp nhất
	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (game->broad->matrix[i][j + 1] == game->broad->matrix[i][j]) {
				game->broad->matrix[i][j + 1] *= 2;
				game->broad->matrix[i][j] = 0;
				game->currentAccount->score += game->broad->matrix[i][j + 1];//
			}
		}
	}
	// tiếp tục dồn bên phải 1 lần nữa
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 0; j--) {
			if (game->broad->matrix[i][j] != 0) {
				int index = size - 1;
				for (index; index > j; index--) {
					if (game->broad->matrix[i][index] == 0) {
						break;
					}
				}
				if (index != j) {
					swap(game->broad->matrix[i][index], game->broad->matrix[i][j]);
				}
			}
		}
	}
	return;
}

void goLeft(GamePlay* game) {
	// dồn tất cả về bên trái
	int size = game->broad->sizeBroad;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (game->broad->matrix[i][j] != 0) {
				int index = 0;
				for (index; index < j; index++) {
					if (game->broad->matrix[i][index]==0) break;
				}
				if (index != j) {
					swap(game->broad->matrix[i][index], game->broad->matrix[i][j]);
				}
			}
		}
	}
	// nếu có 2 gí trị nào giống nhau thì hợp nhất
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (game->broad->matrix[i][j - 1] == game->broad->matrix[i][j]) {
				game->broad->matrix[i][j - 1] *= 2;
				game->broad->matrix[i][j] = 0;
				game->currentAccount->score += game->broad->matrix[i][j - 1];
			}
		}
	}
	// dồn lại qua bên trái 1 lần nữa
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (game->broad->matrix[i][j] != 0) {
				int index = 0;
				for (index; index < j; index++) {
					if (game->broad->matrix[i][index]==0) break;
				}
				if (index != j) {
					swap(game->broad->matrix[i][index], game->broad->matrix[i][j]);
				}
			}
		}
	}
	return;
}

bool isBroadChanged(int** before, int** after, int size) {
	// kiểm tra xem bảng có thay đổi hay chưa
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (before[i][j] != after[i][j]) {
				return 1;
			}
		}
	}
	return 0;
}

int getTimePlay(high_resolution_clock::time_point& timeStart, seconds extra) {
	// hàm tính thời gian bằng thư viện chrono và ép về kiểu giây
	auto timeEnd = high_resolution_clock::now();
	auto res = timeEnd - timeStart + extra;
	return (int)duration_cast<seconds>(res).count();
}

void applyMove(char command, GamePlay* game,high_resolution_clock::time_point& timeStart, chrono::seconds extraTime) {
	// cập nhật thời gian
	int durration = getTimePlay(timeStart,extraTime);
	game->currentAccount->playTime = durration;
	// cấp phát để tạo bảng lúc trước thay đổi
	int** before = new int* [game->broad->sizeBroad];
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		before[i] = new int[game->broad->sizeBroad];
	}
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		for (int j = 0; j < game->broad->sizeBroad; j++) {
			before[i][j] = game->broad->matrix[i][j];
		}
	}
	// đi lên
	if (command == 'w') {
		goUp(game);
	}
	// đi xuống
	else if (command == 's') {
		goDown(game);
	}
	// đi qua phải
	else if (command == 'd') {
		goRight(game);
	}
	// đi qua trái
	else if (command == 'a') {
		goLeft(game);
	}
	// nếu bảng thay đổi so với bảng cũ thì mới thêm phần tử mới
	if (isBroadChanged(before,game->broad->matrix,game->broad->sizeBroad)) {
		addNewUnit(game->broad);
	}
	// giải phóng bảng cũ đã xài xong
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		delete[] before[i];
	}
	delete[] before;
	return;
}

bool isGameLose(GamePlay* game) {
	// hàm để kiểm tra xem bảng còn 2 số nào có giá trị bằng nhau mà ở cạnh nhau hoặc có ô nào còn trống hay không
	int size = game->broad->sizeBroad;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (game->broad->matrix[i][j] == game->broad->matrix[i][j+1] || game->broad->matrix[i][j]== 0 || game->broad->matrix[i][j+1] == 0) {
				return 0;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (game->broad->matrix[j][i] == game->broad->matrix[j+1][i] || game->broad->matrix[j][i] == 0 || game->broad->matrix[j+1][i] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

void writeTopList(AccountList l) {
	// hàm để lưu top vào file 
	fstream fileout;
	fileout.open("top20List.bin", ios::binary | ios::out);
	if (fileout) {
		fileout.write(reinterpret_cast<char*>(&l.size), sizeof(int));
		if (l.head != NULL) {
			Account* current = l.head;
			while (current != NULL) {
				fileout.write(reinterpret_cast<char*>(current->username), 256);
				fileout.write(reinterpret_cast<char*>(current->password), 256);
				fileout.write(reinterpret_cast<char*>(&current->score), 4);
				fileout.write(reinterpret_cast<char*>(&current->playTime), 4);
				fileout.write(reinterpret_cast<char*>(&current->areStillPlaying), 4);
				current = current->next;
			}
		}
	}
	else cout << " CANT WRITE" << endl;
	fileout.close();
}

void deleteGame(GamePlay* game) {
	// hàm để xoá game
	deleteAccount(game->currentAccount);
	for (int i = 0; i < game->broad->sizeBroad; i++) {
		delete[] game->broad->matrix[i];
	}
	delete[] game->broad->matrix;
	delete game;
	game = NULL;
	return;
}

void saveRecord(GamePlay* game) {
	// hàm để xoá tài khoản game khỏi danh sách resume khi game đó hoàn thành ( khi thắng hoặc thua)
	int size = 0;
	// tạo danh sách 5 tài khoản
	GamePlay** accountList = creatAccountList();
	for (int i = 0; i < 5; i++) {
		// nếu tài khoản đang trong danh sách resume thì xoá đi tài khoản đó đi
		if (accountList[i] != NULL&&strcmp(accountList[i]->currentAccount->username,game->currentAccount->username)==0){
			GamePlay* tam = accountList[i];
			accountList[i] = NULL;
			deleteGame(tam);
		}
		else if (accountList[i] != NULL) {
			size++;
		}
	}
	// lưu lại danh sách mới vào file
	saveAccountList(accountList,size);
	// giải phóng danh sách
	releaseList(accountList);
}

void swapNode(AccountList& l ,Account* i , Account* j) {
	// hàm để đổi nội dung 2 node
	char* tem = i->username;
	i->username = j->username;
	j->username = tem;
	tem = i->password;
	i->password = j->password;
	j->password = tem;
	swap(i->score, j->score);
	swap(i->playTime, j->playTime);
	swap(i->areStillPlaying, j->areStillPlaying);
}

void sortList(AccountList& l) {
	// hàm sắp xếp điểm giảm dần, thời gian tăng dần theo bubble sort
	if (l.head != NULL) {
		for (Account* i = l.head; i != NULL; i = i->next) {
			for (Account* j = i->next; j != NULL; j = j->next) {
				if (j->score != i->score) {
					if (j->score > i->score) {
						swapNode(l,i, j);
					}
				}
				else {
					if (j->playTime < i->playTime) {
						swapNode(l,i, j);
					}
				}
			}
		}
	}
}

bool isAccountOnTop(AccountList l,GamePlay* game) {
	// hàm kiểm tra xem tài khoản có xuất hiện trên top không
	if (l.head == NULL) return 0;
	Account* current = l.head;
	while (current != NULL) {
		if (strcmp(current->username,game->currentAccount->username)==0) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}

void deleteAccount(Account* current) {
	// hoá xoá 1 tài khoản trên top 20 hoặc 5 tài khoản đang resume
	if (current != NULL) {
		delete[] current->username;
		delete[] current->password;
		delete current;
		current = NULL;
	}
}

void addNewTopPlayer(AccountList& l,Account* source) {
	// tạo bản sao y chang game đang chơi để thêm vào top 20
	Account* tam = new Account;
	strcpy_s(tam->username, 256, source->username);
	strcpy_s(tam->password, 256, source->password);
	tam->score = source->score;
	tam->playTime = source->playTime;
	tam->areStillPlaying = source->areStillPlaying;
	addTail(l, tam);
}

void updateRank(AccountList& l,GamePlay* game) {
	// kiểm tra xen danh sách có rỗng không
	if (l.head != NULL) {
		// nếu danh sách không rỗng
		if (isAccountOnTop(l,game)) {
			// nếu tài khoản đang ở trên top
			Account* current = l.head;
			// di chuyển đến node tài khoản đang chơi
			while (current != NULL) {
				if (strcmp(current->username, game->currentAccount->username) == 0) {
					break;
				}
				current = current->next;
			}
			// nếu điểm đang chơi cao hơn điểm trên bxh thì cập nhật điểm cao hơn
			if (current->score < game->currentAccount->score) {
				current->score = game->currentAccount->score;
				current->playTime = game->currentAccount->playTime;
			}
		}
		// nếu tài khoản không trên top
		else {
			// thêm vào cuối bảng xếp hạng
			addNewTopPlayer(l,game->currentAccount);
			// sắp xếp theo thứ tự điểm giảm dần, nếu bằng điểm thì so về thời gian
			sortList(l);
			// nếu top có quá 20 người
			if (l.size > 20) {
				// chạy đến node cuối cùng
				Account* current = l.head;
				while (current->next->next != NULL) {
					current = current->next;
				}
				Account* after = current->next;
				current->next = NULL;
				// xoá người thứ 21 có số điểm thấp nhất
				deleteAccount(after);
				l.size--;
			}
			// lưu top 20 lại vào file
			writeTopList(l);
			return;
		}
	}
	else {
		addNewTopPlayer(l, game->currentAccount);
	}
	// sắp xếp điểm giảm dần, nếu điểm  bằng nhau thì so sánh thời gian tăng dần
	sortList(l);
	// lưu lại vào file top 20
	writeTopList(l);
}

bool areYouInTop20(AccountList l,GamePlay* game) {
	// hàm này để kiểm tra xem bạn có trên top không lúc thắng hoặc thua
	if (isAccountOnTop(l, game)) {
		Account* current = l.head;
		while (current != NULL) {
			if (strcmp(current->username, game->currentAccount->username) == 0) {
				if (current->score == game->currentAccount->score) {
					return 1;
				}
			}
			current = current->next;
		}
	}
	return 0;
}

int scs(int n) {
	// hàm để lấy số chữ số để canh trong kẻ bảng và kẻ top 20
	if (n == 0) return 1;
	int dem = 0;
	while (n) {
		dem++;
		n /= 10;
	}
	return dem;
}

void printTopRank() {
	// Hàm để in top 20
	AccountList l;
	int number = 1;
	l = creatTopList();
	Account* current = l.head;
	cout << square_;
	for (int i = 0; i < 55; i++) {
		if (i == 7||i==28||i==40) cout << colum_194;
		else cout << line_;
	}
	cout << square_2 << endl;
	cout << colum_ << "  TOP  " << colum_ << "        NAME        " << colum_ << "   SCORE   " << colum_ << "   TIMEPLAY   " << colum_ << endl;
	while (current != NULL) {
		cout << colum_195;
		for (int i = 0; i < 55; i++) {
			if (i == 7 || i == 28 || i == 40) cout << colum_197;
			else cout << line_;
		}
		if (number>9){
			int count = 0;
			cout << colum_ << endl;
			cout << colum_ << "  " << number << "      " << current->username;
			for (int i = 0; current->username[i] != '\0'; i++) {
				count++;
			}
			for (int i = 0; i < 22-count; i++) {
				cout << " ";
			}
			cout << current->score;
			count = scs(current->score);
			for (int i = 0; i < 15 - count; i++) {
				cout << " ";
			}
			cout << current->playTime << endl;
		}
		else {
			int count = 0;
			cout << colum_ << endl;
			cout << colum_ << "   " << number << "      " << current->username;
			for (int i = 0; current->username[i] != '\0'; i++) {
				count++;
			}
			for (int i = 0; i < 22 - count; i++) {
				cout << " ";
			}
			cout << current->score;
			count = scs(current->score);
			for (int i = 0; i < 15 - count; i++) {
				cout << " ";
			}
			cout << current->playTime << endl;
		}
		current = current->next;
		number++;
	}
	cout << square_3;
	for (int i = 0; i < 55; i++) {
		if (i == 7 || i == 28 || i == 40) cout << colum_193;
		else cout << line_;
	}
	cout << square_4 << endl;
	return;
}

void checkWin2(GamePlay* game, int& status, int& winFlag, high_resolution_clock::time_point& timeStart, chrono::seconds extraTime) {
	// nếu đã win rồi thì không cần check nữa 
	if (winFlag == 1) return;
	int size = game->broad->sizeBroad;
	int move = 0;
	// tạo top 20
	AccountList l = creatTopList();
	// cập nhật lạ thời gian trước lúc kiểm tra
	game->currentAccount->playTime = getTimePlay(timeStart, extraTime);
	// cập nhật bxh lần cuối
	updateRank(l, game);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// nếu có ô đạt 2048 thì win
			if (game->broad->matrix[i][j] == 2048) {
				while (true) {
					system("cls");
					printScreenGame2(game);
					// in bảng xếp hạng néu trong top 20
					if(areYouInTop20(l,game))printTopRank();
					// hỏi xem có muốn chơi tiếp không
					cout<<Yellow_text << "CONGRATULATION, YOU HAVE WON THE GAME, DO YOU WANT TO CONTINUE GAME?" <<reset_text<< endl;
					if (move % 2 == 0) {
						cout << "-->"<<White_back<<Black_text<<" YES" <<reset_text<<reset_backGround<< endl;
						cout << "    NO" << endl;
					}
					else {
						cout << "    YES" << endl;
						cout << "-->"<< White_back << Black_text <<" NO" << reset_text << reset_backGround << endl;
					}
					char command = _getch();
					if (command == 'w' || command == 's') {
						move++;
					}
					else if (command == 'j' && move % 2 == 0) {
						// nếu chơi tiếp thì đổi cờ để không cần phải check win nữa
						winFlag = 1;
						return;
					}
					else if (command == 'j' && move % 2 != 0) {
						// nếu không thì dừng lại và game kết thúc và trờ về menu
						status = 0;
						// lưu game nếu trong top 20
						saveRecord(game);
						return;
					}
				}
			}
		}
	}
}

void checkLose2(GamePlay* game, int& status, int& loseFlag, high_resolution_clock::time_point& timeStart, chrono::seconds extraTime) {
	int move = 0;
	int onTop = 0;
	// tạo danh sách top 20
	AccountList l = creatTopList();
	// cập nhật thời gian trước lúc kiểm tra
	game->currentAccount->playTime = getTimePlay(timeStart, extraTime);
	// cập nhật điểm trên bxh lần cuối cho chắc
	updateRank(l, game);
	// Nếu đã thua từ trước mà sử dụng undo mode thì không cần hiển thị lại
	if (loseFlag == 1) return;
	// Nếu Game thua
	if (isGameLose(game)) {
		while (true) {
			system("cls");
			printScreenGame2(game);
			// in bảng xếp hạng nếu trong top 20
			if (areYouInTop20(l, game))printTopRank();
			// hỏi xem có muốn xài undo để chơi tiếp ko
			cout<<Red_text << "   GAME OVER!!! DO YOU WANT TO CONTINUE BY USING UNO MOD ?" <<reset_text<< endl;
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
				//nếu chọn tiếp tục thì đổi cờ cho xài undo
				loseFlag = 1;
				return;
			}
			else if (command == 'j' && move % 2 != 0) {
				// không chơi tiếp thì trạng thái chơi game tắt và lưu game nếu trong top 20
				status = 0;
				game->currentAccount->areStillPlaying = 0;
				saveRecord(game);
				return;
			}
		}
	}
}

void saveGame(GamePlay* game, int index) {
	// dựa vào chỉ số, mở đúng file có chỉ số truyền vào và lưu game, tài khoản, mật khẩu vào trong file đó
	fstream fileout;
	int size = game->broad->sizeBroad;
	string filename = "account" + to_string(index) + ".bin";
	fileout.open(filename, ios::out | ios::binary);
	if (fileout) {
		fileout.write(reinterpret_cast<char*>(&game->broad->sizeBroad), 4);
		fileout.write(reinterpret_cast<char*>(&game->broad->undoRedoMode), 4);
		for (int i = 0; i < game->broad->sizeBroad;i++) {
			fileout.write(reinterpret_cast<char*>(game->broad->matrix[i]), size * 4);
		}
		fileout.write(reinterpret_cast<char*>(game->currentAccount->username), 256);
		fileout.write(reinterpret_cast<char*>(game->currentAccount->password), 256);
		fileout.write(reinterpret_cast<char*>(&game->currentAccount->score), 4);
		fileout.write(reinterpret_cast<char*>(&game->currentAccount->playTime), 4);
		fileout.write(reinterpret_cast<char*>(&game->currentAccount->areStillPlaying), 4);
	}
	else {
		cout << "CANT WRITE";
	}
	fileout.close();
}

void exitGame2(int& status,GamePlay* game) {
	// Khởi tạo danh sách 5 tài khoản
	GamePlay** list = creatAccountList();
	int index = -1;
	int move = 0;
	// lấy chỉ số id của tài khoản
	for (int i = 0; i < 5; i++) {
		if (list[i] != NULL && strcmp(list[i]->currentAccount->username, game->currentAccount->username) == 0) {
			index = i + 1;
			break;
		}
	}
	while (true) {
		system("cls");
		printScreenGame2(game);
		// Hỏi xem có xác nhận thoát không
		cout <<endl<<Green_46<< "ARE YOU SURE ABOUT QUIT GAME ? YOUR GAME WILL BE SAVED..." << endl;
		if (move % 2 == 0) {
			cout << "--->"<<White_back<<Black_text<<" YES" <<reset_text<<reset_backGround<< endl;
			cout << "     NO" << endl;
		}
		else {
			cout << "     YES" << endl;
			cout << "--->"<< White_back << Black_text <<" NO " << reset_text << reset_backGround<< endl;
		}
		char commnad = _getch();
		if (move % 2 == 0 && commnad == 'j') {
			//lưu game
			saveGame(game,index);
			status = 0;
			break;
		}
		else if (move % 2 != 0 && commnad == 'j') {
			// xác nhận ko muốn thoát game
			break;
		}
		else if (commnad == 'w' || commnad == 's') {
			move++;
		}
	}
	return;
}

void enterGameVer2(GamePlay* game,int& status) {
	// Tạo 2 cờ win và lose để có thể dánh dấu lúc thua cuộc và lúc thắng cuộc
	int winFlag = 0;
	int loseFlag = 0;
	// Khởi tạo bảng mới
	game->broad = creatBroad(game);
	// Tạo danh sách top 20
	AccountList l = creatTopList();
	// KHi chế độ undo redo bật, khởi tạo 2 thùng stack để sử dụng
	StackList undoList, redoList;
	// đặt mốc thời gian bắt đầu chuẩn bị chơi
	auto timeStart = high_resolution_clock::now();
	// khởi tạo Stack
	Stack* currentStack = NULL;
	while (status) {
		//  tạo bản sao game lưu giữ trạng thái của bảng
		currentStack = creatStack(game);
		system("cls");
		// in giao diện
		printScreenGame2(game);
		cout << endl << endl;
		char command = _getch();
		// nhập hành động
		if (command == 'w' || command == 's' || command == 'a' || command == 'd') {
			// di chuyển, cập nhật time
			applyMove(command,game,timeStart,0s);
			// nếu bảng có sự thay đổi, đẩy trạng thái vào thùng undo và giải phóng redoList nếu có
			if (isBroadChanged(currentStack->prevGame->broad->matrix, game->broad->matrix, game->broad->sizeBroad)) {
				releaseStackList(redoList);
				push_frontStack(undoList, currentStack);
			}
			else {
				// nếu bảng không thay đổi thì xoá trạng thái hiện tại
				deleteStack(currentStack);
			}
			// sau khi có những sự thay đổi, cập nhật bxh
			updateRank(l, game);
			// kiểm tra có ô nào đạt 2048 chưa
			checkWin2(game,status,winFlag,timeStart,0s);
			// kiểm tra xem có thua chưa khi không có nước đi nào hợp lệ
			checkLose2(game, status, loseFlag,timeStart,0s);
			if (status == 0) {
				// nếu game kết thúc vì bất kì lí do gì, giải phóng 2 thùng undo và redo
				releaseStackList(undoList);
				releaseStackList(redoList);
			}
		}
		else if (command == 'e') {
			// xác định muốn thoát game 
			exitGame2(status,game);
			if (status == 0) {
				// nếu game kết thúc vì bất kì lí do gì, giải phóng 2 thùng undo và redo
				releaseStackList(undoList);
				releaseStackList(redoList);
			}
		}
		else if (command == 'u' || command == 'r') {
		// khi nhấn u hoặc r sẽ thực hiện chức năng undo redo
			doUndoRedo_Funtion(undoList, redoList, currentStack,game,winFlag,loseFlag,command);
			game->currentAccount->playTime = getTimePlay(timeStart, 0s);
			// cập nhật bxh 
			updateRank(l, game);
		}
	}
	// sau khi chơi xong sẽ giải phóng game và danh sách top 20
	deleteGame(game);
	deleteList(l);
}