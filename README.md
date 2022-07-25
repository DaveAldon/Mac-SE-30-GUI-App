<img src="resources/banner.png" width="100%">

This is an example of an app written in C for a Macintosh SE/30 v1.0 running System 6.0.8 - 7.1.

### Why?

<p float="left">
<img src="resources/example1.png" width="45%">
<img src="resources/example2.png" width="45%">
</p>

The Macintosh SE 30 v1.0 was the first computer I ever used growing up. It still works great, and I wanted to learn more about the development process people used almost 40 years ago. Applications made back then had to be lean and use resources as wisely as possible. Typically you're dealing with around 1-5mb of RAM, so programs have to carefully load in resources. 

I was also curious how much of my own knowledge could be transferred to this new domain for myself. I didn't want to learn HyperTalk, Logo, or Pascal right off the bat. I wanted to use C, which is still relevant today. How hard would it be to spin up an app built with C on a 40 year old computer? 

There are some key takeaways that immediately differentiate this sort of development from what I'm used to:

#### 1. There's no terminal

You do not have a command line interface in order to be a "power user." You have to use the GUI. Steve Jobs' vision for this type of machine included being able to, and *having* to use, the user interface in order to accomplish every task imaginable.

#### 2. The IDE options are limited

There are a couple major players to choose from, and I wanted to mention the ones I've tried, and which one I ultimately went with:

