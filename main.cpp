#include <iostream>
#include <Windows.h>
extern "C" void OpenDocument(const char* filename);
extern "C" void CloseDocument();

typedef void (*ParseAndDisplayElementsFn)(const char*);

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <имя_файла>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];

    OpenDocument(filename);

    HMODULE hRuntimeDll = LoadLibraryA("techpr2rtdll.dll");
    if (hRuntimeDll) {
        ParseAndDisplayElementsFn ParseAndDisplayElements = (ParseAndDisplayElementsFn)GetProcAddress(hRuntimeDll, "ParseAndDisplayElements");
        if (ParseAndDisplayElements) {
            ParseAndDisplayElements(filename);
        }
        else {
            std::cerr << "Не удалось найти функцию ParseAndDisplayElements в run-time DLL.\n";
        }

        FreeLibrary(hRuntimeDll);
    }
    else {
        std::cerr << "Не удалось загрузить run-time DLL (techpr2rtdll.dll).\n";
    }

    CloseDocument();

    return 0;
}
