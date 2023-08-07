#include <iostream>
#include <algorithm>
using namespace std;

class institution;
void AdminLoginPanel(institution &);
void admissionPanel(institution &);
void studentLoginPanel(institution &, int);

class accountinformation {
protected:
    string name, email, pass;
    int ID;
public:
    accountinformation(){};
    void show() {
        cout << "Name: " << name << "\n";
        cout << "Email: " << email << "\n";
        cout << "Password: " << pass << "\n";
        cout << "ID: " << ID << "\n";
    }
    friend void studentLoginPage(institution &);
    friend class adminLoginClass;
};

class studentInformation : public accountinformation{
    string father_name, alocated_dept;
    int merit_pos;
    string choiceList[15];
    int numberofchoice;
    bool givendept;
public:
    studentInformation(){
        numberofchoice = 0;
        givendept = false;
        alocated_dept = "Not Allocated";
    };
    void show() {
        cout << "Name: " << name << "\n";
        cout << "Father Name: " << father_name << "\n";
        cout << "Email: " << email << "\n";
        cout << "Password: " << pass << "\n";
        cout << "ID: " << ID << "\n";
        cout << "Merit Position: " << merit_pos << "\n";
        cout << "Allocated Department: " << alocated_dept << "\n";
    }
    bool operator < (studentInformation &stu) {
        return (merit_pos < stu.merit_pos);
    }
    void checkDept() {
        if(givendept) cout << "Congratulations! you have been Allocated to the department " << alocated_dept << "\n";
        else cout << "Alas! You are not Allocated any department.\n";
    }
    friend class studentDatabse;
    friend class studentLoginClass;
    friend void subjectChoice(institution &, int);
    friend void setSubject(institution &);
};

class studentDatabse {
    studentInformation selectedstudentarr[100];
    int numberofstudent;
public:
    studentDatabse() {
        numberofstudent = 0;
    }
    void addSelectedStudent() {
        cout << "Enter how many student do want to input? \n";
        int cnt; cin >> cnt;
        for(int i = 1; i <= cnt; i++) {
            cout << "Enter Information for Student " << i << "\n";
            cout << "Enter Student Name: \n";
            cin >> selectedstudentarr[numberofstudent].name;
            cout << "Enter Student Father Name: \n";
            cin >> selectedstudentarr[numberofstudent].father_name;
            cout << "Enter Student Email: \n";
            cin >> selectedstudentarr[numberofstudent].email;
            cout << "Enter Student Merit Position: \n";
            cin >> selectedstudentarr[numberofstudent].merit_pos;
            cout << "Enter Student ID for Login: \n";
            cin >> selectedstudentarr[numberofstudent].ID;
            cout << "Enter Student Account Password: \n";
            cin >> selectedstudentarr[numberofstudent].pass;
            numberofstudent++;
            cout << "Student Added successfully \n";
        }
        sort(selectedstudentarr, selectedstudentarr + numberofstudent);
    }
    void login(string email, string pass, institution &ins) {
        bool flag = false;
        for(int i = 0; i < numberofstudent; i++) {
            if(selectedstudentarr[i].email == email && selectedstudentarr[i].pass == pass) {
                flag = true;
                studentLoginPanel(ins, i);
            }
        }
        if(!flag) {
            cout << "Student Not Found.\n";
        }
    }
    friend class institution;
    friend void studentLoginPage(institution &);
    friend void subjectChoice(institution &, int);
    friend void setSubject(institution &);
    friend void studentLoginPanel(institution &, int);
};

class adminLoginClass {
    accountinformation adminarr[100];
    int numofadmin;
public:
    adminLoginClass(){
        numofadmin = 0;
    };
    void registerAdmin() {
        cout << "Enter your name: \n";
        cin >> adminarr[numofadmin].name;
        cout << "Enter your Email: \n";
        cin >> adminarr[numofadmin].email;
        cout << "Enter your Password: \n";
        cin >> adminarr[numofadmin].pass;
        cout << "Enter your ID: \n";
        cin >> adminarr[numofadmin].ID;
        numofadmin++;
    }
    void loginAdmin(string email, string pass, institution &ins) {
        bool flag = false;
        for(int i = 0; i < numofadmin; i++) {
            if(adminarr[i].email == email && adminarr[i].pass == pass) {
                flag = true;
                AdminLoginPanel(ins);
            }
        }
        if(!flag) {
            cout << "Admin User Not Found!\n";
        }
    }
};

