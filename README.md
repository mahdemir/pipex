# ↔️ Pipex
This project will let you discover in detail a UNIX mechanism that you already know from shell  **P | I | P | I | N | G | !**

## 🛠️ Compilation
Clone this repository and go in to the root of the directory by running:
```bash
git clone https://github.com/mahdemir/pipex/ && cd pipex
```
Now you can run ``` make ``` to create a executable named ``` pipex ```

## 🎯 Objective
The program `pipex` should repeat the behaviour of the next shell command:
```bash
$> < file1 cmd1 | cmd2 > file2
```
and looks like this:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
Errors need to be handled like: wrong commands, permission to files, etc. Including the returned exit codes.

## 🌳 Folder structure
```
.
├── Makefile
├── inc
│   └── pipex.h
└── src
    ├── main.c
    └── pipex.c
```

