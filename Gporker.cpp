#include<string>
#include<vector>
#include<iostream>
#include<time.h>
#include<cstdio>
using namespace std;

//カード
string CARDS[64] = {
	"ネズ", "ネズ", "ネズ", "ネズ", "ネズ", "ネズ", "ネズ", "ネズ", 
	"カメ", "カメ", "カメ", "カメ", "カメ", "カメ", "カメ", "カメ", 
	"サソ", "サソ", "サソ", "サソ", "サソ", "サソ", "サソ", "サソ", 
	"カエ", "カエ", "カエ", "カエ", "カエ", "カエ", "カエ", "カエ",
	"ハエ", "ハエ", "ハエ", "ハエ", "ハエ", "ハエ", "ハエ", "ハエ",
	"ゴキ", "ゴキ", "ゴキ", "ゴキ", "ゴキ", "ゴキ", "ゴキ", "ゴキ",
	"クモ", "クモ", "クモ", "クモ", "クモ", "クモ", "クモ", "クモ",
	"モリ", "モリ", "モリ", "モリ", "モリ", "モリ", "モリ", "モリ"
};

//プレイヤー構造体
struct PLAYER {
	int mouse_num;
	int stink_num;
	int sco_num;
	int frog_num;
	int fly_num;
	int coc_num;
	int spider_num;
	int bat_num;
	vector<string> hands;
};

//プレイヤーの配列
PLAYER PLAYERS[5];

//プレイヤーの数
int PLAYER_NUM;

//シャッフル
inline void shuffle();
//手札を配る
void dealCards(int);
//負けプレイヤーの場にカードをプラス
void plusCard(int, string);
//ゲームオーバーしたプレイヤー判定
bool gameOverJudge(int);
//空白を出力
inline void printSpace(int);
//レンダリング(プレイヤー情報)
inline void renderingInformation();
//レンダリング(選択画面)
void renderingSelect(int);
//レンダリング(fromto)
void renderingFromTo(int, string, int);

int main() {

	//プレイヤー人数を得る
	cout << "プレイヤー人数を入力(3～5):";
	cin >> PLAYER_NUM;

	//人数分構造体を生成
	for (int i = 0; i < PLAYER_NUM; i++) {
		PLAYERS[i] = { 0,0,0,0,0,0,0,0, };
	}

	//カードをシャッフル
	shuffle();

	//手札の数を算出
	int hands_num = 64 / PLAYER_NUM;

	//手札を配る
	dealCards(hands_num);

	//ゲームスタート
	bool playing = true;
	int turn_player = 0; //プレイヤー番号マイナス1

	while (playing) {

		//プレイヤー情報を表示
		printSpace(100);
		renderingInformation();
		printf("\n");

		//一人で見てるか確認
		printf("プレイヤー%dのターン", turn_player + 1);
		printf("\n\n");
		cout << "他の人に見えてないですか？(y):";
		string s;
		cin >> s;

		//選択画面を表示
		printSpace(100);
		renderingSelect(turn_player);
		printSpace(20);
		renderingInformation();
		printf("\n");
		cout << "カードを選択(左から何番目 何と言って 誰に):";

		//コマンド入力
		int send_card;
		string decl;
		int given_player;
		cin >> send_card >> decl >> given_player;

		//given_playerを扱いやすくする
		int g_player = given_player - 1;

		//カードの情報を保存
		string card_info = PLAYERS[turn_player].hands[send_card - 1];

		//プレイヤーの手札から抜く
		PLAYERS[turn_player].hands.erase(PLAYERS[turn_player].hands.begin() + (send_card - 1));

		//fromto画面を表示
		printSpace(100);
		renderingFromTo(turn_player, decl, g_player);
		printSpace(20);
		renderingInformation();
		printf("\n");
		cout << "宣言または見る(真 t 偽 f 見る v):";

		//勝負中かどうか
		bool in_battle = true;

		//fromプレイヤーとtoプレイヤー
		int from_player = turn_player;
		int to_player = g_player;

		//敗者が決まるまで繰り返す
		while (in_battle) {

			//コマンド入力
			string cmd;
			cin >> cmd;

			//宣言した場合
			if (cmd == "t" || cmd == "f") {

				//答えを表示
				printSpace(100);
				printf("                                                                             %s", card_info.c_str());
				printf("\n");

				//負けたプレイヤーの場にカードが行く
				if (cmd == "t") {
					if (card_info == decl) {
						plusCard(from_player, card_info);
						playing = gameOverJudge(from_player);
					}
					else {
						plusCard(to_player, card_info);
						playing = gameOverJudge(to_player);
					}
				}
				else if (cmd == "f") {
					if (card_info != decl) {
						plusCard(from_player, card_info);
						playing = gameOverJudge(from_player);
					}
					else {
						plusCard(to_player, card_info);
						playing = gameOverJudge(to_player);
					}
				}

				//勝負中でなくなる
				in_battle = false;

				printSpace(20);
				renderingInformation();
				printf("\n\n");
				if (playing) {
					cout << "次の人のターンに移ります(y):";
					string st;
					cin >> st;
				}
			}
			else {
				//一人で見てるか確認
				printf("\n");
				cout << "他の人に見えてないですか？(y):";
				string s;
				cin >> s;

				//答えを表示
				printSpace(100);
				printf("                                                                             %s", card_info.c_str());
				printf("\n");
				printSpace(20);
				renderingInformation();
				printf("\n");
				cout << "誰に何と言って渡しますか？(誰に 何と言って):";

				//fromプレイヤーを変更
				from_player = to_player;

				//コマンド入力
				cin >> to_player >> decl;

				//given_playerを扱いやすくする
				to_player--;

				//fromto画面を表示
				printSpace(100);
				renderingFromTo(from_player, decl, to_player);
				printSpace(20);
				renderingInformation();
				printf("\n");
				cout << "宣言または見る(真 t 偽 f 見る v):";
			}
		}
		//turn_playerを変更
		if (turn_player < PLAYER_NUM - 1) turn_player++;
		else turn_player = 0;
	}
}

