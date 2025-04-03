#include "data.h"

int main() {
    int mode;
    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("Select System Mode:\n");
        printf("1 - Admin Mode\n");
        printf("2 - User Mode\n");
        printf("3 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mode);
        getchar();  // clear the newline

        switch (mode) {
            case 1: {
                int attempts = 0;
                char password[20];
                while (attempts < 3) {
                    printf("Enter admin password: ");
                    scanf("%s", password);
                    getchar();
                    if (strcmp(password, "1234") == 0) {
                        printf("Access granted.\n");
                        break;
                    } else {
                        attempts++;
                        printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
                    }
                }
                if (attempts == 3) {
                    printf("Too many incorrect attempts. Returning to main menu.\n");
                    break;  // Return to main menu instead of exiting
                }
                
                int adminChoice;
                do {
                    printf("\n--- Admin Menu ---\n");
                    printf("1. Add new patient record\n");
                    printf("2. Edit patient record\n");
                    printf("3. Manage Reservation (Add or Cancel)\n");
                    printf("4. Return to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &adminChoice);
                    getchar();
                    switch (adminChoice) {
                        case 1: {
                            char name[30], gender[30];
                            u8 age;
                            u16 id;
                            printf("Enter patient's name: ");
                            gets(name);
                            printf("Enter patient's gender: ");
                            gets(gender);
                            printf("Enter patient's age: ");
                            scanf("%hhu", &age);
                            printf("Enter patient's ID: ");
                            scanf("%hu", &id);
                            getchar();
                            AddPatient(name, gender, age, id);
                            break;
                        }
                        case 2: {
                            u16 id;
                            printf("Enter patient ID to edit: ");
                            scanf("%hu", &id);
                            getchar();
                            EditPatient(id);
                            break;
                        }
                        case 3: {
                            u16 id;
                            printf("Enter patient ID for reservation management: ");
                            scanf("%hu", &id);
                            getchar();
                            ManageReservation(id);
                            break;
                        }
                        case 4:
                            printf("Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            break;
                    }
                } while (adminChoice != 4);
                break;
            }
            case 2: {
                int userChoice;
                printf("\n--- User Mode ---\n");
                printf("1. View a Patient Record\n");
                printf("2. View Today's Reservations\n");
                printf("Enter your choice: ");
                scanf("%d", &userChoice);
                getchar();
                switch (userChoice) {
                    case 1: {
                        u16 id;
                        printf("Enter patient ID: ");
                        scanf("%hu", &id);
                        getchar();
                        DisplaySpePatient(id);
                        break;
                    }
                    case 2:
                        ViewTodaysReserve();
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            }
            case 3:
                printf("Exiting system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid mode selection. Please try again.\n");
                break;
        }
    }
    return 0;
}