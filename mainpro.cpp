#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Patient {
    int id, age;
    string name, disease, date, time, priority, status;
};


string getPriority(string disease) {
    ifstream file("diseases.txt");
    string line;

    while (getline(file, line)) {

        int pos = line.find_last_of(' ');
        string d = line.substr(0, pos);       
        string p = line.substr(pos + 1);   

        if (d == disease) {
            return p;  
        }
    }

    return "Unknown"; 
}

bool isValidDate(const string& date) {
    if (date.length() != 10) return false; 
    if (date[2] != '-' || date[5] != '-') return false;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int maxDay = 31;
    if (month == 2) maxDay = 28; 
    else if (month == 4 || month == 6 || month == 9 || month == 11) maxDay = 30;

    if (day < 1 || day > maxDay) return false;

    return true;
}


bool isValidTime(const string& time) {
    if (time.length() != 8) return false; 
    if (time[2] != ':' || time[5] != ':') return false;

    int hh = stoi(time.substr(0, 2));
    int mm = stoi(time.substr(3, 2));
    int ss = stoi(time.substr(6, 2));

    if (hh < 0 || hh > 23) return false;
    if (mm < 0 || mm > 59) return false;
    if (ss < 0 || ss > 59) return false;

    return true;
}



void registerPatient() {
    Patient p;

    cout << "\nEnter Patient ID: ";
    cin >> p.id;
    cin.ignore();

    // Check if ID already exists
    ifstream fin("patients.txt");
    string line;
    bool exists = false;
    while (getline(fin, line)) {
        stringstream ss(line);
        string id_str;
        getline(ss, id_str, '|');
        if (stoi(id_str) == p.id) {
            exists = true;
            break;
        }
    }
    fin.close();

    if (exists) {
        cout << " Patient ID already exists! Registration cancelled.\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, p.name);

    cout << "Enter Age: ";
    cin >> p.age; cin.ignore();

    cout << "Enter Disease: ";
    getline(cin, p.disease);

    cout << "Enter Date (DD-MM-YYYY): ";
    getline(cin, p.date);
    if (!isValidDate(p.date)) {
        cout << " Invalid date Registration cancelled.\n";
        return;
    }
    
    cout << "Enter Time (HH:MM:SS): ";
    getline(cin, p.time);
    if (!isValidTime(p.time)) {
        cout << "Invalid time Registration cancelled.\n";
        return;
    }

    p.priority = getPriority(p.disease);
    p.status = "Admitted";

    ofstream fout("patients.txt", ios::app);
    fout << p.id << "|" << p.name << "|" << p.age << "|" << p.disease << "|"
         << p.date << "|" << p.time << "|" << p.priority << "|" << p.status << endl;
    fout.close();

    cout << "\n Patient Registered Successfully!\n";
}






void viewQueue() {
    ifstream f("patients.txt");
    if (!f) {
        cout << "No patient record found!\n";
        return;
    }

    Patient patients[100];
    int count = 0;
    string line;

    // Read each patient line
    while (getline(f, line)) {
        stringstream ss(line);
        string id_str, age_str;

        getline(ss, id_str, '|'); patients[count].id = stoi(id_str);
        getline(ss, patients[count].name, '|');
        getline(ss, age_str, '|'); patients[count].age = stoi(age_str);
        getline(ss, patients[count].disease, '|');
        getline(ss, patients[count].date, '|');
        getline(ss, patients[count].time, '|');
        getline(ss, patients[count].priority, '|');
        getline(ss, patients[count].status, '|');

        if (patients[count].status == "Admitted") {
            count++;
        }
    }
    f.close();

    // Sort by priority (High > Medium > Low) and then by time
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int pri1 = (patients[i].priority == "High") ? 3 :
                       (patients[i].priority == "Medium") ? 2 : 1;
            int pri2 = (patients[j].priority == "High") ? 3 :
                       (patients[j].priority == "Medium") ? 2 : 1;

            if (pri1 < pri2 || (pri1 == pri2 && patients[i].time > patients[j].time)) {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }

    // Display patients
    cout << "\nID\tName\tAge\tDisease\tDate\t\tTime\t\tPriority\tStatus\n";
    cout << "---------------------------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << patients[i].id << "\t" 
             << patients[i].name << "\t" 
             << patients[i].age << "\t" 
             << patients[i].disease << "\t" 
             << patients[i].date << "\t" 
             << patients[i].time << "\t" 
             << patients[i].priority << "\t\t" 
             << patients[i].status << endl;
    }
}


