#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

void ListProcesses() {
    // Take a snapshot of all processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to take process snapshot" << std::endl;
        return;
    }

    // Set up the structure size for PROCESSENTRY32
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve the first process in the snapshot
    if (!Process32First(hSnapshot, &pe32)) {
        std::cerr << "Failed to retrieve process information" << std::endl;
        CloseHandle(hSnapshot);
        return;
    }

    // Loop through all processes in the snapshot
    do {
        // Open the process with minimal access rights
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
        if (hProcess != nullptr) {
            // Print the process name and PID
            std::wcout << L"Process Name: " << pe32.szExeFile << L", PID: " << pe32.th32ProcessID << std::endl;
            CloseHandle(hProcess);  // Close the process handle after we are done with it
        }
        else {
            std::wcout << L"Could not open process: " << pe32.szExeFile << L" (PID: " << pe32.th32ProcessID << L")" << std::endl;
        }

    } while (Process32Next(hSnapshot, &pe32));  // Move to the next process

    // Close the snapshot handle
    CloseHandle(hSnapshot);
}

int main() {
    ListProcesses();
    return 0;
}