class depertmentClass
{
    string name;
    int numofseat;
    int numberofstudent;
    int numberofallocatedseat;
public:
    depertmentClass(){
        numofseat = 0;
        numberofstudent = 0;
        numberofallocatedseat = 0;
    }
    depertmentClass(string s, int n) {
        name = s;
        numofseat = n;
        numberofallocatedseat = n;
    }
    friend class institution;
    friend void subjectChoice(institution &, int);
    friend void setSubject(institution &);
};

class institution
{
    string name;
    adminLoginClass adminarr;
    studentDatabse studentdata1;
    depertmentClass deptarr[15];
    int numofdept;
public:
    institution(){
        numofdept = 0;
    };
    void addInstitutionName() {
        cout << "Enter Your institution Name \n";
        cin >> name;
    }
    void addDept() {
        cout << "How many Department do you have in your varsity? \n";
        cout << "MAX LIMIT 15 \n";
        int n, nofseat; cin >> n;
        string dname;
        for(int i = 1; i <= n; i++) {
            cout << "Enter information of Department NO: " << i << "\n";
            cout << "Enter Name: \n";
            cin >> dname;
            cout << "Enter number of seat in : " << deptarr[numofdept].name << " \n";
            cin >> nofseat;
            depertmentClass *newdept = new depertmentClass(dname, nofseat);
            deptarr[numofdept] = *newdept;
            numofdept++;
            delete newdept;
        }
    }
    void show() {
        cout << "Number of Department: " << numofdept << "\n";
        for(int i = 0; i < numofdept; i++) {
            cout << "Department of " << deptarr[i].name << "\n";
        }
        int *sum = new int(0);
        for(int i = 0; i < numofdept; i++) {
            *sum += deptarr[i].numberofallocatedseat;
        }
        cout << "Number of Total Seat: " << *sum << "\n";
        delete sum;
        for(int i = 0; i < numofdept; i++) {
            cout << "Department of " << deptarr[i].name << " has " << deptarr[i].numberofallocatedseat << " Seat.\n";
        }
        cout << "Number of Total Student: " << studentdata1.numberofstudent << "\n";
    }
    string getname() {
        return name;
    }
    friend class studentDatabse;
    friend void adminLoginPage(institution &);
    friend void AdminLoginPanel(institution &);
    friend void studentLoginPage(institution &);
    friend void subjectChoice(institution &, int);
    friend void setSubject(institution &);
    friend void studentLoginPanel(institution &, int);
};

void setSubject(institution &ins) {
    for(int i = 0; i < ins.studentdata1.numberofstudent; i++) {
        for(int j = 0; j < ins.studentdata1.selectedstudentarr[i].numberofchoice; j++) {
            string deptName = ins.studentdata1.selectedstudentarr[i].choiceList[j];
            bool flag = false;
            if(ins.studentdata1.selectedstudentarr[i].givendept) continue;
            for(int k = 0; k < ins.numofdept; k++) {
                if(ins.deptarr[k].name == deptName && ins.deptarr[k].numofseat > 0) {
                    ins.studentdata1.selectedstudentarr[i].alocated_dept = deptName;
                    ins.deptarr[k].numofseat--;
                    ins.deptarr[k].numberofstudent++;
                    flag = true;
                    ins.studentdata1.selectedstudentarr[i].givendept = true;
                    break;
                }
            }
            if(flag) break;
        }
    }
}

void subjectChoice(institution &ins, int pos) {
    cout << "You can apply for following Department.\n";
    for(int i = 0; i < ins.numofdept; i++) {
        cout << i+1 << ". Department of " << ins.deptarr[i].name << "\n";
    }
    for(int i = 0; i < ins.numofdept; i++) {
        cout << "Enter your choice no: " << i + 1 << "\n";
        cin >> ins.studentdata1.selectedstudentarr[pos].choiceList[i];
        ins.studentdata1.selectedstudentarr[pos].numberofchoice++;
        cout << " Do you want to add more choice? [Y/N]\n";
        char ch; cin >> ch;
        if(ch == 'N') break;
    }
}

