#include <stdio.h>
#include <windows.h>

int main() {
    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!scm) {
        printf("Erreur lors de l'ouverture du gestionnaire de services : %d\n", GetLastError());
        return 1;
    }

    // Remplacez "NomDuPilote" par le nom de votre pilote
    const char* nomDuPilote = "NomDuPilote";
    const char* cheminVersPilote = "C:\\Windows\\System32\\Drivers\\LeFichierDePilote.sys"; // Remplacez par le chemin vers votre pilote

    SC_HANDLE service = CreateService(
        scm,
        nomDuPilote,
        nomDuPilote,
        SERVICE_ALL_ACCESS,
        SERVICE_KERNEL_DRIVER,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_NORMAL,
        cheminVersPilote,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    );

    if (!service) {
        printf("Erreur lors de la création du service : %d\n", GetLastError());
        CloseServiceHandle(scm);
        return 1;
    }

    if (StartService(service, 0, NULL)) {
        printf("Le pilote a été chargé avec succès.\n");
    } else {
        printf("Erreur lors du démarrage du service : %d\n", GetLastError());
    }

    CloseServiceHandle(service);
    CloseServiceHandle(scm);

    return 0;
}
