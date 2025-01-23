// Libraries that we're gonna used in our project
#include <iostream>  // <----- For taking input output like cout, cin
#include <string>    // <----- For string
#include <fstream>   // <----- For file handling
#include <windows.h> // <----- For clearing screen using system("cls")
#include <conio.h>   // <----- For _getch() to take every single character from user without pressing enter
#include <regex>     // <----- For validiation of user's details

using namespace std;

const int MAX_PRODUCTS = 6;   // <---- Maximum number of available products
const int MAX_CART_SIZE = 20; // <---- Maximum number of products in the cart
const int MAX_CATEGORIES = 4; // <---- Number of categories

// Using Struct for product data.
struct Product
{
    string name;     // <------
    string price;    //       | Variables and their data types that are gonna used in
    string quantity; //       | this structure (Name: Product)
    string category; // <------
};

// Using Struct for user's data.
struct User
{
    string name;     // <------
    string username; //       |
    string password; //       | Variables that are gonna used in
    string email;    //       | this structure (Name: User)
    string phone;    //       |
    string address;  // <------
};

// array[6] = {{"k",""},{},{}};
// Products Data
Product products[MAX_PRODUCTS] = {            // <----- 
    {"T-Shirt", "Rs: 1500", "3", "Shirts"},   //      |
    {"Shirt", "Rs: 1800", "2", "Shirts"},     //      | Syntax
    {"Trousers", "Rs: 2100", "5", "Pants"},   //      | {"Name", "Price", " Quantity", "Category"}
    {"Shorts", "Rs: 1850", "6", "Pants"},     //      |
    {"Socks", "Rs: 400", "9", "Accessories"}, //      |
    {"Belt", "Rs: 200", "4", "Accessories"}}; // <-----

Product cart[MAX_CART_SIZE];  // <--- Shopping cart
int cart_size = 0;            // <--- Initialize cart size to 0 at first
float wallet_balance = 10000; // <--- Wallet Balance as gift

string categories[MAX_CATEGORIES] = {"All", "Shirts", "Pants", "Accessories"}; // <----- Names of categories

// Signature of functions
// Definition of functions are defined after main
void menu(); // <---- Function for main menu
void user(); // <---- Function asking user to login or create an account
void login(); // <---- Function for logging to an account
void create_account(); // <---- Function for creating a new account
void get_user_details(User &user); // <---- For getting user details
void save_user_data(const User &user); // <---- For Saving user data in a file 
bool load_user_data(const string &username, User &user); // <---- For loading user data from a file
void display_available_categories(); // <---- For displaying available categories
void display_products_by_category(const string &selected_category); // <---- For displaying products by category
void display_all_products(); // <---- Display all products
void shop(); // <---- Selecting products to add them to cart
void add_to_cart(int productIndex); // <---- Adding products to cart by quantity
void view_cart(); // <---- View products that are added in cart
void checkout(); // <---- Checkout process by confirming order
void printSeparator(char sep); // <---- For designing: taking character input as argument and show it 40 times
string get_hidden_input(); // <---- For masking the password: to show every character as "*"
bool validate_name(const string &name); // <---- Checking validiation for name: Contain only Uppercase or Lowercase letters
bool validate_username(const string &username); // <---- Checking validiation for username: Contain only Lowercase letters or numbers
bool validate_phone(const string &phone); // <---- Checking validiation for phone number: Contain only numbers and atleast of 11 numbers 
bool validate_email(const string &email); // <---- Checking validiation for email: It should follow the syntax (abc123@xyz.com)
bool validate_password(const string &password); // <---- Checking validiation for password: It should must contain uppercase letters, lowercase letters, numbers, characters or atleast 8 characters long
void show_animation_and_redirect(void (*next_function)()); // <---- Animation for redirecting to new function: "Redirecting..."

// Main Function from where code starts
int main()
{
    // User function displays: and asks user to login or create an account 
    // and then proceed to next from function to function
    user();
    
    // Means code executed successfully
    return 0;
}

