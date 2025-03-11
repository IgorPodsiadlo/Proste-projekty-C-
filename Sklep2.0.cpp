#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <optional>
#include <variant>
#include <stdexcept>

struct Product {
    std::string name;
    double price;
    int stock;
};

class Shop {
private:
    std::unordered_map<std::string, Product> inventory;
    std::unordered_map<std::string, int> cart;
    
public:
    void AddProduct(const std::string& name, double price, int stock) {
        if (price < 0 || stock < 0) {
            throw std::invalid_argument("Price and stock must be non-negative.");
        }
        inventory[name] = {name, price, stock};
    }
    
    void ShowProducts() const {
        std::for_each(inventory.begin(), inventory.end(), [](const auto& pair) {
            std::cout << "Product: " << pair.second.name 
                      << " | Price: " << pair.second.price 
                      << " | Stock: " << pair.second.stock << '\n';
        });
    }
    
    std::optional<Product> FindProduct(const std::string& name) const {
        auto it = inventory.find(name);
        return (it != inventory.end()) ? std::optional<Product>(it->second) : std::nullopt;
    }
    
    void AddToCart(const std::string& name, int quantity) {
        auto product = FindProduct(name);
        if (!product || product->stock < quantity) {
            std::cerr << "Product not available or insufficient stock.\n";
            return;
        }
        cart[name] += quantity;
        inventory[name].stock -= quantity;
    }
    
    void Checkout() {
        double total = 0.0;
        auto applyDiscount = [](double price) -> double {
            return (price >= 100) ? price * 0.9 : price;
        };
        
        std::for_each(cart.begin(), cart.end(), [&](const auto& pair) {
            const auto& name = pair.first;
            int quantity = pair.second;
            total += inventory[name].price * quantity;
            std::cout << "Purchased " << quantity << "x " << name << "\n";
        });
        
        total = applyDiscount(total);
        std::cout << "Total price after discount: " << total << "\n";
        cart.clear();
    }
};

int main() {
    auto shop = std::make_unique<Shop>();
    try {
        shop->AddProduct("Laptop", 1200.0, 5);
        shop->AddProduct("Headphones", 80.0, 10);
        shop->AddProduct("Keyboard", 45.0, 7);
    } catch (const std::exception& e) {
        std::cerr << "Error adding product: " << e.what() << "\n";
    }
    
    shop->ShowProducts();
    shop->AddToCart("Laptop", 1);
    shop->AddToCart("Keyboard", 2);
    shop->Checkout();
    
    return 0;
}
