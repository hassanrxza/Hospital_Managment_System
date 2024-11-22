#include <stdio.h>
#include <string.h>
#include "patient.h"

Patient *createPatient(Patient *array) {

  Patient *p = (Patient *)(malloc(sizeof(Patient)));

  return array;
}

// Global variables
Patient patients[MAX_PATIENTS];   // Array to store all patient records
int totalPatients = 0;            // Counter for total patients in the system
int availableBeds[MAX_BEDS];      // Array to track bed availability (1 for free, 0 for occupied)

// Function to initialize bed availability
void initializeBeds() {
    for (int i = 0; i < MAX_BEDS; i++) {
        availableBeds[i] = 1; // All beds are initially available
    }
}

// Function to assign a bed to a patient
int assignBed() {
    for (int i = 0; i < MAX_BEDS; i++) {
        if (availableBeds[i]) {  // Check if bed is available
            availableBeds[i] = 0; // Mark bed as occupied
            return i + 1;        // Return bed number (1-based index)
        }
    }
    return -1; // No beds available
}

// Function to add a new patient
void addPatient() {
    // Check if the maximum limit of patients has been reached
    if (totalPatients >= MAX_PATIENTS) {
        printf("Maximum patient limit reached!\n");
        return;
    }

    // Collect patient details
    Patient p;
    printf("Enter patient name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);
    printf("Enter gender: ");
    scanf("%s", p.gender);
    printf("Enter illness: ");
    scanf(" %[^\n]", p.illness);

    // Assign a doctor based on the patient's illness (simple logic for now)
    if (strcmp(p.illness, "Cardiac") == 0)
        strcpy(p.assignedDoctor, "Dr. Heart");
    else if (strcmp(p.illness, "Ortho") == 0)
        strcpy(p.assignedDoctor, "Dr. Bones");
    else
        strcpy(p.assignedDoctor, "Dr. General");

    // Attempt to assign a bed to the patient
    p.bedNumber = assignBed();
    if (p.bedNumber == -1) {
        printf("No beds available! Unable to admit patient.\n");
        return;
    }

    // Collect billing details
    printf("Enter days of stay: ");
    scanf("%d", &p.daysOfStay);
    printf("Enter service charges: ");
    scanf("%f", &p.serviceCharges);
    printf("Enter doctor fee: ");
    scanf("%f", &p.doctorFee);

    // Calculate the total bill for the patient
    p.totalBill = (p.daysOfStay * 500) + p.serviceCharges + p.doctorFee;

    // Add the patient to the global list
    patients[totalPatients++] = p;

    printf("Patient added successfully! Assigned Bed: %d\n", p.bedNumber);
}

// Function to display all patient records
void viewPatients() {
    // Check if there are any patients in the system
    if (totalPatients == 0) {
        printf("No patients to display.\n");
        return;
    }

    printf("\n--- Patient List ---\n");
    for (int i = 0; i < totalPatients; i++) {
        Patient p = patients[i];
        printf("Name: %s, Age: %d, Gender: %s, Illness: %s, Assigned Doctor: %s, Bed: %d, Total Bill: %.2f\n",
               p.name, p.age, p.gender, p.illness, p.assignedDoctor, p.bedNumber, p.totalBill);
    }
}

// Function to check the number of available beds
void checkBedAvailability() {
    int count = 0;
    for (int i = 0; i < MAX_BEDS; i++) {
        if (availableBeds[i]) count++;
    }
    printf("Available Beds: %d\n", count);
}

// Function to generate and display a patient's bill
void generateBill() {
    char name[MAX_NAME_LEN];
    printf("Enter patient name: ");
    scanf(" %[^\n]", name);

    // Search for the patient by name
    for (int i = 0; i < totalPatients; i++) {
        if (strcmp(patients[i].name, name) == 0) {
            printf("Total Bill for %s: %.2f\n", patients[i].name, patients[i].totalBill);
            return;
        }
    }
    printf("Patient not found.\n"); // If no patient matches the entered name
}