// Function of main menu to jump to different functions
void menu()
{
    printSeparator('~');
    cout << "1. Display available categories\n";
    cout << "2. Display all products\n";
    cout << "3. View cart\n";
    cout << "4. Checkout\n";
    cout << "5. View Wallet\n";
    cout << "6. Exit\n";
    int choice;
    cin >> choice;
    cin.ignore();
    system("cls");
    switch (choice)
    {
    case 1:
        display_available_categories();
        break;
    case 2:
        display_all_products();
        break;
    case 3:
        view_cart();
        break;
    case 4:
        checkout();
        break;
    case 5:
        cout << "Your wallet balance is: " << wallet_balance; // Show wallet balance and wait
        cout << "\nPress Enter to continue..."; // until "Enter" key pressed
        cin.get();
        system("cls");
        show_animation_and_redirect(menu);
        break;
    case 6:
        cout << "Thank you for shopping with us!" << endl;
        exit(0);
    default:
        cout << "Invalid choice. Please try again." << endl;
        show_animation_and_redirect(menu);
    }
}

void user()
{
    printSeparator('~');
    cout << "Do you have an account?" << endl;
    printSeparator('~');
    cout << "1. Login" << endl;
    cout << "2. Create a new account." << endl;
    printSeparator('-');
    cout << "Type 1 or 2: ";
    int user_choice;
    cin >> user_choice;
    cin.ignore();
    system("cls");
    if (user_choice == 1)
    {
        show_animation_and_redirect(login);
    }
    else if (user_choice == 2)
    {
        show_animation_and_redirect(create_account);
    }
    else
    {
        cout << "Wrong input. Please try again." << endl;
        user();
    }
}

void login()
{
    printSeparator('~');
    cout << "Login to your account" << endl;
    printSeparator('~');
    string username, password;
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    password = get_hidden_input();
    system("cls");
    const int delay = 400; // In milliseconds
    const string loading = "Logging in"; // Text to show for animation
    for (int i = 0; i < 3; ++i)
    {
        cout << loading;
        for (int j = 0; j < 3; ++j)
        {
            cout << ".";
            Sleep(delay);
        }
        cout << "\r" << string(loading.size() + 3, ' ') << "\r";
        // First "\r" helps the cursor to move at the beginning of that line
        // string(loading.size() + 3, ' ' helps in giving spaces
        // Second "\r" helps the cursor to move at the beginning of that line
    }
    system("cls");
    User user; // Using struct for user's data
    if (load_user_data(username, user) && user.password == password) // Load user data from file to check if username or password is same as in file
    {
        printSeparator('-');
        cout << "Login Successfully\n";
        cout << "Welcome " << user.name << endl;
        printSeparator('-');
        show_animation_and_redirect(menu);
    }
    else // If username or password is not same as in file then show this(error message)
    {
        printSeparator('-');
        cout << "Login Failed. Please try again." << endl;
        printSeparator('-');
        cout << "1. Try Again\n";
        cout << "2. Create Account\n";
        int choice;
        cin >> choice;
        cin.ignore();
        system("cls");
        if (choice == 1)
        {
            login();
        }
        else if (choice == 2)
        {
            show_animation_and_redirect(create_account);
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
            login();
        }
    }
}

