#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "accountNumber.h"
#include "counter.h"

using namespace std;

struct Bus
{
    int bus_dest_cd;
    string bus_cd[2];
    int seatAvailble[2];
    string leaving_time[4];
};

Bus *bus_rg[100];

Bus bus_info();

struct City
{
    string dest_name;
    float km_from_AA;
    string direction;
    Bus busDestInfo;
};
City *Destination[100], *startingCity[100];

struct reserve
{
    string fname, lname, fullName;
    string destination, initial_city;
    int payement;
    int accountNumber;
    int securityNumber;
    int resrvd_seat;
    int ticket_size;
    int return_oneWay;
    float travelling_distance;
    string resrvd_bus;
    string leaving_time;
    bool is_reserverd;
};
reserve *resrvd_acc[100];

Counter dest_cd, num_of_bus;

// list of functions
void destinationCity();
void starting_city();
void showDestination(City *[]);
void showBusInfo();
int travelling_city();
int initial_city();
void reserveSeat();
float distance_calculator(int, int);
bool bus_assignment(int, int, reserve *[]);
float payement_calculator(int, reserve *[]);
void confirm_resrv(int);
void receipt(int);

// initial_destination city and km
string city[5] = {"Jimma", "Nakemte", "Bahirdar", "Gambela", "Makelle"};
float distance_AA[5] = {25, 50, 100, 30, 10};
char direction_AA[5] = {'N', 'S', 'W', 'E', 'N'};
string l_time[4] = {"12:00 AM", "6:00 AM", "12:00 PM", "6:00 PM"};

// global Variables;
int number_buses = 0, number_dest = 0;
int counter = 0;
int resrv_counter = 0;

int main()
{
    number_buses = 10;
    number_dest = 5;
    bankInformation(); // a function that calls Bank information of a customer;
    destinationCity();
    showDestination(Destination);
    showBusInfo();
    starting_city();
    reserveSeat();
}

// list of destination city
int travelling_city()
{
    int city_choice;
    for (int i = 0; i < 5; i++)
    {
        cout << "[" << i + 1 << "] " << city[i] << endl;
    }
    cin >> city_choice;
    return city_choice;
}

// returns structure
Bus bus_info()
{
    // bus_rg[counter] = new Bus;
    int value = 0;
    bus_rg[counter] = new Bus;
    bus_rg[counter]->bus_dest_cd = 100 + counter;
    int dest_per_bus = number_buses / number_dest;

    for (int i = 0; i < dest_per_bus; i++)
    {
        char code = 65;
        code += i;
        bus_rg[counter]->bus_cd[i] = to_string(bus_rg[counter]->bus_dest_cd) + code;
        bus_rg[counter]->leaving_time[i] = l_time[i];                                
        bus_rg[counter]->seatAvailble[i] = 100;
    }

    return *bus_rg[counter];
}

// create  destination city;
void destinationCity()
{

    for (int i = 0; i < 5; i++)
    {
        Destination[counter] = new City;
        Destination[counter]->dest_name = city[i];
        Destination[counter]->km_from_AA = distance_AA[i];
        Destination[counter]->direction = direction_AA[i];
        Destination[counter]->busDestInfo = bus_info();
        counter++;
    }
}

// create initial starting city
void starting_city()
{
    for (int i = 0; i < 5; i++)
    {
        startingCity[i] = new City;
        startingCity[i]->dest_name = city[i];
        startingCity[i]->km_from_AA = distance_AA[i];
        startingCity[i]->direction = direction_AA[i];
    }
}

void showDestination(City *Destination[])
{
    cout << setw(75) << setfill('_') << "_" << endl;
    cout << "|Destination Name | Distance in KM from AA "
         << "| Direction from AA | Bus Code |\n";
    for (int i = 0; i < 5; i++)
    {
        cout << setw(75) << setfill('_') << "|" << endl;
        cout << left << setw(10) << setfill(' ') << Destination[i]->dest_name << "\t\t"
             << left << setw(5) << Destination[i]->km_from_AA << "\t\t\t  "
             << left << setw(10) << Destination[i]->direction << "\t  "
             << Destination[i]->busDestInfo.bus_dest_cd << "\t  |" << endl;
    }
    cout << setw(75) << setfill('_') << "_" << endl;
}

void showBusInfo()
{
    cout << "AS = Available seat \n";
    cout << "Bus code | Destination | number of buses | Bus 1 AS | Leaving Time | Bus2 AS | Leaving Time \n";
    for (int i = 0; i < 5; i++)
    {
        cout << " " << left << setw(10) << setfill(' ') << bus_rg[i]->bus_dest_cd << "  "
             << left << setw(10) << Destination[i]->dest_name << "\t\t"
             << left << setw(10) << 2 << "   ";
        for (int j = 0; j < 2; j++)
        {
            cout << left << setw(10) << bus_rg[i]->seatAvailble[j]
                 << left << setw(10) << bus_rg[i]->leaving_time[j] << "\t";
        }
        cout << endl;
    }
}

