#include "menuGame.h"

bool isAccountValid(pair<string,string> loginAccount);
Account* getInforAccount(pair<string, string> login);
GamePlay* setUpGame(Account* currentAccount);
void addGamePlay(GamePlay* currentGame, int& accountNumber);
void enterGameVer1(GamePlay* game, int& status);
void enterGameVer2(GamePlay* game, int& status);
void addTail(AccountList& l, Account* tem);
void deleteList(AccountList& l);
AccountList creatTopList();
GamePlay** creatAccountList();
void doYouWantToGoBack(int& loginProcess);
pair<char*, char*> formatString(pair<string, string> login);
void printAccountList(GamePlay** list, int move);
void doCommand(char commnad, int& move, GamePlay** list, GamePlay* currentGame, int& process);
void saveAccountList(GamePlay** list, int size);
void releaseList(GamePlay** list);
void releaseList(GamePlay** list, int move);
void printSrceen();