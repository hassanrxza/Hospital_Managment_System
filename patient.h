#include <stdlib.h>

typedef struct {
  char *name;
  int age;
  char gender;
  char *illness;
  char *doctor_assigned;

} Patient;

Patient *createPatient(Patient *);
