// プログラムからもらう変数
// 行列
matrix WMatrix;         // ワールド変換行列
matrix VPMatrix;        // ビューイング変換とプロジェクション変換行列

// ライト
float3 lightDir;        // ライト方向ベクトル
float4 lightDiffuse;    // アンビエント(環境光のカラー)
float4 lightAmbient;    // 拡散反射光(モデル本来のカラー)

// マテリアル

int ObjType;              // 1.プレーヤー 2.敵 3.大砲


//------------------------------------------------------
// トゥ―ンシェーダー
//------------------------------------------------------
struct CelVertexIN
{
    float3 position : POSITION;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ座標
};

struct CelVertexOUT
{
    float4 position : POSITION0;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ座標
};

//texture Tex; // 使用するテクスチャ
//sampler Samp = // サンプラー
//sampler_state
//{
//    Texture = <Tex>;
//    MipFilter = LINEAR;
//    MinFilter = LINEAR;
//    MagFilter = LINEAR;
//};

// モデル
// 頂点シェーダー
CelVertexOUT CelVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化
    Out.position = mul(float4(In.position, 1.0), WMatrix);
    Out.position = mul(Out.position, VPMatrix);
    Out.normal = mul(float4(In.normal, 1.0), WMatrix);
    Out.uvCoords = In.uvCoords;

    return Out;
}
// ピクセルシェーダー
float4 CelPixelShader(CelVertexOUT In) : COLOR0
{
    float value = dot(-lightDir, In.normal); // 法線と光の内積を計算して、色を決める;
    
    float4 color;
    if (ObjType == 0) // ship
    {
        color = float4(0.43, 0.2, 0.0, 1.0);
    }
    else if (ObjType == 1) // 敵
    {
        color = float4(0.63, 0.4, 0.2, 1.0);
    }
    else if (ObjType == 2) // 大砲
    {
        color = float4(0.4, 0.4, 0.4, 1.0);
    }
    else // バウンディングボックス
    {
        color = float4(0.8, 0.0, 0.0, 0.1);
    }

    if (value > 0.35)
        color = float4(1.0, 1.0, 1.0, 1.0) * color; // 普段の色
    else
        color = float4(0.6, 0.6, 0.6, 0.5) * color; // シャドーの色
    return color; // 色だけを戻る

    //float4 diffuse = tex2D(Samp, In.uvCoords) *LightIntensity;
    //float4 diffuse = In.diffuse * LightIntensity;
    //if (value > 0.35)
    //    diffuse = float4(1.0, 1.0, 1.0, 1.0) * diffuse; // 普段の色
    //else
    //    diffuse = float4(0.6, 0.6, 0.6, 0.5) * diffuse; // シャドーの色
    //return diffuse;
    }

// アウトライン
// 頂点シェーダー
CelVertexOUT OutlineVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化

    float4 position = Out.position = mul(float4(In.position, 1.0f), WMatrix);
    position = Out.position = mul(position, VPMatrix);

    float4 normal = normalize(mul(float4(In.normal, 1.0f), WMatrix));

    Out.position = position + (mul(0.2, -normal)); // 法線の方向へ拡大

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
    pass P0 // OutLine
    {
        VertexShader = compile vs_3_0 OutlineVertexShader();
        PixelShader = compile ps_3_0 OutlinePixelShader();

        CullMode = CW;
    }
    pass P1 // モデル
    {
        VertexShader = compile vs_3_0 CelVertexShader();
        PixelShader = compile ps_3_0 CelPixelShader();

        CullMode = CCW; // 背面を左回りでカリングする
    }
}