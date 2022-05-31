#include <stdio.h>
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
int main()
{
    char text1[] = "This is demonstration text\n";
    int i;

    // 1. Print out text with different colors
    for (i = 0; text1[i] != '\0'; i++)
    {
        // never use black and dark gray
        int color = i % (colors_sz - 2) + 2;
        printf("%s%sm%c%s0m", CSI, colors[color], text1[i], CSI);
    }
    printf("\n");

    // 2. highlight "demo" word with red in output text
    // this word starts at 8th position and ends at
    // 20th position
    for (i = 0; i < 8; i++)
    {
        printf("%c", text1[i]);
    }
    printf("%s%sm", CSI, colors[2]); // setup text color to red
    for (i = 8; i <= 20; i++)
    {
        printf("%c", text1[i]);
    }
    printf("%s0m", CSI); // return normal text color
    for (i = 21; text1[i] != '\0'; i++)
    {
        printf("%c", text1[i]);
    }
    printf("\n");
    // 3. highlight with RED and ITALIC in output text
    // word starts at 8th position and ends at 20th position
    for (i = 0; i < 8; i++)
    {
        printf("%c", text1[i]);
    }
    printf("%s%sm", CSI, colors[2]); // setup text color to red
    printf("%s4m", CSI);             // setup text color to bold

    for (i = 8; i <= 20; i++)
    {
        printf("%c", text1[i]);
    }
    printf("%s0m", CSI); // return normal text color
    for (i = 21; text1[i] != '\0'; i++)
    {
        printf("%c", text1[i]);
    }
    printf("\n");
    // 4. highlight "demonstration" word
    // with RED and WHITE BACKGROUND
    // this word starts at 8th position and ends
    // at 20th position
    for (i = 0; i < 8; i++)
    {
        printf("%c", text1[i]);
    }
    printf("%s%sm", CSI, colors[2]); // setup text color to red
    printf("%s47m", CSI);            // setup background color to white
    for (i = 8; i <= 20; i++)
    {
        printf("%c", text1[i]);
    }
    printf("%s0m", CSI); // return normal text color
    for (i = 21; text1[i] != '\0'; i++)
    {
        printf("%c", text1[i]);
    }
    printf("\n");
}