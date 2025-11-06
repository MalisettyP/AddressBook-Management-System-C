#include "contact.h"

// 🧩 Default Game of Thrones contacts 🐉⚔️
static Contact defaultContacts[] = {
    {"Jon Snow", "9876543210", "jon@winterfell.com"},
    {"Daenerys Targaryen", "9123456780", "dany@dragonstone.com"},
    {"Arya Stark", "9988776655", "arya@faceless.org"},
    {"Tyrion Lannister", "9090909090", "tyrion@casterlyrock.com"},
    {"Sansa Stark", "9812345678", "sansa@winterfell.com"},
    {"Cersei Lannister", "9001122334", "cersei@redkeep.com"},
    {"Jaime Lannister", "9334455667", "jaime@kingsguard.com"},
    {"Bran Stark", "9556677889", "bran@threeeyedraven.com"},
    {"Samwell Tarly", "9445566778", "sam@citadel.com"},
    {"Brienne of Tarth", "9667788990", "brienne@tarth.com"}
};

// 🌿 Load default GOT contacts
void populateAddressBook(AddressBook *addressBook)
{
    int numDefaults = sizeof(defaultContacts) / sizeof(defaultContacts[0]);
    for (int i = 0; i < numDefaults && addressBook->contactCount < MAX_CONTACTS; ++i) {
        addressBook->contacts[addressBook->contactCount++] = defaultContacts[i];
    }
    printf(GREEN"🐺 Game of Thrones contacts loaded successfully!\n"RESET);
}
