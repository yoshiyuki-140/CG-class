#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include "stb_image.h"
#include <ctype.h>

// #define imageWidth 700  // テクスチャ画像の縦幅
// #define imageHeight 402 // テクスチャ画像の横幅
#define imageWidth 1600 // テクスチャ画像の縦幅
#define imageHeight 1066 // テクスチャ画像の横幅

static int star1_year = 0, star2_year = 0, star3_year = 0, numec_year = 0;
// エメラルドのマテリアル
GLfloat mtrl_ambient[] = {0.0215, 0.1745, 0.0215, 1.0}, mtrl_diffuse[] = {0.07568, 0.61424, 0.07568, 1.0}, mtrl_specular[] = {0.633, 0.727811, 0.633, 1.0}, mtrl_shiniess[] = {128.0};

unsigned char texImage[imageHeight][imageWidth][3];

// 画像読み取り用の関数
void readPPMImage(char *filename)
{
  FILE *fp;
  int ch, i;

  if ((fp = fopen(filename, "r")) == NULL) // 読み取りモードで指定されたPPMファイルを読み取り
  {
    // ファイル読み取りが失敗したときの処理
    fprintf(stderr, "Cannot open ppm file %s\n", filename);
    exit(1);
  }
  for (i = 0; i < 4; i++)
  { // skip four in header
    while (1)
    {
      if ((ch = fgetc(fp)) != '#')
        break;                           // skip comment
      fgets((char *)texImage, 1024, fp); // dummy read
      while (isspace(ch))
        ch = fgetc(fp); // skip space
    }
    while (!isspace(ch))
      ch = fgetc(fp); // read header
                      /* Newline or other single terminator after header may exist. */
    if (i < 3)
    {
      while (isspace(ch))
        ch = fgetc(fp); // skip terminator
    }
  }
  fread(texImage, 1, imageWidth * imageHeight * 3, fp); // read RGB data
  fclose(fp);
}

void setUpTexture(void)
{
  readPPMImage("./textures/hengao.ppm");
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
}

void myInit(char *progname)
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ディスプレイモードを初期化
  glutInitWindowSize(700, 700);                              // ウィンドウサイズを設定
  glutInitWindowPosition(0, 0);                              // ウィンドウの位置を設定
  glutCreateWindow(progname);                                // ウィンドウを作成
  glEnable(GL_DEPTH_TEST);                                   // 深度テストを有効化
  glEnable(GL_LIGHTING);                                     // 照明を有効化
  GLfloat light_position[] = {0.0, 0.0, 1.0, 1.0};           // 光源の位置
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};              // 白色光
  GLfloat ambient_light[] = {0.2, 0.2, 0.2, 1.0};            // 環境光
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);         // 光源の位置を設定
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);             // 拡散光を設定
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);            // 鏡面光を設定
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);           // 環境光を設定
  glEnable(GL_LIGHT0);                                       // 光源0を有効化
  glClearColor(0.0, 0.0, 0.0, 0.0);                          // 背景色を設定
}

