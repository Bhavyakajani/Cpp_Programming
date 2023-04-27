#include <iostream>
#include <cstring>
using namespace std;

///////main class

class Restaurant {

private:
    int choice;


public :

    void select(int choice);
    void print();

    friend class employeeList;
    friend class employee;
    friend class orderList;
    friend class order;
    void emp_detail();
    void order_detail();
    void emp_orders();
};

class orderList : public Restaurant{
private :
    class order{
    private:
        int order_id;
        int quantity;
        double order_cost;
        string item;
        order *next1;
    public :
        order(string item, int quantity, int order_id, double order_cost, order *next1);
        friend class employee;
        friend class employeeList;
        friend class orderList;
        friend class Restaurant;
    };
    order *head1=nullptr;
public  :
    void add_order(string item, int quantity, int order_id, double order_cost);
    void remove_order(int order_id);
    void assign_orders();
    void print_orders();
    //void order_detail();
    friend class order;
    friend class employee;
    friend class employeeList;

};


class employeeList : public Restaurant{
private :

///class employee for details of the employee
    class employee{
    private:
        string fname;
        int eid;
        double salary;
        int age;
        employee *next;
        orderList::order* ord;
    public:
        employee(string fname, int eid, int age, double salary, employee* next);
        friend class Restaurant;
        friend class employeeList;
        friend class orderList;
    };
    employee* head = nullptr;
public :
    employeeList() = default;
    void add(string fname, int eid, int age, double salary);
    void printEmp();

    //void add(char *fname, char *eid, char* position, double salary);
    void delete_emp(int eid);
    friend class order;
    friend class orderList;
    friend class Restaurant;
};

Restaurant s;///object for restaurant class
employeeList* employees = new employeeList();


void Restaurant :: select(int choice) {

    //Select the choice for admin page or placing order

    //do {
    switch (choice) {
        case 1 :
            cout << "\n-----------Employee Page----------\n";


            s.emp_detail();
            //s.add(fname, eid, position, salary);


            break;
        case 2 :
            cout << "Place your order here :\n";
            //print_menu();
            s.order_detail();
            break;
        case 3 :
            cout<<"it works!!"<<endl;
            emp_orders();
        default :
            cout << "Exit\n";
    }


}

///printing the final employee list

void Restaurant :: print(){
    //printing the options

    cout<<"1.Admin page\n";
    cout<<"2.Place your Order\n";
    cout<<"3.See employee orders\n";
    cout<<"0.Exit\n";

}

///constructor for employee class

employeeList :: employee::employee(string fname, int eid, int age, double salary, employee* next){



    this->eid=eid;

    this->salary=salary;

    this->fname=fname;

    this->age=age;

    this->next=next;
}

///printing the menu for modifying employee

void Restaurant :: emp_detail(){
    int choose = 1;
    while(choose == 1 || choose == 2 || choose == 3){

        cout << "1.Add new employee\n";
        cout << "2.Delete employee\n";
        cout << "3.Print employees\n";
        cout << "Select an option (1, 2 or 3) :\n";
        cin >> choose;
        string name; int id, age; double sal;
        switch(choose){
            case 1:
                cout << "Enter the employee name: \n";
                cin >> name;
                cout << "Enter the id :\n";
                cin >> id;
                cout << "Enter the salary: \n";
                cin >> sal;
                cout << "Enter the age: \n";
                cin >> age;
                employees->add(name, id, age, sal);
                break;
            case 2:
                cout<<"\nEnter the id of the employee to be removed: \n ";
                cin>>id;
                employees->delete_emp(id);
                break;
            case 3:
                employees->printEmp();
                break;
            default:
                    cout<<"\nWrong choice!!! Logging out...\n";
                break;
        }
    }
}

//function for adding employees

void employeeList :: add(string fname, int eid, int age, double salary){
    employee* e = new employee(fname,eid,age,salary, nullptr);




    employee* c = head;
    employee* p = nullptr;

    while(c){
        p = c;
        c = c->next;
    }
    if(c == employees->head)
        employees->head = e;
    else
        p->next = e;
}

//printing the final employee list

void employeeList :: printEmp(){
    employee* c = employees->head;
    while(c){
        cout << "Name: " << c->fname<<" | " << " Id: " << c->eid << " Age: " << c->age << " Salary: " << c->salary << endl;
        c = c->next;
    }
}

///fucntion for deleting the employees

