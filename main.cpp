#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include "PaymentIntegration/accountNumber.h"
#include "bus_city_info.h"

using namespace std;

struct reserve
{
    string fullName;
    string destination, initial_city;
    unsigned int age;
    int payement;
    int accountNumber;
    int securityNumber;
    int resrvd_seat;
    int ticket_size;
    int return_oneWay;
    float travelling_distance;
    bool is_reserverd;
    bool is_prepaid;
    int dest_no, bus_code;
    string resrvd_bus;
    string leaving_time;
};
reserve *resrvd_acc[1000];

// functions participating in reserving a seat
void reserveSeat();
float distance_calculator(int, int);
bool bus_assignment(int, int, reserve *[], int &);
int change_leaving_time(int);
float payement_calculator(int, reserve *[], bool);
void confirm_resrv(int);
void receipt(int);

//global functions
int first_ui();
void date_time();

//interface of customer
int cust_first_ui();
void respond_cust_request();
int search_destination();
void modify_reservation(int);
void cancel_reservation(int, int, int);
void see_reservation();

//login page functions
bool login_page(int);
bool login_success(int, int, string, string);

// ticketer interface
int ticketer_interface();
void respond_ticketer_request(int);

// administrator functions
int admnistrator_interface();
void respond_admin_request(int);
void add_city();
void remove_city();
void show_all_reservation();
void massBusReservation_cancel();
void massDestReservation_cancel();
void cancelAll_reservation();
void generate_report();

// global variable
int resrv_counter = 0;
float total_payement_received = 0;

int main()
{
    // random_number generator
    random_generator(random1);
    random_generator(random2);

    // user-defined library functions
    bankInformation();
    destinationCity();

    //login_information container
    login_info();
    first_ui();
}

// Home page
int first_ui()
{
    system("cls");
    bool do_not_exit = true;
    while (do_not_exit)
    {
        cout << right << setw(10) << "Welcome to Bus X reservation system\n";
        cout << "[1] Enter as customer \n"
             << "[2] Login as Ticketer \n"
             << "[3] Login as Administrator \n";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            respond_cust_request();
            break;
        case 2:
            respond_ticketer_request(choice);
            break;
        case 3:
            respond_admin_request(choice);
            break;

        default:
            do_not_exit = false;
            break;
        }
    }
}

// homepage for customer
int cust_first_ui()
{
    //system("cls");
    cout << "Welcome to CompanyX Bus Reservation System \n"
         << "[1] Search destination\n"
         << "[2] Make Reservation \n"
         << "[3] See Your Reservation \n"
         << "[4] Create a new prepaid card \n"
         << "[5] Deposit to prepaid card\n"
         << "[press any number other than specified] to continue\n";

    int option;
    cin >> option;
    return option;
}

void respond_cust_request()
{
    bool do_not_exit = true;
    int option;
    while (do_not_exit)
    {
        option = cust_first_ui();

        switch (option)
        {
        case 1:
            search_destination();
            break;
        case 2:
            reserveSeat();
            break;
        case 3:
            see_reservation();
            break;
        case 4:
            create_prepaidAccount();
            break;
        case 5:
            deposit_prepaid();
            break;
        default:
                        system("cls");
            do_not_exit = false;
            break;
        }
    }
}

