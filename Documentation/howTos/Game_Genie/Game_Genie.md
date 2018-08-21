% Game Genie

![](genie.png)

---

**In scene1.c**

---

### Float

Allow the character to float.  

---

**Find:**

~~~ {.c}
zCtrlForce = -fallSpeed;
~~~

**And replace with:**

~~~ {.c}
if (jumpUp)
fallSpeed = gravity_force;

zCtrlForce = -fallSpeed;
~~~

---

Compile and run.

---

---

### Fly

Allow the character to fly when the 'Z' key is pressed.  

---

**Find:**

~~~ {.c}
zCtrlForce = -fallSpeed;
~~~

**And replace with:**

~~~ {.c}
if (keyDown[90])// Z
{
   jumpUp = TRUE;
   fallSpeed = -gravity_force;
}

zCtrlForce = -fallSpeed;
~~~

---

Compile and run.

---

---

**In initialize.c**

---

### Mushroom

Make the character larger.  

---

**In initialize.c**

**Find:**

~~~ {.c}
   copyTransFromTo(&character_TRANS[0], &character_STATICTRANS[0], character_MESHCNT);
~~~

**And replace with:**

~~~ {.c}
   globalResize(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 3, 3, 3);
   globalResize(&run1_TRANS[0], run1_MESHCNT, 0, 0, 0, 3, 3, 3);
   globalResize(&run2_TRANS[0], run2_MESHCNT, 0, 0, 0, 3, 3, 3);
   globalResize(&run3_TRANS[0], run3_MESHCNT, 0, 0, 0, 3, 3, 3);
   globalResize(&run4_TRANS[0], run4_MESHCNT, 0, 0, 0, 3, 3, 3);
   globalResize(&jump_TRANS[0], jump_MESHCNT, 0, 0, 0, 3, 3, 3);
   globalResize(&liftUp_TRANS[0], liftUp_MESHCNT, 0, 0, 0, 3, 3, 3);
   
   copyTransFromTo(&character_TRANS[0], &character_STATICTRANS[0], character_MESHCNT);
~~~

---

Compile and run.

---

---

### Bigger Blasts

Increase the blast size for the tanks.  

---

**In initialize.c**

**Find:**

~~~ {.c}
   // resize meshes
   globalResize(&arena_TRANS[0], arena_MESHCNT, 0, 0, 0, 20, 20, 20);
~~~

**And replace with:**

~~~ {.c}
   // resize meshes
   globalResize(&arena_TRANS[0], arena_MESHCNT, 0, 0, 0, 20, 20, 20);
   globalResize(&arena_TRANS[arena_explodeYellow*TRSZ], 1, 0, 0, 0, 3, 3, 3);
~~~

---

Compile and run.

---

---

