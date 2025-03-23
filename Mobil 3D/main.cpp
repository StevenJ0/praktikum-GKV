// Kode OpenGL dengan GLUT untuk Mobil 3D dengan Depth dan Lighting
// Kamera bisa maju mundur kiri kanan
// Dilengkapi dengan pencahayaan
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f; // posisi awal kamera
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;
int bitmapHeight = 12;
float mobilRotasi = 0.0f; // Rotasi untuk mobilnya

void Reshape(int w1, int h1)
{
    // Fungsi reshape
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f);
}

void orientMe(float ang)
{
    // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int i)
{
    // Fungsi ini untuk maju mundur kamera
    x = x + i*(lx)*0.1;
    z = z + i*(lz)*0.1;
    glLoadIdentity();

    gluLookAt(x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f);
}

void Grid() {
    // Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for(i = Z_MIN; i < Z_MAX; i += gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for(i = X_MIN; i < X_MAX; i += gap)
    {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

// Fungsi untuk membuat persegi panjang 3D
void createBox(float width, float height, float depth) {
    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    // Sisi depan
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);  // Normal menghadap ke depan
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);
    glEnd();

    // Sisi belakang
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);  // Normal menghadap ke belakang
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);
    glEnd();

    // Sisi atas
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);  // Normal menghadap ke atas
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);
    glEnd();

    // Sisi bawah
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);  // Normal menghadap ke bawah
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);
    glEnd();

    // Sisi kanan
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);  // Normal menghadap ke kanan
    glVertex3f(w, -h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, h, d);
    glVertex3f(w, -h, d);
    glEnd();

    // Sisi kiri
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);  // Normal menghadap ke kiri
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);
    glEnd();
}

void DrawRoda(float x, float y, float z, float radius, float thickness) {
    // Fungsi untuk membuat roda mobil secara manual (tanpa glutSolidTorus)
    int i, j;
    int slices = 20;
    int stacks = 10;
    float theta, phi;
    float p1[3], p2[3], p3[3], p4[3], n[3];
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 0, 1, 0); // Rotasi agar roda menghadap ke arah yang benar
    
    glColor3f(0.1, 0.1, 0.1); // Warna hitam untuk ban
    
    // Membuat lingkaran ban (cylinder shape)
    for (i = 0; i < slices; i++) {
        theta = i * 2.0 * M_PI / slices;
        theta += M_PI / 2.0; // Rotasi agar sejajar sumbu Z
        
        for (j = 0; j < stacks; j++) {
            phi = j * 2.0 * M_PI / stacks;
            
            // Perhitungan titik-titik untuk quad
            p1[0] = radius * cos(theta) * cos(phi);
            p1[1] = radius * sin(theta);
            p1[2] = thickness * sin(phi) + radius * 0.2;
            
            p2[0] = radius * cos(theta + 2.0 * M_PI / slices) * cos(phi);
            p2[1] = radius * sin(theta + 2.0 * M_PI / slices);
            p2[2] = thickness * sin(phi) + radius * 0.2;
            
            p3[0] = radius * cos(theta + 2.0 * M_PI / slices) * cos(phi + 2.0 * M_PI / stacks);
            p3[1] = radius * sin(theta + 2.0 * M_PI / slices);
            p3[2] = thickness * sin(phi + 2.0 * M_PI / stacks) + radius * 0.2;
            
            p4[0] = radius * cos(theta) * cos(phi + 2.0 * M_PI / stacks);
            p4[1] = radius * sin(theta);
            p4[2] = thickness * sin(phi + 2.0 * M_PI / stacks) + radius * 0.2;
            
            // Menggambar quad
            glBegin(GL_QUADS);
            glNormal3f(cos(theta) * cos(phi), sin(theta), sin(phi));
            glVertex3fv(p1);
            glNormal3f(cos(theta + 2.0 * M_PI / slices) * cos(phi), sin(theta + 2.0 * M_PI / slices), sin(phi));
            glVertex3fv(p2);
            glNormal3f(cos(theta + 2.0 * M_PI / slices) * cos(phi + 2.0 * M_PI / stacks), sin(theta + 2.0 * M_PI / slices), sin(phi + 2.0 * M_PI / stacks));
            glVertex3fv(p3);
            glNormal3f(cos(theta) * cos(phi + 2.0 * M_PI / stacks), sin(theta), sin(phi + 2.0 * M_PI / stacks));
            glVertex3fv(p4);
            glEnd();
        }
    }
    
    // Membuat sisi-sisi roda (hubcap)
    glColor3f(0.3, 0.3, 0.3); // Warna abu-abu untuk velg
    
    // Sisi luar
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, thickness + radius * 0.2); // Pusat
    for (i = 0; i <= slices; i++) {
        theta = i * 2.0 * M_PI / slices;
        theta += M_PI / 2.0; // Rotasi agar sejajar sumbu Z
        glVertex3f(radius * cos(theta) * 0.8, radius * sin(theta) * 0.8, thickness + radius * 0.2);
    }
    glEnd();
    
    // Sisi dalam
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, -thickness + radius * 0.2); // Pusat
    for (i = slices; i >= 0; i--) {
        theta = i * 2.0 * M_PI / slices;
        theta += M_PI / 2.0; // Rotasi agar sejajar sumbu Z
        glVertex3f(radius * cos(theta) * 0.8, radius * sin(theta) * 0.8, -thickness + radius * 0.2);
    }
    glEnd();
    
    glPopMatrix();
}

