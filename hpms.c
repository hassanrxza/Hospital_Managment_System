#include <stddef.h>
#include <stdio.h>

void checkData();


int main(void) {
  printf("Hello, World!");
  
  checkData();

  return 0;
}

void checkData()
{
  FILE *patPtr = fopen("patient.txt", "r");

  if (patPtr == NULL)
  {
    fprintf(stderr, "The patient data file does not exist, creating file\n");
    FILE *patPtr = fopen("patient.txt", "w");
    fprintf(patPtr, "Init Patient Data\n");
    fclose(patPtr);
  }
  

  FILE *docPtr = fopen("doctors.txt", "r");

  if (docPtr == NULL)
  {
    fprintf(stderr, "The doctors data file does not exist, creating file\n");
    FILE *docPtr = fopen("doctors.txt", "w");
    fprintf(docPtr, "Init Doctors Data\n");
    fclose(docPtr);
  }
}
