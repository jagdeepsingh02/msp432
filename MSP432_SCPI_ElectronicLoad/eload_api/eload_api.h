/*
 * eload_api.h
 *
 *  Created on: 24 dec. 2016
 *      Author: jancu
 */

#ifndef ELOAD_API_ELOAD_API_H_
#define ELOAD_API_ELOAD_API_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum eload_mode {
    ELOAD_MODE_CURRENT = 0,
    ELOAD_MODE_VOLTAGE,
    ELOAD_MODE_POWER,
    ELOAD_MODE_RESISTANCE,
    ELOAD_MODE_COUNT
}eload_mode;

/*!
 *  @brief  Retrieve voltage sampled from the instrument terminals
 *
 *  This function returns the most recent sampled voltage on the instruments main terminals.
 *  Calling this function doesn't initiate a sample. There's a scheduled task that collects
 *  the info in the background.
 *
e.
 */

void eloadReset();

double eloadGetVoltageDC();

void eloadSetMode(eload_mode mode);
eload_mode eloadGetMode();
int8_t eloadGetChar();
void eloadControlLoop();
uint32_t eloadControlLoopGetSchedule();

// instrument operations
bool eloadSetConstantCurrent(uint32_t value);
bool eloadSetConstantVoltage(uint32_t value);

uint32_t eLoadGetCurrentRangeMax();
uint32_t eLoadGetVoltageRangeMax();
uint32_t eLoadGetOutputRangeMax();

void eloadInputEnable(bool bEnable);
bool eloadInputEnabled();


void eLoadTest();
void eLoadRawSetDac(uint32_t uModule, uint32_t value);
uint32_t eLoadDevelopGetAdc(uint32_t uModule);
uint32_t eLoadDevelopGetAdcRaw();
float eLoadDevelopGetAdcVolt(uint32_t uModule);

// calibration
void eloadCalibrationStart();
bool eloadCalibrationEnd();
bool eLoadCalibrateSetTemperatureMaxResistance(uint32_t value);
uint32_t eLoadCalibrateGetTemperatureMaxResistance();




#endif /* ELOAD_API_ELOAD_API_H_ */
