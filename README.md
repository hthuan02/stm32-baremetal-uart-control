# Buid Bare Metal system with UART - STM32F103C8T6

#### Mục tiêu project
- Xây dựng dự án bare-metal hoàn chỉnh với startup file, linker script, driver ngoại vi và biên dịch bằng Makefile.

- Hiểu sâu về quá trình Build Process (Compilation, Linking) và quy trình flash firmware xuống MCU mà không phụ thuộc vào IDE.

- Lập trình cấu hình thanh ghi đối với các ngoại vi (Register-level): RCC (Clock), GPIO, và UART.

- Thay cơ chế phản hồi điều khiển (Polling) bằng cơ chế ngắt (Interrupt) kết hợp cấu trúc vòng đệm (Ring Buffer) để tối ưu hóa hiệu năng CPU tăng tốc độ xử lý.

---

https://github.com/user-attachments/assets/757e9605-6a00-402d-90b2-5cac36012d12

## Tài liệu nghiên cứu
| File | Description |
|---|---|
|[rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf](rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)| Tra cứu cấu trúc thanh ghi, bản đồ bộ nhớ và cấu hình chi tiết các ngoại vi (RCC, GPIO, UART...) cho dòng STM32F1. |

## Giới thiệu 
Project sử dụng vi điều khiển STM32F103C8T6, lõi ARM Cortex-M3. Đây là dòng MCU lý tưởng để tiếp cận cấp độ bare-metal nhờ cấu trúc thanh ghi mạch lạc và bản đồ bộ nhớ (Memory Map) tường minh.

### I. Hardware

<table align="center">
  <tr>
    <td align="center"><img width="500" height="430" alt="Image" src="https://github.com/user-attachments/assets/28de0e0b-8d20-4ddb-9c46-257320c9cb57" /></td>
  </tr>
</table>
<p align="center"><strong><em>Hình 1:</em></strong> Board Blue Pill </p>

**MCU: Overview**
```c
SoC Name   : STM32F103C8T6
SRAM       : 20KB (Address Base: 0x2000 0000)
Flash      : 64KB (Address Base: 0x0800 0000)
Peripherals:       Address Base: 0x4000 0000
```



<table align="center">
  <tr>
    <td align="center"><img width="420" height="420" alt="Image" src="https://github.com/user-attachments/assets/c2367a30-a875-4d79-a7a1-89127d4251d6" /></td>
  </tr>
</table>
<p align="center"><strong><em>Hình 2:</em></strong> Module USB-TTL(CP2110) </p>


**Module: Overview**
```c
Module Name : USB To TTL CP2102
Chipset     : CP2102 (Silicon Labs)
Hardware Specifications
- Interface     : USB 2.0 to TTL Level (3.3V / 5V Tolerant)
- Baud Rates    : 300 bps to 1 Mbps
- Pinouts       : 3V3, TXD, RXD, GND, +5V
```

<table align="center">
  <tr>
    <td align="center"><img width="600" height="520" alt="Image" src="https://github.com/user-attachments/assets/f70b1d66-2590-4230-abac-aeae6f3c46df" /></td>
  </tr>
</table>
<p align="center"><strong><em>Hình 3:</em></strong> Sơ đồ khối chức năng </p>

## II. Cấu trúc thư mục

```text
├── doc/                    # Thư mục chứa Reference Manual
├── driver/                 # Thư mục chứa các Driver 
│   ├── gpio/               
│   │   ├── gpio.c
│   │   └── gpio.h
│   ├── ring_buffer/       
│   └── uart/               
├── linker/                 # Chứa file Linker Script (.ld) 
├── output/                 # Thư mục chứa các file build đầu ra (.o, .map, .elf, .hex)
├── startup/                # Thư mục chứa Startup file khởi tạo Vector Table
├── user/                   # Tầng ứng dụng của người dùng
│   ├── inc/
│   │   └── sys_stm32f10x.h # File định nghĩa base address
│   └── src/
│       └── main.c          # Luồng xử lý chính (Main Loop) điều khiển LED và phản hồi UART
├── Makefile                # Script tự động hóa toàn bộ quy trình biên dịch (Build Process)
└── README.md               # Tài liệu hướng dẫn và mô tả chi tiết dự án
```

