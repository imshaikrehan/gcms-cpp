# Galactic Cargo Management System (GCMS)

So, I got tired of how messy interstellar logistics can get, especially when you're trying to figure out which bin fits that one weirdly shaped hyper-battery. This is GCMS—a C++ project I put together to handle the heavy lifting of cargo management without the usual headaches.

It uses some pretty solid data structures (AVL trees, mostly) to make sure everything stays fast and balanced, even when you're tracking thousands of items across different sectors.

## Why this exists

If you've ever had to manage storage bins across a nebula, you know the drill. You need a system that doesn't just find a spot, but finds the right spot based on how you like to pack. I've built in a few different search protocols to handle that:

- Blue Protocol: For when you want the tightest fit possible (compact least).
- Yellow Protocol: For those who like a bit of breathing room (compact greatest).
- Red/Green Protocols: For when you just need the biggest bin on the deck (largest least/greatest).

## Getting it running

It's pretty straightforward. Just throw it at a C++ compiler and you're good to go.

### Compile
I usually use g++ for this. Run this in your terminal:

```bash
g++ -o gcms_control main.cpp Bin.cpp GCMS.cpp -I.
```

### Run
Once it's built, just fire it up:

```bash
./gcms_control
```

## What's under the hood

- GCMS.h/cpp: The core logic. It manages the trees for objects and bins.
- Bin.h/cpp: Represents the actual containers. I used shared pointers here so the different trees can track the same bin data without making a mess of memory.
- AVLTree.h: The template I wrote for the balanced trees. It handles all the rotations and specific search logic.
- Object.h: A simple class for the items you're storing.
- Exceptions.h: Basic error handling for when an object just won't fit.

---
Hope this helps keep your cargo organized. Safe travels.
