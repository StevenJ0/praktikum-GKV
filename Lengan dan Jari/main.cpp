// Steven Jonathan Sihombing
// 24060123120044
// Lengan dan jari"

#include <GL/glut.h>


// Angle variables
static int shoulder = 0, elbow = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, finger5 = 0;
// Finger base angles
static int finger1Base = 0, finger2Base = 0, finger3Base = 0, finger4Base = 0, finger5Base = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

// Fungsi untuk menggambar jari yang lebih pendek
void drawFinger(GLfloat baseAngle, GLfloat tipAngle) {
    // Draw finger base part
    glRotatef(baseAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);  // Lebih pendek (dari 0.4)
    glPushMatrix();
    glScalef(0.4, 0.15, 0.15);    // Lebih pendek (dari 0.8) dan lebih proporsional
    glutWireCube(1.0);
    glPopMatrix();
    
    // Draw finger tip part
    glTranslatef(0.2, 0.0, 0.0);  // Lebih pendek (dari 0.4)
    glRotatef(tipAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0); // Lebih pendek (dari 0.4)
    glPushMatrix();
    glScalef(0.3, 0.13, 0.13);    // Lebih pendek (dari 0.8) dan lebih proporsional
    glutWireCube(1.0);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Menggerakkan bahu (shoulder)
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Menggambar bagian atas lengan
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Menggerakkan siku (elbow)
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Menggambar bagian bawah lengan
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Position for hand and fingers
    glTranslatef(1.0, 0.0, 0.0);
    
    // Draw palm/hand
    glPushMatrix();
    glScalef(0.5, 0.5, 0.8);  // Telapak tangan yang lebih proporsional
    glutWireCube(1.0);
    glPopMatrix();
    
    // FINGER 1 (ibu jari) - positioned differently
    glPushMatrix();
    glTranslatef(-0.15, -0.2, 0.0);  // Posisi yang lebih dekat ke telapak
    glRotatef(-90, 0.0, 0.0, 1.0);   // Rotate to position thumb correctly
    drawFinger((GLfloat)finger1Base, (GLfloat)finger1);
    glPopMatrix();
    
    // FINGER 2 (telunjuk)
    glPushMatrix();
    glTranslatef(0.25, 0.2, 0.25);  // Jarak antar jari yang lebih proporsional
    drawFinger((GLfloat)finger2Base, (GLfloat)finger2);
    glPopMatrix();
    
    // FINGER 3 (jari tengah)
    glPushMatrix();
    glTranslatef(0.25, 0.2, 0.08);  // Jarak antar jari yang lebih proporsional
    drawFinger((GLfloat)finger3Base, (GLfloat)finger3);
    glPopMatrix();
    
    // FINGER 4 (jari manis)
    glPushMatrix();
    glTranslatef(0.25, 0.2, -0.08); // Jarak antar jari yang lebih proporsional
    drawFinger((GLfloat)finger4Base, (GLfloat)finger4);
    glPopMatrix();
    
    // FINGER 5 (kelingking)
    glPushMatrix();
    glTranslatef(0.25, 0.2, -0.25); // Jarak antar jari yang lebih proporsional
    drawFinger((GLfloat)finger5Base, (GLfloat)finger5);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Shoulder controls
        case 's': shoulder = (shoulder + 5) % 360;
                  glutPostRedisplay();
                  break;
        case 'S': shoulder = (shoulder - 5) % 360;
                  glutPostRedisplay();
                  break;
        // Elbow controls
        case 'e': elbow = (elbow + 5) % 360;
                  glutPostRedisplay();
                  break;
        case 'E': elbow = (elbow - 5) % 360;
                  glutPostRedisplay();
                  break;
        // Finger 1 (thumb) base controls
        case '1': finger1Base = (finger1Base + 5) % 90;
                  glutPostRedisplay();
                  break;
        case '!': finger1Base = (finger1Base - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 1 (thumb) tip controls
        case 'q': finger1 = (finger1 + 5) % 90;
                  glutPostRedisplay();
                  break;
        case 'Q': finger1 = (finger1 - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 2 (index) base controls
        case '2': finger2Base = (finger2Base + 5) % 90;
                  glutPostRedisplay();
                  break;
        case '@': finger2Base = (finger2Base - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 2 (index) tip controls
        case 'w': finger2 = (finger2 + 5) % 90;
                  glutPostRedisplay();
                  break;
        case 'W': finger2 = (finger2 - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 3 (middle) base controls
        case '3': finger3Base = (finger3Base + 5) % 90;
                  glutPostRedisplay();
                  break;
        case '#': finger3Base = (finger3Base - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 3 (middle) tip controls
        case 'r': finger3 = (finger3 + 5) % 90;
                  glutPostRedisplay();
                  break;
        case 'R': finger3 = (finger3 - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 4 (ring) base controls
        case '4': finger4Base = (finger4Base + 5) % 90;
                  glutPostRedisplay();
                  break;
        case '$': finger4Base = (finger4Base - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 4 (ring) tip controls
        case 't': finger4 = (finger4 + 5) % 90;
                  glutPostRedisplay();
                  break;
        case 'T': finger4 = (finger4 - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 5 (pinky) base controls
        case '5': finger5Base = (finger5Base + 5) % 90;
                  glutPostRedisplay();
                  break;
        case '%': finger5Base = (finger5Base - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Finger 5 (pinky) tip controls
        case 'y': finger5 = (finger5 + 5) % 90;
                  glutPostRedisplay();
                  break;
        case 'Y': finger5 = (finger5 - 5) % 90;
                  glutPostRedisplay();
                  break;
        // Exit program
        case 27: exit(0);
                 break;
        default: break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Hand with Shorter Fingers");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
