int getNextState(char *sample, int substr_len, int state, int x);
void PrintTable(int **TF, int substr);
void ComputeTF(char *sample, int substr_len, int **TF);
void FreeMemory(int **TF);
void FiniteAutomationMatcher(char *sample, char *txt);
char* FileTextInArray(FILE *input);
int FileLength(FILE *input);
void FileFree(char *file_text);