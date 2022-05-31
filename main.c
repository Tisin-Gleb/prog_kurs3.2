#define CHAR_BORD 256
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"FSM.h"
#include <sys/types.h>
#include <dirent.h>
#include<stdint.h>

DIR *opendir(const char *name);
int closedir(DIR *dirp);
struct dirent *readdir(DIR *dirp);




//функция перехода
int getNextState(char *sample, int substr_len, int state, int x)
{
    //case '*':'/', '\\'
    // switch(x){
    //     case '\\':
    //         ;
    //     case '.':
    //         return state+1;
    //     case '*':
    //         int i = 0;
    //         while (1){
    //             if (sample[state+1] == x){
    //                 return state + 1;
    //             }else{
    //                 i++;
    //                 state++;
    //             }
    //         }
            

    // }
        
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
    printTable(TF, substr_len);
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
    for (i = 0; i < N; i++)
    {
        state = TF[state][(int)txt[i]];
        if (state == substr_len)
            printf ("\n Pattern found at index %d", i-substr_len+1);
    }

    freeMemory(TF);
}

void listdir(char *name, uint8_t key) //мб готово
{
    DIR *dir; //как файл
    struct dirent *entry; //Съела объект в файловой системе - файл/папка
    
    if (!(dir = opendir(name))) //пососи рекурсия
        return;

    while ((entry = readdir(dir)) != NULL) { // readdir(dir) последовательно файлы в директории считывает
        if (entry->d_type == DT_DIR) {
            char path[260];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            sprintf(path, "%s/%s", name, entry->d_name); //папка  
            if (key == 1) {
                listdir(path, key); //только папки
            }
        } else { // всё удали нахуй
        //зашёл в файл накткнулся
        //пишу что можно сделат ь с файлами
        }
    }
    closedir(dir);
}

void processMain(int argc, char *argvc[], int *key, char *sample)
{
    int flag_sample = 0;
    int flag_path = 0;
    for (int i = 0; i < argc; i++){
        if (strcmp(argvc[i], "-r" && *key == 0) == 0){
            *key = 1;
            continue;
        }

        if (flag_sample == 0){
            strcpy (sample, argvc[i]);
            flag_sample = 1;
            continue;
        }
        
        if (flag_path == 0){
            strcpy (sample, argvc[i]);
            flag_path = 1;
            break;
        }
    }
}


int main(int argc, char *argvc[])
{
    int key = 0;
    processMain(argc, argvc, &key);

    char *txt = "dsadsaCAADAABAAABAA";
    char *sample = "AABA";
    finiteAutomationMatcher(sample, txt);
    return 0;
}