void employeeList ::  delete_emp(int eid) {
    employee *c = head;
    employee *p = nullptr;
    if (head == nullptr) {
        cout << "\n No employees to delete.\n";
        return ;
    } else {
        while (c) {
            if (c->eid == eid)
                break;
            p = c;
            c = c->next;
        }
        if (c == head) {
            employee *temp = head;
            head = head->next;
            delete temp;
        } else if (c) {
            employee *temp = c;
            p->next = c->next;
            delete temp;
        }
    }
}


///object for the class orderList  
orderList* orders=new orderList();


///default constructor for creating the list
orderList :: order::order(string item, int quantity, int order_id, double order_cost, order *next1){



    this->item=item;

    this->quantity=quantity;

    this->order_id=order_id;

    this->order_cost=order_cost;

    this->next1=next1;
}


///Menu for the modifying orders

void Restaurant :: order_detail(){
    int choose = 1;
    //select_opt:
    while(choose == 1 || choose == 2 || choose == 3 || choose==4 ){
        cout << "1.Add new order\n";
        cout << "2.Delete order\n";
        cout << "3.Print order\n";
        cout << "4.Assign orders\n";
        cout << "0.Exit\n";
        cout << "Select an option (1, 2, 3 or 0) :\n";
        cin >> choose;
        string item; int order_id, quantity; double order_cost;
        switch(choose){
            case 1:
                cout << "Enter the order name: \n";
                cin >> item;
                cout << "Enter the order id :\n";
                cin >> order_id;
                cout << "Enter the cost: \n";
                cin >> order_cost;
                cout << "Enter the quantity: \n";
                cin >> quantity;
                orders->add_order(item, quantity, order_id, order_cost);
                break;
            case 2:
                cout<<"\nEnter the id of order to be removed: \n ";
                cin>>order_id;
                orders->remove_order(order_id);
                break;
            case 3:
                orders->print_orders();
                break;
            case 4 :
                cout<<"\n Orders asssigned to the employee successfully\n";
                orders->assign_orders();
            case 0 :
                cout<<"\nLogging out... \n";
                break;
            default:
                cout<<"\nWrong choice!!! Logging out...\n";

                break;
        }
    }
}

///Printing the assgined order to the employees

void Restaurant :: emp_orders(){
    int choose=1;

    employeeList::employee* curr = employees->head;
    cout<<"\n----------x------------x------------x------------\n";
    switch(choose){
        case 1:

            while(curr){
                cout << "Employee id: " << curr->eid <<" | "<< " order id : " << curr->ord->order_id << " order : " << curr->ord->item;
                cout<<" order price: " << (curr->ord->order_cost)*(curr->ord->quantity) << endl;
                curr = curr->next;
            }
            break;
        default:
            break;
    }

}

///Adding orders

void orderList :: add_order(string item, int quantity, int order_id, double order_cost){
    //Placing orders and addding to it

    order *o =new order(item, order_id, quantity, order_cost, nullptr);
    order* current = head1;
    order* prev = nullptr;

    while(current){
        prev = current;
        current = current->next1;
    }
    if(current == orders->head1)
        orders->head1 = o;
    else
        prev->next1 = o;
}

///removing orders

void orderList :: remove_order(int order_id){
    //removing the orders
    order* current = head1;
    order* prev = nullptr;
    while(current){
        if(current->order_id == order_id)
            break;
        prev=current;
        current=current->next1;
    }
    if(current == head1){
        order* temp = head1;
        head1 = head1->next1;
        delete temp;
    }
    else if (current){
        order* temp = current;
        prev->next1 = current->next1;
        delete temp;
    }

}


///Assigns every single order to single employee

void orderList :: assign_orders(){
    employeeList :: employee *current=employees->head;
    orderList :: order *current1=orders->head1;

    while(current){
        current->ord=current1;
        current=current->next;
        current1=current1->next1;
    }
}

/// Printing orders

void orderList :: print_orders(){
    order* current = orders->head1;
    cout<<"\n----------x------------x------------x------------\n";
    while(current){
        cout << "Item Name: " << current->item << " Order Id: " << current->order_id << " Quantity: " << current->quantity << " Price: " << (current->order_cost)*(current->quantity) << endl;
        current = current->next1;
    }
}


//main
int main(){
    int number=1;
    while(number==1 ||number==2 || number==3){
        s.print();
        cout<<"\n";
        cout<<"Select an option :\n";
        cin>>number;
        s.select(number);
    }

    return 0;
}
