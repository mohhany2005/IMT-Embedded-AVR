#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma pack (1)

#ifndef Std_Types_H_
typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed long int s32;
typedef unsigned long int u32;
typedef signed long long int s64;
typedef unsigned long long int u64;
typedef float f32;
#endif

typedef char string[30];

#define NUM_SLOTS 5

typedef struct {
    string time;
    bool reserved;
} TimeSlot;

TimeSlot Reserve[NUM_SLOTS] = {
    { "2pm - 2:30pm", false },
    { "2:30pm - 3pm", false },
    { "3pm - 3:30pm", false },
    { "4pm - 4:30pm", false },
    { "4:30pm - 5pm", false }
};

typedef struct patient {
    string name;
    string gender;
    u16 ID;
    u8 age;
    int slotIndex;  // -1 indicates no reservation
    struct patient *next;
} patient;

patient *HEAD = NULL, *TEMP = NULL;

u8 chooseAvailableSlot(void) {
    int input;
    bool valid = false;

    while (!valid) {
        printf("Available time slots:\n");
        for (u8 i = 0; i < NUM_SLOTS; i++) {
            if (!Reserve[i].reserved) {
                printf("%d: %s\n", i, Reserve[i].time);
            }
        }

        printf("Enter the number corresponding to your desired time slot: ");
        if (scanf("%d", &input) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (input >= 0 && input < NUM_SLOTS) {
            if (!Reserve[input].reserved) {
                valid = true;
            } else {
                printf("This slot is already reserved. Choose another.\n");
            }
        } else {
            printf("Invalid slot number. Try again.\n");
        }
    }

    while (getchar() != '\n'); // clear leftover input
    return (u8)input;
}

// Add a new patient with no reservation (slotIndex set to -1)
void AddPatient(string n, string g, u8 age, u16 id) {
    patient *NewNode = (patient*) malloc(sizeof(patient));
    if (NewNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(NewNode->name, n);
    strcpy(NewNode->gender, g);
    NewNode->age = age;
    NewNode->ID = id;
    NewNode->slotIndex = -1;  // no reservation initially
    NewNode->next = NULL;

    // Append the new patient to the end of the linked list
    if (HEAD == NULL) {
        HEAD = NewNode;
    } else {
        patient *temp = HEAD;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = NewNode;
    }
}

// Cancel a patient's reservation
void CancelReservation(u16 id) {
    patient *temp = HEAD;
    bool found = false;
    while (temp != NULL) {
        if (temp->ID == id) {
            found = true;
            if (temp->slotIndex != -1) {
                Reserve[temp->slotIndex].reserved = false;
                printf("Reservation for patient ID %d canceled. Slot %d (%s) is now available.\n", 
                       id, temp->slotIndex, Reserve[temp->slotIndex].time);
                temp->slotIndex = -1;
            } else {
                printf("Patient ID %d does not have a reservation to cancel.\n", id);
            }
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Patient with ID %d not found.\n", id);
    }
}

// Edit patient details
void EditPatient(u16 id) {
    bool found = false;
    if (HEAD != NULL) {
        TEMP = HEAD;
        while (TEMP != NULL) {
            if (TEMP->ID == id) {
                found = true;
                printf("Patient found:\nID: %d\nName: %s\nGender: %s\nAge: %d\n", 
                       TEMP->ID, TEMP->name, TEMP->gender, TEMP->age);
                // (Editing functionality omitted for brevity; use your existing code)
                break;
            }
            TEMP = TEMP->next;
        }
        if (!found) {
            printf("Patient with ID %d is not found.\n", id);
        }
    } else {
        printf("No patients in the clinic.\n");
    }
}

// Display all patients
void DisplayPatient(void) {
    if (HEAD != NULL) {
        TEMP = HEAD;
        while (TEMP != NULL) {
            printf("ID: %d\nName: %s\nGender: %s\nAge: %d\n", 
                   TEMP->ID, TEMP->name, TEMP->gender, TEMP->age);
            if (TEMP->slotIndex != -1) {
                printf("Reservation Slot: %s\n", Reserve[TEMP->slotIndex].time);
            } else {
                printf("No reservation.\n");
            }
            TEMP = TEMP->next;
        }
    } else {
        printf("No patients in the clinic.\n");
    }
}

// Display a specific patient by ID
void DisplaySpePatient(u16 id) {
    if (HEAD != NULL) {
        TEMP = HEAD;
        while (TEMP != NULL) {
            if (TEMP->ID == id) {
                printf("ID: %d\nName: %s\nGender: %s\nAge: %d\n", 
                       TEMP->ID, TEMP->name, TEMP->gender, TEMP->age);
                if (TEMP->slotIndex != -1) {
                    printf("Reservation Slot: %s\n", Reserve[TEMP->slotIndex].time);
                } else {
                    printf("No reservation.\n");
                }
                break;
            }
            TEMP = TEMP->next;
        }
    } else {
        printf("Patient with ID %d was not found.\n", id);
    }
}

// Display today's reservations
void ViewTodaysReserve() {
    if (HEAD != NULL) {
        TEMP = HEAD;
        while (TEMP != NULL) {
            if (TEMP->slotIndex != -1 && Reserve[TEMP->slotIndex].reserved) {
                printf("ID: %d  Reservation Slot: %s\n", TEMP->ID, Reserve[TEMP->slotIndex].time);
            }
            TEMP = TEMP->next;
        }
    } else {
        printf("No patients in the clinic.\n");
    }
}

void ManageReservation(u16 id) {
    patient *temp = HEAD;
    bool found = false;

    while (temp != NULL) {
        if (temp->ID == id) {
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }

    int choice;
    printf("Reservation Management for patient ID %d:\n", id);
    printf("1. Add Reservation\n");
    printf("2. Cancel Reservation\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); // flush newline

    if (choice == 1) {
        if (temp->slotIndex != -1) {
            printf("Patient already has a reservation in slot %d (%s).\n",
                   temp->slotIndex, Reserve[temp->slotIndex].time);
        } else {
            int slot = chooseAvailableSlot();
            temp->slotIndex = slot;
            Reserve[slot].reserved = true;
            printf("Reserved slot %d: %s for patient ID: %d\n",
                   slot, Reserve[slot].time, id);
        }
    } else if (choice == 2) {
        CancelReservation(id);
    } else {
        printf("Invalid choice.\n");
    }
}