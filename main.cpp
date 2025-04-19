

// #include<bits/stdc++.h>
#include<string>
#include <iostream>
#include <windows.h> //for colors
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

const int TITLE_COLOR = 11;    // Cyan
const int MENU_COLOR = 15;     // White (bright)
const int HIGHLIGHT_COLOR = 10; // Green
const int WARNING_COLOR = 12;   // Red
const int BILL_COLOR = 11;     // Cyan
const int MAIN_MENU_COLOR = 14; //yellow


const string BANNER = R"(
               C R A V I N G S 
             -------------------    
)";

// Color functions
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printColor(string text, int color) {
    setColor(color);
    cout << text;
    setColor(7); // Reset to default
}

class OrderItem {
public:
    string name;
    float price;
};

class Customer {
public:
    string name;
    string contact;
    string address;
};

// Base class
class BillSystem {
protected:
    float totalBill;
    float value;

public:
    BillSystem() {
        totalBill = 0;
        value = 0;
    }

    BillSystem(float v) {
        totalBill = v;
        value = v;
    }

    ~BillSystem() {}

    BillSystem operator+ (const BillSystem &b1) const {
        return BillSystem(totalBill + b1.totalBill);
    }

    float getTotalBill() const { return totalBill; }

    void display(vector<OrderItem> items, Customer customer) {
        printColor("\n============= BILL SUMMARY =============\n", BILL_COLOR);
        
        // Customer details
        printColor("\nCustomer Details:\n", HIGHLIGHT_COLOR);
        cout << "Name: " << customer.name << endl;
        cout << "Contact: " << customer.contact << endl;
        cout << "Address: " << customer.address << endl;
        
        // Order details
        printColor("\nOrder Details:\n", HIGHLIGHT_COLOR);
        for(auto& item : items){
            cout << "  " << left << setw(25) << item.name << " - " << item.price << " Rs." << endl;
        }
        
        // Bill calculation
        printColor("\n----------------------------------------\n", BILL_COLOR);
        printColor("Subtotal: ", HIGHLIGHT_COLOR);
        cout << totalBill << " Rs.\n";
        
        float gst = (2.5 * totalBill) / 100;
        printColor("GST (2.5%): ", HIGHLIGHT_COLOR);
        cout << gst << " Rs.\n";
        
        printColor("\nTotal Bill: ", HIGHLIGHT_COLOR);
        cout << totalBill + gst << " Rs. \n";
        printColor("========================================\n", BILL_COLOR);
        
        // Save bill to file
        saveBillToFile(items, customer, gst);
    }

    void saveBillToFile(vector<OrderItem> items, Customer customer, float gst) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string filename = "Bill_" + to_string(ltm->tm_year + 1900) + 
                         to_string(ltm->tm_mon + 1) + 
                         to_string(ltm->tm_mday) + "_" +
                         to_string(ltm->tm_hour) + 
                         to_string(ltm->tm_min) + ".txt";
        
        ofstream billFile(filename);
        if (billFile.is_open()) {
            billFile << "============= RESTAURANT BILL =============\n";
            billFile << "Date: " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << ltm->tm_year + 1900 << endl;
            billFile << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << endl;
            
            billFile << "\nCustomer Details:\n";
            billFile << "Name: " << customer.name << endl;
            billFile << "Contact: " << customer.contact << endl;
            billFile << "Address: " << customer.address << endl;
            
            billFile << "\nOrder Details:\n";
            for (auto& item : items) {
                billFile << "  " << left << setw(25) << item.name << " - " << item.price << " Rs." << endl;
            }
            
            billFile << "\n----------------------------------------\n";
            billFile << "Subtotal: " << totalBill << " Rs.\n";
            billFile << "GST (2.5%): " << gst << " Rs.\n";
            billFile << "\nTotal Bill: " << totalBill + gst << " Rs. \n";
            billFile << "========================================\n";
            
            billFile.close();
            printColor("\nBill saved to " + filename + "\n", WARNING_COLOR);
        } else {
            printColor("\nError saving bill to file!\n", WARNING_COLOR);
        }
    }
};

