#include <stdint.h>

#define SRAM_START  0x20000000U
#define SRAM_SIZE   (20U * 1024U)     /* 20 KB */
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

/* Lấy tên biến từ Linker Script */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Khai báo hàm main */
extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);

/* Các ngắt hệ thống lõi của Cortex-M3 */
void NMI_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));

// Cho hàm ngắt
void USART2_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));

__attribute__((section(".isr_vector"), used))
void (* const vectors[])(void) = {
    (void (*)(void))STACK_START, /* 0: Top of Stack */
    Reset_Handler,               /* 1: Reset */
    NMI_Handler,                 /* 2: NMI */
    HardFault_Handler,           /* 3: Hard Fault */
    MemManage_Handler,           /* 4: MemManage */
    BusFault_Handler,            /* 5: Bus Fault */
    UsageFault_Handler,          /* 6: Usage Fault */
    0, 0, 0, 0,                  /* 7 đến 10: Reserved */
    SVC_Handler,                 /* 11: SVCall */
    DebugMon_Handler,            /* 12: Debug Monitor */
    0,                           /* 13: Reserved */
    PendSV_Handler,              /* 14: PendSV */
    SysTick_Handler,             /* 15: SysTick */

    /* ========== CÁC NGẮT NGOẠI VI (Bắt đầu từ vị trí 16 trong mảng ========== */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* Ngắt ngoại vi 0 đến 9 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* Ngắt ngoại vi 10 đến 19 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* Ngắt ngoại vi 20 đến 29 */
    0, 0, 0, 0, 0, 0, 0, 0,       /* Ngắt ngoại vi 30 đến 37 */
    USART2_IRQHandler             /* Ngắt ngoại vi 38: USART2 global Interrupt */
};

void Reset_Handler(void)
{
    /* 1. Copy .data từ FLASH vào SRAM */
    uint32_t *pSrc = &_etext;
    uint32_t *pDst = &_sdata;
    
    while (pDst < &_edata)
    {
        *pDst++ = *pSrc++;
    }
    
    /* 2. Xóa trắng vùng .bss trong SRAM */
    pDst = &_sbss;
    while (pDst < &_ebss)
    {
        *pDst++ = 0;
    }
    
    /* 3. Gọi hàm main */
    main();
    
    while(1);
}

void Default_Handler(void)
{
    while(1);
}