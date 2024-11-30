// Function for admin menu
void adminMenu() {
    int choice;

    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Logout\n");
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
                searchPatient();
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Function for user menu
void userMenu() {
    int choice;

    while (1) {
        printf("\n--- User Menu ---\n");
        printf("1. View Patients\n");
        printf("2. Search Patient\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewPatients();
                break;
            case 2:
                searchPatient();
                break;
            case 3:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}