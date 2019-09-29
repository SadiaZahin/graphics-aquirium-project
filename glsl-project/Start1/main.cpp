/**
 * This project (GLSL_Project1) is created by Fahim Hasan Khan (fahimhasan.khan [at] ucalgary.ca)
 * based on the works of Andrew Robert Owens (arowens [at] ucalgary.ca)
 * who is a PhD student at Graphics Jungle, University of Calgary
 *
 * File:	main.cpp
 *
 * Summary:
 *
 * This is a (very) basic program to
 * 1) load shaders from external files, and make a shader program
 * 2) make Vertex Array Object and Vertex Buffer Object for the quad
 *
 **/

#include <iostream>
#include <cmath>
#include <chrono>
#include <limits>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ShaderTools.h"
#include "Vec3f.h"
#include "Mat4f.h"
#include "OpenGLMatrixTools.h"
#include "Camera.h"

//==================== GLOBAL VARIABLES ====================//
/*	Put here for simplicity. Feel free to restructure into
*	appropriate classes or abstractions.
*/

// Drawing Program
GLuint basicProgramID;
GLuint basicProgramID1;

// Data needed for Quad

///Fish body
GLuint vaoID;
GLuint vertBufferID;
Mat4f M;

///Aqua body
GLuint vao2;
GLuint vertBuffer2;
Mat4f M2;
///Aqua Sand
GLuint vao3;
GLuint vertBuffer3;
Mat4f M3;

///Fish Tail
GLuint vao4;
GLuint vertBuffer4;
Mat4f M4;

///Aqua Grass
GLuint vao5;
GLuint vertBuffer5;
Mat4f M5;

///Aqua Grass
GLuint vao6;
GLuint vertBuffer6;
Mat4f M6;

///Aqua Grass
GLuint vao7;
GLuint vertBuffer7;
Mat4f M7;

///Aqua Grass
GLuint vao8;
GLuint vertBuffer8;
Mat4f M8;

///Fish 2 Body
GLuint vao9;
GLuint vertBuffer9;
Mat4f M9;

///Fish 2 Tail
GLuint vao10;
GLuint vertBuffer10;
Mat4f M10;


///Room
GLuint vao11;
GLuint vertBuffer11;
Mat4f M11;

GLuint vao12;
GLuint vertBuffer12;
Mat4f M12;

GLuint vao13;
GLuint vertBuffer13;
Mat4f M13;

GLuint vao14;
GLuint vertBuffer14;
Mat4f M14;

///Room done


///Aqua Grass
GLuint vao15;
GLuint vertBuffer15;
Mat4f M15;

///Aqua Grass
GLuint vao16;
GLuint vertBuffer16;
Mat4f M16;

///Aqua Grass
GLuint vao17;
GLuint vertBuffer17;
Mat4f M17;

///Aqua Grass
GLuint vao18;
GLuint vertBuffer18;
Mat4f M18;

///Aquarium table
GLuint vao19;
GLuint vertBuffer19;
Mat4f M19;

///window1
GLuint vao20;
GLuint vertBuffer20;
Mat4f M20;

// Data needed for Line
GLuint line_vaoID;
GLuint line_vertBufferID;
Mat4f line_M;

// Only one camera so only one veiw and perspective matrix are needed.
Mat4f V;
Mat4f P;

// Only one thing is rendered at a time, so only need one MVP
// When drawing different objects, update M and MVP = M * V * P
Mat4f MVP;

// Camera and veiwing Stuff
Camera camera;
int g_moveUpDown = 0;
int g_moveLeftRight = 0;
int g_moveBackForward = 0;
int g_rotateLeftRight = 0;
int g_rotateUpDown = 0;
int g_rotateRoll = 0;
float g_rotationSpeed = 0.015625;
float g_panningSpeed = 0.25;
bool g_cursorLocked;
float g_cursorX, g_cursorY;

bool g_play = false;

int WIN_WIDTH = 1600, WIN_HEIGHT = 1000;
int FB_WIDTH = 800, FB_HEIGHT = 600;
float WIN_FOV = 60;
float WIN_NEAR = 0.01;
float WIN_FAR = 1000;

//==================== FUNCTION DECLARATIONS ====================//
void displayFunc();
void resizeFunc();
void init();
void generateIDs();
void deleteIDs();
void setupVAO();
void loadQuadGeometryToGPU();
void reloadProjectionMatrix();
void loadModelViewMatrix();
void setupModelViewProjectionTransform();

