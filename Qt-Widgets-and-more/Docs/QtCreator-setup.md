# Re-setting up Qt Creator
QWAM has many different setup tips for Qt Creator. This document collect steps for re-setting up a new Qt Creator - as some of the things need to be re-setup for each new installation.

## Setup the spell checker
[QWAM episode - Spell Checking in Qt Creator](https://www.youtube.com/watch?v=3Dg5u1Mrj0I&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=9&t=344s)

These are usually the steps:

1. [Download the plugin](https://github.com/CJCombrink/SpellChecker-Plugin)
    * Take it from the *Releases* section, and check it matches your Qt Creator version
2. Copy the files to $QTDIR/Tools/QtCreator/
3. Restart Qt Creator, and check it appears in Help->About Plugins



## Setup the fonts - Jetbrains Mono
[QWAM episode - Changing the Font to Jetbrains Mono in Qt Creator](https://www.youtube.com/watch?v=iBbWbJo4Xpw&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=13&t=4s)

1. [go to website](https://www.jetbrains.com/lp/mono/)
2. Click the Download font
3. Click _How to install_ at the top and follow the steps
4. In Qt Creator, choose Tools->Options->TextEditor->Font & Colors
5. Choose JetBrains Mono



## Install your document templates
[QWAM episode - Document Templates in Qt Creator](https://www.youtube.com/watch?v=rX2jXRU8Qho&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=17&t=2s)

Likely in your source directory locate the install script, which will copy files over. [It might look like this one](https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/QtCreatorFileTemplates/install)



## Install your Qt Designer plugins
[QWAM episode - Qt Designer Plugins](https://www.youtube.com/watch?v=LGzNWFHUvpM&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=23&t=174s)

This likely requires no more than you compiling your source code, as the episode told you how to setup CMake for it to automatically install it.

There might be a chance you need to configure it in CMake though.



## Setup CPPreference in Qt Creator
[QWAM episode - Adding CPPreference to Qt Creator](https://www.youtube.com/watch?v=5ELbrOdRM2c&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=32&t=2s)

1. [Download the help bool](https://en.cppreference.com/w/Cppreference:Archives)
2. Go to Tools -> Options -> Help -> Documentation
3. Press Add, and choose the downloaded file.

## Ensuring your are setup with clang, ninja and ccache
[QWAM episode - Speeding Up Compilation Using CCache, Ninja and Clang](https://www.youtube.com/watch?v=cKedzwAWBC0&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=33&t=775s)

1. Check which kit you are using: **Tools** sidebar, check section **Build & Run**. Active kits are the ones _not_ grayed out.
2. Check your kit is correct: Tools -> Options -> Kits
    * Check C and C++ compiler points to something like:
    > **Clang** (C++, x86, 64bit in /usr/lib/**ccache**)
    * Check your CMake generator is set to **Ninja**
    
    

    
## Install Debugging Helpers
[QWAM episode - Writing Qt Creator Debugging Helpers](https://www.youtube.com/watch?v=mgBBT7aUNco&list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI&index=39&t=1579s)

You need to copy the .py file to the subdir share/qtcreator/debugger inside your qt creator sources.
If you haven't set up an install script yet, it might make sense to do so, have a look at [this file for inspiration](https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/debuggingHelper/install.sh)
    

   
