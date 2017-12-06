matrix WVPMatrix; // 変換行列
vector LightDirection; // 光の方向

struct S00_INPUT // 入力頂点
{
    vector position : POSITION;
    vector normal   : NORMAL;
};

struct S00_OUTPUT // 出力頂点
{
    vector position : POSITION;
    vector diffuse : COLOR;
};

S00_OUTPUT Main(S00_INPUT input)
{
    S00_OUTPUT output = (S00_OUTPUT) 0; // output行列を初期化
    
    output.position = input.position;

    output.position = mul(output.position, WVPMatrix); // 頂点を3つ変換する
    output.diffuse = dot((-LightDirection), input.normal); // 法線で色を計算
    
    return output;
}