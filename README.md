# Password Storage (C)
This is a C program which logs the username, password, and title of the company the username and password are for. 

Every change to the list of entries is currently done so by first parsing the text file containing the entries. The parsed entries are then stored into a linked list of structs that store the entries. With this linked list, nodes and their respective title, username, and password can be modified or deleted, or a new node can be added. When the user is done, the program deletes the contents of the password log and writes in the new/modified entries.

A main goal of mine is to change the data structure from a linked list to a self-balancing tree to make parsing data much quicker.
