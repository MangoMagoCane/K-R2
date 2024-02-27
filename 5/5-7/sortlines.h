#define MAXLEN 1000 /* max length of any input line */
#define MAXLINES 5000 /* max #lines to be sorted */

int readlines(char *lineptr[], char lines[][MAXLEN], int maxlines);
void writelines(char *lineptr[], int nlines);
int getline(char *, int);
void new_qsort(char *lineptr[], int left, int right);
void swap(char *v[], int i, int j);