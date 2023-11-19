#include <stdio.h>
#include <windows.h>

VOID ServiceMain(DWORD argc, LPTSTR *argv) {
    while (1) {
        Sleep(1000); 
    }
}

int main() {
    SERVICE_TABLE_ENTRY ServiceTable[] = {
        { "NomDuService", ServiceMain },
        { NULL, NULL }
    };

    if (!StartServiceCtrlDispatcher(ServiceTable)) {
        printf("Erreur lors du démarrage du service : %d\n", GetLastError());
        return 1;
    }

    return 0;
}
