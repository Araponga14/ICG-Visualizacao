#include <GL/glut.h>

GLfloat angle, fAspect;

// Função callback chamada para fazer o desenho
void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa buffers de cor e profundidade
    glColor3f(0.0f, 1.0f, 0.0f);

    // Aplica uma rotação de 30 graus ao redor do eixo X
    glPushMatrix();  // Salva a matriz corrente
    glRotatef(10.0f, 0.0f, 0.0f, 1.0f); // Rotação de 30 graus no eixo X

    // Desenha o teapot
    glutWireTeapot(50.0f);

    glPopMatrix();  // Restaura a matriz anterior

    // Executa os comandos OpenGL
    glutSwapBuffers();
}


void EspecificaParametrosVisualizacao(void) {
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();
    // Especifica a projeção perspectiva
    gluPerspective(angle,fAspect,0.1,500);
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
    // gluLookAt(100, 200, 100, 0, 0, 0, 1, 1, 1); // para alterar a posicao da camera
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;
    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;
    EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) { // Zoom-in
            if (angle >= 10) angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) { // Zoom-out
            if (angle <= 130) angle += 5;
        }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void Inicializa(void) {
    // Define a cor de fundo da janela
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Branco
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f); Preto
    // glClearColor(1.0f, 0.0f, 0.0f, 1.0f); Vermelho

    // Inicializa o ângulo de visão
    angle = 60; // possivel alterar o zoom com 30 (mais próximo) ou 60 (mais afastado)

    // Habilita o teste de profundidade (para 3D correto)
    glEnable(GL_DEPTH_TEST);
}


// Programa Principal
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa a GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(350,300);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    Inicializa();
    glutMainLoop();
}
