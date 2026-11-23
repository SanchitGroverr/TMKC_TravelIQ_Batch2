#include <stdio.h>
#include <string.h>

#define MIN_ATTENDANCE 75

struct Booking
{
    int id;
    char name[50];
    int age;
    int from;
    int to;
    int journey;
    int fare;
    int cancelled;
};

char cities[8][20] = {
    "Delhi",
    "Mumbai",
    "Dehradun",
    "Lucknow",
    "Jaipur",
    "Chandigarh",
    "Agra",
    "Bhopal"
};

struct Booking b[100];

int count = 0;
int nextId = 1001;

// Function to check attendance
int checkAttendance()
{
    int total, attended;
    float percentage;

    printf("\nEnter total classes held: ");
    scanf("%d", &total);

    printf("Enter classes attended: ");
    scanf("%d", &attended);

    if (total <= 0 || attended < 0 || attended > total)
    {
        printf("\nInvalid attendance details!\n");
        return 0;
    }

    percentage = (attended * 100.0) / total;

    printf("\nYour attendance is: %.2f%%\n", percentage);

    if (percentage >= MIN_ATTENDANCE)
    {
        printf("Attendance criteria satisfied. You can travel.\n");
        return 1;
    }
    else
    {
        printf("Attendance is below 75%%.\n");
        printf("Booking denied. You may be detained from examination.\n");
        return 0;
    }
}

// Function to display available cities
void displayCities()
{
    int i;

    printf("\nAvailable Cities:\n");

    for (i = 0; i < 8; i++)
    {
        printf("%d. %s\n", i + 1, cities[i]);
    }
}

// Function to select departure and destination
int selectCities(int *from, int *to)
{
    displayCities();

    printf("\nEnter departure city number: ");
    scanf("%d", from);

    printf("Enter destination city number: ");
    scanf("%d", to);

    if (*from < 1 || *from > 8 || *to < 1 || *to > 8)
    {
        printf("\nInvalid city selection!\n");
        return 0;
    }
    if (*from == *to)
    {
        printf("\nDeparture and destination cannot be the same!\n");
        return 0;
    }

    return 1;
}

// Function to book a ticket
void bookTicket()
{
    int from, to, choice;

    if (count >= 100)
    {
        printf("\nBooking limit reached!\n");
        return;
    }

    printf("\n----- Ticket Booking -----\n");

    if (!selectCities(&from, &to))
    {
        return;
    }

    printf("\nSelect Travel Mode:\n");
    printf("1. Train\n");
    printf("2. Flight\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2)
    {
        printf("\nInvalid travel mode!\n");
        return;
    }

    // Check attendance before confirming booking
    if (!checkAttendance())
    {
        return;
    }

    printf("\nEnter passenger name: ");
    scanf(" %49[^\n]", b[count].name);

    printf("Enter passenger age: ");
    scanf("%d", &b[count].age);

    if (b[count].age <= 0)
    {
        printf("\nInvalid age!\n");
        return;
    }

    b[count].id = nextId++;
    b[count].from = from - 1;
    b[count].to = to - 1;
    b[count].journey = choice;
    b[count].cancelled = 0;

    if (choice == 1)
    {
        b[count].fare = 1000;
    }
    else
    {
        b[count].fare = 4000;
    }

    printf("\n----- Booking Confirmed -----\n");
    printf("Ticket ID: %d\n", b[count].id);
    printf("Passenger Name: %s\n", b[count].name);
    printf("Departure: %s\n", cities[b[count].from]);
    printf("Destination: %s\n", cities[b[count].to]);

    if (choice == 1)
    {
        printf("Travel Mode: Train\n");
    }
    else
    {
        printf("Travel Mode: Flight\n");
    }

    printf("Fare: Rs. %d\n", b[count].fare);

    count++;
}

// Function to view all bookings
void viewBookings()
{
    int i, found = 0;

    printf("\n----- All Bookings -----\n");

    for (i = 0; i < count; i++)
    {
        if (b[i].cancelled == 0)
        {
            found = 1;

            printf("\nTicket ID: %d\n", b[i].id);
            printf("Passenger Name: %s\n", b[i].name);
            printf("Age: %d\n", b[i].age);
            printf("Departure: %s\n", cities[b[i].from]);
            printf("Destination: %s\n", cities[b[i].to]);

            if (b[i].journey == 1)
            {
                printf("Travel Mode: Train\n");
            }
            else
            {
                printf("Travel Mode: Flight\n");
            }

            printf("Fare: Rs. %d\n", b[i].fare);
        }
    }

    if (found == 0)
    {
        printf("\nNo active bookings found!\n");
    }
}

// Function to cancel a ticket
void cancelBooking()
{
    int id, i, found = 0;

    printf("\nEnter Ticket ID to cancel: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (b[i].id == id && b[i].cancelled == 0)
        {
            b[i].cancelled = 1;
            found = 1;

            printf("\nTicket cancelled successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("\nTicket not found or already cancelled!\n");
    }
}

// Main function
int main()
{
    int choice;

    printf("=================================\n");
    printf("        WELCOME TO TRAVELIQ      \n");
    printf("=================================\n");

    do
    {
        printf("\n\n========== MAIN MENU ==========\n");
        printf("1. Book Ticket\n");
        printf("2. View Bookings\n");
        printf("3. Cancel Ticket\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                viewBookings();
                break;

            case 3:
                cancelBooking();
                break;

            case 4:
                printf("\nThank you for using TravelIQ!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}