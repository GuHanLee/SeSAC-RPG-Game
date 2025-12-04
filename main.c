#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NUM_DUNGEONS 10 // 총 던전 개수
#define MAX_ITEMS 10   // 인벤토리 아이템 수

typedef struct { // 아이템 구조체
    char name[30];
    int type;  // 1: 무기, 2: 방어구
    int value; // 아이템 효과
    int count; // 아이템 갯수
} Item;

Item inven_item[MAX_ITEMS];
int inven_count = 0;
int total_gold = 0;

// 장착 아이템
Item equipped_weapon = {"없음", 1, 0, 0};
Item equipped_armor = {"없음", 2, 0, 0};

Item drop[5] = {
    {"A급 검", 1, 10, 0},
    {"A급 갑옷", 2, 10, 0},
    {"B급 검", 1, 5, 0},
    {"B급 갑옷", 2, 5, 0},
    {"S급 검", 1, 20, 0}
};

// 상점 아이템
typedef struct {
    char name[30];
    int type;
    int value;
    int price;
} ShopItem;

ShopItem shop_items[6] = {
    {"A급 검", 1, 10, 100},
    {"A급 갑옷", 2, 10, 100},
    {"S급 검", 1, 20, 500},
    {"S급 갑옷", 2, 20, 500},
    {"SSS급 검", 1, 30, 1000},
    {"SSS급 갑옷", 2, 30, 1000}
};

// 게임 초기화
void game_initialize() {
    srand((unsigned int)time(NULL));
    printf("******************************\n");
    printf("SESAC 프로젝트 RPG 게임 \n");
    printf("1 : 게임 시작\n");
    printf("2 : 게임 종료\n");
    printf("선택: ");
    
    int game_state;
    scanf("%d", &game_state);
    if (game_state < 1 || game_state > 2) {
        printf("<오류> 잘못된 선택입니다. 다시 입력해주세요.\n");
        printf("선택: ");
        scanf("%d", &game_state);
    }
    printf("******************************\n");
    if (game_state == 2) {
        printf("게임을 종료합니다.\n");
        exit(0);
    } else {
        printf("게임을 시작합니다.\n\n");
    }
}

void add_item(Item item) {
    if (inven_count < MAX_ITEMS) { // 아이템 추가
        inven_item[inven_count] = item;
        inven_item[inven_count].count = 1;
        printf("새 아이템 획득: %s\n", item.name);
        inven_count++;
    } else {
        printf("<경고> 인벤토리가 가득 찼습니다.\n");
    }
}

void store(int *pH_attack, int *pH_defense) {
    while (1) {
        printf("******************************\n");
        printf("상점입니다.\n");
        printf("보유 골드: %d\n", total_gold);
        printf("******************************\n");
        printf("판매 아이템:\n");
        
        for (int i = 0; i < 6; i++) {
            printf("%d. %s (", i + 1, shop_items[i].name);
            if (shop_items[i].type == 1) {
                printf("무기, 공격력 +%d", shop_items[i].value);
            } else {
                printf("방어구, 방어력 +%d", shop_items[i].value);
            }
            printf(") - %d골드\n", shop_items[i].price);
        }
        
        printf("0. 마을로 돌아가기\n");
        printf("선택: ");
        
        int choice;
        scanf("%d", &choice);
        
        if (choice == 0) {
            printf("마을로 돌아갑니다.\n\n");
            return;
        } else if (choice >= 1 && choice <= 6) {
            int index = choice - 1;
            if (total_gold >= shop_items[index].price) {
                total_gold -= shop_items[index].price;
                
                Item purchased_item;
                strcpy(purchased_item.name, shop_items[index].name);
                purchased_item.type = shop_items[index].type;
                purchased_item.value = shop_items[index].value;
                purchased_item.count = 1;
                
                add_item(purchased_item);
                printf("구매 완료! 남은 골드: %d\n\n", total_gold);
            } else {
                printf("<경고> 골드가 부족합니다. (필요: %d, 보유: %d)\n\n", 
                       shop_items[index].price, total_gold);
            }
        } else {
            printf("<오류> 잘못된 선택입니다.\n\n");
        }
    }
}

