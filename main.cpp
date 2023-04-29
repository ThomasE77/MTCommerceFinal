//Khoa Nguyen(ktn100)
//Thomas Stockstill(tes192)
//Vishal Murugavel (vm603)
//Sam Parker(scp347)
#include <iostream>
#include "User.h"
#include "Order.h"
#include "Cart.h"
#include "Product.h"
#include <iomanip>
#include <ctime>
#include <set>


using namespace std;

void loginMenu(User& user)
{
    bool success = false;
    char choice;
    string username, password;
    
    do
    {
        success = false;
        cout << "\n--------- Login ---------\n";
        cout << "Enter your username: ";
        cin >> username;
        cin.ignore(1024, '\n');
        cout << "Enter your password: ";
        cin >> password;
        cin.ignore(1024, '\n');
        cout << "1. Login (CONFIRM).\n"
            << "2. Back (CANCEL).\n";
        cout << "\nEnter your choice: ";
        cin.get(choice);
        cin.ignore(1024, '\n');
        
        switch (choice)
        {
            case '1': success = user.login(username, password);
                break;
            case '2': cout << "Login canceled\n";
                break;
            default: cout << "Invalid choice. Please try again.\n";
        }
        if(success)
        {
            cout << "Logged in successful.\n";
            break;
        }        
        if(!success && choice == '1')
            cout << "Invalid username or password. Please try again.\n";
    }
    while(choice != '2');
};
void createAccountMenu(User& user)
{
    bool success = false;
    char paymentChoice;
    char choice;
    string username, password, firstName, lastName, address, payment;

    do
    {
        cout << "\n--------- Create Account ---------\n";
        cout << "Enter your desired username: ";
        cin >> username;
        cin.ignore(1024, '\n');
        cout << "Enter your desired password: ";
        cin >> password;
        cin.ignore(1024, '\n');
        cout << "Enter your first name: ";
        cin >> firstName;
        cin.ignore(1024, '\n');
        cout << "Enter your last name: ";
        cin >> lastName;
        cin.ignore(1024, '\n');
        cout << "Enter your address: ";
        getline(cin, address);
        cin.ignore(1024, '\n');
        do
        {
            cout << "Choose your payment method:\n";
            cout << "1. Mastercard.\n";
            cout << "2. Visa.\n";
            cout << "3. American Express.\n";
            cout << "4. Discover.\n";
            cout << "5. PayPal.\n";
            cout << "6. Cancel.\n";
            cin.get(paymentChoice);
            cin.ignore(1024, '\n');
            switch(paymentChoice)
            {
                case '1': payment = "Mastercard";
                    break;
                case '2': payment = "Visa";
                    break;
                case '3': payment = "American Express";
                    break;
                case '4': payment = "Discover";
                    break;
                case '5': payment = "PayPal";
                    break;
                case '6': cout << "Canceled.\n";
                    break;
                default: cout << "Invalid payment method. Please try again.\n";
                    break;
            }
            if(paymentChoice == '6') break;
        }
        while(paymentChoice < '1' || paymentChoice > '5');

        cout << "---Review---\n" 
            << "username: " << username << endl
            << "password: " << password << endl
            << "firstName: " << firstName << endl
            << "lastName: " << lastName << endl
            << "address: " << address << endl
            << "payment: " << payment << endl;
        cout << "1. Create Account (CONFIRM).\n"
            << "2. Back (CANCEL).\n";
        
        cin.get(choice);
        cin.ignore(1024, '\n');
        
        switch (choice)
        {
            case '1': success = user.createAccount(username, password, firstName, lastName, address, payment);
                break;
            case '2': cout << "Canceled\n";
                break;
            default: cout << "Invalid choice. Please try again.\n";
        }
        if(!success && choice != '2')
            cout << "Failed to create account. Please try again.\n";
        else if(success)
        {
            cout << "Account created successful\n";
            break;
        }
    }
    while(choice != '2' || !success);
};
void beforeLoginMenu(User& user)
{
    char choice;
    do
    {

        cout << "\n--------- Bakery ---------\n"
            << "1. Login.\n"
            << "2. Create Account.\n"
            << "3. Exit.\n";
        cout << "Type your choice: ";
        cin.get(choice);
        cin.ignore(1024, '\n');
        switch (choice)
        {
            case '1': loginMenu(user);
                break;
            case '2': createAccountMenu(user);
                break;
            case '3': cout << "Exiting\n";
                break;
            default: cout << "Invalid choice. Please try again.\n";
                break;
        }
        if(user.isLoggedIn()) break;
    }
    while(choice != '3');
};
void logoutMenu(User &user)    //add other object to make them empty at logout
{
    char choice;
    bool success = false;
    do
    {
        cout << "\n--------------- Logout ---------------\n";
        cout << "Are you sure to logout?\n";
        cout << "1. Yes\n"
            << "2. No\n";
        cout << "\nEnter your choice: ";
        
        cin.get(choice);
        cin.ignore(1024, '\n');
        switch(choice)
        {
            case '1': success = user.logout();
                break;
            case '2': cout << "logout canceled\n";
                break;
            default: cout << "Invalid choice. Please enter 1 to logout, or 2 to cancel logout.\n";
                break;
        }
        if(!success)
            cout << "logged out failed\n";
        else
        {
            cout << "Logged out successful\n";
            break;
        }
    }
    while(choice != '2');
};
void userInfo(User &user)
{
    cout << "Username: " << user.getUsername() << endl
        << "FirstName: " << user.getFirstName() << endl
        << "LastName: " << user.getLastName() << endl
        << "Address: " << user.getAddress() << endl
        << "Payment: " << user.getPayment() << endl << endl;
};
void editPayment(User &user)
{
    char choice, paymentChoice;
    string payment;
    bool success = false;
    do
    {
        cout << "\nChoose your new payment method:\n";
        cout << "1. Mastercard.\n";
        cout << "2. Visa.\n";
        cout << "3. American Express.\n";
        cout << "4. Discover.\n";
        cout << "5. PayPal.\n";
        cout << "6. Cancel.\n";
        cout << "\nEnter your choice: ";
        cin.get(paymentChoice);
        cin.ignore(1024, '\n');
        switch(paymentChoice)
        {
            case '1': payment = "Mastercard";
                break;
            case '2': payment = "Visa";
                break;
            case '3': payment = "American Express";
                break;
            case '4': payment = "Discover";
                break;
            case '5': payment = "PayPal";
                break;
            case '6': cout << "Canceled.\n";
                break;
            default: cout << "Invalid payment method. Please try again.\n";
                break;
        }
        if(paymentChoice == '6') break;
    }
    while(paymentChoice < '1' || paymentChoice > '6');
    if(paymentChoice != '6')
    {
        do
        {
            cout << "New payment:" << payment << endl;
            cout << "\nAre you sure to make change:\n";
            cout << "1. Yes\n"
                << "2. No\n";
            cout << "Enter your choice: ";
            
            cin.get(choice);
            cin.ignore(1024, '\n');
            switch(choice)
            {
                case '1': success = user.setPayment(payment);
                    break;
                case '2': cout << "Change canceled\n";
                    break;
                default: cout << "Invalid choice. Please try again.\n";
                    break;
            }
            if(!success)
                cout << "Payment changing failed\n";
            else
            {
                cout << "Payment changed successful\n";
                break;
            }
        }
        while(choice != '2');
    }
};
void editAddress(User &user)
{
    char choice;
    string address;
    bool success = false;
    cout << "\n--------------- Edit Address ---------------\n";
    cout << "\nEnter your new address: ";
    getline(cin, address);
    cout << "\nNew address:" << address << endl;
    do
    {
        cout << "Are you sure to make change:\n";
        cout << "1. Yes\n"
            << "2. No\n";
        cout << "\nEnter your choice: ";
        
        cin.get(choice);
        cin.ignore(1024, '\n');
        switch(choice)
        {
            case '1': success = user.setAddress(address);
                break;
            case '2': cout << "Change canceled\n";
                break;
            default: cout << "Invalid choice. Please try again.\n";
                break;
        }
        if(!success)
            cout << "Address changing failed\n";
        else
        {
            cout << "Address changed successful\n";
            break;
        }
    }
    while(choice != '2');
};
void deleteAccount(User &user)    //add more to delete other data
{
    Order order(user);
    Cart cart(user.getUsername());
    char choice;
    bool success = false;
    do
    {
        cout << "Are you sure to delete this account?\n";
        cout << "1. Yes\n"
            << "2. No\n";
        cout << "Enter your choice: ";
        
        cin.get(choice);
        cin.ignore(1024, '\n');
        switch(choice)
        {
            case '1': 
            {
                success = cart.removeUserCart();
                success = order.removeUserOrders();
                success = user.deleteAccount();
            }    
                break;
            case '2': cout << "Delete canceled\n";
                return;
            default: cout << "Invalid choice. Please enter 1 to delete your account, or 2 to cancel deletion.\n";
                break;
        }
        if(!success)
            cout << "Account deletion failed\n";
        else
        {
            cout << "Account deleted successful\n";
            break;
        }
    }
    while(choice != '2');
};
void account(User &user)
{
    char choice;
    do
    {
        cout << "\n---------- Account Information ----------\n";
        userInfo(user);
        
        cout << "1. Edit Payment Information\n";
        cout << "2. Edit Address Information\n";
        cout << "3. Delete Account\n";
        cout << "4. Go back to Main menu\n";
        cout << "Enter your choice: ";
        cin.get(choice);
        cin.ignore(1024, '\n');
        switch(choice)
        {
            case '1': editPayment(user);
                break;
            case '2': editAddress(user);
                break;
            case '3': deleteAccount(user);
                break;
            case '4':
                break;
            default: cout << "Invalid choice. Please try again.\n";
                break;
        }
        if(choice == '3') break;
    }
    while(choice != '4');
};
void categoryMenu(User& user)
{
    char choice;
    char categoryChoice;
    int quantity = 1;
    int id;
    string category;
    vector<Product> products;
    Product product;
    Cart cart(user.getUsername()); // HERE 

    do {
        cout << "\n--------- Category Menu ---------" << endl;
        cout << "1. Go back to Main menu" << endl;
        cout << "2. View items in Category" << endl;
        cout << "3. Add item to Cart" << endl;
        cout << "\nEnter a choice: " << endl;
        cin >> choice;
        cin.ignore(1024, '\n');

        if (choice == '2')
        {
            cout << "Available categories: " << endl 
                << "1. Donuts" << endl
                << "2. Bagels" << endl 
                << "3. Pastries" << endl 
                << "4. Fritters" << endl;
            cout << "Enter a choice: ";
            cin >> categoryChoice;
            cin.ignore(1024, '\n');
          
            switch(categoryChoice)
            {
                case '1': category = "Donuts";
                    break;
                case '2': category = "Bagels";
                    break;
                case '3': category = "Pastries";
                    break;  
                case '4': category = "Fritters";
                    break;
                default: cout << "\nInvalid choice. Please try again." << endl;
                    break;
            }
            product.readFile(products);
            cout << endl << "Products in " << category << " category:" << endl;
            product.viewItemsInCategory(category);
        }
        if (choice == '3')
        {
            //Add item to cart by entering Product ID
            int id;
            cout << "Enter the product ID: ";
            cin >> id;
            cin.ignore(1024, '\n');
            cout << "Enter quantity: ";
            cin >> quantity;
            cin.ignore(1024, '\n');

            product.readFile(products);
            for (int i = 0; i < products.size(); i++)
            {
                if (products[i].getId() == id)
                {
                  //add product
                    cart.addProduct(products[i], quantity);
                    products[i].setQuantity(products[i].getQuantity() - 1);
                    cout << "Added: " << products[i].getName() << " to cart!" << endl;
                    break;
                }
            }

        }
    } while (choice != '1');

};

