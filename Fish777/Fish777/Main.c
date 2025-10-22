#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <direct.h> // _mkdir 사용 (log 폴더 자동 생성)

struct Fish {
    char* name;
    char* talk;
    int answer;
    char* talk_O;
    char* talk_X;
};

int main() {
    struct Fish fishes[5] = {
        {"세자르", "문제: 2+2는?\n1)3 2)4 3)5\n정답 번호 >", 2, "정답이군! 훌륭해!", "하하! 틀렸지!"},
        {"니모", "문제: 바다는 몇 %%가 물일까?\n1)71 2)50 3)90\n정답 번호 >", 1, "지식이 풍부하군!", "다시 공부해!"},
        {"피쉬", "문제: 물고기는 어디서 살까?\n1)물 2)불 3)흙\n정답 번호 >", 1, "맞아, 물속이지!", "그건 아니야!"},
        {"구피", "문제: C언어에서 printf는?\n1)입력 2)출력 3)계산\n정답 번호 >", 2, "완벽해!", "아쉽군..."},
        {"금붕어", "문제: 컴파일러는 무엇일까?\n1)번역기 2)그릇 3)물고기\n정답 번호 >", 1, "멋지다!", "하하 틀렸네!"}
    };

    FILE* fp = NULL;
    int correct = 0;
    int games_played = 0;
    errno_t err;

    // ---------------------------
    // [1] log 폴더 자동 생성
    // ---------------------------
    _mkdir("log"); // 이미 있으면 무시됨

    // ---------------------------
    // [2] 기존 기록 읽기 (정답률 계산용)
    // ---------------------------
    err = fopen_s(&fp, "./log/log.txt", "r");
    if (err != 0 || fp == NULL) {
        perror("log/log.txt 열기 실패(읽기 모드)");
    }
    else {
        char name_line[256];
        char result_line[256];

        while (fgets(name_line, sizeof(name_line), fp) != NULL) {
            if (fgets(result_line, sizeof(result_line), fp) == NULL)
                break; // 짝이 안 맞는 경우 방지
            games_played++;
            if (result_line[0] == 'O')
                correct++;
        }

        if (ferror(fp))
            perror("log/log.txt 읽기 중 오류");

        if (fclose(fp) == EOF)
            perror("log/log.txt 닫기 실패(읽기)");
    }

    int next_game = games_played + 1;
    printf("%d번째 게임입니다!\n", next_game);
    if (games_played == 0)
        printf("정답률 0/0 (첫 게임입니다!)\n\n");
    else
        printf("정답률 %d/%d\n\n", correct, games_played);

    // ---------------------------
    // [3] 찌 던지기 입력
    // ---------------------------
    printf("찌를 던진다 (Y/N) > ");
    char yn = _getch();
    printf("%c\n", yn);
    if (yn != 'Y' && yn != 'y') {
        printf("게임을 종료합니다.\n");
        return 0;
    }

    printf("던지는 중");
    for (int i = 0; i < 5; i++) {
        Sleep(500);
        printf(".");
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    printf("\n입질이 왔다!!!!\n");
    SetConsoleTextAttribute(hConsole, 7);

    // ---------------------------
    // [4] 랜덤 물고기 선택 및 퀴즈 출제
    // ---------------------------
    srand((unsigned)time(NULL));
    int fishIndex = rand() % 5;
    struct Fish current = fishes[fishIndex];
    printf("%s : %s", current.name, current.talk);

    int userAnswer;
    scanf_s("%d", &userAnswer);

    // ---------------------------
    // [5] 결과 저장 (log/log.txt에 누적)
    // ---------------------------
    err = fopen_s(&fp, "./log/log.txt", "a");
    if (err != 0 || fp == NULL) {
        perror("log/log.txt 열기 실패(쓰기 모드)");
        return EXIT_FAILURE;
    }

    if (fprintf(fp, "%s\n", current.name) < 0) {
        perror("이름 기록 실패");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (userAnswer == current.answer) {
        printf("%s\n", current.talk_O);
        if (fprintf(fp, "O\n") < 0) perror("정답 기록 실패");
    }
    else {
        printf("%s\n", current.talk_X);
        if (fprintf(fp, "X\n") < 0) perror("오답 기록 실패");
    }

    if (fclose(fp) == EOF) {
        perror("log/log.txt 닫기 실패(쓰기)");
        return EXIT_FAILURE;
    }

    printf("\n게임이 종료되었습니다.\n");
    return 0;
}
