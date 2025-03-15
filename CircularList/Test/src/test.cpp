#include <iostream>
#include "circular_list/circular_list.hpp"

int main()
{
    circular_list<int> example_list;
    std::cout << "List: " << example_list.str() << std::endl; // DEBUG

    example_list.insert(1);
    example_list.next();
    example_list.insert(2);
    example_list.next();
    example_list.insert(3);

    std::cout << std::endl;

    example_list.insert(4);
    example_list.prev();
    example_list.insert(5);
    example_list.prev();
    example_list.insert(6);

    std::cout << std::endl;

    example_list.next();
    example_list.remove();
    example_list.remove();
    example_list.remove();

    std::cout << std::endl;

    circular_list<int>* p_copied_list = new circular_list<int>;
    *p_copied_list = example_list;

    for (int i = 0; i < 10; i++) {
        p_copied_list->next();
    }

    std::cout << std::endl;

    for (int i = 0; i < 10; i++) {
        p_copied_list->prev();
    }

    std::cout << std::endl;

    std::cout << "First Element: " << p_copied_list->front() << std::endl;
    std::cout << "Last Element: " << p_copied_list->back() << std::endl;

    std::cout << std::endl;


    return 0;
}