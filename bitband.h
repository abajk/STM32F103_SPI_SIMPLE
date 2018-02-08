/* base address for bit banding */
#define BITBAND_PERIPH_REF                  (0x40000000)
/* base address for bit banding */
#define BITBAND_PERIPH_BASE                 (0x42000000)
#define BITBAND_PERIPH(address, bit) ((void*)(BITBAND_PERIPH_BASE + (((uint32_t)address) - BITBAND_PERIPH_REF) * 32 + (bit) * 4))