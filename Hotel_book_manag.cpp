#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Room {
public:
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isBooked;

    Room(int number, string type, double price) {
        roomNumber = number;
        roomType = type;
        pricePerNight = price;
        isBooked = false;
    }

    void display() const {
        cout << "Room Number: " << roomNumber
             << " | Type: " << roomType
             << " | Price: Rs. " << fixed
             << setprecision(2) << pricePerNight
             << " | Status: "
             << (isBooked ? "Booked" : "Available")
             << endl;
    }
};

class Booking {
public:
    int bookingID;
    int roomNumber;
    string guestName;
    int nights;

    Booking(int id, int room, string name, int n) {
        bookingID = id;
        roomNumber = room;
        guestName = name;
        nights = n;
    }

    double calculateBill(double price) const {
        return price * nights;
    }

    void display(double price) const {
        cout << "\nBooking ID : " << bookingID;
        cout << "\nGuest Name : " << guestName;
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nNights     : " << nights;
        cout << "\nTotal Bill : Rs. " << fixed
             << setprecision(2)
             << calculateBill(price) << endl;
        cout << "------------------------------\n";
    }
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Booking> bookings;
    int nextBookingID;

public:
    Hotel() {
        nextBookingID = 1001;

        rooms.emplace_back(101, "Single", 1000);
        rooms.emplace_back(102, "Single", 1000);
        rooms.emplace_back(201, "Double", 1800);
        rooms.emplace_back(202, "Double", 1800);
        rooms.emplace_back(301, "Deluxe", 3000);
    }

    void displayRooms() const {
        cout << "\n===== HOTEL ROOM LIST =====\n";

        for (const Room& room : rooms) {
            room.display();
        }
    }

    void bookRoom() {
        int number, nights;
        string name;

        cout << "Enter guest name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter room number: ";
        cin >> number;

        cout << "Enter number of nights: ";
        cin >> nights;

        if (nights <= 0) {
            cout << "Number of nights must be positive!\n";
            return;
        }

        for (Room& room : rooms) {
            if (room.roomNumber == number) {
                if (room.isBooked) {
                    cout << "Room is already booked!\n";
                    return;
                }

                room.isBooked = true;

                bookings.emplace_back(
                    nextBookingID, number, name, nights
                );

                cout << "Room booked successfully!\n";
                cout << "Your booking ID: "
                     << nextBookingID << endl;

                nextBookingID++;
                return;
            }
        }

        cout << "Room number not found!\n";
    }

    void displayBookings() const {
        if (bookings.empty()) {
            cout << "No bookings available!\n";
            return;
        }

        for (const Booking& booking : bookings) {
            for (const Room& room : rooms) {
                if (booking.roomNumber == room.roomNumber) {
                    booking.display(room.pricePerNight);
                    break;
                }
            }
        }
    }

    void searchBooking() const {
        int id;

        cout << "Enter booking ID: ";
        cin >> id;

        for (const Booking& booking : bookings) {
            if (booking.bookingID == id) {
                for (const Room& room : rooms) {
                    if (room.roomNumber == booking.roomNumber) {
                        booking.display(room.pricePerNight);
                        return;
                    }
                }
            }
        }

        cout << "Booking not found!\n";
    }

    void checkOut() {
        int id;

        cout << "Enter booking ID for checkout: ";
        cin >> id;

        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i].bookingID == id) {
                int number = bookings[i].roomNumber;

                for (Room& room : rooms) {
                    if (room.roomNumber == number) {
                        bookings[i].display(room.pricePerNight);
                        room.isBooked = false;
                        break;
                    }
                }

                bookings.erase(bookings.begin() + i);
                cout << "Checkout completed successfully!\n";
                return;
            }
        }

        cout << "Booking not found!\n";
    }
};

int main() {
    Hotel hotel;
    int choice;

    do {
        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. View Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. View All Bookings\n";
        cout << "4. Search Booking\n";
        cout << "5. Check Out Guest\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hotel.displayRooms();
            break;

        case 2:
            hotel.bookRoom();
            break;

        case 3:
            hotel.displayBookings();
            break;

        case 4:
            hotel.searchBooking();
            break;

        case 5:
            hotel.checkOut();
            break;

        case 6:
            cout << "Thank you for using the hotel system!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
