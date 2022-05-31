#define NO_OF_CHARS 5


int getNextState(char *sample, int substr_len, int state, int x)
{
    if (state < substr_len && x == sample[state])
        return state+1;
 
    int next_state, i;

    for (next_state = state; next_state > 0; next_state--)
    {
        if (sample[next_state-1] == x)
        {
            for (i = 0; i < next_state-1; i++)
                if (sample[i] != sample[state-next_state+1+i])
                    break;
            if (i == next_state-1)
                return next_state;
        }
    }
 
    return 0;
}
 
void computeTF(char *sample, int substr_len, int **TF)
{
    int state, x;
    for (state = 0; state <= substr_len; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(sample, substr_len, state, x);
}
 
void FiniteAutomationMatcher(char *sample, char *txt)
{
    int substr_len = strlen(sample);
    int N = strlen(txt);
 
    int **TF;
    TF = (int**)malloc(sizeof(int*) * (substr_len + 1) );
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        TF[i] = (int*)malloc(sizeof(NO_OF_CHARS) * sizeof(int));
    }

    computeTF(sample, substr_len, TF);
 
    int i, state=0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][(int)txt[i] - 'a'];
        if (state == substr_len)
            printf ("\n Pattern found at index %d", i-substr_len+1);
    }
}

// Driver program to test above function
int main()
{
    char *txt = "aabaacaadaabaaabaa";
    char *sample = "aaba";
    FiniteAutomationMatcher(sample, txt);
    return 0;
}