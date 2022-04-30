#  📝Cpad

**Do you use several commands in your terminal, one after the other?** This tool allows you to combine **multiple templated** bash commands with the alias of your choice and many others.

## 👨🏽‍💻 Installation
### Prebuilt binaries
Download the binary depending on your configuration here: https://github.com/AmineZouitine/Cpad/releases

Then you just need to enter this command in your terminal:
```sh
tar -xf <downloaded_archive> cpad && sudo mv cpad /usr/local/bin
````
  
## ⚡️ Quick start

### Launch Cpad

To use **Cpad**, you must type in your terminal :
```sh
cpad
```

### 🌗 Enable/Disable emojis 
Emoji are great, but can cause display problems on someconfigurations.
To enable/disable cpad take positional arguments *(you only need to type it once, your preference will be saved)*.

🌕 **Enable**

```sh
cpad 1 
```

🌑 **Disable**

```sh
cpad 0
```
### Interesting examples of usage

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

![newgif-2022-04-29_18 22 00](https://user-images.githubusercontent.com/53370597/165984987-a9e0a7a2-6837-426c-8cae-70e3e5d8245e.gif)

### Fast project C++ Setup
Create your project setup quickly with this kind of command.
```sh
  -cb mkdir [?] [cb] cd [?] [cb] touch Makefile [cb] mkdir test [cb] mkdir -p src/header [cb] touch src/main.cc
```

**Here is how to use the command we just created:** 

![newproject-2022-04-29_18 33 07](https://user-images.githubusercontent.com/53370597/165987189-56cb58b4-0c32-4eff-916f-0f56af0e4a84.gif)


## 📋 Features

![image](https://user-images.githubusercontent.com/53370597/165990358-fbe50e30-a930-47ba-93c1-735f811cc45b.png)

## 👏🏼 Share your configuration with your friends

All your configuration is saved in the **.cpad** file in your home folder (Don't delete it or your configuration will be too).

What you should do:

```sh
cp ~/.cpad ~/my_cpad_configuration
```
What your friends should do

```sh
mv my_cpad_configuration ~/.cpad
```


## 💞 Acknowledgement

Thanks to [Paul-annet Renoux](https://github.com/DashPolo) and [Oceane Valat](https://github.com/oceane-vlt) for their great contributions on this project.

And to [Adil Zouitine](https://github.com/AdilZouitine), [Raphael Sourty](https://github.com/raphaelsty) and [Mehdi Zouitine](https://github.com/MehdiZouitine) for their precious advice.
