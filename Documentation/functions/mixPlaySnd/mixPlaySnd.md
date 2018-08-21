% mixPlaySnd.c

---

### mixPlaySound()

Controls when to send sound data to a buffer for mixing and playing.

Note: the sound volume needs to be divided by 8 to insure there is no over amplification.

![](0.png)

Sound data is sent to mixSndTracks() where it is mixed and later seamlessly played with the help of two buffers in loadPlaySnd().

![](1.png) ![](2.png)

---

### endAllSound()

Controls when to stop all sound from playing.

---

### endSound()

Controls when to stop a specific sound from playing.

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

