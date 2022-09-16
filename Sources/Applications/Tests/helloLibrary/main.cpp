#include "helloLibrary/Class1.h"
#include <iostream>

using namespace helloLibrary;
using namespace std;

int main()
{
	Class1 c("Hello World!");
	cout<<c.GetText()<<endl;	
	return 0;
}
