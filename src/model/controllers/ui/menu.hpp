#include "menuItem.hpp"

class Menu
{
protected:
    std::vector<baseItem *> _items;
    std::string _name;
    Menu *_previous;
    Command* _navigateBackCommand;
    unsigned int selectedIndex = 0;

public:
    Menu(std::string name, Menu *previous, Command* navigateBackCommand) : _name(name), _previous(previous), _navigateBackCommand(navigateBackCommand) {}
    void addItem(baseItem *item) { _items.push_back(item); }
    std::vector<baseItem *> getItems(){return _items;}
    void selectedUp();
    void selectedDown();
    void clickb1();
    void clickb2();
    void clickok();
    void clickback();
    std::string getName(){return _name;}
    std::atomic_bool selecting = false;
    int getSelectedIndex(){return selectedIndex;}
};