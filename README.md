# Inventory Managament System


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

sdflmkjsdlkf test




## Backend functions

### File management system

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




