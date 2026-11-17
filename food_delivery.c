#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 5
#define MAX_ORDERS 10

typedef struct {
    int id;
    char name[40];
    float price;
} MenuItem;

typedef struct {
    int itemId;
    int quantity;
} OrderItem;

MenuItem menu[MAX_ITEMS] = {
    {1, "Margherita Pizza", 249.00},
    {2, "Paneer Tikka Burger", 149.00},
    {3, "Masala Dosa", 120.00},
    {4, "Veg Biryani", 199.00},
    {5, "Cold Coffee", 89.00}
};

void displayMenu() {
    printf("\n--- MENU ---\n");
    printf("%-4s %-25s %-10s\n", "ID", "Item", "Price (Rs.)");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%-4d %-25s Rs. %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

int main() {
    OrderItem cart[MAX_ORDERS];
    int cartCount = 0;
    int choice, qty;
    char customerName[50], address[100];

    printf("=== Welcome to C Food Delivery System ===\n");
    printf("Enter Customer Name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = 0;

    printf("Enter Delivery Address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;

    while (1) {
        displayMenu();
        printf("\nEnter Item ID to add to cart (0 to checkout): ");
        if (scanf("%d", &choice) != 1 || choice == 0) break;

        if (choice < 1 || choice > MAX_ITEMS) {
            printf("Invalid Item ID. Try again.\n");
            continue;
        }

        printf("Enter Quantity: ");
        scanf("%d", &qty);
        if (qty <= 0) {
            printf("Invalid quantity.\n");
            continue;
        }

        cart[cartCount].itemId = choice;
        cart[cartCount].quantity = qty;
        cartCount++;
        printf("Added %d x %s to cart.\n", qty, menu[choice - 1].name);

        if (cartCount >= MAX_ORDERS) {
            printf("Cart is full! Proceeding to checkout.\n");
            break;
        }
    }

    if (cartCount == 0) {
        printf("\nNo items ordered. Thank you for visiting!\n");
        return 0;
    }

    float subtotal = 0.0f, deliveryFee = 40.0f;
    printf("\n================ INVOICE ================\n");
    printf("Customer : %s\n", customerName);
    printf("Address  : %s\n", address);
    printf("-----------------------------------------\n");
    printf("%-22s %-5s %-10s\n", "Item", "Qty", "Total");

    for (int i = 0; i < cartCount; i++) {
        MenuItem item = menu[cart[i].itemId - 1];
        float lineTotal = item.price * cart[i].quantity;
        subtotal += lineTotal;
        printf("%-22s x%-4d Rs. %.2f\n", item.name, cart[i].quantity, lineTotal);
    }

    float tax = subtotal * 0.05f; // 5% GST
    float grandTotal = subtotal + tax + deliveryFee;

    printf("-----------------------------------------\n");
    printf("Subtotal        : Rs. %.2f\n", subtotal);
    printf("GST (5%%)        : Rs. %.2f\n", tax);
    printf("Delivery Charge : Rs. %.2f\n", deliveryFee);
    printf("Grand Total     : Rs. %.2f\n", grandTotal);
    printf("=========================================\n");
    printf("Order Status: Confirmed & Out for Delivery!\n");

    return 0;
}