void windowSetSizeFunc();
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
void windowSetSizeFunc(GLFWwindow *window, int width, int height);
void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height);
void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
                           int mods);
void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
void animateQuad(float t);
void moveCamera();
void reloadMVPUniform(GLuint ProgramID);
void reloadColorUniform(float r, float g, float b, GLuint ProgramID);
std::string GL_ERROR();
int main(int, char **);

//==================== FUNCTION DEFINITIONS ====================//

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Use our shader
  glUseProgram(basicProgramID1);
  ///Fish body and tail
  // ===== DRAW QUAD ====== //
  MVP = P * V * M;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(1, .3, .8, basicProgramID1);


  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vaoID);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 11);


  // ===== DRAW QUAD ====== //
  MVP = P * V * M;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(1, .7, 0, basicProgramID1);


  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao4);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  ///Fish 1 end

  glUseProgram(basicProgramID);
   ///Fish 2 body and tail
  // ===== DRAW QUAD ====== //
  MVP = P * V * M9;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(0.859, .078, .234, basicProgramID1);


  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao9);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 11);


  // ===== DRAW QUAD ====== //
  MVP = P * V * M9;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.5, .5, .5, basicProgramID);


  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao10);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  ///Fish 2 end
  ///Aquarium start
   // ===== DRAW QUAD ====== //
  //glUseProgram(basicProgramID1);
  MVP = P * V * M2;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.6, 1, 1, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao2);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);


   // ===== DRAW QUAD ====== //
  glUseProgram(basicProgramID);
  MVP = P * V * M3;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.76, 0.69, 0.52, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao3);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);

    // ===== DRAW QUAD ====== //
  MVP = P * V * M14;
  reloadMVPUniform(basicProgramID1);
  reloadColorUniform(0.1, 0.1, 0.3, basicProgramID1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao14);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      // ===== DRAW QUAD ====== //
  MVP = P * V * M19;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0, 0, 0, basicProgramID);
 // reloadColorUniform(0.285, 0.218, 0.160);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao19);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);


  ///Aquarium End
  ///Grass
   // ===== DRAW QUAD ====== //
  MVP = P * V * M5;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(.004, 0.55, .33, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao5);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M6;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(.2, 0.76, .33, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao6);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M7;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(.2, 0.8, .02, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao7);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M8;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.65,0.41, 0, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao8);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

 // ===== DRAW QUAD ====== //
  MVP = P * V * M15;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(.004, 0.55, .33, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao15);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M16;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(1,0.268 , 0, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao16);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M17;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(.2, 0.8, .02, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao17);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M18;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(.5, 0.5, .33, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao18);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);



  ///Grass end
  ///Room
   // ===== DRAW QUAD ====== //
  MVP = P * V * M11;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.90, 0.88, 0.85, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao11);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);

   // ===== DRAW QUAD ====== //
  MVP = P * V * M12;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.63, 0.531, 0.597, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao12);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD ====== //
  MVP = P * V * M13;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.99, 0.99, 0.99, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao13);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  ///Room end

  ///Window

     // ===== DRAW QUAD ====== //
  MVP = P * V * M20;
  reloadMVPUniform(basicProgramID);
  reloadColorUniform(0.67, 0.914, 1, basicProgramID);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(vao20);
  // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


  /*
  // ==== DRAW LINE ===== //
  MVP = P * V * line_M;
  reloadMVPUniform();

  reloadColorUniform(0, 1, 1);

  // Use VAO that holds buffer bindings
  // and attribute config of buffers
  glBindVertexArray(line_vaoID);
  // Draw lines
  glDrawArrays(GL_LINES, 0, 2);

  */

}

void animateQuad(float t) {

  M = RotateAboutYMatrix(100 * t);
  M9 = RotateAboutYMatrix(100 * t);
  float s = (std::sin(t) + 1.f) / 2.f;
  float x = (1 - s) * (10) + s * (-10);
  float v = (std::sin(t/2) + 1.f) / 2.f;
  float y = (1 - v) * (10) + v * (-10);

  M = TranslateMatrix(x, 0, 0) * M;
  M4 = TranslateMatrix(x, 0, 0) * M4;
  M9 = TranslateMatrix(-y, 0, 0) * M9;
  M10 = TranslateMatrix(-y, 0, 0) * M10;


  setupModelViewProjectionTransform();
  reloadMVPUniform(basicProgramID1);
}

