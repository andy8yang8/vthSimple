//https://stackoverflow.com/questions/1542108/how-to-hack-the-virtual-table
// get the VTable location either by dereferencing the
// first pointer in the object or by analyzing the compiled binary.

#include <iostream>
using namespace std;

void HackedVtable()
{
	cout << "Hacked V-Table\n" << endl;
}

class Base
{
public:
	virtual void Test() { cout << "base\n"; }
	//virtual void Test1() { cout << "Test 1"; }
	void *prt;
	Base() {}
};
/*
class Derived : public Base
{
public:
	void Test()
	{
		cout << "derived\n";
	}
};
*/
typedef void(*FUNPTR)();
typedef struct
{
	FUNPTR funptr;
} VTable;

int main()
{
	Base b1;
	Base *b1ptr = &b1;

	VTable vtable;
	vtable.funptr = HackedVtable;

	VTable *vptr = &vtable;
	memcpy(&b1, &vptr, sizeof(long));
	
	b1.Test();
	b1ptr->Test();// `HackedVtable` should be called instead of `Test`

	system("pause");
	return 0;
}
