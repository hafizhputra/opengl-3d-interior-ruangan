#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

 //memberikan fileheader yang dibutuhkan
GLuint texture[35];



using namespace std;

// variabel untuk menggerakan kamera
static float ypos = 0, zpos = 0, xpos = 0,
a = -9, b = -5,c =-30;
int z=0;

struct Image {
        unsigned long sizeX;
        unsigned long sizeY;
        char *data;
};

typedef struct Image Image; //struktur data untuk ukuran image #bisa di set sesuai kebutuhan
#define checkImageWidth 164
#define checkImageHeight 164



// membuat texture background
void init(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0); // background abu2
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);


}

//fungsi kotak kosong, belum diisi koordinat. diisi di display()
void kotak(float x1,float y1,float z1,float x2,float y2,float z2)
{
        //depan
        glTexCoord2f(0.0, 0.0);// untuk menghitung kordinat textur
        glVertex3f(x1,y1,z1);   // untuk menggambar obyek 3d
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y1,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y2,z1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y2,z1);

        //atas
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y2,z1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y2,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y2,z2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y2,z2);

        //belakang
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y2,z2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y2,z2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y1,z2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y1,z2);

        //bawah
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y1,z2);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x2,y1,z2);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y1,z1);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x1,y1,z1);

        //samping kiri
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x1,y1,z1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x1,y2,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x1,y2,z2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x1,y1,z2);

        //samping kanan
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x2,y1,z1);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x2,y2,z1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x2,y2,z2);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x2,y1,z2);
}

// fungsi atur kamera dengan keybord
void keyboard(unsigned char key, int x, int y)
{
        switch (key)
        {
                //putar arah jarum jam (menambah derajat putaran)
                case 'z':
                ypos=ypos+5;
                if (ypos>360) ypos=0;
                glutPostRedisplay();
                break;
                //putar berlawanan arah jarum jam (mengurangi derajat putaran)
                case 'x':
                ypos=ypos-5;
                if (ypos>360) ypos=0;
                glutPostRedisplay();
                break;
                //vertikal bawah (menambah koordinat y)
                case 's':
                b = b + 1;
                glutPostRedisplay();
                break;
                //vertikal atas (mengurangi koordinat y)
                case 'w':
                b = b - 1;
                glutPostRedisplay();
                break;
                //horisontal kiri (mengurangi koordinat x)
                case 'a':
                a = a + 1;
                glutPostRedisplay();
                break;
                //horisontal kanan (menambah koordinat x)
                case 'd':
                a = a - 1;
                glutPostRedisplay();
                break;
                //memperbesar objek (menambah koordinat z)
                case 'q':
                c = c + 1;
                glutPostRedisplay();
                break;
                //memperkecil abjek(mengurangi koordinat z)
                case 'e':
                c = c - 1;
                glutPostRedisplay();
                break;

                //putar arah jarum jam (menambah derajat putaran)
                case '[':
                xpos=xpos+5;
                if (xpos>360) xpos=0;
                glutPostRedisplay();
                break;

                //putar berlawanan arah jarum jam (mengurangi derajat putaran)
                case ']':
                xpos=xpos-5;
                if (xpos>360) xpos=0;
                glutPostRedisplay();

        }
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity ();
        glEnable(GL_DEPTH_TEST);
        //perpindahan
        glTranslatef(a,b,c);

        //putaran keyboard
        glRotatef(xpos,1,0,0);
        glRotatef(ypos,0,1,0);
        glRotatef(zpos,0,0,1);

        //lantai bawah
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[1]); // header
                glBegin(GL_QUADS);
                  glColor3f(0.10f, 0.5f, 0.5f); // hijau tosca tua

                        kotak(0,0,18,40,0.5,0); // samping kanan/kiri , atas/bawah, depan/belakang , samping kanan/kiri, atas/bawah, depan/belakang
                glEnd();
        glPopMatrix();

        //lantai atas
     glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[1]);
                glBegin(GL_QUADS);
                  glColor3f(0.10,0.5,0.5);

                        kotak(-10,15,18,40,15.5,0);
                glEnd();
        glPopMatrix();

    //dinding kiri
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);

                      glColor3f(0.0f,-2.0f,1.0f); // biru

                        kotak(6,0.5,18,5.5,35,0);

                glEnd();
        glPopMatrix();


        //dinding kanan
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);

                    glColor3f(0.0f,-2.0f,1.0f); // biru

                        kotak(40,0.5,18,39.5,35,0);

                glEnd();
        glPopMatrix();

