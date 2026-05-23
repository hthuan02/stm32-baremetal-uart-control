#ifndef __SYSTEM_STM32F10x_H
#define __SYSTEM_STM32F10x_H

/* Định nghĩa kiểu dữ liệu cơ bản */
typedef unsigned int            uint32_t;
typedef unsigned short          uint16_t;
typedef unsigned char           uint8_t;
typedef int                     int32_t;

/* ========================================================================== */
/*                         ĐỊA CHỈ NGẮT HỆ THỐNG (NVIC INTERRUPT NUMBER)      */
/* ========================================================================== */
typedef enum 
{
    Reset_IRQn                    = -15,
    NonMaskableInt_IRQn           = -14,
    HardFault_IRQn                = -13,
    
    USART1_IRQn                   = 37,      /* USART1 global Interrupt */
    USART2_IRQn                   = 38,      /* USART2 global Interrupt */
    USART3_IRQn                   = 39       /* USART3 global Interrupt */
} IRQn_Type;

/* ========================================================================== */
/*                         ĐỊA CHỈ NGOẠI VI (MEMORY MAP)                      */
/* ========================================================================== */
#define PERIPH_BASE             0x40000000UL
#define APB1PERIPH_BASE         PERIPH_BASE
#define APB2PERIPH_BASE         (PERIPH_BASE + 0x00010000UL) /* Ngoại vi xuất phát: AFIO */
#define AHBPERIPH_BASE          (PERIPH_BASE + 0x00020000UL) /* Ngoại vi xuất phát: DMA1 */

/* Base address RCC, GPIO, USART2 */
#define RCC_BASE                (AHBPERIPH_BASE + 0x00001000UL)  /* 0x40021000 */
#define GPIOA_BASE              (APB2PERIPH_BASE + 0x00000800UL) /* 0x40010800 */
#define USART2_BASE             (APB1PERIPH_BASE + 0x00004400UL) /* 0x40004400 */

/* ========================================================================== */
/* CẤU TRÚC THANH GHI (REGISTER LAYOUT)               */
/* ========================================================================== */

/* Cấu trúc thanh ghi RCC */
typedef struct
{
    volatile uint32_t CR;       /* Offset: 0x00 */
    volatile uint32_t CFGR;     /* Offset: 0x04 */
    volatile uint32_t CIR;      /* Offset: 0x08 */
    volatile uint32_t APB2RSTR; /* Offset: 0x0C */
    volatile uint32_t APB1RSTR; /* Offset: 0x10 */
    volatile uint32_t AHBENR;   /* Offset: 0x14 */
    volatile uint32_t APB2ENR;  /* Offset: 0x18 */
    volatile uint32_t APB1ENR;  /* Offset: 0x1C */
    volatile uint32_t BDCR;     /* Offset: 0x20 */
    volatile uint32_t CSR;      /* Offset: 0x24 */
} RCC_TypeDef;

/* Cấu trúc thanh ghi của GPIO */
typedef struct
{
    volatile uint32_t CRL;      /* Cấu hình chân từ 0 -> 7   - Offset: 0x00 */
    volatile uint32_t CRH;      /* Cấu hình chân từ 8 -> 15  - Offset: 0x04 */
    volatile uint32_t IDR;      /* Thanh ghi dữ liệu ngõ vào - Offset: 0x08 */
    volatile uint32_t ODR;      /* Thanh ghi dữ liệu ngõ ra  - Offset: 0x0C */
    volatile uint32_t BSRR;     /* Thanh ghi đặt/xóa nhanh   - Offset: 0x10 */
    volatile uint32_t BRR;      /* Thanh ghi xóa nhanh bit   - Offset: 0x14 */
    volatile uint32_t LCKR;     /* Thanh ghi khóa cấu hình   - Offset: 0x18 */
} GPIO_TypeDef;

/* Cấu trúc thanh ghi USART */
typedef struct
{
    volatile uint32_t SR;       /* Thanh ghi trạng thái         - Offset: 0x00 */
    volatile uint32_t DR;       /* Thanh ghi dữ liệu            - Offset: 0x04 */
    volatile uint32_t BRR;      /* Thanh ghi cấu hình Baudrate  - Offset: 0x08 */
    volatile uint32_t CR1;      /* Thanh ghi cấu hình 1         - Offset: 0x0C */
    volatile uint32_t CR2;      /* Thanh ghi cấu hình 2         - Offset: 0x10 */
    volatile uint32_t CR3;      /* Thanh ghi cấu hình 3         - Offset: 0x14 */
    volatile uint32_t GTPR;     /* Thanh ghi Guard time/Prescaler - Offset: 0x18 */
} USART_TypeDef;

/* Ép kiểu con trỏ địa chỉ sang dạng Struct để sử dụng */
#define RCC                     ((RCC_TypeDef *) RCC_BASE)
#define GPIOA                   ((GPIO_TypeDef *) GPIOA_BASE)
#define USART2                  ((USART_TypeDef *) USART2_BASE)

/* ========================================================================== */
/* ĐỊA CHỈ VỊ TRÍ CÁC BIT (BITMASK)                   */
/* ========================================================================== */
/* Enable Clock cho ngoại vi */
#define RCC_APB2ENR_IOPAEN      (1U << 2)  /* Bit bật Clock GPIOA */
#define RCC_APB1ENR_USART2EN    (1U << 17) /* Bit 17: Bật Clock ngoại vi USART2 */