void BuatMobil() {
    // Body utama mobil (bagian tengah)
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0); // Posisi mobil
    
    // Body utama - bagian tengah
    glColor3f(1.0, 0.0, 0.0); // Warna merah untuk body utama mobil
    glPushMatrix();
    createBox(2.0, 0.6, 4.0); // Skala untuk membuat body utama
    glPopMatrix();
    
    // Bagian depan mobil (kap mesin)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0); // Posisi kap mesin
    glColor3f(1.0, 0.1, 0.1); // Sedikit lebih gelap untuk kap mesin
    createBox(2.0, 0.5, 0.8); // Skala untuk kap mesin
    glPopMatrix();
    
    // Bagian belakang mobil (bagasi)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 2.0); // Posisi bagasi
    glColor3f(0.9, 0.0, 0.0); // Sedikit lebih gelap untuk bagasi
    createBox(2.0, 0.5, 0.8); // Skala untuk bagasi
    glPopMatrix();
    
    // Bagian kabin (atap mobil)
    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0); // Posisi kabin
    glColor3f(0.1, 0.1, 0.7); // Warna biru tua untuk kabin
    createBox(1.8, 0.6, 2.0); // Skala untuk kabin
    glPopMatrix();
    
    // Kaca depan
    glPushMatrix();
    glTranslatef(0.0, 0.6, -1.0); // Posisi kaca depan
    glRotatef(45, 1.0, 0.0, 0.0); // Miring kaca depan
    glColor3f(0.7, 0.7, 0.9); // Warna biru muda untuk kaca
    createBox(1.7, 0.01, 0.7); // Skala untuk kaca depan
    glPopMatrix();
    
    // Kaca belakang
    glPushMatrix();
    glTranslatef(0.0, 0.6, 1.0); // Posisi kaca belakang
    glRotatef(-45, 1.0, 0.0, 0.0); // Miring kaca belakang
    glColor3f(0.7, 0.7, 0.9); // Warna biru muda untuk kaca
    createBox(1.7, 0.01, 0.7); // Skala untuk kaca belakang
    glPopMatrix();
    
    // Lampu depan - kiri
    glPushMatrix();
    glTranslatef(-0.7, 0.0, -2.4); // Posisi lampu depan kiri
    glColor3f(1.0, 1.0, 0.0); // Warna kuning untuk lampu
    createBox(0.3, 0.3, 0.1); // Skala untuk lampu
    glPopMatrix();
    
    // Lampu depan - kanan
    glPushMatrix();
    glTranslatef(0.7, 0.0, -2.4); // Posisi lampu depan kanan
    glColor3f(1.0, 1.0, 0.0); // Warna kuning untuk lampu
    createBox(0.3, 0.3, 0.1); // Skala untuk lampu
    glPopMatrix();
    
    // Lampu belakang - kiri
    glPushMatrix();
    glTranslatef(-0.7, 0.0, 2.4); // Posisi lampu belakang kiri
    glColor3f(1.0, 0.0, 0.0); // Warna merah untuk lampu belakang
    createBox(0.3, 0.3, 0.1); // Skala untuk lampu
    glPopMatrix();
    
    // Lampu belakang - kanan
    glPushMatrix();
    glTranslatef(0.7, 0.0, 2.4); // Posisi lampu belakang kanan
    glColor3f(1.0, 0.0, 0.0); // Warna merah untuk lampu belakang
    createBox(0.3, 0.3, 0.1); // Skala untuk lampu
    glPopMatrix();
    
    // Membuat Roda (menggunakan fungsi DrawRoda kustom)
    DrawRoda(-1.0, -0.3, -1.5, 0.4, 0.2); // Roda depan kiri
    DrawRoda(1.0, -0.3, -1.5, 0.4, 0.2);  // Roda depan kanan
    DrawRoda(-1.0, -0.3, 1.5, 0.4, 0.2);  // Roda belakang kiri
    DrawRoda(1.0, -0.3, 1.5, 0.4, 0.2);   // Roda belakang kanan
    
    glPopMatrix();
}

void display() {
    // Kalau move dan angle tidak nol, gerakkan kamera...
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Gambar grid
    Grid();
    
    // Gambar mobil dengan rotasi
    glPushMatrix();
    glRotatef(mobilRotasi, 0.0, 1.0, 0.0); // Rotasi mobil
    BuatMobil();
    glPopMatrix();
    
    mobilRotasi += 0.1; // Rotasi mobil pelan-pelan
    if(mobilRotasi > 360) mobilRotasi = 0;
    
    glutSwapBuffers();
    glFlush();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) // Tombol ESC
        exit(0);
}

void pressKey(int key, int x, int y) {
    // Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
    // Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
        case GLUT_KEY_UP : deltaMove = 1; break;
        case GLUT_KEY_DOWN : deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
    // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
    // Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti
    switch (key) {
        case GLUT_KEY_LEFT :
            if (deltaAngle < 0.0f)
                deltaAngle = 0.0f;
            break;
        case GLUT_KEY_RIGHT : 
            if (deltaAngle > 0.0f)
                deltaAngle = 0.0f;
            break;
        case GLUT_KEY_UP : 
            if (deltaMove > 0)
                deltaMove = 0;
            break;
        case GLUT_KEY_DOWN : 
            if (deltaMove < 0)
                deltaMove = 0;
            break;
    }
}

// Variable untuk pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting(){
    // Fungsi mengaktifkan pencahayaan
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.2, 0.2, 0.3, 1.0); // Warna background biru gelap
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mobil 3D dengan Depth dan Lighting - GLUT");
    
    glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus)
    
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(display); // Fungsi display-nya dipanggil terus-menerus
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    
    lighting();
    init();
    
    glutMainLoop();
    return(0);
}
