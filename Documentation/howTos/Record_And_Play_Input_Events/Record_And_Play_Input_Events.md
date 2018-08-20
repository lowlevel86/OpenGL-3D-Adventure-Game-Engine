% Record And Play Input Events

![](Record_And_Play_Input_Events/arcadeCabinet.png)

If you have noticed in an arcade, games automatically playing. This howto will show how it could be done.

---

Use this code to record input events and save to files.

**In main.c**

---

**Find:**

~~~ {.c}
// executes only just after startup
void afterStartup()
{

}
~~~

**And replace with:**

~~~ {.c}
#define REC 1
#define PLAY 2

int recOrPlay = REC;
char *readWriteAccess;
FILE *keyDownFilePtr;
FILE *keyUpFilePtr;
FILE *keyPressFilePtr;

// executes only just after startup
void afterStartup()
{
   if (recOrPlay == REC)
   readWriteAccess = "w+b";
   
   if (recOrPlay == PLAY)
   readWriteAccess = "r+b";
   
   if (recOrPlay)
   {
      keyDownFilePtr = fopen("keyDown.dat", readWriteAccess);
      keyUpFilePtr = fopen("keyUp.dat", readWriteAccess);
      keyPressFilePtr = fopen("keyPress.dat", readWriteAccess);
   }
}
~~~

---

**Find:**

~~~ {.c}
// executes just before shutdown
void beforeShutdown()
{

}
~~~

**And replace with:**

~~~ {.c}
// executes just before shutdown
void beforeShutdown()
{
   if (recOrPlay)
   {
      fclose(keyPressFilePtr);
      fclose(keyUpFilePtr);
      fclose(keyDownFilePtr);
   }
}
~~~

---

**Find:**

~~~ {.c}
   #include "initialize.c"
~~~

**And replace with:**

~~~ {.c}
   #include "initialize.c"
   
   if (recOrPlay == REC)
   {
      eventRecToFile((void **)keyDown, 256, keyDownFilePtr);
      eventRecToFile((void **)keyUp, 256, keyUpFilePtr);
      eventRecToFile((void **)keyPress, 256, keyPressFilePtr);
   }
   
   if (recOrPlay == PLAY)
   {
      eventPlayFromFile((void **)keyDown, 256, keyDownFilePtr);
      eventPlayFromFile((void **)keyUp, 256, keyUpFilePtr);
      eventPlayFromFile((void **)keyPress, 256, keyPressFilePtr);
   }
~~~

---

Compile and run.

---

---

Use this code to play input events that were saved to files.

---

**Find:**

~~~ {.c}
int recOrPlay = REC;
~~~

**And replace with:**

~~~ {.c}
int recOrPlay = PLAY;
~~~

---

Compile and run.

---

This can be setup to replay exactly the same over and over which makes it useful for debugging.

---

[Back to Game Engine HowTos](index.html)

