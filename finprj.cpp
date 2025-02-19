/******************************************************************************
# Author:           Josh Sarles
# Assignment:       Final Project (CS161B)
# Date:             February 23, 2025
# Description:      Main file for the Album Sales Program. Loads album data
#                   from "AlbumSales.csv" into an array of structs and provides
#                   a menu-driven interface for managing and analyzing the data.
# Input:            User menu selections (A, R, P, F, M, S, Q).
# Output:           Album data tables, prompts, and status messages.
# Sources:          Assignment specifications
******************************************************************************/

#include "album.h"
#include <iostream>
using namespace std;

int main() {
    Album albums[MAX_ALBUMS];
    int count = 0;
    char choice = '\0';

    cout << "Welcome to the Album Sales Program!\n";

    bool loaded = loadAlbums("albums.csv", albums, count);
    if (loaded) {
        bool done = false;
        while (!done) {
            cout << "\n(A)dd  (R)emove  (P)rint  (F)ind  (S)ort  (Q)uit\n";
            cout << "Enter choice: ";
            cin >> choice;
            choice = toupper(choice);
            if (choice == 'A') {
                addAlbum(albums, count);
            } else if (choice == 'R') {
                removeAlbum(albums, count);
            } else if (choice == 'P') {
                printAlbums(albums, count);
            } else if (choice == 'F') {
                findAlbum(albums, count);
            } else if (choice == 'S') {
                sortAlbums(albums, count);
            } else if (choice == 'Q') {
                done = true;
            } else {
                cout << "Invalid choice!\n";
            }
        }
        cout << "Goodbye!\n";
    } else {
        cout << "Failed to load albums.csv. Exiting.\n";
    }
    return 0;
}
