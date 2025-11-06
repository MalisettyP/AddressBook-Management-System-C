#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// ✅ Check if phone number already exists
int phone_unique(AddressBook *addressBook, char *phone) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            printf(YELLOW"⚠️  This number already exists. Please enter a unique one.\n"RESET);
            return 1;
        }
    }
    return 0;
}

// ✅ Check if email already exists
int email_unique(AddressBook *addressBook, char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            printf(YELLOW"⚠️  This email is already in use. Try again with another one.\n"RESET);
            return 1;
        }
    }
    return 0;
}

// ✅ Validate name
int chek_name(char *name) {
    if (name[0] == ' ' || name[0] == '.') {
        printf(RED"❌ Name cannot start with space or dot.\n"RESET);
        return 1;
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '.') {
            printf(RED"❌ Invalid name. Please use only letters, spaces, or dots.\n"RESET);
            return 1;
        }
    }
    return 0;
}

// ✅ Validate mobile number
int chek_mobil(char *phone) {
    int i = 0;
    while (phone[i] != '\0') {
        if (!isdigit(phone[i])) {
            printf(RED"❌ Invalid phone number. Digits only please.\n"RESET);
            return 1;
        }
        i++;
    }
    if (i != 10) {
        printf(RED"❌ Phone number must contain exactly 10 digits.\n"RESET);
        return 1;
    }
    return 0;
}

// ✅ Validate email format
int chek_email(char *email) {
    if (!islower(email[0])) {
        printf(RED"❌ Email must start with a lowercase letter.\n"RESET);
        return 1;
    }
    char *at = strchr(email, '@');
    char *dot = strstr(email, ".com");

    if (!at || !dot) {
        printf(RED"❌ Invalid email format. Must contain '@' and end with '.com'.\n"RESET);
        return 1;
    }
    return 0;
}

// 🔍 Search by phone
int search_by_phone(AddressBook *addressBook, char *phone) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasecmp(addressBook->contacts[i].phone, phone) == 0) {
            printf(GREEN"📇 Contact found:\n"RESET);
            printf("👤 Name: %s | 📞 Phone: %s | 📧 Email: %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            return i;
        }
    }
    printf(YELLOW"⚠️  No contact found with this phone number.\n"RESET);
    return -1;
}

// 🔍 Search by name
int search_by_name(AddressBook *addressBook, char *name) {
    int found = -1;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].name, name)) {
            printf(GREEN"📇 Contact found:\n"RESET);
            printf("👤 Name: %s | 📞 Phone: %s | 📧 Email: %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            found = i;
        }
    }
    if (found == -1)
        printf(YELLOW"⚠️  No contact found with that name.\n"RESET);
    return found;
}

// 🔍 Search by email
int search_by_email(AddressBook *addressBook, char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcasestr(addressBook->contacts[i].email, email)) {
            printf(GREEN"📇 Contact found:\n"RESET);
            printf("👤 Name: %s | 📞 Phone: %s | 📧 Email: %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            return i;
        }
    }
    printf(YELLOW"⚠️  No contact found with that email.\n"RESET);
    return -1;
}

// 📋 List all contacts
void listContacts(AddressBook *addressBook, int sortCriteria) {
    if (addressBook->contactCount == 0) {
        printf(YELLOW"⚠️  No contacts to display.\n"RESET);
        return;
    }

    printf(BLUE"\n📋 Contact List:\n"RESET);
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%d️⃣  👤 %s | 📞 %s | 📧 %s\n",
            i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
}

// 🆕 Create a new contact
void createContact(AddressBook *addressBook) {
    char name[50], phone[11], email[50];
    int valid;

    do {
        printf(CYAN"📝 Enter name: "RESET);
        scanf(" %[^\n]", name);
        valid = chek_name(name);
    } while (valid);

    do {
        printf(CYAN"📞 Enter phone (10 digits): "RESET);
        scanf(" %[^\n]", phone);
        valid = chek_mobil(phone) || phone_unique(addressBook, phone);
    } while (valid);

    do {
        printf(CYAN"📧 Enter email: "RESET);
        scanf(" %[^\n]", email);
        valid = chek_email(email) || email_unique(addressBook, email);
    } while (valid);

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;

    printf(GREEN"✅ Contact added successfully!\n"RESET);
}

// ✏️ Edit existing contact
void editContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf(YELLOW"⚠️  No contacts available to edit.\n"RESET);
        return;
    }

    char searchKey[50];
    printf(CYAN"🔍 Enter name to edit: "RESET);
    scanf(" %[^\n]", searchKey);
    int index = search_by_name(addressBook, searchKey);
    if (index == -1) return;

    char newName[50], newPhone[11], newEmail[50];
    int valid;

    printf(MAGENTA"✏️ Editing contact...\n"RESET);

    do {
        printf("📝 New name: ");
        scanf(" %[^\n]", newName);
        valid = chek_name(newName);
    } while (valid);

    do {
        printf("📞 New phone: ");
        scanf(" %[^\n]", newPhone);
        valid = chek_mobil(newPhone) || phone_unique(addressBook, newPhone);
    } while (valid);

    do {
        printf("📧 New email: ");
        scanf(" %[^\n]", newEmail);
        valid = chek_email(newEmail) || email_unique(addressBook, newEmail);
    } while (valid);

    strcpy(addressBook->contacts[index].name, newName);
    strcpy(addressBook->contacts[index].phone, newPhone);
    strcpy(addressBook->contacts[index].email, newEmail);

    printf(GREEN"✅ Contact updated successfully!\n"RESET);
}

// 🗑️ Delete contact
void deleteContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf(YELLOW"⚠️  No contacts to delete.\n"RESET);
        return;
    }

    char searchKey[50];
    printf(CYAN"🔍 Enter name to delete: "RESET);
    scanf(" %[^\n]", searchKey);
    int index = search_by_name(addressBook, searchKey);

    if (index == -1) return;

    for (int i = index; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;
    printf(RED"🗑️  Contact deleted successfully.\n"RESET);
}
void searchContact(AddressBook *addressBook) {
    int option;
    char key[50];

    printf(YELLOW"\n🔍 Search by:\n"RESET);
    printf("1️⃣  Name\n");
    printf("2️⃣  Phone\n");
    printf("3️⃣  Email\n");
    printf(GREEN"👉 Enter choice: "RESET);
    scanf("%d", &option);
    getchar(); // clear newline

    switch (option) {
        case 1:
            printf("Enter name: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0;
            search_by_name(addressBook, key);
            break;

        case 2:
            printf("Enter phone: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0;
            search_by_phone(addressBook, key);
            break;

        case 3:
            printf("Enter email: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0;
            search_by_email(addressBook, key);
            break;

        default:
            printf(RED"⚠️ Invalid choice!\n"RESET);
    }
}

