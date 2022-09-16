#include "helloLibrary/Class1.h"

using namespace helloLibrary;

Class1::Class1(string text)
{
    _text = text;
}

string Class1::GetText()
{
    return _text;
}