void character(int *Hblood, int *Hattack, int *Hdefense, int *Htype, int *Hskill, char *hero_name) {
    struct Hero {
        int blood;
        int attack;
        int defense;
        int type;
        int skill;
        char name[10];
    }; 

    struct Hero hr1 = {100, 5, 5, 1, 10, "전사"}; // 전사 (흙)
    struct Hero hr2 = {80, 9, 3, 2, 20, "궁수"}; // 궁수 (불)
    struct Hero hr3 = {60, 12, 2, 3, 10, "도적"}; // 도적 (물)

    // 직업별 스킬 구현
    // 전사 스킬 : 공격력 증가(1회)
    // 궁수 스킬 : 체력 회복(1회)
    // 도적 스킬 : 방어력 증가(1회)
    
    printf("히어로를 선택하세요\n");
    printf("1. 전사 (HP: %d, Attack: %d, Defense: %d, 속성: 흙)\n", hr1.blood, hr1.attack, hr1.defense);
    printf("2. 궁수 (HP: %d, Attack: %d, Defense: %d, 속성: 불)\n", hr2.blood, hr2.attack, hr2.defense);
    printf("3. 도적 (HP: %d, Attack: %d, Defense: %d, 속성: 물)\n", hr3.blood, hr3.attack, hr3.defense);
    printf("선택: ");
    
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) {
        printf("<오류> 잘못된 선택입니다. 다시 입력해주세요.\n");
        printf("선택: ");
        scanf("%d", &choice);
    }
    printf("******************************\n");
    
    if (choice == 1) {
        printf("전사(흙)가 선택되었습니다!\n");
        *Hblood = hr1.blood;
        *Hattack = hr1.attack;
        *Hdefense = hr1.defense;
        *Htype = hr1.type;
        *Hskill = hr1.skill;
        strcpy(hero_name, hr1.name);
    } else if (choice == 2) {
        printf("궁수(불)가 선택되었습니다!\n");
        *Hblood = hr2.blood;
        *Hattack = hr2.attack;
        *Hdefense = hr2.defense;
        *Htype = hr2.type;
        *Hskill = hr2.skill;
        strcpy(hero_name, hr2.name);
    } else {
        printf("도적(물)이 선택되었습니다!\n");
        *Hblood = hr3.blood;
        *Hattack = hr3.attack;
        *Hdefense = hr3.defense;
        *Htype = hr3.type;
        *Hskill = hr3.skill;
        strcpy(hero_name, hr3.name);
    }

    printf("마을에 진입합니다.\n");
    printf("******************************\n\n");
}

