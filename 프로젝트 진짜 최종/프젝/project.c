/*
    프로젝트명 : Number Baseball

    설명 :
    사용자가 서로 다른 숫자 3개를 입력하여
    컴퓨터가 생성한 랜덤 숫자를 맞히는 게임이다.

    기능 :
    1. 난이도 선택
    2. 숫자 중복 검사
    3. 스트라이크/볼 판정
    4. 시도 횟수 기록
    5. 하드 모드 클리어 시 이스터에그 출력
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "project.h"

void is_answer(int *random, int *answer, int *ba, int *st);

int main(){
    // 난수 생성 시드 설정
    srand(time(NULL));

    // 메인 메뉴
    while(1){
        main_menu();
    }

    return 0;
}

void main_menu(){

    line();
    printf("    number baseball");
    line();

    printf("1. 게임 설명\n");
    printf("2. 게임 시작\n");
    printf("3. 나가기");

    line();

    input();

    // 메뉴 입력을 문자열로 받아서
    // "abc" 같은 잘못된 입력을 걸러냄
    char in[10] = {'\0'};
    fgets(in, 10, stdin);
    
    // 입력이 한 글자인 경우만 정상 처리
    if(in[1] == '\n'){
        if(in[0] == '1'){
            manual();
        }
        else if(in[0] == '2'){
            game();
        }
        else if(in[0] == '3'){
            printf("끝!\n");
            exit(0);
        }
        else{
            printf("잘못된 입력이야! 다시 설명을 잘 읽고 입력해줘!");
        }
    }else{
        printf("잘못된 입력이야! 다시 설명을 잘 읽고 입력해줘!");
    }
}


void main_menu();
void eg();

void line(){
    printf("\n");
    for(int i=0; i<30; i++){
        printf("=");
    }
    printf("\n");
}

void input(){
    printf("입력 => ");
} 

void message(int min, int max){
    line();
    printf("잘못된 입력이야!\n숫자가 %d~%d까지의 숫자인지 혹은 숫자끼리 띄어서 쓰셨는지 다시 확인해봐!",min,max);
    printf("\n숫자끼리 겹쳐도 안돼!");
    line();
    input(); 
}

void manual(){
    line();
    printf("숫자 야구 규칙\n\t●서로 다른 숫자 3자리를 맞히는 게임입니다.\n\t●숫자는 중복되지 않게 정해짐 (예: 1, 4, 7 / 3, 1, 6).\n\t●추측한 숫자를 부르면 결과를 알려줌\n======================================================\n판정 규칙\n\t●스트라이크(S): 숫자와 자리(위치)가 모두 맞음\n\t●볼(B): 숫자는 있지만 자리가 틀림\n=======================================================\n예시 (정답이 123일 때)\n\t●145 → 1S 0B.\n\t●231 → 0S 3B.\n\t●123 → 정답.");
}

int select_level(){
    // 난이도에 따라 랜덤 숫자 범위 설정
    int num_range = 0;

    line();
    printf("난이도를 설정합시다!\n1. easy\n2. normal\n3. hard\n");
    printf("easy는 숫자 1~9, normal은 숫자 1~20, hard는 숫자 1~50\n");
    line();

    input();

    // 난이도 입력 검사용 문자열
    char stage[10] = {'\0'};
    fgets(stage, 10, stdin);

    line();
    // 한 글자 입력만 허용
    if(stage[1] == '\n'){
        if(stage[0] == '1'){
            printf("난이도가 easy로 설정되었습니다!\n");
            printf("숫자가 1에서 9사이에서 숫자가 설정됩니다.");
            num_range = 9;
        }
        else if(stage[0] == '2'){
            printf("난이도가 normal로 설정되었습니다!\n");
            printf("숫자가 1에서 20사이에서 숫자가 설정됩니다.");
            num_range = 20;
       }
        else if(stage[0] == '3'){
            printf("난이도가 hard로 설정되었습니다!\n");
            printf("숫자가 1에서 50사이에서 숫자가 설정됩니다.");
            num_range = 3;
        }
        else{
            printf("잘못된 입력입니다!\n");
            printf("다시 한 번 입력해주세요!");
            game();
            return 0;
        }
    }else{
        printf("잘못된 입력입니다!\n");
        printf("다시 한 번 입력해주세요!");
        game();
        return 0;
    }
    return num_range;
}

void game(){
    int num_range = select_level();

    line();
    printf("숫자 3개를 띄어쓰기로 구분해서 입력해줘!\n같은 숫자를 입력해도 안돼!");
    line();
    input();

    // 컴퓨터가 생성한 정답 숫자 저장
    int random[3];

    // 서로 다른 랜덤 숫자 3개 생성
    for(int i=0; i<3; i++){
        while(1){
            random[i] = rand()%num_range+1;

            int cnt = 0;

            // 이전 숫자들과 중복되는지 검사
            if(i > 0 && random[i] == random[i-1]){
                if(random[i] > 1){
                    random[i] = rand()%num_range+1;
                }
                else{
                    random[i] = rand()%num_range+1;
                }
            }
            else{
                cnt++;
            }
            // 첫 번째 숫자와도 중복되는지 검사
            if(i > 1 && random[i] == random[i-2]){
                if(random[i] > 1){
                    random[i] = rand()%num_range+1;
                }
                else{
                    random[i] = rand()%num_range+1;
                }
            }
            else{
                cnt++;
            }

            if(cnt >= 2) break;
        }
    }

    // 플레이어가 몇 번 시도했는지 저장
    int try_count = 0;

    while(1){

        int st = 0;
        int ba = 0;
        int error = 0;

        // 사용자가 입력한 숫자 초기화
        int answer[3] = {-1,-1,-1};

        for(int i=0; i<3; i++){
        
        // 숫자가 아닌 문자 입력 방지
        if(scanf("%d",&answer[i]) != 1){
            printf("문자를 입력하면 어떡해!!\n다시 입력해줘!");
            line();
            input();
            while(getchar() != '\n');

            error++;
            break;
        }

    // 허용 범위를 벗어난 숫자 검사
    if(answer[i] > num_range || answer[i] <= 0){
        message(1,num_range);
        error++;
        break;
    }
}

        if(error > 0) continue;

        // 입력 숫자끼리 중복 검사
        if(answer[0] == answer[1] ||
           answer[0] == answer[2] ||
           answer[1] == answer[2]){
            message(1,num_range);
            continue;
        }

        // 정상적인 시도일 때만 카운트 증가
        try_count++;

        // 스트라이크와 볼 개수 계산
        is_answer(random, answer, &ba, &st);

        // 3스트라이크면 게임 종료
        if(st == 3){

            printf("3스트라이크~! 숫자 %d %d %d를 맞췄어!",
                   random[0],random[1],random[2]);

            printf("\n총 %d번 만에 맞췄어!", try_count);

            if(num_range == 3){
                eg();
                exit(0);
            }
            line();
            printf("메인메뉴로 이동합니다.");
            break;
        }

        printf("%d회, %d스트라이크, %d볼~!",try_count,st,ba);
        line();
        input();
    }
    return;
} 

// 정답 배열과 사용자 입력을 비교하여
// 스트라이크와 볼 개수 계산
void is_answer(int random[], int answer[], int *ba, int *st){
    // 모든 숫자를 서로 비교
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){

            // 숫자가 같은 경우
            if(random[i] == answer[j]){
                // 위치까지 같으면 스트라이크
                if(i == j){
                    *st = *st + 1;
                }
                // 숫자만 같으면 볼
                else{
                    *ba = *ba + 1;
                }
            }
        }
    }
}

void eg(){
    // 이스터에그 텍스트 파일 출력
    FILE *file = fopen("egg.txt", "r");
    char c;
    c = fgetc(file);
    // 한 글자씩 출력하면서 딜레이 적용
    while(c!=EOF){
        putchar(c);
        c = fgetc(file);
        Sleep(10);
    }
    fclose(file);
}
