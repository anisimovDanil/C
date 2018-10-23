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
    char str_buf[500];  //����������� ���� � ���������
    char sort[500][500];  //���������� �����, ������ �� str_buf
    char *mesta[8];  //���������� ���� �� �������
    char c;
    int i = 0, j = 0, k = 0;


    if(sizeFile(cars) > 500)//������ ���� ����� >500 ��������
    {
        printf("������, ���� ������� �������");
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
        if(rand()%2 == 1) // ������� �� ������ � ������ ��� ���
            if(mesta[0]=='\0')
            {
                mesta[0] = sort[i%7];
                printf("\nStatus: %s ������ � �������", sort[i%8]);
            }
            else
                printf("\nStatus: %s �� ������ ������� �� �������", sort[i%8]);
        for(j = 0; j < 8; j++) // ����� �� �� ��� ����� ������ �� �������
            if(rand() % 2 == 1)
                if(j >= 5)     // ���� ��� �� �� 3-�� ��������� ������ ����� �� ����� �����
                {
					printf("\nStatus: %s ������� �� ������", mesta[j]);
                    mesta[j] = '\0';
                }else
                    printf("\nStatus: %s �� ������ ������� �� �������", mesta[j]);
        for(int j = 6; j >= 0; j--)  // ���� ��� ������ �������
            if(mesta[j+1] == '\0')
            {
                mesta[j+1] = mesta[j];
                mesta[j] = '\0';
            }
    }
    return 0;
}
