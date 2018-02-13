//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

// 頂点IN構造体
struct CelVertexIN
{
    float3 position : POSITION;
    float3 normal : NORMAL0;
    float2 uvCoords : TEXCOORD0; // テクスチャ座標
};

// 頂点OUT構造体
struct CelVertexOUT
{
    float4 position : POSITION0;
    float3 normal : NORMAL0;
    float4 diffuse : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ座標
};

// 行列
matrix WMatrix;         // ワールド変換行列
matrix VPMatrix;        // ビューイング変換とプロジェクション変換行列
matrix rotMatix;        // 回転マトリックス

// ライト
float3 lightDir;        // ライト方向ベクトル
float4 lightDiffuse;    // アンビエント(環境光のカラー)
float4 lightSpecular;   // 鏡面反射光(スペキュラー)

// マテリアル
//float4 materialDiffuseColor; // マテリアルのディフェーズ

int ObjType;                 // 1.プレーヤー 2.敵 3.大砲

// サンプラー
texture tex; // 使用するテクスチャ
sampler texSamp = // サンプラー
sampler_state
{
    Texture = <tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

//------------------------------------------------------
//
// 頂点シェーダー(トゥ―ンシェーダー)
//
//------------------------------------------------------
CelVertexOUT CelVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化

    // 座標変換
    Out.position = mul(float4(In.position, 1.0), WMatrix);
    Out.position = mul(Out.position, VPMatrix);
    
    // 法線変換
    Out.normal = normalize(mul(float4(In.normal, 1.0), rotMatix));

    // UV座標
    Out.uvCoords = In.uvCoords;

    return Out;
}

//------------------------------------------------------
//
// ピクセルシェーダー(トゥ―ンシェーダー)
//
//------------------------------------------------------
float4 CelPixelShader(CelVertexOUT In) : COLOR0
{
    float4 globalIlumination = lightDiffuse + lightSpecular;

    float value = dot(-lightDir, In.normal); // 法線と光の内積を計算して、色を決める;
    
    float4 diffuse;
    if (ObjType == 0) // ship
    {
        diffuse = tex2D(texSamp, In.uvCoords) * globalIlumination;
    }
    else if (ObjType == 1) // 敵
    {
        diffuse = In.diffuse * globalIlumination;
    }
    else if (ObjType == 2) // 大砲
    {
        diffuse = float4(22, 22, 22, 1) * globalIlumination;
    }

    //法線とライトの内積によってカラーを決める
    if (value < 0.85)
        diffuse = float4(0.55, 0.55, 0.55, 0.55) * diffuse;

    return diffuse;
}

//------------------------------------------------------
//
// 頂点シェーダー(アウトライン)
//
//------------------------------------------------------
CelVertexOUT OutlineVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化

    float4 position = Out.position = mul(float4(In.position, 1.0f), WMatrix);
    position = Out.position = mul(position, VPMatrix);

    float4 normal = normalize(mul(float4(In.normal, 1.0f), rotMatix));
    
    //float3 lightVec = normalize(lightDir);

    float value = dot(lightDir, In.normal); // 法線と光の内積を計算

     
    if (value > 0)                          // 法線の方向へ拡大
    {
        Out.position = position - (mul(0.18, normal));
    }
    else
    {
        Out.position = position + (mul(0.18, normal));
    }

        return Out;
    }

//------------------------------------------------------
//
// ピクセルシェーダー(アウトライン)
//
//------------------------------------------------------
float4 OutlinePixelShader(CelVertexOUT In) : COLOR0
{
    return float4(0, 0, 0, 1); // 法線と光の内積を計算して、色を決める;
}

//------------------------------------------------------
//
// 各テクニック
//
//------------------------------------------------------
technique CelShader // トゥ―ンシェーダー
{
    pass P0 // OutLine
    {
        VertexShader = compile vs_3_0 OutlineVertexShader();
        PixelShader = compile ps_3_0 OutlinePixelShader();

        CullMode = CW;
    }
    pass P // モデル
    {
        VertexShader = compile vs_3_0 CelVertexShader();
        PixelShader = compile ps_3_0 CelPixelShader();

        CullMode = CCW;
    }
}