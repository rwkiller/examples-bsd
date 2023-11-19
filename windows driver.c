#include <ntddk.h>

extern "C" NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    KdPrint(("Hello, World! Driver Loaded\n"));

    // Indique que le pilote gère les déchargements (Unload)
    DriverObject->DriverUnload = UnloadDriver;

    return STATUS_SUCCESS;
}

extern "C" VOID UnloadDriver(_In_ PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);

    KdPrint(("Hello, World! Driver Unloaded\n"));
}
