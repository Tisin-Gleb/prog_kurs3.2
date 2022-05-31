// C program for Finite Automata Pattern searching
// Algorithm
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"FSM.h"
#define CHAR_BORD 256

//функция перехода
int getNextState(char *sample, int *substr_len, int state, int x)
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

void PrintTable(int **TF, int substr)
{
    for (int i = 0; i < substr + 1; i++){
        for (int j = 0; j < CHAR_BORD; j++){
            printf("%d ", TF[i][j]);
        }
        puts("");
    }
    puts("");
}

//строит таблицу переходов
void ComputeTF(char *sample, int substr_len, int **TF)
{
    int state, x;
    for (state = 0; state <= substr_len; ++state){
        for (x = 0; x < CHAR_BORD; ++x){
            TF[state][x] = getNextState(sample, &substr_len, state, x);
        }
    }
    PrintTable(TF, substr_len);
}

void FreeMemory(int **TF)
{
    for (int i = 0; i < CHAR_BORD; i++)
    {
        free(TF[i]);
    }
    free(TF);
}
 
void FiniteAutomationMatcher(char *sample, char *txt)
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

    ComputeTF(sample, substr_len, TF);

    int i, state = 0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][(int)txt[i]];
        if (state == substr_len)
            printf ("\n Pattern found at index %d", i-substr_len+1);
    }

    FreeMemory(TF);
}


int main(int argc, char *argvc[])
{
    char *txt = "dsadsaCAADAABAAABAA";
    char *sample = "AABA";
    FiniteAutomationMatcher(sample, txt);
    return 0;
}