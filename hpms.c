#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATIENTS 100
#define MAX_NAME_LEN 50
#define MAX_BEDS 20
#define MAX_DOCTORS 20

// Structure to store patient details
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

// Structure to store doctor details
typedef struct {
    char name[MAX_NAME_LEN];
    char specialization[MAX_NAME_LEN];
} Doctor;

// Global Variables
Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
int totalPatients = 0;
int totalDoctors = 0;
int availableBeds[MAX_BEDS];

// Function Prototypes
void initializeBeds();
void loadPatientData();
void savePatientData();
void loadBedAvailability();
void saveBedAvailability();
void loadDoctors();
const char* assignDoctor(char *illness);
int assignBed();
void addPatient();
void viewPatients();
void viewAllBeds();
void generateBill();
void removePatient();
void adminMenu();
void userMenu();
int authenticate(const char *username, const char *password, const char *role);
void displayBanner();

// Initialize beds (1 = available, 0 = occupied)
void initializeBeds() {
    for (int i = 0; i < MAX_BEDS; i++) {
        availableBeds[i] = 1;
    }
}

// Load patient data from text file
void loadPatientData() {
    FILE *file = fopen("patients.txt", "r");
    if (!file) {
        totalPatients = 0; // No file means no patients yet
        return;
    }

    totalPatients = 0;
    while (fscanf(file, "%49[^,], %d, %9[^,], %49[^,], %49[^,], %d, %d, %f, %f, %f\n",
                  patients[totalPatients].name,
                  &patients[totalPatients].age,
                  patients[totalPatients].gender,
                  patients[totalPatients].illness,
                  patients[totalPatients].assignedDoctor,
                  &patients[totalPatients].bedNumber,
                  &patients[totalPatients].daysOfStay,
                  &patients[totalPatients].serviceCharges,
                  &patients[totalPatients].doctorFee,
                  &patients[totalPatients].totalBill) == 10) {
        totalPatients++;
        if (totalPatients >= MAX_PATIENTS) break;
    }
    fclose(file);
}

// Save patient data to text file
void savePatientData() {
    FILE *file = fopen("patients.txt", "w");
    if (!file) {
        printf("Error: Unable to save patient data.\n");
        return;
    }

    for (int i = 0; i < totalPatients; i++) {
        fprintf(file, "%s, %d, %s, %s, %s, %d, %d, %.2f, %.2f, %.2f\n",
                patients[i].name,
                patients[i].age,
                patients[i].gender,
                patients[i].illness,
                patients[i].assignedDoctor,
                patients[i].bedNumber,
                patients[i].daysOfStay,
                patients[i].serviceCharges,
                patients[i].doctorFee,
                patients[i].totalBill);
    }
    fclose(file);
}

// Load bed availability from text file
void loadBedAvailability() {
    FILE *file = fopen("beds.txt", "r");
    if (!file) {
        initializeBeds(); // Initialize if the file doesn't exist
        return;
    }

    for (int i = 0; i < MAX_BEDS; i++) {
        if (fscanf(file, "%d", &availableBeds[i]) != 1) {
            availableBeds[i] = 1; // Default to available if there's an issue
        }
    }
    fclose(file);
}

// Save bed availability to text file
void saveBedAvailability() {
    FILE *file = fopen("beds.txt", "w");
    if (!file) {
        printf("Error: Unable to save bed availability.\n");
        return;
    }

    for (int i = 0; i < MAX_BEDS; i++) {
        fprintf(file, "%d\n", availableBeds[i]);
    }
    fclose(file);
}

// Load doctor data from text file
void loadDoctors() {
    FILE *file = fopen("doctors.txt", "r");
    if (!file) {
        printf("Error: doctors.txt file not found!\n");
        exit(1);
    }
    totalDoctors = 0;
    while (fscanf(file, " %49[^,], %49[^\n]", doctors[totalDoctors].name, doctors[totalDoctors].specialization) == 2) {
        totalDoctors++;
        if (totalDoctors >= MAX_DOCTORS) break;
    }
    fclose(file);
}

// Assign a doctor based on illness
const char* assignDoctor(char *illness) {
    const char *specialization = NULL;

    // Illness-to-specialization mapping
    if (strstr(illness, "heart") || strstr(illness, "Cardiac")) {
        specialization = "Cardiology";
    } else if (strstr(illness, "brain") || strstr(illness, "neurological")) {
        specialization = "Neurology";
    } else if (strstr(illness, "bone") || strstr(illness, "fracture")) {
        specialization = "Orthopedics";
    } else if (strstr(illness, "child") || strstr(illness, "pediatric")) {
        specialization = "Pediatrics";
    } else if (strstr(illness, "cancer") || strstr(illness, "tumor")) {
        specialization = "Oncology";
    } else if (strstr(illness, "skin") || strstr(illness, "dermatitis")) {
        specialization = "Dermatology";
    } else if (strstr(illness, "stomach") || strstr(illness, "digestive")) {
        specialization = "Gastroenterology";
    } else if (strstr(illness, "mental") || strstr(illness, "psychiatric")) {
        specialization = "Psychiatry";
    } else if (strstr(illness, "kidney") || strstr(illness, "urinary")) {
        specialization = "Urology";
    } else {
        specialization = "General Medicine";
    }

    // Find a doctor with the matching specialization
    for (int i = 0; i < totalDoctors; i++) {
        if (strcmp(doctors[i].specialization, specialization) == 0) {
            return doctors[i].name; // Return the doctor's name
        }
    }

    return "General Practitioner"; // Default doctor if no match found
}

