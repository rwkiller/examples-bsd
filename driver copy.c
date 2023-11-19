#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shellapi.h>

int main(int argc, char* argv[]) {
    // Vérifier si l'application est exécutée en tant qu'administrateur
    BOOL isElevated = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &cbSize)) {
            isElevated = elevation.TokenIsElevated;
        }
    }
    if (!isElevated) {
        // Si l'application n'est pas exécutée en tant qu'administrateur, demandez l'élévation
        char exePath[MAX_PATH];
        if (GetModuleFileName(NULL, exePath, sizeof(exePath))) {
            SHELLEXECUTEINFO shExecInfo = {0};
            shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shExecInfo.lpVerb = "runas"; // Demande l'élévation UAC
            shExecInfo.lpFile = exePath;
            shExecInfo.nShow = SW_SHOW;
            if (ShellExecuteEx(&shExecInfo) == ERROR_SUCCESS) {
                // Attendre la fin de l'exécution de la copie du pilote (ou autre action)
                WaitForSingleObject(shExecInfo.hProcess, INFINITE);
            }
            return 0;
        }
    }

    // Copiez le fichier du pilote vers le répertoire de destination
    const char* sourceFile = "C:\\Chemin\\Vers\\LeFichierDePilote.sys"; // Remplacez par le chemin de votre fichier de pilote
    const char* destinationDir = "C:\\Windows\\System32\\Drivers"; // Répertoire de destination du pilote
    char destinationPath[MAX_PATH];
    snprintf(destinationPath, sizeof(destinationPath), "%s\\%s", destinationDir, "LeFichierDePilote.sys"); // Nom du fichier de pilote de destination
    if (CopyFile(sourceFile, destinationPath, FALSE)) {
        printf("Le pilote a été copié avec succès.\n");
    } else {
        printf("Erreur lors de la copie du pilote : %d\n", GetLastError());
    }

    return 0;
}
