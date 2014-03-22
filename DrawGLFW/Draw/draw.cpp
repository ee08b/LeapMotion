#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <objloader.hpp>
#include "draw.hpp"

std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;

double rotate_y=0; 
double rotate_x=0;
double rotate_z=0;


double translate_y=0;
double translate_x=0;
double translate_z=0;


float scale = 1.0;

bool diffuse = false;
bool emissive = false;
bool specular = false;
bool mesh = false;

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; //set the material to red
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuselight to white
GLfloat mShininess[] = {128}; //set the shininess of the material

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);

    if (mods == GLFW_MOD_SHIFT){
        if (key == GLFW_KEY_UP)
            translate_y += 0.1;
        if (key == GLFW_KEY_DOWN)
            translate_y -= 0.1;
        if (key == GLFW_KEY_LEFT)
            translate_x -= 0.1;
        if (key == GLFW_KEY_RIGHT)
            translate_x += 0.1;
        return;
    }
    if (key == GLFW_KEY_UP)
        rotate_x -= 5;
    if (key == GLFW_KEY_DOWN)
        rotate_x += 5;
    if (key == GLFW_KEY_LEFT)
        rotate_y += 5;
    if (key == GLFW_KEY_RIGHT) 
        rotate_y -= 5;


    if(key == GLFW_KEY_M && action == GLFW_PRESS){
        if(mesh == false){
            mesh = true;
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
        }else{
            mesh = false;
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
        }
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {   
        if (specular==false)
        {   
            specular = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, 
                    whiteSpecularMaterial); 
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
        }
        else if (specular==true)
        {
            specular = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,
                    blankMaterial);
        }   
    }       

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {   
        if (diffuse==false)
        {   
            diffuse = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
                    redDiffuseMaterial);
        }
        else if (diffuse==true)
        {   
            diffuse = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
        }   
    }       

    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {   
        if (emissive==false)
        {   
            emissive = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
                    greenEmissiveMaterial);
        }
        else if (emissive==true)
        {
            emissive = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
        }
    }

    if (key == GLFW_KEY_KP_ADD) {
        scale *= 1.1;
    }

    if (key == GLFW_KEY_KP_SUBTRACT) {
        scale *= 0.9;
    }


}

void setlight(){
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}


void draw(void* s){
    
  char* filename = (char *) s;

    loadOBJ(filename, vertices, normals);
    
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Draw", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);


    while (!glfwWindowShouldClose(window))
    {   
        //Added Code
        glClearColor (0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        //
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //ratio = width / (float) height;
        //glViewport(0, 0, width, height);
        //glClear(GL_COLOR_BUFFER_BIT);
        //glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        //Added Code
        setlight();
    
        glTranslatef(translate_x,  0.0, 0.0);
        glTranslatef(0.0, translate_y,  0.0);
        glRotatef( rotate_x, 1.0, 0.0, 0.0 );
        glRotatef( rotate_y, 0.0, 1.0, 0.0 );
        glScalef( scale, scale, scale);

        for (unsigned int i = 0; i < vertices.size(); i+=3) {
            if(!mesh) 
                glBegin(GL_POLYGON);
            else
                glBegin(GL_LINE_LOOP);
            glColor3f(1.0, 1.0, 1.0); 
            for (unsigned int j = 0; j < 3; j++) {
                glNormal3f(normals[i+j].x, normals[i+j].y, normals[i+j].x);
                glVertex3f(vertices[i+j].x, vertices[i+j].y, vertices[i+j].z);
            }
            glEnd();
        }
        

        /*
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();      
        */
        
        glfwSwapBuffers(window);
        //glfwPollEvents();
	wait();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
  
}

/*

int main(int argc, char* argv[])
{


    if (argc > 1)
        loadOBJ(argv[1], vertices, normals);
    
    
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Draw", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);


    while (!glfwWindowShouldClose(window))
    {   
        //Added Code
        glClearColor (0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        //
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //ratio = width / (float) height;
        //glViewport(0, 0, width, height);
        //glClear(GL_COLOR_BUFFER_BIT);
        //glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        //Added Code
        setlight();
    
        glTranslatef(translate_x,  0.0, 0.0);
        glTranslatef(0.0, translate_y,  0.0);
        glRotatef( rotate_x, 1.0, 0.0, 0.0 );
        glRotatef( rotate_y, 0.0, 1.0, 0.0 );
        glScalef( scale, scale, scale);

        for (unsigned int i = 0; i < vertices.size(); i+=3) {
            if(!mesh) 
                glBegin(GL_POLYGON);
            else
                glBegin(GL_LINE_LOOP);
            glColor3f(1.0, 1.0, 1.0); 
            for (unsigned int j = 0; j < 3; j++) {
                glNormal3f(normals[i+j].x, normals[i+j].y, normals[i+j].x);
                glVertex3f(vertices[i+j].x, vertices[i+j].y, vertices[i+j].z);
            }
            glEnd();
        }
        

        /*
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();      
        */
        
        glfwSwapBuffers(window);
        //glfwPollEvents();
	wait();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
*/