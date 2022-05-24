#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// int Suffix(FILE *input, char *text, char *substring)
// {
//     int text_length = FileLength(input);
//     int substring_length = strlen(substring);
//     int i = 0;
//     int j = 0;

//     for (i = 0; i < text_length; i++)
//     {
//         if (text[i] == substring[j]){
//             j++;
//             continue;
//         }else{
//             j = 0;
//         }
//         if (j == substring_length) return i;
//     }

//     puts("Have no prefix");
//     return 0;
// }

// int Suffix(FILE *input, char *text, char *substring)
// {
//     if (feof(input)) return -1;

//     int text_length = FileLength(input);
//     int substring_length = strlen(substring);

//     int i = ftell(input);
//     int suffix = 0;

//     while (i < text_length)
//     {
//         i = ftell(input);
//         if (text[i] == substring[suffix]){
//             ++suffix;
//             if (suffix == substring_length) return suffix;
//             continue;
//         }else{
//             return suffix;
//         }
//         fseek(input, 1, SEEK_CUR);
//     }
    
//     //if (getchar(input) == EOF && suffix != 0) return -1; dont uncommment

//     return suffix;
// }

typedef struct {
    int current_state;
	char read_char; 
	int next_state;
} State;

//Finite-state machine
int FSM(FILE *input, char *sample)
{
    char *text;
    text = FileTextInArray(input);

    int file_length = FileLength(input);

    State state;
    state.current_state = 0;



    int i = 0;
    int j = 0;
    for (; i < file_length; i++)
    {
        if (text[i] == sample[j]){
            j++;
            state.current_state = 1;
            StateTransition(state.current_state, text, i);    
        }        
    }
}

int StateTransition(int current_state, char *text, int current_symbol)
{
    int j = 1;
    for (; i < count; i++)
    {
        
    }
    
}

int FileLength(FILE *input)
{
    fseek(input, 0, SEEK_END);
    int file_length = ftell(input);
    fseek(input, 0, SEEK_SET);
    return file_length;
}

char* FileTextInArray(FILE *input)
{
    int file_length = FileLength(input);
    char *file_text = malloc(file_length);
    if (file_text == NULL) exit(1);

    int i = 0;
    char ch;
    while ( (ch = fgetc(input) ) != EOF){
        file_text[i] = ch;
        ++i;
    }

    return file_text;
}

void FileFree(char *file_text)
{
    free(file_text);
}

void generate_file()
{
    FILE *file;
    file = fopen("text.le", "w");
    int number;
    char c;
    for (int i = 0; i < 1000000; i++)
    {
        number = rand() % 2;
        c = number + 97;
        fprintf(file, "%c", c);
    }
    fclose(file);
}

int main()
{
    srand(time(NULL));
    generate_file();
    FILE *input, *suf_test;
    char subsrting[] = "aaabab";
    if ( (input = fopen("input.le", "r")) == NULL) return 0;
    printf("Введите строку для поиска: ");

    if ( (suf_test = fopen("input.le", "r")) == NULL) return 0;

    char *file_text = NULL;
    int file_length = FileLength(input);
     = FileTextInArray(input);
    
    // ПРОТЕСТИРУЙ ФУНКЦИЮ СУФФИКС
    // АВТОМАТЫ ЧЕРЕЗ СВИТЧ КАЙС
    // ШАБЛОНЫ: ПЕРЕХОД ЕСЛИ ЕСТЬ СИМВОЛ ЕСТЬ В МАССИВЕ ШАБЛОНА
    
    while(1){
        Suffix(suf_test, );
    }

    FileFree(file_text);
    fclose(input);
    puts("Okay");
}