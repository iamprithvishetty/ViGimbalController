#ifndef DRIVER_CONF_H_
#define DRIVER_CONF_H_

#include "hal.h"
#include "ch.h"

#include "usbcfg.h"
#include "chprintf.h"

/*===========================================================================*/
/* I2C driver                                                                */
/*===========================================================================*/

I2CConfig i2ccfg = {
    OPMODE_I2C,
    400000, // 400kHz frequency I2C
    FAST_DUTY_CYCLE_2,
};


/*===========================================================================*/
/* PWM driver                                                                */
/*===========================================================================*/

static PWMConfig pwmcfg_tim4 = {
    72000000, /* 72MHz PWM clock frequency.                      */
    1000,     /* PWM period 1000/72000000 s, Frequency 72kHz     */
    NULL,     /* Period callback.                                */
    {
        {PWM_OUTPUT_DISABLED, NULL},    /* CH1 mode and callback.         */
        {PWM_OUTPUT_DISABLED, NULL},    /* CH2 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* CH3 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}  /* CH4 mode and callback.         */
    },
    0, /* Control Register 2.            */
    0  /* DMA/Interrupt Enable Register. */
};

static PWMConfig pwmcfg_tim3 = {
    72000000, /* 72MHz PWM clock frequency.                      */
    1000,     /* PWM period 1000/72000000 s, Frequency 72kHz     */
    NULL,     /* Period callback.                                */
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* CH1 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* CH2 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* CH3 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}  /* CH4 mode and callback.         */
    },
    0, /* Control Register 2.            */
    0  /* DMA/Interrupt Enable Register. */
};

static PWMConfig pwmcfg_tim2 = {
    72000000, /* 72MHz PWM clock frequency.                      */
    1000,     /* PWM period 1000/72000000 s, Frequency 72kHz     */
    NULL,     /* Period callback.                                */
    {
        {PWM_OUTPUT_DISABLED, NULL},    /* CH1 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* CH2 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* CH3 mode and callback.         */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}  /* CH4 mode and callback.         */
    },
    0, /* Control Register 2.            */
    0  /* DMA/Interrupt Enable Register. */
};



/*===========================================================================*/
/* ICU driver                                                                */
/*===========================================================================*/


// ICU Tim1 Related

icucnt_t last_width_tim1, last_period_tim1;

/*
 * Callback Function to save pwm width
 */
static void icuwidthcbTim1(ICUDriver *icup)
{
  last_width_tim1 = icuGetWidthX(icup);
}

/*
 * Callback Function to save period
 */
static void icuperiodcbTim1(ICUDriver *icup) {
  last_period_tim1 = icuGetPeriodX(icup);
}

static ICUConfig icucfgTim1 = {
    ICU_INPUT_ACTIVE_HIGH,
    1000000, /* 1MHz ICU clock frequency.   */
    icuwidthcbTim1,
    icuperiodcbTim1,
    NULL,
    ICU_CHANNEL_1,
    0,
};


// ICU Tim8

icucnt_t last_width_tim8, last_period_tim8;

/*
 * Callback Function to save pwm width
 */
static void icuwidthcbTim8(ICUDriver *icup)
{
  last_width_tim8 = icuGetWidthX(icup);
}

/*
 * Callback Function to save period
 */
static void icuperiodcbTim8(ICUDriver *icup) {
  last_period_tim8 = icuGetPeriodX(icup);
}

static ICUConfig icucfgTim8 = {
    ICU_INPUT_ACTIVE_HIGH,
    1000000, /* 1MHz ICU clock frequency.   */
    icuwidthcbTim8,
    icuperiodcbTim8,
    NULL,
    ICU_CHANNEL_1,
    0,
};



/*===========================================================================*/
/* ADC driver                                                                */
/*===========================================================================*/

#define ADC_NUM_CHANNELS   1
#define ADC_BUF_DEPTH      1

static adcsample_t adc_sample[ADC_NUM_CHANNELS * ADC_BUF_DEPTH];

/*
 * ADC streaming callback.
 */
size_t nx = 0, ny = 0;
static void adccallback(ADCDriver *adcp) {

  if (adcIsBufferComplete(adcp)) {
    nx += 1;
  }
  else {
    ny += 1;
  }
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN10, IN11, IN10, IN11, IN10, IN11, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  0, 0,           /* CR1, CR2 */
  0,
  ADC_SMPR2_SMP_AN5(ADC_SAMPLE_13P5),                            /* SMPR2 */
  ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN5),
};



/*===========================================================================*/
/* USB                                                                       */
/*===========================================================================*/

void print(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  chvprintf((BaseSequentialStream *)&SDU1, fmt, ap);
  va_end(ap);
}

#endif