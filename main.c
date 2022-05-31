#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    unsigned char current;
	signed char sym; // signed, для обозначения свободного перехода как -1.
	unsigned char next;
} State; 


// int Suffix(char *text, FILE *input, int *caret, char *sample)
// {
//     int file_length = FileLength(input);
//     int sample_length = strlen(sample);
//     int symb = 0;

//     for (; *caret < file_length; symb++)
//     {
//         (*caret)++;
//         if (symb == sample_length) break;

//         if (text[*caret - 1] == sample[symb]){
//             continue;
//         }else{
//             break;
//         }
//     }
//     return symb;

//     // (*caret)++;
//     //     if ( !(text[*caret] == sample[symb]) || symb == sample_length){
//     //         return symb;
//     //     }
//     //     symb++;
// }

//Finite-state machine
int FSM(FILE *input, char *sample)
{
    char *text;
    int caret;
    text = FileTextInArray(input);
    int file_length = FileLength(input);
    

    State *finite_machine;
    finite_machine = malloc(sizeof(*finite_machine) * strlen(sample));

    for (int i = 0; i < strlen(sample); i++)
    {
        finite_machine[i].current = i;
        finite_machine[i].sym = sample[i]; //здесь сделать свитч для шаблона
        finite_machine[i].next = i + 1;
    }

    int current_state = 0;
    while (caret < file_length)
    {
        if (current_state == strlen(sample) + 1) break; ////////////////////////////////////////////////////////////////сделать функцию подсветки текста

        if (finite_machine[current_state].sym == text[caret]){
            current_state = finite_machine[current_state].next;
            caret++;
            continue;
        }else{
            current_state = 0;
        }
        
    }
}

//finite inpite alphabet
char FI_alph()
{
    
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

Compute_transition(char *sample, char input_symbol)
{
    ;
}

Suffix_function(char *sample, )
{

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