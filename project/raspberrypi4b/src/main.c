/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-01-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/01/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_bme280_read_test.h"
#include "driver_bme280_register_test.h"
#include "driver_bme280_basic.h"
#include "driver_bme280_shot.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     bme280 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t bme280(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"interface", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    bme280_interface_t interface = BME280_INTERFACE_IIC;
    bme280_address_t addr = BME280_ADDRESS_ADO_LOW;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running addr pin */
            case 1 :
            {
                if (strcmp("0", optarg) == 0)
                {
                    addr = BME280_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = BME280_ADDRESS_ADO_HIGH;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running interface */
            case 2 :
            {
                if (strcmp("iic", optarg) == 0)
                {
                    interface = BME280_INTERFACE_IIC;
                }
                else if (strcmp("spi", optarg) == 0)
                {
                    interface = BME280_INTERFACE_SPI;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        uint8_t res;
        
        /* run the reg test */
        res = bme280_register_test(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* run the read test */
        res = bme280_read_test(interface, addr, times);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature_c;
        float pressure_pa;
        float humidity_percentage;
        
        /* basic init */
        res = bme280_basic_init(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
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
            bme280_interface_debug_print("bme280: %d/%d.\n", i + 1, times);
            bme280_interface_debug_print("bme280: temperature is %0.2fC.\n", temperature_c);
            bme280_interface_debug_print("bme280: pressure is %0.2fPa.\n", pressure_pa);
            bme280_interface_debug_print("bme280: humidity is %0.2f%%.\n", humidity_percentage);
        }
        
        /* deinit */
        (void)bme280_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature_c;
        float pressure_pa;
        float humidity_percentage;
        
        /* shot init */
        res = bme280_shot_init(interface, addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
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
            bme280_interface_debug_print("bme280: %d/%d.\n", i + 1, times);
            bme280_interface_debug_print("bme280: temperature is %0.2fC.\n", temperature_c);
            bme280_interface_debug_print("bme280: pressure is %0.2fPa.\n", pressure_pa);
            bme280_interface_debug_print("bme280: humidity is %0.2f%%.\n", humidity_percentage);
        }
        
        /* deinit */
        (void)bme280_shot_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        bme280_interface_debug_print("Usage:\n");
        bme280_interface_debug_print("  bme280 (-i | --information)\n");
        bme280_interface_debug_print("  bme280 (-h | --help)\n");
        bme280_interface_debug_print("  bme280 (-p | --port)\n");
        bme280_interface_debug_print("  bme280 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]\n");
        bme280_interface_debug_print("  bme280 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]\n");
        bme280_interface_debug_print("  bme280 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]\n");
        bme280_interface_debug_print("  bme280 (-e shot | --example=shot) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]\n");
        bme280_interface_debug_print("\n");
        bme280_interface_debug_print("Options:\n");
        bme280_interface_debug_print("      --addr=<0 | 1>                 Set the chip iic address.([default: 0])\n");
        bme280_interface_debug_print("  -e <read | shot>, --example=<read | shot>\n");
        bme280_interface_debug_print("                                     Run the driver example.\n");
        bme280_interface_debug_print("  -h, --help                         Show the help.\n");
        bme280_interface_debug_print("  -i, --information                  Show the chip information.\n");
        bme280_interface_debug_print("      --interface=<iic | spi>        Set the chip interface.([default: iic])\n");
        bme280_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        bme280_interface_debug_print("  -t <reg | read>, --test=<reg | read>\n");
        bme280_interface_debug_print("                                     Run the driver test.\n");
        bme280_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        bme280_info_t info;
        
        /* print bme280 info */
        bme280_info(&info);
        bme280_interface_debug_print("bme280: chip is %s.\n", info.chip_name);
        bme280_interface_debug_print("bme280: manufacturer is %s.\n", info.manufacturer_name);
        bme280_interface_debug_print("bme280: interface is %s.\n", info.interface);
        bme280_interface_debug_print("bme280: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bme280_interface_debug_print("bme280: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bme280_interface_debug_print("bme280: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bme280_interface_debug_print("bme280: max current is %0.2fmA.\n", info.max_current_ma);
        bme280_interface_debug_print("bme280: max temperature is %0.1fC.\n", info.temperature_max);
        bme280_interface_debug_print("bme280: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        /* print pin connection */
        bme280_interface_debug_print("bme280: SPI interface SCK connected to GPIO11(BCM).\n");
        bme280_interface_debug_print("bme280: SPI interface MISO connected to GPIO9(BCM).\n");
        bme280_interface_debug_print("bme280: SPI interface MOSI connected to GPIO10(BCM).\n");
        bme280_interface_debug_print("bme280: SPI interface CS connected to GPIO8(BCM).\n");
        bme280_interface_debug_print("bme280: IIC interface SCL connected to GPIO3(BCM).\n");
        bme280_interface_debug_print("bme280: IIC interface SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = bme280(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        bme280_interface_debug_print("bme280: run failed.\n");
    }
    else if (res == 5)
    {
        bme280_interface_debug_print("bme280: param is invalid.\n");
    }
    else
    {
        bme280_interface_debug_print("bme280: unknown status code.\n");
    }

    return 0;
}
