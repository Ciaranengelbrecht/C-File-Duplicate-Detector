# C-File-Duplicate-Detector

his C program analyzes file duplicates in directories based on different command-line options. Here's a concise overview:

Purpose:
The program identifies and reports duplicate files within specified directories, providing various options for customization.

Code Structure:
duplicates.c:

Parses command-line options and handles corresponding functionalities.
Defines a usage report function.
Utilizes a hashtable for efficient duplicate tracking.
hashtable.c:

Implements a hashtable to store file details.
Provides functions for list manipulation and hash generation.
find.c:

Offers functions to find duplicates based on filename or hash.
Prints statistics, duplicates of a specific file, or duplicates with specific hash values.
listdupes.c:

Manages potential duplicates and confirms actual duplicates.
Sorts and prints duplicate file details.
scandir.c:

Scans directories recursively, collecting file details.
Utilizes a hashtable to store and track unique files.
Noteworthy Features:
Command-line Options:

-a: Includes hidden files.
-A: Exits after attempting advanced features.
-l: Lists all duplicate files found.
-q: Quietly tests if any duplicates exist.
-f filename: Searches for duplicates of a specific file.
-h hash: Searches for duplicates of a specific hash.
Hashing:

Implements FNV32 hashing for efficient string hashing.
File Details:

Stores file information such as inode, size, and path.
Tracks total file count, size, and unique files.
