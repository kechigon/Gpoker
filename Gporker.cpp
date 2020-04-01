#include<string>
#include<vector>
#include<iostream>
#include<time.h>
#include<cstdio>
using namespace std;

//�J�[�h
string CARDS[64] = {
	"�l�Y", "�l�Y", "�l�Y", "�l�Y", "�l�Y", "�l�Y", "�l�Y", "�l�Y", 
	"�J��", "�J��", "�J��", "�J��", "�J��", "�J��", "�J��", "�J��", 
	"�T�\", "�T�\", "�T�\", "�T�\", "�T�\", "�T�\", "�T�\", "�T�\", 
	"�J�G", "�J�G", "�J�G", "�J�G", "�J�G", "�J�G", "�J�G", "�J�G",
	"�n�G", "�n�G", "�n�G", "�n�G", "�n�G", "�n�G", "�n�G", "�n�G",
	"�S�L", "�S�L", "�S�L", "�S�L", "�S�L", "�S�L", "�S�L", "�S�L",
	"�N��", "�N��", "�N��", "�N��", "�N��", "�N��", "�N��", "�N��",
	"����", "����", "����", "����", "����", "����", "����", "����"
};

//�v���C���[�\����
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

//�v���C���[�̔z��
PLAYER PLAYERS[5];

//�v���C���[�̐�
int PLAYER_NUM;

//�V���b�t��
inline void shuffle();
//��D��z��
void dealCards(int);
//�����v���C���[�̏�ɃJ�[�h���v���X
void plusCard(int, string);
//�Q�[���I�[�o�[�����v���C���[����
bool gameOverJudge(int);
//�󔒂��o��
inline void printSpace(int);
//�����_�����O(�v���C���[���)
inline void renderingInformation();
//�����_�����O(�I�����)
void renderingSelect(int);
//�����_�����O(fromto)
void renderingFromTo(int, string, int);

int main() {

	//�v���C���[�l���𓾂�
	cout << "�v���C���[�l�������(3�`5):";
	cin >> PLAYER_NUM;

	//�l�����\���̂𐶐�
	for (int i = 0; i < PLAYER_NUM; i++) {
		PLAYERS[i] = { 0,0,0,0,0,0,0,0, };
	}

	//�J�[�h���V���b�t��
	shuffle();

	//��D�̐����Z�o
	int hands_num = 64 / PLAYER_NUM;

	//��D��z��
	dealCards(hands_num);

	//�Q�[���X�^�[�g
	bool playing = true;
	int turn_player = 0; //�v���C���[�ԍ��}�C�i�X1

	while (playing) {

		//�v���C���[����\��
		printSpace(100);
		renderingInformation();
		printf("\n");

		//��l�Ō��Ă邩�m�F
		printf("�v���C���[%d�̃^�[��", turn_player + 1);
		printf("\n\n");
		cout << "���̐l�Ɍ����ĂȂ��ł����H(y):";
		string s;
		cin >> s;

		//�I����ʂ�\��
		printSpace(100);
		renderingSelect(turn_player);
		printSpace(20);
		renderingInformation();
		printf("\n");
		cout << "�J�[�h��I��(�����牽�Ԗ� ���ƌ����� �N��):";

		//�R�}���h����
		int send_card;
		string decl;
		int given_player;
		cin >> send_card >> decl >> given_player;

		//given_player�������₷������
		int g_player = given_player - 1;

		//�J�[�h�̏���ۑ�
		string card_info = PLAYERS[turn_player].hands[send_card - 1];

		//�v���C���[�̎�D���甲��
		PLAYERS[turn_player].hands.erase(PLAYERS[turn_player].hands.begin() + (send_card - 1));

		//fromto��ʂ�\��
		printSpace(100);
		renderingFromTo(turn_player, decl, g_player);
		printSpace(20);
		renderingInformation();
		printf("\n");
		cout << "�錾�܂��͌���(�^ t �U f ���� v):";

		//���������ǂ���
		bool in_battle = true;

		//from�v���C���[��to�v���C���[
		int from_player = turn_player;
		int to_player = g_player;

		//�s�҂����܂�܂ŌJ��Ԃ�
		while (in_battle) {

			//�R�}���h����
			string cmd;
			cin >> cmd;

			//�錾�����ꍇ
			if (cmd == "t" || cmd == "f") {

				//������\��
				printSpace(100);
				printf("                                                                             %s", card_info.c_str());
				printf("\n");

				//�������v���C���[�̏�ɃJ�[�h���s��
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

				//�������łȂ��Ȃ�
				in_battle = false;

				printSpace(20);
				renderingInformation();
				printf("\n\n");
				if (playing) {
					cout << "���̐l�̃^�[���Ɉڂ�܂�(y):";
					string st;
					cin >> st;
				}
			}
			else {
				//��l�Ō��Ă邩�m�F
				printf("\n");
				cout << "���̐l�Ɍ����ĂȂ��ł����H(y):";
				string s;
				cin >> s;

				//������\��
				printSpace(100);
				printf("                                                                             %s", card_info.c_str());
				printf("\n");
				printSpace(20);
				renderingInformation();
				printf("\n");
				cout << "�N�ɉ��ƌ����ēn���܂����H(�N�� ���ƌ�����):";

				//from�v���C���[��ύX
				from_player = to_player;

				//�R�}���h����
				cin >> to_player >> decl;

				//given_player�������₷������
				to_player--;

				//fromto��ʂ�\��
				printSpace(100);
				renderingFromTo(from_player, decl, to_player);
				printSpace(20);
				renderingInformation();
				printf("\n");
				cout << "�錾�܂��͌���(�^ t �U f ���� v):";
			}
		}
		//turn_player��ύX
		if (turn_player < PLAYER_NUM - 1) turn_player++;
		else turn_player = 0;
	}
}

