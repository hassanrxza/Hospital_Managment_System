#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_NAME_LEN 50
#define MAX_BEDS 20

typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    char gender[10];
    char illness[MAX_NAME_LEN];
    char assignedDoctor[MAX_NAME_LEN];
    int bedNumber;
    int daysOfStay;
    float serviceCharges;
    float doctorFee;
    float totalBill;
} Patient;

Patient patients[MAX_PATIENTS];
int totalPatients = 0;
int availableBeds[MAX_BEDS];

void initializeBeds() {
    for (int i = 0; i < MAX_BEDS; i++) {
        availableBeds[i] = 1; // 1 indicates the bed is available
    }
}

int assignBed() {
    for (int i = 0; i < MAX_BEDS; i++) {
        if (availableBeds[i]) {
            availableBeds[i] = 0; // Mark bed as occupied
            return i + 1;
        }
    }
    return -1; // No beds available
}

void addPatient() {
    if (totalPatients >= MAX_PATIENTS) {
        printf("Maximum patient limit reached!\n");
        return;
    }
    Patient p;
    printf("Enter patient name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);
    printf("Enter gender: ");
    scanf("%s", p.gender);
    printf("Enter illness: ");
    scanf(" %[^\n]", p.illness);

    // Assign a doctor based on illness (simplified logic)
    if (strcmp(p.illness, "Cardiac") == 0)
        strcpy(p.assignedDoctor, "Dr. Heart");
    else if (strcmp(p.illness, "Ortho") == 0)
        strcpy(p.assignedDoctor, "Dr. Bones");
    else
        strcpy(p.assignedDoctor, "Dr. General");

    p.bedNumber = assignBed();
    if (p.bedNumber == -1) {
        printf("No beds available!\n");
        return;
    }

    printf("Enter days of stay: ");
    scanf("%d", &p.daysOfStay);
    printf("Enter service charges: ");
    scanf("%f", &p.serviceCharges);
    printf("Enter doctor fee: ");
    scanf("%f", &p.doctorFee);

    // Calculate total bill
    p.totalBill = (p.daysOfStay * 500) + p.serviceCharges + p.doctorFee;

    // Add patient to the list
    patients[totalPatients++] = p;

    printf("Patient added successfully! Assigned Bed: %d\n", p.bedNumber);
}

void viewPatients() {
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

void checkBedAvailability() {
    int count = 0;
    for (int i = 0; i < MAX_BEDS; i++) {
        if (availableBeds[i]) count++;
    }
    printf("Available Beds: %d\n", count);
}

void generateBill() {
    char name[MAX_NAME_LEN];
    printf("Enter patient name: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < totalPatients; i++) {
        if (strcmp(patients[i].name, name) == 0) {
            printf("Total Bill for %s: %.2f\n", patients[i].name, patients[i].totalBill);
            return;
        }
    }
    printf("Patient not found.\n");
}

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

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: checkBedAvailability(); break;
            case 4: generateBill(); break;
            case 5: printf("Exiting\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

int main() {
    initializeBeds();
    menu();
    return 0;
}
