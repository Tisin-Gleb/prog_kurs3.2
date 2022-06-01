#define CHAR_BORD 256
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"FSM.h"
#include <sys/types.h>
#include <dirent.h>
#include<stdint.h>

#define CSI "\x1B\x5B"
char colors[][5] = {
    "0;30", /* Black */ "1;30", /* Dark Gray */
    "0;31", /* Red */ "1;31", /* Bold Red */
    "0;32", /* Green */ "1;32", /* Bold Green */
    "0;33", /* Yellow */ "1;33", /* Bold Yellow */
    "0;34", /* Blue */ "1;34",   /* Bold Blue */
    "0;35", /* Purple */ "1;35", /* Bold Purple */
    "0;36", /* Cyan */ "1;36" /*Bold Cyan */
    };

int colors_sz = sizeof(colors) / sizeof(colors[0]);

DIR *opendir(const char *name);
int closedir(DIR *dirp);
struct dirent *readdir(DIR *dirp);

//функция перехода
int getNextState(char *sample, int substr_len, int state, int x)
{ 
    if (state < substr_len && x == sample[state]){
        return state+1;
    }
    int next_state, i;
 
    for (next_state = state; next_state > 0; next_state--)
    {
        if (sample[next_state-1] == x)
        {
            for (i = 0; i < next_state-1; i++){
                if (sample[i] != sample[state-next_state+1+i])
                    break;
            }
            if (i == next_state-1)
                return next_state;
        }
    }
 
    return 0;
}

void printTable(int **TF, int substr)
{
    for (int i = 0; i < substr + 1; i++){
        for (int j = 0; j < CHAR_BORD - 140; j++){
            printf("%d ", TF[i][j]);
        }
        puts("");
    }
    puts("");
}

//строит таблицу переходов
void computeTF(char *sample, int substr_len, int **TF)
{
    int state, x;
    for (state = 0; state <= substr_len; ++state){
        for (x = 0; x < CHAR_BORD; ++x){
            TF[state][x] = getNextState(sample, substr_len, state, x);
        }
    }
    
}

void freeMemory(int **TF)
{
    // for (int i = 0; i < CHAR_BORD; i++)
    // {
    //     free(TF[i]);
    // }
    free(TF);
}
 
void finiteAutomationMatcher(char *sample, char *txt)
{
    int substr_len = strlen(sample);
    int N = strlen(txt);
 
    //массив указателей для FSM таблицы
    int **TF = NULL;
    TF = (int**)malloc((substr_len + 1) * sizeof(int*) );
    for (int i = 0; i < CHAR_BORD; i++)
    {
        TF[i] = (int*)malloc(CHAR_BORD * sizeof(int));
    }

    computeTF(sample, substr_len, TF);

    int i, state = 0;
    int hold_pref = 0;
    char *txt_copy = malloc(N * sizeof(int));
    int k = 0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][(int)txt[i]];
        if (state == substr_len){
            txt_copy[k] = i-substr_len+1;
            k++;
        }
    }

    k = 0;
    for (int i = 0; i < N; i++)
    {
        if (i == txt_copy[k]){
            printf("%s%sm", CSI, colors[2]);
            for (int j = 0; j < substr_len; j++)
            {
                printf("%c", txt[i]);
                i++;
            }
            i--;
            printf("%s0m", CSI);
            k++;
            continue;
        }
        
        printf("%c", txt[i]);
    }

    free(txt_copy);
    puts("");
    freeMemory(TF);
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

void listdir(char *name, uint8_t key, char *sample) 
{
    DIR *dir; 
    struct dirent *entry; 
    
    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) { 
        if (entry->d_type == DT_DIR) {
            char path[260];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            sprintf(path, "%s/%s", name, entry->d_name); 
            if (key == 1) {
                listdir(path, key, sample); 
            }
        } else {
            FILE* input;
            char fullpath[400];
            sprintf(fullpath, "%s/%s", name, entry->d_name);
            if ( (input = fopen(fullpath, "r") ) == NULL) 
                puts("Нет файла");
            char *txt = FileTextInArray(input);
            finiteAutomationMatcher(sample, txt);
            fclose(input);
            FileFree(txt);
        }
    }
    closedir(dir);
}

int main(int argc, char *argvc[])
{
    int key = 0;
    char *sample;
    char *directory;

    int flag_sample = 0;
    int flag_path = 0;
    for (int i = 1; i < argc;){
        if (strcmp(argvc[i], "-r") == 0 && key == 0){
            key = 1;
            i++;
        }

        if (flag_sample == 0){
            sample = malloc(strlen(argvc[i]) + 1);
            strcpy (sample, argvc[i]);
            flag_sample = 1;
            i++;
        }
        
        if (flag_path == 0){
            directory = malloc(strlen(argvc[i]) + 1);
            strcpy (directory, argvc[i]);
            flag_path = 1;
            break;
        }
    }

    listdir(directory, key, sample);
    
    free(sample);
    free(directory);

    return 0;
}

//     ./true -r AABA /mnt/e/C_programms/texts