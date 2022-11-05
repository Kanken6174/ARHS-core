#include "menu.hpp"

void Menu::selectedUp()
{
    if (selecting && _items.at(selectedIndex) != nullptr)
    {
        switch (_items.at(selectedIndex)->getTrueType())
        {
        case NumberPickerItemT:
            static_cast<NumberPickerItem *>(_items.at(selectedIndex))->increment();
            break;

        case CheckerItemT:
            static_cast<CheckerItem *>(_items.at(selectedIndex))->toggle();
            break;

        default:
            selecting = false;  //if a non-selectable item is somehow selected
            break;
        }
    }
    else
    {
        if (selectedIndex < _items.size() - 1)
            ++selectedIndex;
        else
            selectedIndex = 0;
    }
}

void Menu::selectedDown()
{
    if (selecting && _items.at(selectedIndex) != nullptr)
    {
        switch (_items.at(selectedIndex)->getTrueType())
        {
        case NumberPickerItemT:
            static_cast<NumberPickerItem *>(_items.at(selectedIndex))->decrement();
            break;

        case CheckerItemT:
            static_cast<CheckerItem *>(_items.at(selectedIndex))->toggle();
            break;

        default:
            selecting = false;  //if a non-selectable item is somehow selected
            break;
        }
    }
    else
    {
        std::cout << "not selecting, down " << selectedIndex << std::endl;
        if (selectedIndex > 0)
            --selectedIndex;
        else
            selectedIndex = _items.size() - 1;
    }
}

void Menu::clickb1() {}

void Menu::clickb2() {}

void Menu::clickok()
{
    if(_items.size() <= 0) return;
    if (_items.at(selectedIndex) != nullptr)
    {
        switch (_items.at(selectedIndex)->getTrueType())
        {
        case NumberPickerItemT:
            //static_cast<NumberPickerItem *>(_items.at(selectedIndex))->selected = true;
            selecting = true;
            break;

        case CheckerItemT:
            static_cast<CheckerItem *>(_items.at(selectedIndex))->toggle();
            break;

        case MenuitemT:
            static_cast<menuitem *>(_items.at(selectedIndex))->navigate();
            break;

        case ExectuableT:
            static_cast<ButtonItem *>(_items.at(selectedIndex))->click();
            break;

        default:
            break;
        }
    }
}

void Menu::clickback(){
    if(selecting)
        selecting = false;
    else
        _navigateBackCommand->Execute();
}