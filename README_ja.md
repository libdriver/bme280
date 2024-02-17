[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME280

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme280/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BME280 は、サイズと低消費電力が主要な設計パラメータであるモバイル アプリケーションおよびウェアラブル向けに特別に開発された湿度センサーです。 このユニットは、高い直線性と高精度のセンサーを組み合わせており、低消費電流、長期安定性、および高い EMC 堅牢性を実現します。 湿度センサーは非常に速い応答時間を提供するため、コンテキスト認識などの新しいアプリケーションのパフォーマンス要件や、広い温度範囲にわたる高精度をサポートします。

LibDriver BME280 は、LibDriver によって起動された BME280 のフル機能ドライバーです。圧力、温度、湿度の連続読み取り、圧力、温度、湿度の単一読み取りなどを提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver BME280のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver BME280用のプラットフォームに依存しないIIC, SPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver BME280ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver BME280プログラミング例が含まれています。

/ docディレクトリには、LibDriver BME280オフラインドキュメントが含まれています。

/ datasheetディレクトリには、BME280データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIIC, SPIバステンプレートを参照して、指定したプラットフォームのIIC, SPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
uint8_t res;
uint32_t i;
float temperature_c;
float pressure_pa;
float humidity_percentage;

/* basic init */
res = bme280_basic_init(BME280_INTERFACE_IIC, BME280_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    bme280_interface_delay_ms(1000);

    /* read data */
    res = bme280_basic_read((float *)&temperature_c, (float *)&pressure_pa, (float *)&humidity_percentage);
    if (res != 0)
    {
        (void)bme280_basic_deinit();

        return 1;
    }

    /* output */
    bme280_interface_debug_print("bme280: %d/%d.\n", i + 1, 3);
    bme280_interface_debug_print("bme280: temperature is %0.2fC.\n", temperature_c);
    bme280_interface_debug_print("bme280: pressure is %0.2fPa.\n", pressure_pa);
    bme280_interface_debug_print("bme280: humidity is %0.2f%%.\n", humidity_percentage);
    
    ...
}

...
    
/* deinit */
(void)bme280_basic_deinit();

return 0;
```

#### example shot

```c
uint8_t res;
uint32_t i;
float temperature_c;
float pressure_pa;
float humidity_percentage;

/* shot init */
res = bme280_shot_init(BME280_INTERFACE_IIC, BME280_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    bme280_interface_delay_ms(1000);

    /* read data */
    res = bme280_shot_read((float *)&temperature_c, (float *)&pressure_pa, (float *)&humidity_percentage);
    if (res != 0)
    {
        (void)bme280_shot_deinit();

        return 1;
    }

    /* output */
    bme280_interface_debug_print("bme280: %d/%d.\n", i + 1, 3);
    bme280_interface_debug_print("bme280: temperature is %0.2fC.\n", temperature_c);
    bme280_interface_debug_print("bme280: pressure is %0.2fPa.\n", pressure_pa);
    bme280_interface_debug_print("bme280: humidity is %0.2f%%.\n", humidity_percentage);
    
    ...
}

...
    
/* deinit */
(void)bme280_shot_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/bme280/index.html](https://www.libdriver.com/docs/bme280/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。