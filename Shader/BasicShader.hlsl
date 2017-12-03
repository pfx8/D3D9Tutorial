matrix WVPMatrix;	// ワールド、ビュー、プロジェクション変換マトリックス
vector color;					// 頂点カラー

struct VS_INPUT	// 入力頂点構造体
{
	vector position:POSITION;
};

struct VS_OUTPUT	// 出力頂点構造体
{
	vector position : POSITION;
	vector color:COLOR;
};

VS_OUTPUT SetColor(VS_INPUT input)	// カラー設定と３つ変換
{
	VS_OUTPUT output = (VS_OUTPUT)0;	// マトリックスを初期化

	output.position = mul(input.position, WVPMatrix);	// 2つマトリックスかける
	output.color = color;	// カラーを設定

	return output;
}