void loadQuadGeometryToGPU() {
  // Just basic layout of floats, for a quad
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
  std::vector<Vec3f> verts1;
  std::vector<Vec3f> verts2;
  std::vector<Vec3f> verts3;
  std::vector<Vec3f> verts4;
  std::vector<Vec3f> verts5;
  std::vector<Vec3f> verts6;
  std::vector<Vec3f> verts7;
  std::vector<Vec3f> verts8;
  std::vector<Vec3f> verts9;
  std::vector<Vec3f> verts10;
  std::vector<Vec3f> verts11;
  std::vector<Vec3f> verts12;
  std::vector<Vec3f> verts13;
  std::vector<Vec3f> verts14;
  std::vector<Vec3f> verts15;
  std::vector<Vec3f> verts16;
  std::vector<Vec3f> verts17;
  std::vector<Vec3f> verts18;
  std::vector<Vec3f> verts19;

  /*verts.push_back(Vec3f(-1, -1, 0));
  verts.push_back(Vec3f(-1, 1, 0));
  verts.push_back(Vec3f(1, -1, 0));
  verts.push_back(Vec3f(1, 1, 0));*/
  ///Fish body
  verts.push_back(Vec3f(-1.2, 0, -1));
  verts.push_back(Vec3f(0.2, -1, -0.8));
  verts.push_back(Vec3f(0.2, 1, -0.8));

  verts.push_back(Vec3f(0.2, -1, -1.3));
  verts.push_back(Vec3f(0.2, 1, -1.3));
  verts.push_back(Vec3f(-1.2, 0, -1));
  verts.push_back(Vec3f(0.2, -1, -0.8));
  verts.push_back(Vec3f(0.2, 1, -0.8));

  verts.push_back(Vec3f(1, 0, -1));
  verts.push_back(Vec3f(0.2, -1, -1.3));
  verts.push_back(Vec3f(0.2, 1, -1.3));


  ///Fish tail
  verts3.push_back(Vec3f(1, 0, -1));
  verts3.push_back(Vec3f(1.3, 1, -1));
  verts3.push_back(Vec3f(1.3, -1, -1));
  verts3.push_back(Vec3f(1, 0, -1));

  ///Fish 2 body
  verts8.push_back(Vec3f(-4.4, -2, -2));
  verts8.push_back(Vec3f(-1.6, -4, -2));
  verts8.push_back(Vec3f(-1.6, 0, -2));

  verts8.push_back(Vec3f(-1.6, -4, -1));
  verts8.push_back(Vec3f(-1.6, 0, -1));

  verts8.push_back(Vec3f(-4.4, -2, -2));

  verts8.push_back(Vec3f(-1.6, -4, -2));
  verts8.push_back(Vec3f(-1.6, 0, -2));

  verts8.push_back(Vec3f(0, -2, -2));
  verts8.push_back(Vec3f(-1.6, -4, -1));
  verts8.push_back(Vec3f(-1.6, 0, -1));

  ///Fish 2 tail
  verts9.push_back(Vec3f(0, -2, -2));
  verts9.push_back(Vec3f(0.6, 0, -2));
  verts9.push_back(Vec3f(0.6, -4, -2));
  verts9.push_back(Vec3f(0, -2, -2));

  ///Aquarium body
  verts1.push_back(Vec3f(-18, -5, 10));
  verts1.push_back(Vec3f(-18, 5, 10));
  verts1.push_back(Vec3f(-18, -5, -10));
  verts1.push_back(Vec3f(-18, 5, -10));
  verts1.push_back(Vec3f(16, -5, -10));
  verts1.push_back(Vec3f(16, 5, -10));

  verts1.push_back(Vec3f(16, -5, 10));
  verts1.push_back(Vec3f(16, 5, 10));


   ///Aquarium ground (sand)

   verts2.push_back(Vec3f(-18, -5, 10));
   verts2.push_back(Vec3f(-18, -5, -10));
   verts2.push_back(Vec3f(16, -5, -10));
   verts2.push_back(Vec3f(16, -5, 10));
   verts2.push_back(Vec3f(-18, -5, 10));
   verts2.push_back(Vec3f(-18, -4, 10));
   verts2.push_back(Vec3f(16, -5, 10));
   verts2.push_back(Vec3f(16, -4, 10));
   verts2.push_back(Vec3f(16, -4, -10));
   verts2.push_back(Vec3f(-18, -4, -10));
   verts2.push_back(Vec3f(-18, -4, 10));
   verts2.push_back(Vec3f(16, -4, 10));


   ///Aquarium Ceiling (black)

   verts13.push_back(Vec3f(-18, 5, -10));
   verts13.push_back(Vec3f(-18, 5, 10));
   verts13.push_back(Vec3f(16, 5, -10));
   verts13.push_back(Vec3f(16, 5, 10));

   ///Aquarium table

   verts18.push_back(Vec3f(-18, -5.1, 10));
   verts18.push_back(Vec3f(-18, -24.9, 10));
   verts18.push_back(Vec3f(-18, -5.1, -10));
   verts18.push_back(Vec3f(-18, -24.9, -10));

   verts18.push_back(Vec3f(16, -5.1, -10));
   verts18.push_back(Vec3f(16, -24.9, -10));
   verts18.push_back(Vec3f(16, -5.1, 10));
   verts18.push_back(Vec3f(16, -24.9, 10));

   verts18.push_back(Vec3f(-18, -5.1, 10));
   verts18.push_back(Vec3f(-18, -24.9, 10));


   ///Grass
   verts4.push_back(Vec3f(-15, -5, -4));
   verts4.push_back(Vec3f(-16, -4, -4));
   verts4.push_back(Vec3f(-16, 1, -4));
   verts4.push_back(Vec3f(-15, -5, -4));

   verts5.push_back(Vec3f(-14, -5, -4));
   verts5.push_back(Vec3f(-15.5, -2, -4));
   verts5.push_back(Vec3f(-15.5, 2, -4));
   verts5.push_back(Vec3f(-14, -5, -4));

   verts6.push_back(Vec3f(-13, -5, -2));
   verts6.push_back(Vec3f(-11, -2, -2));
   verts6.push_back(Vec3f(-11, 1, -2));
   verts6.push_back(Vec3f(-13, -5, -2));

   verts7.push_back(Vec3f(-14, -5, -4));
   verts7.push_back(Vec3f(-13, -4, -4));
   verts7.push_back(Vec3f(-13, 2, -4));
   verts7.push_back(Vec3f(-14, -5, -4));

   verts14.push_back(Vec3f(15, -5, 4));
   verts14.push_back(Vec3f(16, -4, 4));
   verts14.push_back(Vec3f(16, 1, 4));
   verts14.push_back(Vec3f(15, -5, 4));

   verts15.push_back(Vec3f(14, -5, 4));
   verts15.push_back(Vec3f(15.5, -2, 4));
   verts15.push_back(Vec3f(15.5, 2, 4));
   verts15.push_back(Vec3f(14, -5, 4));

   verts16.push_back(Vec3f(13, -5, 2));
   verts16.push_back(Vec3f(11, -2, 2));
   verts16.push_back(Vec3f(11, 1, 2));
   verts16.push_back(Vec3f(13, -5, 2));

   verts17.push_back(Vec3f(14, -5, 4));
   verts17.push_back(Vec3f(13, -4, 4));
   verts17.push_back(Vec3f(13, 2, 4));
   verts17.push_back(Vec3f(14, -5, 4));
   ///Grass end

  ///Room body
  verts10.push_back(Vec3f(-48, -25, 68));
  verts10.push_back(Vec3f(-48, 25, 68));
  verts10.push_back(Vec3f(-48, -25, -12));
  verts10.push_back(Vec3f(-48, 25, -12));
  verts10.push_back(Vec3f(46, -25, -12));
  verts10.push_back(Vec3f(46, 25, -12));
  verts10.push_back(Vec3f(46, -25, 68));
  verts10.push_back(Vec3f(46, 25, 68));
  verts10.push_back(Vec3f(-48, -25, 68));
  verts10.push_back(Vec3f(-48, 25, 68));


   ///Room floor
   verts11.push_back(Vec3f(-48, -25, -12));
   verts11.push_back(Vec3f(-48, -25, 68));
   verts11.push_back(Vec3f(46, -25, -12));
   verts11.push_back(Vec3f(46, -25, 68));

   ///Room Roof
   verts12.push_back(Vec3f(-48, 25, -12));
   verts12.push_back(Vec3f(-48, 25, 68));
   verts12.push_back(Vec3f(46, 25, -12));
   verts12.push_back(Vec3f(46, 25, 68));

   ///Room

   ///Windows
   verts19.push_back(Vec3f(45, -10, 15));
  verts19.push_back(Vec3f(45, 5, 15));
  verts19.push_back(Vec3f(45, -10, 35));
  verts19.push_back(Vec3f(45, 5, 35));




/*
  verts1.push_back(Vec3f(0, -5, 5));
  verts1.push_back(Vec3f(0, 5, 5));
  verts1.push_back(Vec3f(16, -5, -5));
  verts1.push_back(Vec3f(16, 5, -5));

  verts.push_back(Vec3f(-0.5, -0.5, 0.5));
  verts.push_back(Vec3f(-0.5, 0.5, -0.5));
  verts.push_back(Vec3f(0.5, -0.5, -0.5));
  verts.push_back(Vec3f(0.5, 0.5, 0.5));
  */


  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 11, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer2);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 8, // byte size of Vec3f, 4 of them
               verts1.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer3);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 12, // byte size of Vec3f, 4 of them
               verts2.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer
   glBindBuffer(GL_ARRAY_BUFFER, vertBuffer4);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts3.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

     glBindBuffer(GL_ARRAY_BUFFER, vertBuffer5);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts4.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

      glBindBuffer(GL_ARRAY_BUFFER, vertBuffer6);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts5.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer7);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts6.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer8);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts7.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer9);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 11, // byte size of Vec3f, 4 of them
               verts8.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer10);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts9.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer11);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 10, // byte size of Vec3f, 4 of them
               verts10.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer12);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts11.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer13);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts12.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer14);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts13.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer15);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts14.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer16);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts15.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer17);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts16.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer18);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts17.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer19);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 10, // byte size of Vec3f, 4 of them
               verts18.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer

  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer20);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
               verts19.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer



}

