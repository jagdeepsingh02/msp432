/*
 * dac_impl.c
 *
 *  Created on: 2 mrt. 2017
 *      Author: jancu
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/cfg/global.h> // needed to get the global from the .cfg file

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
//#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>

/* Example/Board Header files */
#include "Board.h"

#include "i2c_impl.h"
#include "dac_impl.h"

#define DAC_I2C_ADDR           (0x4C)


uint8_t         d_txBuffer[3];
uint8_t         d_rxBuffer[1]; // DAC doesn't read
I2C_Transaction d_i2cTransaction;
MsgDAC msg;


/*
 *  ======== fnTaskDAC ========
 *  Task for this function is created statically. See the project's .cfg file.
 */
Void fnTaskDAC(UArg arg0, UArg arg1)
{
    d_i2cTransaction.writeBuf = d_txBuffer;
    d_i2cTransaction.readBuf = d_rxBuffer;
    d_i2cTransaction.slaveAddress = DAC_I2C_ADDR;
    d_i2cTransaction.writeCount = 3;
    d_i2cTransaction.readCount = 0;
    d_txBuffer[0] = 0x10; // set value direct

    while (1) {

        /* wait for mailbox to be posted by writer() */
        if (Mailbox_pend(mbDAC, &msg, BIOS_WAIT_FOREVER)) {

            d_txBuffer[1] = msg.value >> 8; // MSB
            d_txBuffer[2] = msg.value; // LSB
            if (! I2C_transfer(i2c_implGetHandle(), &d_i2cTransaction)) {
                System_printf("I2C Bus fault\n");
                System_flush();
            }
        }

    }

}