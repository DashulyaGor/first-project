#include <stdio.h>
#define NMAX 10

int main() {
    int data[NMAX]; //статический массив
    int counter = 0, flag = 1; //предполагаем верный выход
    for(int i = 0; i < NMAX; i++) {
        if(scanf("%d", &data[i]) == 1) {
            if(data[i] == -1) {
                break;
            } else {
                counter++;
            }
        } else {
            flag = 0; //false ошибка ввода
            break;
        }
    }

    if(flag == 1) {
        if(counter % 2 == 0) { //если четное количество элементов
            for(int j = 0; j < counter / 2; j++) {
                if(j != 0) {
                    printf(" ");
                }
                printf("%d", data[j]);
                printf("%d", data[counter - 1 - j]);
            }
        } else {
            for (int j = 0; j < counter / 2; j++) {
                printf("%d", data[j]);
                printf("%d", data[counter - 1 - j]);
            }
            printf("%d", data[counter/2]);
        }
    } else {
        printf("n/a");
    }
    return 0;
}