void loadLineGeometryToGPU() {

  // Just basic layout of floats, for a quad
  // 3 floats per vertex, 4 vertices
  std::vector<Vec3f> verts;
  verts.push_back(Vec3f(-10, 0, 0));
  verts.push_back(Vec3f(10, 0, 0));





  glBindBuffer(GL_ARRAY_BUFFER, line_vertBufferID);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vec3f) * 2, // byte size of Vec3f, 4 of them
               verts.data(),      // pointer (Vec3f*) to contents of verts
               GL_STATIC_DRAW);   // Usage pattern of GPU buffer




}

void setupVAO() {
  glBindVertexArray(vaoID);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );


   glBindVertexArray(vao2);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer2);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

   glBindVertexArray(vao3);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer3);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

   glBindVertexArray(vao4);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer4);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao5);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer5);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(vao6);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer6);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(vao7);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer7);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
  glBindVertexArray(vao8);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer8);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(vao9);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer9);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
  glBindVertexArray(vao10);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer10);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao11);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer11);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
  glBindVertexArray(vao12);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer12);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
  glBindVertexArray(vao13);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer13);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao14);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer14);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao15);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer15);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao16);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer16);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao17);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer17);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
   glBindVertexArray(vao18);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer18);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

     glBindVertexArray(vao19);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer19);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(vao20);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, vertBuffer20);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );
  glBindVertexArray(line_vaoID);

  glEnableVertexAttribArray(0); // match layout # in shader
  glBindBuffer(GL_ARRAY_BUFFER, line_vertBufferID);
  glVertexAttribPointer(0,        // attribute layout # above
                        3,        // # of components (ie XYZ )
                        GL_FLOAT, // type of components
                        GL_FALSE, // need to be normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
                        );

  glBindVertexArray(0); // reset to default
}

