#ifndef AMIT_PROJECT_RTC_PRIVATE_H_
#define AMIT_PROJECT_RTC_PRIVATE_H_
//
#define CONTROL_1                0x00
#define CONTROL_1_CAP_SEL        7
#define CONTROL_1_STOP           5
#define CONTROL_1_SR             4
#define CONTROL_1_12_24          3
#define CONTROL_1_SIE            2
#define CONTROL_1_AIE            1
#define CONTROL_1_CIE            0
//                               
#define CONTROL_2                0x01
#define CONTROL_2_WTAF           7
#define CONTROL_2_CTAF           6
#define CONTROL_2_CTBF           5
#define CONTROL_2_SF             4
#define CONTROL_2_AF             3
#define CONTROL_2_WTAIE          2
#define CONTROL_2_CTAIE          1
#define CONTROL_2_CTBIE          0
//                               
#define CONTROL_3                0x02
#define CONTROL_3_PM_2           7
#define CONTROL_3_PM_1           6
#define CONTROL_3_PM_0           5
#define CONTROL_3_BSF            3
#define CONTROL_3_BLF            2
#define CONTROL_3_BSIE           1
#define CONTROL_3_BLIE           0
//                               
#define SECONDS                  0x03
#define SECONDS_OS               7
#define SECONDS_TENS_2           6
#define SECONDS_TENS_1           5
#define SECONDS_TENS_0           4
#define SECONDS_UNITS_3          3
#define SECONDS_UNITS_2          2
#define SECONDS_UNITS_1          1
#define SECONDS_UNITS_0          0
//                               
#define MINUTES                  0x04
#define MINUTES_TENS_2           6
#define MINUTES_TENS_1           5
#define MINUTES_TENS_0           4
#define MINUTES_UNITS_3          3
#define MINUTES_UNITS_2          2
#define MINUTES_UNITS_1          1
#define MINUTES_UNITS_0          0
//                               
#define HOURS                    0x05
#define HOURS_AMPM               5
#define HOURS_12_TENS            4
#define HOURS_12_UNITS_3         3
#define HOURS_12_UNITS_2         2
#define HOURS_12_UNITS_1         1
#define HOURS_12_UNITS_0         0
#define HOURS_24_TENS_1          5
#define HOURS_24_TENS_0          4
#define HOURS_24_UNITS_3         3
#define HOURS_24_UNITS_2         2
#define HOURS_24_UNITS_1         1
#define HOURS_24_UNITS_0         0
//                               
#define DAYS                     0x06
#define DAYS_TENS_1              5
#define DAYS_TENS_0              4
#define DAYS_UNITS_3             3
#define DAYS_UNITS_2             2
#define DAYS_UNITS_1             1
#define DAYS_UNITS_0             0
//                               
#define WEEKDAYS                 0x07
#define WEEKDAYS_2               2
#define WEEKDAYS_1               1
#define WEEKDAYS_0               0
//                               
#define MONTHS                   0x08
#define MONTHS_TENS              4
#define MONTHS_UNITS_3           3
#define MONTHS_UNITS_2           2
#define MONTHS_UNITS_1           1
#define MONTHS_UNITS_0           0
//                               
#define YEARS                    0x09
#define YEARS_TENS_3             7
#define YEARS_TENS_2             6
#define YEARS_TENS_1             5
#define YEARS_TENS_0             4
#define YEARS_UNITS_3            3
#define YEARS_UNITS_2            2
#define YEARS_UNITS_1            1
#define YEARS_UNITS_0            0
//
#define MINUTE_ALARM             0x0A
#define MINUTE_ALARM_AEN_M       7
#define MINUTE_ALARM_TENS_2      6
#define MINUTE_ALARM_TENS_1      5
#define MINUTE_ALARM_TENS_0      4
#define MINUTE_ALARM_UNITS_3     3
#define MINUTE_ALARM_UNITS_2     2
#define MINUTE_ALARM_UNITS_1     1
#define MINUTE_ALARM_UNITS_0     0
//
#define HOUR_ALARM               0x0B
#define HOUR_ALARM_AEN_H         7
#define HOUR_ALARM_AMPM          5
#define HOUR_ALARM_12_TENS       4
#define HOUR_ALARM_12_UNITS_3    3
#define HOUR_ALARM_12_UNITS_2    2
#define HOUR_ALARM_12_UNITS_1    1
#define HOUR_ALARM_12_UNITS_0    0
#define HOUR_ALARM_24_TENS_1     5
#define HOUR_ALARM_24_TENS_0     4
#define HOUR_ALARM_24_UNITS_3    3
#define HOUR_ALARM_24_UNITS_2    2
#define HOUR_ALARM_24_UNITS_1    1
#define HOUR_ALARM_24_UNITS_0    0
//
#define DAY_ALARM                0x0C
#define DAY_ALARM_AEN_D          7
#define DAY_ALARM_TENS_1         5
#define DAY_ALARM_TENS_0         4
#define DAY_ALARM_UNITS_3        3
#define DAY_ALARM_UNITS_2        2
#define DAY_ALARM_UNITS_1        1
#define DAY_ALARM_UNITS_0        0
//
#define WEEKDAY_ALARM            0x0D
#define WEEKDAY_ALARM_AEN_W      7
#define WEEKDAY_ALARM_2          2
#define WEEKDAY_ALARM_1          1
#define WEEKDAY_ALARM_0          0
//
#define OFFESET_REG              0x0E
#define OFFESET_REG_MODE         7
#define OFFESET_REG_OFFSET_6     6
#define OFFESET_REG_OFFSET_5     5
#define OFFESET_REG_OFFSET_4     4
#define OFFESET_REG_OFFSET_3     3
#define OFFESET_REG_OFFSET_2     2
#define OFFESET_REG_OFFSET_1     1
#define OFFESET_REG_OFFSET_0     0
//
#define TMR_CLKOUT_CTRL          0x0F
#define TMR_CLKOUT_CTRL_TAM      7
#define TMR_CLKOUT_CTRL_TBM      6
#define TMR_CLKOUT_CTRL_COF_2    5
#define TMR_CLKOUT_CTRL_COF_1    4
#define TMR_CLKOUT_CTRL_COF_0    3
#define TMR_CLKOUT_CTRL_TAC_1    2
#define TMR_CLKOUT_CTRL_TAC_0    1
#define TMR_CLKOUT_CTRL_TBC      0
//
#define TMR_A_FREQ_CTRL          0x10
#define TMR_A_FREQ_CTRL_TAQ_2    2
#define TMR_A_FREQ_CTRL_TAQ_1    1
#define TMR_A_FREQ_CTRL_TAQ_0    0
//
#define TMR_A_REG                0x11
//
#define TMR_B_FREQ_CTRL          0x12
#define TMR_B_FREQ_CTRL_TBW_2    6
#define TMR_B_FREQ_CTRL_TBW_1    5
#define TMR_B_FREQ_CTRL_TBW_0    4
#define TMR_B_FREQ_CTRL_TBQ_2    2
#define TMR_B_FREQ_CTRL_TBQ_1    1
#define TMR_B_FREQ_CTRL_TBQ_0    0
//
#define TMR_B_REG                0x13
#endif