// 2 вариант. Написать программу, которая в качестве аргументов командной строки принимает заданное слово
// и имена текстовых файлов. Посчитать медиану вхождений слова в документы.
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// argc - ин-ция о кол-ве аргументов в командной строке, argv - хранит адрес начала аргументов командной строки
int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "Rus");

    int max_size=100;        //максимальная длина строки
    char line[max_size];    //line - массив символов, где будут хранится строки

    if(argc<2)
    {
        printf("Вы забыли ввести слово. \n");
        exit(1);
    }

    char *word=argv[1]; //argv[0] указывает на имя программы
    int len_word=strlen(word);
    printf("Искомое слово: %s\n", word);
    printf("\n");
    //printf(argv[2]);

    int i;
    int count_mass[argc-2]; // чтобы получить кол-во документов надо вычесть: 1 аргумент- название программы, 2 аргумент - искомое слово
    FILE *TextFile;
    for(i=2; i<argc; i++)
    {
        //чтобы открыть файл, надо прописать полный путь к нему. Project->Set param's arguments
        TextFile=fopen(argv[i], "r");
        if (TextFile==NULL)
        {
            printf("Файл не существует, либо он пустой \n");
            exit(1);
        }

        int count=0;
        while (fgets(line, max_size, TextFile)) //считываем строки файла
        {
            printf("Текст файла: %s\n", line);

            char *pos=line;   //позиция, с которой продолжается поиск слова, после нахождения предыдущего вхождения
            while (pos=strstr(pos, word)) // strstr возвращает указатель 1 вхождения word в строку pos. Пока есть вхождения повторяем цикл
            {
                char *k=pos; //позиция вхождения послед-ти символов, составляющих слово
                pos+=len_word; //наращиваем позицию на длину найденного слова
                if (k!=line) //если слово не в начале строки, то проверяем стоящий перед словом символ
                    if ( !ispunct(*(k-1)) && !isspace(*(k-1)) ) // если символ перед словом не знак пунктуации и не пробел, то
                        continue; // переходим к следующей итерации
                if (ispunct(*pos) || isspace(*pos) || (*pos=='\0')) //если символ после слова - это знак пунктуации, пробел или конец строки, то
                    count++;

            }

        }
        printf("Количество вхождений слова: %d\n", count);
        count_mass[i-2]=count; //т.к. i начинается с 2
        fclose(TextFile);
        printf("\n");

    }

    // для вычисления медианы надо отсортировать массив по возрастанию и выбрать число, стоящее
    // посередине массива. Если кол-во элементов массива четное, то найти среднее арифметическое элементов,
    // стоящих посередине.

    //сортируем массив методом пузырька для нахождения медианы
    int sz=argc-2;
    int tmp;
    int flag;

    int j;
    float mediana=0.0;
    if (sz>1)
    {
        for (i=sz-1; i>=0; i--)
        {
            flag=1;
            for(j=0; j<i; j++)
            {
                if (count_mass[j]>count_mass[j+1])
                {
                    tmp = count_mass[j];
                    count_mass[j]=count_mass[j+1];
                    count_mass[j+1]=tmp;
                    flag=0;
                }
            }
            if (flag==1)
                break;
        }

        printf("Отсортированный по возрастанию массив вхождений слова во все файлы: \n");

        for(i=0; i<sz; ++i)
        {
            printf("%d ", count_mass[i]);
        }
        printf("\n");

        if (sz % 2 != 0)
        {
            mediana=count_mass[sz / 2 +1];
        }
        else
        {
            mediana=count_mass[sz / 2 - 1] ;
        }
    }
    else
    {
        printf("Для вычисления медианы нужно минимум два текстовых документа \n");
        mediana =0.0;
    }

    printf("Медиана: %f\n", mediana);


    return 0;
}
