/*
 * eload_api.c
 *
 *  Created on: 24 dec. 2016
 *      Author: jancu
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/cfg/global.h> // needed to get the global from the .cfg file

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>


#include <stdint.h>
#include "eload_api.h"
#include "dac_impl.h"
#include "adc_impl.h"

eload_mode eloadMode = ELOAD_MODE_CURRENT;

double eloadGetVoltageDC() {
    return (double)3.141592653589793; // todo: get input voltage from the sampled value
}


void eloadSetMode(eload_mode mode){
    // todo: stop PID engine and reinitialise strategy
    eloadMode = mode;
}

eload_mode eloadGetMode() {
    return eloadMode;
}

uint32_t eLoadGetCurrentRangeMax() {
    return 0b1111111111111111; // 16 bit ADC
}

uint32_t eLoadGetVoltageRangeMax() {
    return 0b1111111111111111; // 16 bit ADC
}

uint32_t eLoadGetOutputRangeMax() {
    return 0b1111111111111111; // 16 bit DAC
}

void eLoadTest() {
    // todo: make this a system test, currently uset to test different things
    MsgDAC      pMsg;

    pMsg.value = 0x4000;
    pMsg.module = 0u;
    /* enqueue message */
    Mailbox_post(mbDAC, &pMsg, BIOS_WAIT_FOREVER);

}

void eLoadDevelopSetDac(uint32_t uModule, uint32_t value) {
    MsgDAC      pMsg;

    // value has to be validated before it arrives here. We assume it's valid
    pMsg.value = (uint16_t)value;
    pMsg.module = (uint8_t)uModule;
    /* enqueue message */
    Mailbox_post(mbDAC, &pMsg, BIOS_WAIT_FOREVER);

}

uint32_t eLoadDevelopGetAdc(uint32_t uModule) {

    return adcImplToValue(adcImplGetAdc(uModule));
}

uint32_t eLoadDevelopGetAdcRaw(uint32_t uModule) {

    return adcImplGetAdc(uModule);
}

float eLoadDevelopGetAdcVolt(uint32_t uModule) {

    return adcImplToFloat(adcImplGetAdc(uModule));
}
