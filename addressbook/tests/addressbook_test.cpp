#include <fstream>
#include <iostream>
#include <string>
#include "addressbook/addressbook.pb.h"

using namespace std;

void promptForAddress(tutorial::Person* person) {
  cout << "enter person id number:";
  int id;
  cin >> id;
  person->set_id(id);
  cin.ignore(256, '\n');

  cout << "enter name:";
  getline(cin, *person->mutable_name());

  cout << "enter email address (blank for none):";
  string email;
  getline(cin, email, '\n');

  if (!email.empty()) person->set_email(email);

  while (true) {
    cout << "enter a phone number (or leave blank to finish):";
    string number;
    getline(cin, number);
    if (number.empty()) break;

    tutorial::Person::PhoneNumber* phone_number = person->add_phone();
    phone_number->set_number(number);
    cout << "is this a mobile, home, or work phone? ";
    string type;
    getline(cin, type);
    if (type == "mobile")
      phone_number->set_type(tutorial::Person::MOBILE);
    else if (type == "home") {
      phone_number->set_type(tutorial::Person::HOME);
    } else if (type == "work") {
      phone_number->set_type(tutorial::Person::WORK);
    } else {
      cout << "unknown phone type. using default." << endl;
    }
  }
}

void listPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.person_size(); ++i) {
    const tutorial::Person& person = address_book.person(i);
    cout << "person id: " << person.id() << endl;
    cout << "person name: " << person.name() << endl;
    if (!person.email().empty()) {
      cout << "email address: " << person.email();
    }
    for (int j = 0; j < person.phone_size(); ++j) {
      const tutorial::Person::PhoneNumber& phone_number = person.phone(j);
      switch (phone_number.type()) {
        case tutorial::Person::PhoneType::
            Person_PhoneType_Person_PhoneType_INT_MIN_SENTINEL_DO_NOT_USE_:
        case tutorial::Person::MOBILE:
          cout << " mobile phone#:";
          break;
        case tutorial::Person::HOME:
          cout << " home phone#:";
          break;
        case tutorial::Person::PhoneType::
            Person_PhoneType_Person_PhoneType_INT_MAX_SENTINEL_DO_NOT_USE_:
        case tutorial::Person::WORK:
          cout << " work phone#:";
          break;
      }
      cout << phone_number.number() << endl;
    }
  }
}

int main(int argc, char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  if (argc != 2) {
    cerr << "usage: " << argv[0] << "ADDRESS_BOOK_FILE" << endl;
  }

  tutorial::AddressBook address_book;

  {
    fstream input(argv[1], ios::in | ios::binary);
    if (!input)
      cout << argv[1] << ": file not found. creating a new file." << endl;
    else if (!address_book.ParseFromIstream(&input)) {
      cerr << "failed to parse address book." << endl;
      return -1;
    }
  }

  listPeople(address_book);
  promptForAddress(address_book.add_person());
  listPeople(address_book);

  {
    fstream output(argv[1], ios::out | ios::binary);
    if (!address_book.SerializeToOstream(&output)) {
      cerr << "failed to write address book." << endl;
      return -1;
    }
  }

  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
