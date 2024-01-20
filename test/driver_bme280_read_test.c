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
 * @file      driver_bme280_read_test.c
 * @brief     driver bme280 read test source file
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

static bme280_handle_t gs_handle;        /**< bme280 handle */

/**
 * @brief     read test
 * @param[in] interface is the set interface
 * @param[in] addr_pin is the chip address pin
 * @param[in] times is the read times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bme280_read_test(bme280_interface_t interface, bme280_address_t addr_pin, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint32_t temperature_raw;
    uint32_t pressure_raw;
    uint32_t humidity_raw;
    float temperature_c;
    float pressure_pa;
    float humidity_percentage;
    bme280_info_t info;
    
    /* link interface function */
    DRIVER_BME280_LINK_INIT(&gs_handle, bme280_handle_t); 
    DRIVER_BME280_LINK_IIC_INIT(&gs_handle, bme280_interface_iic_init);
    DRIVER_BME280_LINK_IIC_DEINIT(&gs_handle, bme280_interface_iic_deinit);
    DRIVER_BME280_LINK_IIC_READ(&gs_handle, bme280_interface_iic_read);
    DRIVER_BME280_LINK_IIC_WRITE(&gs_handle, bme280_interface_iic_write);
    DRIVER_BME280_LINK_SPI_INIT(&gs_handle, bme280_interface_spi_init);
    DRIVER_BME280_LINK_SPI_DEINIT(&gs_handle, bme280_interface_spi_deinit);
    DRIVER_BME280_LINK_SPI_READ(&gs_handle, bme280_interface_spi_read);
    DRIVER_BME280_LINK_SPI_WRITE(&gs_handle, bme280_interface_spi_write);
    DRIVER_BME280_LINK_DELAY_MS(&gs_handle, bme280_interface_delay_ms);
    DRIVER_BME280_LINK_DEBUG_PRINT(&gs_handle, bme280_interface_debug_print);
    
    /* get bme280 info */
    res = bme280_info(&info);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print bme280 */
        bme280_interface_debug_print("bme280: chip is %s.\n", info.chip_name);
        bme280_interface_debug_print("bme280: manufacturer is %s.\n", info.manufacturer_name);
        bme280_interface_debug_print("bme280: interface is %s.\n", info.interface);
        bme280_interface_debug_print("bme280: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bme280_interface_debug_print("bme280: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bme280_interface_debug_print("bme280: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bme280_interface_debug_print("bme280: max current is %0.2fmA.\n", info.max_current_ma);
        bme280_interface_debug_print("bme280: max temperature is %0.1fC.\n", info.temperature_max);
        bme280_interface_debug_print("bme280: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    bme280_interface_debug_print("bme280: start read test.\n");
    
    /* set interface */
    res = bme280_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bme280_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set addr pin failed.\n");
       
        return 1;
    }
    
    /* init */
    res = bme280_init(&gs_handle);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: init failed.\n");
       
        return 1;
    }
    
    /* set humidity oversampling x1 */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set temperatue oversampling x2 */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set pressure oversampling x16 */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set standby time 0.5ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_0P5_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set filter 16 */
    res = bme280_set_filter(&gs_handle, BME280_FILTER_COEFF_16);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set normal mode */
    res = bme280_set_mode(&gs_handle, BME280_MODE_NORMAL);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set mode failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* delay 1000ms */
    bme280_interface_delay_ms(1000);
    
    /* continue read test */
    bme280_interface_debug_print("bme280: continue read test.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        /* read temperature pressure humidity */
        res = bme280_read_temperature_pressure_humidity(&gs_handle, &temperature_raw, &temperature_c, 
                                                        &pressure_raw, &pressure_pa,
                                                        &humidity_raw, &humidity_percentage);
        if (res != 0)
        {
            bme280_interface_debug_print("bme280: read temperature pressure humidity failed.\n");
            (void)bme280_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* delay 1000ms */
        bme280_interface_delay_ms(1000);
        
        /* output */
        bme280_interface_debug_print("bme280: temperature is %0.2fC.\n", temperature_c);
        bme280_interface_debug_print("bme280: pressure is %0.2fpa.\n", pressure_pa);
        bme280_interface_debug_print("bme280: humidity is %0.2f%%.\n", humidity_percentage);
    }
     
    /* set sleep mode */
    res = bme280_set_mode(&gs_handle, BME280_MODE_SLEEP);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set mode failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* delay 1000ms */
    bme280_interface_delay_ms(1000);
    
    /* shot read test */
    bme280_interface_debug_print("bme280: shot read test.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        /* read temperature pressure humidity */
        res = bme280_read_temperature_pressure_humidity(&gs_handle, &temperature_raw, &temperature_c, 
                                                        &pressure_raw, &pressure_pa,
                                                        &humidity_raw, &humidity_percentage);
        if (res != 0)
        {
            bme280_interface_debug_print("bme280: read temperature pressure humidity failed.\n");
            (void)bme280_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* delay 1000ms */
        bme280_interface_delay_ms(1000);
        
        /* output */
        bme280_interface_debug_print("bme280: temperature is %0.2fC.\n", temperature_c);
        bme280_interface_debug_print("bme280: pressure is %0.2fpa.\n", pressure_pa);
        bme280_interface_debug_print("bme280: humidity is %0.2f%%.\n", humidity_percentage);
    }
    
    /* finish read test */
    bme280_interface_debug_print("bme280: finish read test.\n");
    (void)bme280_deinit(&gs_handle); 
    
    return 0;
}
