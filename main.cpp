#include<windows.h>
#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "imageloader.h"

using namespace std;
//HATIRJILL PROJECT
//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
    }
}


//loadTexture function takes an Image object and returns a GLuint (which is kind of like an unsigned int) giving the id that OpenGL assigned to the texture.
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image)
{
    GLuint textureId;

    //The first argument is the number of textures we need, and the second is an array where OpenGL will store the id's of the textures.
    glGenTextures(1, &textureId); //Make room for our texture
    // to assign the texture id to our image data.
//	We call glBindTexture(GL_TEXTURE_2D, textureId) to let OpenGL know
// that we want to work with the texture we just created. Then, we call glTexImage2D to load the image into OpenGL.
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;

//Initializes 3D rendering
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    //you can have upto 8 lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading

    //Take a look at imageloader.h. This gives us the basic idea of what loadBMP does.
    //(The actual code for loadBMP is in imageloader.cpp.) Given a filename, it returns an Image object,
    //which contains the width and height of the image, as well as the array pixels,
    //which stores the pixels' colors in the format we want.
    Image* image = loadBMP("C:\\Users\\sajid\\Desktop\\Hatijheel\\water.bmp");

    Image* image1 = loadBMP("C:\\Users\\sajid\\Desktop\\Hatijheel\\sky.bmp");

    Image* image2 = loadBMP("C:\\Users\\sajid\\Desktop\\Hatijheel\\grass.bmp");

    Image* image3 = loadBMP("C:\\Users\\sajid\\Desktop\\Hatijheel\\wall.bmp");

    Image* image4 = loadBMP("C:\\Users\\sajid\\Desktop\\Hatijheel\\sample1.bmp");

    //Once we've got the image, we have to send it to OpenGL. We do this in a function we write called loadTexture.
    _textureId = loadTexture(image);
    _textureId1 = loadTexture(image1);
    _textureId2 = loadTexture(image2);
    _textureId3 = loadTexture(image3);
    _textureId4 = loadTexture(image4);
    //Note that we should only use images whose widths and heights are 64, 128, or 256, since computers like powers of 2.
//	Other sizes of images might not work properly.
    delete image;
    delete image1;
    delete image2;
    delete image3;
    delete image4;


}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = -70.0f;

//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -8.0f);

    //Add ambient light
    //sh that shines everywhere in our scene by the same amount
    //every face gets the same amount
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2) and intensity //can be greater than 1 so not like color
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    // 0 because direced light source
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    glRotatef(_angle, 0.0f, 1.0f, 0.0f);


    //test for texture starts here

    //water codes are here

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    //Bottom

    //The first call tells OpenGL to use the blocky mapping (GL_NEAREST)
//	when the texture is far away from us, and the second call tells it to use blocky mapping when the texture is close.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // blurry mapping, we'd pass GL_LINEAR as the third parameter of these two functions.
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //Now, in addition to a normal vector, each vertex has a texture coordinate.
    //The texture coordinates indicates to what point on the image each vertex maps.
    //The texture coordinate (a + b, c + d), where a and c are integers,
