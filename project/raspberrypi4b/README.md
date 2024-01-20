### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(bme280 REQUIRED)
```

### 3.BME280

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
./bme280 -i

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
./bme280 -p

bme280: SPI interface SCK connected to GPIO11(BCM).
bme280: SPI interface MISO connected to GPIO9(BCM).
bme280: SPI interface MOSI connected to GPIO10(BCM).
bme280: SPI interface CS connected to GPIO8(BCM).
bme280: IIC interface SCL connected to GPIO3(BCM).
bme280: IIC interface SDA connected to GPIO2(BCM).
```

```shell
./bme280 -t reg --interface=spi

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
bme280: check mode error.
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
bme280: bme280_get_status test.
bme280: status is 0x0C.
bme280: bme280_soft_reset test.
bme280: check soft reset ok.
bme280: finish register test.
```

```shell
./bme280 -t read --interface=spi --times=3

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
bme280: temperature is 28.42C.
bme280: pressure is 102637.30pa.
bme280: humidity is 15.55%.
bme280: temperature is 28.54C.
bme280: pressure is 102639.30pa.
bme280: humidity is 15.48%.
bme280: temperature is 28.57C.
bme280: pressure is 102639.69pa.
bme280: humidity is 15.39%.
bme280: shot read test.
bme280: temperature is 28.55C.
bme280: pressure is 102639.26pa.
bme280: humidity is 15.27%.
bme280: temperature is 28.52C.
bme280: pressure is 102639.13pa.
bme280: humidity is 15.27%.
bme280: temperature is 28.50C.
bme280: pressure is 102638.94pa.
bme280: humidity is 15.21%.
bme280: finish read test.
```

```shell
./bme280 -e read --interface=spi --times=3

bme280: 1/3.
bme280: temperature is 27.52C.
bme280: pressure is 102634.26Pa.
bme280: humidity is 15.94%.
bme280: 2/3.
bme280: temperature is 27.66C.
bme280: pressure is 102636.12Pa.
bme280: humidity is 15.94%.
bme280: 3/3.
bme280: temperature is 27.69C.
bme280: pressure is 102636.45Pa.
bme280: humidity is 15.95%.
```

```shell
./bme280 -e shot --interface=spi --times=3

me280: 1/3.
bme280: temperature is 26.98C.
bme280: pressure is 102634.50Pa.
bme280: humidity is 17.04%.
bme280: 2/3.
bme280: temperature is 26.98C.
bme280: pressure is 102634.23Pa.
bme280: humidity is 16.56%.
bme280: 3/3.
bme280: temperature is 26.98C.
bme280: pressure is 102634.20Pa.
bme280: humidity is 16.41%.
```

```shell
./bme280 -h

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