//�V���b�t��
inline void shuffle() {

	//�����_���Ȓl�𓾂邽�߂ɏ����l��srand�ŏ�����
	srand((unsigned int)time(NULL));

	/*�t�B�b�V���[�C�F�[�c�̃V���b�t���ŃV���b�t��*/

	//�J�[�h���V���b�t��
	for (int i = 63; i > 0; i--) {

		//�����_���Ȓl���擾
		int r = rand() % (i + 1);

		string tmp = CARDS[i];
		CARDS[i] = CARDS[r];
		CARDS[r] = tmp;
	}
}

//��D��z��
void dealCards(int hands_num) {

	int card_index = -1;
	for (int i = 0; i < PLAYER_NUM; i++) {
		for (int j = 0; j < hands_num; j++) {
			card_index++;
			PLAYERS[i].hands.push_back(CARDS[card_index]);
		}
	}
}

//�������v���C���[�̏�ɃJ�[�h���v���X
void plusCard(int loser_num, string card_info) {
	if (card_info == "�l�Y") {
		PLAYERS[loser_num].mouse_num++;
	}else if (card_info == "�J��") {
		PLAYERS[loser_num].stink_num++;
	}else if (card_info == "�T�\") {
		PLAYERS[loser_num].sco_num++;
	}else if (card_info == "�J�G") {
		PLAYERS[loser_num].frog_num++;
	}else if (card_info == "�n�G") {
		PLAYERS[loser_num].fly_num++;
	}else if (card_info == "�S�L") {
		PLAYERS[loser_num].coc_num++;
	}else if (card_info == "�N��") {
		PLAYERS[loser_num].spider_num++;
	}else if (card_info == "����") {
		PLAYERS[loser_num].bat_num++;
	}
}

//�Q�[���I�[�o�[�����v���C���[����
bool gameOverJudge(int player_num) {

	//��ł��l���ȏ�ɂȂ�����Q�[���I�[�o�[
	if (PLAYERS[player_num].mouse_num >= 4 || PLAYERS[player_num].stink_num >= 4 || PLAYERS[player_num].sco_num >= 4 || PLAYERS[player_num].frog_num >= 4 || PLAYERS[player_num].fly_num >= 4 || PLAYERS[player_num].coc_num >= 4 || PLAYERS[player_num].spider_num >= 4 || PLAYERS[player_num].bat_num >= 4) {
		return false;
	}

	//�S��ޑ�������Q�[���I�[�o�[
	if (PLAYERS[player_num].mouse_num >= 1 && PLAYERS[player_num].stink_num >= 1 && PLAYERS[player_num].sco_num >= 1 && PLAYERS[player_num].frog_num >= 1 && PLAYERS[player_num].fly_num >= 1 && PLAYERS[player_num].coc_num >= 1 && PLAYERS[player_num].spider_num >= 1 && PLAYERS[player_num].bat_num >= 1) {
		return false;
	}

	return true;
}

//�󔒂��o��
inline void printSpace(int num) {
	for (int i = 0; i < num; i++) printf("\n");
}

//�����_�����O(�v���C���[���)
inline void renderingInformation() {
	printf("\n");
	printf("     ");
	for (int i = 1; i <= PLAYER_NUM; i++) {
		printf("player%d                       ", i);
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		if (PLAYERS[i].hands.size() >= 10) printf("��D: %d��                    ", PLAYERS[i].hands.size());
		else                               printf("��D: %d��                     ", PLAYERS[i].hands.size());
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		printf("�l�Y %d �J�� %d �T�\ %d �J�G %d   ",PLAYERS[i].mouse_num, PLAYERS[i].stink_num, PLAYERS[i].sco_num, PLAYERS[i].frog_num);
	}
	printf("\n");
	printf("     ");
	for (int i = 0; i < PLAYER_NUM; i++) {
		printf( "�n�G %d �S�L %d �N�� %d ���� %d   ", PLAYERS[i].fly_num, PLAYERS[i].coc_num, PLAYERS[i].spider_num, PLAYERS[i].bat_num);
	}
	printf("\n");
}

//�����_�����O(�I�����)
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

//�����_�����O(fromto)
void renderingFromTo(int turn_player, string decl, int g_player) {
	printf("\n");
	printf("                                                                             ????");
	printf("\n\n");
	printf("                                                            From player %d    %s    To player %d", turn_player + 1, decl.c_str(), g_player + 1);
	printf("\n");
}