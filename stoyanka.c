#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

long int sizeFile( FILE *f)
{
    long int pos, size;
    pos = ftell(f);
    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    fseek(f, pos, SEEK_SET);
    return(size);
}

int main()
{
    setlocale(LC_ALL, "rus");
    FILE *cars = fopen("car.txt", "r");
    char str_buf[500];  //побуквенный сбор с документа
    char sort[500][500];  //сортировка машин, взятые из str_buf
    char *mesta[8];  //количество мест на стоянке
    char c;
    int i = 0, j = 0, k = 0;


    if(sizeFile(cars) > 500)//ошибка если будет >500 символов
    {
        printf("Ошибка, файл слишком большой");
        return(1);
    }

    while(1)
    {
        c = fgetc(cars);
        if(c == EOF)
            break;
        else
            str_buf[i] = c;
        i++;
    }
    for(i = 0; str_buf[i] != '\0'; i++)
    {
        if(str_buf[i] != '\n')
        {
            sort[j][k] = str_buf[i];
            k++;
        }
        else
        {
            j++;
            k = 0;
        }
    }
    fclose(cars);
    for(i = 0; i < 8; i++)
        mesta[i] = sort[rand()%8];
    for(i = 0; i < 10; i++)
    {
        if(rand()%2 == 1) // Встанет ли машина в очеред или нет
            if(mesta[0]=='\0')
            {
                mesta[0] = sort[i%7];
                printf("\nStatus: %s Встала в очередь", sort[i%8]);
            }
            else
                printf("\nStatus: %s не смогла заехать на стоянку", sort[i%8]);
        for(j = 0; j < 8; j++) // Спрос на то кто хочет уехать со стоянке
            if(rand() % 2 == 1)
                if(j >= 5)     // Если кто то на 3-ёх последних местах хочет то пусть валит
                {
					printf("\nStatus: %s выехала из стояки", mesta[j]);
                    mesta[j] = '\0';
                }else
                    printf("\nStatus: %s не смогла выехать из стоянки", mesta[j]);
        for(int j = 6; j >= 0; j--)  // Цикл для свдига очереди
            if(mesta[j+1] == '\0')
            {
                mesta[j+1] = mesta[j];
                mesta[j] = '\0';
            }
    }
    return 0;
}
