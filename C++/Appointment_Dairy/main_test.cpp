#include "Calendar_t.h"
#include "Meeting_t.h"
#include <iostream>
#include <string>

using namespace std;

void testCalendar();
void insertMeeting(Calendar_t* calendar);
void removeMeeting(Calendar_t* calendar);
void findMeeting(Calendar_t* calendar);
void printMenu();

int main()
{
    testCalendar();
    return 0;
}

void testCalendar()
{
    unsigned int option;
    bool cont = true;
    Calendar_t calendar;

    while (cont)
    {
        printMenu();
        cin >> option;
        switch(option)
        {
        case 1:
            insertMeeting(&calendar);
            break;
        case 2:
            removeMeeting(&calendar);
            break;
        case 3:
            findMeeting(&calendar);
            break;
        case 4:
            calendar.print();
            break;
        default:
            cont = false;
            break;
        }
    }
    calendar.clean();
}

void insertMeeting(Calendar_t* calendar)
{
    float begin, end;
    string subject;
    Meeting_t* meeting;

    cout << "Enter begin hour, end hour and subject of meeting:" << endl;
    cin >> begin >> end >> subject;

    meeting = calendar->createMeeting(begin, end, subject);
    if(meeting != 0)
    {
        cout << endl << "New meeting has been created" << endl;
    }
    else
    {
        cout << endl << "Meeting creation failed" << endl << endl;
        return;
    }

    if(calendar->insertMeeting(meeting))
    {
        cout << "Meeting successfully inserted" << endl << endl;
    }
    else
    {
        cout << "Meeting insertion failed" << endl << endl;
    }
}

void removeMeeting(Calendar_t* calendar)
{
    float begin;
    cout << "Enter begin hour of meeting that you want to remove:" << endl;
    cin >> begin;

    if(calendar->removeMeeting(begin))
    {
        cout << endl << "Meeting successfully removed" << endl << endl;
    }
    else
    {
        cout << endl << "There is no such meeting" << endl << endl;
    }
}

void findMeeting(Calendar_t* calendar)
{
    float begin;
    cout << "Enter begin hour of meeting that you want to find:" << endl;
    cin >> begin;
    Meeting_t* meeting = calendar->findMeeting(begin);

    if(meeting != 0)
    {
        cout <<  endl << "Meeting begin hour: "  << meeting->getBegin()      << endl
                      << "        end hour: "    << meeting->getEnd()        << endl
                      << "        subject: "     << meeting->getSubject()    << endl << endl;
    }
    else
    {
        cout << endl << "There is no such meeting" << endl << endl;
    }
}

void printMenu()
{
    cout << "Choose option:"            << endl
         << "1: Insert meeting"         << endl
         << "2: Remove meeting"         << endl
         << "3: Find meeting"           << endl
         << "4: Print calendar"         << endl
         << "Any another number - stop" << endl;
}