void create_account()
{
    printSeparator('~');
    cout << "Create your new account" << endl;
    printSeparator('~');
    User user;
    cout << "Enter your Full Name" << endl;
    cout << "Only contain uppercase or lowercase letters" << endl;
    getline(cin, user.name);
    if (!validate_name(user.name))
    {
        cout << "Invalid name. Please use letters only." << endl;
        create_account();
        return;
    }
    printSeparator('-');

    cout << "Enter your Username" << endl;
    cout << "Only contain lowercase letters or numbers" << endl;
    getline(cin, user.username);
    if (!validate_username(user.username))
    {
        cout << "Invalid username. Please use lowercase letters, numbers and no spaces." << endl;
        create_account();
        return;
    }
    printSeparator('-');

    cout << "Password must contain at least 8 characters, including uppercase, lowercase, and numbers." << endl;
    cout << "Enter your Password: ";
    user.password = get_hidden_input();
    cout << "Confirm your Password: ";
    string password2 = get_hidden_input();
    printSeparator('-');

    if (user.password == password2)
    {
        if (!validate_password(user.password))
        {
            cout << "Invalid password. It should contain at least 8 characters, including uppercase, lowercase, and numbers." << endl;
            show_animation_and_redirect(create_account);
            return;
        }
        get_user_details(user);
        save_user_data(user);
        const int delay = 400;
        const string loading = "Creating your account";
        for (int i = 0; i < 3; ++i)
        {
            cout << loading;
            for (int j = 0; j < 3; ++j)
            {
                cout << ".";
                Sleep(delay);
            }
            cout << "\r" << string(loading.size() + 3, ' ') << "\r";
        }
        system("cls");
        cout << user.name << ", your account was created successfully." << endl;
        cout << "Redirecting to the login page" << endl;
        show_animation_and_redirect(login);
    }
    else
    {
        cout << user.name << ", your password doesn't match. Please re-enter your information." << endl;
        show_animation_and_redirect(create_account);
    }
}

void get_user_details(User &user)
{
    cout << "Enter your Email: ";
    getline(cin, user.email);
    if (!validate_email(user.email))
    {
        cout << "Invalid email format. Please try again." << endl;
        get_user_details(user);
        return;
    }
    printSeparator('-');

    cout << "Enter your Phone Number: ";
    getline(cin, user.phone);
    if (!validate_phone(user.phone))
    {
        cout << "Invalid phone number. Please enter an 11-digit number." << endl;
        get_user_details(user);
        return;
    }
    printSeparator('-');

    cout << "Enter your City Name: ";
    getline(cin, user.address);
    printSeparator('-');
}

void save_user_data(const User &user)
{
    ofstream file(user.username + ".txt"); // File created with name of username for saving user's data
    if (file.is_open()) // Open File to save user's data
    {
        // Store user's data into a file taking details from struct
        file << user.name << endl;
        file << user.username << endl;
        file << user.password << endl;
        file << user.email << endl;
        file << user.phone << endl;
        file << user.address << endl;
        file.close(); // Close file after saving user's data
    }
}

bool load_user_data(const string &username, User &user)
{
    ifstream file(username + ".txt"); // Load data from file that we created before from name of username
    if (file.is_open()) // Open file to load user's data
    {
        // Load user's data from file save through these variables
        getline(file, user.name);
        getline(file, user.username);
        getline(file, user.password);
        getline(file, user.email);
        getline(file, user.phone);
        getline(file, user.address);
        file.close();
        return true;
    }
    return false;
}

void display_available_categories()
{
    printSeparator('~');
    cout << "Available categories are:\n";
    printSeparator('~');
    for (int i = 0; i < MAX_CATEGORIES; i++)
    {
        cout << i + 1 << ": " << categories[i] << endl;
    }
    int selected_category_index;
    cout << "Enter the number of the category you want to view: ";
    cin >> selected_category_index;
    cin.ignore();
    if (selected_category_index >= 1 && selected_category_index <= MAX_CATEGORIES)
    {
        string selected_category = categories[selected_category_index - 1];
        system("cls");
        display_products_by_category(selected_category);
    }
    else
    {
        cout << "Invalid category selection. Please try again." << endl;
        display_available_categories();
    }
}

void display_products_by_category(const string &selected_category)
{
    printSeparator('~');
    cout << "Products in Category: " << selected_category << endl;
    printSeparator('~');
    bool foundProducts = false;
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (selected_category == "All" || products[i].category == selected_category)
        {
            cout << i + 1 << ":" << endl;
            cout << "Name: " << products[i].name << endl;
            cout << "Price: " << products[i].price << endl;
            cout << "Quantity: " << products[i].quantity << endl;
            printSeparator('-');
            foundProducts = true;
        }
    }
    if (foundProducts)
    {
        shop();
    }
    else
    {
        cout << "No products found in category: " << selected_category << endl;
    }
}

