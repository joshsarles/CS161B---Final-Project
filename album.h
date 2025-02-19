/******************************************************************************
# Description:      Header file for the Album Sales Program. Defines the Album
#                   struct and declares functions for managing album data.
******************************************************************************/

#ifndef ALBUM_H
#define ALBUM_H

// --- Global constants ---
const int MAX_CHAR = 50;
const int MAX_ALBUMS = 100;
const int COL_WIDTH_ARTIST = 19;
const int COL_WIDTH_ALBUM  = 29;
const int COL_WIDTH_YEAR   = 9;
const int COL_WIDTH_SALES  = 16;
const int LINE_LENGTH = 79;

// --- Struct definition ---
struct Album {
    char artist[MAX_CHAR];
    char albumTitle[MAX_CHAR];
    int releaseYear;
    double certifiedSales;
};

// --- Function prototypes ---
// Desc: Loads album data from a CSV file into the array.
// Input: File name, albums array, count (reference).
// Output: Error message if file fails.
// Return: True if successful, false otherwise.
bool loadAlbums(const char fileName[], Album albums[], int &count);

// Desc: Adds a new album to the array.
// Input: albums array, count (reference).
// Output: Prompts and success/error message.
void addAlbum(Album albums[], int &count);

// Desc: Removes an album by index.
// Input: albums array, count (reference).
// Output: Prompts and updated list.
void removeAlbum(Album albums[], int &count);

// Desc: Prints all albums in a table.
// Input: albums array, count.
// Output: Formatted table or "no albums" message.
void printAlbums(const Album albums[], int count);

// Desc: Finds albums by substring in artist or title.
// Input: albums array, count.
// Output: Matching albums or "not found" message.
void findAlbum(const Album albums[], int count);

// Desc: Sorts albums by a user-selected field.
// Input: albums array, count.
// Output: Prompt and sort confirmation.
void sortAlbums(Album albums[], int count);

#endif
