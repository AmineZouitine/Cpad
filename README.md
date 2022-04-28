# Cpad

**Do you use several commands in your terminal, one after the other ?** This tool allows you to combine **multiple templated** bash commands with the alias of your choice.

## 👨🏽‍💻 Installation

## ⚡️ Quick start

in these examples you will remember to see the following elements: **-cb** **[cb]** **[?]**.
They are explained in the features section, but quickly:

**-cb** - Allows you to create a combo command.

**[cb]** - Is the separator between the commands

**[?]** - Is a template allowing the user to give a custom argument

### Fast push on Github
Add files to a commit, set a commit message, see the changes in your repository. Push your changes to the branch of your choice.
```sh
  -cb git add [?] [cb] git status [?] [cb] git commit -m "[?]" [cb] git push origin [?] [cb] git checkout [?]
```

```
 Here is how to use the command we just created: 
```
--> gif

### Fast project C++ Setup
Create your project setup quickly with this kind of command.
```sh
  -cb mkdir [?] [cb] cb [?] [cb] touch Makefile [cb] mkdir test [cb] mkdir -p src/header [cb] touch src/main.cc
```
```
 Here is how to use the command we just created: 
```
--> gif

## 📋 Features

![image](https://user-images.githubusercontent.com/53370597/165828252-2f91299f-fb96-4cb9-92ef-d506956f86e8.png)


## 💞 Acknowledgement
