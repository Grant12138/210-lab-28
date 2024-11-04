#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

// Additional functionalities
void sortGoatByAge(list<Goat>& trip);
void sortGoatByName(list<Goat>& trip);
void reverseTripOrder(list<Goat>& trip);
void removeGoatsOlderThan(list<Goat>& trip);
void countGoatsByColor(list<Goat>& trip);
void findGoatByName(list<Goat>& trip);
void increaseAges(list<Goat>& trip);
void removeGoatsBySpecies(list<Goat>& trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 11) {
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
                cout << "Sorting goats by age.\n";
                sortGoatByAge(trip);
                break;
            case 5:
                cout << "Sorting goats by name.\n";
                sortGoatByName(trip);
                break;
            case 6:
                cout << "Reversing the trip order.\n";
                reverseTripOrder(trip);
                break;
            case 7:
                cout << "Removing goats older than a certain age.\n";
                removeGoatsOlderThan(trip);
                break;
            case 8:
                cout << "Counting goats by color.\n";
                countGoatsByColor(trip);
                break;
            case 9:
                cout << "Finding a goat by name.\n";
                findGoatByName(trip);
                break;
            case 10:
                cout << "Increasing age of all goats by 1.\n";
                increaseAges(trip);
                break;
            case 11:
                cout << "Removing goats by species.\n";
                removeGoatsBySpecies(trip);
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
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n";
    cout << "[5] Reverse trip order\n";
    cout << "[6] Remove goats older than a certain age\n";
    cout << "[7] Count goats by color\n";
    cout << "[8] Find a goat by name\n";
    cout << "[9] Increase age of all goats by 1\n";
    cout << "[10] Remove goats by species\n"
    cout << "[11] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 11) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

// Sort Goats by Age
void sortGoatByAge(list<Goat>& trip)
{
    trip.sort([](const Goat& a, const Goat& b) -> bool { return a.get_age() < b.get_age(); });
}
// Sort Goats by Name
void sortGoatByName(list<Goat>& trip)
{
    trip.sort([](const Goat& a, const Goat& b) -> bool { return a.get_name() < b.get_name(); });
}
// Reverse the Trip Order
void reverseTripOrder(list<Goat>& trip)
{
    trip.reverse();
}
// Remove Goats Older Than 10
void removeGoatsOlderThan(list<Goat>& trip)
{
    int AGE_THRESHOLD = 10;
    trip.remove_if([AGE_THRESHOLD](const Goat& g) -> bool { return g.get_age() > AGE_THRESHOLD; });
}
// Count Goats by Color
void countGoatsByColor(list<Goat>& trip)
{
    string color;
    cout << "Enter color to count: ";
    getline(cin, color);

    int count = count_if(trip.begin(), trip.end(), [&color](const Goat& g) -> bool { return g.get_color() == color; });
    cout << "Number of goats with " << color << " color: " << count;
}
// Find and Display a Goat by Name
void findGoatByName(list<Goat>& trip)
{
    string name;
    cout << "Enter goat name to find: ";
    getline(cin, name);

    auto it = find_if(trip.begin(), trip.end(), [&name](const Goat& g) -> bool { return g.get_name() == name; });
    if (it == trip.end())
        cout << "Goat not found\n";
    else
        cout << "Goat found: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
}
void increaseAges(list<Goat>& trip);
void removeGoatsBySpecies(list<Goat>& trip);