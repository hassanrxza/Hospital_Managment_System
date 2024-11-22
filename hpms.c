#include <stdio.h>
#include <stddef.h>
#include "patient.h"

#define MAX_PATIENTS 100 // Maximum number of patients the system can handle
#define MAX_NAME_LEN 50  // Maximum length for names
#define MAX_BEDS 20      // Total number of beds in the hospital


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

// Function to display the menu and handle user choices
void menu() {
    int choice;
    do {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Check Bed Availability\n");
        printf("4. Generate Bill\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Call the corresponding function based on user's choice
        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: checkBedAvailability(); break;
            case 4: generateBill(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5); // Exit when the user chooses 5
}

// Main function
int main() {
    initializeBeds(); // Initialize bed availability
    menu();           // Display the menu and handle operations
 
  return 0;
}

