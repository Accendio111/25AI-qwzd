#include <stdio.h>
#include <windows.h>

// 폭탄이 터질 때 출력되는 함수 (이미 구현되어 있다고 가정)
void printBomb(int frame) {
    printf("\033[14;7H");
    printf("     ");
    printf("\033[15;7H");
    printf(" BOOM");
    printf("\033[16;7H");
    printf("     ");
}

// 커서 이동용 함수
void gotoxy(int y, int x) {
    printf("\033[%d;%dH", y, x);
}

// 심지 경로 저장: (y, x)
int fuse[][2] = {
    {14, 9}, {13, 9}, {12, 9}, {11, 9}, {10, 9},
    {10,10}, {10,11}, {10,12},
    {11,12}, {12,12}, {13,12}, {14,12},
    {14,11}, {14,10}
};
int fuseLength = sizeof(fuse) / sizeof(fuse[0]);

int main() {
    // 1. 심지 그리기
    for (int i = 0; i < fuseLength; i++) {
        gotoxy(fuse[i][0], fuse[i][1]);
        printf("#");
    }

    // 2. 폭탄 그리기 (B는 심지 끝 위치 + 1 아래쪽)
    gotoxy(15, 9);
    printf("B");

    // 3. 심지를 따라 * 이동
    for (int i = 0; i < fuseLength; i++) {
        // 현재 위치에 *
        gotoxy(fuse[i][0], fuse[i][1]);
        printf("*");

        // 이전 위치 지우기 (공백)
        if (i > 0) {
            gotoxy(fuse[i - 1][0], fuse[i - 1][1]);
            printf(" ");
        }

        Sleep(200);
    }

    // 4. 폭발
    printBomb(1);

    // 커서 아래로 이동 (마무리)
    gotoxy(18, 1);
    return 0;
}