// Derived classes for menu categories
class Beverage : public BillSystem {
public:
    void BeverageMenu() {
        printColor("\n======== Beverages ========\n\n", MENU_COLOR);
        printColor("1. Coke     - 20 Rs. \n", MENU_COLOR);
        printColor("2. Sprite   - 20 Rs. \n", MENU_COLOR);
        printColor("3. Mojito   - 60 Rs. \n", MENU_COLOR);
        printColor("4. Juices   - 100 Rs. \n", MENU_COLOR);
        printColor("5. Back to main menu\n", WARNING_COLOR);
    }
};

class Appetizier : public BillSystem {
public:
    void AppetizierMenu() {
        printColor("\n======== Appetizier ========\n\n", MENU_COLOR);
        printColor("1. Panner Chilli Dry     - 220 Rs. \n", MENU_COLOR);
        printColor("2. Cheese Bites          - 150 Rs. \n", MENU_COLOR);
        printColor("3. French Fries          - 150 Rs. \n", MENU_COLOR);
        printColor("4. Basket Chaat          - 100 Rs. \n", MENU_COLOR);
        printColor("5. Back to main menu\n", WARNING_COLOR);
    }
};

class MainCourse : public BillSystem {
public:
    void MainCourseMenu() {
        printColor("\n======== Main Course ========\n\n", MENU_COLOR);
        printColor("1. Panner Butter Masala       - 420 Rs. \n", MENU_COLOR);
        printColor("2. Jeera Rice & Dal Fry       - 350 Rs. \n", MENU_COLOR);
        printColor("3. Hydredabadi Biryani        - 250 Rs. \n", MENU_COLOR);
        printColor("4. Choole Bhature             - 300 Rs. \n", MENU_COLOR);
        printColor("5. Back to main menu\n", WARNING_COLOR);
    }
};

class Dessert : public BillSystem {
public:
    void DessertMenu(){
        printColor("\n======== Dessert ========\n\n", MENU_COLOR);
        printColor("1. Cheese Cake         - 120 Rs. \n", MENU_COLOR);
        printColor("2. Gulab Jamun         - 50 Rs. \n", MENU_COLOR);
        printColor("3. Choco Brownie       - 100 Rs. \n", MENU_COLOR);
        printColor("4. Ice Cream           - 80 Rs. \n", MENU_COLOR);
        printColor("5. Back to main menu\n", WARNING_COLOR);
    }
};

class FastFood : public BillSystem {
public:
    void FastFoodMenu(){
        printColor("\n======== FastFood ========\n\n", MENU_COLOR);
        printColor("1. Pizza                   - 350 Rs. \n", MENU_COLOR);
        printColor("2. Burger                  - 150 Rs. \n", MENU_COLOR);
        printColor("3. Sandwich                - 100 Rs. \n", MENU_COLOR);
        printColor("4. Garlic Bread Sticks     - 200 Rs. \n", MENU_COLOR);
        printColor("5. Back to main menu\n", WARNING_COLOR);
    }
};

Customer getCustomerDetails(){
    Customer customer;
    system("cls");
    printColor("\n======== CUSTOMER DETAILS ========\n\n", HIGHLIGHT_COLOR);
    
    cout << "Enter customer name: ";
    getline(cin >> ws, customer.name);
    
    cout << "Enter contact number: ";
    getline(cin, customer.contact);
    
    cout << "Enter delivery address: ";
    getline(cin, customer.address);
    
    return customer;
}

