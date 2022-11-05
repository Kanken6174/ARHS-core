#include <string>
#include "./../../hardware/hw/serial.hpp"   //used to include the observer patter? eh...
#include "../../hardware/psvr/_psvr.hpp"    //used to include the command patter... eh²
#include <atomic>

enum underlyingType
{
    MenuitemT = 0,
    NumberPickerItemT = 1,
    CheckerItemT = 2,
    ExectuableT = 3
};

class baseItem : public MapObservable   //base abstract 
{
protected:
    underlyingType type;
public:
    std::atomic_bool selected = false;
    std::atomic_bool visible = true;
    underlyingType getTrueType(){
        return type;
    }
};

class menuitem : public baseItem    //menu item used soley for navigation
{
protected:
    std::string data;
    Command* _navigateToDestination;
public:
    menuitem(Command* navigateToDestination): _navigateToDestination(navigateToDestination){type = MenuitemT;}
    void setData(std::string newData)
    {
        data = newData;
        sendMessage("data", data);
    }
    std::string getData(){return data;}
    void navigate(){_navigateToDestination->Execute();}
};

class NumberPickerItem : public baseItem    //menu item used to display and pick a number (increment/decrement)
{
protected:
    int data;

public:
    NumberPickerItem(){type = NumberPickerItemT;}
    void decrement(){++data; sendMessage("data", std::to_string(data));}
    void increment(){--data; sendMessage("data", std::to_string(data));}
    int getData(){ return data; }
};

class CheckerItem : public baseItem
{
protected:
    bool data;
    Command* _ifFalse;
    Command* _ifTrue;
public:
    CheckerItem(Command* ifFalse, Command* ifTrue): _ifFalse(ifFalse), _ifTrue(ifTrue) {type = CheckerItemT;}
    void toggle()
    {
        data = !data;
        data ? _ifTrue->Execute() : _ifFalse->Execute();
        sendMessage("data", data ? "true" : "false");
    }

    bool getData()
    {
        return data;
    }
};

class ButtonItem : public baseItem
{
    protected:
    std::string data;
    Command* _toExec;
    public:
    ButtonItem(Command* toExec): _toExec(toExec) {type = ExectuableT;}
    void click(){_toExec->Execute();}
    void setData(std::string newData){data = newData; sendMessage("data", data);}
    std::string getData(){return data;}
};