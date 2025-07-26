#include <stdio.h>
#include <windows.h>
#include <string.h>

int main() {
    HANDLE hDisk;
    DWORD bytesRead;
    BYTE buffer[512];
    LARGE_INTEGER offset = { 0 };

    FILE *out = NULL;
    int found_start = 0;

    hDisk = CreateFileA(
        "\\\\.\\PhysicalDrive1",  
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDisk == INVALID_HANDLE_VALUE) {
        printf("Failed to access drive. Run as admin.\n");
        return 1;
    }

    printf("🔍 Scanning for JPEG...\n");

    // Scan up to 100MB (adjust as needed)
    for (int sector = 0; sector < 200000; sector++) {
        SetFilePointerEx(hDisk, offset, NULL, FILE_BEGIN);
        if (!ReadFile(hDisk, buffer, sizeof(buffer), &bytesRead, NULL) || bytesRead == 0)
            break;

        if (!found_start) {
            // Check if this sector contains JPEG start marker
            for (int i = 0; i < bytesRead - 1; i++) {
                if (buffer[i] == (BYTE)0xFF && buffer[i + 1] == (BYTE)0xD8) {
                    printf("JPEG header found at offset %llu bytes\n", offset.QuadPart + i);
                    out = fopen("recovered.jpg", "wb");
                    found_start = 1;
                    break;
                }
            }
        }

        if (found_start && out != NULL) {
            fwrite(buffer, 1, bytesRead, out);

            // Check for JPEG end marker
            for (int i = 0; i < bytesRead - 1; i++) {
                if (buffer[i] == (BYTE)0xFF && buffer[i + 1] == (BYTE)0xD9) {
                    printf(" JPEG footer found. File complete.\n");
                    fclose(out);
                    CloseHandle(hDisk);
                    return 0;
                }
            }
        }

        offset.QuadPart += sizeof(buffer);
    }

    // Close open handles if something fails
    if (out != NULL) fclose(out);
    CloseHandle(hDisk);

    printf("JPEG end not found. File may be incomplete or corrupted.\n");
    return 0;
}