//dinding belakang
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                   glColor3f(0.0f,1.0f,1.0f); //tosca
                        kotak(5.5,0.5,0.5,40,35,0.0);
                glEnd();
        glPopMatrix();

   //meja
    //atas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3f(0.2f,0.1f,0.1f); // coklat
                        kotak(13,18.5,16,16.8,18.8,9.5);
                //kaki kanan belakang
                        kotak(13.3,15.5,15.9,13.6,18.6,15.6);
                //kaki kiri belakang
                        kotak(13.3,15.5,9.9,13.6,18.6,9.6);
                //kaki kiri depan
                        kotak(16.1,15.5,9.9,16.4,18.6,9.6);
                //kaki kanan depan
                        kotak(16.1,15.5,15.9,16.4,18.6,15.6);
                glEnd();
        glPopMatrix();


        //laptop
        glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
                glBegin(GL_QUADS);
                    glColor3f(0.0f,0.0f,0.0f);

                        //Monitor lcd
            kotak(16.3, 20.2, 15.0, 16.4, 19.3, 13.0);
            kotak(16.3, 18.8, 15.0, 16.4, 19.3, 13.0);

            //keyboard
            kotak(14.7, 19.0, 15.0, 16.4, 18.6, 13.0);

        glEnd();
        glPopMatrix();

        //layar lcd
        glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[8]);
                glBegin(GL_QUADS);
                    glColor3f(1.1f,1.0f,1.0f); // putih

                    // layar
                        kotak(16.2, 20.05, 15.0, 16.30, 19.2, 13.1);
                glEnd();
        glPopMatrix();

        //kursi
        //alas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(0.2f,0.1f,0.1f);
                    // alas
                        kotak(10, 17.2, 15.5, 12.8, 17.5, 12.8);
            //kanan depan
                        kotak(12.5, 15.5, 15.5, 12.17, 17.5, 15.2);
            //kiri depan
                        kotak(12.5, 15.5, 13.1, 12.17, 17.5, 12.8);
            //kiri belakang
                        kotak(10, 15.5, 13.1, 10.3, 17.2, 12.8);
                //kanan belakang
                        kotak(10, 15.5, 15.5, 10.3, 17.2, 15.2);
            //senderan
                        kotak(10, 19.8, 15.5, 10.2, 16.9, 12.8);
                glEnd();
        glPopMatrix();



        //pintu atas
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,0.0f,0.0f);

            //pintu
                        kotak(6.3, 26.8, 5.5, 5.2, 15.20, 0.5);


                glEnd();
            glPopMatrix();

            //pegangan pintu
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,1.0f,0.0f);

            //pegangan

                    kotak(4.4, 22.8, 4.5, 10.-3, 18.9, 4.8);

                glEnd();
            glPopMatrix();




             //pintu bawah
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,0.0f,0.0f);

            //pintu
                        kotak(6.3, 0.1, 5.5, 5.2, 10.20, 0.5);


                glEnd();
            glPopMatrix();

            //pegangan pintu
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,1.0f,0.0f);

            //pegangan

                    kotak(4.4, 3.8, 4.5, 10.-3, 6.9, 4.8);

                glEnd();
            glPopMatrix();





               //lemari
        //kaki
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(0.2f,0.1f,0.1f);

                        // atas
                        kotak(37, 26.2, 5.5, 25.15, 26.5, 1.8);

                        // bawah
                           kotak(37, 16.2, 5.5, 25.15, 16.5, 1.8);

                        // kaki kanan
                        kotak(38, 15.10, 5.5, 37.15, 26.9, 1.8);

                         // kaki tengah
                        kotak(30, 16.18, 5.5, 32.15, 26.9, 1.8);

                        // kaki kiri
                         kotak(24, 15.10, 5.5, 25.15, 26.9, 1.8);


                glEnd();
        glPopMatrix();


           //lemari

        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,1.0f,0.0f);

                        // badan
                        kotak(37, 16.2, 5.5, 25.15, 26.5, 1.8);



                glEnd();
            glPopMatrix();

                //lemari
        //pegangan
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,0.0f,0.0f);

                        // kanan
                       kotak(32.5, 20.10, 6.5, 33.15, 23.9, 1.8);

                        // kiri
                       kotak(29.13, 20.10, 6.5, 28.50, 23.9, 1.8);



                glEnd();
            glPopMatrix();





          //green screen
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(0.0f,1.0f,0.0f);

                        // kain green screen
                        kotak(6.3, 29.8, 17.5, 6.2, 16.20, 7.5);


                glEnd();
            glPopMatrix();


        //atas green screen
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(0.0f,0.0f,0.0f);


                        kotak(7.3, 30.8, 17.9, 6.2, 29.50, 6.5);


                glEnd();
            glPopMatrix();




               //kursi bawah belakang
        //alas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);

            // pisah
            glColor3f(1.5f,0.3f,0.5f);

                        kotak(6.5, 0.5, 13.1, 6.17, 5.5, 12.8);



                glColor3f(0.2f,0.1f,0.1f); // coklat


                        // alas
                         kotak(28.5, 2.10, 5.1, 16.17, 2.5, 0.8);

                         //senderan
                          kotak(28.5, 6.10, 2.1, 16.17, 2.5, 0.8);


                        //kaki kursi bawah ( kursi belakang )
                         kotak(16.5, 0.5, 1.1, 16.17, 2.5, 1.8);

                          kotak(16.5, 0.5, 5.1, 16.17, 2.5, 5.8);

                          kotak(28.5, 0.5, 1.1, 28.17, 2.5, 1.8);

                            kotak(28.5, 0.5, 5.1, 28.17, 2.5, 5.8);


                            // kursi samping kiri

                            // alas
                            kotak(15.5, 2.10, 12.1, 12.17, 2.5, 7.8);

                            // senderan
                             kotak(12.5, 6.10, 12.1, 12.17, 2.5, 7.8);

                            // kaki

                             kotak(12.5, 0.5, 8.1, 12.17, 2.5, 7.8);

                            kotak(15.5, 0.5, 8.1, 15.17, 2.5, 7.8);

                             kotak(12.5, 0.5, 12.1, 12.17, 2.5, 11.8);

                                kotak(15.5, 0.5, 12.1, 15.17, 2.5, 11.8);


                                  // kursi samping kanan

                                   // alas
                            kotak(32.5, 2.10, 12.1, 29.17, 2.5, 7.8);

                            // senderan
                             kotak(32.5, 6.10, 12.1, 32.17, 2.5, 7.8);

                            // kaki

                             kotak(29.5, 0.5, 8.1, 29.17, 2.5, 7.8);

                            kotak(32.5, 0.5, 8.1, 32.17, 2.5, 7.8);

                             kotak(29.5, 0.5, 12.1, 29.17, 2.5, 11.8);

                                kotak(32.5, 0.5, 12.1, 32.17, 2.5, 11.8);


                                  // meja
                            // alas
                            kotak(26.5, 2.5, 12.1, 18.17, 2.1, 7.8);

                            // kaki meja
                             kotak(25.5, 0.5, 8.1, 25.17, 2.1, 7.8);

                            kotak(19.5, 0.5, 8.1, 19.17, 2.1, 7.8);

                             kotak(25.5, 0.5, 12.1, 25.17, 2.1, 11.8);

                                kotak(19.5, 0.5, 12.1, 19.17, 2.1, 11.8);



                glEnd();
        glPopMatrix();




        //sofa
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(1.0f,1.0f,1.0f);


            //sofa belakang
                         kotak(28.5, 3.10, 5.1, 16.17, 2.5, 0.8);

                         // sofa kiri
                          kotak(15.5, 3.10, 12.1, 12.17, 2.5, 7.8);

                         //sofa kanan
                           kotak(32.5, 3.10, 12.1, 29.17, 2.5, 7.8);





                glEnd();
        glPopMatrix();


          //kipas angin
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);
                    glColor3f(0.0f,0.0f,0.0f);



            // duduka kipas 1
            kotak(23.5,  15.5, 11.1, 23.17, 14.5, 10.8);

             // duduka kipas 2
             kotak(24.5,  13.5, 12.1, 22.17, 14.5, 9.8);


             // baling baling
              glColor3f(1.0f,1.0f,1.0f);

               kotak(22.80,  13.60, 16.1, 23.80, 14.0, 5.8);

               kotak(16.5,  13.55, 11.60, 30.17, 14.0, 10.80);


                glEnd();
        glPopMatrix();




         //pisah
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);

        // pisah
            glColor3f(1.5f,0.3f,0.5f);

                        kotak(6.5, 0.5, 13.1, 6.17, 5.5, 12.8);



                glEnd();
        glPopMatrix();







     //rak buku dinding
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
                glBegin(GL_QUADS);

        // warna
            glColor3f(0.0f,0.0f,0.0f); // hitam

                        // kaki kiri
                        kotak(39.5, 30.5, 15.1, 38.17, 21.5, 15.1);

                        // kaki kanan
                         kotak(39.5, 30.5, 8.1, 38.17, 21.5, 8.1);

                          // alas atas
                         kotak(39.5, 30.5, 15.1, 38.17, 30.1, 8.1);

                         // alas tengah
                         kotak(39.5, 25.5, 15.1, 38.17, 26.1, 8.1);

                          // alas bawah
                         kotak(39.5, 21.5, 15.1, 38.17, 22.1, 8.1);


            // buku
            glColor3f(1.0f,0.0f,0.0f); //merah

            // buku
            // buku belakang
            kotak(39.5, 28.5, 9.6, 38.17, 26.1, 9.1);

            glColor3f(1.0f,1.0f,0.0f); // kuning
            // buku tengah
            kotak(39.5, 28.0, 10.6, 38.17, 26.1, 10.1);

             glColor3f(0.0f,1.0f,0.0f); // hijau
            // buku tengah
            kotak(39.5, 27.5, 11.6, 38.17, 26.1, 11.1);


                glEnd();
        glPopMatrix();





        glFlush();
        glutSwapBuffers();
}





// untuk mengubah garis kolom
void reshape (int w, int h)
{

    glViewport(0, 0, w, h); // untuk membuat view di windows
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // untuk mengatur/menggeser obyek

        gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 40.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, 0.0);

        // menentukan sudut pandang obyek
        gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1024, 600); // ukuran windows
    glutInitWindowPosition (20, 75); // windows tampilan awal keluar
    glutCreateWindow ("Interior Ruangan");

    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
return 0;
}