void reloadProjectionMatrix() {
  // Perspective Only

  // field of view angle 60 degrees
  // window aspect ratio
  // near Z plane > 0
  // far Z plane

  P = PerspectiveProjection(WIN_FOV, // FOV
                            static_cast<float>(WIN_WIDTH) /
                                WIN_HEIGHT, // Aspect
                            WIN_NEAR,       // near plane
                            WIN_FAR);       // far plane depth
}

void loadModelViewMatrix() {
  M = IdentityMatrix();
  M2 = IdentityMatrix();
  M3 = IdentityMatrix();
  M4 = IdentityMatrix();
  M5 = IdentityMatrix();
  M6 = IdentityMatrix();
  M7 = IdentityMatrix();
  M8 = IdentityMatrix();
  M9 = IdentityMatrix();
  M10 = IdentityMatrix();
  M11 = IdentityMatrix();
  M12 = IdentityMatrix();
  M13 = IdentityMatrix();
  M14 = IdentityMatrix();
  M15 = IdentityMatrix();
  M16 = IdentityMatrix();
  M17 = IdentityMatrix();
  M18 = IdentityMatrix();
  M19 = IdentityMatrix();
  M20 = IdentityMatrix();
  line_M = IdentityMatrix();
  // view doesn't change, but if it did you would use this
  V = camera.lookatMatrix();
}

