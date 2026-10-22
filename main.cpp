
/*
  Name: Utkrista Mardan Basnyat
  Course: COMSC-210 Data Structures
  Lab 28: STL Algorithms
  File: main.cpp
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Goat.h"

using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void count_older_goats(const list<Goat> &trip);
void find_goat(const list<Goat> &trip);
void find_youngest_goat(const list<Goat> &trip);
void find_oldest_goat(const list<Goat> &trip);
void check_all_goats(const list<Goat> &trip);
void check_goat_color(const list<Goat> &trip);
int main_menu();

int main() {
  srand(time(0));

  // Read names and colors from files
  ifstream fin("names.txt");
  string names[SZ_NAMES];
  int i = 0;

  while (i < SZ_NAMES && fin >> names[i]) {
    i++;
  }
  fin.close();

  ifstream fin1("colors.txt");
  string colors[SZ_COLORS];
  i = 0;

  while (i < SZ_COLORS && fin1 >> colors[i]) {
    i++;
  }
  fin1.close();

  // Create a random list of goats
  int tripSize = rand() % 8 + 8;
  list<Goat> trip;

  for (int i = 0; i < tripSize; i++) {
    int age = rand() % MAX_AGE;
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];

    Goat tmp(name, age, color);
    trip.push_back(tmp);
  }

  // Goat Manager menu
  int sel = main_menu();

  while (sel != 10) {
    switch (sel) {
      case 1:
        cout << "Adding a goat.\n";
        add_goat(trip, names, colors);
        break;

      case 2:
        cout << "Removing a goat.\n";
        delete_goat(trip);
        break;

      case 3:
        cout << "Displaying goat data.\n";
        display_trip(trip);
        break;

      case 4:
        count_older_goats(trip);
        break;

      case 5:
        find_goat(trip);
        break;

      case 6:
        find_youngest_goat(trip);
        break;

      case 7:
        find_oldest_goat(trip);
        break;

      case 8:
        check_all_goats(trip);
        break;

      case 9:
        check_goat_color(trip);
        break;

      default:
        cout << "Invalid selection.\n";
        break;
    }

    sel = main_menu();
  }

  return 0;
}

int main_menu() {
  cout << "\n*** GOAT MANAGER 3001 ***\n";
  cout << "[1] Add a goat\n";
  cout << "[2] Delete a goat\n";
  cout << "[3] List goats\n";
  cout << "[4] Count goats older than 10\n";
  cout << "[5] Find a goat by name\n";
  cout << "[6] Find the youngest goat\n";
  cout << "[7] Find the oldest goat\n";
  cout << "[8] Check if all goats are older than 5\n";
  cout << "[9] Check if any goat has a selected color\n";
  cout << "[10] Quit\n";
  cout << "Choice --> ";

  int choice;
  cin >> choice;

  while (choice < 1 || choice > 10) {
    cout << "Invalid, again --> ";
    cin >> choice;
  }

  return choice;
}

void count_older_goats(const list<Goat> &trip) {
  // Count goats older than 10
  int count = count_if(trip.begin(), trip.end(),
    [](const Goat &g) {
      return g.get_age() > 10;
    });

  cout << "Goats older than 10: " << count << endl;
}

void find_goat(const list<Goat> &trip) {
  // Search for a goat by name
  string name;

  cout << "Enter goat name: ";
  cin >> name;

  auto it = find_if(trip.begin(), trip.end(),
    [name](const Goat &g) {
      return g.get_name() == name;
    });

  if (it != trip.end()) {
    cout << "Goat found: " << it->get_name()
         << " (" << it->get_age()
         << ", " << it->get_color() << ")\n";
  } else {
    cout << name << " not found.\n";
  }
}

void find_youngest_goat(const list<Goat> &trip) {
  // Find the goat with the lowest age
  if (trip.empty()) {
    cout << "No goats available.\n";
    return;
  }

  auto it = min_element(trip.begin(), trip.end(),
    [](const Goat &a, const Goat &b) {
      return a.get_age() < b.get_age();
    });

  cout << "Youngest goat: " << it->get_name()
       << " (" << it->get_age()
       << ", " << it->get_color() << ")\n";
}

void find_oldest_goat(const list<Goat> &trip) {
  // Find the goat with the highest age
  if (trip.empty()) {
    cout << "No goats available.\n";
    return;
  }

  auto it = max_element(trip.begin(), trip.end(),
    [](const Goat &a, const Goat &b) {
      return a.get_age() < b.get_age();
    });

  cout << "Oldest goat: " << it->get_name()
       << " (" << it->get_age()
       << ", " << it->get_color() << ")\n";
}

void check_all_goats(const list<Goat> &trip) {
  // Check if every goat is older than 5
  if (trip.empty()) {
    cout << "No goats available.\n";
    return;
  }

  bool allOlder = all_of(trip.begin(), trip.end(),
    [](const Goat &g) {
      return g.get_age() > 5;
    });

  if (allOlder) {
    cout << "Yes, all goats are older than 5.\n";
  } else {
    cout << "No, not all goats are older than 5.\n";
  }
}

void check_goat_color(const list<Goat> &trip) {
  // Check if at least one goat matches the selected color
  string color;

  cout << "Enter goat color: ";
  cin >> color;

  bool found = any_of(trip.begin(), trip.end(),
    [color](const Goat &g) {
      return g.get_color() == color;
    });

  if (found) {
    cout << "Yes, a goat with color " << color
         << " exists.\n";
  } else {
    cout << "No goats with color " << color
         << " found.\n";
  }
}

void delete_goat(list<Goat> &trip) {
  cout << "DELETE A GOAT\n";

  if (trip.empty()) {
    cout << "No goats to delete.\n";
    return;
  }

  int index = select_goat(trip);
  auto it = trip.begin();
  advance(it, index - 1);
  trip.erase(it);

  cout << "Goat deleted. New trip size: "
       << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
  cout << "ADD A GOAT\n";

  int age = rand() % MAX_AGE;
  string nm = nms[rand() % SZ_NAMES];
  string cl = cls[rand() % SZ_COLORS];

  Goat tmp(nm, age, cl);
  trip.push_back(tmp);

  cout << "Goat added. New trip size: "
       << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
  int i = 1;

  for (auto gt : trp) {
    cout << "\t[" << i++ << "] "
         << gt.get_name() << " ("
         << gt.get_age() << ", "
         << gt.get_color() << ")\n";
  }
}

int select_goat(list<Goat> trp) {
  int input;

  cout << "Make a selection:\n";
  display_trip(trp);
  cout << "Choice --> ";
  cin >> input;

  while (input < 1 || input > static_cast<int>(trp.size())) {
    cout << "Invalid choice, again --> ";
    cin >> input;
  }

  return input;
}
