#include <stdlib.h>
#include <GL/glut.h>

// キーボードの処理をどうするかを定義しておいて、後でコールバック関数として呼び出す。
void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

// この関数は後でコールバック関数として呼び出されるため、定義する処理の内容は自由であるが、ここでは2次元のポリゴンを呼び出す処理を書くこととする。
void myDisplay()
{
    // グラフィックス用のフレームバッファ(メモリの一種)をクリア
    // 描写する物体の色をRGBで[0,1]の範囲にて指定。
    // モノを描くために、glBegin()とglEnd(),および、glVertex()を使う。
    // glBegin()を呼び出す。
    // ポリゴンの角を描写1
    // ポリゴンの角を描写2
    // ポリゴンの角を描写3
    // ポリゴンの角を描写4
    // glEnd()を呼び出す。
    // このコマンド以前のGLコマンドを直ちにすべて実行する。つまり、描写を直ちに行うことを意味する。
    //      -> なお、glBegin()とglEnd()の間でglFlush()を呼び出すとエラーになる。
}

// 初期化処理をまとめて関数の中に定義しておく。
void myInit(char *progname)
{
    // ディスプレイモードの宣言
    // ウィンドウサイズの指定(単位はピクセル)
    // ウィンドウの左上の位置を指定する。
    // ウィンドウを生成する
    // glClearがカラーバッファをクリアして設定するときの色を指定する。
}
int main()
{
    // glutInit関数を呼び出す
    // myInit関数を呼び出す
    // ユーザーが定義したキーボード処理関数を呼び出す
    // ユーザーが定義した関数を呼び出す。
    //      -> myDisplayではWindow描写処理が定義してあるので、ここでは描写処理を行うことになる。
    // GLUTを用いたプログラムでは、これを呼び出さないといけなくて、これを呼び出すことで、イベント処理ループを開始する。
    return 0;
}