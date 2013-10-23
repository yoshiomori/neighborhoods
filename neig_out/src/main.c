/*
 * File: hw.c
 * ----------
 * This program reads a matrix in a file
 * and store it in a suitbable way.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Constants
 * ---------
 * ...
 */

/* Private function prototypes */

static void ReadMatrix(FILE *file, int **matrix);
static int CharToDigit(char ch);
static int GetNrows(FILE *infile);
static int **GetBlock(int n);

/* Main program */

int main(int argc, char **argv)
{
    int i, j, nrows;
    int **matrix;
    FILE *infile;

    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        printf("Can't open the file\n."); // ver TASC, p. 457, pdf.
        exit(1);
    }
    nrows = GetNrows(infile);
    fclose(infile);
    matrix = GetBlock(nrows); 
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        printf("Can't open the file\n."); // ver TASC, p. 457, pdf.
        exit(1);
    } //ver necessidade de fechar e abrir de novo
    ReadMatrix(infile, matrix);
    for (i = 0; i < nrows; i++)
        for (j = i + 1; j < nrows; j++)
            printf("%d", matrix[i][j]);
    fclose(infile);
}

/*
 * Function: ReadMatrix
 * Usage: ReadMatrix(file, matrix);
 * ----------------------------------------
 * This function reads a square matrix from a file
 * and store it a 2-dimensional array of ints 
 * representing the matrix. (Review!)
 */
 
static void ReadMatrix(FILE *file, int **matrix)
{
    int i, j;
    char ch; //ver mudança para int

    i = 0;
    j = 0;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\n') {
            i++;
            j = 0;
        }
        if (ch != ' ' && ch != '\n') { //melhorar pois repete condição acima
            matrix[i][j] = CharToDigit(ch);
            j++;
        }
    }
}

/*
 * Function: CharToDigit
 * Usage: n = CharToDigit(ch);
 * ---------------------------
 * This function coverts a char to corresponding
 * digit. 
 */

static int CharToDigit(char ch)
{
    return (ch - '0');
}

/*
 * Function: GetNrows
 * Usage: nrows = GetNrows(file);
 * ------------------------------
 * ...
 */

static int GetNrows(FILE *infile)
{
    int n;
    char ch; //ver TASC para declaração como int 

    n = 0;
    while ((ch = getc(infile)) != EOF) {
        if (ch == '\n') n++;
    }
    return (n);
}

/*
 * Function: GetBlock
 * Usage: matrix = GetBlock(nrows);
 * --------------------------------
 * ...
 */

static int **GetBlock(int n)
{
    int i;
    int **arr;

    arr = malloc(n * sizeof(int*));
    if (arr != NULL) {
        for (i = 0; i < n; i++) {
            arr[i] = malloc(n * sizeof(int));
            if (arr[i] == NULL) { 
                printf("No memory available");
                exit(1);
            }
        }
        return (arr);
    printf("No memory available");
    exit(1);
    }
    return 0;
}
