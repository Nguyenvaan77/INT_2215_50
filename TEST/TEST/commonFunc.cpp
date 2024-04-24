#include"commonFunc.h"

using namespace std;

bool checkdoidien(int trangthai1, int trangthai2)
{
	if (trangthai1 == 1)
	{
		if (trangthai2 == 2)
		{
			cout << "12ok" << endl;
			return true;
		}
		cout << "Kodoidien" << endl;
		return false;
	}
	if (trangthai1 == 2)
	{
		if (trangthai2 == 1)
		{
			cout << "21ok" << endl;
			return true;
		}
		cout << "Kodoidien" << endl;
		return false;
	}
	if (trangthai1 == 3)
	{
		if (trangthai2 == 4)
		{
			cout << "34ok" << endl;
			return true;
		}
		cout << "Kodoidien" << endl;
		return false;
	}
	if (trangthai1 == 4)
	{
		if (trangthai2 == 3)
		{
			cout << "43ok" << endl;
			return true;
		}
		cout << "Kodoidien" << endl;
		return false;
	}
}