#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice, x = 0;
    AddressBook addressBook;
    addressBook.contactCount = 0;

    // Load saved contacts at start
    loadContactsFromFile(&addressBook);

    do {
        printf(CYAN"\n📖  ADDRESS BOOK MENU\n"RESET);
        printf(MAGENTA"1️⃣  Add New Contact\n");
        printf("2️⃣  Search Contact\n");
        printf("3️⃣  Edit Contact\n");
        printf("4️⃣  Delete Contact\n");
        printf("5️⃣  List All Contacts\n");
        printf("6️⃣  Save & Exit\n"RESET);
        printf(BLUE"👉 Enter your choice: "RESET);

        x = scanf("%d", &choice);

        if (x != 1) {
            printf(RED"❌ Invalid input. Please enter a number.\n"RESET);
            break;
        }

        switch (choice) {
            case 1:
                printf(YELLOW"\n🆕 Adding a new contact...\n"RESET);
                createContact(&addressBook);
                break;

            case 2:
                printf(YELLOW"\n🔍 Searching for a contact...\n"RESET);
                searchContact(&addressBook);
                break;

            case 3:
                printf(YELLOW"\n✏️  Editing a contact...\n"RESET);
                editContact(&addressBook);
                break;

            case 4:
                printf(YELLOW"\n🗑️  Deleting a contact...\n"RESET);
                deleteContact(&addressBook);
                break;

            case 5:
                if (addressBook.contactCount == 0) {
                    printf(YELLOW"⚠️  No contacts available to display.\n"RESET);
                    break;
                }

                printf(CYAN"\n📋 Choose how to sort contacts:\n"RESET);
                printf(MAGENTA"1️⃣  Sort by Name\n");
                printf("2️⃣  Sort by Phone\n");
                printf("3️⃣  Sort by Email\n"RESET);
                printf(BLUE"👉 Enter your choice: "RESET);

                int sortChoice;
                int z = scanf("%d", &sortChoice);
                if (z != 1) {
                    printf(RED"❌ Invalid input.\n"RESET);
                    break;
                }

                listContacts(&addressBook, sortChoice);
                break;

            case 6:
                printf(GREEN"\n💾 Saving contacts...\n"RESET);
                saveContactsToFile(&addressBook);
                printf(BLUE"👋 Goodbye! Contacts saved successfully.\n"RESET);
                break;

            default:
                printf(RED"❌ Invalid choice. Please try again.\n"RESET);
        }

    } while (choice != 6);

    return 0;
}