void reloadViewMatrix() { V = camera.lookatMatrix(); }

void setupModelViewProjectionTransform() {
  MVP = P * V * M; // transforms vertices from right to left (odd huh?)
}

void reloadMVPUniform(GLuint ProgramID) {
  GLint id = glGetUniformLocation(ProgramID, "MVP");

  glUseProgram(ProgramID);
  glUniformMatrix4fv(id,        // ID
                     1,         // only 1 matrix
                     GL_TRUE,   // transpose matrix, Mat4f is row major
                     MVP.data() // pointer to data in Mat4f
                     );
}

void reloadColorUniform(float r, float g, float b, GLuint ProgramID) {
  GLint id = glGetUniformLocation(ProgramID, "inputColor");

  glUseProgram(ProgramID);
  glUniform3f(id, // ID in basic_vs.glsl
              r, g, b);
}

void generateIDs() {
  // shader ID from OpenGL
  std::string vsSource = loadShaderStringfromFile("./shaders/basic.vert");
  std::string fsSource = loadShaderStringfromFile("./shaders/basic.frag");
  basicProgramID = CreateShaderProgram(vsSource, fsSource);

  std::string vsSource1 = loadShaderStringfromFile("./shaders/cube.vert");
  std::string fsSource1 = loadShaderStringfromFile("./shaders/cube.frag");
  basicProgramID1 = CreateShaderProgram(vsSource1, fsSource1);

  // VAO and buffer IDs given from OpenGL
  glGenVertexArrays(1, &vaoID);
  glGenBuffers(1, &vertBufferID);

  glGenVertexArrays(1, &vao2);
  glGenBuffers(1, &vertBuffer2);


  glGenVertexArrays(1, &vao3);
  glGenBuffers(1, &vertBuffer3);

  glGenVertexArrays(1, &vao4);
  glGenBuffers(1, &vertBuffer4);

  glGenVertexArrays(1, &vao5);
  glGenBuffers(1, &vertBuffer5);

  glGenVertexArrays(1, &vao6);
  glGenBuffers(1, &vertBuffer6);

  glGenVertexArrays(1, &vao7);
  glGenBuffers(1, &vertBuffer7);

  glGenVertexArrays(1, &vao8);
  glGenBuffers(1, &vertBuffer8);

  glGenVertexArrays(1, &vao9);
  glGenBuffers(1, &vertBuffer9);

  glGenVertexArrays(1, &vao10);
  glGenBuffers(1, &vertBuffer10);

  glGenVertexArrays(1, &vao11);
  glGenBuffers(1, &vertBuffer11);

  glGenVertexArrays(1, &vao12);
  glGenBuffers(1, &vertBuffer12);

  glGenVertexArrays(1, &vao13);
  glGenBuffers(1, &vertBuffer13);

  glGenVertexArrays(1, &vao14);
  glGenBuffers(1, &vertBuffer14);

  glGenVertexArrays(1, &vao15);
  glGenBuffers(1, &vertBuffer15);

  glGenVertexArrays(1, &vao16);
  glGenBuffers(1, &vertBuffer16);

  glGenVertexArrays(1, &vao17);
  glGenBuffers(1, &vertBuffer17);

  glGenVertexArrays(1, &vao18);
  glGenBuffers(1, &vertBuffer18);

  glGenVertexArrays(1, &vao19);
  glGenBuffers(1, &vertBuffer19);

  glGenVertexArrays(1, &vao20);
  glGenBuffers(1, &vertBuffer20);

  glGenVertexArrays(1, &line_vaoID);
  glGenBuffers(1, &line_vertBufferID);
}