// searching destination
int search_destination()
{
    system("cls");
    cout << "Enter name of the city: ";
    string city_name;
    cin >> city_name;

    int city_index;
    bool found = false;

    for (int i = 0; i < cityNo_count; i++)
        // if the city the customer searches are on the destination name
        if (city_name == cities_info[i]->city_name)
        {
            city_index = i;
            found = true;
        }

    if (found)
    {
        cout << "Name: " << cities_info[city_index]->city_name << endl
             << "Distance from AA: " << cities_info[city_index]->km_from_AA << endl
             << "Direction from AA: " << cities_info[city_index]->direction << endl
             << "Leaving Time: ";
        for (int j = 0; j < 2; j++)
            cout << cities_info[city_index]->busDestInfo.leaving_time[j] << " ";

        bool cityExists = false;
        for (int i = 0; i < 2; i++)
            if (cities_info[city_index]->busDestInfo.seatAvailble[i] > 0)
                cityExists = true;

        cout << "\nAvailable: ";
        if (cityExists)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    else
        cout << "\n No such city found in our database\n";
}

// reserve seat
void reserveSeat()
{
    system("cls");
    // create a new reserve everytime this function is called
    resrvd_acc[resrv_counter] = new reserve;

    cout << "Enter FullName: ";
    string fname, lname;
    cin >> fname >> lname;
    resrvd_acc[resrv_counter]->fullName = fname + " " + lname;

    cout << "Enter your age: ";
    cin >> resrvd_acc[resrv_counter]->age;
    while (resrvd_acc[resrv_counter]->age < 18)
    {
        cout << "You are under Age: ";
        cin >> resrvd_acc[resrv_counter]->age;
    }
// travelling city information;
label:
    cout << "Choose starting Point: ";
    int startingPoint = travelling_city() - 1;
    cout << "Choose Destination City: ";
    int destination = travelling_city() - 1;
    resrvd_acc[resrv_counter]->dest_no = destination;

    // calculating distance between starting city and destination city;
    // checks whether customer enters the same name at both destination and starting city
    if (startingPoint != destination)
    {
        // assign a city to customer information
        resrvd_acc[resrv_counter]->destination = cities_info[destination]->city_name;
        resrvd_acc[resrv_counter]->initial_city = cities_info[startingPoint]->city_name;

        resrvd_acc[resrv_counter]->travelling_distance = distance_calculator(destination, startingPoint);
    }
    else
    {
        cout << "No inside service:Please enter again! \n";
        goto label;
    }

    cout << "Choose Travelling option \n"
         << "[1] One Way \n"
         << "[2] Round Trip: ";
    cin >> resrvd_acc[resrv_counter]->return_oneWay;
    cout << "Number of tickets: ";
    cin >> resrvd_acc[resrv_counter]->ticket_size;

    // asking a customer for time of reservation
    cout << "Leaving Time: \n";
    for (int i = 0; i < 2; i++)
    {
        cout << "[" << i + 1 << "] " << l_time[i] << endl;
    }
    int l_time_choice;
    cin >> l_time_choice;
    l_time_choice -= 1;

    // assigning bus to a customer
    // bus_assignment also checks if there's avaible seat
    bool bus_available = bus_assignment(destination, resrv_counter, resrvd_acc, (l_time_choice));
    if (bus_available)
    {
        // payement
        cout << "Choose payement method\n"
             << "[1] Prepaid\n"
             << "[2] Bank \n";
        int payement_method;
        cin >> payement_method;
        if (payement_method == 1)
            resrvd_acc[resrv_counter]->is_prepaid = true;
        else 
            resrvd_acc[resrv_counter]->is_prepaid = false;

        // Bank Account Information;
        cout << "Enter account: ";
        cin >> resrvd_acc[resrv_counter]->accountNumber;
        cout << "Enter security Code: ";
        cin >> resrvd_acc[resrv_counter]->securityNumber;

        // calculates total payement;
        float payement = payement_calculator(resrv_counter, resrvd_acc,
                                             resrvd_acc[resrv_counter]->is_prepaid);
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
            // if the customer have balance that allows him to reserve a seat success will be true.
            bool success = accountCheck(resrvd_acc[resrv_counter]->payement,
                                        resrvd_acc[resrv_counter]->accountNumber,
                                        resrvd_acc[resrv_counter]->securityNumber,
                                        resrvd_acc[resrv_counter]->is_prepaid, true);
            if (success)
            {
                resrvd_acc[resrv_counter]->resrvd_seat = (100 - bus_rg[destination]->seatAvailble[l_time_choice]);
                receipt(resrv_counter);
                resrvd_acc[resrv_counter]->is_reserverd = true;
                resrvd_acc[resrv_counter]->bus_code = l_time_choice;

                // recording payement information
                bus_rg[destination]->payement[l_time_choice] += payement;
                total_payement_received += payement;

                resrv_counter++;
            }
            else
            { /* if customer does provide accountNumber that does not exist, 
                    does not have enough balance in the account, and 
                    haven't not provided correct security code, cancel the reservation
                 */

                delete resrvd_acc[resrv_counter];
                cout << "Transaction was not successful \n"
                     << "Please check your bank information \n";
            }
        }
        else
        {
            // if the customer do not want to continue cancle reservation
            delete resrvd_acc[resrv_counter];
            cout << "Request canceled \n";
        }
    }
}

// distance calculator
float distance_calculator(int destination, int startingPoint)
{
    float distance_km;
    // if the two cities are on the same direction
    if (cities_info[destination]->direction == cities_info[startingPoint]->direction)
    {
        distance_km = cities_info[destination]->km_from_AA -
                      cities_info[startingPoint]->km_from_AA;
        distance_km = (distance_km < 0) ? ((-1) * distance_km) : distance_km;
    }
    else // if the two cities are on different direction;
    {
        cout << "Choose path: "
             << "[1] Through Addis Ababa \n"
             << "[2] Direct way \n";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
        {
            distance_km = (cities_info[destination]->km_from_AA +
                           cities_info[startingPoint]->km_from_AA);
            break;
        }
        case 2:
        {
            distance_km = sqrt(pow(cities_info[destination]->km_from_AA, 2) +
                               pow(cities_info[startingPoint]->km_from_AA, 2));
            break;
        }
        default:
            break;
        }
    }
    return distance_km;
}

