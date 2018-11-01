#ifndef __RISCV32_VEXRISCV_H_
#define __RISCV32_VEXRISCV_H_

#include <soc_common.h>


/* Timer configuration */
#define RISCV_MTIME_BASE             0xF0010
#define RISCV_MTIMECMP_BASE          0xF0018

/* lib-c hooks required RAM defined variables */
#define RISCV_RAM_BASE               CONFIG_RISCV_RAM_BASE_ADDR
#define RISCV_RAM_SIZE               CONFIG_RISCV_RAM_SIZE

#endif /* __RISCV32_VEXRISCV_H_ */
