
#include <iostream>
#include <cstdlib> // used for clearing terminal 
#include <limits> // used for limiting input to one character

using namespace std;

// Define a Disk struct to represen disks
struct Disk {
    int size;
    Disk* next = nullptr;
    Disk(int size);
};

// Constructor for Disk
Disk::Disk(int size) {
    this->size = size;
}

// Define a Tower class to tower in the Tower of Hanoi
class Tower {
private:
    Disk* top = nullptr;

public:
    Tower();
    ~Tower();
    void addDisk(int size);
    void removeDisk();
    void displayTower() const;
    int lastElementSize() const;
    int size() const;
};

// Constructor for Tower
Tower::Tower() {
}

// Destructor for Tower 
Tower::~Tower() {
    while (top) {
        Disk* temp = top;
        top = top->next;
        delete temp;
    }
}

// Return the size of the last disk in the tower
int Tower::lastElementSize() const {
    Disk* temp = top;
    int last{ 0 };
    while (temp) {
        last = temp->size;
        temp = temp->next;
    }
    return last;
}

// Display the current arrangement of disks in the tower
void Tower::displayTower() const {
    Disk* temp = top;
    while (temp) {
        cout << "| Disk: " << temp->size << " |" << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Return the number of disks in the tower
int Tower::size() const {
    Disk* temp = top;
    int size{ 0 };
    while (temp) {
        size++;
        temp = temp->next;
    }
    return size;
}

// Remove the top disk from the tower
void Tower::removeDisk() {
    if (top == nullptr)
        ;
    else if (top->next == nullptr) {
        delete top;
        top = nullptr;
    }
    else {
        Disk* temp = top;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}

// Add a disk to the tower with the given size
void Tower::addDisk(int size) {
    Disk* newDisk = new Disk(size);
    if (top == nullptr) {
        top = newDisk;
    }
    else {
        Disk* temp = top;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newDisk;
    }
}

// Function to clear the terminal screen
void clearTerminal() {
#ifdef _WIN32
    system("cls");  // For Windows
#else
    system("clear");  // For Linux and macOS
#endif
}

// Function for moving disks between towers
void moveDisk(Tower& source, Tower& destination) {
    if (destination.lastElementSize() > source.lastElementSize() || destination.lastElementSize() == 0) {
        destination.addDisk(source.lastElementSize());
        source.removeDisk();
    }
    else {
        cout << "\nYou cannot place a larger disk on a smaller one.";
    }
}

int main() {
    Tower tower1;
    Tower tower2;
    Tower tower3;

    // Get the number of disks from the user
    int n;
    cout << "Enter the number of disks in the Tower of Hanoi: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid input. Please enter a positive integer for the number of disks.";
    }

    // Initialize Tower 1 with disks in descending order
    for (int i = 0; i < n; i++) {
        tower1.addDisk(n - i);
    }

    // Main loop for user interaction
    while (tower3.size() != n) {
        clearTerminal();

        cout << "======================================================================================\n";
        cout << "                                         RULES:\n";
        cout << "                  1) you can only move smaller disk on top of larger one\n";
        cout << "              2) to complete the tower, you need to move all disks to tower 3\n";
        cout << "                3) to move disks, input letters corresponding to the given moves\n";
        cout << "======================================================================================\n\n";

        cout << "\nCurrent arrangement of disks in the Tower of Hanoi: \n";
        cout << "Tower 1: ";
        tower1.displayTower();
        cout << "\nTower 2: ";
        tower2.displayTower();
        cout << "\nTower 3: ";
        tower3.displayTower();
        cout << endl;

        char operation;

        // Get user input for disk movement
        cout << "How do you want to move the disks? \n a: from Tower 1 to Tower 2 \n b: from Tower 1 to Tower 3 \n c: from Tower 2 to Tower 3 \n d: from Tower 2 to Tower 1 \n e: from Tower 3 to Tower 2 \n f: from Tower 3 to Tower 1\n";

        // Validate user input to be a single character
        while (!(cin >> operation) || cin.peek() != '\n') {
            cout << "Invalid input. Please enter a single character.\n";
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        }

        switch (operation) {
        case 'a':
            moveDisk(tower1, tower2);
            break;
        case 'b':
            moveDisk(tower1, tower3);
            break;
        case 'c':
            moveDisk(tower2, tower3);
            break;
        case 'd':
            moveDisk(tower2, tower1);
            break;
        case 'e':
            moveDisk(tower3, tower2);
            break;
        case 'f':
            moveDisk(tower1, tower3);
            break;
        default:
            cout << "\nInvalid operation. Please choose a valid operation.";
        }
    }

    clearTerminal();

    cout << "======================================================================================\n\n";
    cout << "                   Congratulations you completed the Hanoi Tower\n\n";
    cout << "======================================================================================\n\n";

    return 0;
}
