// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

class Player {
public:
	void SetCurrentState(int vitality, int attack, int defence) {
		vitality_ = vitality;
		attack_ = attack;
		defence_ = defence;
	}

public:
	int vitality_ = 0;
	int attack_ = 0;
	int defence_ = 0;
};

class Memento {
public:
	void GetPlayerState(Player* player) {
		player->vitality_ = player_->vitality_;
		player->attack_ = player_->attack_;
		player->defence_ = player_->defence_;
	}

	void SetPlayer(Player* player) {
		player_->vitality_ = player->vitality_;
		player_->attack_ = player->attack_;
		player_->defence_ = player->defence_;
	}

public:
	Player* player_ = new Player();
};

void print_player_state(Player* player) {
	printf("vitality: %d \n", player->vitality_);
	printf("attack: %d \n", player->attack_);
	printf("defence: %d \n", player->defence_);
}

int main14()
{
	// before pk boss
	Player* playerA = new Player();
	playerA->SetCurrentState(100, 100, 100);

	print_player_state(playerA);

	// memento
	Memento* memento = new Memento();
	memento->SetPlayer(playerA);

	print_player_state(playerA);

	// after pk boss
	playerA->SetCurrentState(0, 0, 0);

	print_player_state(playerA);

	// memento to player
	memento->GetPlayerState(playerA);

	print_player_state(playerA);

	return 0;
}


