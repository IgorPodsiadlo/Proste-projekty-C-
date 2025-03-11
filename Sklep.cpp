#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iomanip>

class Product {
public:
    std::string name;
    double price;
    int stock;

    Product() : name(""), price(0.0), stock(0) {}

    Product(const std::string& n, double p, int s) : name(n), price(p), stock(s) {}
};

class Shop {
private:
    std::unordered_map<std::string, Product> inventory;
    std::vector<std::pair<std::string, int>> cart;

public:
    void AddProduct(const std::string& name, double price, int stock) {
        inventory.insert({name, Product(name, price, stock)});
    }

    void ShowProducts() const {
        std::cout << "\nDostępne produkty:\n";
        for (const auto& productPair : inventory) {
            const auto& product = productPair.second;
            std::cout << "- " << product.name << " | Cena: " << product.price << " PLN | Dostępność: " << product.stock << "\n";
        }
    }

    void AddToCart(const std::string& name, int quantity) {
        auto findProduct = inventory.find(name);
        if (findProduct != inventory.end() && findProduct->second.stock >= quantity) {
            cart.push_back({name, quantity});
            findProduct->second.stock -= quantity;
            std::cout << "Dodano " << quantity << "x " << name << " do koszyka.\n";
        } else {
            std::cerr << "Brak produktu lub niewystarczająca ilość.\n";
        }
    }

    void Checkout() {
        double totalPrice = 0.0;

        std::cout << "\nTwój koszyk:\n";
        for (const auto& item : cart) {
            const std::string& name = item.first;
            int quantity = item.second;
            double productPrice = inventory[name].price * quantity;
            std::cout << "- " << name << " x" << quantity << " | Łącznie: " << productPrice << " PLN\n";
            totalPrice += productPrice;
        }

        auto applyDiscount = [](double price) -> double {
            return (price >= 100) ? price * 0.9 : price;
        };

        totalPrice = applyDiscount(totalPrice);
        std::cout << "Do zapłaty: " << std::fixed << std::setprecision(2) << totalPrice << " PLN\n";
        cart.clear();
    }
};

int main() {
    Shop myShop;

    myShop.AddProduct("Mleko", 4.50, 10);
    myShop.AddProduct("Chleb", 3.00, 20);
    myShop.AddProduct("Ser", 12.99, 5);
    myShop.AddProduct("Kawa", 25.50, 8);
    
    int choice;
    do {
        std::cout << "\n1. Pokaż produkty\n2. Dodaj do koszyka\n3. Zapłać\n4. Wyjście\nWybierz opcję: ";
        std::cin >> choice;

        if (choice == 1) {
            myShop.ShowProducts();
        } else if (choice == 2) {
            std::string product;
            int quantity;
            std::cout << "Podaj nazwę produktu: ";
            std::cin >> product;
            std::cout << "Podaj ilość: ";
            std::cin >> quantity;
            myShop.AddToCart(product, quantity);
        } else if (choice == 3) {
            myShop.Checkout();
        }
    } while (choice != 4);

    std::cout << "Dziękujemy za zakupy.\n";
    return 0;
}