void deleteIDs() {
  glDeleteProgram(basicProgramID);
  glDeleteProgram(basicProgramID1);

  glDeleteVertexArrays(1, &vaoID);
  glDeleteBuffers(1, &vertBufferID);

  glDeleteVertexArrays(1, &vao2);
  glDeleteBuffers(1, &vertBuffer2);

  glDeleteVertexArrays(1, &vao3);
  glDeleteBuffers(1, &vertBuffer3);

  glDeleteVertexArrays(1, &vao4);
  glDeleteBuffers(1, &vertBuffer4);

  glDeleteVertexArrays(1, &vao5);
  glDeleteBuffers(1, &vertBuffer5);

  glDeleteVertexArrays(1, &vao6);
  glDeleteBuffers(1, &vertBuffer6);

  glDeleteVertexArrays(1, &vao7);
  glDeleteBuffers(1, &vertBuffer7);

  glDeleteVertexArrays(1, &vao8);
  glDeleteBuffers(1, &vertBuffer8);

  glDeleteVertexArrays(1, &vao9);
  glDeleteBuffers(1, &vertBuffer9);

  glDeleteVertexArrays(1, &vao10);
  glDeleteBuffers(1, &vertBuffer10);

  glDeleteVertexArrays(1, &vao11);
  glDeleteBuffers(1, &vertBuffer11);

  glDeleteVertexArrays(1, &vao12);
  glDeleteBuffers(1, &vertBuffer12);

  glDeleteVertexArrays(1, &vao13);
  glDeleteBuffers(1, &vertBuffer13);

  glDeleteVertexArrays(1, &vao14);
  glDeleteBuffers(1, &vertBuffer14);

  glDeleteVertexArrays(1, &vao15);
  glDeleteBuffers(1, &vertBuffer15);

  glDeleteVertexArrays(1, &vao16);
  glDeleteBuffers(1, &vertBuffer16);

  glDeleteVertexArrays(1, &vao17);
  glDeleteBuffers(1, &vertBuffer17);

  glDeleteVertexArrays(1, &vao18);
  glDeleteBuffers(1, &vertBuffer18);

  glDeleteVertexArrays(1, &vao19);
  glDeleteBuffers(1, &vertBuffer19);

  glDeleteVertexArrays(1, &vao20);
  glDeleteBuffers(1, &vertBuffer20);

  glDeleteVertexArrays(1, &line_vaoID);
  glDeleteBuffers(1, &line_vertBufferID);
}

void init() {
  glEnable(GL_DEPTH_TEST);
  glPointSize(50);

  camera = Camera(Vec3f{0, 0, 20}, Vec3f{0, 0, -1}, Vec3f{0, 1, 0});

  // SETUP SHADERS, BUFFERS, VAOs

  generateIDs();
  setupVAO();
  loadQuadGeometryToGPU();
  loadLineGeometryToGPU();

  loadModelViewMatrix();
  reloadProjectionMatrix();
  setupModelViewProjectionTransform();
  reloadMVPUniform(basicProgramID);
}

int main(int argc, char **argv) {
  GLFWwindow *window;

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window =
      glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "CSE414 Project 1", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetWindowSizeCallback(window, windowSetSizeFunc);
  glfwSetFramebufferSizeCallback(window, windowSetFramebufferSizeFunc);
  glfwSetKeyCallback(window, windowKeyFunc);
  glfwSetCursorPosCallback(window, windowMouseMotionFunc);
  glfwSetMouseButtonCallback(window, windowMouseButtonFunc);

  glfwGetFramebufferSize(window, &WIN_WIDTH, &WIN_HEIGHT);

  // Initialize glad
  if (!gladLoadGL()) {
    std::cerr << "Failed to initialise GLAD" << std::endl;
    return -1;
  }

  std::cout << "GL Version: :" << glGetString(GL_VERSION) << std::endl;
  std::cout << GL_ERROR() << std::endl;

  // Initialize all the geometry, and load it once to the GPU
  init(); // our own initialize stuff func

  float t = 0;
  float dt = 0.01;

  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         !glfwWindowShouldClose(window)) {

    if (g_play) {
      //t += dt;
      t = t + 0.009;
      animateQuad(t);
    }

    displayFunc();
    moveCamera();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // clean up after loop
  deleteIDs();

  return 0;
}

//==================== CALLBACK FUNCTIONS ====================//

void windowSetSizeFunc(GLFWwindow *window, int width, int height) {
  WIN_WIDTH = width;
  WIN_HEIGHT = height;

  reloadProjectionMatrix();
  setupModelViewProjectionTransform();
  reloadMVPUniform(basicProgramID);
}

void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height) {
  FB_WIDTH = width;
  FB_HEIGHT = height;

  glViewport(0, 0, FB_WIDTH, FB_HEIGHT);
}

