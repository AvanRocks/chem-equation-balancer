# Chemical Equation Balancer
A Program that balances chemical equations by mass

## Build

To compile the program (written in C++), you will need a c++ compiler (like g++). You will then need to compile the bal.cpp file and the Matrix.cpp file at the same time in order for the linker to work properly.

## Linux

If you are on Linux (or Mac, but I haven't tested it) run the following command to compile:

```
$ g++ bal.cpp Matrix.cpp -o bal
```

You may replace the `-o bal` with another filename for the executable. For example `-o balance`.

Then, move the executable into a directory in your $PATH, and it is ready to use.

## Windows / Mac

Compile it as you would compile any other c++ program. Note that bal.cpp uses Matrix.h header file (with definitions in Matrix.cpp) so link appropriately. If you don't know how to do this, simply use an IDE.


## Usage

Run the executable with no arguments.

Then type the chemical equation you wish to balance, keeping a few things in mind:

- Elements with 1 letter must be capital

- Elements with 2 letters must have their first letter capital and second letter lowercase

- Use an equal sign (not an arrow) to seperate the reactants and products

- Subscripts can be indicated with an underscore, (`Cl_2`) or without (`Cl`), it doesn't matter

- Seperate compounds with a plus sign (`+`)

- Replace unchanging polyatomic ions with another capital letter when inputting. For ex. replace `SO_4` with `Z`.

Any other characters you add besides letters, numbers, `=`, `_`, and `+` will be ignored.

If it is possible to balance the equation, the program will output the balanced equation. If not, it will throw an error.

If you get an error, try simplifying the equation by cancelling same terms on both sides and substituting for immutable polyatomic ions.
