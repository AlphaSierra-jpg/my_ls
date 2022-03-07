![banner](https://user-images.githubusercontent.com/67347242/157099534-90d55200-b212-4eab-a145-325babf7ab6d.png)

Language: ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

#Installation 

For install my_ls follow the instructions:

if "libmy.a my_assets.o", exists delete them.
```
1- gcc -c assets/my_assets.c
2- ar -r libmy.a my_assets.o
3- ranlib libmy.a
4- make
```
#Information 

This program is an interpretation of the "ls" function on linux. It integrates the parameters:
```
  -l : List information about the files
  -L : Using with -l for display information of the file target by the symbolique link
  -R : When reading the folder -R reads the contents of the lister folders and displays them with recursivity
  -a : Display hidden files
  -A : Same as -a but hide "." and ".."
  -d : Directories are listed as plain files (not searched recursively)
```
you can try for example:
```my_ls -A -l -L ~/ /etc
