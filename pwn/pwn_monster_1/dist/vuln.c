#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

// バッファリングを無効化して時間制限を60秒に設定
__attribute__((constructor))
void setup() {
  alarm(60);
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
}

void show_flag() {
	FILE* fp = fopen("./flag.txt", "r");
	char flag[256];
	if (fp == NULL) {
		printf("Not found flag.txt! Do you run in local?\n");
	} else {
		fgets(flag, 256, fp);
		printf("%s\n", flag);
		fclose(fp);
	}
}

void print_and_wait(const char* message) {
	puts(message);
	getchar();
}


void print_title() {
	print_and_wait(
		" ____                 __  __                 _            \n"
		"|  _ \\__      ___ __ |  \\/  | ___  _ __  ___| |_ ___ _ __ \n"
		"| |_) \\ \\ /\\ / / '_ \\| |\\/| |/ _ \\| '_ \\/ __| __/ _ \\ '__|\n"
		"|  __/ \\ V  V /| | | | |  | | (_) | | | \\__ \\ ||  __/ |   \n"
		"|_|     \\_/\\_/ |_| |_|_|  |_|\\___/|_| |_|___/\\__\\___|_|   \n"
		"                        Press Any Key                            \n"
	);
}

typedef struct {
	char name[16];
	int64_t hp;
	int64_t attack;
} Monster;

void print_monster_infomation(Monster monster) {
	printf("+--------+--------------------+----------------------+\n");
	printf("|name    | 0x%016lx | %20.8s |\n", *(int64_t*)monster.name      , monster.name);
	printf("|        | 0x%016lx | %20.8s |\n", *(int64_t*)(monster.name + 8), monster.name + 8);
	printf("|HP      | 0x%016lx | % 20ld |\n", monster.hp                , monster.hp);
	printf("|ATK     | 0x%016lx | % 20ld |\n", monster.attack            , monster.attack);
	printf("+--------+--------------------+----------------------+\n");
}

void give_monster_name(Monster* monster) {
	printf("Let's give your monster a name!\n");
	print_monster_infomation(*monster);

	printf("Input name: ");
	scanf("%s%*c", monster->name);
	
	print_monster_infomation(*monster);
	print_and_wait("OK, Nice name.");
}

bool battle(Monster my_monster, Monster rival_monster) {
	bool my_turn = true;
	while (1) {
		printf("[You] %s HP: %ld\n", my_monster.name, my_monster.hp);
		printf("[Rival] %s HP: %ld\n", rival_monster.name, rival_monster.hp);
		
		if (rival_monster.hp < 0) {
			print_and_wait("Win!");
			return true;
		}
		if (my_monster.hp < 0) {
			print_and_wait("Lose...");
			return false;
		}

		if (my_turn) {
			print_and_wait("Your Turn.");
			printf("Rival monster took %ld damage!\n", my_monster.attack);
			print_and_wait("");
			rival_monster.hp -= my_monster.attack;
		} else {
			print_and_wait("Rival Turn.");
			printf("Your monster took %ld damage!\n", rival_monster.attack);
			print_and_wait("");
			my_monster.hp -= rival_monster.attack;
		}

		my_turn = !my_turn;
	}
}

int main() {
	Monster rival_monster = {"pwnchu", 9999, 9999};
	Monster my_monster = {"", 100, 10};
	bool win = false;

	print_title();
	
	print_and_wait("Welcome to Pwn Monster World!");
	print_and_wait("I'll give your first monster!");
	
	give_monster_name(&my_monster);

	print_and_wait("Let's battle with Rival! If you win, give you FLAG.");
	win = battle(my_monster, rival_monster);
	if (win) {
		show_flag();
	}
	return 0;
}