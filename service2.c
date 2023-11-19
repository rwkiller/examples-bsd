#include <stdio.h>
#include <windows.h>

// Fonction du service (vous pouvez la personnaliser)
VOID ServiceMain(DWORD argc, LPTSTR *argv) {
    // Effectuez le travail du service ici
    while (1) {
        // Votre code de service va ici
        // Vous pouvez exécuter votre logique en continu dans cette boucle
        Sleep(1000);  // Exemple : attendez 1 seconde
    }
}

// Point d'entrée principal pour le service
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