int inventory(int *pH_attack, int *pH_defense) {
    while (1) {
        printf("******************************\n");
        printf("인벤토리입니다.\n");
        printf("현재 공격력: %d\n", *pH_attack);
        printf("현재 방어력: %d\n", *pH_defense);
        printf("보유 골드: %d\n", total_gold);
        printf("******************************\n");
        printf("장착 중인 아이템:\n");
        printf("무기: %s", equipped_weapon.name);
        if (equipped_weapon.value > 0) {
            printf(" (공격력 +%d)", equipped_weapon.value);
        }
        printf("\n");
        printf("방어구: %s", equipped_armor.name);
        if (equipped_armor.value > 0) {
            printf(" (방어력 +%d)", equipped_armor.value);
        }
        printf("\n");
        printf("******************************\n");
        printf("보유 아이템 목록:\n");
        
        if (inven_count == 0) {
            printf("(아이템 없음)\n");
        } else {
            for (int i = 0; i < inven_count; i++) {
                printf("%d. %s (", i + 1, inven_item[i].name);
                if (inven_item[i].type == 1) {
                    printf("무기, 공격력 +%d", inven_item[i].value);
                } else if (inven_item[i].type == 2) {
                    printf("방어구, 방어력 +%d", inven_item[i].value);
                }
                printf(")\n");
            }
        }
        printf("******************************\n");
        printf("0. 마을로 돌아가기\n");
        printf("선택 (아이템 번호 입력 시 장착): ");
        
        int choice;
        scanf("%d", &choice);
        
        if (choice == 0) {
            printf("마을로 돌아갑니다.\n\n");
            return 0;
        } else if (choice >= 1 && choice <= inven_count) {
            int index = choice - 1;
            Item selected = inven_item[index];
            
            if (selected.type == 1) { // 무기
                // 기존 무기 해제
                if (equipped_weapon.value > 0) {
                    *pH_attack -= equipped_weapon.value;
                    printf("%s 장착 해제 (공격력 -%d)\n", equipped_weapon.name, equipped_weapon.value);
                }
                
                // 새 무기 장착
                equipped_weapon = selected;
                *pH_attack += selected.value;
                printf("%s 장착 완료! (공격력 +%d, 현재: %d)\n\n", 
                       selected.name, selected.value, *pH_attack);
                
            } else if (selected.type == 2) { // 방어구
                // 기존 방어구 해제
                if (equipped_armor.value > 0) {
                    *pH_defense -= equipped_armor.value;
                    printf("%s 장착 해제 (방어력 -%d)\n", equipped_armor.name, equipped_armor.value);
                }
                
                // 새 방어구 장착
                equipped_armor = selected;
                *pH_defense += selected.value;
                printf("%s 장착 완료! (방어력 +%d, 현재: %d)\n\n", 
                       selected.name, selected.value, *pH_defense);
            }
        } else {
            printf("<오류> 잘못된 선택입니다.\n\n");
        }
    }
}

void enemy(int *Mblood, int *Mattack, int *Mtype, char *monster_name) {
    struct Monster {
        char name[20];
        int blood;
        int attack;
        int type;
    }; 
    
    struct Monster mst1 = {"고블린(흙)", 80, 10, 1}; // 고블린 (흙)
    struct Monster mst2 = {"트롤(불)", 100, 5, 2}; // 트롤 (불)
    struct Monster mst3 = {"오크(물)", 50, 20, 3}; // 오크 (물)
    
    int rand_choice = (rand() % 3) + 1;
    if (rand_choice == 1) {
        strcpy(monster_name, mst1.name);
        *Mblood = mst1.blood;
        *Mattack = mst1.attack;
        *Mtype = mst1.type;
    } else if (rand_choice == 2) {
        strcpy(monster_name, mst2.name);
        *Mblood = mst2.blood;
        *Mattack = mst2.attack;
        *Mtype = mst2.type;
    } else {
        strcpy(monster_name, mst3.name);
        *Mblood = mst3.blood;
        *Mtype = mst3.type;
        *Mattack = mst3.attack;
    }
    printf("몬스터: %s 등장 (HP: %d, Attack: %d)\n", monster_name, *Mblood, *Mattack);
}

