/******************************************************************************
# Description:      Implementation file for the Album Sales Program. Contains
#                   functions for managing and displaying album data.
******************************************************************************/

#include "album.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>
using namespace std;

// --- Utility Functions ---
void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getInt(const char* prompt, int min, int max) {
    int value = min - 1;
    cout << prompt;
    while (!(cin >> value) || value < min || value > max) {
        cin.clear();
        clearBuffer();
        cout << "Invalid input! Enter a number between " << min << " and " << max << ": ";
    }
    clearBuffer();
    return value;
}

double getDouble(const char* prompt, double min) {
    double value = min - 1;
    cout << prompt;
    while (!(cin >> value) || value < min) {
        cin.clear();
        clearBuffer();
        cout << "Invalid input! Enter a number >= " << min << ": ";
    }
    clearBuffer();
    return value;
}

void getText(char* dest, int maxLen, const char* prompt) {
    char temp[MAX_CHAR] = "";
    bool valid = false;
    while (!valid) {
        cout << prompt;
        if (cin.getline(temp, maxLen)) {
            if (strlen(temp) < (unsigned)maxLen) {
                valid = true;
            } else {
                cout << "Input too long! Must be < " << maxLen << " chars. Try again.\n";
            }
        } else {
            cin.clear();
            clearBuffer();
            cout << "Error reading input. Please try again.\n";
        }
    }
    strcpy(dest, temp);
}

int compareField(const Album &a, const Album &b, char field) {
    int result = 0;
    if (field == 'A') {
        result = strcasecmp(a.artist, b.artist);
    } else if (field == 'Y') {
        result = b.releaseYear - a.releaseYear;
    } else if (field == 'S') {
        if (a.certifiedSales == b.certifiedSales) result = 0;
        else result = (a.certifiedSales < b.certifiedSales) ? 1 : -1;
    } else {
        result = strcasecmp(a.albumTitle, b.albumTitle); // Default to title
    }
    return result;
}

bool contains(const char* haystack, const char* needle) {
    bool found = true;
    if (!needle || !*needle) {
        found = true;
    } else {
        size_t hLen = strlen(haystack); // Use size_t instead of int
        size_t nLen = strlen(needle);   // Use size_t instead of int
        found = false;
        for (size_t i = 0; i <= hLen - nLen && !found; i++) {
            bool match = true;
            for (size_t j = 0; j < nLen && match; j++) {
                if (toupper(haystack[i + j]) != toupper(needle[j])) {
                    match = false;
                }
            }
            found = match;
        }
    }
    return found;
}

// --- Main Functions ---
bool loadAlbums(const char fileName[], Album albums[], int &count) {
    ifstream inFile(fileName);
    bool success = inFile.is_open();
    if (success) {
        count = 0;
        char buffer[256] = "";
        inFile.getline(buffer, 256); // Skip header
        while (count < MAX_ALBUMS && inFile.getline(buffer, 256)) {
            char* token = strtok(buffer, ",");
            strcpy(albums[count].artist, token);
            token = strtok(nullptr, ",");
            strcpy(albums[count].albumTitle, token);
            token = strtok(nullptr, ",");
            albums[count].releaseYear = atoi(token);
            token = strtok(nullptr, ",");
            albums[count].certifiedSales = atof(token);
            count++;
        }
        inFile.close();
    }
    return success;
}

void addAlbum(Album albums[], int &count) {
    bool added = (count < MAX_ALBUMS);
    if (added) {
        clearBuffer(); // Ensure buffer is cleared before getting text
        getText(albums[count].artist, COL_WIDTH_ARTIST, "Enter artist (< 19 chars): ");
        getText(albums[count].albumTitle, COL_WIDTH_ALBUM, "Enter title (< 29 chars): ");
        albums[count].releaseYear = getInt("Enter year (0-9999): ", 0, 9999);
        albums[count].certifiedSales = getDouble("Enter certified sales (millions): ", 0);
        count++;
        cout << "Album added.\n";
    } else {
        cout << "No space for more albums.\n";
    }
}

void removeAlbum(Album albums[], int &count) {
    bool removed = (count > 0);
    if (removed) {
        printAlbums(albums, count);
        char prompt[50] = "Enter index to remove (0-";
        char countStr[10];
        snprintf(countStr, sizeof(countStr), "%d", count - 1); // Use snprintf instead of sprintf
        strcat(prompt, countStr);
        strcat(prompt, "): ");
        int index = getInt(prompt, 0, count - 1);
        for (int i = index; i < count - 1; i++) {
            albums[i] = albums[i + 1];
        }
        count--;
        memset(&albums[count], 0, sizeof(Album));
        cout << "Album removed.\n";
        printAlbums(albums, count);
    } else {
        cout << "No albums to remove.\n";
    }
}

void printAlbums(const Album albums[], int count) {
    bool hasAlbums = (count > 0);
    if (hasAlbums) {
        cout << "\n " << left << setw(COL_WIDTH_ARTIST) << "Artist"
             << " " << setw(COL_WIDTH_ALBUM) << "Album"
             << " " << setw(COL_WIDTH_YEAR) << "Year"
             << " " << setw(COL_WIDTH_SALES) << "Certified(M)" << endl;
        cout << " " << string(LINE_LENGTH - 2, '-') << endl;
        for (int i = 0; i < count; i++) {
            cout << " " << left << setw(COL_WIDTH_ARTIST) << albums[i].artist
                 << " " << setw(COL_WIDTH_ALBUM) << albums[i].albumTitle
                 << " " << setw(COL_WIDTH_YEAR) << albums[i].releaseYear
                 << " " << setw(COL_WIDTH_SALES) << fixed << setprecision(1) << albums[i].certifiedSales
                 << endl;
        }
    } else {
        cout << "\nNo albums in the list.\n";
    }
}

void findAlbum(const Album albums[], int count) {
    bool hasAlbums = (count > 0);
    if (hasAlbums) {
        char search[MAX_CHAR] = "";
        clearBuffer();
        getText(search, MAX_CHAR, "Enter artist or title to find: ");
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (contains(albums[i].artist, search) || contains(albums[i].albumTitle, search)) {
                if (!found) {
                    cout << "\nMatches found:\n";
                    printAlbums(albums + i, 1); // Print header and first match
                    found = true;
                } else {
                    // Print only the album record for subsequent matches, not the header
                    cout << " " << left << setw(COL_WIDTH_ARTIST) << albums[i].artist
                         << " " << setw(COL_WIDTH_ALBUM) << albums[i].albumTitle
                         << " " << setw(COL_WIDTH_YEAR) << albums[i].releaseYear
                         << " " << setw(COL_WIDTH_SALES) << fixed << setprecision(1) << albums[i].certifiedSales
                         << endl;
                }
            }
        }
        if (!found) {
            cout << "No matches found.\n";
        }
    } else {
        cout << "No albums to search.\n";
    }
}

void sortAlbums(Album albums[], int count) {
    bool canSort = (count > 1);
    if (canSort) {
        clearBuffer();
        char field = '\0';
        cout << "Sort by (A)rtist, (T)itle, (Y)ear, (S)ales: ";
        cin >> field;
        field = toupper(field);
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (compareField(albums[j], albums[j + 1], field) > 0) {
                    Album temp = albums[j];
                    albums[j] = albums[j + 1];
                    albums[j + 1] = temp;
                }
            }
        }
        cout << "Sorted by ";
        if (field == 'A') cout << "Artist.\n";
        else if (field == 'T') cout << "Title.\n";
        else if (field == 'Y') cout << "Year.\n";
        else cout << "Sales.\n";
    } else {
        cout << "Not enough albums to sort.\n";
    }
}
