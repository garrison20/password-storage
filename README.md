# Password Storage (C)
This is a C program which logs the title of the user's service and their respective username and password. Entries (meaning the combined title, username, and password) can be inserted or deleted. Current entries can also have any of their string values modified for updating. When given the name of the service, the program can print the username or password associated with it, if the service name exists.

Every change to the list of entries is currently done so by first parsing the text file containing the entries. The parsed entries are then stored into a linked list which stores the entries. With this linked list, nodes and their respective title, username, and password can be modified or deleted, or a new node can be added. When the user is done, the program deletes the contents of the password log file and writes in the changed set of entries.

A main goal of mine is to change the data structure from a linked list to a self-balancing tree to make parsing data much quicker.