void AdminLoginPanel(institution &ins)
{
    int op;
    char ch;
    do
    {

        cout<<"                       Welcome to Admin Panel"<<endl;
        cout<<"                       ____________________"<<endl;
        cout<<"                       1. input student list"<<endl;
        cout<<"                       2. show institution information"<<endl;
        cout<<"                       3. Go to HomePage"<<endl;
        cout<<"Select your option:";
        cin>>op;
        switch(op) {
            case 1:
            {
                ins.studentdata1.addSelectedStudent();
                break;
            }
            case 2:
            {
                ins.show();
                break;
            }
            case 3: {
                admissionPanel(ins);
                break;
            }
        }
        cout<<"Go to Admin Panel?[Y/N]"<<endl;
        cin>>ch;
    }
    while(ch=='Y');
    admissionPanel(ins);
}

void studentLoginPanel(institution &ins, int pos)
{
    int op;
    char ch;
    do
    {

        cout<<"                       Welcome to Student Panel"<<endl;
        cout<<"                       ____________________"<<endl;
        cout<<"                       1. Subject Choice"<<endl;
        cout<<"                       2. Departmental result"<<endl;
        cout<<"                       3. Show details information"<<endl;
        cout<<"                       4. Go to HomePage"<<endl;
        cout<<"Select your option:";
        cin>>op;
        switch(op) {
            case 1:
            {
                subjectChoice(ins, pos);
                setSubject(ins);
                break;
            }
            case 2:
            {
                ins.studentdata1.selectedstudentarr[pos].checkDept();
                break;
            }
            case 3:
            {
                ins.studentdata1.selectedstudentarr[pos].show();
                break;
            }
            case 4: {
                admissionPanel(ins);
                break;
            }
        }
        cout<<"Go to the Student Panel?[Y/N]"<<endl;
        cin>>ch;
    }
    while(ch=='Y');
    admissionPanel(ins);
}

void adminLoginPage(institution &ins) {
    char option_for_login,option_for_registration;
    cout<<"\t\tAdmin login page"<< endl;
    cout<<"\t\t-----------------"<<endl;
    cout<<"Do you already have an account ?[Y/N]"<<endl<<endl;
    cout<<"Select your option:";
    cin>>option_for_login;
    if(option_for_login=='Y')
    {
        string em, pass;
        cout << "Enter Your Email: \n";
        cin >> em;
        cout << "Enter Your Password: \n";
        cin >> pass;
        ins.adminarr.loginAdmin(em, pass, ins);
    }
    else if(option_for_login=='N')
    {
        cout<<endl<<"Please register and then login !"<<endl;
        cout<<endl;
        cout<<"Do you  want to register?[Y/N]"<<endl<<endl;
        cout<<"Select your option:";
        cin>>option_for_registration;
        if(option_for_registration=='Y')
        {
            ins.adminarr.registerAdmin();
        }
        else if(option_for_registration=='N')
        {
            cout<<endl<<"Thank you for using Kuet Admission Panel !"<<endl;
        }
    }
}

void studentLoginPage(institution &ins) {
    char option_for_login,option_for_registration;
    cout<<"\t\tStudent login page"<< endl;
    cout<<"\t\t-----------------"<<endl;
    cout<<"Enter Your Login ID \n";
    int id;
    cin >> id;
    int pos = -1;
    for(int i = 0; i < ins.studentdata1.numberofstudent; i++) {
        if(ins.studentdata1.selectedstudentarr[i].ID) {
            pos = i;
            break;
        }
    }
    if(pos != -1) {
        string em, pass;
        cout << "Enter Your Email: \n";
        cin >> em;
        cout << "Enter Your Password: \n";
        cin >> pass;
        ins.studentdata1.login(em, pass, ins);
    }
    else {
        cout << "Alas! You are not selected!\n";
    }
}

void admissionPanel(institution &ins) {
    int option;
    char p;
    do
    {
        cout<<"                       WELCOME TO " << ins.getname() << " ADMISSION PANEL"<<endl;
        cout<<"                     ----------------------------------"<<endl;
        cout<<"                                1. Admin Login"<<endl;
        cout<<"                                2. Student Login"<<endl;
        cout<<"                                3. Exit"<<endl;
        cout<<"select your option:";
        cin>>option;

        switch(option)
        {
            case 1:
            {
                adminLoginPage(ins);
                break;
            }
            case 2:
            {
                studentLoginPage(ins);
            }
            case 3:
            {
                exit(0);
            }
        }
        cout<<"do you want to go back to the homepage[Y/N]?"<<endl;
        cin>>p;
    }
    while(p =='Y');
}
int main()
{
    institution ins;
    ins.addInstitutionName();
    ins.addDept();
    admissionPanel(ins);
    return 0;
}
