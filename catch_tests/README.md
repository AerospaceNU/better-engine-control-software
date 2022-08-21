## Testing with Catch2

This folder contains our unit tests, which uses the
Catch2 framework.

If you want some reference materials:
- **Note:** We are not using the latest version of Catch2. Newer versions
  have abandoned the single-header include. As we do not
  currently need sophisticated features for our tests, we use the older
  single header-file due to its convenience
- [A pretty in-depth tutorial](https://mariusbancila.ro/blog/2018/03/29/writing-cpp-unit-tests-with-catch2/)
- [The official quick tutorial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md)
    - just ignore the "Getting Catch2" section because we are
      using the old versions
    - (in particular, pay attention to the Sections section because
  we use that a lot)


### Building Catch2 tests on Windows:
This assumes that your Windows setup is CLion + MSVC, as detailed
in the topmost README.

A tutorial for building and running Catch tests can be found at the
[official JetBrains documentation](https://www.jetbrains.com/help/clion/catch-tests-support.html)

//TODO: add more instructions if this is not detailed enough

### Building Catch2 tests on Linux/Unix
//TODO: lmao idk i dont have these