// assignning bus to a customer;
bool bus_assignment(int d_num, int resrv_counter, reserve *resrvd_acc[], int &l_choice)
{
    int time_changed;
    bool seat_exist;

    if (bus_rg[d_num]->seatAvailble[l_choice] > 0)
        seat_exist = true;
    // if time customer request is not available
    else
    {
        time_changed = change_leaving_time(l_choice);
        if (time_changed != l_choice)
        {
            seat_exist = true;
            l_choice = time_changed;
        }
        else
            seat_exist = false;
    }

    if (seat_exist)
    {
        resrvd_acc[resrv_counter]->resrvd_bus = bus_rg[d_num]->bus_cd[l_choice];
        resrvd_acc[resrv_counter]->leaving_time = l_time[l_choice];
        bus_rg[d_num]->seatAvailble[l_choice]--;

        return true;
    }
    else
        return false;
}

// if bus is not available at requested time
int change_leaving_time(int l_choice)
{

    char change;
    int time_index;

    cout << "NO seat available at " << l_time[l_choice] << "\n";
    for (int i = 0; i < 2; i++)
        if ((i != l_choice) && (bus_rg[i]->seatAvailble > 0))
        {
            cout << "Would you like to change time to: " << l_time[i];
            time_index = i;
        }
    cout << (" y/n") << endl;

    cin >> change;
    change = tolower(change);

    // if the customer changes time return the time index;
    if (change == 'y')
    {
        return time_index;
    }
    else
        return l_choice;
}

// calculating payement;
float payement_calculator(int resrv_counter, reserve *resrvd_acc[], bool isPrepaid)
{
    float birr_per_km = 10;
    float discount_rate = 20 / 100.0;

    // prepaid card have discount
    if (isPrepaid)
        birr_per_km = birr_per_km - (birr_per_km * discount_rate);

    float payement = resrvd_acc[resrv_counter]->return_oneWay *
                     resrvd_acc[resrv_counter]->ticket_size *
                     resrvd_acc[resrv_counter]->travelling_distance * birr_per_km;
    return payement;
}

// confirm reservation
void confirm_resrv(int i)
{
    system("cls");
    cout << "Confirm Your Reservation\n\n";
    cout << "Name: " << resrvd_acc[i]->fullName << endl;
    cout << "Destination: " << resrvd_acc[i]->destination << endl;
    cout << "Bus code : " << resrvd_acc[i]->resrvd_bus << endl;
    cout << "Leaving time: " << resrvd_acc[i]->leaving_time << endl;
    cout << "Distance in km: " << resrvd_acc[i]->travelling_distance << endl;
    cout << "Total payment : " << resrvd_acc[i]->payement << endl;
}

void date_time()
{
    std::time_t t = std::time(0); // get time now
    std::tm *now = std::localtime(&t);
    std::cout << (now->tm_year + 1900) << '-'
              << (now->tm_mon + 1) << '-'
              << now->tm_mday
              << "\n";
}

// printing receipt after confirming the transaction;
void receipt(int resrv_counter)
{
    system("cls");
    cout << right << setw(50) << "Bus X Transport Service\n";
    cout << "Reciept \n";
    cout << "Seat Number: " << resrvd_acc[resrv_counter]->resrvd_seat << endl;
    cout << "Prepared for: " << resrvd_acc[resrv_counter]->fullName << endl;
    cout << "Travel Info: From " << resrvd_acc[resrv_counter]->initial_city 
         << " TO " << resrvd_acc[resrv_counter]->destination << endl;
    cout << "Leaving Time: " << resrvd_acc[resrv_counter]->leaving_time << endl;
    cout << "Date: ";
    date_time();

    cout << endl
         << endl;
    cout << "Description Quantity price/Quantity Total Price " << endl;
    cout << left << setw(10) << "Transport\t"
         << left << setw(10) << resrvd_acc[resrv_counter]->ticket_size << " "
         << left << setw(10) << resrvd_acc[resrv_counter]->travelling_distance / 10
         << left << setw(10) << resrvd_acc[resrv_counter]->payement << endl;
}

