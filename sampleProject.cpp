#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void addStudent();
void showStudents();
int getNextStudentId();
void oneStudent();

struct info
{
    int id;
    string rollNo;
    string name;
    string phone;
    string address;
    vector<string> courses; // for flexibility
};

int main()
{
    
    oneStudent();

    return 0;
}

void addStudent()
{
    ofstream data("studentInfo.csv", ios::app); // open file in append mode so it doesnt overwrite

    int choice;

    // is_open() --> a function to check if file is open or not
    if (!data.is_open())
    {
        cout << "Error: Couldn't open file for writing  " << endl;
        return;
    }

    do
    {
        info s1;
        cout << endl
             << "------Enter student info-----" << endl;
        s1.id = getNextStudentId();
        cout << "Assigned Student ID: " << s1.id << endl;

        cout << "Enter Student Roll No: ";
        getline(cin, s1.rollNo);

        cout << "Enter Student Name: ";
        getline(cin, s1.name);

        cout << "Enter Student Phone: ";
        getline(cin, s1.phone);

        cout << "Enter Student Address: ";
        getline(cin, s1.address);

        cout << "Enter Student Courses (Enter done to stop adding courses): ";
        while (true)
        {
            string courses;
            getline(cin, courses);
            if (courses == "done")
            {
                break;
            }
            s1.courses.push_back(courses);
        }

        // 5 --> 4, 1
        data << s1.id << "," << s1.rollNo << "," << s1.name << "," << s1.phone << "," << s1.address << ",";
        for (int i = 0; i < s1.courses.size(); i++)
        {
            if (i < (s1.courses.size() - 1))
            {
                data << s1.courses[i] << ";";
            }
            else
                data << s1.courses[i];
        }

        data << "\n";
        cout << "Student added succesfully! " << endl;

        cout << "Want to add another student? (Type 0 to exit) : ";
        cin >> choice;
        cin.ignore();
    } while (choice != 0);

    data.close();
}

int getNextStudentId()
{
    ifstream data("studentInfo.csv");
    string line;
    int lastId = 0;

    if (!data.is_open())
        return 1; // start from 1 if file doesn't exist

    getline(data, line); // skip header row

    while (getline(data, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ','); // first column = Student_ID
        if (!idStr.empty())
            lastId = stoi(idStr);
    }

    return lastId + 1;
}

void showStudents()
{
    ifstream data("studentInfo.csv");
    string line;

    if (!data.is_open())
    {
        cout << "Error: Can't open file ";
        return;
    }

    // Skip header row
    getline(data, line);

    while (getline(data, line))
    {
        stringstream ss(line);
        info s1;

        string idStr;
        getline(ss, idStr, ',');
        s1.id = stoi(idStr);
        getline(ss, s1.rollNo, ',');
        getline(ss, s1.name, ',');
        getline(ss, s1.phone, ',');
        getline(ss, s1.address, ',');

        string coursesField;
        getline(ss, coursesField, ','); // all courses in one cell

        stringstream cs(coursesField);
        string course;
        while (getline(cs, course, ';'))
        {
            s1.courses.push_back(course);
        }

        cout << endl
             << "Student ID is : " << s1.id << endl;
        cout << "Student Roll no is : " << s1.rollNo << endl;
        cout << "Student name is : " << s1.name << endl;
        cout << "Student Phone is : " << s1.phone << endl;
        cout << "Student Address is : " << s1.address << endl;
        cout << "Student Courses are : ";
        for (int i = 0; i < s1.courses.size(); ++i)
        {
            cout << s1.courses[i] << " ";
        }
        cout << endl;
    }

    cout << "\n No more students.\n";
    data.close();
}

void oneStudent()
{
    bool found= false;
    string name, rollNo;
    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter student roll No: ";
    getline(cin, rollNo);

    ifstream data("studentInfo.csv");
    string line;
    getline(data, line);

    while (getline(data, line))
    {
        stringstream ss(line);
        info s1;
        

        string idStr;
        getline(ss, idStr, ',');
        s1.id = stoi(idStr);
        getline(ss, s1.rollNo, ',');
        getline(ss, s1.name, ',');
        getline(ss, s1.phone, ',');
        getline(ss, s1.address, ',');

        string coursesField;
        getline(ss, coursesField, ','); // all courses in one cell

        stringstream cs(coursesField);
        string course;
        while (getline(cs, course, ';')) // Hajra Ishfaq // 25021519-123
        {
            s1.courses.push_back(course);
        }

        if ((s1.rollNo==rollNo) && (s1.name== name))
        {
            found= true;
            cout<< endl<< "Student Found"<< endl;
            cout << endl
                 << "Student ID is : " << s1.id << endl;
            cout << "Student Roll no is : " << s1.rollNo << endl;
            cout << "Student name is : " << s1.name << endl;
            cout << "Student Phone is : " << s1.phone << endl;
            cout << "Student Address is : " << s1.address << endl;
            cout << "Student Courses are : ";
            for (int i = 0; i < s1.courses.size(); ++i)
            {
                cout << s1.courses[i] << " ";
            }
            cout << endl;
        }
    }
    if(found== false)
    {
        cout<< endl<< "Student doesn't exists." ;
    }
    data.close();
}