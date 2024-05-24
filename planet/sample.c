#include <stdlib.h>
#include <GL/glut.h>

static int year = 0, day = 0;

// ウィンドウの初期化
void myInit(char *progname)
{
    // RGBAの色指方法でダブルバッファリングを行う
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    // 画面サイズの設定
    glutInitWindowSize(500, 500);
    // 画面の左上の位置を座標の0,0に指定
    glutInitWindowPosition(0, 0);
    // ウィンドウの作成
    glutCreateWindow(progname);
    // 背景色の設定(描写バッファをクリアする際の色の設定)
    // void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    glClearColor(0.0, 0.0, 0.0, 0.0); // 完全に透明な黒
}

// フレーム毎に行う処理を定義する関数(のちにコールバック関数として使う)
void myDisplay(void)
{
    // 一度画面を塗りつぶしてリセット
    glClear(GL_COLOR_BUFFER_BIT);
    // 後続の描写の色を設定 -> ここではRGB=(1,1,1)で白色を指定している。
    glColor3d(1.0, 1.0, 1.0);

    // 現在の変換行列を保存
    glPushMatrix();

    // 太陽をワイヤーフレームで描写
    // void glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
    // radius : 球体の半径, slices : 球体の経度方向(縦方向)の分割数, stacks : 球体の緯度方向(横方向)の分割数
    glutWireSphere(1.0, 20, 16); // 太陽

    // 指定された角度だけオブジェクトを回転させるための変換を適用する。
    // void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
    //      - angle : 回転角度(度単位)
    //      - x,y,z : 回転軸を表すベクトルの成分
    glRotated((double)year, 0.0, 1.0, 0.0);

    // 地球の位置に平行移動
    glTranslated(2.0, 0.0, 0.0);

    // dayだけ、y軸を中心として、angl[deg]だけオブジェクトを回転させる。
    glRotated((double)day, 0.0, 1.0, 0.0);

    // 地球をワイヤーフレームで描写
    glutWireSphere(0.2, 10, 8); // 地球
    // スタックに保存した変換行列を復元
    glPopMatrix();

    // バックバッファとフロントバッファを入れ替え。
    glutSwapBuffers();
}

// ウィンドウのサイズが変更された時に呼び出される関数。
void myReshape(int width, int height)
{
    // 生成したウィンドウ全体を描写領域に設定。
    // ビューポートとは、画像が実際に表示されるウィンドウの部分を指定します。
    glViewport(0, 0, width, height);
    // 操作する行列スタックを投影行列のスタックに設定する。
    glMatrixMode(GL_PROJECTION); // ビューポート
    // 現在選択されている行列を単位行列にリセットする。
    glLoadIdentity();

    // 透視投影変換行列を設定
    gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);

    // 操作する行列スタックをモデルビュー行列用の行列スタックに切り替える。
    glMatrixMode(GL_MODELVIEW);

    // 現在選択されている行列を単位行列にリセットする。
    glLoadIdentity();

    // 視点と注視点、および視点の上方向となるベクトルをしていする。
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// キーボードの処理を行うために使う関数
void myKeyboard(unsigned char key, int x, int y)
{
    int speed_of_day = 10, speed_of_year = 5;
    switch (key)
    {
    case 'j':
        day = (day + speed_of_day) % 360;

        // 再描写
        glutPostRedisplay();
        break;
    case 'k':
        day = (day - speed_of_day) % 360;

        // 再描写
        glutPostRedisplay();
        break;
    case 'J':
        year = (year + speed_of_year) % 360;

        // 再描写
        glutPostRedisplay();
        break;
    case 'K':
        year = (year - speed_of_year) % 360;

        // 再描写
        glutPostRedisplay();
        break;
    case 27: // これは多分エスケープキー10進数
        exit(0);
        break;
    default:
        break;
    }
}

// メインの処理を行うための関数
// 処理のルート
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);

    // キーボード操作関連の処理をコールバック関数で指定。
    glutKeyboardFunc(myKeyboard);

    // ウィンドウのサイズが変更された時に呼び出される関数。
    glutReshapeFunc(myReshape);

    // フレーム毎に行う処理をコールバック関数として定義してあるので、それをセッティング
    glutDisplayFunc(myDisplay);

    // 描写ループの開始
    glutMainLoop();

    return 0;
}