//シャッフル
inline void shuffle() {

	//ランダムな値を得るために初期値をsrandで初期化
	srand((unsigned int)time(NULL));

	/*フィッシャーイェーツのシャッフルでシャッフル*/

	//カードをシャッフル
	for (int i = 63; i > 0; i--) {

		//ランダムな値を取得
		int r = rand() % (i + 1);

		string tmp = CARDS[i];
		CARDS[i] = CARDS[r];
		CARDS[r] = tmp;
	}
}

//手札を配る
void dealCards(int hands_num) {

	int card_index = -1;
	for (int i = 0; i < PLAYER_NUM; i++) {
		for (int j = 0; j < hands_num; j++) {
			card_index++;
			PLAYERS[i].hands.push_back(CARDS[card_index]);
		}
	}
}

//負けたプレイヤーの場にカードをプラス
void plusCard(int loser_num, string card_info) {
	if (card_info == "ネズ") {
		PLAYERS[loser_num].mouse_num++;
	}else if (card_info == "カメ") {
		PLAYERS[loser_num].stink_num++;
	}else if (card_info == "サソ") {
		PLAYERS[loser_num].sco_num++;
	}else if (card_info == "カエ") {
		PLAYERS[loser_num].frog_num++;
	}else if (card_info == "ハエ") {
		PLAYERS[loser_num].fly_num++;
	}else if (card_info == "ゴキ") {
		PLAYERS[loser_num].coc_num++;
	}else if (card_info == "クモ") {
		PLAYERS[loser_num].spider_num++;
	}else if (card_info == "モリ") {
		PLAYERS[loser_num].bat_num++;
	}
}

//ゲームオーバーしたプレイヤー判定
bool gameOverJudge(int player_num) {

	//一つでも四枚以上になったらゲームオーバー
	if (PLAYERS[player_num].mouse_num >= 4 || PLAYERS[player_num].stink_num >= 4 || PLAYERS[player_num].sco_num >= 4 || PLAYERS[player_num].frog_num >= 4 || PLAYERS[player_num].fly_num >= 4 || PLAYERS[player_num].coc_num >= 4 || PLAYERS[player_num].spider_num >= 4 || PLAYERS[player_num].bat_num >= 4) {
		return false;
	}

	//全種類揃ったらゲームオーバー
	if (PLAYERS[player_num].mouse_num >= 1 && PLAYERS[player_num].stink_num >= 1 && PLAYERS[player_num].sco_num >= 1 && PLAYERS[player_num].frog_num >= 1 && PLAYERS[player_num].fly_num >= 1 && PLAYERS[player_num].coc_num >= 1 && PLAYERS[player_num].spider_num >= 1 && PLAYERS[player_num].bat_num >= 1) {
		return false;
	}

	return true;
}

//空白を出力
inline void printSpace(int num) {
	for (int i = 0; i < num; i++) printf("\n");
}

//レンダリング(プレイヤー情報)
inline void renderingInformation() {
	printf("\n");
	printf("     ");
	for (int i = 1; i <= PLAYER_NUM; i++) {
		printf("player%d                       ", i);
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (PLAYERS[i].hands.size() >= 10) printf("手札: %d枚                    ", PLAYERS[i].hands.size());
		else                               printf("手札: %d枚                     ", PLAYERS[i].hands.size());
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		printf("ネズ %d カメ %d サソ %d カエ %d   ",PLAYERS[i].mouse_num, PLAYERS[i].stink_num, PLAYERS[i].sco_num, PLAYERS[i].frog_num);
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		printf( "ハエ %d ゴキ %d クモ %d モリ %d   ", PLAYERS[i].fly_num, PLAYERS[i].coc_num, PLAYERS[i].spider_num, PLAYERS[i].bat_num);
	}
	printf("\n");
}

//レンダリング(選択画面)
void renderingSelect(int turn_player) {
	printf("\n");
	printf("     ");
	for (int i = 1; i <= PLAYERS[turn_player].hands.size(); i++) {
		if(i < 10) printf(" %d     ", i);
		else printf(" %d    ", i);
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYERS[turn_player].hands.size(); i++) {
		printf("%s   ", PLAYERS[turn_player].hands[i].c_str());
	}
	printf("\n");
}

//レンダリング(fromto)
void renderingFromTo(int turn_player, string decl, int g_player) {
	printf("\n");
	printf("                                                                             ????");
	printf("\n\n");
	printf("                                                            From player %d    %s    To player %d", turn_player + 1, decl.c_str(), g_player + 1);
	printf("\n");
}