/* Thanh ghi GPIO_CRL (Quản lý chân 0 -> 7) */
// Chân PA2 (TX)
#define GPIO_CRL_MODE2          (3U << 8)  /* Bit 8,9 = 11 */
#define GPIO_CRL_MODE2_0        (1U << 8)  /* Bit 8 = 1 (Output mode, max speed 2 MHz) */
#define GPIO_CRL_CNF2           (3U << 10) /* Bit 10,11 = 11 */
#define GPIO_CRL_CNF2_1         (1U << 11) /* Bit 11 = 1 (Alternate function push-pull) */

// Chân PA3 (RX)
#define GPIO_CRL_MODE3          (3U << 12) /* Bit 12,13 = 11 */
#define GPIO_CRL_CNF3           (3U << 14) /* Bit 14,15 = 11 */
#define GPIO_CRL_CNF3_1         (1U << 15) /* Bit 15 = 1 (Input with pull-up / pull-down) */

/* Thanh ghi GPIO_CRH (Quản lý chân 8 -> 15) */
// Chân PA10 (LED)
#define GPIO_CRH_MODE10         (3U << 8)  /* Bit 8,9 = 11 (Output mode, max speed 50 MHz) */
#define GPIO_CRH_CNF10          (3U << 10) /* Bit 10,11 = 11 (General purpose output push-pull) */

/* ========================================================================== */
/*                        BITMASK ĐIỀU KHIỂN KHỐI USART                       */
/* ========================================================================== */

/* Thanh ghi USART_SR */
#define USART_SR_PE             (1U << 0)  /* Bit 0: Parity Error */
#define USART_SR_FE             (1U << 1)  /* Bit 1: Framing Error */
#define USART_SR_NE             (1U << 2)  /* Bit 2: Noise Error Detected Flag */
#define USART_SR_ORE            (1U << 3)  /* Bit 3: Overrun Error */
#define USART_SR_RXNE           (1U << 5)  /* Bit 5: Read Data Register Not Empty */
#define USART_SR_TXE            (1U << 7)  /* Bit 7: Transmit Data Register Empty */

/* Thanh ghi USART_CR1 */
#define USART_CR1_SBK           (1U << 0)  /* Bit 0: Send Break */
#define USART_CR1_RWU           (1U << 1)  /* Bit 1: Receiver wakeup */
#define USART_CR1_RE            (1U << 2)  /* Bit 2: Receiver Enable (Bật bộ nhận RX) */
#define USART_CR1_TE            (1U << 3)  /* Bit 3: Transmitter Enable (Bật bộ phát TX) */
#define USART_CR1_IDLEIE        (1U << 4)  /* Bit 4: IDLE Interrupt Enable (Ngắt khi đường truyền rảnh) */
#define USART_CR1_RXNEIE        (1U << 5)  /* Bit 5: RXNE Interrupt Enable (Ngắt khi bộ đệm nhận có dữ liệu) */
#define USART_CR1_TCIE          (1U << 6)  /* Bit 6: Transmission Complete Interrupt Enable (Ngắt khi truyền xong hoàn toàn) */
#define USART_CR1_TXEIE         (1U << 7)  /* Bit 7: TXE Interrupt Enable (Ngắt khi thanh ghi dữ liệu trống) */
#define USART_CR1_PEIE          (1U << 8)  /* Bit 8: PE Interrupt Enable (Ngắt khi có lỗi Parity) */
#define USART_CR1_PS            (1U << 9)  /* Bit 9: Parity Selection (0: Even Parity, 1: Odd Parity) */
#define USART_CR1_PCE           (1U << 10) /* Bit 10: Parity Control Enable (Bật kiểm tra lỗi Parity) */
#define USART_CR1_WAKE          (1U << 11) /* Bit 11: Wakeup method (0: Idle Line, 1: Address Mark) */
#define USART_CR1_M             (1U << 12) /* Bit 12: Word length (0: 8 Data bits, 1: 9 Data bits) */
#define USART_CR1_UE            (1U << 13) /* Bit 13: USART Enable (Kích hoạt toàn bộ khối ngoại vi USART) */

/* Thanh ghi USART_CR2 */
#define USART_CR2_STOP          (3U << 12) /* Bitmask quét cả 2 bit 12 và 13 */

#define USART_CR2_STOP_1BIT     (0U << 12) /* 00: 1 Stop Bit (Mặc định) */
#define USART_CR2_STOP_0_5BIT   (1U << 12) /* 01: 0.5 Stop Bit */
#define USART_CR2_STOP_2BIT     (2U << 12) /* 10: 2 Stop Bits */
#define USART_CR2_STOP_1_5BIT   (3U << 12) /* 11: 1.5 Stop Bits */

/* ========================================================================== */
/* CORE CORTEX-M3: HÀM KHỞI TẠO ĐIỀU KHIỂN HỆ THỐNG NGẮT NVIC                */
/* ========================================================================== */

/* Hàm kích hoạt ngắt trên NVIC */
static inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)IRQn >= 0)
    {
        uint32_t irq = (uint32_t)IRQn;
        if (irq < 32) {
            volatile uint32_t *nvic_iser0 = (volatile uint32_t *)0xE000E100UL;
            *nvic_iser0 |= (1U << irq);
        } else if (irq < 64) {
            volatile uint32_t *nvic_iser1 = (volatile uint32_t *)0xE000E104UL;
            *nvic_iser1 |= (1U << (irq - 32));
        }
    }
}

/* Hàm cài đặt độ ưu tiên ngắt trên NVIC */
static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    if ((int32_t)IRQn >= 0)
    {
        volatile uint8_t *nvic_ipr = (volatile uint8_t *)0xE000E400UL;
        nvic_ipr[(uint32_t)IRQn] = (uint8_t)((priority << 4) & 0xFFUL);
    }
}

#endif /* __SYSTEM_STM32F10x_H */