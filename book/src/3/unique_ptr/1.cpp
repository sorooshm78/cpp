#include <iostream>
#include <memory>

void uniquePtrExample() {
    std::unique_ptr<int> unique = std::make_unique<int>(10);
    std::unique_ptr<int> movedUnique = std::move(unique);
    if (!unique) {
        std::cout << "uniquePtr is now nullptr\n";
    }
    std::cout << "movedUnique: " << *movedUnique << "\n";
}

void sharedPtrExample() {
    std::shared_ptr<int> shared1 = std::make_shared<int>(20);
    std::shared_ptr<int> shared2 = shared1; // مالکیت مشترک
    std::cout << "shared1: " << *shared1 << ", shared2: " << *shared2 << "\n";
    std::cout << "Use count: " << shared1.use_count() << "\n";
}

int main() {
    uniquePtrExample();
    sharedPtrExample();
    return 0;
}
