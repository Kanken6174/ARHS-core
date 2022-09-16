#ifndef HL_CLASS1_POINTER_H
#define HL_CLASS1_POINTER_H

#include <string>

using namespace std;

///a simple namespace
/** a full description
  */
namespace helloLibrary
{
	///a simple class
	class Class1
	{
	public:
		///initializes the Class1 instance
		/** @param text	a simple text
			*/
		Class1(string text);

		string GetText();

	private:
		///a simple text
		string _text;

	};
}

#endif //HL_CLASS1_POINTER_H
