#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)(HW16A048 桂脩也)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H) (HW16A048 桂脩也)
>>>>>>> f82f34b6a1dee4a7edfa11209d4b78efd8fb795a


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
int     upDown;


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-80, -150);
    targetRect = Rect(80, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;


     PlayBGM("bgm_maoudamashii_8bit07.mp3");//hw16a216 山本BGMの追加


    upDown = 1;
>>>>>>> 468fdb54e8402fbaaabdc4ca413a5e9d5509e40c
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);


        PlaySound("se_maoudamashii_system20.mp3");

    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 90 * Time::deltaTime;
        
        if (bulletPos.x > 320)
            bulletPos.x = -999;


        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算 1から100へ hw16a101 須賀
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
           
        }
    }
    
    //大砲の移動　hw16a216 山本
    cannonPos.y += 100 * Time::deltaTime * upDown;
    if(cannonPos.y > -70){
        upDown *= -1;
        cannonPos.y = -70;
    }
    if(cannonPos.y < -145){
        upDown *= -1;
        cannonPos.y = -140;
    }


    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);
    

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    cloudPos.x += 100 *Time::deltaTime;// hw16a216山本　雲の移動を追加
    if(cloudPos.x >400){
        cloudPos.x = -545;
    }

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-100, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    

    // ターゲットの描画
    FillRect(Rect(targetRect.x+100, -140, 40, 40), Color::red);
    
    
    // スコアの描画

    SetFont("nicoca_v1.ttf", 50.0f); //スコアを20から50へ　hw16a101 須賀

    DrawText(FormatString("%05d", score), Vector2(-319, 199), Color::black); //%02dを05に変更 hw16a101 須賀
    DrawText(FormatString("%05d", score), Vector2(-320, 200), Color::white);

}

