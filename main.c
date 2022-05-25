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
    int *state_count;
    int current_state;
	char read_char; 
	int next_state;
    char *sample;
} State;

int Suffix(char *text, FILE *input, int *caret, char *sample)
{
    int file_length = FileLength(input);
    int sample_length = strlen(sample);
    int symb = 0;
    for (; *caret < file_length; (*caret)++)
    {
        if ( !(text[*caret] == sample[symb]) || symb == sample_length){
            (*caret)++;
            return symb;
        }
        symb++;
    }
    return -1;
}

// //Finite-state machine
// int FSM(FILE *input, char *sample)
// {
//     char *text;
//     text = FileTextInArray(input);

//     int file_length = FileLength(input);

//     State state;
//     state.current_state = 0;
//     state.sample = sample;

//     int i = 0;
//     int j = 0;
//     for (; i < file_length; i++)
//     {
//         if (text[i] == state.sample[j]){
//             state.current_state = 1;
//             ComputeTransition(state);
//         }

//     }
// }

// CreateFSMSample(char *sample, State state)
// {
//     state.state_count = malloc(sizeof(int) * File);
// }

// ComputeTransition(State state)
// {
//     for ( i = 0; i < count; i++)
//     {
//         /* code */
//     }
    
// }

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

    fseek(input, 0 , SEEK_SET);
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
    for (int i = 0; i < 100; i++)
    {
        number = rand() % 2;
        c = number + 97;
        fprintf(file, "%c", c);
    }
    fclose(file);
}

int main()
{
    //srand(time(NULL));
    //generate_file();
    FILE *input;
    char sample[] = "aab";
    if ( (input = fopen("text.le", "r")) == NULL) return 0;

    char *file_text = NULL;
    int file_length = FileLength(input);
    file_text = FileTextInArray(input);

    
    // ПРОТЕСТИРУЙ ФУНКЦИЮ СУФФИКС
    // АВТОМАТЫ ЧЕРЕЗ СВИТЧ
    // ШАБЛОНЫ: ПЕРЕХОД ЕСЛИ ЕСТЬ СИМВОЛ ЕСТЬ В МАССИВЕ ШАБЛОНА
    
    int caret = 0;
    int result = 0;
    int i = 1;
    while(caret < file_length){
        result = Suffix(file_text, input, &caret, sample);
        printf("%d. %d\n", i, result);
        ++i;
    }

    FileFree(file_text);
    fclose(input);
    puts("Okay");
}