void display_all_products()
{
    printSeparator('~');
    cout << "All Products:\n";
    printSeparator('~');
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        cout << i + 1 << ". Name: " << products[i].name << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Quantity: " << products[i].quantity << endl;
        cout << "Category: " << products[i].category << endl;
        printSeparator('-');
    }
    shop();
}

void shop()
{
    int productIndex;
    cout << "Enter the number of the product you want to buy or 0 to go back: ";
    cin >> productIndex;
    cin.ignore();
    if (productIndex == 0)
    {
        system("cls");
        show_animation_and_redirect(menu);
    }
    else if (productIndex > 0 && productIndex <= MAX_PRODUCTS)
    {
        add_to_cart(productIndex - 1);
    }
    else
    {
        cout << "Invalid selection. Please try again." << endl;
        shop();
    }
}

void add_to_cart(int productIndex)
{
    // Checking for product if it is available in cart before
    // If yes then run this "if" part and add 1 to quantity of that cart product
    // if no then run "if" part next to it
    bool itemFound = false;
    for (int i = 0; i < cart_size; i++)
    {
        if (cart[i].name == products[productIndex].name)
        {
            cart[i].quantity = to_string(stoi(cart[i].quantity) + 1);
            itemFound = true;
            break;
        }
    }

    // if product is not available in cart before then set the quantity of product to 1
    if (!itemFound && cart_size < MAX_CART_SIZE)
    {
        cart[cart_size] = products[productIndex];
        cart[cart_size].quantity = "1";
        cart_size++;
        cout << "Product added to cart." << endl;
    }
    else if (cart_size >= MAX_CART_SIZE)
    {
        cout << "Cart is full. Please proceed to checkout or remove some items." << endl;
    }

    system("cls");
    show_animation_and_redirect(menu);
}

void view_cart()
{
    if (cart_size == 0)
    {
        cout << "Your cart is empty. Please add products to view.\n";
        show_animation_and_redirect(menu);
    }
    else
    {
        printSeparator('~');
        cout << "Your Cart:\n";
        printSeparator('~');
        for (int i = 0; i < cart_size; i++)
        {
            cout << i + 1 << ". Name: " << cart[i].name << endl;
            cout << "Price: " << cart[i].price << endl;
            cout << "Quantity: " << cart[i].quantity << endl;
            cout << "Category: " << cart[i].category << endl;
            printSeparator('-');
        }
        cout << "1. Checkout\n";
        cout << "2. Delete all products from cart\n";
        cout << "3. Delete a single product from cart\n";
        cout << "4. Back to menu\n";
        int choice;
        cin >> choice;
        cin.ignore();
        system("cls");
        if (choice == 1)
        {
            show_animation_and_redirect(checkout);
        }
        else if (choice == 2)
        {
            cart_size = 0;
            const int delay = 400;
            const string loading = "Deleting all products";
            for (int i = 0; i < 3; ++i)
            {
                cout << loading;
                for (int j = 0; j < 3; ++j)
                {
                    cout << ".";
                    Sleep(delay);
                }
                cout << "\r" << string(loading.size() + 3, ' ') << "\r";
            }
            system("cls");
            cout << "Products deleted successfully.\n";
            show_animation_and_redirect(menu);
        }
        else if (choice == 3)
        {
            int delete_index;
            cout << "Enter the product number to delete: ";
            cin >> delete_index;
            cin.ignore();

            if (delete_index > 0 && delete_index <= cart_size)
            {
                for (int i = delete_index - 1; i < cart_size - 1; i++)
                {
                    cart[i] = cart[i + 1];
                }
                cart_size--;

                const int delay = 400;
                const string loading = "Deleting product";
                for (int i = 0; i < 3; ++i)
                {
                    cout << loading;
                    for (int j = 0; j < 3; ++j)
                    {
                        cout << ".";
                        Sleep(delay);
                    }
                    cout << "\r" << string(loading.size() + 3, ' ') << "\r";
                }
                system("cls");
                cout << "Product deleted successfully.\n";
            }
            else
            {
                cout << "Invalid product number.\n";
            }

            show_animation_and_redirect(menu);
        }
        else
        {
            show_animation_and_redirect(menu);
        }
    }
}

