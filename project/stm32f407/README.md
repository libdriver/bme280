### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

SPI Pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. BME280

#### 3.1 Command Instruction

1. Show bme280 chip and driver information.

   ```shell
   bme280 (-i | --information)
   ```

2. Show bme280 help.

   ```shell
   bme280 (-h | --help)
   ```

3. Show bme280 pin connections of the current board.

   ```shell
   bme280 (-p | --port)
   ```

4. Run bme280 register test.

   ```shell
   bme280 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
   ```

5. Run bme280 read test, num means the test times. 

   ```shell
   bme280 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

8. Run bme280 read function, num means the read times. 

   ```shell
   bme280 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

7. Run bme280 shot function, num means the read times.

   ```shell
   bme280 (-e shot | --example=shot) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
bme280 -i

bme280: chip is Bosch BME280.
bme280: manufacturer is Bosch.
bme280: interface is IIC SPI.
bme280: driver version is 1.0.
bme280: min supply voltage is 1.7V.
bme280: max supply voltage is 3.6V.
bme280: max current is 0.71mA.
bme280: max temperature is 85.0C.
bme280: min temperature is -40.0C.
```

```shell
bme280 -p

bme280: SPI interface SCK connected to GPIOA PIN5.
bme280: SPI interface MISO connected to GPIOA PIN6.
bme280: SPI interface MOSI connected to GPIOA PIN7.
bme280: SPI interface CS connected to GPIOA PIN4.
bme280: SCL connected to GPIOB PIN8.
bme280: SDA connected to GPIOB PIN9.
```

```shell
bme280 -t reg --addr=1 --interface=iic

bme280: chip is Bosch BME280.
bme280: manufacturer is Bosch.
bme280: interface is IIC SPI.
bme280: driver version is 1.0.
bme280: min supply voltage is 1.7V.
bme280: max supply voltage is 3.6V.
bme280: max current is 0.71mA.
bme280: max temperature is 85.0C.
bme280: min temperature is -40.0C.
bme280: start register test.
bme280: bme280_set_interface/bme280_get_interface test.
bme280: set interface spi.
bme280: check interface ok.
bme280: set interface iic.
bme280: check interface ok.
bme280: bme280_set_addr_pin/bme280_get_addr_pin test.
bme280: set addr pin low.
bme280: check addr pin ok.
bme280: set addr pin high.
bme280: check addr pin ok.
bme280: bme280_set_temperatue_oversampling/bme280_get_temperatue_oversampling test.
bme280: set temperatue oversampling skip.
bme280: check temperatue oversampling ok.
bme280: set temperatue oversampling x1.
bme280: check temperatue oversampling ok.
bme280: set temperatue oversampling x2.
bme280: check temperatue oversampling ok.
bme280: set temperatue oversampling x4.
bme280: check temperatue oversampling ok.
bme280: set temperatue oversampling x8.
bme280: check temperatue oversampling ok.
bme280: set temperatue oversampling x16.
bme280: check temperatue oversampling ok.
bme280: bme280_set_pressure_oversampling/bme280_get_pressure_oversampling test.
bme280: set pressure oversampling skip.
bme280: check pressure oversampling ok.
bme280: set pressure oversampling x1.
bme280: check pressure oversampling ok.
bme280: set pressure oversampling x2.
bme280: check pressure oversampling ok.
bme280: set pressure oversampling x4.
bme280: check pressure oversampling ok.
bme280: set pressure oversampling x8.
bme280: check pressure oversampling ok.
bme280: set pressure oversampling x16.
bme280: check pressure oversampling ok.
bme280: bme280_set_humidity_oversampling/bme280_get_humidity_oversampling test.
bme280: set humidity oversampling skip.
bme280: check humidity oversampling ok.
bme280: set humidity oversampling x1.
bme280: check humidity oversampling ok.
bme280: set humidity oversampling x2.
bme280: check humidity oversampling ok.
bme280: set humidity oversampling x4.
bme280: check humidity oversampling ok.
bme280: set humidity oversampling x8.
bme280: check humidity oversampling ok.
bme280: set humidity oversampling x16.
bme280: check humidity oversampling ok.
bme280: bme280_set_mode/bme280_get_mode test.
bme280: set mode normal.
bme280: check mode ok.
bme280: set mode sleep.
bme280: check mode ok.
bme280: bme280_set_standby_time/bme280_get_standby_time test.
bme280: set standby time 0.5ms.
bme280: check standby time ok.
bme280: set standby time 62.5ms.
bme280: check standby time ok.
bme280: set standby time 125ms.
bme280: check standby time ok.
bme280: set standby time 250ms.
bme280: check standby time ok.
bme280: set standby time 500ms.
bme280: check standby time ok.
bme280: set standby time 1000ms.
bme280: check standby time ok.
bme280: set standby time 10ms.
bme280: check standby time ok.
bme280: set standby time 20ms.
bme280: check standby time ok.
bme280: bme280_set_filter/bme280_get_filter test.
bme280: set filter off.
bme280: check filter ok.
bme280: set filter coeff 2.
bme280: check filter ok.
bme280: set filter coeff 4.
bme280: check filter ok.
bme280: set filter coeff 8.
bme280: check filter ok.
bme280: set filter coeff 16.
bme280: check filter ok.
bme280: bme280_set_spi_wire/bme280_get_spi_wire test.
bme280: set spi wire 3.
bme280: check spi wire ok.
bme280: set spi wire 4.
bme280: check spi wire ok.
bme280: bme280_get_status test.
bme280: status is 0x04.
bme280: bme280_soft_reset test.
bme280: check soft reset ok.
bme280: finish register test.
```

