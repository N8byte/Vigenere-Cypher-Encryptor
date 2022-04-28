/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Nathan Waskiewicz
| Language: c, c++, Java
|
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
|
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2021
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
  int i, j;
  char *keyfile, *plainfile, currentChar;
  char plaintext[513], keytext[513], cyphertext[513];

  keyfile = argv[1];
  plainfile = argv[2];
  FILE *kp = fopen(keyfile, "r");
  FILE *pp = fopen(plainfile, "r");

  // store key into variable: keytext
  if (kp == 0)
    printf("Could not open key file\n");
  else
  {
    for (i = 0; i < 512; i++)
    {
      currentChar = fgetc(kp);
      if (currentChar == -1)
      {
        keytext[i] = '\0';
        i = 512;
      }
      else if (!isalpha(currentChar))
        i --;
      else
        keytext[i] = tolower(currentChar);
    }
    printf("\n\nVigenere Key:\n\n");
    for (i = 0; i < 512; i++)
    {
      if (keytext[i] == '\0')
        break;
      printf("%c", keytext[i]);
      if ((i + 1) % 80 == 0)
        printf("\n");
    }
  }
  fclose(kp);

  // store plaintext into variable: plaintext
  if (pp == 0)
    printf("Could not open plaintext file\n");
  else
  {
    for (i = 0; i < 512; i++)
    {
      currentChar = fgetc(pp);
      if (currentChar == -1)
        plaintext[i] = 'x';
      else if (!isalpha(currentChar))
        i --;
      else
        plaintext[i] = tolower(currentChar);
    }
    plaintext[512] = '\0';
    printf("\n\n\nPlaintext:\n\n");
    for (i = 0; i < 512; i++)
    {
      printf("%c", plaintext[i]);
      if ((i + 1) % 80 == 0)
        printf("\n");
    }
  }
  fclose(pp);

  // perform vigenere encryption and store in cyphertext
  j = 0;
  for (i = 0; i < 512; i++)
  {
    if (keytext[j] == '\0')
      j = 0;
    cyphertext[i] = plaintext[i] + keytext[j] - 97;
    if (plaintext[i] + keytext[j] - 97 > 122)
      cyphertext[i] -= 26;
    j ++;
  }
  cyphertext[512] = '\0';
  printf("\n\n\nCiphertext:\n\n");
  for (i = 0; i < 512; i++)
  {
    printf("%c", cyphertext[i]);
    if ((i + 1) % 80 == 0)
      printf("\n");
  }
  printf("\n");

  return 0;
}

/*=============================================================================
| I Nathan Waskiewicz (na231839) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