void updatePatient() {
    ifstream fin("patients.txt");
    ofstream fout("temp.txt");

    if (!fin) {
        cout << "No patient record found!\n";
        return;
    }

    int searchId;
    cout << "Enter Patient ID to update: ";
    cin >> searchId;
    cin.ignore();  // clear input buffer

    Patient p;
    bool found = false;
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        string id_str, age_str;

        getline(ss, id_str, '|'); p.id = stoi(id_str);
        getline(ss, p.name, '|');
        getline(ss, age_str, '|'); p.age = stoi(age_str);
        getline(ss, p.disease, '|');
        getline(ss, p.date, '|');
        getline(ss, p.time, '|');
        getline(ss, p.priority, '|');
        getline(ss, p.status, '|');

        if (p.id == searchId) {
            found = true;
            cout << "\nPatient found!\n";
            cout << "1. Name: " << p.name << "\n2. Age: " << p.age
                 << "\n3. Disease: " << p.disease << "\n4. Date: " << p.date
                 << "\n5. Time: " << p.time << "\n6. Status: " << p.status << endl;

            char choice;
            cout << "\nDo you want to update all details? (y/n): ";
            cin >> choice;
            cin.ignore();

            if (choice == 'y' || choice == 'Y') {
                cout << "Enter New Name: "; getline(cin, p.name);
                cout << "Enter New Age: "; cin >> p.age; cin.ignore();
                cout << "Enter New Disease: "; getline(cin, p.disease);
                cout << "Enter New Date (DD-MM-YYYY): "; getline(cin, p.date);
                cout << "Enter New Time (HH:MM:SS): "; getline(cin, p.time);
                cout << "Enter Status (Admitted/Discharged): "; getline(cin, p.status);
                p.priority = getPriority(p.disease);
            } else {
                int opt;
                do {
                    cout << "\nSelect field to update (0 to finish):\n";
                    cout << "1. Name\n2. Age\n3. Disease\n4. Date\n5. Time\n6. Status\nChoice: ";
                    cin >> opt;
                    cin.ignore(); // clear buffer
                    switch(opt) {
                        case 1: cout << "Enter New Name: "; getline(cin, p.name); break;
                        case 2: cout << "Enter New Age: "; cin >> p.age; cin.ignore(); break;
                        case 3: cout << "Enter New Disease: "; getline(cin, p.disease); p.priority = getPriority(p.disease); break;
                        case 4: cout << "Enter New Date: "; getline(cin, p.date); break;
                        case 5: cout << "Enter New Time: "; getline(cin, p.time); break;
                        case 6: cout << "Enter Status (Admitted/Discharged): "; getline(cin, p.status); break;
                        case 0: break;
                        default: cout << "Invalid option!\n";
                    }
                } while(opt != 0);
            }

            cout << "\n✅ Patient details updated!\n";
        }

        // Write patient to temp file
        fout << p.id << "|" << p.name << "|" << p.age << "|" << p.disease << "|"
             << p.date << "|" << p.time << "|" << p.priority << "|" << p.status << endl;
    }

    fin.close();
    fout.close();

    remove("patients.txt");
    rename("temp.txt","patients.txt");

    if (!found) cout << "Patient not found!\n";
}



void dischargePatient() {
    ifstream fin("patients.txt");
    ofstream fout("temp.txt");
    if(!fin){ cout << "No patient record found!\n"; return; }

    int dischargeId;
    cout << "Enter Patient ID to discharge: ";
    cin >> dischargeId; cin.ignore();

    Patient p;
    bool found=false;
    string line;

    while(getline(fin,line)){
        stringstream ss(line);
        string id_str, age_str;

        getline(ss, id_str,'|'); p.id=stoi(id_str);
        getline(ss, p.name,'|');
        getline(ss, age_str,'|'); p.age=stoi(age_str);
        getline(ss, p.disease,'|');
        getline(ss, p.date,'|');
        getline(ss, p.time,'|');
        getline(ss, p.priority,'|');
        getline(ss, p.status,'|');

        if(p.id==dischargeId){
            p.status="Discharged";
            cout << "Patient " << p.name << " discharged successfully!\n";
            found=true;
        }

        fout << p.id << "|" << p.name << "|" << p.age << "|" << p.disease << "|"
             << p.date << "|" << p.time << "|" << p.priority << "|" << p.status << endl;
    }

    fin.close();
    fout.close();
    remove("patients.txt");
    rename("temp.txt","patients.txt");

    if(!found) cout << "Patient not found!\n";
}


int main() {
    int choice;
    do {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Register Patient\n";
        cout << "2. View Patient Queue\n";
        cout << "3. Update Patient Details\n";
        cout << "4. Discharge Patient\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: registerPatient(); break;
            case 2: viewQueue(); break;
            case 3: updatePatient(); break;
            case 4: dischargePatient(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while(choice != 5);

    return 0;
}