void see_reservation()
{
    system("cls");
    cout << "Enter FullName: ";
    string fname, lname, name;
    cin >> fname >> lname;
    name = fname + " " + lname;

    bool isFound = false;
    int index;
    for (int i = 0; i < resrv_counter; i++)
        if (name == resrvd_acc[i]->fullName)
        {
            isFound = true;
            index = i;
        }

    if (isFound)
    {
        receipt(index); // shows customer his reservation;

        cout << "[1] To cancel reservation \n"
             << "[2] To change reservation \n"
             << "[press any number other than specified] to continue \n";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cancel_reservation(index, resrvd_acc[index]->dest_no, resrvd_acc[index]->bus_code);
            cout << "Reservation canceled \n";
            break;
        case 2:
            modify_reservation(index);
            break;
        default:
            break;
        }
    }
    else
        cout << "No reservation under the name " << name << endl;
}

// cancel reservation: can be used to make  cancel all the reservation;
void cancel_reservation(int cust_index, int i, int j)
{
    //payback the money
    float payement = resrvd_acc[cust_index]->payement;
    bool isMoney_back = accountCheck(payement,
                                     resrvd_acc[cust_index]->accountNumber,
                                     resrvd_acc[cust_index]->securityNumber,
                                     resrvd_acc[cust_index]->is_prepaid, false);

    // deleting the reservation from system
    for (int i = cust_index; i < resrv_counter; i++)
    {
        resrvd_acc[i] = resrvd_acc[i + 1];
    }
    // rearranging bus seat number and payement;
    total_payement_received -= payement;
    bus_rg[i]->payement[j] -= payement;
    bus_rg[i]->seatAvailble[j]++;

    delete resrvd_acc[resrv_counter];
    resrvd_acc[resrv_counter] = NULL;
    resrv_counter--;
}

// modifying reservation
void modify_reservation(int cust_index)
{
    bool do_not_exit = true;
    while (do_not_exit)
    {
        cout << "You can change the following information in your booking \n"
             << "[1] Your name \n"
             << "[2] Leaving Time: \n"
             << "[3] To Finish\n"
             << "[press any number other than specified] To continue" << endl;
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            cout << "Enter your new name: ";
            string fname, lname;
            cin >> fname >> lname;
            resrvd_acc[cust_index]->fullName = fname + " " + lname;
            cout << "Name changed successfuly \n";
            break;
        }
        case 2:
        {
            cout << "Leaving Time: \n";
            for (int i = 0; i < 2; i++)
                cout << "[" << i + 1 << "] " << l_time[i] << endl;
            int l_time_choice;
            cin >> l_time_choice;

            // Not the best way to do it, but for now
            resrvd_acc[cust_index]->leaving_time = l_time[l_time_choice - 1];
            cout << "Leaving time is changed successfuly \n";
            break;
        }
        case 3:
            receipt(cust_index);
            break;
        default:
                            system("cls");
            do_not_exit = false;
            break;
        }
    }
}

// second section of the project

// login page for ticketer and administrator
bool login_page(int i)
{
    system("cls");
    bool status;
    string password, id;
    cout << setw(10) << "Enter your Login information below\n";
    cout << "Both ID and password are case sensitive \n";
    cout << "ID NO: ";
    cin >> id;
    cout << "password: ";
    cin >> password;

    switch (i)
    {
    case 2:
        status = login_success(0, num_access, id, password);
        break;
    case 3:
        status = login_success(0, 1, id, password);
        break;
    default:
        status = false;
        break;
    }
    return status;
}

// confirms login credentials
bool login_success(int start, int end, string id, string password)
{
    bool login_success = false;
    for (int i = start; i < end; i++)
        if ((id == login_create[i]->id) && (password == login_create[i]->password))
            login_success = true;

    return login_success;
}

// ticketer page
int ticketer_interface()
{
    cout << "Welcome to CompanyX Bus Reservation System \n"
         << "[1] Reserve for customer\n"
         << "[2] Show All cities and Buses Assigned \n"
         << "[3] Show All Major Buses Information \n"
         << "[press any number other than specified] To continue\n";

    int option;
    cin >> option;
    return option;
}

void respond_ticketer_request(int index)
{
    if (login_page(index))
    {
        bool do_not_exit = true;
        int option;
        while (do_not_exit)
        {
            option = ticketer_interface();

            switch (option)
            {
            case 1:
                respond_cust_request();
                break;
            case 2:
                list_cities(cities_info);
                break;
            case 3:
                showBusInfo();
                break;
            case 4:
                first_ui();
                break;
            default:
                system("cls");
                do_not_exit = false;
                break;
            }
        }
    }
    else
        cout << "Incorrect login information \n";
}

