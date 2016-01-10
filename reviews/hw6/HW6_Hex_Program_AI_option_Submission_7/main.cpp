#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include "hexboard.h"

#ifdef __linux
#include <GL/gl.h>
#include <GL/glut.h>
#elif __unix
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

using namespace std;

//The graph used for the AI
graph test1(11);
colors_t Pcolor;
colors_t AIcolor;
bool playerSwap = false;
bool AIswap = true;
bool gameOver = false;

//Gets the j to use for the graph vector
int findYcoor(float yLocation){
  int j = ((yLocation-3)/(-0.15))+0.2;
  return j;
}

//Get the i to use for the graph vector
int findXcoor(float xLocation, int yCoor) {
  int i = ( ( (xLocation-0.625)-(0.0875*yCoor) )/0.175)+0.2;
  return i;
}

//The shape superclass
class Shape{
public:
  float xLoc;
  float yLoc;
  float scaleFactor;
virtual void specificDraw() const;

public:
  static vector<Shape *> drawList;
  static Shape* cursor;
  Shape(float x, float y, float s);
  void draw() const;
  void addMove(float x, float y){xLoc += x; yLoc += y;};
  void scale(float s){scaleFactor = s;};
};

vector<Shape*> Shape::drawList = vector<Shape*>();


//Shape constructor
Shape::Shape(float x, float y, float s): 
  xLoc(0),yLoc(0),scaleFactor(1){
  this->xLoc = x;
  this->yLoc = y;
  this->scaleFactor = s;
}

//Shape Draw:
void Shape::draw() const{
    glPushMatrix();
    glTranslatef(xLoc,yLoc,0);
    glScalef(scaleFactor,scaleFactor,1);
    
    this->specificDraw();
    glPopMatrix();
  };

//Shape Specific Draw:
void Shape::specificDraw() const{
  cout << "Virtual specific draw\n";
}


//The Hexgon class
class Hexagon : public Shape{
public:
  Hexagon(float x, float y, float s, float c1, float c2, float c3, bool fillHex);
protected:
  //colors
  float c1;
  float c2;
  float c3;
  //use to fill the hexagon instead of make a border hex
  bool fillHex = false;
  void specificDraw() const;
};

Hexagon::Hexagon(float x, float y, float s, float c1, float c2, float c3, bool fillHex):Shape(x,y,s){
  this->c1 = c1;
  this->c2 = c2;
  this->c3 = c3;
  this->fillHex = fillHex;
}

void Hexagon::specificDraw() const{
  glColor3f(this->c1,this->c2,this->c3);
  if(!this->fillHex){
    glBegin(GL_LINES);
  }else{
    glBegin(GL_POLYGON);
  }
  //draws the Hexgon using circles
  glVertex2d(sin(0/6.0*2*M_PI), cos(0/6.0*2*M_PI) );
  for(int i = 1; i < 6; ++i) {
    glVertex2d(sin(i/6.0*2*M_PI), cos(i/6.0*2*M_PI) );
    glVertex2d(sin(i/6.0*2*M_PI), cos(i/6.0*2*M_PI) );
  }
  glVertex2d(sin(0/6.0*2*M_PI), cos(0/6.0*2*M_PI) );

  glEnd();
}

// the cursor
Shape* Shape::cursor = new Hexagon(0.625,3,0.08,1,0,0,false);
//----------------
//Text class:
class Text : public Shape{
public:
  string text;
  Text(float x, float y, float s, string t);
  
private:
  void specificDraw() const;
};

Text::Text(float x, float y, float s, string t):Shape(x,y,s){
    this->text = t;
}

void Text::specificDraw() const{
  for(auto i : text){
  //for(int i=0; i<this->text.length(); ++i){
    glutStrokeCharacter(GLUT_STROKE_ROMAN, i);
  }
}



//Main draw callback:
void drawStuff(){
  

  //Standard initialisation stuff:
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 

  //Viewpoint:
    //Left, right, bottom, top, near, far    
  glOrtho(-0.0, 4.0, -0.0, 4.0, -2.0, 500.0); 
  glMatrixMode(GL_MODELVIEW);
    
  for(vector<Shape *>::iterator it = Shape::drawList.begin();
      it != Shape::drawList.end(); ++it){
    (*it)->draw();
  }

  glPushMatrix();
  glTranslatef(0,0,1);
  (Shape::cursor)->draw();
  glPopMatrix();

  glutSwapBuffers(); 
}



static void idle(){
  for(vector<Shape *>::iterator it = Shape::drawList.begin();
      it != Shape::drawList.end(); ++it){
    //(*it)->addMove(0.1, 0);
  }

  glutPostRedisplay();
}

// makes the initial board
void setupDrawList(){

  for(int i = 0; i<11; i++) {
    for(int j= 0; j<11; j++) {
      Shape::drawList.push_back(new Hexagon(0.625+(0.175*i)+(0.0875)*j, 3+(-0.15*j), 0.1, 0, 1, 0, false));
    }
  }
  //Shape::drawList.push_back(new Text(2,2,0.005,"hello"));

}