int main(){
    system("cls"); // Clear screen
    printColor(BANNER + "\n\n", TITLE_COLOR);
    
    vector<OrderItem> currentOrder;
    BillSystem total;
    Customer customer;
    bool customerDetailsTaken = false;
    int mainChoice = 0;

    while(true){
        printColor("\n~~~~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~~~~\n\n", MAIN_MENU_COLOR);
        printColor("1. Beverages \n", MENU_COLOR);
        printColor("2. Appetizer \n", MENU_COLOR);
        printColor("3. Main Course \n", MENU_COLOR);
        printColor("4. Dessert \n", MENU_COLOR);
        printColor("5. Fast Food \n", MENU_COLOR);
        printColor("6. View Current Order\n", HIGHLIGHT_COLOR);
        printColor("7. Exit & Generate Bill\n", WARNING_COLOR);
        printColor("\nChoose category: ", HIGHLIGHT_COLOR);
        cin >> mainChoice;

        if(mainChoice >= 1 && mainChoice <= 5){
            if(!customerDetailsTaken){
                customer = getCustomerDetails();
                customerDetailsTaken = true;
                printColor(BANNER + "\n\n", TITLE_COLOR);
            }
            
            switch(mainChoice){
                case 1: {
                    Beverage b1;
                    b1.BeverageMenu();
                    int drinkChoice = 0;
                    while(true){
                        printColor("Choose: ", HIGHLIGHT_COLOR);
                        cin >> drinkChoice;

                        if(drinkChoice == 1 || drinkChoice == 2){
                            string item = (drinkChoice == 1) ? "Coke" : "Sprite";
                            total = total + BillSystem(20);
                            currentOrder.push_back({item, 20});
                            printColor("\nAdded " + item + " to order!\n", HIGHLIGHT_COLOR);
                        }else if(drinkChoice == 3){
                            total = total + BillSystem(60);
                            currentOrder.push_back({"Mojito", 60});
                            printColor("\nAdded Mojito to order!\n", HIGHLIGHT_COLOR);
                        }else if(drinkChoice == 4){
                            total = total + BillSystem(100);
                            currentOrder.push_back({"Juices", 100});
                            printColor("\nAdded Juices to order!\n", HIGHLIGHT_COLOR);
                        }else if(drinkChoice == 5){
                            break;
                        }else{
                            printColor("Invalid option. Try again.\n", WARNING_COLOR);
                        }
                    }
                    break;
                }
                case 2: {
                    Appetizier a1;
                    a1.AppetizierMenu();
                    int AppetizierChoice = 0;
                    while(true){
                        printColor("Choose: ", HIGHLIGHT_COLOR);
                        cin >> AppetizierChoice;

                        if(AppetizierChoice == 1){
                            total = total + BillSystem(220);
                            currentOrder.push_back({"Panner Chilli Dry", 220});
                            printColor("\nAdded Panner Chilli Dry to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(AppetizierChoice == 2){
                            total = total + BillSystem(150);
                            currentOrder.push_back({"Cheese Bites", 150});
                            printColor("\nAdded Cheese Bites to order!\n", HIGHLIGHT_COLOR);
                        }
                        else if(AppetizierChoice == 3){
                            total = total + BillSystem(150);
                            currentOrder.push_back({"French Fries", 150});
                            printColor("\nAdded French Fries to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(AppetizierChoice == 4){
                            total = total + BillSystem(100);
                            currentOrder.push_back({"Basket Chaat", 100});
                            printColor("\nAdded Basket Chaat to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(AppetizierChoice == 5){
                            break;
                        } 
                        else{
                            printColor("Invalid option. Try again.\n", WARNING_COLOR);
                        }
                    }
                    break;
                }
                case 3: {
                    MainCourse m1;
                    m1.MainCourseMenu();
                    int MainCourseChoice = 0;
                    while(true){
                        printColor("Choose: ", HIGHLIGHT_COLOR);
                        cin >> MainCourseChoice;

                        if(MainCourseChoice == 1){
                            total = total + BillSystem(420);
                            currentOrder.push_back({"Panner Butter Masala", 420});
                            printColor("\nAdded Panner Butter Masala to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(MainCourseChoice == 2){
                            total = total + BillSystem(350);
                            currentOrder.push_back({"Jeera Rice & Dal Fry", 350});
                            printColor("\nAdded Jeera Rice & Dal Fry to order!\n", HIGHLIGHT_COLOR);
                        }
                        else if(MainCourseChoice == 3){
                            total = total + BillSystem(250);
                            currentOrder.push_back({"Hydredabadi Biryani", 250});
                            printColor("\nAdded Hydredabadi Biryani to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(MainCourseChoice == 4){
                            total = total + BillSystem(300);
                            currentOrder.push_back({"Choole Bhature", 300});
                            printColor("\nAdded Choole Bhature to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(MainCourseChoice == 5){
                            break;
                        } 
                        else{
                            printColor("Invalid option. Try again.\n", WARNING_COLOR);
                        }
                    }
                    break;
                }
                case 4:{
                    Dessert d1;
                    d1.DessertMenu();
                    int DessertChoice = 0;
                    while(true){
                        printColor("Choose: ", HIGHLIGHT_COLOR);
                        cin >> DessertChoice;

                        if(DessertChoice == 1){
                            total = total + BillSystem(120);
                            currentOrder.push_back({"Cheese Cake", 120});
                            printColor("\nAdded Cheese Cake to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(DessertChoice == 2){
                            total = total + BillSystem(50);
                            currentOrder.push_back({"Gulab Jamun", 50});
                            printColor("\nAdded Gulab Jamun to order!\n", HIGHLIGHT_COLOR);
                        }
                        else if(DessertChoice == 3){
                            total = total + BillSystem(100);
                            currentOrder.push_back({"Choco Brownie", 100});
                            printColor("\nAdded Choco Brownie to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(DessertChoice == 4){
                            total = total + BillSystem(80);
                            currentOrder.push_back({"Ice Cream", 80});
                            printColor("\nAdded Ice Cream to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(DessertChoice == 5){
                            break;
                        } 
                        else{
                            printColor("Invalid option. Try again.\n", WARNING_COLOR);
                        }
                    }
                    break;
                }
                case 5: {
                    FastFood f1;
                    f1.FastFoodMenu();
                    int FastFoodChoice = 0;
                    while(true){
                        printColor("Choose: ", HIGHLIGHT_COLOR);
                        cin >> FastFoodChoice;

                        if(FastFoodChoice == 1){
                            total = total + BillSystem(350);
                            currentOrder.push_back({"Pizza", 350});
                            printColor("\nAdded Pizza to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(FastFoodChoice == 2){
                            total = total + BillSystem(150);
                            currentOrder.push_back({"Burger", 150});
                            printColor("\nAdded Burger to order!\n", HIGHLIGHT_COLOR);
                        }
                        else if(FastFoodChoice == 3){
                            total = total + BillSystem(100);
                            currentOrder.push_back({"Sandwich", 100});
                            printColor("\nAdded Sandwich to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(FastFoodChoice == 4){
                            total = total + BillSystem(200);
                            currentOrder.push_back({"Garlic Bread Sticks", 200});
                            printColor("\nAdded Garlic Bread Sticks to order!\n", HIGHLIGHT_COLOR);
                        } 
                        else if(FastFoodChoice == 5){
                            break;
                        } 
                        else{
                            printColor("Invalid option. Try again.\n", WARNING_COLOR);
                        }
                    }
                    break;
                }
            }
        }
        else if(mainChoice == 6){
            system("cls");
            printColor("\n============= CURRENT ORDER =============\n", TITLE_COLOR);
            
            if(currentOrder.empty()){
                printColor("\nYour order is empty.\n", WARNING_COLOR);
            }else{
                for(auto& item : currentOrder){
                    cout << "  " << left << setw(25) << item.name << " - " << item.price << " Rs." << endl;
                }
                
                printColor("\n----------------------------------------\n", TITLE_COLOR);
                printColor("Current Subtotal: ", HIGHLIGHT_COLOR);
                cout << (total + BillSystem(0)).getTotalBill() << " Rs.\n";
            }
            
            printColor("\nPress enter to continue...", MENU_COLOR);
            cin.ignore();
            cin.get();
            system("cls");
            printColor(BANNER + "\n\n", TITLE_COLOR);
        }
        else if(mainChoice == 7){
            if(currentOrder.empty()){
                printColor("\nYour order is empty. Nothing to bill!\n", WARNING_COLOR);
                continue;
            }
            
            if(!customerDetailsTaken){
                customer = getCustomerDetails();
                customerDetailsTaken = true;
            }
            
            system("cls");
            total.display(currentOrder, customer);
            
            printColor("\nConfirm order? (y/n): ", HIGHLIGHT_COLOR);
            char PaymentChoice;
            cin >> PaymentChoice;
            
            if(PaymentChoice == 'y' || PaymentChoice == 'Y'){
                printColor("\nPreparing your order...\n", HIGHLIGHT_COLOR);
                for(int i = 0; i < 5; i++){
                    cout << ".";
                    Sleep(2000);
                }
                
                printColor("\n\nOrder placed! Estimated delivery: ", HIGHLIGHT_COLOR);
                time_t now = time(0);
                tm *ltm = localtime(&now);
                cout << (ltm->tm_hour) << ":" << (ltm->tm_min + 30) << "\n";
                printColor("Thank you for your order! Enjoy your meal!\n\n", TITLE_COLOR);
                break;
            }else{
                printColor("\nReturning to menu...\n", WARNING_COLOR);
                Sleep(1000);
                system("cls");
                printColor(BANNER + "\n\n", TITLE_COLOR);
            }
        }
        else{
            printColor("Invalid option. Please try again.\n", WARNING_COLOR);
        }
    }
    
    return 0;
}