```shell
bme280 -t read --addr=1 --interface=iic --times=3

bme280: chip is Bosch BME280.
bme280: manufacturer is Bosch.
bme280: interface is IIC SPI.
bme280: driver version is 1.0.
bme280: min supply voltage is 1.7V.
bme280: max supply voltage is 3.6V.
bme280: max current is 0.71mA.
bme280: max temperature is 85.0C.
bme280: min temperature is -40.0C.
bme280: start read test.
bme280: continue read test.
bme280: temperature is 27.65C.
bme280: pressure is 102648.02pa.
bme280: humidity is 17.21%.
bme280: temperature is 27.79C.
bme280: pressure is 102648.95pa.
bme280: humidity is 16.82%.
bme280: temperature is 27.83C.
bme280: pressure is 102650.38pa.
bme280: humidity is 16.95%.
bme280: shot read test.
bme280: temperature is 27.82C.
bme280: pressure is 102649.52pa.
bme280: humidity is 17.50%.
bme280: temperature is 27.80C.
bme280: pressure is 102649.50pa.
bme280: humidity is 17.27%.
bme280: temperature is 27.77C.
bme280: pressure is 102649.15pa.
bme280: humidity is 16.82%.
bme280: finish read test.
```

```shell
bme280 -e read --addr=1 --interface=iic --times=3

bme280: 1/3.
bme280: temperature is 27.60C.
bme280: pressure is 102647.91Pa.
bme280: humidity is 18.40%.
bme280: 2/3.
bme280: temperature is 27.75C.
bme280: pressure is 102649.19Pa.
bme280: humidity is 18.40%.
bme280: 3/3.
bme280: temperature is 27.79C.
bme280: pressure is 102648.62Pa.
bme280: humidity is 17.99%.
```

```shell
bme280 -e shot --addr=1 --interface=iic --times=3

bme280: 1/3.
bme280: temperature is 27.36C.
bme280: pressure is 102645.01Pa.
bme280: humidity is 19.77%.
bme280: 2/3.
bme280: temperature is 27.36C.
bme280: pressure is 102644.91Pa.
bme280: humidity is 20.40%.
bme280: 3/3.
bme280: temperature is 27.36C.
bme280: pressure is 102644.92Pa.
bme280: humidity is 20.81%.
```

```shell
bme280 -h

Usage:
  bme280 (-i | --information)
  bme280 (-h | --help)
  bme280 (-p | --port)
  bme280 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
  bme280 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bme280 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bme280 (-e shot | --example=shot) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]

Options:
      --addr=<0 | 1>                 Set the chip iic address.([default: 0])
  -e <read | shot>, --example=<read | shot>
                                     Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --interface=<iic | spi>        Set the chip interface.([default: iic])
  -p, --port                         Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                     Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