//the Keyboard inputs
void key(unsigned char key, int a, int b){
  int yCoor = findYcoor(Shape::cursor->yLoc);
  int xCoor = findXcoor(Shape::cursor->xLoc, yCoor);
  switch(key){
  //up  
  case 'a':
    if(xCoor > 0) {
      Shape::cursor->addMove(-0.175,0);
      xCoor = xCoor-1;
    }
    break;
  //right
  case 'd':
    if(xCoor < 10) {
      Shape::cursor->addMove(0.175,0);
      xCoor = xCoor+1;
    }
    break;
  //down
  case 's':
    if(yCoor < 10) {
      Shape::cursor->addMove(.0875,-0.15);
      yCoor = yCoor+1;
    }
    break;
  //left
  case 'w':
    if(yCoor > 0) {
      Shape::cursor->addMove(-.0875, 0.15);
      yCoor = yCoor-1;
    }
    break;
  }
  //the filling of the board
  if(key =='r' && !gameOver){
    //player movement
    if(Pcolor == white){
      Shape::drawList.push_back(new Hexagon(Shape::cursor->xLoc, Shape::cursor->yLoc, 0.1, 1, 0, 0, true));
    }else{
      Shape::drawList.push_back(new Hexagon(Shape::cursor->xLoc, Shape::cursor->yLoc, 0.1, 0, 0, 1, true));
    }
    bool move = test1.playerMovement(Pcolor, xCoor, yCoor, playerSwap);
	if(playerSwap) {
    playerSwap = false;
    Shape::drawList.clear();
    setupDrawList();
    Shape::drawList.push_back(new Hexagon(Shape::cursor->xLoc, Shape::cursor->yLoc, 0.1, 0, 0, 1, true));
  }
    if(test1.searchForWinner(false) != empty){
      cout << "Winner is the player" << endl;
      cout << "to restart press q" << endl;
      gameOver = true;
    }
    //AI movement
    if(move){
      pair<int, int> AImove = test1.newMovement(AIcolor, AIswap);
      if(Pcolor == white){
        Shape::drawList.push_back(new Hexagon(0.625+(0.175*AImove.first)+(0.0875)*AImove.second,
                                            3+(-0.15*AImove.second), 0.1, 0, 0, 1, true));
      }else{
        Shape::drawList.push_back(new Hexagon(0.625+(0.175*AImove.first)+(0.0875)*AImove.second,
                                            3+(-0.15*AImove.second), 0.1, 1, 0, 0, true));
      }
	  if(AIswap) {
      AIswap = false;
      Shape::drawList.clear();
      setupDrawList();
      Shape::drawList.push_back(new Hexagon(0.625+(0.175*AImove.first)+(0.0875)*AImove.second,
                                            3+(-0.15*AImove.second), 0.1, 0, 0, 1, true));
    }
      if(test1.searchForWinner(false) != empty){
        cout << "Winner is the AI" << endl;
        cout << "to restart press q" << endl;
        gameOver = true;
      }
    }
  }
  //restarting the board.
  if(key == 'q'){
    Shape::drawList.clear();
    setupDrawList();
    test1.clearG1();
    gameOver = false;
    cout << "use AWSD to move, R to fill up a space, and Q to restart" << endl;
    cout << "Red wins UP and Blue wins ACROSS" << endl;
    cout << "Do you want to be Red (press 0) or Blue (press 1)" << endl;
  }

}



int main(int argc, char **argv){
  cout << "use AWSD to move, R to fill up a space, and Q to restart" << endl;
  cout << "Red wins UP and Blue wins ACROSS" << endl;
  cout << "Do you want to be Red (press 0) or Blue (press 1)" << endl;
  Pcolor = empty;
  int pInput = -1;
  cout << "Enter color: ";
  cin >> pInput;
  if(pInput == 0)  Pcolor = white;
  if(pInput == 1)  Pcolor = black;
  AIcolor = black;
  if(Pcolor == black) AIcolor = white;
  //setup the board
  setupDrawList();
  //making the AI go first
  if(AIcolor == white){
    pair<int, int> AImove = test1.newMovement(AIcolor, AIswap);
    Shape::drawList.push_back(new Hexagon(0.625+(0.175*AImove.first)+(0.0875)*AImove.second,
                                          3+(-0.15*AImove.second), 0.1, 1, 0, 0, true));
	playerSwap = true;
	AIswap = false;
  }
  

  //If there is a display, do something.
  if(getenv("DISPLAY")){
      std::string display (getenv("DISPLAY"));
      std::cout << display << std::endl;

      

      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
      glutInitWindowSize(500,500); //Set the size you want
      glutCreateWindow("GL Primer"); //Window name
        

      glutDisplayFunc(drawStuff); //Callback for the current window
      glutKeyboardFunc(key);
      glutIdleFunc(idle);
      glutMainLoop();
  }else{ //otherwise complain
    std::cout <<"arg no display" << std::endl;
  }

  return 0;

}
