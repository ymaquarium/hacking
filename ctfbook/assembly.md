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
//保存しておいたリターンアドレスをeipレジスタにpopし命令ポインタをサブルーチン後の命令アドレスにする
ret

//callなどでスタックに退避されていた値を戻す
leave
```

### 逆アセンブル解析

#### エントリーポイント

- プログラムは大抵mainルーチンから処理される
- バイナリレベルではmainルーチン前の初期化設定などが先に行われる
    - レジスタやスタックの初期化処理
    - main関数へ渡すコマンドライン引数の処理
- 例えばLinuxならば以下のようになる

```
public start
start       proc near
            xor ebp, ebp
            pop esi
            mov ecx, esp
            and esp 0FFFFFF0h
            push eax
            push esp    ; stack_end
            push edx    ; rtld_fini
            push offset fini    ;fini
            push offset init    ;init
            push ecx    ;ubp_av
            push esi    ;argc
            push offset main    ;main
            call ___libc_start_main
            hlt
start       endp
```

#### 条件分岐

##### Jcc命令

- eipを参照していくような逐次実行以外でも命令を実行
- cmp, test, subなどフラグレジスタに影響を与える命令を伴うことが多い

```
Jccの主な命令

JE(jump if equal), JZ(jump if zero):    ZF=1で分岐
JNE(jump if not equal), JNZ(jump if not zero):  ZF=0で分岐
JG(jump if greater):    ZF=0 and SF=OF
JL(jump if less):   SF<>OFの時分岐
```

#### API呼び出し

##### 呼出規約

- サブルーチンにおいて引数の渡し方や戻り値の返し方を定めたもの
- 決められたレジスタやスタックに引数が渡され戻り値が返される
- 色々な呼出規約があり、引数の渡し方はそれぞれ異なる

##### 関数呼び出しとスタック

- スタックに少しずつpush&popすることによって進む
- サブルーチンに入ったらebpとespレジスタのアドレスを動かしてLocal用の領域を作る(関数のプロローグ)
- 復帰したら退避しておいた元のebpレジスタに戻り、サブルーチン呼び出し前の状態にする
- 終わったら命令ポインタをサブルーチン前のものにセット(関数のエピローグ)

```
Func1
...
push    arg2
push    arg1
call    Func2 ;subroutine発生
mov retval, eax
...

Func2
push    ebp ;ebpレジスタを復帰用に保存
mov ebp, esp ;ebpレジスタをespレジスタの指す位置に移動(サブルーチン領域用)
sub esp, 100h ;espレジスタをサブルーチン領域用に100hだけ移動(引き算), 現在のスタックポインタが下に100hうつる
mov eax, [ebp+8]; ebpレジスタより高位にある(サブルーチン領域外)場所から変数を格納
mov ebx, [ebp+Ch]
...
mov esp, ebp ;スタックポインタをサブルーチンの前に戻す
pop ebp ;退避しておいた元のベースポインタへebpを復帰
ret ;Func2の終了, 命令ポインタをサブルーチン直後のものにうつす
```
