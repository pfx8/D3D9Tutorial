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

// ライト
float3 lightDir;        // ライト方向ベクトル
float4 lightDiffuse;    // アンビエント(環境光のカラー)
float4 lightAmbient;    // 拡散反射光(モデル本来のカラー)
float4 lightSpecular;   // 鏡面反射光(スペキュラー)

// マテリアル
float4 materialAmbientColor; // マテリアルのアンビエンド
float4 materialDiffuseColor; // マテリアルのディフェーズ

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
    Out.normal = mul(float4(In.normal, 1.0), WMatrix);

    // UV座標
    Out.uvCoords = In.uvCoords;

    //--------------------------------------------------------------------------------
    //
    // ライティングの計算
    // Global Illumination = AmbientLight + DiffuseLight + SpecularLight + EmissiveLight
    //
    //--------------------------------------------------------------------------------
    float4 globalIlumination = lightAmbient + lightDiffuse + lightSpecular;

    return Out;
}

//------------------------------------------------------
//
// ピクセルシェーダー(トゥ―ンシェーダー)
//
//------------------------------------------------------
float4 CelPixelShader(CelVertexOUT In) : COLOR0
{
    matrix lightWMatrix; // ライト用ワールド変換行列
    lightWMatrix = WMatrix;
    lightWMatrix._42 = 0;

    float3 lightVector = normalize(mul(float4(lightDir, 1.0), WMatrix));
    float value = dot(-lightVector, In.normal); // 法線と光の内積を計算して、色を決める;

    //float value = dot(-lightDir, In.normal); // 法線と光の内積を計算して、色を決める;
    
    float4 color;
    if (ObjType == 0) // ship
    {
       //color = tex2D(texSamp, In.uvCoords) * In.diffuse;
       color = tex2D(texSamp, In.uvCoords);
    }
    else if (ObjType == 1) // 敵
    {
        color = In.diffuse;
    }
    else if (ObjType == 2) // 大砲
    {
        color = In.diffuse;
    }

    // 法線とライトの内積によってカラーを決める
    if (value > 0.85)
        color = float4(1.0, 1.0, 1.0, 1.0) * color; // 正常の色
    else
        color = float4(0.6, 0.6, 0.6, 0.5) * color; // シャドーの色

    return color;
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

    float4 normal = normalize(mul(float4(In.normal, 1.0f), WMatrix));

    Out.position = position + (mul(0.25, -normal)); // 法線の方向へ拡大

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
    pass P1 // モデル
    {
        VertexShader = compile vs_3_0 CelVertexShader();
        PixelShader = compile ps_3_0 CelPixelShader();

        CullMode = CCW; // 背面を左回りでカリングする
    }
}