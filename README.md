# CPP Animator

> This application was adapted from a project in my Java-based OOD class that I used to practice creating applications in C++.

The CPP Animator reads in animation instructions from a text file and outputs an animation in various formats (`txt`, `svg`, and more to come...).

## Usage

```bash
usage: ./main -v <VIEW> -i <INFILE> [-o <OUTFILE>]
  VIEW = text | svg
  # if no outfile is specified, the output will be sent to stdout
```

## Animation `.txt` files

Animations are stored as human-readable/writable plain text animation instructions.

### Animation Instructions

There are currently three types of supported animation instructions:

1. [`canvas`](#canvas-instruction) - initialize the width and height of the animation's canvas
2. [`shape`](#shape-instruction) - declare a new shape to animate
3. [`keyframe`](#keyframe-instruction) - create a new keyframe for a declared shape

#### `canvas` Instruction

Used **only once** for initializing the width and height of the animation's canvas.
Any shape that appears outside of the canvas's bounds will not be visible.

```bash
canvas WIDTH HEIGHT # where WIDTH and HEIGHT are positive integers
```

#### `shape` Instruction

Declare a new shape to animate.
Must declare a shape before [creating keyframes](#keyframe-instruction) for it.

```bash
shape NAME TYPE # where NAME contains no whitespace, TYPE = rectangle | ellipse
```

#### `keyframe` Instruction

Create a new keyframe for a declared shape.
Must [declare a shape](#shape-instruction) before creating keyframes for it.
Keyframes for the same shape cannot share the same `TICK` value.

```bash
keyframe SHAPE_NAME TICK X_POS Y_POS WIDTH HEIGHT RED GREEN BLUE
# where SHAPE_NAME is the name of a declared shape,
#       TICK is a positive integer
#       RED, GREEN, BLUE are [0, 255]
```
