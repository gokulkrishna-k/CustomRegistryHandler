#include<Windows.h>
#include<iostream>
using namespace std;


LONG CreateRegKey(LPCWSTR path) {
	wcout << L"Creating a Registery in : " << path << endl;
	LONG lReg;
	HKEY hKey;

	lReg = RegCreateKey(
		HKEY_LOCAL_MACHINE,
		path,
		&hKey
	);

	if (lReg != ERROR_SUCCESS) {
		std::cout << "Registery Creation Failed , Error No" << GetLastError() << std::endl;
		return GetLastError();

	}
	else {
		std::cout << "Registery Creation Successfull\n";
		return ERROR_SUCCESS;
	}
	RegCloseKey(hKey);
}

LONG SetRegKeyValue(LPCWSTR path, LPCWSTR keyName, DWORD data) {


	HKEY hKey;
	LONG lReg;

	lReg = RegOpenKey(
		HKEY_LOCAL_MACHINE,
		path,
		&hKey
	);
	if (lReg != ERROR_SUCCESS) {
		std::cout << "Registery Open Failed , Error No" << GetLastError() << std::endl;
		return GetLastError();

	}
	else {
		std::cout << "Registery Opened Successfully\n";
	}

	lReg = RegSetValueEx(
		hKey,
		keyName,
		NULL,
		REG_DWORD,
		(LPBYTE)&data,
		sizeof(data)
	);
	if (lReg != ERROR_SUCCESS) {
		std::cout << "Registery Key Creation Failed , Error No" << GetLastError() << std::endl;
		return GetLastError();

	}
	else {
		std::cout << "Registery Key Creation Successfull\n";
		return ERROR_SUCCESS;
	}

	RegCloseKey(hKey);

}

LONG ReadRegKeyValue(LPCWSTR path, LPCWSTR keyName) {

	LONG lReg;

	DWORD outValue;
	DWORD size = sizeof(outValue);


	lReg = RegGetValue(
		HKEY_LOCAL_MACHINE,
		path,
		keyName,
		RRF_RT_REG_DWORD,
		nullptr,
		&outValue,
		&size
	);
	if (lReg != ERROR_SUCCESS) {
		std::cout << "Registery Read Failed , Error No" << GetLastError() << std::endl;
		return GetLastError();
	}
	else {
		std::cout << "Registery Read Successfull\n";
		std::cout << outValue << endl;
		return ERROR_SUCCESS;
	}

}


LONG SetRegKeyValueString() {
	return 0;
}


int main() {

	cout << "\nCUSTOM REGISTERY HANDLER\n";

	cout << "Enter the Option: \n";
	cout << "1. Create Key.\n";
	cout << "2. Add Value.\n";
	cout << "3. Get Value.\n";

	int ch;
	while (1) {
		cout << "Enter option : ";
		cin >> ch;
		switch (ch) {
		case 1:
		{
			string path;
			cout << "Enter the path : ";
			cin >> path;
			wstring widestr = wstring(path.begin(), path.end());
			LPCWSTR widecstr = widestr.c_str();

			CreateRegKey(widecstr);
			break;
		}
		case 2:
		{
			string spath;
			string skeyName;
			DWORD data;

			cout << "Enter the path : ";
			cin >> spath;
			cout << "Enter Key Name : ";
			cin >> skeyName;
			cout << "Enter the Value: ";
			wcin >> data;


			wstring wpath = wstring(spath.begin(), spath.end());
			LPCWSTR path = wpath.c_str();
			wstring wkeyName = wstring(skeyName.begin(), skeyName.end());
			LPCWSTR keyName = wkeyName.c_str();
			SetRegKeyValue(path, keyName, data);
			break;
		}

		case 3:
		{
			string spath;
			string skeyName;

			cout << "Enter the path : ";
			cin >> spath;
			cout << "Enter Key Name : ";
			cin >> skeyName;

			wstring wpath = wstring(spath.begin(), spath.end());
			LPCWSTR path = wpath.c_str();
			wstring wkeyName = wstring(skeyName.begin(), skeyName.end());
			LPCWSTR keyName = wkeyName.c_str();
			ReadRegKeyValue(path, keyName);
			break;
		}

		case 10:exit(1); break;
		}

	}






}