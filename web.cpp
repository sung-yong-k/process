#include <windows.h>
#include <urlmon.h>
#include <iostream>

#pragma comment(lib, "urlmon.lib")

int main() {
    const char* url = "https://test2.fibertelecom.it/10MB.zip";  // Replace with your file URL
    const char* filePath = "test.zip";  // Replace with your file path

    HRESULT result = URLDownloadToFile(NULL, url, filePath, 0, NULL);

    if (SUCCEEDED(result)) {
        std::cout << "File downloaded successfully!" << std::endl;
    }
    else {
        std::cerr << "File download failed. HRESULT: " << result << std::endl;
    }

    return 0;
}
