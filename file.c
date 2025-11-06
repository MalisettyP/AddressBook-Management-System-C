#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contact.txt", "w");
    if (fptr == NULL) {
        printf(RED"❌ Error: Unable to save contacts file.\n"RESET);
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf(GREEN"💾 Contacts saved successfully!\n"RESET);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.txt", "r");
    if (fp == NULL) {
        printf(YELLOW"⚠️  No saved contacts found. Starting a new address book.\n"RESET);
        return;
    }

    fscanf(fp, "%d\n", &addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++) {
        fscanf(fp, "%[^,],%[^,],%s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fp);
    printf(GREEN"📂 Loaded %d contacts successfully!\n"RESET, addressBook->contactCount);
}
