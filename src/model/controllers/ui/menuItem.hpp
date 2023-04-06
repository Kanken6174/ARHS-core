#include <string>
#include "./../../hardware/hw/inputManager.hpp"   //used to include the observer patter? eh...
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
    int _data;
    std::string _name;
    std::string _targetValue;
public:
    NumberPickerItem(std::string name, std::string targetValue, int value = 0):_name(name),_targetValue(targetValue),_data(value){type = NumberPickerItemT;}
    void decrement(){--_data; sendMessage(_targetValue, std::to_string(_data));}
    void increment(){++_data; sendMessage(_targetValue, std::to_string(_data));}
    int getData(){ return _data; }
    std::string getName(){return _name;}
};

class CheckerItem : public baseItem
{
protected:
    bool data;
    std::string _name;
    Command* _ifFalse;
    Command* _ifTrue;
public:
    CheckerItem(std::string name, Command* ifFalse, Command* ifTrue): _name(name),_ifFalse(ifFalse), _ifTrue(ifTrue) {type = CheckerItemT;}
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

    std::string getName(){return _name;}
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