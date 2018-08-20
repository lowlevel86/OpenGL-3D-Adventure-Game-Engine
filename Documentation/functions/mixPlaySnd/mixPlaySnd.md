% mixPlaySnd.c

---

### mixPlaySound()

Controls when to send sound data to a buffer for mixing and playing.

Note: the sound volume needs to be divided by 8 to insure there is no over amplification.

![](mixPlaySnd/0.png)

Sound data is sent to mixSndTracks() where it is mixed and later seamlessly played with the help of two buffers in loadPlaySnd().

![](mixPlaySnd/1.png) ![](mixPlaySnd/2.png)

---

### endAllSound()

Controls when to gently stop all sound from playing.

![](mixPlaySnd/3.png)

---

### endSound()

Controls when to gently stop a specific sound from playing.

![](mixPlaySnd/3.png)

---

### iniSndBuffs()

Allocates sound buffers and sets the sample rate.

---

### closeSndBuffs()

Frees memory used by the sound buffers.

---

### soundToDevice()

Sends sound for output.

---

[Back to Game Engine Functions](index.html)

