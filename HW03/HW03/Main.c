#include <stdio.h>
#include <windows.h>

// ��ź�� ���� �� ��µǴ� �Լ� (�̹� �����Ǿ� �ִٰ� ����)
void printBomb(int frame) {
    printf("\033[14;7H");
    printf("     ");
    printf("\033[15;7H");
    printf(" BOOM");
    printf("\033[16;7H");
    printf("     ");
}

// Ŀ�� �̵��� �Լ�
void gotoxy(int y, int x) {
    printf("\033[%d;%dH", y, x);
}

// ���� ��� ����: (y, x)
int fuse[][2] = {
    {14, 9}, {13, 9}, {12, 9}, {11, 9}, {10, 9},
    {10,10}, {10,11}, {10,12},
    {11,12}, {12,12}, {13,12}, {14,12},
    {14,11}, {14,10}
};
int fuseLength = sizeof(fuse) / sizeof(fuse[0]);

int main() {
    // 1. ���� �׸���
    for (int i = 0; i < fuseLength; i++) {
        gotoxy(fuse[i][0], fuse[i][1]);
        printf("#");
    }

    // 2. ��ź �׸��� (B�� ���� �� ��ġ + 1 �Ʒ���)
    gotoxy(15, 9);
    printf("B");

    // 3. ������ ���� * �̵�
    for (int i = 0; i < fuseLength; i++) {
        // ���� ��ġ�� *
        gotoxy(fuse[i][0], fuse[i][1]);
        printf("*");

        // ���� ��ġ ����� (����)
        if (i > 0) {
            gotoxy(fuse[i - 1][0], fuse[i - 1][1]);
            printf(" ");
        }

        Sleep(200);
    }

    // 4. ����
    printBomb(1);

    // Ŀ�� �Ʒ��� �̵� (������)
    gotoxy(18, 1);
    return 0;
}