int war(int *pH_blood, int *pH_attack, int *pH_defense, int H_type, int H_skill, char *hero_name) {
    int clear[NUM_DUNGEONS] = {0};
    int count = 0;
    int dungeon_choice;
    int M_blood, M_attack, M_type;
    char monster_name[20];
    int max_blood = *pH_blood;
    
    int skill_used = 0; // 스킬 사용 여부 (1회 제한)

    while(*pH_blood > 0 && count < NUM_DUNGEONS) {
        *pH_blood = max_blood; // 매 던전마다 체력 회복
        skill_used = 0; // 던전마다 스킬 초기화
        
        printf("******************************\n");
        printf("현재 체력: %d\n", *pH_blood);
        printf("완료 던전: %d / %d\n", count, NUM_DUNGEONS);
        printf("******************************\n");

        printf("입장할 던전을 선택해 주세요\n");
        for (int i = 0; i < NUM_DUNGEONS; i++) {
            printf("%d. 던전 %c %s\n", i + 1, 'A' + i, clear[i] ? "(완료)" : "");
        }
        printf("%d. 마을로 돌아가기\n", NUM_DUNGEONS + 1);
        printf("선택: ");
        
        if (scanf("%d", &dungeon_choice) != 1) {
            while (getchar() != '\n');
            printf("<오류> 유효한 숫자를 입력해 주세요.\n");
            continue;
        }

        if (dungeon_choice == NUM_DUNGEONS + 1) {
            printf("마을로 돌아갑니다.\n\n");
            return 1; // 마을로 복귀
        }

        if (dungeon_choice < 1 || dungeon_choice > NUM_DUNGEONS) {
            printf("<오류> 1부터 %d 사이의 던전을 선택해 주세요.\n", NUM_DUNGEONS);
            continue;
        }

        if (clear[dungeon_choice - 1] == 1) {
            printf("<경고> %d번 던전은 이미 클리어했습니다. 다른 던전을 선택해 주세요.\n", dungeon_choice);
            continue;
        }

        printf("******************************\n");
        printf("%d번 던전(%c)에 입장하였습니다\n", dungeon_choice, 'A' + dungeon_choice - 1);

        enemy(&M_blood, &M_attack, &M_type, monster_name);
        
        int turn = 1;
        do {
            printf("\n[%d번째 턴] %s(%d) vs %s(%d)\n", turn, hero_name, *pH_blood, monster_name, M_blood);

            // Hero 공격
            int choice;
            printf("******************************\n");
            printf("공격을 선택해주세요.\n");
            printf("1. 일반 공격 (공격력: %d)\n", *pH_attack);
            
            if (!skill_used) {
                if (strcmp(hero_name, "전사") == 0) {
                    printf("2. 스킬 사용 (공격력 +%d, 1회 한정)\n", H_skill);
                } else if (strcmp(hero_name, "궁수") == 0) {
                    printf("2. 스킬 사용 (체력 회복 +%d, 1회 한정)\n", H_skill);
                } else if (strcmp(hero_name, "도적") == 0) {
                    printf("2. 스킬 사용 (방어력 +%d, 1회 한정)\n", H_skill);
                }
            } else {
                printf("2. 스킬 이미 사용함\n");
            }
            printf("선택: ");
            
            scanf("%d", &choice);
            
            if (choice == 1) { // 일반 공격
                M_blood -= *pH_attack;
                printf("일반 공격 | 몬스터에게 %d의 피해\n", *pH_attack);
            } else if (choice == 2 && !skill_used) { // 스킬 사용
                skill_used = 1;
                if (strcmp(hero_name, "전사") == 0) { // 전사: 공격력 증가
                    int total_damage = *pH_attack + H_skill;
                    M_blood -= total_damage;
                    printf("스킬 사용 (공격력 +%d) | 몬스터에게 %d의 피해\n", H_skill, total_damage);
                } else if (strcmp(hero_name, "궁수") == 0) { // 궁수: 체력 회복
                    int before_hp = *pH_blood;
                    *pH_blood += H_skill;
                    printf("스킬 사용 | 체력 %d 회복 (%d -> %d)\n", H_skill, before_hp, *pH_blood);
                } else if (strcmp(hero_name, "도적") == 0) { // 도적: 방어력 증가
                    *pH_defense += H_skill;
                    printf("스킬 사용 | 방어력 +%d 증가 (현재 방어력: %d)\n", H_skill, *pH_defense);
                }
            } else {
                printf("<오류> 잘못된 선택입니다. 일반 공격으로 처리됩니다.\n");
                M_blood -= *pH_attack;
                printf("일반 공격 | 몬스터에게 %d의 피해\n", *pH_attack);
            }
            
            if (M_blood <= 0) {
                printf("******************************\n");
                printf("전투에서 승리했습니다\n");
                
                // 골드 획득
                int golden = (rand() % 401) + 100;
                total_gold += golden;
                printf("골드 %d원을 획득했습니다! (총 골드: %d)\n", golden, total_gold);
                
                // 아이템 드롭 (50% 확률)
                int drop_chance = rand() % 100;
                if (drop_chance < 50) {
                    int item_index = rand() % 5;
                    printf("%s이 아이템을 드롭했습니다!\n", monster_name);
                    add_item(drop[item_index]);
                }
                
                clear[dungeon_choice - 1] = 1;
                count++;
                printf("******************************\n\n");
                
                break;
            }

            // 몬스터 공격
            int monster_damage = M_attack - *pH_defense;
            if (monster_damage < 0) monster_damage = 0;
            
            *pH_blood -= monster_damage;
            printf("몬스터의 공격 | %s에게 %d의 피해 (방어력 %d로 %d 감소)\n", 
                   hero_name, monster_damage, *pH_defense, M_attack - monster_damage);
            
            if (*pH_blood <= 0) {
                printf("******************************\n");
                printf("전투에서 패배했습니다.\n");
                printf("******************************\n");
                break;
            }
            
            turn++;
        } while (*pH_blood > 0 && M_blood > 0); 

        if (*pH_blood <= 0) {
            return 0; // 사망
        }
    }
    
    printf("\n******************************\n");
    if (count == NUM_DUNGEONS) {
        printf("모든 던전을 클리어했습니다.\n");
    } else if (*pH_blood <= 0) {
        printf("체력이 모두 소진되었습니다.\n");
    }
    printf("******************************\n\n");
    
    return 1; // 클리어 또는 마을 복귀
}

