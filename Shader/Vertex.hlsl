matrix WVPMatrix;	// ワールド、ビュー、プロジェクション変換マトリックス

vector LightDirection;	// 光の方向ベクトル
vector Scalar;		// モーフィング計算
					// T総時間、t変換時間
					// Scalar = t / T
					// C = A * (1-S) + B * S

struct VS_INPUT	// 入力頂点構造体
{
	// 1st頂点stream
	vector position	: POSITION;
	vector normal		: NORMAL;

	// 2nd頂点stream
	vector position1	: POSITION1;
	vector normal1	: NORMAL;

	// テクスチャ座標  
	float2 uvCoords	: TEXCOORD;
};

struct VS_OUTPUT	// 出力頂点構造体
{
	vector position	: POSITION;
	vector diffuse	: COLOR;
	float2 uvCoords	: TEXCOORD;
};

VS_OUTPUT SetColor(VS_INPUT input)	// カラー設定と３つ変換
{
	VS_OUTPUT output = (VS_OUTPUT)0;	// マトリックスを初期化

	output.position = input.position*Scalar.x + input.position1*Scalar.y;	// 頂点計算
	output.position = mul(output.position, WVPMatrix);					// 3つ変換

	vector normal = input.normal * Scalar.x + input.position1 * Scalar.y;	// 法線計算
    output.diffuse = dot((-LightDirection), normal);	// 法線と光の内積を計算して、色を決める

    output.uvCoords = input.uvCoords;

	return output;
}