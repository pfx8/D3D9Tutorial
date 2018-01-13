// プログラムからもらう変数
matrix WVPMatrix;       // WVP変換行列
float3 LightDirection;  // 光方向ベクトル

// シェーダー中の変数
float LightIntensity = 1.0f; // 光の強さ

//------------------------------------------------------
// トゥ―ンシェーダー
//------------------------------------------------------
struct CelVertexIN
{
    float3 position : POSITION;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
};

struct CelVertexOUT
{
    float4 position : POSITION0;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
};

// モデル
// 頂点シェーダー
CelVertexOUT CelVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化
    Out.position = mul(float4(In.position, 1.0), WVPMatrix);
    Out.normal = In.normal;

    return Out;
}
// ピクセルシェーダー
float4 CelPixelShader(CelVertexOUT In) : COLOR0
{
    float value = dot(-LightDirection, In.normal); // 法線と光の内積を計算して、色を決める;
    float4 color = float4(0.89, 0.69, 0.1, 1.0) * LightIntensity; // 赤

    //if(value >0.75)
    //    color = float4(1.0, 1.0, 1.0, 1.0) * color;
    //else if(value > 0.6)
    //    color = float4(0.8, 0.8, 0.8, 1.0) * color;
    //else if(value > 0.35)
    //    color = float4(0.5, 0.5, 0.5, 1.0) * color;
    //else
    //    color = float4(0.2, 0.2, 0.2, 1.0) * color;

    if (value > 0.35)
        color = float4(1.0, 1.0, 1.0, 1.0) * color; // 普段の色
    else
        color = float4(0.6, 0.6, 0.6, 0.5) * color; // シャドーの色

    return color; // 色を戻る
}

// アウトライン
// 頂点シェーダー
CelVertexOUT OutlineVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化

    float4 position = Out.position = mul(float4(In.position, 1.0f), WVPMatrix);
    float4 normal = normalize(mul(float4(In.normal, 1.0f), WVPMatrix));

    Out.position = position + (mul(0.3, -normal)); // 法線の方向へ拡大

    return Out;
}
// ピクセルシェーダー
float4 OutlinePixelShader(CelVertexOUT In) : COLOR0
{
    return float4(0, 0, 0, 1); // 法線と光の内積を計算して、色を決める;
}

technique Outline // トゥ―ンシェーダー
{
    //pass P0 // OutLine
    //{
    //    VertexShader = compile vs_3_0 OutlineVertexShader();
    //    PixelShader = compile ps_3_0 OutlinePixelShader();

    //    CullMode = CW; // 背面を右回りでカリングする
    //}
}

technique CelShader // トゥ―ンシェーダー
{
    //pass P0 // OutLine
    //{
    //    VertexShader = compile vs_3_0 OutlineVertexShader();
    //    PixelShader = compile ps_3_0 OutlinePixelShader();

    //    CullMode = CW;
    //}
    pass P0 // モデル
    {
        VertexShader = compile vs_3_0 CelVertexShader();
        PixelShader = compile ps_3_0 CelPixelShader();

        //CullMode = CCW; // 背面を左回りでカリングする
    }
}