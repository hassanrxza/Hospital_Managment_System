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
int authenticate(char *username, char *password, char *role) {
    // Predefined credentials
    const char *adminUsername = "hospital";
    const char *adminPassword = "123456";

    const char *userUsername = "user";
    const char *userPassword = "user123";

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
        strcpy(role, "admin");
        return 1;
    } else if (strcmp(username, userUsername) == 0 && strcmp(password, userPassword) == 0) {
        strcpy(role, "user");
        return 1;
    }
    return 0;
}