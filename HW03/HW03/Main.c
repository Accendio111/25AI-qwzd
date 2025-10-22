#include <stdio.h>
#include <stdlib.h>

#define KEY_A 97
#define KEY_Z 123

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int random[KEY_Z - KEY_A + 1];

    // �迭 �ʱ�ȭ
    int i = 0;
    for (i = 97; i < KEY_Z; i++)
    {
        random[i - KEY_A] = 0;
    }

    // ���� ���ĺ� ä���
    for (i = 0; i < KEY_Z - KEY_A; i++)
    {
        while (1)
        {
            int rand_index = rand() % (KEY_Z - KEY_A);
            if (random[rand_index] == 0)
            {
                random[rand_index] = (char)(i + KEY_A);
                break;
            }
        }
    }

    int sort[KEY_Z - KEY_A];
    for (i = 0; i < KEY_Z - KEY_A; i++) {
        sort[i] = random[i];
    }

    // ���� ����
    for (int j = 0; j < KEY_Z - KEY_A - 1; j++) {
        for (int k = 0; k < KEY_Z - KEY_A - 1 - j; k++) {
            if (sort[k] > sort[k + 1]) {
                swap(&sort[k], &sort[k + 1]);
            }
        }
    }

    // ��� ��� (�ƽ�Ű�ڵ� ���ڵ� ���� ���)
    printf("\tIndex\trandom\t\tsort\n");
    for (i = 0; i < KEY_Z - KEY_A; i++) {
        printf("\t%c(%d)\t%c\t\t%c\n", i + KEY_A, i + KEY_A, random[i], sort[i]);
    }

    return 0;
}
