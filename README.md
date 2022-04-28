# Cpad

**Do you use several commands in your terminal, one after the other ?** This tool allows you to combine **multiple templated** bash commands with the alias of your choice.

## 👨🏽‍💻 Installation
### Prebuilt binaries
  #### ⭐️ Beautiful version (It may have some issues if you don't have the right fonts) 
  
  #### 🪶 Solf version
  
## ⚡️ Quick start

In these examples, you will discover the following elements: : **-cb** **[cb]** **[?]**.
They are explained in the features section, but quickly :

**-cb** - Allows you to create a combo command.

**[cb]** - Is the separator between the commands

**[?]** - Is a template allowing the user to give a custom argument

### Fast push on Github
Add files to a commit, set a commit message, see the changes in your repository. Push your changes to the branch of your choice.
```sh
  -cb git add [?] [cb] git status [cb] git commit -m "[?]" [cb] git push origin [?] [cb] git checkout main
```


 **Here is how to use the command we just created:**

![final-2022-04-28_23 26 38](https://user-images.githubusercontent.com/53370597/165849013-3814ea42-bf85-4e0f-a7ba-197344c9b8b2.gif)

### Fast project C++ Setup
Create your project setup quickly with this kind of command.
```sh
  -cb mkdir [?] [cb] cd [?] [cb] touch Makefile [cb] mkdir test [cb] mkdir -p src/header [cb] touch src/main.cc
```

**Here is how to use the command we just created:** 

## 📋 Features

![image](https://user-images.githubusercontent.com/53370597/165828252-2f91299f-fb96-4cb9-92ef-d506956f86e8.png)


## 💞 Acknowledgement

Thanks to [Paul-annet Renoux](https://github.com/DashPolo) and [Oceane Valat](https://github.com/oceane-vlt) for their great contributions on this project.

And to [Raphael Sourty](https://github.com/raphaelsty), [Adil Zouitine](https://github.com/AdilZouitine) and [Mehdi Zouitine](https://github.com/MehdiZouitine) for their precious advice.
