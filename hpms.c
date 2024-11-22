#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100 // Maximum number of patients the system can handle
#define MAX_NAME_LEN 50  // Maximum length for names
#define MAX_BEDS 20      // Total number of beds in the hospital
#define MAX_DOCTORS 20   // Maximum number of doctors the system can handle

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

// Structure to store doctor details
typedef struct {
    char name[MAX_NAME_LEN];       // Doctor's name
    char specialty[MAX_NAME_LEN];  // Doctor's specialty
} Doctor;

// Global variables
Patient patients[MAX_PATIENTS];   // Array to store all patient records
int totalPatients = 0;            // Counter for total patients in the system
int availableBeds[MAX_BEDS];      // Array to track bed availability (1 for free, 0 for occupied)
Doctor doctors[MAX_DOCTORS];      // Array to store doctor records
int totalDoctors = 0;             // Counter for total doctors in the system

// File paths
const char *patientsFile = "patients.txt";
const char *bedsFile = "beds.txt";
const char *doctorsFile = "doctors.txt";

// Function prototypes
void loadPatients();
void savePatients();
void loadBeds();
void saveBeds();
void loadDoctors();
void initializeBeds();
int assignBed();
void addPatient();
void viewPatients();
void checkBedAvailability();
void generateBill();
void menu();

// Function to load doctor records from the file
void loadDoctors() {
    FILE *file = fopen(doctorsFile, "r");
    if (!file) {
        printf("Doctors file not found. Please ensure %s exists with valid data.\n", doctorsFile);
        return;
    }

    while (fscanf(file, " %[^\n] %[^\n]", doctors[totalDoctors].name, doctors[totalDoctors].specialty) == 2) {
        totalDoctors++;
    }

    fclose(file);
}

// Function to find a doctor based on specialty
const char *findDoctor(const char *specialty) {
    for (int i = 0; i < totalDoctors; i++) {
        if (strcmp(doctors[i].specialty, specialty) == 0) {
            return doctors[i].name;
        }
    }
    return "Dr. General"; // Default doctor if no match found
}

// Function to load patient records from the file
void loadPatients() {
    FILE *file = fopen(patientsFile, "r");
    if (!file) return; // If the file doesn't exist, skip loading

    while (fscanf(file, " %[^\n] %d %s %[^\n] %[^\n] %d %d %f %f %f",
                  patients[totalPatients].name, &patients[totalPatients].age,
                  patients[totalPatients].gender, patients[totalPatients].illness,
                  patients[totalPatients].assignedDoctor, &patients[totalPatients].bedNumber,
                  &patients[totalPatients].daysOfStay, &patients[totalPatients].serviceCharges,
                  &patients[totalPatients].doctorFee, &patients[totalPatients].totalBill) == 10) {
        totalPatients++;
    }

    fclose(file);
}

// Function to save patient records to the file
void savePatients() {
    FILE *file = fopen(patientsFile, "w");
    if (!file) {
        printf("Error saving patient data.\n");
        return;
    }

    for (int i = 0; i < totalPatients; i++) {
        Patient p = patients[i];
        fprintf(file, "%s\n%d\n%s\n%s\n%s\n%d\n%d\n%.2f\n%.2f\n%.2f\n",
                p.name, p.age, p.gender, p.illness, p.assignedDoctor, p.bedNumber,
                p.daysOfStay, p.serviceCharges, p.doctorFee, p.totalBill);
    }

    fclose(file);
}

// Function to load bed availability data from the file
void loadBeds() {
    FILE *file = fopen(bedsFile, "r");
    if (!file) return; // If the file doesn't exist, skip loading

    for (int i = 0; i < MAX_BEDS; i++) {
        if (fscanf(file, "%d", &availableBeds[i]) != 1) break;
    }

    fclose(file);
}

// Function to save bed availability data to the file
void saveBeds() {
    FILE *file = fopen(bedsFile, "w");
    if (!file) {
        printf("Error saving bed data.\n");
        return;
    }

    for (int i = 0; i < MAX_BEDS; i++) {
        fprintf(file, "%d\n", availableBeds[i]);
    }

    fclose(file);
}

// Function to initialize bed availability
void initializeBeds() {
    for (int i = 0; i < MAX_BEDS; i++) {
        availableBeds[i] = 1; // All beds are initially available
    }
    saveBeds();
}

// Function to assign a bed to a patient
int assignBed() {
    for (int i = 0; i < MAX_BEDS; i++) {
        if (availableBeds[i]) {  // Check if bed is available
            availableBeds[i] = 0; // Mark bed as occupied
            saveBeds();          // Save updated bed data
            return i + 1;        // Return bed number (1-based index)
        }
    }
    return -1; // No beds available
}

// Function to add a new patient
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

    // Assign a doctor based on the patient's illness
    const char *doctor = findDoctor(p.illness);
    strcpy(p.assignedDoctor, doctor);

    p.bedNumber = assignBed();
    if (p.bedNumber == -1) {
        printf("No beds available! Unable to admit patient.\n");
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

    savePatients(); // Save updated patient data
    printf("Patient added successfully! Assigned Bed: %d\n", p.bedNumber);
}

// Main function
int main() {
    loadDoctors();   // Load doctor data
    loadPatients();  // Load patient data
    loadBeds();      // Load bed data
    if (totalPatients == 0) initializeBeds(); // Initialize beds if no data is present
    menu();          // Display the menu and handle operations
    savePatients();  // Save patient data on exit
    saveBeds();      // Save bed data on exit
    return 0;
}
