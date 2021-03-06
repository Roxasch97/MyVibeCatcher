# Round one!

## Brief

This time I was going to describe some difficulties with environment setup, and
 the way I decided to get over them, so maybe it will spare some blood and sweat
 to somebody, but it got a little bit long, so i decided to focus on one smaller
 parts of text.

>As you make your bed, so you must lie in it

## OS
So, as i wasn't too experienced in using Linux or other Unix-based systems,
I often make brakes in random moments of coding because I have to handle
something university-related (MS Office included) or I just want to play some
games with my friend, i think it wouldn't be comfortable to run a Linux as my
main OS. Generally i thought that i don't really need to use it ***YET***.

I couldn't be more wrong. Installing, and getting most of tools to work properly
on Windows is a pain in the you-know-what, and it it isn't for you, it's at
least less comfortable. I mean, seriously - don't do it if you don't have to.

## Why?

Because you have to search the web for every package you need, install it,
get disappointed because it has some prerequisites, those prerequisites throw
some errors in your face, because they has theirs too. You have those?
Oh! It's sad, and you know why? Because PATH! I know that you've
checked that sweet little "Add to PATH" check-box. It won't work anyway.
I spent one whole evening trying to get everything to work, got flustered,and
left it for another day, or whenever.

But hold your horses! Don't be like "Oh, FIIINE! I'll install that LINUX! And
I'll keep forgetting to change which OS i want to boot this time, and keep
 rebooting." You don't have to! Because there's some alternative that i have
 beloved. **B E L O V E D**, and it couldn't be named other way.

 ## Ta-tata taaa! WSL!

And if you google it, and you're polish, you'll be like "Whaaat? Wyższa Szkoła
Logistyki?!". And I'm in hurry with explanations: Nope.

I mean Windows Subsystem
for Linux, which is great way to use Linux as lazy windows-user, because you
get Linux command line with all its features, as window application, just like
in Cygwin etc. (Well... No, i don't know why i don't use Cygwin or mingw.)

Tl;dr, i recommend WSL because it is simple to get to work, installation is
mostly based on "next-next-next-agree-next", you don't have to fiddle with two
systems on boot, as I recall you can run various distributions of Linux on it,
i have chosen Ubuntu (it was recommended, and I'm not a Linux junkie, so i
don't get into the details of distributions).

***You want to use WSL, because:***

- Linux commonly used commercially, and if you get surprised by Linux in your
work, it won't look good *(been there, had to search the web even for "how to
change directory", and it was kind of embarrassing)*

- You don't have to search the web for tools sources, compile them, worry about
prerequisites and etc. Just type `sudo apt-get install /whatever/`, and in
most cases you're ready to go, or package manager will let you know that you
need *this* and *that* too

- You can run git, and all the other stuff in the same console. Which is pretty
handy, spares you extra window for git bash hanging around and making mess on
your screen

- It don't disrupt your daily routine and habits working with windows

- I won't make your girlfriend mad at you, because your PC automatically
boots to Linux and she can't find her The Sims 4 , or The Witcher, or whatever,
because of your freaky programming things

- Something could appear here later, if i find some more pro's

## Example of setup

To prove that it is really easy and comfy, I'd like to show you what does it take
to get all the apps that I'm using right now. I skip the windows part, which is
generally STM32 CubeIDE, and PyCharm (fun fact, you don't need python, you can
write in PyCharm and run those applications by WSL).

First of all, we want to update package information from all sources. Just to be
sure.

`sudo apt-get update`

Then, we want ***Development Tools***, which are extremely important, because it
contains general useful tools like GCC, g++, make, which are pre-requisites for
most of applications used by us.

`sudo apt-get install build-essential`

We are going to use Ceedling, which is Ruby-based (I'll write something about
Ruby too, later) framework, so we'll going to install Ruby:

`sudo apt-get install ruby`

We'd like to make sure we got it, right? Just type

`ruby --version`

And it should something like this:

`ruby 2.7.0p0 (2019-12-25 revision 647ee6f091) [x86_64-linux-gnu]`

Ceedling needs GCC, but we already got if with DevTools. So, let's get Ceedling!

`gem install ceedling`

Aaaand it's done! To make sure, you can type

`gem list ceedling`

We would like to get cppcheck too, right? This time it would be easier. Just
type:

`sudo apt-get install cppcheck`

Done! Noice! clang-format?

`sudo apt-get install clang-format`

 Done! Did I've forgotten something? I don't think so, but if I did, remember!

`sudo apt-get install what-i-have-forgotten`

And if it don't get found, you can easily find solution on Google, without
rummaging through 15 sites of stack overflow and etc.

Next time, I suppose I'm going to mumble a little bit about Ceedling, first
tests and this sort of things. And before you start to miss me, check those
 materials out!

## Bonus

[1st one](https://youtu.be/bTVIMt3XllM), is nicely explained MarkDown tutorial,
 which I enjoyed, and I think is enjoyable to watch while chilling.

 [2nd](https://www.youtube.com/watch?v=_51MXgwJj3g&t=4490s) is recording from
 [Maciek Gajdzica](https://ucgosu.pl/) live stream about TDD in embedded.