// Assign a bed to a patient
int assignBed() {
    for (int i = 0; i < MAX_BEDS; i++) {
        if (availableBeds[i]) {
            availableBeds[i] = 0; // Mark bed as occupied
            saveBedAvailability(); // Save updated bed availability
            return i + 1;
        }
    }
    return -1; // No beds available
}

// Add a new patient
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

    strcpy(p.assignedDoctor, assignDoctor(p.illness));
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

    p.totalBill = (p.daysOfStay * 500) + p.serviceCharges + p.doctorFee;

    patients[totalPatients++] = p;
    savePatientData();
    printf("Patient added successfully! Assigned Bed: %d, Assigned Doctor: %s\n", p.bedNumber, p.assignedDoctor);
}

// View all patients
void viewPatients() {
    if (totalPatients == 0) {
        printf("No patients to display.\n");
        return;
    }

    printf("\n--- Patient List ---\n");
    for (int i = 0; i < totalPatients; i++) {
        Patient p = patients[i];
        printf("Name: %s, Age: %d, Gender: %s, Illness: %s, Assigned Doctor: %s, Bed: %d, Total Bill: %.2f\n\n",
               p.name, p.age, p.gender, p.illness, p.assignedDoctor, p.bedNumber, p.totalBill);
    }
}

// Check real-time bed availability
void viewAllBeds() {
    printf("\n--- Bed Availability ---\n");
    for (int i = 0; i < MAX_BEDS; i++) {
        printf("Bed %d: %s\n", i + 1, availableBeds[i] ? "Available" : "Occupied");
    }
}

// Generate bill for a patient
void generateBill() {
    if (totalPatients == 0) {
        printf("No patients to generate a bill for.\n");
        return;
    }

    printf("Enter patient name: ");
    char name[MAX_NAME_LEN];
    scanf(" %[^\n]", name);

    for (int i = 0; i < totalPatients; i++) {
        if (strcmp(patients[i].name, name) == 0) {
            Patient p = patients[i];
            printf("\n--- Bill ---\n");
            printf("Name: %s, Days of Stay: %d, Service Charges: %.2f, Doctor Fee: %.2f, Total Bill: %.2f\n",
                   p.name, p.daysOfStay, p.serviceCharges, p.doctorFee, p.totalBill);
            return;
        }
    }

    printf("Patient not found!\n");
}

// Remove a discharged patient
void removePatient() {
    if (totalPatients == 0) {
        printf("No patients to remove.\n");
        return;
    }

    printf("Enter patient name to remove: ");
    char name[MAX_NAME_LEN];
    scanf(" %[^\n]", name);

    int found = 0;
    for (int i = 0; i < totalPatients; i++) {
        if (strcmp(patients[i].name, name) == 0) {
            availableBeds[patients[i].bedNumber - 1] = 1; // Mark bed as available
            saveBedAvailability();
            for (int j = i; j < totalPatients - 1; j++) {
                patients[j] = patients[j + 1];
            }
            totalPatients--;
            savePatientData();
            printf("Patient removed successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient not found!\n");
    }
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. View Bed Availability\n");
        printf("4. Generate Bill\n");
        printf("5. Remove Patient\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                viewAllBeds();
                break;
            case 4:
                generateBill();
                break;
            case 5:
                removePatient();
                break;
            case 6:
                printf("Exiting admin menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}

// User menu
void userMenu() {
    int choice;
    do {
        printf("\n--- User Menu ---\n");
        printf("1. View Bed Availability\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllBeds();
                break;
            case 2:
                printf("Exiting user menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);
}

// Authentication for admin and user roles
int authenticate(const char *username, const char *password, const char *role) {
    if (strcmp(role, "admin") == 0) {
        return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
    } else if (strcmp(role, "user") == 0) {
        return strcmp(username, "user") == 0 && strcmp(password, "user123") == 0;
    }
    return 0;
}

// Display welcome banner
void displayBanner() {
    printf("==================================\n");
    printf("     Hospital Management System   \n");
    printf("==================================\n");
}

int main() {
    loadPatientData();
    loadBedAvailability();
    loadDoctors();

    displayBanner();

    char username[50], password[50];
    printf("Enter username (user/admin): ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password, "admin")) {
        printf("Admin authenticated!\n");
        adminMenu();
    } else if (authenticate(username, password, "user")) {
        printf("User authenticated!\n");
        userMenu();
    } else {
        printf("Authentication failed! Exiting...\n");
    }

    return 0;
}
