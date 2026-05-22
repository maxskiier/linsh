LINSH - The Linux Shell
=======================

First things first, this is not endorsed by Linus Torvalds, The Linux
Foundation, or anybody associated with Linux. This is my passion project. With
that being noted let me get into it.

I'm working this for a couple of reasons. Obviously we all work on something
for any reason but here's my personal list.

1. I like coding.
2. I want to learn more about interactivity with the user.
3. I'm a massochist.

Another big reason that I'm making this is because I'm writing a lot of
software that uses git, and it can be rather annoying to type:

maxd@mypc ~/Software % git commit -s
maxd@mypc ~/Software % git format-patch -1

all the time. So basically, the point is, I want to make my workflow more
efficient. Anyways have fun.

============
Coding Style
============

We use the Linux Kernel Coding Standards, which is the main style guide for the
Linux Kernel. It can be found at docs.kernel.org/process/coding-style.html.

==============
Git Operations
==============

I don't really care how you get your changes to me (so either via GitHub web
interface or via patch-email), so long as it follows these conventions:

------------------------------
1. Descriptive commit message.
------------------------------

Don't send me something like:

"yo broski

hey broski i tried idk"

Send me a thorough list of changes you're making (but don't be obnoxious about
it).

------
2. DCO
------

We use the DCO (aka the Developer's Certificate of Origin) on all commits to
linsh. That means, you are _REQUIRED_ to sign-off all of your commits in the
following format:

Signed-off-by: Jonathan Bringus <jon@bringleman.com>

Here's a break down:

Signed-off-by: first-name (middle-name if you want) last-name <email>

This goes for everyone who handled the patch as well.

----------------------------
3. Separate logical changes.
----------------------------

While this one may have been broken in old commits, it's important that it gets
established now so if we ever need to bisect for a commit that caused an issue,
we can easily find it. It also keeps the history tidy!
