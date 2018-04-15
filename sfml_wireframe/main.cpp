#include <cmath>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

// Replacement for gluPerspective function.
void perspectiveGL(GLdouble, GLdouble, GLdouble, GLdouble);
void drawCube(void);

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(1024, 768), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    
    glEnable(GL_TEXTURE_3D);
    
    // load resources, initialize the OpenGL states, ...
    glMatrixMode(GL_PROJECTION);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glLoadIdentity();
    
    sf::Vector2u wsize = window.getSize();
    glViewport(0, 0, wsize.x, wsize.y);
    perspectiveGL(60, (float)wsize.x/(float)wsize.y, 0.1f, 512.f);
    
    
    
    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        
        
        // Activate the window before using OpenGL commands.
        // This is useless here because we have only one window which is
        // always the active one, but don't forget it if you use multiple windows
        window.setActive();
        
        // clear the buffers
        glClearColor(0.3f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // draw...
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        

        // draw...
        glMatrixMode(GL_TEXTURE_3D);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -5.f);

        drawCube();

        glPopMatrix();
        
        GLenum err = glGetError();
        
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    
    // release resources...
    
    return EXIT_SUCCESS;
}

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    
    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void drawCube()
{
    glBegin(GL_QUADS);      // Draw The Cube Using quads
    
    glColor3f(1.0f,1.0f,1.0f);  // Color White
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f( 1.0f, 1.0f,-1.0f);  // Top Right Of The Quad (Top)
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(-1.0f, 1.0f,-1.0f);  // Top Left Of The Quad (Top)
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Quad (Top)
    glNormal3f(0.f, 1.f, 0.f);
    glVertex3f( 1.0f, 1.0f, 1.0f);  // Bottom Right Of The Quad (Top)
    
    glColor3f(1.0f,1.0f,1.0f);  // Color White
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f( 1.0f,-1.0f, 1.0f);  // Top Right Of The Quad (Bottom)
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-1.0f,-1.0f, 1.0f);  // Top Left Of The Quad (Bottom)
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-1.0f,-1.0f,-1.0f);  // Bottom Left Of The Quad (Bottom)
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f( 1.0f,-1.0f,-1.0f);  // Bottom Right Of The Quad (Bottom)
    
    glColor3f(1.0f,1.0f,1.0f);  // Color White
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f( 1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Front)
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Front)
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(-1.0f,-1.0f, 1.0f);  // Bottom Left Of The Quad (Front)
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f( 1.0f,-1.0f, 1.0f);  // Bottom Right Of The Quad (Front)
    
    glColor3f(1.0f,1.0f,1.0f);  // Color White
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f( 1.0f,-1.0f,-1.0f);  // Top Right Of The Quad (Back)
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(-1.0f,-1.0f,-1.0f);  // Top Left Of The Quad (Back)
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f(-1.0f, 1.0f,-1.0f);  // Bottom Left Of The Quad (Back)
    glNormal3f(0.f, 0.f, -1.f);
    glVertex3f( 1.0f, 1.0f,-1.0f);  // Bottom Right Of The Quad (Back)
    
    glColor3f(1.0f,1.0f,1.0f);  // Color White
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Quad (Left)
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f, 1.0f,-1.0f);  // Top Left Of The Quad (Left)
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f,-1.0f,-1.0f);  // Bottom Left Of The Quad (Left)
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f(-1.0f,-1.0f, 1.0f);  // Bottom Right Of The Quad (Left)
    
    glColor3f(1.0f,1.0f,1.0f);  // Color White
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f( 1.0f, 1.0f,-1.0f);  // Top Right Of The Quad (Right)
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f( 1.0f, 1.0f, 1.0f);  // Top Left Of The Quad (Right)
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f( 1.0f,-1.0f, 1.0f);  // Bottom Left Of The Quad (Right)
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f( 1.0f,-1.0f,-1.0f);  // Bottom Right Of The Quad (Right)
    
    glEnd();          // End Drawing The Cube
}