void checkout()
{
    if (cart_size == 0)
    {
        cout << "Your cart is empty. Please add products to view.\n";
        show_animation_and_redirect(menu);
    }
    else
    {
        string address;
        cout << "Enter your shipping address: ";
        getline(cin, address);

        float total_cost = 0.0;
        for (int i = 0; i < cart_size; i++)
        {
            string price_str = cart[i].price.substr(4); // <---- Remove "Rs: " from price string
            float price = stof(price_str);              // <---- Convert price to float
            int quantity = stoi(cart[i].quantity);      // <---- Convert quantity to int 
            total_cost += price * quantity;             // <---- Multiply by the quantity to calculate total price
        }

        // Display the receipt
        printSeparator('~');
        cout << "Receipt\n";
        printSeparator('~');
        cout << "Shipping Address: " << address << endl;
        cout << "Items:\n";
        for (int i = 0; i < cart_size; i++)
        {
            cout << i + 1 << ". " << cart[i].name
                 << " (Quantity: " << cart[i].quantity
                 << ", Price: " << cart[i].price << " each)\n";
        }
        float recieptBalance = wallet_balance;
        cout << "Total Amount: " << total_cost << endl;
        cout << "Wallet Balance: " << recieptBalance << endl;
        cout << "Remaining Balance after Purchase: " << recieptBalance - total_cost << endl;
        printSeparator('~');

        // Confirm the order
        cout << "Confirm your order (Y/N): ";
        string confirm;
        getline(cin, confirm);

        if (confirm == "y" || confirm == "Y")
        {
            if (wallet_balance >= total_cost)
            {
                const int delay = 400;
                const string loading = "Confirming order";
                for (int i = 0; i < 3; ++i)
                {
                    cout << loading;
                    for (int j = 0; j < 3; ++j)
                    {
                        cout << ".";
                        Sleep(delay);
                    }
                    cout << "\r" << string(loading.size() + 3, ' ') << "\r";
                }
                system("cls");
                wallet_balance -= total_cost;
                cout << "Order confirmed." << endl;
                cout << "Your balance is: " << wallet_balance << endl;
                cart_size = 0;
            }
            else
            {
                cout << "Insufficient funds. Order not confirmed.\n";
            }
        }
        else if (confirm == "n" || confirm == "N")
        {
            cout << "Order cancelled." << endl;
        }
        else
        {
            cout << "Incorrect input. Order not confirmed.\n";
        }
    }

    show_animation_and_redirect(menu);
}

void printSeparator(char sep)
{
    cout << string(40, sep) << endl;
}

string get_hidden_input()
{
    string input;
    char ch;
    while ((ch = _getch()) != '\r') // until Enter is pressed
    {
        if (ch == '\b' && !input.empty()) // handle backspace
        {
            cout << "\b \b";
            input.pop_back();
        }
        else if (ch != '\b')
        {
            cout << '*';
            input.push_back(ch);
        }
    }
    cout << endl;
    return input;
}

bool validate_name(const string &name)
{
    return regex_match(name, regex("^[A-Za-z ]+$"));
}

bool validate_username(const string &username)
{
    return regex_match(username, regex("^[a-z0-9]+$"));
}

bool validate_phone(const string &phone)
{
    return regex_match(phone, regex("^\\d{11}$"));
}

bool validate_email(const string &email)
{
    return regex_match(email, regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.com$"));
}

bool validate_password(const string &password)
{
    return regex_match(password, regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$"));
}

void show_animation_and_redirect(void (*next_function)())
{
    const int delay = 400;
    const string loading = "Redirecting";
    for (int i = 0; i < 3; ++i)
    {
        cout << loading;
        for (int j = 0; j < 3; ++j)
        {
            cout << ".";
            Sleep(delay);
        }
        cout << "\r" << string(loading.size() + 3, ' ') << "\r";
    }
    system("cls");
    next_function();
}