/*
 * COP 3515 – Fall Semester 2022
 *
 * Homework #1: Password Strength Meter
 *
 * Name: Ritvik Komaragiri
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_FILES 3

int main(void) {
  FILE *passFiles[NUM_FILES];
  passFiles[0] = fopen("Proposed passwords #1.txt", "r");
  passFiles[1] = fopen("Proposed passwords #2.txt", "r");
  passFiles[2] = fopen("Proposed passwords #3.txt", "r");

  // File open test
  for (int i = 0; i < NUM_FILES; i++) { // checks for null pointers in all files
    if (passFiles[i] == NULL) {
      printf("Couldn't open file %d\n", i + 1);
      return i + 1;
    } else {
      continue;
    }
  }

  int params[6] = {-1, -1, -1, -1, -1, -1};
  int minPasswordLength;
  int maxPasswordLength;
  bool allowPassPhrases;
  int minPassPhraseLength = 0; // optional
  bool allowOptionalTests;
  int numOptionalTests = 0; // optional
  bool isPassPhrase = false;

  bool exceedsMinLength; // required tests
  bool underMaxLength;
  bool containsRepeatChars = false;

  bool containsLower; // optional Tests
  bool containsUpper;
  bool containsInt;
  bool containsSpecialCharacter;

  for (int i = 0; i < NUM_FILES; i++) {

    printf("Processing password file #%d\n\n\n", i + 1);

    for (int j = 0; j < 6; j++) {
      fscanf(passFiles[i], "%d", &params[j]);
    }

    minPasswordLength = params[1];
    maxPasswordLength = params[0];
    printf("Maximum Password Length: %d\n", maxPasswordLength);
    printf("Minimum Password Length: %d\n", minPasswordLength);

    // SETTING PARAMETERS FOR TESTS
    if (params[2] == 0 && params[3] == 0) {
      allowPassPhrases = false;
      printf("Pass Phrases are NOT allowed\n");
      allowOptionalTests = false;
      printf("Optional Tests are NOT allowed\n\n");
    } else if (params[2] == 0 && params[3] == 1) {
      allowPassPhrases = false;
      printf("Pass Phrases are NOT allowed\n");
      allowOptionalTests = true;
      printf("Optional Tests are allowed\n");
      numOptionalTests = params[5];
      printf("Number of Optional Tests: %d", numOptionalTests);
    } else if (params[2] == 1 && params[4] == 0) {
      allowPassPhrases = true;
      minPassPhraseLength = params[3];
      printf("Pass Phrases are allowed\n");
      printf("Minimum Pass Phrase Length: %d\n", minPassPhraseLength);
      allowOptionalTests = false;
      printf("Optional Tests are NOT allowed\n");
    } else if (params[2] == 1 && params[4] == 1) {
      allowPassPhrases = true;
      allowOptionalTests = true;
      minPassPhraseLength = params[3];
      numOptionalTests = params[5];
      printf("Pass Phrases are allowed\n");
      printf("Minimum Pass Phrase Length: %d\n", minPassPhraseLength);
      printf("Optional Tests are allowed\n");
      printf("Number of Optional Tests: %d\n\n", numOptionalTests);
    }
    // SETTING PARAMETERS FOR TESTS

    char singleLine[150];

    while (fgets(singleLine, sizeof(singleLine), passFiles[i])) {

      int passedTests[7] = {-1, -1, -1, -1, -1, -1, -1};
      
      int stringLength = strlen(singleLine) - 1;

      if (!allowPassPhrases && !allowOptionalTests) {
        if (stringLength == 0) {
          continue;
        }

        printf("Potential Password(len:%d): %s\n", stringLength, singleLine);
        for (int j = 0; j < stringLength - 2; j++) {
          if (singleLine[j] == singleLine[j + 1] &&
              singleLine[j] == singleLine[j + 2]) {
            containsRepeatChars = true;
          }
        }

        for (int j = 0; j < stringLength; j++) {
          if (singleLine[j] == ' ') {
            printf("Password can't contain spaces\n\nPassword failed - it "
                   "cannot be used\n\n\n");
          }
        }

        if (stringLength > maxPasswordLength) {
          passedTests[1] = 0;
        } else {
          passedTests[1] = 1;
        }

        if (stringLength < minPasswordLength) {
          passedTests[0] = 0;
        } else {
          passedTests[0] = 1;
        }

        if (containsRepeatChars) {
          passedTests[2] = 0;
          containsRepeatChars = false;
        } else {
          passedTests[2] = 1;
        }

        for (int j = 0; j < 3; j++) {
          printf("(%d)", passedTests[j]);
          passedTests[j] = -1;
        }
        printf("\n\n\n");
      }

      if (allowPassPhrases && allowOptionalTests) {
        if (stringLength == 0) {
          continue;
        }
        printf("Potential Password(len:%d): %s\n", stringLength, singleLine);
        for (int j = 0; j < stringLength; j++) {
          if (singleLine[j] == ' ') {
            isPassPhrase = true;
          }
        }

        for (int j = 0; j < stringLength; j++) {
          if (singleLine[j] == singleLine[j + 1] &&
              singleLine[j] == singleLine[j + 2]) {
            containsRepeatChars = true;
          }
        }

        if (isPassPhrase) {

          passedTests[1] = 1;

          if (stringLength < minPasswordLength) {
            passedTests[0] = 0;
          } else {
            passedTests[0] = 1;
          }

          if (containsRepeatChars) {
            passedTests[2] = 0;
            containsRepeatChars = false;
          } else {
            passedTests[2] = 1;
          }

          for (int j = 0; j < 3; j++) {
            printf("(%d)", passedTests[j]);
            passedTests[j] = -1;
          }
          printf("\n\n\n");
          isPassPhrase = false;
        } else {

          switch (numOptionalTests) {
          case 4: // contains one special/non-alphanumeric character
            for (int j = 0; j < stringLength; j++) {
              if ((singleLine[j] > 32 && singleLine[j] < 48) ||
                  (singleLine[j] > 57 && singleLine[j] < 65) ||
                  (singleLine[j] > 90 && singleLine[j] < 97) ||
                  (singleLine[j] > 122 && singleLine[j] < 127)) {
                containsSpecialCharacter = true;
                passedTests[6] = 1;
              }
            }
          case 3: // contains atleast one number
            for (int j = 0; j < stringLength; j++) {
              if (singleLine[j] > 47 && singleLine[j] < 58) {
                containsInt = true;
                passedTests[5] = 1;
              }
            }
          case 2: // contains atleast one uppercase letter
            for (int j = 0; j < stringLength; j++) {
              if (singleLine[j] > 64 && singleLine[j] < 91) {
                containsUpper = true;
                passedTests[4] = 1;
              }
            }
          case 1: // contains atleast one lowercase letter
            for (int j = 0; j < stringLength; j++) {
              if (singleLine[j] > 96 && singleLine[j] < 123) {
                containsUpper = true;
                passedTests[3] = 1;
              }
            }
          }

          if (stringLength > maxPasswordLength) {
            passedTests[1] = 0;
          } else {
            passedTests[1] = 1;
          }

          if (stringLength < minPasswordLength) {
            passedTests[0] = 0;
          } else {
            passedTests[0] = 1;
          }

          if (containsRepeatChars) {
            passedTests[2] = 0;
            containsRepeatChars = false;
          } else {
            passedTests[2] = 1;
          }

          for (int j = 0; j < 3; j++) {
            printf("(%d)", passedTests[j]);
          }
          printf("\n\n");
          printf("Optional Tests (%d): ", numOptionalTests);
          int numPassedOptionalTests = 0;
          for (int j = 3; j < 7; j++) {
            printf("(%d)", passedTests[j]);
            if (passedTests[j] == 1) {
              numPassedOptionalTests++;
            }
            passedTests[j] = -1;
          }
          printf(" || Passed: %d", numPassedOptionalTests);
          printf("\n\n\n");
        }
      }
    }
  }

  printf("\n\n\n");

  for (int k = 0; k < NUM_FILES; k++) { // closes all files in file array
    fclose(passFiles[k]);
  }

  return 0;
}