void cartMenu(User& user)
{
    char choice;
    int id, quantity;
    Cart cart(user.getUsername());
    Order order(user);
    Product product;
    vector<Product> cartItems;
    bool success = false;
    
    do {
        cout << "\n--------- Cart Menu ---------" << endl;
        cout << "1. Go back to Main menu" << endl;
        cout << "2. View items in cart" << endl;
        cout << "3. Remove item from cart" << endl;
        cout << "4. Checkout" << endl;
        cout << "Enter a choice: ";
        cin >> choice;
        cin.ignore(1024, '\n');

        switch (choice)
        {
            case '2':
            {
                cart.getProducts();
                cout << "\nTotal: $" << cart.getTotalCost() << endl;
                break;
            }

            case '3':
                cout << "Enter the product ID to remove: ";
                cin >> id;
                cin.ignore(1024, '\n');
                if (cart.removeProduct(id))
                {
                    cout << "Product removed successfully." << endl;
                }
                else
                {
                    cout << "Product could not be removed." << endl;
                }
                break;
            case '4': cart.checkOut();
                break;
            default:
                break;
        }
    } while (choice != '1');
}

void orderMenu(User &user) {
  std::string order;
  std::string date;
  Order orderObj(user);

  int choice = 0;
  while (choice != 2) {
    std::cout << "\n--------- Order Menu ---------\n";
    std::cout << "Please choose an option:\n";
    std::cout << "1. View stored orders\n";
    std::cout << "2. Quit\n";
    std::cout << "Enter a choice: " << endl;
    std::cin >> choice;
    std::cin.ignore(1024, '\n');      

    switch (choice) {
      case 1:
        // View stored orders
        orderObj.setUser(user.getUsername());
        std::cout << orderObj.getHistory() << std::endl;
        break;
      case 2:
        // Quit
        std::cout << "Goodbye!" << std::endl;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }
  }
}

void mainMenu(User &user)
{
    char choice;
    do
    {
        cout << "\n--------- Main Menu ---------\n";
        cout << "1. Category Information\n";
        cout << "2. Cart Information\n";
        cout << "3. Account Information\n";
        cout << "4. Order Information\n";
        cout << "5. Logout\n";
        cout << "\nEnter your choice: ";
        cin.get(choice);
        cin.ignore(1024, '\n');
        switch(choice)
        {
            case '1': categoryMenu(user);
                break;
            case '2': cartMenu(user);
                break;
            case '3': account(user);
                break;
            case '4': orderMenu(user);
                break;
            case '5': logoutMenu(user);
                break;
            default: cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while(choice != '5');
};

int main() 
{
    User user;
    beforeLoginMenu(user);
    while(user.isLoggedIn()) 
    {
        mainMenu(user);
    }
    return 0;
}