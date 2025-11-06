// 💾 file.h — Handles saving and loading contacts
#ifndef FILE_H
#define FILE_H

#include "contact.h"

// 💾 Save all contacts to file
void saveContactsToFile(AddressBook *addressBook);

// 📂 Load contacts from file
void loadContactsFromFile(AddressBook *addressBook);

#endif
