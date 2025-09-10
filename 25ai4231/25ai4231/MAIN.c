#include <stdio.h>
#include <time.h>   // 딜레이용 (sleep 대용)

void drawStar(int x, int y) {
    printf("\x1B[%d;%dH", y, x);
    printf("*");
    fflush(stdout);
}

void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

int main() {
    int width = 6;
    int height = 5;

    printf("\x1B[2J");    // 화면 클리어
    printf("\x1B[?25l");  // 커서 숨기기

    int row = 1;
    int col = 1;

    while (row <= height) {
        if (row == 1 || row == height) {
            // 첫 줄, 마지막 줄: 모든 칸에 별
            drawStar(col, row);
            delay(200);  // 0.2초 딜레이
            col++;
            if (col > width) {
                col = 1;
                row++;
            }
        }
        else {
            // 중간 줄: 양끝만 별
            if (col == 1 || col == width) {
                drawStar(col, row);
                delay(200);
            }
            col++;
            if (col > width) {
                col = 1;
                row++;
            }
        }
    }

    printf("\x1B[?25h");              // 커서 보이기
    printf("\x1B[%d;1H", height + 2); // 커서 위치 마지막 줄 아래로 이동

    printf("실행이 시작되고 종료됩니다.\n");

    return 0;
}