void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      g_cursorLocked = GL_TRUE;
    } else {
      g_cursorLocked = GL_FALSE;
    }
  }
}

void windowMouseMotionFunc(GLFWwindow *window, double x, double y) {
  if (g_cursorLocked) {
    float deltaX = (x - g_cursorX) * 0.01;
    float deltaY = (y - g_cursorY) * 0.01;
    camera.rotateAroundFocus(deltaX, deltaY);

    reloadViewMatrix();
    setupModelViewProjectionTransform();
    reloadMVPUniform(basicProgramID);
  }

  g_cursorX = x;
  g_cursorY = y;
}

void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods) {
  bool set = action != GLFW_RELEASE && GLFW_REPEAT;
  switch (key) {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  case GLFW_KEY_W:
    g_moveBackForward = set ? 1 : 0;
    break;
  case GLFW_KEY_S:
    g_moveBackForward = set ? -1 : 0;
    break;
  case GLFW_KEY_A:
    g_moveLeftRight = set ? 1 : 0;
    break;
  case GLFW_KEY_D:
    g_moveLeftRight = set ? -1 : 0;
    break;
  case GLFW_KEY_Q:
    g_moveUpDown = set ? -1 : 0;
    break;
  case GLFW_KEY_E:
    g_moveUpDown = set ? 1 : 0;
    break;
  case GLFW_KEY_UP:
    g_rotateUpDown = set ? -1 : 0;
    break;
  case GLFW_KEY_DOWN:
    g_rotateUpDown = set ? 1 : 0;
    break;
  case GLFW_KEY_LEFT:
    if (mods == GLFW_MOD_SHIFT)
      g_rotateRoll = set ? -1 : 0;
    else
      g_rotateLeftRight = set ? 1 : 0;
    break;
  case GLFW_KEY_RIGHT:
    if (mods == GLFW_MOD_SHIFT)
      g_rotateRoll = set ? 1 : 0;
    else
      g_rotateLeftRight = set ? -1 : 0;
    break;
  case GLFW_KEY_SPACE:
    g_play = set ? !g_play : g_play;
    break;
  case GLFW_KEY_LEFT_BRACKET:
    if (mods == GLFW_MOD_SHIFT) {
      g_rotationSpeed *= 0.5;
    } else {
      g_panningSpeed *= 0.5;
    }
    break;
  case GLFW_KEY_RIGHT_BRACKET:
    if (mods == GLFW_MOD_SHIFT) {
      g_rotationSpeed *= 1.5;
    } else {
      g_panningSpeed *= 1.5;
    }
    break;
  default:
    break;
  }
}

//==================== OPENGL HELPER FUNCTIONS ====================//

void moveCamera() {
  Vec3f dir;

  if (g_moveBackForward) {
    dir += Vec3f(0, 0, g_moveBackForward * g_panningSpeed);
  }
  if (g_moveLeftRight) {
    dir += Vec3f(g_moveLeftRight * g_panningSpeed, 0, 0);
  }
  if (g_moveUpDown) {
    dir += Vec3f(0, g_moveUpDown * g_panningSpeed, 0);
  }

  if (g_rotateUpDown) {
    camera.rotateUpDown(g_rotateUpDown * g_rotationSpeed);
  }
  if (g_rotateLeftRight) {
    camera.rotateLeftRight(g_rotateLeftRight * g_rotationSpeed);
  }
  if (g_rotateRoll) {
    camera.rotateRoll(g_rotateRoll * g_rotationSpeed);
  }

  if (g_moveUpDown || g_moveLeftRight || g_moveBackForward ||
      g_rotateLeftRight || g_rotateUpDown || g_rotateRoll) {
    camera.move(dir);
    reloadViewMatrix();
    setupModelViewProjectionTransform();
    reloadMVPUniform(basicProgramID1);
  }
}

std::string GL_ERROR() {
  GLenum code = glGetError();

  switch (code) {
  case GL_NO_ERROR:
    return "GL_NO_ERROR";
  case GL_INVALID_ENUM:
    return "GL_INVALID_ENUM";
  case GL_INVALID_VALUE:
    return "GL_INVALID_VALUE";
  case GL_INVALID_OPERATION:
    return "GL_INVALID_OPERATION";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case GL_OUT_OF_MEMORY:
    return "GL_OUT_OF_MEMORY";
  default:
    return "Non Valid Error Code";
  }
}
