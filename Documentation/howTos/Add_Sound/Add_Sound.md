% Add Sound

This howto will add sound to the 4th scene and play each time the left mouse button is pressed.

You will need to compile wavToC from the "Tools" folder and place it in the "sounds" folder.  
Go into the "sounds" folder open a terminal and type:  
**wavToC shoot.wav**  

This should convert the .wav file into source code.

---

**In main.c**

---

**Add under the includes:**

~~~ {.c}
#include "sounds/shootSndData.h"
~~~

---

**In scene4.c**

---

**Find:**

~~~ {.c}
if (leftMouseDown)
{
~~~

**And replace with:**

~~~ {.c}
if (leftMouseDown)
{
   mixPlaySound(shootSndData, sizeof(shootSndData), FALSE, TRUE);// you can play with the TRUE, FALSE values
~~~

---

**Find:**

~~~ {.c}
if (rightMouseClick)
{
~~~

**And replace with:**

~~~ {.c}
if (rightMouseClick)
{
   endSound(shootSndData);
~~~

---

---

The compiler needs to be told to compile the sound data.

To compile with gcc:

**In Makefile.win**

---

**Find:**

~~~ {.c}
sounds\boomSndData.o
~~~

**And replace with:**

~~~ {.c}
sounds\boomSndData.o sounds\shootSndData.o 
~~~

---

To compile with tcc:

**In tmake.bat**

---

**Find:**

~~~ {.c}
sounds\boomSndData.o
~~~

**And replace with:**

~~~ {.c}
sounds\boomSndData.o sounds\shootSndData.o 
~~~

---

**Find:**

~~~ {.c}
if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc
~~~

**And replace with:**

~~~ {.c}
if NOT exist sounds\shootSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\shootSndData.c -o sounds\shootSndData.o

if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc
~~~

---

Compile and run.

Press enter 4 times to see the results in the 4th scene.

---