// reserve seat
void reserveSeat()
{
    resrvd_acc[resrv_counter] = new reserve;

    cout << "Enter Name: ";
    cin >> resrvd_acc[resrv_counter]->fname;

    // travelling city information;
    cout << "Choose starting Point: ";
    int startingPoint = travelling_city() - 1;
    cout << "Choose Destination City: ";
    int destination = travelling_city() - 1;

    // calculating distance between starting city and destination city;
    if (startingPoint != destination)
    {
        // assign a city to customer information
        resrvd_acc[resrv_counter]->destination = city[destination];
        resrvd_acc[resrv_counter]->initial_city = city[startingPoint];

        resrvd_acc[resrv_counter]->travelling_distance = distance_calculator(destination, startingPoint);
    }
    else
        cout << "No inside service \n";

    cout << "Choose Travelling option \n"
         << "[1] One Way \n"
         << "[2] Return: ";
    cin >> resrvd_acc[resrv_counter]->return_oneWay;
    cout << "Number of tickets: ";
    cin >> resrvd_acc[resrv_counter]->ticket_size;

    // bus Assignment
    bool bus_available = bus_assignment(destination, resrv_counter, resrvd_acc);
    if (bus_available)
    {
        // Bank Account Information;
        cout << "Enter account: ";
        cin >> resrvd_acc[resrv_counter]->accountNumber;
        cout << "Enter security Code: ";
        cin >> resrvd_acc[resrv_counter]->securityNumber;

        // calculates total payement;
        float payement = payement_calculator(resrv_counter, resrvd_acc);
        resrvd_acc[resrv_counter]->payement = payement;

        // confirm payement and reservation;
        confirm_resrv(resrv_counter);
        cout << "Do you want to continue \n (Y\\N)";
        char confirm;
        cin >> confirm;
        confirm = tolower(confirm);

        if (confirm == 'y')
        {
            // check your payement information from banks
            bool success = accountCheck(resrvd_acc[resrv_counter]->payement,
                                        resrvd_acc[resrv_counter]->accountNumber,
                                        resrvd_acc[resrv_counter]->securityNumber);
            if (success)
            {
                resrvd_acc[resrv_counter]->resrvd_seat = 1 + resrv_counter;
                cout << "Transaction was successful \n";
                receipt(resrv_counter);
                resrv_counter++;
            }
            else
                cout << "Transaction was not successful \n";
        }
        else
        {
            delete resrvd_acc[resrv_counter];
            cout << "Request canceled \n";
        }
    }
}

// confirm reservation
void confirm_resrv(int i)
{
    cout << "Name: " << resrvd_acc[i]->fname << endl;
    cout << "Destination: " << resrvd_acc[i]->destination << endl;
    cout << "Bus code : " << resrvd_acc[i]->resrvd_bus << endl;
    cout << "Leaving time: " << resrvd_acc[i]->leaving_time << endl;
    cout << "Distance in km: " << resrvd_acc[i]->travelling_distance << endl;
    cout << "Total payment : " << resrvd_acc[i]->payement << endl;
}

// distance calculator
float distance_calculator(int destination, int startingPoint)
{
    float distance_km;
    // if the two cities are on the same direction
    if (Destination[destination]->direction == startingCity[startingPoint]->direction)
    {
        bool dist_check = Destination[destination]->km_from_AA > 
                          startingCity[startingPoint]->km_from_AA;
        if (dist_check)
        {
            distance_km = (Destination[destination]->km_from_AA - 
                           startingCity[startingPoint]->km_from_AA);
        }
        else
        {
            distance_km = (startingCity[startingPoint]->km_from_AA - 
                           Destination[destination]->km_from_AA);
        }
    }
    else // if the two cities are on different direction;
    {
        cout << "Choose path: "
             << "[1] Through Addis Ababa \n"
             << "[2] Direct way \n";
        int option; cin >> option;
        switch (option)
        {
        case 1:
        {
            distance_km = (Destination[destination]->km_from_AA + 
                           startingCity[startingPoint]->km_from_AA);
            break;
        }
        case 2:
        {
            distance_km = sqrt(pow(Destination[destination]->km_from_AA, 2) + 
                               pow(startingCity[startingPoint]->km_from_AA, 2));
            break;
        }
        default:
            break;
        }
    }
    return distance_km;
}

// assignning bus to a customer;
bool bus_assignment(int destination, int resrv_counter, reserve *resrvd_acc[])
{
    if (bus_rg[destination]->seatAvailble[0] > 0)
    {
        resrvd_acc[resrv_counter]->resrvd_bus = bus_rg[destination]->bus_cd[0];
        resrvd_acc[resrv_counter]->leaving_time = l_time[0];
        bus_rg[destination]->seatAvailble[0]--;
        return true;
    }
    else if ((bus_rg[destination]->seatAvailble[0] == 0) && 
              bus_rg[destination]->seatAvailble[1] > 0)
    {
        resrvd_acc[resrv_counter]->resrvd_bus = bus_rg[destination]->bus_cd[1];
        resrvd_acc[resrv_counter]->leaving_time = l_time[1];
        bus_rg[destination]->seatAvailble[1]--;
        return true;
    }
    else
    {
        cout << "NO available seat \n";
        return false;
    }
}

// calculating payement;
float payement_calculator(int resrv_counter, reserve *resrvd_acc[])
{

    float payement = resrvd_acc[resrv_counter]->return_oneWay *
                     resrvd_acc[resrv_counter]->ticket_size *
                     resrvd_acc[resrv_counter]->travelling_distance * 10;
    return payement;
}


// printing receipt after confirming the transaction;
void receipt(int resrv_counter) {
    system("cls");
    cout  << right <<setw(50) << "Bus X Transport Service\n";
    cout << "Receipt Number: " << resrvd_acc[resrv_counter]->resrvd_seat << endl;
    cout << "Prepared for: " << resrvd_acc[resrv_counter]->fname << endl;
    cout << "Travel Info: From " << resrvd_acc[resrv_counter]->initial_city << " TO " <<  resrvd_acc[resrv_counter]->destination << endl;
    cout << "Date: " << "01-01-2021" << endl;
    cout << endl;
    cout << "Description Quantity price/Quantity Total Price " << endl;
    cout << left << setw(10) << "Transport\t"
         << left << setw(10) << resrvd_acc[resrv_counter]->ticket_size << " "
         << left << setw(10) << resrvd_acc[resrv_counter]->travelling_distance /10
         << left << setw(10) << resrvd_acc[resrv_counter]->payement;

}