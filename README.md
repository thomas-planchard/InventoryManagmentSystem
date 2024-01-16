# Inventory Management System


| Name | Role |
|----|----|
| Malo | Frontend |
| Aurélien | Backend |
| Quentin | Frontend |
| Thomas | Frontend |
| Mathis | Backend |

## Rules of the project

In short:
	-**Backend - File** management system
	- **Frontend - Inventory** management system 

You must develop a simple file management system 
Create a command-line program that allows users to perform basic file operations such as : 
 - creating new files 
 - deleting files
 - [PLUS] listing files in a directory 
 - [PLUS] searching for files based on criteria.
the system must support text and binary files 

Your main function should be very minimal;
Don't open files (only for previewing/debugging)
Create appropriate utility functions for the frontend 

### Frontend Overview

Develop a basic Inventory Management System. Each product is represented by a record containing information such as 
- product id 
- name 
- quantity 
- price 
The users of your frontend should be able to:
- read and write report (text files)

Records operations should include :
 - ADD
 - View
 - search
 - Update 
 - Delete



## Frontend functions


## Backend functions

### File management system

#### Write in a file

```c
int writeFile(char *fileName, char *content);
```

#### Create a file

```c
int createFile(char *fileName);
```

#### Delete a file

```c
int deleteFile(char *fileName);
```

#### List files in a directory

```c
int listFiles(char *directoryName);
```

#### Search for files based on criteria

```c
int searchFiles(char *directoryName, char *criteria);
```

#### Add report




- Launch the program:
	- Press 1 for: Make a transaction (add or remove or modify an item)
		- Press 1 for: for: Add a product (receive stocks)
		- Press 2 for: Remove a product (sell stuff)
		- Press 3 for: Modify (change price, or name or etc.)
		- Press 9 for: Back()
	- Press 2 for: Inventory
		- Press 1 for: Display the whole inventory
		- Press 2 for: Search an item given a criterion
		- Press 9 for: Back()
	- Press 3 for: Reports
		- Press 1 for: List Reports
			- Press 1 for: Select Report
			- Press 9 for: Back()
		- Press 2 for: Write a new report
		- Press 9 for: Back()
	- Press 9 for: Exit()