//	indicates the spot that is the fractional amount b above the bottom of the texture
// and the fractional amount d right of the left of the texture.
// To specify the texture coordinates of a vertex, we simply call glTexCoord2f with the texture coordinates we want before calling glVertex3f for the vertex.

    //floorside
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.9f, -2.0f, 15.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.9f, -2.0f, 15.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(5.9f, -2.0f, -15.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.9f, -2.0f, -15.5f);

    glEnd();

    //water code end
    //---------------------------------------------------------------------

    //waterside grass code starts

    //1st part
    //right part

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.21f, -0.551f, 35.5f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(-4.8f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(-4.8f, -2.5f, -35.5f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-5.21f, -0.551f, -35.5f);

    glEnd();

    //upper part road

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 1.0f, 1.0f);
    glVertex3f(-5.11f, -0.551f, 35.5f);
    glVertex3f(-6.0f, -0.551f, 35.5f);
    glVertex3f(-6.0f, -0.551f, -35.5f);
    glVertex3f(-5.11f, -0.551f, -35.5f);

    glEnd();

    //left part grass

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.0f, -0.551f, 35.5f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(-6.0f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(-6.0f, -2.5f, -35.5f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-6.0f, -0.551f, -35.5f);

    glEnd();

    //lower part grass


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.0f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(-4.8f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(-4.8f, -2.5f, -35.5f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-6.0f, -2.5f, -35.5f);

    glEnd();

    //----------------------------------------------------

    //two extra parts to fill the gap

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.0f, -2.5f, 3.9f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(-4.8f, -2.5f, 3.9f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(-5.2f, -0.551f, 3.9f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-6.0f, -0.551f, 3.9f);

    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.0f, -2.5f, -3.9f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(-4.8f, -2.5f, -3.9f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(-5.2f, -0.551f, -3.9f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(-6.0f, -0.551f, -3.9f);

    glEnd();

    //upper slope part 1

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.0f, -0.551f, 35.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-6.0f, -0.551f, 5.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(-8.5f, 3.4f, 5.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-8.5f, 3.4f, 35.0f);

    glEnd();



    //upper slope part 2

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.0f, -0.551f, -4.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-6.0f, -0.551f, -35.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(-8.5f, 3.4f, -35.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-8.5f, 3.4f, -4.5f);

    glEnd();



    //upper slope part 1 updated

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-14.0f, -0.551f, 35.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-14.0f, -0.551f, 5.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(-10.5f, 3.4f, 5.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-10.5f, 3.4f, 35.0f);

    glEnd();


    //upper slope part 2 updated

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-14.0f, -0.551f, -4.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-14.0f, -0.551f, -35.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(-10.5f, 3.4f, -35.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-10.5f, 3.4f, -4.5f);

    glEnd();


    //left side upper slope road code starts here

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-8.5f, 3.4f, 35.5f);
    glVertex3f(-8.5f, 3.4f, -35.5f);
    glVertex3f(-10.5f, 3.4f, -35.5f);
    glVertex3f(-10.5f, 3.4f, 35.5f);

    glEnd();

    //left side upper slope road code starts here

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-8.5f, 3.2f, 35.5f);
    glVertex3f(-8.5f, 3.2f, -35.5f);
    glVertex3f(-10.5f, 3.2f, -35.5f);
    glVertex3f(-10.5f, 3.2f, 35.5f);

    glEnd();

    //left side upper slope road code starts here

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-8.5f, 3.2f, 35.3f);
    glVertex3f(-8.5f, 3.4f, -35.3f);
    glVertex3f(-10.5f, 3.4f, -35.3f);
    glVertex3f(-10.5f, 3.2f, 35.3f);

    glEnd();


    //2nd part

    //right part

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.1f, -0.551f, 35.5f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(5.7f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(5.7f, -2.5f, -35.5f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(6.1f, -0.551f, -35.5f);

    glEnd();

    //upper part

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 1.0f, 1.0f);
    glVertex3f(6.1f, -0.55f, 35.5f);
    glVertex3f(6.9f, -0.55f, 35.5f);
    glVertex3f(6.9f, -0.55f, -35.5f);
    glVertex3f(6.1f, -0.55f, -35.5f);

    glEnd();

    //left part

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.9f, -0.551f, 35.5f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(6.9f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(6.9f, -2.5f, -35.5f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(6.9f, -0.551f, -35.5f);

    glEnd();

    //lower part

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.9f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(5.7f, -2.5f, 35.5f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(5.7f, -2.5f, -35.5f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(6.9f, -2.5f, -35.5f);

    glEnd();

    //two extra parts to fill the gap

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.1f, -0.551f, 3.9f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(6.9f, -0.551f, 3.9f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(6.9f, -2.5f, 3.9f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(5.7f, -2.5f, 3.9f);

    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.9f, -2.5f, -3.9f);
    glTexCoord2f(10.0f, 0.0f);
    glVertex3f(5.7f, -2.5f, -3.9f);
    glTexCoord2f(10.0f, 10.0f);
    glVertex3f(6.1f, -0.551f, -3.9f);
    glTexCoord2f(0.0f, 10.0f);
    glVertex3f(6.9f, -0.551f, -3.9f);

    glEnd();


    //upper slope part 1 right

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.9f, -0.551f, 35.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(6.9f, -0.551f, 5.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(9.4f, 3.4f, 5.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(9.4f, 3.4f, 35.0f);

    glEnd();



    //upper slope part 1 right updated

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(13.4f, -0.551f, 35.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(13.4f, -0.551f, 5.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(11.4f, 3.4f, 5.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(11.4f, 3.4f, 35.0f);

    glEnd();


    //upper slope part 2 right updated

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(13.4f, -0.551f, -4.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(13.4f, -0.551f, -35.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(11.4f, 3.4f, -35.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(11.4f, 3.4f, -4.5f);

    glEnd();



    //upper slope part 2 right

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.9f, -0.551f, -4.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(6.9f, -0.551f, -35.0f);
    glTexCoord2f(5.0f, 5.0f);
    glVertex3f(9.4f, 3.4f, -35.0f);
    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(9.4f, 3.4f, -4.5f);

    glEnd();


    //right side upper slope road code starts here

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(9.4f, 3.4f, 35.5f);
    glVertex3f(9.4f, 3.4f, -35.5f);
    glVertex3f(11.4f, 3.4f, -35.5f);
    glVertex3f(11.4f, 3.4f, 35.5f);

    glEnd();

    //right side upper slope road code starts here

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(9.4f, 3.2f, 35.5f);
    glVertex3f(9.4f, 3.2f, -35.5f);
    glVertex3f(11.4f, 3.2f, -35.5f);
    glVertex3f(11.4f, 3.2f, 35.5f);

    glEnd();

    //right side upper slope road code starts here

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(9.4f, 3.2f, 35.3f);
    glVertex3f(9.4f, 3.4f, -35.3f);
    glVertex3f(11.4f, 3.4f, -35.3f);
    glVertex3f(11.4f, 3.2f, 35.3f);

    glEnd();


    //waterside grass code endss
    //----------------------------------------------------------------------

    //sky code starts here

    //uppersky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.2f, 35.0f, 35.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(36.1f, 35.0f, 35.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(36.1f, 35.0f, -30.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.2f, 35.0f, -30.5f);

    glEnd();

    //leftsky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.2f, 55.0f, 65.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-35.2f, -35.0f, 65.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-35.2f, -35.0f, -60.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.2f, 55.0f, -60.5f);

    glEnd();


    //rightsky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(36.1f, 55.0f, 65.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(36.1f, -35.0f, 65.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(36.1f, -35.0f, -60.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(36.1f, 55.0f, -60.5f);

    glEnd();


    //backsky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(36.1f, 55.0f, -60.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(36.1f, -35.0f, -60.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.2f, -35.0f, -60.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.2f, 55.0f, -60.5f);

    glEnd();


    //frontsky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(36.1f, 55.0f, 65.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(36.1f, -35.0f, 65.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.2f, -35.0f, 65.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.2f, 55.0f, 65.5f);

    glEnd();


    //sky code ends here

    //test for texture ends here


    //piller1_front_leftpart
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-5.2f, -0.5f, 2.5f);
    glVertex3f(-3.5f, 1.5f, 2.5f);
    glVertex3f(-3.0f, 1.5f, 2.5f);
    glVertex3f(-4.8f, -0.5f, 2.5f);

    glEnd();

    //piller1_front_leftpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-3.0f, 1.5f, 2.5f);
    glVertex3f(-4.8f, -0.5f, 2.5f);
    glVertex3f(-4.8f, -0.5f, 2.1f);
    glVertex3f(-3.0f, 1.5f, 2.1f);

    glEnd();

    //piller1_front_leftpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-3.0f, 1.5f, 2.1f);
    glVertex3f(-4.8f, -0.5f, 2.1f);
    glVertex3f(-5.2f, -0.5f, 2.1f);
    glVertex3f(-3.5f, 1.5f, 2.1f);

    glEnd();

    //piller1_front_leftpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-5.2f, -0.5f, 2.1f);
    glVertex3f(-3.5f, 1.5f, 2.1f);
    glVertex3f(-3.5f, 1.5f, 2.5f);
    glVertex3f(-5.2f, -0.5f, 2.5f);

    glEnd();

    //--------------------------------------------------------------------------
    //piller1_front_rightpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-1.5f, -0.5f, 2.5f);
    glVertex3f(-3.0f, 1.5f, 2.5f);
    glVertex3f(-3.0f, 1.5f, 2.1f);
    glVertex3f(-1.5f, -0.5f, 2.1f);

    glEnd();


    //piller1_front_rightpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-1.5f, -0.5f, 2.1f);
    glVertex3f(-3.0f, 1.5f, 2.1f);
    glVertex3f(-3.35f, 1.128f, 2.1f);
    glVertex3f(-2.0f, -0.5f, 2.1f);

    glEnd();


    //piller1_front_rightpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-3.35f, 1.128f, 2.1f);
    glVertex3f(-2.0f, -0.5f, 2.1f);
    glVertex3f(-2.0f, -0.5f, 2.5f);
    glVertex3f(-3.35f, 1.128f, 2.5f);

    glEnd();

    ////piller1_front_rightpartcode
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.35f, 1.128f, 2.5f);
    glVertex3f(-3.0f, 1.5f, 2.5f);
    glVertex3f(-1.5f, -0.5f, 2.5f);
    glVertex3f(-2.0f, -0.5f, 2.5f);

    glEnd();

    //----------------------------------------------------------------------------


    //piller1_front_upperpartcode
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.5f, 2.5f);
    glVertex3f(-3.0f, 1.5f, 2.5f);
    glVertex3f(-3.0f, 1.9f, 2.5f);
    glVertex3f(-3.5f, 1.9f, 2.5f);

    glEnd();

    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.0f, 1.5f, 2.5f);
    glVertex3f(-3.0f, 1.9f, 2.5f);
    glVertex3f(-3.0f, 1.9f, 2.1f);
    glVertex3f(-3.0f, 1.5f, 2.1f);

    glEnd();

    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.0f, 1.9f, 2.1f);
    glVertex3f(-3.0f, 1.5f, 2.1f);
    glVertex3f(-3.5f, 1.5f, 2.1f);
    glVertex3f(-3.5f, 1.9f, 2.1f);

    glEnd();

    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.5f, 2.1f);
    glVertex3f(-3.5f, 1.9f, 2.1f);
    glVertex3f(-3.5f, 1.9f, 2.5f);
    glVertex3f(-3.5f, 1.5f, 2.5f);

    glEnd();


    //-----------------------------------------------------------------------

    //piller1_back-LEFTPART
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-5.2f, -0.5f, -2.0f);
    glVertex3f(-3.5f, 1.5f, -2.0f);
    glVertex3f(-3.0f, 1.5f, -2.0f);
    glVertex3f(-4.8f, -0.5f, -2.0f);


    glEnd();

    //piller1_back_leftpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-3.0f, 1.5f, -2.0f);
    glVertex3f(-4.8f, -0.5f, -2.0f);
    glVertex3f(-4.8f, -0.5f, -2.4f);
    glVertex3f(-3.0f, 1.5f, -2.4f);

    glEnd();

    //piller1_back_leftpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-3.0f, 1.5f, -2.4f);
    glVertex3f(-4.8f, -0.5f, -2.4f);
    glVertex3f(-5.2f, -0.5f, -2.4f);
    glVertex3f(-3.5f, 1.5f, -2.4f);

    glEnd();

    //piller1_back_leftpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-5.2f, -0.5f, -2.4f);
    glVertex3f(-3.5f, 1.5f, -2.4f);
    glVertex3f(-3.5f, 1.5f, -2.0f);
    glVertex3f(-5.2f, -0.5f, -2.0f);

    glEnd();


    //--------------//backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.0f, 1.9f, -2.4f);
    glVertex3f(-3.0f, 1.5f, -2.4f);
    glVertex3f(-3.5f, 1.5f, -2.4f);
    glVertex3f(-3.5f, 1.9f, -2.4f);

    glEnd();

    //--------------------------------------------------------
    //piller1_back_rightpart
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.35f, 1.128f, -2.0f);
    glVertex3f(-3.0f, 1.5f, -2.0f);
    glVertex3f(-1.5f, -0.5f, -2.0f);
    glVertex3f(-2.0f, -0.5f, -2.0f);

    glEnd();

    //piller1_back_rightpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-1.5f, -0.5f, -2.0f);
    glVertex3f(-3.0f, 1.5f, -2.0f);
    glVertex3f(-3.0f, 1.5f, -2.4f);
    glVertex3f(-1.5f, -0.5f, -2.4f);

    glEnd();

    //piller1_back_rightpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(-1.5f, -0.5f, -2.4f);
    glVertex3f(-3.0f, 1.5f, -2.4f);
    glVertex3f(-3.35f, 1.128f, -2.4f);
    glVertex3f(-2.0f, -0.5f, -2.4f);

    glEnd();

    //piller1_back_rightpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-3.35f, 1.128f, -2.4f);
    glVertex3f(-2.0f, -0.5f, -2.4f);
    glVertex3f(-2.0f, -0.5f, -2.0f);
    glVertex3f(-3.35f, 1.128f, -2.0f);

    glEnd();


    //-----------------------------------------------------------------

    //piller1_back_upperpart
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.5f, -2.0f);
    glVertex3f(-3.0f, 1.5f, -2.0f);
    glVertex3f(-3.0f, 1.9f, -2.0f);
    glVertex3f(-3.5f, 1.9f, -2.0f);

    glEnd();

    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-3.0f, 1.5f, -2.0f);
    glVertex3f(-3.0f, 1.9f, -2.0f);
    glVertex3f(-3.0f, 1.9f, -2.4f);
    glVertex3f(-3.0f, 1.5f, -2.4f);

    glEnd();

    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.0f, 1.9f, -2.4f);
    glVertex3f(-3.0f, 1.5f, -2.4f);
    glVertex3f(-3.5f, 1.5f, -2.4f);
    glVertex3f(-3.5f, 1.9f, -2.4f);

    glEnd();

    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.5f, -2.4f);
    glVertex3f(-3.5f, 1.9f, -2.4f);
    glVertex3f(-3.5f, 1.9f, -2.0f);
    glVertex3f(-3.5f, 1.5f, -2.0f);

    glEnd();

    //-----------------------------------------------
    //-----------------------------------------------

    //upper connection piller1

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.0f, 1.7f, -2.0f);
    glVertex3f(-3.0f, 1.6f, -2.0f);
    glVertex3f(-3.0f, 1.6f, 2.5f);
    glVertex3f(-3.0f, 1.7f, 2.5f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.7f, -2.0f);
    glVertex3f(-3.5f, 1.6f, -2.0f);
    glVertex3f(-3.5f, 1.6f, 2.5f);
    glVertex3f(-3.5f, 1.7f, 2.5f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.7f, -2.0f);
    glVertex3f(-3.5f, 1.7f, 2.5f);
    glVertex3f(-3.0f, 1.7f, 2.5f);
    glVertex3f(-3.0f, 1.7f, -2.0f);

    glEnd();


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(-3.5f, 1.6f, -2.0f);
    glVertex3f(-3.5f, 1.6f, 2.5f);
    glVertex3f(-3.0f, 1.6f, 2.5f);
    glVertex3f(-3.0f, 1.6f, -2.0f);

    glEnd();


    //-----------------------------------------------
    //-----------------------------------------------

    //piller2codes

    //piller2_front_leftpart
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-1.5f, -0.5f, 2.5f);
    glVertex3f(0.2f, 1.5f, 2.5f);
    glVertex3f(0.7f, 1.5f, 2.5f);
    glVertex3f(-1.0f, -0.5f, 2.5f);

    glEnd();

    //piller1_front_leftpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(0.7f, 1.5f, 2.5f);
    glVertex3f(-1.0f, -0.5f, 2.5f);
    glVertex3f(-1.0f, -0.5f, 2.1f);
    glVertex3f(0.7f, 1.5f, 2.1f);

    glEnd();

    //piller1_front_leftpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(0.7f, 1.5f, 2.1f);
    glVertex3f(-1.0f, -0.5f, 2.1f);
    glVertex3f(-1.5f, -0.5f, 2.1f);
    glVertex3f(0.2f, 1.5f, 2.1f);

    glEnd();

    //piller1_front_leftpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-1.5f, -0.5f, 2.1f);
    glVertex3f(0.2f, 1.5f, 2.1f);
    glVertex3f(0.2f, 1.5f, 2.5f);
    glVertex3f(-1.5f, -0.5f, 2.5f);

    glEnd();

    //--------------------------------------------------------------------------
    //piller1_front_rightpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(2.3f, -0.5f, 2.5f);
    glVertex3f(0.7f, 1.5f, 2.5f);
    glVertex3f(0.7f, 1.5f, 2.1f);
    glVertex3f(2.3f, -0.5f, 2.1f);

    glEnd();


    //piller1_front_rightpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(2.3f, -0.5f, 2.1f);
    glVertex3f(0.7f, 1.5f, 2.1f);
    glVertex3f(0.35f, 1.128f, 2.1f);
    glVertex3f(1.8f, -0.5f, 2.1f);

    glEnd();


    //piller1_front_rightpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(0.35f, 1.128f, 2.1f);
    glVertex3f(1.8f, -0.5f, 2.1f);
    glVertex3f(1.8f, -0.5f, 2.5f);
    glVertex3f(0.35f, 1.128f, 2.5f);

    glEnd();

    ////piller1_front_rightpartcode
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.35f, 1.128f, 2.5f);
    glVertex3f(0.7f, 1.5f, 2.5f);
    glVertex3f(2.3f, -0.5f, 2.5f);
    glVertex3f(1.8f, -0.5f, 2.5f);

    glEnd();

    //----------------------------------------------------------------------------


    //piller1_front_upperpartcode
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.5f, 2.5f);
    glVertex3f(0.7f, 1.5f, 2.5f);
    glVertex3f(0.7f, 1.9f, 2.5f);
    glVertex3f(0.2f, 1.9f, 2.5f);

    glEnd();

    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.7f, 1.5f, 2.5f);
    glVertex3f(0.7f, 1.9f, 2.5f);
    glVertex3f(0.7f, 1.9f, 2.1f);
    glVertex3f(0.7f, 1.5f, 2.1f);

    glEnd();

    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.7f, 1.9f, 2.1f);
    glVertex3f(0.7f, 1.5f, 2.1f);
    glVertex3f(0.2f, 1.5f, 2.1f);
    glVertex3f(0.2f, 1.9f, 2.1f);

    glEnd();

    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.5f, 2.1f);
    glVertex3f(0.2f, 1.9f, 2.1f);
    glVertex3f(0.2f, 1.9f, 2.5f);
    glVertex3f(0.2f, 1.5f, 2.5f);

    glEnd();


    //-----------------------------------------------------------------------

    //piller1_back-LEFTPART
    //frontside



    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-1.5f, -0.5f, -2.0f);
    glVertex3f(0.2f, 1.5f, -2.0f);
    glVertex3f(0.7f, 1.5f, -2.0f);
    glVertex3f(-1.0f, -0.5f, -2.0f);

    glEnd();

    //piller1_front_leftpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(0.7f, 1.5f, -2.0f);
    glVertex3f(-1.0f, -0.5f, -2.0f);
    glVertex3f(-1.0f, -0.5f, -2.4f);
    glVertex3f(0.7f, 1.5f, -2.4f);

    glEnd();

    //piller1_front_leftpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(0.7f, 1.5f, -2.4f);
    glVertex3f(-1.0f, -0.5f, -2.4f);
    glVertex3f(-1.5f, -0.5f, -2.4f);
    glVertex3f(0.2f, 1.5f, -2.4f);

    glEnd();

    //piller1_front_leftpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(-1.5f, -0.5f, -2.4f);
    glVertex3f(0.2f, 1.5f, -2.4f);
    glVertex3f(0.2f, 1.5f, -2.0f);
    glVertex3f(-1.5f, -0.5f, -2.0f);

    glEnd();

    //--------------------------------------------------------------------------
    //piller1_front_rightpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(2.3f, -0.5f, -2.0f);
    glVertex3f(0.7f, 1.5f, -2.0f);
    glVertex3f(0.7f, 1.5f, -2.4f);
    glVertex3f(2.3f, -0.5f, -2.4f);

    glEnd();


    //piller1_front_rightpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(2.3f, -0.5f, -2.4f);
    glVertex3f(0.7f, 1.5f, -2.4f);
    glVertex3f(0.35f, 1.128f, -2.4f);
    glVertex3f(1.8f, -0.5f, -2.4f);

    glEnd();


    //piller1_front_rightpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(0.35f, 1.128f, -2.4f);
    glVertex3f(1.8f, -0.5f, -2.4f);
    glVertex3f(1.8f, -0.5f, -2.0f);
    glVertex3f(0.35f, 1.128f, -2.0f);

    glEnd();

    ////piller1_front_rightpartcode
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.35f, 1.128f, -2.0f);
    glVertex3f(0.7f, 1.5f, -2.0f);
    glVertex3f(2.3f, -0.5f, -2.0f);
    glVertex3f(1.8f, -0.5f, -2.0f);

    glEnd();

    //----------------------------------------------------------------------------


    //piller1_front_upperpartcode
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.5f, -2.0f);
    glVertex3f(0.7f, 1.5f, -2.0f);
    glVertex3f(0.7f, 1.9f, -2.0f);
    glVertex3f(0.2f, 1.9f, -2.0f);

    glEnd();

    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.7f, 1.5f, -2.0f);
    glVertex3f(0.7f, 1.9f, -2.0f);
    glVertex3f(0.7f, 1.9f, -2.4f);
    glVertex3f(0.7f, 1.5f, -2.4f);

    glEnd();

    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.7f, 1.9f, -2.4f);
    glVertex3f(0.7f, 1.5f, -2.4f);
    glVertex3f(0.2f, 1.5f, -2.4f);
    glVertex3f(0.2f, 1.9f, -2.4f);

    glEnd();

    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.5f, -2.4f);
    glVertex3f(0.2f, 1.9f, -2.4f);
    glVertex3f(0.2f, 1.9f, -2.0f);
    glVertex3f(0.2f, 1.5f, -2.0f);

    glEnd();

    //-----------------------------------------------------



    //upper connection piller2

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.7f, 1.7f, -2.0f);
    glVertex3f(0.7f, 1.6f, -2.0f);
    glVertex3f(0.7f, 1.6f, 2.5f);
    glVertex3f(0.7f, 1.7f, 2.5f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.7f, -2.0f);
    glVertex3f(0.2f, 1.6f, -2.0f);
    glVertex3f(0.2f, 1.6f, 2.5f);
    glVertex3f(0.2f, 1.7f, 2.5f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.7f, -2.0f);
    glVertex3f(0.2f, 1.7f, 2.5f);
    glVertex3f(0.7f, 1.7f, 2.5f);
    glVertex3f(0.7f, 1.7f, -2.0f);

    glEnd();


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(0.2f, 1.6f, -2.0f);
    glVertex3f(0.2f, 1.6f, 2.5f);
    glVertex3f(0.7f, 1.6f, 2.5f);
    glVertex3f(0.7f, 1.6f, -2.0f);

    glEnd();


    //-----------------------------------------------
    //-----------------------------------------------


    //PILLER3 STARTS HERE

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(2.3f, -0.5f, -2.0f);
    glVertex3f(4.0f, 1.5f, -2.0f);
    glVertex3f(4.5f, 1.5f, -2.0f);
    glVertex3f(2.8f, -0.5f, -2.0f);

    glEnd();

    //piller1_front_leftpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(4.5f, 1.5f, -2.0f);
    glVertex3f(2.8f, -0.5f, -2.0f);
    glVertex3f(2.8f, -0.5f, -2.4f);
    glVertex3f(4.5f, 1.5f, -2.4f);

    glEnd();

    //piller1_front_leftpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(4.5f, 1.5f, -2.4f);
    glVertex3f(2.8f, -0.5f, -2.4f);
    glVertex3f(2.3f, -0.5f, -2.4f);
    glVertex3f(4.0f, 1.5f, -2.4f);

    glEnd();

    //piller1_front_leftpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(2.3f, -0.5f, -2.4f);
    glVertex3f(4.0f, 1.5f, -2.4f);
    glVertex3f(4.0f, 1.5f, -2.0f);
    glVertex3f(2.3f, -0.5f, -2.0f);

    glEnd();

    //--------------------------------------------------------------------------
    //piller1_front_rightpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(6.1f, -0.5f, -2.0f);
    glVertex3f(4.5f, 1.5f, -2.0f);
    glVertex3f(4.5f, 1.5f, -2.4f);
    glVertex3f(6.1f, -0.5f, -2.4f);

    glEnd();


    //piller1_front_rightpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(6.1f, -0.5f, -2.4f);
    glVertex3f(4.5f, 1.5f, -2.4f);
    glVertex3f(4.15f, 1.128f, -2.4f);
    glVertex3f(5.6f, -0.5f, -2.4f);

    glEnd();


    //piller1_front_rightpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(4.15f, 1.128f, -2.4f);
    glVertex3f(5.6f, -0.5f, -2.4f);
    glVertex3f(5.6f, -0.5f, -2.0f);
    glVertex3f(4.15f, 1.128f, -2.0f);

    glEnd();

    ////piller1_front_rightpartcode
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.17f, 1.128f, -2.0f);
    glVertex3f(4.5f, 1.5f, -2.0f);
    glVertex3f(6.1f, -0.5f, -2.0f);
    glVertex3f(5.6f, -0.5f, -2.0f);

    glEnd();

    //----------------------------------------------------------------------------


    //piller1_front_upperpartcode
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.5f, -2.0f);
    glVertex3f(4.5f, 1.5f, -2.0f);
    glVertex3f(4.5f, 1.9f, -2.0f);
    glVertex3f(4.0f, 1.9f, -2.0f);

    glEnd();

    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.5f, 1.5f, -2.0f);
    glVertex3f(4.5f, 1.9f, -2.0f);
    glVertex3f(4.5f, 1.9f, -2.4f);
    glVertex3f(4.5f, 1.5f, -2.4f);

    glEnd();

    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.5f, 1.9f, -2.4f);
    glVertex3f(4.5f, 1.5f, -2.4f);
    glVertex3f(4.0f, 1.5f, -2.4f);
    glVertex3f(4.0f, 1.9f, -2.4f);

    glEnd();

    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.5f, -2.4f);
    glVertex3f(4.0f, 1.9f, -2.4f);
    glVertex3f(4.0f, 1.9f, -2.0f);
    glVertex3f(4.0f, 1.5f, -2.0f);

    glEnd();

    //-----------------------------------------------------------------
    //FRONT_PILLER3

    //----------------------------------------------------------------


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(2.3f, -0.5f, 2.5f);
    glVertex3f(4.0f, 1.5f, 2.5f);
    glVertex3f(4.5f, 1.5f, 2.5f);
    glVertex3f(2.8f, -0.5f, 2.5f);

    glEnd();

    //piller1_front_leftpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(4.5f, 1.5f, 2.5f);
    glVertex3f(2.8f, -0.5f, 2.5f);
    glVertex3f(2.8f, -0.5f, 2.1f);
    glVertex3f(4.5f, 1.5f, 2.1f);

    glEnd();

    //piller1_front_leftpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(4.5f, 1.5f, 2.1f);
    glVertex3f(2.8f, -0.5f, 2.1f);
    glVertex3f(2.3f, -0.5f, 2.1f);
    glVertex3f(4.0f, 1.5f, 2.1f);

    glEnd();

    //piller1_front_leftpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(2.3f, -0.5f, 2.1f);
    glVertex3f(4.0f, 1.5f, 2.1f);
    glVertex3f(4.0f, 1.5f, 2.5f);
    glVertex3f(2.3f, -0.5f, 2.5f);

    glEnd();

    //--------------------------------------------------------------------------
    //piller1_front_rightpart
    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(6.1f, -0.5f, 2.5f);
    glVertex3f(4.5f, 1.5f, 2.5f);
    glVertex3f(4.5f, 1.5f, 2.1f);
    glVertex3f(6.1f, -0.5f, 2.1f);

    glEnd();


    //piller1_front_rightpart
    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(6.1f, -0.5f, 2.1f);
    glVertex3f(4.5f, 1.5f, 2.1f);
    glVertex3f(4.15f, 1.128f, 2.1f);
    glVertex3f(5.6f, -0.5f, 2.1f);

    glEnd();


    //piller1_front_rightpart
    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);


    glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(4.15f, 1.128f, 2.1f);
    glVertex3f(5.6f, -0.5f, 2.1f);
    glVertex3f(5.6f, -0.5f, 2.5f);
    glVertex3f(4.15f, 1.128f, 2.5f);

    glEnd();

    ////piller1_front_rightpartcode
    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.17f, 1.128f, 2.5f);
    glVertex3f(4.5f, 1.5f, 2.5f);
    glVertex3f(6.1f, -0.5f, 2.5f);
    glVertex3f(5.6f, -0.5f, 2.5f);

    glEnd();

    //----------------------------------------------------------------------------


    //piller1_front_upperpartcode
    //frontside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.5f, 2.5f);
    glVertex3f(4.5f, 1.5f, 2.5f);
    glVertex3f(4.5f, 1.9f, 2.5f);
    glVertex3f(4.0f, 1.9f, 2.5f);

    glEnd();

    //rightside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.5f, 1.5f, 2.5f);
    glVertex3f(4.5f, 1.9f, 2.5f);
    glVertex3f(4.5f, 1.9f, 2.1f);
    glVertex3f(4.5f, 1.5f, 2.1f);

    glEnd();

    //backside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.5f, 1.9f, 2.1f);
    glVertex3f(4.5f, 1.5f, 2.1f);
    glVertex3f(4.0f, 1.5f, 2.1f);
    glVertex3f(4.0f, 1.9f, 2.1f);

    glEnd();

    //leftside

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.5f, 2.1f);
    glVertex3f(4.0f, 1.9f, 2.1f);
    glVertex3f(4.0f, 1.9f, 2.5f);
    glVertex3f(4.0f, 1.5f, 2.5f);

    glEnd();
    //PILLER3 BACK ENDS HERE
    //--------------------------------------------------------------------------



    //upper connection piller2

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.5f, 1.7f, -2.0f);
    glVertex3f(4.5f, 1.6f, -2.0f);
    glVertex3f(4.5f, 1.6f, 2.5f);
    glVertex3f(4.5f, 1.7f, 2.5f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.7f, -2.0f);
    glVertex3f(4.0f, 1.6f, -2.0f);
    glVertex3f(4.0f, 1.6f, 2.5f);
    glVertex3f(4.0f, 1.7f, 2.5f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.7f, -2.0f);
    glVertex3f(4.0f, 1.7f, 2.5f);
    glVertex3f(4.5f, 1.7f, 2.5f);
    glVertex3f(4.5f, 1.7f, -2.0f);

    glEnd();


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,0.0,1.0);
    glVertex3f(4.0f, 1.6f, -2.0f);
    glVertex3f(4.0f, 1.6f, 2.5f);
    glVertex3f(4.5f, 1.6f, 2.5f);
    glVertex3f(4.5f, 1.6f, -2.0f);

    glEnd();


    //-----------------------------------------------
    //-----------------------------------------------


    //bridge road code start

    //roadupperpart
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-5.2f,-0.48f,2.5);
    glVertex3f(6.1f,-0.48f,2.5);
    glVertex3f(6.1f,-0.48f,-2.4);
    glVertex3f(-5.2f,-0.48f,-2.4);

    glEnd();

    //roadrightpart

    glColor3f(.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(6.1f,-0.48f,2.5);
    glVertex3f(6.1f,-0.55f,2.5);
    glVertex3f(6.1f,-0.55f,-2.4);
    glVertex3f(6.1f,-0.48f,-2.4);

    glEnd();

    //roadlowerpart

    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-5.2f,-0.55f,2.5);
    glVertex3f(6.1f,-0.55f,2.5);
    glVertex3f(6.1f,-0.55f,-2.4);
    glVertex3f(-5.2f,-0.55f,-2.4);

    glEnd();

    //bridgeleftpart

    glColor3f(.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-5.2f,-0.48f,2.5);
    glVertex3f(-5.2f,-0.55f,2.5);
    glVertex3f(-5.2f,-0.55f,-2.4);
    glVertex3f(-5.2f,-0.48f,-2.4);

    glEnd();

    //bridge road code end
    //---------------------------------------------------------------------------------------------

    //road divider code starts

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-5.2f,-0.47f,0.11);
    glVertex3f(-4.0f,-0.47f,0.11);
    glVertex3f(-4.0f,-0.47f,0.21);
    glVertex3f(-5.2f,-0.47f,0.21);

    glEnd();


    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-3.0f,-0.47f,0.11);
    glVertex3f(-1.8f,-0.47f,0.11);
    glVertex3f(-1.8f,-0.47f,0.21);
    glVertex3f(-3.0f,-0.47f,0.21);

    glEnd();


    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-0.8f,-0.47f,0.11);
    glVertex3f(0.4f,-0.47f,0.11);
    glVertex3f(0.4f,-0.47f,0.21);
    glVertex3f(-0.8f,-0.47f,0.21);

    glEnd();


    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(1.4f,-0.47f,0.11);
    glVertex3f(2.6f,-0.47f,0.11);
    glVertex3f(2.6f,-0.47f,0.21);
    glVertex3f(1.4f,-0.47f,0.21);

    glEnd();


    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(3.6f,-0.47f,0.11);
    glVertex3f(4.8f,-0.47f,0.11);
    glVertex3f(4.8f,-0.47f,0.21);
    glVertex3f(3.6f,-0.47f,0.21);

    glEnd();


    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(5.5f,-0.47f,0.11);
    glVertex3f(6.1f,-0.47f,0.11);
    glVertex3f(6.1f,-0.47f,0.21);
    glVertex3f(5.5f,-0.47f,0.21);

    glEnd();

    //road divider code ends
    //-------------------------------------------------------------


    //Left wall starts here

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-11.5f, -0.551f, 35.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-11.5f, -0.551f, -35.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-11.5f, 1.4f, -35.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-11.5f, 1.4f, 35.0f);

    glEnd();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(13.4f, -0.551f, 35.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(13.4f, -0.551f, -35.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(13.4f, 1.4f, -35.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(13.4f, 1.4f, 35.0f);

    glEnd();

    //-----------------------------------------------------------
    //-----------------------------------------------------------

    //wall road codes

    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-6.0f,-0.551f,35.0f);
    glVertex3f(-6.0f,-0.551f,-35.0f);
    glVertex3f(-11.5f,-0.551f,-35.0f);
    glVertex3f(-11.5f,-0.551f,35.0f);

    glEnd();


    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_QUADS);

    glNormal3f(0.0,1.0,0.0);
    glVertex3f(6.9f,-0.551f,35.0f);
    glVertex3f(6.9f,-0.551f,-35.0f);
    glVertex3f(13.4f,-0.551f,-35.0f);
    glVertex3f(13.4f,-0.551f,35.0f);

    glEnd();

    //----------------------------------------

    //building codes

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(19.45f, -0.551f, -5.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(19.45f, -0.551f, 15.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(19.45f, 10.4f, 15.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(19.45f, 10.4f, -5.0f);

    glEnd();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-19.45f, -0.551f, -5.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-19.45f, -0.551f, 15.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-19.45f, 10.4f, 15.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-19.45f, 10.4f, -5.0f);

    glEnd();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -4.551f, -35.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(9.9f, -4.551f, -35.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(9.9f, 10.4f, -35.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-10.0f, 10.4f, -35.0f);

    glEnd();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -4.551f, 35.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(9.9f, -4.551f, 35.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(9.9f, 10.4f, 35.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-10.0f, 10.4f, 35.0f);

    glEnd();

    //----------------------------------

    //base piller1 code

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-4.5f,-0.55f,2.5f);
    glVertex3f(-4.5f,-0.55f,-2.4f);
    glVertex3f(-4.5f,-2.85f,-1.1f);
    glVertex3f(-4.5f,-2.851f,1.1f);

    glEnd();


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-4.0f,-0.55f,2.5f);
    glVertex3f(-4.0f,-0.55f,-2.4f);
    glVertex3f(-4.0f,-2.85f,-1.1f);
    glVertex3f(-4.0f,-2.851f,1.1f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-4.0f,-0.55f,2.5f);
    glVertex3f(-4.5f,-0.55f,2.5f);
    glVertex3f(-4.5f,-2.85f,1.1f);
    glVertex3f(-4.0f,-2.851f,1.1f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-4.0f,-0.55f,-2.4f);
    glVertex3f(-4.5f,-0.55f,-2.4f);
    glVertex3f(-4.5f,-2.85f,-1.1f);
    glVertex3f(-4.0f,-2.851f,-1.1f);

    glEnd();


    //base piller2 code

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-0.5f,-0.55f,2.5f);
    glVertex3f(-0.5f,-0.55f,-2.4f);
    glVertex3f(-0.5f,-2.85f,-1.1f);
    glVertex3f(-0.5f,-2.851f,1.1f);

    glEnd();


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-0.0f,-0.55f,2.5f);
    glVertex3f(-0.0f,-0.55f,-2.4f);
    glVertex3f(-0.0f,-2.85f,-1.1f);
    glVertex3f(-0.0f,-2.851f,1.1f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-0.0f,-0.55f,2.5f);
    glVertex3f(-0.5f,-0.55f,2.5f);
    glVertex3f(-0.5f,-2.85f,1.1f);
    glVertex3f(-0.0f,-2.851f,1.1f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(-0.0f,-0.55f,-2.4f);
    glVertex3f(-0.5f,-0.55f,-2.4f);
    glVertex3f(-0.5f,-2.85f,-1.1f);
    glVertex3f(-0.0f,-2.851f,-1.1f);

    glEnd();


    //base piller3 code

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(3.5f,-0.55f,2.5f);
    glVertex3f(3.5f,-0.55f,-2.4f);
    glVertex3f(3.5f,-2.85f,-1.1f);
    glVertex3f(3.5f,-2.851f,1.1f);

    glEnd();


    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(4.0f,-0.55f,2.5f);
    glVertex3f(4.0f,-0.55f,-2.4f);
    glVertex3f(4.0f,-2.85f,-1.1f);
    glVertex3f(4.0f,-2.851f,1.1f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(3.5f,-0.55f,2.5f);
    glVertex3f(4.0f,-0.55f,2.5f);
    glVertex3f(4.0f,-2.85f,1.1f);
    glVertex3f(3.5f,-2.851f,1.1f);

    glEnd();

    glColor3f(0.8f, 0.4f, 0.0f);
    glBegin(GL_QUADS);

    glNormal3f(1.0,0.0,0.0);
    glVertex3f(3.5f,-0.55f,-2.4f);
    glVertex3f(4.0f,-0.55f,-2.4f);
    glVertex3f(4.0f,-2.85f,-1.1f);
    glVertex3f(3.5f,-2.851f,-1.1f);

    glEnd();


    glutSwapBuffers();
}

void update(int value)
{
    _angle += 0.8f;
    if (_angle > 360)
    {
        _angle -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1266, 760);

    //Create the window
    glutCreateWindow("Lighting ");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0); //Add a timer

    glutMainLoop();
    return 0;
}
