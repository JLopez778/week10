# DESCRIPTION #


Week 10 Solution - Adding Bullet and Bullet Manager. 

**Note:** A lot of minor bugs with this weeks additions turned into a much larger undertaking as there some bugs introduced in earlier solutions. 

|Operating System|SDL2 Version|SDL2\_image Version|Status|
|:--|---|---|:-:|
|Linux|2.20.11|2.8.4|**DONE**|
|Windows|2.20.11|2.8.4|**DONE**| 

# INSTRUCTIONS #

At present I'm maintaining a version for Command Line Linux and Visual Studio 2022 only, if other versions are required let me know and I'll set them up.  

The build environment on Windows takes a bit of setting up if you want to do it all yourself, however, I will provide a video detailing the setup process for anyone who wants to setup their project from scratch. 

## Visual Studio 2022 ##
   
There should be no additional steps, a post-build process will copy the required dll files and the content of ```assets/images``` to the output directory and the debugger is set to run from there.  

## Linux ##

Make sure you have the these packages installed:
```
sdl2
sdl2-devel
sdl2_image
sdl2_image-devel
```

Package names may vary on other flavours of Linux (these are the Fedora ones). 

1. Open a terminal in the Linux folder (or via MS Code)
2. Compile ```make``` 
3. Run ```./test```

Debugging via gdb is possible but painful, consider using an editor if required. 


 
