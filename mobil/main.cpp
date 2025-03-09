#include <GL/glut.h>
#include <cmath>

float carPosition = 0.0f; // Variabel untuk menyimpan posisi mobil

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Langit biru
    glBegin(GL_QUADS);
    glColor3f(0.53, 0.81, 0.98); // Warna biru langit
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glColor3f(0.68, 0.85, 0.90); // Warna biru langit yang lebih terang
    glVertex2f(1.0, -0.5);
    glVertex2f(-1.0, -0.5);
    glEnd();

    // Jalanan
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2); // Warna abu-abu gelap
    glVertex2f(-1.0, -0.5);
    glVertex2f(1.0, -0.5);
    glColor3f(0.4, 0.4, 0.4); // Warna abu-abu terang
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    // Garis jalan
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0); // Warna kuning
    glVertex2f(-1.0, -0.75);
    glVertex2f(1.0, -0.75);
    glEnd();

    // Mobil
    glPushMatrix(); // Stack utama
    glTranslatef(carPosition, 0.0f, 0.0f); // Geser mobil berdasarkan posisi

    // Badan mobil
    glColor3f(0.0, 0.0, 1.0); // Warna biru
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.6);  // Posisi bawah kiri
        glVertex2f(0.5, -0.6);   // Posisi bawah kanan
        glVertex2f(0.4, -0.3);   // Posisi atas kanan
        glVertex2f(-0.4, -0.3);  // Posisi atas kiri
    glEnd();
    
    // Atap mobil
    glColor3f(0.0, 1.0, 1.0); // Warna cyan
    glBegin(GL_POLYGON);
        glVertex2f(-0.3, -0.3);  // Posisi bawah kiri
        glVertex2f(0.3, -0.3);   // Posisi bawah kanan
        glVertex2f(0.2, -0.1);   // Posisi atas kanan
        glVertex2f(-0.2, -0.1);  // Posisi atas kiri
    glEnd();
    
    // Kaca depan
    glColor3f(0.8, 0.8, 0.8); // Warna abu-abu terang
    glBegin(GL_POLYGON);
        glVertex2f(-0.2, -0.3);  // Posisi bawah kiri
        glVertex2f(0.2, -0.3);   // Posisi bawah kanan
        glVertex2f(0.1, -0.2);   // Posisi atas kanan
        glVertex2f(-0.1, -0.2);  // Posisi atas kiri
    glEnd();
    
    // Roda kiri
    glColor3f(0.0, 0.0, 0.0); // Warna hitam
    glPushMatrix();
    glTranslatef(-0.3, -0.6, 0.0); // Geser ke kiri dan ke bawah
    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++) {
            float theta = i * 3.1415926 / 180;
            glVertex2f(0.1 * cos(theta), 0.1 * sin(theta));
        }
    glEnd();
    glPopMatrix();
    
    // Roda kanan
    glPushMatrix();
    glTranslatef(0.3, -0.6, 0.0); // Geser ke kanan dan ke bawah
    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++) {
            float theta = i * 3.1415926 / 180;
            glVertex2f(0.1 * cos(theta), 0.1 * sin(theta));
        }
    glEnd();
    glPopMatrix();
    
    glPopMatrix(); // Akhir stack utama

    glFlush();
}

void keyboard(int key, int x, int y) {
    float moveAmount = 0.1f; // Jumlah pergerakan mobil

    switch (key) {
        case GLUT_KEY_LEFT:
            carPosition -= moveAmount; // Geser mobil ke kiri
            break;
        case GLUT_KEY_RIGHT:
            carPosition += moveAmount; // Geser mobil ke kanan
            break;
    }

    glutPostRedisplay(); // Minta OpenGL untuk menggambar ulang
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Background putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mobil 2D dengan Background Jalanan dan Langit Biru");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard); // Daftarkan fungsi keyboard khusus untuk tombol panah
    glutMainLoop();
    return 0;
}
