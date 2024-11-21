#include <stdlib.h>

#define MAX_PATIENTS 100 // Maximum number of patients the system can handle
#define MAX_NAME_LEN 50  // Maximum length for names
#define MAX_BEDS 20      // Total number of beds in the hospital


// Structure to store patient details
typedef struct {
    char name[MAX_NAME_LEN];       // Patient's name
    int age;                       // Patient's age
    char gender[10];               // Patient's gender
    char illness[MAX_NAME_LEN];    // Patient's illness
    char assignedDoctor[MAX_NAME_LEN]; // Doctor assigned to the patient
    int bedNumber;                 // Bed number assigned to the patient
    int daysOfStay;                // Number of days the patient stays
    float serviceCharges;          // Service charges incurred
    float doctorFee;               // Doctor's consultation fee
    float totalBill;               // Total bill calculated for the patient
} Patient;

Patient *createPatient(Patient *);

void initializeBeds();
int assignBed();
void addPatient();
void viewPatients();
void checkBedAvailability();
void menu();
