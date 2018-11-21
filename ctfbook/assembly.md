# アセンブリ言語とかのまとめ

## レジスタとスタック

### レジスタの種類

- 6つの汎用レジスタと特殊レジスタ、フラグレジスタ、セグメントレジスタがある
- 32bitのレジスタ長をもつ
- 汎用レジスタのA, C, D, Bは下位16bitに*Xレジスタ、そのうち上位8bitは*Hレジスタ、そのうち下位8bitは*Lレジスタと呼ぶ
- ESI, EDIレジスタの下位16bitはSI, DIレジスタと呼ぶ

### レジスタの役割

- 厳密な役割はない
- x86-64はレジスタ幅が64bit
- 64bitの時はRAX, RCX, RDX, RBXなどになり、下位32bitにE*Xなどがある

#### 汎用レジスタ

- 大雑把にEAXはAUX関連、ECXはCounter関連、EDXはData関連、EBXはアドレスのBase値を格納
- ESIはSource Index, EDIはDistination Indexを格納

#### 特殊レジスタ

- 専用用途のレジスタ
- EBPは現在のスタックフレームのベースアドレス(Base Pointer)を格納
- ESPは現在のスタックトップのアドレス(Stack Pointer)を格納
- EIPは次に実行するアセンブリ命令のアドレス(Instruction Pointer)を格納

#### フラグレジスタ

- 前の命令による捜査の結果生じた状態やプロセッサの状態を格納
- 次の操作の内容を決定する要素
- EFLAGSレジスタという32bitのレジスタで実装されている
- 17個のflagが格納されている
- 文字列処理命令や条件分岐命令などで使われる

##### flagの種類

- CF(Carry Flag)...桁上がりか桁借りがあった時にセット
- ZF(Zero Flag)...演算結果が0の時セット
- SF(Sign Flag)...操作の結果が負になった時にセット
- DF(Direction Flag)...ストリームの方向を制御
- OF(Overload Flag)...符号付き算術演算の結果がレジスタの格納範囲を超えた場合にセット

#### セグメントレジスタ

- メモリ管理のために格納するデータの種類によって領域として区切ったものをセグメントという
- セグメントをメモリ管理に用いる方式をセグメント方式という
- セグメントの先頭のアドレスを参照するのに用いられるレジスタがセグメントレジスタ
- CS, DS, SS, ES, FS, GSがある

### スタック

- 後入れ先出し構造
- 関数呼び出しなどで使う

## バイトオーダ

- マルチバイトデータをどのようにメモリ上に配置するかを示すもの
- ビッグエンディアンとリトルエンディアンがある
- イメージ的にはリトルエンディアンが4バイトずつのスタック方式

## x86アセンブリ命令と記法

- intelで書いておく

```
//数字を格納
mov eax 5
//アドレス先に格納された数字を格納
mov eax [ebx]
//ebx+4のアドレスを格納
mov eax [ebx+4]
//オフセットレジスタやスケーラを指定可能
mov eax [ebx+8+edi*4]
```

- intel記法ではオペランドがメモリアドレスの時はPTR演算子を使ってサイズを記述

```
b: byte
w: word(16bit)
d: double word(32bit int), double(64bit float)
q: quad word(64bit)

mov BYTE PTR [eax] 5
```

### 基本的なアセンブリ命令

```
//データをsrcからdestにコピー
mov dest src

//srcのデータのアドレスをdestにコピー
//スタックポインタのさすアドレスから変位の0x40を加えた位置のアドレスが格納される
lea dest src

//値の交換
xchg dest1, dest2

//データセグメントからソースインデックスまでの内容をBYTE分だけALレジスタに読み込む
lodsb

//ALレジスタから[DS:ESI]に書き込む
stosb

//ESPのレジスタの値をレジスタ幅だけ減らしてargオペランドのESPをさすスタックのトップに格納
push src

//逆
pop dest

//dest += src
add dest src

//dest -= src
sub dest src

//EAXに格納された値にsrcをかけ、結果の上位4バイトをEDXに、下位4バイトをEAXレジスタに格納
mul src

//EDX:EAXの8バイトをsrcでわり、商をEAXに、剰余をEDXレジスタに格納
div src

//dest +-= 1
inc dest
dec dest

//差をとるけど格納しない
cmp src1, src2

//ビットシフト
shr/shl dest, count

//ビットローテート
ror/rol dest, count

//排他的論理和をdestに格納(同じ値をxorにしてレジスタを0で初期化する時によく使う)
xor dest src

//論理積をとるが結果は格納しない
test src1, src2

//argオペランドへと分岐
jmp arg

//retで戻れるようcallの次の命令アドレスをスタックに保存しつつジャンプ
call arg

//call元に戻る
ret

//callなどでスタックに退避されていた値を戻す
leave
```
