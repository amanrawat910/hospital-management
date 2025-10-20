# Emergency Patient Room Prioritization System

## Overview
The Emergency Patient Room Prioritization System is a C++ program developed to help hospitals manage emergency patients efficiently.  
It records, organizes, and prioritizes patient data to ensure that patients with severe conditions are given room access first.

This project demonstrates how file handling and data structures can be used to solve a real-world healthcare problem.  
It serves as a practical implementation of C++ fundamentals and core DSA concepts.

## Objectives
- Automate the process of room allocation based on emergency severity.  
- Store and manage patient records using file handling for permanent storage.  
- Apply data structures for faster searching, updating, and sorting of records.  
- Implement logical decision-making to fairly prioritize patients.

## Features
- Add, view, update, and delete patient records  
- Automatic prioritization based on disease severity  
- File handling for data persistence (`patients.txt` and `diseases.txt`)  
- Efficient searching and sorting using data structures  
- Simple text-based user interface  

## System Modules

### 1. Patient Management Module
Handles all patient-related operations such as adding, updating, deleting, and viewing records.  
Each patient record contains details like ID, name, age, disease, date, time, and current status.

### 2. File Handling Module
Stores and retrieves all patient data using text files.  
- `patients.txt` stores patient records.  
- `diseases.txt` stores disease names and their priority levels.  
File handling is implemented using `ifstream`, `ofstream`, and `fstream`.

### 3. Disease Prioritization Module
Each disease is assigned a priority level such as High, Medium, or Low.  
The system uses this data to determine which patient should receive treatment or room allocation first.

### 4. Room Allocation Module
After assigning priority levels, this module allocates rooms to patients based on urgency and availability.  
Critical patients receive rooms before lower-priority cases.

### 5. Search and Sort Module
Allows searching for patients by ID or name and sorting them by disease priority or admission time.  
Ensures that staff can quickly access and organize patient information.


## Core DSA Concepts Used

**Structures (`struct`):** Used to define the Patient structure, grouping related data like ID, name, age, disease, and status.  

**Linked List:** Helps in dynamically managing records, allowing insertion, deletion, and updates without memory waste.  

**Maps (`std::map`):** Used for mapping diseases to their priority levels, enabling quick lookup and retrieval during prioritization.  

**File Handling:** Used as a persistent data structure to permanently store and retrieve records instead of using arrays.  

**Sorting Algorithms:** Used to reorder patients based on disease priority before allocating rooms.  

**Searching Algorithms:** Used to find specific patients quickly based on their ID or name.  

**Decision Logic:** Uses conditional statements to determine patient priority and room allocation order.
