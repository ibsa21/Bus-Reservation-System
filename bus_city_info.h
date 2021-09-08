#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// bus information container
struct Bus
{
    int bus_dest_cd;
    string bus_cd[2];
    int seatAvailble[2];
    int payement[2];
    string leaving_time[4];
};
Bus *bus_rg[100];

// contains information about city
struct City
{
    string city_name;
    float km_from_AA;
    string direction;
    Bus busDestInfo;
};
City *cities_info[100];

// login informatino container
struct login
{
    string id, password;
};
login *login_create[5];

// variables
int cityNo_count = 0;

// list of initial cities city and km
string city[5] = {"Jimma", "Nakemte", "Bahirdar", "Gambela", "Makelle"};
float distance_AA[5] = {25, 50, 100, 30, 10};
string direction_AA[5] = {"north", "south", "west", "east", "north"};
string l_time[4] = {"12:00 AM", "6:00 AM", "12:00 PM", "6:00 PM"};

// initial login information for ticketer and administrator
string initial_login[][2] = {{"admin", "password"}, {"ticketer", "password"}};

// ammending bus information
int number_buses = 10;
int number_dest = 5;
int bus_dest_count = 0;
Bus bus_info()
{
    bus_rg[bus_dest_count] = new Bus;
    bus_rg[bus_dest_count]->bus_dest_cd = 100 + bus_dest_count;
    int dest_per_bus = number_buses / number_dest;

    for (int i = 0; i < dest_per_bus; i++)
    {
        char code = 65;
        code += i;
        bus_rg[bus_dest_count]->bus_cd[i] = to_string(bus_rg[bus_dest_count]->bus_dest_cd) + code;
        bus_rg[bus_dest_count]->leaving_time[i] = l_time[i];
        bus_rg[bus_dest_count]->seatAvailble[i] = 100;
        bus_rg[bus_dest_count]->payement[i] = 0;
    }

    return *bus_rg[bus_dest_count];
}

// create  destination city;
void destinationCity()
{

    for (int i = 0; i < 5; i++)
    {
        cities_info[cityNo_count] = new City;
        cities_info[cityNo_count]->city_name = city[i];
        cities_info[cityNo_count]->km_from_AA = distance_AA[i];
        cities_info[cityNo_count]->direction = direction_AA[i];
        cities_info[cityNo_count]->busDestInfo = bus_info();
        cityNo_count++;
        bus_dest_count++;
    }
}

// shows customer list of cities giving service
int travelling_city()
{
    int city_choice;
    for (int i = 0; i < cityNo_count; i++)
    {
        cout << "[" << i + 1 << "] " << cities_info[i]->city_name << endl;
    }
    cin >> city_choice;
    return city_choice;
}

// INITIAL ACCESS GRANTING
int num_access = 0;
void login_info()
{
    for (int i = 0; i < 2; i++)
    {
        login_create[num_access] = new login;
        login_create[num_access]->id = initial_login[i][0];
        login_create[num_access]->password = initial_login[i][1];
        num_access++;
    }
}

// TICKETER PAGE FUNCTIONALITIES
// show lists of all cities and correspoing bus information
void list_cities(City *cities_info[])
{
    system("cls");
    cout << setw(75) << setfill('_') << "_" << endl;
    cout << "|Name of cities   | Distance in KM from AA "
         << "| Direction from AA | Bus Code |\n";
    for (int i = 0; i < 5; i++)
    {
        if (cities_info[i] != NULL)
        {
            cout << setw(75) << setfill('_') << "|" << endl;
            cout << left << setw(10) << setfill(' ') << cities_info[i]->city_name << "\t\t"
                 << left << setw(5) << cities_info[i]->km_from_AA << "\t\t\t  "
                 << left << setw(10) << cities_info[i]->direction << "\t  "
                 << cities_info[i]->busDestInfo.bus_dest_cd << "\t  |" << endl;
        }
    }
    cout << setw(75) << setfill('_') << "_" << endl;
}

// show buscode, leaving time, and available seat
void showBusInfo()
{
    system("cls");
    cout << "AS = Available seat \n";
    cout << "Bus code | Destination | number of buses | "
         << "Bus 1 AS | Leaving Time | Bus2 AS | Leaving Time \n";

    for (int i = 0; i < 5; i++)
    {
        cout << " " << left << setw(10) << setfill(' ')
             << bus_rg[i]->bus_dest_cd << "  "
             << left << setw(10) << cities_info[i]->city_name << "\t\t"
             << left << setw(10) << 2 << "   ";

        for (int j = 0; j < 2; j++)
        {
            cout << left << setw(10) << bus_rg[i]->seatAvailble[j]
                 << left << setw(10) << bus_rg[i]->leaving_time[j] << "\t";
        }
        cout << endl;
    }
}

// ## administrator functionalites
void add_city()
{
    system("cls");
    cities_info[cityNo_count] = new City;
    cout << "Enter name of new city: ";
    cin >> cities_info[cityNo_count]->city_name;
    cout << "Enter city distance in km from AA: ";
    cin >> cities_info[cityNo_count]->km_from_AA;
    cout << "Enter city direction from AA: ";
    cin >> cities_info[cityNo_count]->direction;

    // appending bus information
    cities_info[cityNo_count]->busDestInfo = bus_info();
    cout << "Operation ended successfuly\n";
    cityNo_count++;
}

void remove_city()
{
        system("cls");
    string city_rmv;
    int city_rmv_index;
    bool found_city = false;

    cout << "Enter a city Name to be removed: ";
    cin >> city_rmv;

    for (int i = 0; i < cityNo_count; i++)
    {
        if (city_rmv == cities_info[i]->city_name)
        {
            city_rmv_index = i;
            found_city = true;
        }
    }

    if (found_city)
    {
        for (int i = city_rmv_index; i < cityNo_count; i++)
            cities_info[i] = cities_info[i + 1];

        delete cities_info[cityNo_count];
        cities_info[cityNo_count] = NULL;
        cityNo_count--;
    }
    else 
        cout << "The city you have entered does not exist \n";
}

//access granting to ticketer by administrator
void create_ticketer_login()
{
        system("cls");
    login_create[num_access] = new login;

    cout << "Enter ticketer ID: ";
    cin >> login_create[num_access]->id;
    cout << "Enter ticketer password: ";
    cin >> login_create[num_access]->password;
    cout << "Operation ended successfuly \n";
    num_access++;
}