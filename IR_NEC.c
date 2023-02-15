#include "Common.h"
#include "ir_rx.h"

#define IR_DATA_LEN 4

uint8_t ir_data[IR_DATA_LEN];

void process_ir_data(uint8_t ir_data[]) {
    int m = ir_data[2];
    int n = ir_data[3];
    printf("m:%d  n:%d\n", m, n);

    if (m == 112 && n == 143) {
        P14 = !P14;
        printf("P14:%d\n",(int)P14);
    }

    if (m == 88 && n == 167) {
        P12 = !P12;
      printf("P12:%d\n",(int)P12);
    }
}

void main(void) {
    InitialUART0_Timer1(115200);
    Set_All_GPIO_Quasi_Mode;

    ir_rx_setup(IR_USE_EXT1_IT);

    while (1) {
        if (is_ir_data_received()) {
            get_ir_data(ir_data, IR_DATA_LEN);
            process_ir_data(ir_data);
        }
    }
}
