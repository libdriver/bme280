[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BME280

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bme280/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The BME280 is a humidity sensor especially developed for mobile applications and wearables where size and low power consumption are key design parameters. The unit combines high linearity and high accuracy sensors and is perfectly feasible for low current consumption, long-term stability and high EMC robustness. The humidity sensor offers an extremely fast response time and therefore supports performance requirements for emerging applications such as context awareness, and high accuracy over a wide temperature range.

LibDriver BME280 is a full function driver of BME280 launched by LibDriver.It provides continuous reading of pressure, temperature and humidity , single reading of pressure, temperature and humidity, etc. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver BME280 source files.

/interface includes LibDriver BME280 IIC, SPI platform independent template.

/test includes LibDriver BME280 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver BME280 sample code.

/doc includes LibDriver BME280 offline document.

/datasheet includes BME280 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC, SPI platform independent template and finish your platform IIC, SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

```C
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

### Document

Online documents: [https://www.libdriver.com/docs/bme280/index.html](https://www.libdriver.com/docs/bme280/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.