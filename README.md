# rrcal - Rational Root Calculator

<iframe width="560" height="315" src="https://www.youtube.com/embed/ES3OZJ8LiPQ?si=Cpn-nv3enpppuk7p" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

This is a tool to calculate rational roots of a polynomial equation. This tool does its job by applying the [Rational root theorem](#rational-root-theorem).

This program is developed entirely in C99. There are no dynamic allocations; everything is static and the program memory is completely predictable. Documentation of each function, macro and struct can be read in the header files inside the folder `include/`.

## Rational root theorem

> If the polynomial equation $a_{n} x^{n} + a_{n - 1} x^{n - 1} + ... + a_{0} = 0$ with integer coefficients $a_{i} \in \Z$ and $a_{0}, a_{n} \neq 0$ has a rational solution $x = \frac{p}{q}$ ($p$ and $q$ are relative prime), then the solution satisfies:
> - $p$ is an integer factor of $a_{0}$, and
> - $q$ is an integer factor of $a_{n}$.

For example, looking at the equation $x_{2} - 3x + 2 = 0$, in which $a_{0} = 2$ and $a_{2} = 1$, we can see a possible solution $\frac{p}{q}$ ($p$ and $q$ are relative prime) would satisfy: $p \in \{\pm 1, \pm 2\}$ and $q \in \{\pm 1\}$.

After testing for all possible values of $\frac{p}{q}$ efficiently, we would know every possible rational roots of the equation, regardless of its degree.

## Build from source

Compile the program with make (gcc is required):

```bash
make
```

The program would be compiled in seconds; the standalone executable file would be created at `build/bin/rrcal`.

The exhaustive list of pre-defined settings are presented in [`include/macros.h`](./include/macros.h). See the documentation in that file for more.

## API

> Before running anything, make sure you have the executable `rrcal` (or `rrcal.exe`) in the
> current working directory, or in the PATH variable. Nonetheless, you can
> access the executable with its absolute path. The executable is "standalone", which means you can move or copy it to anywhere you want.

To calculate rational roots of a polynomial equation (under the condition specified in the theorem), for instance, $x^{2} - x - 6 = 0$, simply run:

```bash
rrcal -6 -1 1
```

All rational roots of the polynomial specified by coefficients (sequentially from $a_{0}, a_{1}, ...$ to $a_{n}$) would be presented in readable form to the standard output.

Another example: $6x^3 - 29x^2 + 23x + 30 = 0$

```bash
rrcal 30 23 -29 6
```

## To-Do

* [x] Implement simple factorization.
* [x] Implement rational root hunter.
* [x] Parse arguments.
* [ ] Write unit tests.
* [ ] Write a simple UI.
