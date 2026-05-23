ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector)
        *(.text)
        *(.text*)          
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .; /* _etext lưu địa chỉ trong FLASH, ngay sau vùng .text */
    }> FLASH
    
    /* Thêm ALIGN(4) trước khi lấy địa chỉ bắt đầu _sdata */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH
    
    /* Thêm ALIGN(4) trước _sbss */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    }> SRAM
}