void myDisplay(void)
{
  int evenness = 10;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // カラーバッファとデプスバッファをクリア
  glColor3d(1.0, 1.0, 1.0);                           // 描画色を白に設定
  glPushMatrix();                                     // 現在の行列を保存

  // ナメック星 : こいつは発光しない
  glPushMatrix(); // 現在の行列を保存
  glEnable(GL_TEXTURE_2D);
  glColor3d(0.0, 0.5, 1.0); // 描画色をブルーグリーンに設定
  // これが発光の設定
  // START
  GLfloat emissionN[] = {0.0, 0.0, 0.0, 1.0};     // 発光しないように発光色を設定
  glMaterialfv(GL_FRONT, GL_EMISSION, emissionN); // マテリアルの発光色を設定
  // END

  // ナメック星の材質の設定
  // GLfloat mtrl_ambient[] = {0.0215, 0.1745, 0.0215, 1.0}, mtrl_diffuse[] = {0.07568, 0.61424, 0.07568, 1.0}, mtrl_specular[] = {0.5, 0.5, 0.5, 1.0}, mtrl_shiniess[] = {128.0};
  // glMaterialfv(GL_FRONT, GL_AMBIENT, mtrl_ambient);    // マテリアルの環境光を設定
  // glMaterialfv(GL_FRONT, GL_DIFFUSE, mtrl_diffuse);    // マテリアルの拡散光を設定
  // glMaterialfv(GL_FRONT, GL_SPECULAR, mtrl_specular);  // マテリアルの鏡面光を設定
  // glMaterialfv(GL_FRONT, GL_SHININESS, mtrl_shiniess); // マテリアルの鏡面反射指数を設定

  glRotated((double)numec_year, 0.0, 1.0, 0.0);      // Y軸周りに回転
  glTranslated(7.0, 0.0, 0.0);                       // 位置を移動
  glutSolidSphere(0.3, 10 * evenness, 8 * evenness); // 小さな球体を描画
  // if following code executed, It seems like too dark numec star.
  glDisable(GL_TEXTURE_2D);
  glPopMatrix(); // 保存した行列を復元

  // 太陽 B
  glPushMatrix();                                    // 現在の行列を保存
  glColor3d(1.0, 1.0, 0.0);                          // 描画色を黄色に設定
  GLfloat emissionB[] = {1.0, 1.0, 0.0, 1.0};        // 発光色を設定
  glMaterialfv(GL_FRONT, GL_EMISSION, emissionB);    // マテリアルの発光色を設定
  glRotated((double)star1_year, 0.0, 1.0, 0.0);      // Y軸周りに回転
  glTranslated(4.0, 0.0, 0.0);                       // 位置を移動
  glutSolidSphere(0.4, 10 * evenness, 8 * evenness); // 球体を描画

  // 太陽 C
  glPushMatrix();                                    // 現在の行列を保存
  glColor3d(1.0, 0.5, 0.0);                          // 描画色をオレンジに設定
  GLfloat emissionC[] = {1.0, 0.5, 0.0, 1.0};        // 発光色を設定
  glMaterialfv(GL_FRONT, GL_EMISSION, emissionC);    // マテリアルの発光色を設定
  glRotated((double)star2_year, 0.0, 1.0, 0.0);      // Y軸周りに回転
  glTranslated(1.0, 0.0, 0.0);                       // 位置を移動
  glutSolidSphere(0.3, 10 * evenness, 8 * evenness); // 球体を描画
  glPopMatrix();                                     // 保存した行列を復元
  glPopMatrix();                                     // 保存した行列を復元

  // 太陽A (中心の太陽)
  glColor3d(0.0, 1.0, 0.5);                           // 描画色をシアンに設定
  GLfloat emissionA[] = {1.0, 0.5, 0.0, 1.0};         // 発光色を設定
  glMaterialfv(GL_FRONT, GL_EMISSION, emissionA);     // マテリアルの発光色を設定
  glutSolidSphere(1.0, 20 * evenness, 16 * evenness); // 大きな球体を描画

  glPopMatrix();     // 保存した行列を復元
  glutSwapBuffers(); // バッファを交換して画面に表示
}

void myReshape(int width, int height)
{
  glViewport(0, 0, width, height);                                 // ビューポートを設定
  glMatrixMode(GL_PROJECTION);                                     // 投影行列を選択
  glLoadIdentity();                                                // 投影行列を単位行列にリセット
  gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0); // 透視投影を設定
  glMatrixMode(GL_MODELVIEW);                                      // モデルビュー行列を選択
  glLoadIdentity();                                                // モデルビュー行列を単位行列にリセット
  gluLookAt(0.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);         // 視点を設定
}

void myIdle(void)
{
  int speed_of_year = 1; // 回転速度
  star1_year = (star1_year + 2 * speed_of_year) % 360;
  star2_year = (star2_year + 3 * speed_of_year) % 360;
  star3_year = (star3_year + 4 * speed_of_year) % 360;
  numec_year = (numec_year + speed_of_year) % 360;
  glutPostRedisplay(); // 再描画
}

void myKeyboard(unsigned char key, int x, int y)
{
  int speed_of_year = 2; // 回転速度
  switch (key)
  {
  case 'j': // 'j'キーで前進
    star1_year = (star1_year + 2 * speed_of_year) % 360;
    star2_year = (star2_year + 3 * speed_of_year) % 360;
    star3_year = (star3_year + 4 * speed_of_year) % 360;
    numec_year = (numec_year + speed_of_year) % 360;
    glutPostRedisplay(); // 再描画
    break;
  case 'k': // 'k'キーで後退
    star1_year = (star1_year - 2 * speed_of_year) % 360;
    star2_year = (star2_year - 3 * speed_of_year) % 360;
    star3_year = (star3_year - 4 * speed_of_year) % 360;
    numec_year = (numec_year - speed_of_year) % 360;
    glutPostRedisplay(); // 再描画
    break;
  case 27: // ESCキーで終了
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv); // GLUTを初期化
  myInit(argv[0]);       // 初期設定関数を呼び出し
  setUpTexture();               // テクスチャのセットアップ
  glutKeyboardFunc(myKeyboard); // キーボード関数を設定 
  glutReshapeFunc(myReshape);   // リサイズ関数を設定
  glutIdleFunc(myIdle);         // アイドル関数を設定
  glutDisplayFunc(myDisplay);   // ディスプレイ関数を設定
  glutMainLoop();               // イベント処理ループに入る
  return 0;
}