void town(int *pH_blood, int *pH_attack, int *pH_defense, int H_type, int H_skill, char *hero_name) {
    while (1) {
        printf("******************************\n");
        printf("마을입니다. 무엇을 하시겠습니까?\n");
        printf("1. 인벤토리 확인\n");
        printf("2. 던전\n");
        printf("3. 캐릭터 재선택\n");
        printf("4. 상점\n");
        printf("5. 퀘스트 확인\n");
        printf("6. 종료\n");
        printf("******************************\n");
        printf("선택: ");
        
        int choice;
        scanf("%d", &choice);
        
        if (choice == 1) {
            inventory(pH_attack, pH_defense);
        } else if (choice == 2) {
            int result = war(pH_blood, pH_attack, pH_defense, H_type, H_skill, hero_name);
            if (result == 0) {
                // 전투 결과 HP 0
                return;
            }
            // 마을로 복귀
        } else if (choice == 3) {
            printf("캐릭터 선택 화면으로 돌아갑니다.\n\n");
            return;
        } else if (choice == 4) {
            store(pH_attack, pH_defense);
        } else if (choice == 5) {
            printf("퀘스트 기능은 아직 구현되지 않았습니다.\n\n");
        } else if (choice == 6) {
            printf("게임을 종료합니다.\n");
            exit(0);
        } else {
            printf("<오류> 잘못된 선택입니다.\n\n");
        }
    }
}

int main() {
    // 게임 시작
    game_initialize();

    while(1){
        inven_count = 0;
        total_gold = 0; // 새 캐릭터는 골드 초기화
        
        // 장착 아이템 초기화
        strcpy(equipped_weapon.name, "없음");
        equipped_weapon.value = 0;
        strcpy(equipped_armor.name, "없음");
        equipped_armor.value = 0;
        
        int H_blood, H_attack, H_type, H_defense, H_skill;
        char hero_name[10];

        int* pH_blood = &H_blood;
        int* pH_attack = &H_attack;
        int* pH_type = &H_type;
        int* pH_defense = &H_defense;
        int* pH_skill = &H_skill;
        char* pH_name = hero_name;
        
        character(pH_blood, pH_attack, pH_defense, pH_type, pH_skill, pH_name);
        town(pH_blood, pH_attack, pH_defense, H_type, H_skill, pH_name);

        if (H_blood <= 0) {
            printf("\n캐릭터가 사망했습니다. 마을로 돌아갑니다.\n");
            printf("계속하시겠습니까?\n");
            printf("1: 예\n");
            printf("0: 아니오\n");

            int continue_game;
            scanf("%d", &continue_game);
            if (continue_game != 1) {
                printf("게임을 종료합니다.\n");
                break;
            }

            printf("\n******************************\n");
            printf("마을로 돌아갑니다.\n");
            printf("******************************\n\n");
        }
    }
    return 0;
}