1. [Macintosh Programmer's Workshop](https://p2k.unibabwi.ac.id/IT/en/2821-2718/Apple's-MPW-C_11117_p2k-unibabwi.html) (MPW), created by Apple themselves. It provides a "think different" approach to development. More on that later.
2. [Code Warrior](https://en.wikipedia.org/wiki/CodeWarrior), created by Metrowerks, one of the first development platforms that supported both the Motorola 68k *and* PowerPC architectures. It was later known as **Classic IDE**, and then became what is more commonly know as **Eclipse**.
3. [THINK C](https://en.wikipedia.org/wiki/THINK_C), created by Think Technologies and then acquired by Symantec, was viewed as the **standard** environment for developers, as MPW was considered an overpriced niche product, and Code Warrior wouldn't come out until the 1990s.

##### A side note on MPW

MPW is a fascinating piece of software in itself. This was created by Apple as the primary software development tool of Macintosh. This program is as close to a terminal as you can get. The MPW Shell lets you run commands inside a giant text editor. It outputs the results as new lines directly below your command. You also have to use the **enter** key instead of the **return** key to invoke commands.

If you'd like to try experiencing this on a modern machine, [BBEdit](https://www.barebones.com/products/bbedit/) has a shell worksheet that you can use.

Although it was interesting, it wasn't "fun" to use. The CLI uses Pascal instead of Unix, and all of the 1980s books I could track down for MPW were written as though I should already have every library and program installed perfectly, and with all the right versions, and all the right included tutorial floppies. *Which I didn't.*

##### THINK C 

I abandoned MPW for its over-complexity, and Code Warrior because I could never get a compatible install for my system (it was made for a newer age, I think). But the one that stood out as a forward-thinking IDE was THINK C. It solved all my problems, and is a supreme example of what I would expect from the simplicity promised by the Macintosh.

THINK C does what it should do. You run it, make a project, and compile. No complex installs, no compatibility issues. It was made for my Macintosh.

### Requirements

So now that you know the **why**, and a little bit about the tools, let's break this project down in the same way that we would any modern project. Here's a list of requirements you'll need to follow along.

*All you have to do to install each of the programs is drag the files into a new folder. That's it!*

1. A Macintosh running System 6.0.8 through 7.1 (Other versions are untested, but they should work as this example is very simple)
2. I recommend a **32-bit Motorola 68020**. It's possible that a 68000 will work as well, but your mileage may vary, and some developer applications may not run
3. [THINK C](https://archive.org/download/think_c_5)
4. [ResEdit](https://www.macintoshrepository.org/1317-resedit-2-1-3), although THINK C should come with this in its Utilities folder. This is for creating/editing resource forks
5. [MacPaint](https://www.macintoshrepository.org/1912-macpaint-source-code), this is for drawing a picture we'll use in the app
6. [Stuffit Expander](https://www.macintoshrepository.org/1468-stuffit-expander-4-0-2), this is so that you can open any installer archives

##### Optional Stuff that makes things easier
1. [MPW](https://www.macintoshrepository.org/545-macintosh-programmer-s-workshop-mpw-3-x), the Shell worksheet can be useful if you want to automate anything
2. [MacApp](https://www.macintoshrepository.org/632-macapp-2-0), an extension for MPW that includes a lot of class libraries that can be helpful
3. [MultiFinder](https://en.wikipedia.org/wiki/MultiFinder), this allows you to run multiple apps side by side. If you want to use the THINK C debugger, this is necessary. This only matters if you're running anything below System 7. Anything higher includes this by default

### Getting Started

1. Make a new folder somewhere for your project files, and open THINK C, and go to Project -> New Project
2. Choose your new folder location and name your project whatever you like, and then go to Source -> Add. This is where we add our library dependencies
3. You need to add `MacTraps` (contains all of the GUI libraries we need) located in `THINK C 5.0 Folder` if you use the install linked from this repo, and `ANSI-small` in `C Libraries`. You can use the other `ANSI` files instead, but our app isn't very complicated, so it will keep the resources leaner in during development

<img src="resources/resources.png" width="75%">

4. With your project open, go to File -> New, and name it `main.c`, and then Edit -> Options -> Language Options, and change `Strict Prototype Enforcement` to `Require Prototypes` and hit `OK`

<img src="resources/prototypes.png" width="75%">

5. Open `MacPaint`, draw a **small** picture (if it's too big, it will take up too much memory, and we're not dealing with memory management here)

<img src="resources/macpaint.png" width="75%">

6. Use the `Select` tool and select a small area of the drawing, and hit `Command+C` to copy, or Edit -> Copy. You're safe to close the app now as long as the image is still in your clipboard

7. Open `ResEdit`, and navigate to your THINK C project folder. Then name your new ResEdit file with the same name as your project name, but with `.rsrc` at the end, and create it. So `<ProjectName>.rsrc`. This is so that the compiler can find and associate the resource with our project

8. With your new `.rsrc` file open, hit `Command+V` to paste, or Edit -> Paste. You'll see a `PICT` resource in the window. Open it and remember the number presented underneath your image. In this case, mine is `128`

<img src="resources/pict.png" width="75%">

9. Go back to your THINK C project. You should see the two libraries you added earlier, and your new `main.c` file. Double-click on `main.c` to open it

<img src="resources/dependancies.png" width="75%">

10. Add in the code from this repo's `main.c` file [here](https://github.com/DaveAldon/Mac-SE-30-GUI-App/blob/main/main.c)

11. Go to Project -> Run, and accept any requests to update the makefile or project, and wait for everything to compile

<img src="resources/run.png" width="75%">

12. If you get an `out of memory error`, you likely just need to shut down all other opened applications and windows. Remember, we're dealing with extremely small amounts of memory

<img src="resources/error.png" width="75%">

13. If everything went well, you should see a window with your image! The window is draggable, closable using the top left button, and if you drag the window so that it's partly off the screen and then bring it back, it will redraw itself!

<img src="resources/success.png" width="75%">

### What's Next

I added some documentation to the code to help explain what's going on, but there's a lot more to explore in the future. The app in this repo is very simple, and I would love to create guides on how to debug using THINK C, how to manage memory better, and how to create a more interactive GUI.

If you'd like to read about where the library references from this app come from and how to use them, I highly recommend checking out [this website](https://vintageapple.org/macprogramming/) which has hundreds of vintage Macintosh development books available. 

*Remember, with 40+ year old technology you can't expect to be able to Google all of your questions. Sometimes you just need to read a book written by the experts from that time period.*
