#include <windows.h>
#include <tchar.h>
#include <cstdio>
#include <process.h>

#define SIZE 4096

// Declaración de la función ChildThread
unsigned int __stdcall ChildThread(void* pBuf);

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,   // usar archivo de paginación
            nullptr,                   // seguridad predeterminada
            PAGE_READWRITE,         // acceso de lectura/escritura
            0,                      // tamaño máximo del objeto (DWORD de orden superior)
            SIZE,                   // tamaño máximo del objeto (DWORD de orden inferior)
            _T("Local\\MyFileMappingObject")); // nombre del objeto de mapeo de archivos

    if (hMapFile == nullptr) {
        _tprintf(_T("No se pudo crear el objeto de mapeo de archivos (%lu).\n"),    GetLastError());
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // manejador del objeto de mapeo
                                 FILE_MAP_ALL_ACCESS, // permiso de lectura/escritura
                                 0,
                                 0,
                                 SIZE);

    if (pBuf == nullptr) {
        _tprintf(_T("No se pudo mapear la vista del archivo (%lu).\n"), GetLastError());

        CloseHandle(hMapFile);
        return 1;
    }
