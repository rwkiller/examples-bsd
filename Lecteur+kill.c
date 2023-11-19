#include <windows.h>
#include <stdio.h>

void WatchDirectory(const char *path) {
    DWORD dwBytes;
    char buffer[1024];
    HANDLE hDir = CreateFile(
        path,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        printf("Erreur lors de l'ouverture du répertoire. Code d'erreur : %d\n", GetLastError());
        return;
    }

    while (ReadDirectoryChangesW(
        hDir,
        buffer,
        sizeof(buffer),
        TRUE,
        FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE,
        &dwBytes,
        NULL,
        NULL
    )) {
        FILE_NOTIFY_INFORMATION *info = (FILE_NOTIFY_INFORMATION *)buffer;
        do {
            if (info->Action == FILE_ACTION_MODIFIED) {
                wprintf(L"Fichier modifié : %s\n", info->FileName);
            }
            info = (FILE_NOTIFY_INFORMATION *)((char *)info + info->NextEntryOffset);
        } while (info->NextEntryOffset);
    }

    CloseHandle(hDir);
}

int main() {
    const char *directoryToWatch = "C:\\Chemin\\Vers\\Le\\Dossier"; // Remplacez par le chemin du dossier à surveiller
    WatchDirectory(directoryToWatch);
    return 0;
}
