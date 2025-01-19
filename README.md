# SVGebra

An immediate mode library to generate SVG files with basic shapes and functions.
This was orignally a school assignment, but i decided to improve it further.<br>
Because of this, the library is only written in italian.

## Functionalities

This library can render simple primitive shapes like triangles or circles to
more complicated functions such as parabolas in a cartesian coordinate plane.

## Example

```cpp
#include "svgebra.h"

int main(void)
{
    // Start of SVG image
    svg_inizio(800, 800);

    // Render the cartesian plane and setup the right coordinate system
    svg_piano_cartesiano_inizio();

    // Linear equation variables (y = m*x + q)
    float m = 2.0f;
    float q = 3.0f;

    // Parabola's variables (y = a*x*x + b*x + c)
    float a = -2.0f;
    float b =  5.0f;
    float c =  4.5f;

    svg_retta(m, q); // Render a linear function
    svg_parabola(a, b, c); // Render a parabola

    // Reset settings and coordinates system
    svg_piano_cartesiano_fine();

    // End of image
    svg_fine();

    return 0;
}
```

To render the example:

```bash
$ make && ./libsvgebra > example.svg
```
