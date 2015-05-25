
#include <GL/glut.h>
#include <stdio.h>

//defining a RGB struct to color the pixel
struct Type_rgb{
       float r;
       float g;
       float b;
};

struct Type_rgb pixels[841*1440], pattern[999];

/*Find out if a given set belongs to the Mandelbrot or not
*Also assigns a pixel value using the iteration pattern
*/

void mandelbrotset()
{
/*
* x0 :- is the real part of c value
*       will range from -2.5 to 1.1.
* y0 :- is the imaginary part of c value
*       will range from -1 to 1.1.
*/

    float x0, y0, x, y, xtemp;
    int iteration, max_iteration, loc=0;
    for(y0 = -1; y0 < 1.1; y0 = y0 + 0.0025)
    for(x0 = -2.5; x0 < 1.1; x0 = x0 + 0.0025)
    {
        x = 0;
        y = 0;
        iteration = 0;
        max_iteration = 1000;
/*
* (x*x) + (y*y) < (2*2) is the 2nd bailout condition ie
* the mandelbrot set is always within a radius of 2.
*/
        while(((x*x) + (y*y) < (2*2)) && iteration < max_iteration)
        {
            xtemp = (x*x) - (y*y) + x0;
            y = (2*x*y) + y0;

            x = xtemp;
            iteration++;
        }
            if(iteration >= 999){
//If within the set, set color to black
     pixels[loc].r = 0;
     pixels[loc].g = 0;
     pixels[loc].b = 0;
}else{
//Else follow the iterations to set the color for the pixel
     pixels[loc].r = pattern[iteration].r;
     pixels[loc].g = pattern[iteration].g;
     pixels[loc].b = pattern[iteration].b;
}
loc = loc + 1;
}
}

void Init( )
{
    glViewport(0, 0, 1440, 841);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0, 1440, 0, 841);

    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1,1,1,1);

    i = 0;
    float r, g, b;

// Initializing all the pattern color till 9*9*9

   for(r = 0.1; r <= 0.9; r= r+0.1)
      for(g = 0.1; g <= 0.9; g = g+0.1)
         for(b = 0.1; b <= 0.9; b = b+0.1)
         {
                pattern[i].r = b;
                pattern[i].g = r;
                pattern[i].b = g;
                i++;
         }

// Set rest of the pattern colors as white since we need upto 1000

   for( ; i <= 999; i++)
   {
        pattern[i].r = 1;
        pattern[i].g = 1;
        pattern[i].b = 1;
   }

 //Once pattern is initialised, call the Mandelbrot set function
    mandelbrotset();

}

void onDisplay()
{
//Clear the buffer initially
   glClearColor(1, 1, 1, 0);
   glClear(GL_COLOR_BUFFER_BIT);

   glDrawPixels(1440, 841, GL_RGB, GL_FLOAT, pixels);
   glutSwapBuffers();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize (1440, 841);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Mandelbrot Set by Bhoomika");

    Init();
    glutDisplayFunc(onDisplay);
    glutMainLoop();
    return 0;
}