// administrator first user interfaces
int administrator_interface()
{
    cout << "Welcome Mr. Admisnistrator \n"
         << "[1] To add city to lists \n"
         << "[2] To remove city from lists \n"
         << "[3] show all reservations \n"
         << "[4] To Grant a Ticketer priveledges \n"
         << "[5] Mass reservation cancelling \n"
         << "[6] Generate Report \n"
         << "[press any number other than specified] to continue \n";

    int response;
    cin >> response;
    return response;
}

// functional response to administrator requests
void respond_admin_request(int index)
{
    if (login_page(index))
    {
        bool do_not_exit = true;
        while (do_not_exit)
        {
            int response = administrator_interface();
            switch (response)
            {
            case 1:
                add_city();
                break;
            case 2:
                remove_city();
                break;
            case 3:
                show_all_reservation();
                break;
            case 4:
                create_ticketer_login();
                break;
            case 5:
                cancelAll_reservation();
                break;
            case 6:
                generate_report();
                break;
            default:
                system("cls");
                do_not_exit = false;
                break;
            }
        }
    }
    else
        cout << "Incorrect Login information \n";
}

void show_all_reservation()
{
    system("cls");
    cout << "Total Number of resrvation: " << resrv_counter << endl;
    cout << " Full Name   \t| Initial | Destination | "
         << "Bus Assigned | seatNumber | Leaving Time | Distance | payement\n";
    cout << setprecision(1) << fixed;
    for (int i = 0; i < resrv_counter; i++)
    {
        if (resrvd_acc[i] != NULL)
        {
            cout << " " << left << setw(5) << resrvd_acc[i]->fullName << right << setw(10)
                 << resrvd_acc[i]->initial_city << right << setw(15)
                 << resrvd_acc[i]->destination << right << setw(12)
                 << resrvd_acc[i]->resrvd_bus << right << setw(12)
                 << resrvd_acc[i]->resrvd_seat << right << setw(18)
                 << resrvd_acc[i]->leaving_time << right << setw(10)
                 << resrvd_acc[i]->travelling_distance << right << setw(10)
                 << resrvd_acc[i]->payement << endl;
        }
    }
}

void cancelAll_reservation()
{
    system("cls");
    bool do_not_exit = true;
    while (do_not_exit)
    {
        cout << "[1] To all reservation to destination\n"
             << "[2] To cancel specific buses reservation to destination\n"
             << "[press any number other than specified] to exit from current page \n";

        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            massDestReservation_cancel();
            break;
        case 2:
            massBusReservation_cancel();
            break;
        default:
            do_not_exit = false;
            break;
        }
    }
}

// mass bus reservation cancelling
void massBusReservation_cancel()
{
    cout << "Enter bus code: ";
    string bus_code;
    cin >> bus_code;

    bool is_canceled = false;
    for (int i = 0; i < resrv_counter; i++)
        if (resrvd_acc[i]->resrvd_bus == bus_code)
        {
            cancel_reservation(i, resrvd_acc[i]->dest_no, resrvd_acc[i]->bus_code);
            is_canceled = true;
        }

    if (is_canceled)
        cout << "All reservation have been canceled succesfully!\n";
    else
        cout << "Operation was not successful, check name/bus code again!\n";
}

// mass destination reservation cancelling
void massDestReservation_cancel()
{
    cout << "Enter a destination name: ";
    string destinationName;
    cin >> destinationName;

    bool is_canceled = false;
    for (int i = 0; i < resrv_counter; i++)
        if (resrvd_acc[i]->destination == destinationName)
        {
            cancel_reservation(i, resrvd_acc[i]->dest_no, resrvd_acc[i]->bus_code);
            is_canceled = true;
        }

    if (is_canceled)
        cout << "All reservation have been canceled succesfully!\n";
    else
        cout << "Operation was not successful, check name/bus code again!\n";
}

void generate_report()
{
    system("cls");
    cout << "Date: ";
    date_time();
    cout << "Bus Code | payement Received | Seat Reserved" << endl;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
        {
            cout << " " << bus_rg[i]->bus_cd[j] << right << setw(15);
            if (bus_rg[i]->seatAvailble[j] < 100)
            {
                cout << bus_rg[i]->payement[j] << right << setw(15)
                     << (100 - bus_rg[i]->seatAvailble[j]) << endl;
            }
            else
                cout << "None" << right << setw(15)
                     << "0" << endl;
        }

    cout << "Total reservation made: " << resrv_counter << endl;
    cout << "Total Payement Received: " << total_payement_received << endl;
}
