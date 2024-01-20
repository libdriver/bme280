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
 * @file      driver_bme280_register_test.c
 * @brief     driver bme280 register test source file
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

#include "driver_bme280_register_test.h"

static bme280_handle_t gs_handle;        /**< bme280 handle */

/**
 * @brief     register test
 * @param[in] interface is the set interface
 * @param[in] addr_pin is the chip address pin
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bme280_register_test(bme280_interface_t interface, bme280_address_t addr_pin)
{
    uint8_t res;
    uint8_t status;
    bme280_info_t info;
    bme280_address_t addr_pin_check;
    bme280_interface_t interface_check;
    bme280_oversampling_t oversampling;
    bme280_mode_t mode;
    bme280_standby_time_t standby_time;
    bme280_filter_t filter;
    bme280_spi_wire_t spi;
    
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
    
    /* start register test */
    bme280_interface_debug_print("bme280: start register test.\n");
    
    /* bme280_set_interface/bme280_get_interface test */
    bme280_interface_debug_print("bme280: bme280_set_interface/bme280_get_interface test.\n");
    
    /* set interface */
    res = bme280_set_interface(&gs_handle, BME280_INTERFACE_SPI);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set interface failed.\n");
       
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set interface spi.\n");
    
    /* get interface */
    res = bme280_get_interface(&gs_handle, &interface_check);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get interface failed.\n");
       
        return 1;
    }
    bme280_interface_debug_print("bme280: check interface %s.\n", interface_check == BME280_INTERFACE_SPI ? "ok" : "error");
    
    /* set interface */
    res = bme280_set_interface(&gs_handle, BME280_INTERFACE_IIC);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set interface failed.\n");
       
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set interface iic.\n");
    
    /* get interface */
    res = bme280_get_interface(&gs_handle, &interface_check);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get interface failed.\n");
       
        return 1;
    }
    bme280_interface_debug_print("bme280: check interface %s.\n", interface_check == BME280_INTERFACE_IIC ? "ok" : "error");
    
    /* bme280_set_addr_pin/bme280_get_addr_pin test */
    bme280_interface_debug_print("bme280: bme280_set_addr_pin/bme280_get_addr_pin test.\n");
    
    /* set addr pin low */
    res = bme280_set_addr_pin(&gs_handle, BME280_ADDRESS_ADO_LOW);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set addr pin failed.\n");
       
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set addr pin low.\n");
    
    /* get addr pin */
    res = bme280_get_addr_pin(&gs_handle, &addr_pin_check);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get addr pin failed.\n");
       
        return 1;
    }
    bme280_interface_debug_print("bme280: check addr pin %s.\n", addr_pin_check == BME280_ADDRESS_ADO_LOW ? "ok" : "error");
    
    /* set addr pin high */
    res = bme280_set_addr_pin(&gs_handle, BME280_ADDRESS_ADO_HIGH);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set addr pin failed.\n");
       
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set addr pin high.\n");
    
    /* get addr pin */
    res = bme280_get_addr_pin(&gs_handle, &addr_pin_check);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get addr pin failed.\n");
       
        return 1;
    }
    bme280_interface_debug_print("bme280: check addr pin %s.\n", addr_pin_check == BME280_ADDRESS_ADO_HIGH ? "ok" : "error");
    
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
    
    /* bme280_set_temperatue_oversampling/bme280_get_temperatue_oversampling test */
    bme280_interface_debug_print("bme280: bme280_set_temperatue_oversampling/bme280_get_temperatue_oversampling test.\n");
    
    /* set temperatue oversampling skip */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_SKIP);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set temperatue oversampling skip.\n");
    
    /* get temperatue oversampling */
    res = bme280_get_temperatue_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check temperatue oversampling %s.\n", oversampling == BME280_OVERSAMPLING_SKIP ? "ok" : "error");
    
    /* set temperatue oversampling x1 */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set temperatue oversampling x1.\n");
    
    /* get temperatue oversampling */
    res = bme280_get_temperatue_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check temperatue oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x1 ? "ok" : "error");
    
    /* set temperatue oversampling x2 */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set temperatue oversampling x2.\n");
    
    /* get temperatue oversampling */
    res = bme280_get_temperatue_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check temperatue oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x2 ? "ok" : "error");
    
    /* set temperatue oversampling x4 */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_x4);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set temperatue oversampling x4.\n");
    
    /* get temperatue oversampling */
    res = bme280_get_temperatue_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check temperatue oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x4 ? "ok" : "error");
    
    /* set temperatue oversampling x8 */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_x8);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set temperatue oversampling x8.\n");
    
    /* get temperatue oversampling */
    res = bme280_get_temperatue_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check temperatue oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x8 ? "ok" : "error");
    
    /* set temperatue oversampling x16 */
    res = bme280_set_temperatue_oversampling(&gs_handle, BME280_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set temperatue oversampling x16.\n");
    
    /* get temperatue oversampling */
    res = bme280_get_temperatue_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get temperatue oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check temperatue oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x16 ? "ok" : "error");
    
    /* bme280_set_pressure_oversampling/bme280_get_pressure_oversampling test */
    bme280_interface_debug_print("bme280: bme280_set_pressure_oversampling/bme280_get_pressure_oversampling test.\n");
    
    /* set pressure oversampling skip */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_SKIP);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set pressure oversampling skip.\n");
    
    /* get pressure oversampling */
    res = bme280_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check pressure oversampling %s.\n", oversampling == BME280_OVERSAMPLING_SKIP ? "ok" : "error");
    
    /* set pressure oversampling x1 */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set pressure oversampling x1.\n");
    
    /* get pressure oversampling */
    res = bme280_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check pressure oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x1 ? "ok" : "error");
    
    /* set pressure oversampling x2 */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set pressure oversampling x2.\n");
    
    /* get pressure oversampling */
    res = bme280_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check pressure oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x2 ? "ok" : "error");
    
    /* set pressure oversampling x4 */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_x4);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set pressure oversampling x4.\n");
    
    /* get pressure oversampling */
    res = bme280_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check pressure oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x4 ? "ok" : "error");
    
    /* set pressure oversampling x8 */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_x8);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set pressure oversampling x8.\n");
    
    /* get pressure oversampling */
    res = bme280_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check pressure oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x8 ? "ok" : "error");
    
    /* set pressure oversampling x16 */
    res = bme280_set_pressure_oversampling(&gs_handle, BME280_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set pressure oversampling x16.\n");
    
    /* get pressure oversampling */
    res = bme280_get_pressure_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get pressure oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check pressure oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x16 ? "ok" : "error");
    
    /* bme280_set_humidity_oversampling/bme280_get_humidity_oversampling test */
    bme280_interface_debug_print("bme280: bme280_set_humidity_oversampling/bme280_get_humidity_oversampling test.\n");
    
    /* set humidity oversampling skip */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_SKIP);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set humidity oversampling skip.\n");
    
    /* get humidity oversampling */
    res = bme280_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check humidity oversampling %s.\n", oversampling == BME280_OVERSAMPLING_SKIP ? "ok" : "error");
    
    /* set humidity oversampling x1 */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_x1);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set humidity oversampling x1.\n");
    
    /* get humidity oversampling */
    res = bme280_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check humidity oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x1 ? "ok" : "error");
    
    /* set humidity oversampling x2 */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_x2);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set humidity oversampling x2.\n");
    
    /* get humidity oversampling */
    res = bme280_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check humidity oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x2 ? "ok" : "error");
    
    /* set humidity oversampling x4 */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_x4);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set humidity oversampling x4.\n");
    
    /* get humidity oversampling */
    res = bme280_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check humidity oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x4 ? "ok" : "error");
    
    /* set humidity oversampling x8 */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_x8);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set humidity oversampling x8.\n");
    
    /* get humidity oversampling */
    res = bme280_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check humidity oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x8 ? "ok" : "error");
    
    /* set humidity oversampling x16 */
    res = bme280_set_humidity_oversampling(&gs_handle, BME280_OVERSAMPLING_x16);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set humidity oversampling x16.\n");
    
    /* get humidity oversampling */
    res = bme280_get_humidity_oversampling(&gs_handle, &oversampling);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get humidity oversampling failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check humidity oversampling %s.\n", oversampling == BME280_OVERSAMPLING_x16 ? "ok" : "error");
    
    /* bme280_set_mode/bme280_get_mode test */
    bme280_interface_debug_print("bme280: bme280_set_mode/bme280_get_mode test.\n");
    
    /* set mode normal */
    res = bme280_set_mode(&gs_handle, BME280_MODE_NORMAL);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set mode failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set mode normal.\n");
    
    res = bme280_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get mode failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check mode %s.\n", mode == BME280_MODE_NORMAL ? "ok" : "error");
    
    /* set mode sleep */
    res = bme280_set_mode(&gs_handle, BME280_MODE_SLEEP);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set mode failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set mode sleep.\n");
    
    res = bme280_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get mode failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check mode %s.\n", mode == BME280_MODE_SLEEP ? "ok" : "error");
    
    /* bme280_set_standby_time/bme280_get_standby_time test */
    bme280_interface_debug_print("bme280: bme280_set_standby_time/bme280_get_standby_time test.\n");
    
    /* set standby time 0.5ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_0P5_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 0.5ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_0P5_MS ? "ok" : "error");
    
    /* set standby time 62.5ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_62P5_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 62.5ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_62P5_MS ? "ok" : "error");
    
    /* set standby time 125ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_125_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 125ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_125_MS ? "ok" : "error");
    
    /* set standby time 250ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_250_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 250ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_250_MS ? "ok" : "error");
    
    /* set standby time 500ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_500_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 500ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_500_MS ? "ok" : "error");
    
    /* set standby time 1000ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_1000_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 1000ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_1000_MS ? "ok" : "error");
    
    /* set standby time 10ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_10_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 10ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_10_MS ? "ok" : "error");
    
    /* set standby time 10ms */
    res = bme280_set_standby_time(&gs_handle, BME280_STANDBY_TIME_20_MS);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set standby time 20ms.\n");
    
    /* get standby time */
    res = bme280_get_standby_time(&gs_handle, &standby_time);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get standby time failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check standby time %s.\n", standby_time == BME280_STANDBY_TIME_20_MS ? "ok" : "error");
    
    /* bme280_set_filter/bme280_get_filter test */
    bme280_interface_debug_print("bme280: bme280_set_filter/bme280_get_filter test.\n");
    
    /* set filter off */
    res = bme280_set_filter(&gs_handle, BME280_FILTER_OFF);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set filter off.\n");
    
    /* get filter */
    res = bme280_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check filter %s.\n", filter == BME280_FILTER_OFF ? "ok" : "error");
    
    /* set filter coeff 2 */
    res = bme280_set_filter(&gs_handle, BME280_FILTER_COEFF_2);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set filter coeff 2.\n");
    
    /* get filter */
    res = bme280_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check filter %s.\n", filter == BME280_FILTER_COEFF_2 ? "ok" : "error");
    
    /* set filter coeff 4 */
    res = bme280_set_filter(&gs_handle, BME280_FILTER_COEFF_4);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set filter coeff 4.\n");
    
    /* get filter */
    res = bme280_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check filter %s.\n", filter == BME280_FILTER_COEFF_4 ? "ok" : "error");
    
    /* set filter coeff 8 */
    res = bme280_set_filter(&gs_handle, BME280_FILTER_COEFF_8);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set filter coeff 8.\n");
    
    /* get filter */
    res = bme280_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check filter %s.\n", filter == BME280_FILTER_COEFF_8 ? "ok" : "error");
    
    /* set filter coeff 16 */
    res = bme280_set_filter(&gs_handle, BME280_FILTER_COEFF_16);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: set filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* output */
    bme280_interface_debug_print("bme280: set filter coeff 16.\n");
    
    /* get filter */
    res = bme280_get_filter(&gs_handle, &filter);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get filter failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check filter %s.\n", filter == BME280_FILTER_COEFF_16 ? "ok" : "error");
    
    /* if iic interface */
    if (interface == BME280_INTERFACE_IIC)
    {
        /* bme280_set_spi_wire/bme280_get_spi_wire test */
        bme280_interface_debug_print("bme280: bme280_set_spi_wire/bme280_get_spi_wire test.\n");
        
        /* set spi wire3 */
        res = bme280_set_spi_wire(&gs_handle, BME280_SPI_WIRE_3);
        if (res != 0)
        {
            bme280_interface_debug_print("bme280: set spi wire failed.\n");
            (void)bme280_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* output */
        bme280_interface_debug_print("bme280: set spi wire 3.\n");
        
        /* get spi wire */
        res = bme280_get_spi_wire(&gs_handle, &spi);
        if (res != 0)
        {
            bme280_interface_debug_print("bme280: get spi wire failed.\n");
            (void)bme280_deinit(&gs_handle); 
            
            return 1;
        }
        bme280_interface_debug_print("bme280: check spi wire %s.\n", spi == BME280_SPI_WIRE_3 ? "ok" : "error");
        
        /* set spi wire4 */
        res = bme280_set_spi_wire(&gs_handle, BME280_SPI_WIRE_4);
        if (res != 0)
        {
            bme280_interface_debug_print("bme280: set spi wire failed.\n");
            (void)bme280_deinit(&gs_handle); 
            
            return 1;
        }
        
        /* output */
        bme280_interface_debug_print("bme280: set spi wire 4.\n");
        
        /* get spi wire */
        res = bme280_get_spi_wire(&gs_handle, &spi);
        if (res != 0)
        {
            bme280_interface_debug_print("bme280: get spi wire failed.\n");
            (void)bme280_deinit(&gs_handle); 
            
            return 1;
        }
        bme280_interface_debug_print("bme280: check spi wire %s.\n", spi == BME280_SPI_WIRE_4 ? "ok" : "error");
    }

    /* bme280_get_status test */
    bme280_interface_debug_print("bme280: bme280_get_status test.\n");
    
    /* get status */
    res = bme280_get_status(&gs_handle, &status);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: get status failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: status is 0x%02X.\n", status);
    
    /* bme280_soft_reset test */
    bme280_interface_debug_print("bme280: bme280_soft_reset test.\n");
    
    /* soft reset */
    res = bme280_soft_reset(&gs_handle);
    if (res != 0)
    {
        bme280_interface_debug_print("bme280: soft reset failed.\n");
        (void)bme280_deinit(&gs_handle); 
        
        return 1;
    }
    bme280_interface_debug_print("bme280: check soft reset %s.\n", res == 0 ? "ok" : "error");
    
    /* finish register test */
    bme280_interface_debug_print("bme280: finish register test.\n");
    (void)bme280_deinit(&gs_handle); 

    return 0;
}
