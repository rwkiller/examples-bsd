#include <windows.h>
#include <stdio.h>

void WatchDirectories() {
    DWORD dwBytes;
    char buffer[1024];

    // Surveillez les lecteurs locaux (C:, D:, etc.)
    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        char path[4];
        sprintf(path, "%c:\\", drive);

        HANDLE hDir = CreateFile(
            path,
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );

        if (hDir != INVALID_HANDLE_VALUE) {
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
    }
}

int main() {
    WatchDirectories();
    return 0;
}
