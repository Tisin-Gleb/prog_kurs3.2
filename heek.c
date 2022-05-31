// C program for Finite Automata Pattern searching
// Algorithm
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NO_OF_CHARS 256
 
int getNextState(char *sample, int substr_len, int state, int x)
{
    if (state < substr_len && x == sample[state]){
        return state+1;
    }
    // ns stores the result which is next state
    int next_state, i;
 
    // ns finally contains the longest prefix
    // which is also suffix in "pat[0..state-1]c"
 
    // Start from the largest possible value
    // and stop when you find a prefix which
    // is also suffix
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

void PrintTable(int **TF, int substr) //not work
{
    for (int i = 0; i < substr + 1; i++){
        for (int j = 0; j < NO_OF_CHARS; j++){
            printf("%d ", TF[i][j]);
        }
        puts("");
    }
    puts("");
}

/* This function builds the TF table which represents4
    Finite Automata for a given pattern */
void computeTF(char *sample, int substr_len, int **TF)
{
    int state, x;
    for (state = 0; state <= substr_len; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(sample, substr_len, state, x);
}
 
/* Prints all occurrences of sample in txt */
void FiniteAutomationMatcher(char *sample, char *txt)
{
    int substr_len = strlen(sample);
    int N = strlen(txt);
 
    //int TF[M+1][NO_OF_CHARS];
    int **TF = NULL;
    TF = (int**)malloc(sizeof(int*) * (substr_len + 1) );
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        TF[i] = (int*)malloc(NO_OF_CHARS * sizeof(int));
    }

    computeTF(sample, substr_len, TF);
    PrintTable(TF, substr_len);
 
    // Process txt over FA.
    int i, state = 0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][(int)txt[i]];
        if (state == substr_len)
            printf ("\n Pattern found at index %d", i-substr_len+1);
    }
}
// Driver program to test above function
int main()
{
    char *txt = "dsadsaCAADAABAAABAA";
    char *sample = "AABA";
    FiniteAutomationMatcher(sample, txt);
    return 0;
}