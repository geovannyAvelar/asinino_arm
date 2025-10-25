#include "bsp/board_api.h"
#include "bsp_api.h"


/* ######################### BOOTLOADERS that use BOSSA ##################### */
#ifdef BOSSA_LOADER 
  
  /* **************** BOOTLOADERS that use BOSSA and DFU ******************* */   
  
  #ifdef DFU_LOADER
    /* OPTA expansions:
        - OPTA ANALOG
        - OPTA DIGITAL  */

    /* interrupt declaration */
    
    //void usbfs_interrupt_handler(void);
    //void usbfs_resume_handler(void);
    //void usbfs_d0fifo_handler(void);
    //void usbfs_d1fifo_handler(void);
    //void usbhs_interrupt_handler(void);
    //void usbhs_d0fifo_handler(void);
    //void usbhs_d1fifo_handler(void);
    void sci_uart_txi_isr(void);
    void sci_uart_tei_isr(void);
    void sci_uart_rxi_isr(void);
    void sci_uart_eri_isr(void);

    /* interrupt table */

    BSP_DONT_REMOVE BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS)
    const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] = {
      [0] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
      [1] = usbfs_resume_handler,    /* USBFS RESUME (USBFS resume interrupt) */
      #ifndef RENESAS_CORTEX_M23
      [2] = usbfs_d0fifo_handler,    /* USBFS FIFO 0 (DMA transfer request 0) */
      [3] = usbfs_d1fifo_handler,    /* USBFS FIFO 1 (DMA transfer request 1) */
      #endif  
      #ifdef BOARD_HAS_USB_HIGHSPEED
      [4] = usbhs_interrupt_handler, /* USBHS INT (USBHS interrupt) */
      [5] = usbhs_d0fifo_handler,    /* USBHS FIFO 0 (DMA transfer request 0) */
      [6] = usbhs_d1fifo_handler,    /* USBHS FIFO 1 (DMA transfer request 1) */
      #endif
      [7] = sci_uart_txi_isr,
      [8] = sci_uart_tei_isr,
      [9] = sci_uart_rxi_isr,
      [10] = sci_uart_eri_isr
    };

    const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] = {
      [0] = BSP_PRV_IELS_ENUM(EVENT_USBFS_INT),            /* USBFS INT (USBFS interrupt) */
      [1] = BSP_PRV_IELS_ENUM(EVENT_USBFS_RESUME),         /* USBFS RESUME (USBFS resume interrupt) */
      #ifndef RENESAS_CORTEX_M23
      [2] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_0),         /* USBFS FIFO 0 (DMA transfer request 0) */
      [3] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_1),         /* USBFS FIFO 1 (DMA transfer request 1) */
      #endif
      #ifdef BOARD_HAS_USB_HIGHSPEED
      [4] = BSP_PRV_IELS_ENUM(EVENT_USBHS_USB_INT_RESUME), /* USBHS USB INT RESUME (USBHS interrupt) */
      [5] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_0),         /* USBHS FIFO 0 (DMA transfer request 0) */
      [6] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_1),         /* USBHS FIFO 1 (DMA transfer request 1) */
      #endif
      [7] = BSP_PRV_IELS_ENUM(EVENT_SCI2_TXI),
      [8] = BSP_PRV_IELS_ENUM(EVENT_SCI2_TEI),
      [9] = BSP_PRV_IELS_ENUM(EVENT_SCI2_RXI),
      [10] = BSP_PRV_IELS_ENUM(EVENT_SCI2_ERI), 
    };
  

  #else // BOSSA_LOADER but not DFU_LOADER

    /* **************** BOOTLOADERS that use only  BOSSA  ********************* */
    
    /* ARDUINO UNO R4 WIFI */ 
    void sci_uart_txi_isr(void);
    void sci_uart_tei_isr(void);
    void sci_uart_rxi_isr(void);
    void sci_uart_eri_isr(void);

     BSP_DONT_REMOVE const
       fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) = {
         [0] = sci_uart_txi_isr,
         [1] = sci_uart_tei_isr,
         [2] = sci_uart_rxi_isr,
         [3] = sci_uart_eri_isr
     };

     const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] = {
       [0] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TXI),
       [1] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TEI),
       [2] = BSP_PRV_IELS_ENUM(EVENT_SCI9_RXI),
       [3] = BSP_PRV_IELS_ENUM(EVENT_SCI9_ERI)
     };
   #endif // BOSSA_LOADER but not DFU_LOADER
/* ######################### BOOTLOADERS that use DFU ####################### */
#else // DFU_LOADER
 
  #if BSP_FEATURE_FLASH_HP_VERSION
    
    /* PORTENTA C33 */

    #include "r_iic_master.h"
    #include "r_sci_i2c.h"

    /* interrupt declaration */
    
    //void usbfs_interrupt_handler(void);
    //void usbfs_resume_handler(void);
    //void usbfs_d0fifo_handler(void);
    //void usbfs_d1fifo_handler(void);
    //void usbhs_interrupt_handler(void);
    //void usbhs_d0fifo_handler(void);
    //void usbhs_d1fifo_handler(void);
    void fcu_frdyi_isr();
    void fcu_fiferr_isr();
    void sci_i2c_txi_isr();
    void sci_i2c_tei_isr();

    /* interrupt table */

    BSP_DONT_REMOVE BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS)
    const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] = {
      [0] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
      [1] = usbfs_resume_handler,    /* USBFS RESUME (USBFS resume interrupt) */
      #ifndef RENESAS_CORTEX_M23
      [2] = usbfs_d0fifo_handler,    /* USBFS FIFO 0 (DMA transfer request 0) */
      [3] = usbfs_d1fifo_handler,    /* USBFS FIFO 1 (DMA transfer request 1) */
      #endif  
      #ifdef BOARD_HAS_USB_HIGHSPEED
      [4] = usbhs_interrupt_handler, /* USBHS INT (USBHS interrupt) */
      [5] = usbhs_d0fifo_handler,    /* USBHS FIFO 0 (DMA transfer request 0) */
      [6] = usbhs_d1fifo_handler,    /* USBHS FIFO 1 (DMA transfer request 1) */
      #endif
      [7] = fcu_frdyi_isr,
      [8] = fcu_fiferr_isr,
      [9] = sci_i2c_txi_isr,
      [10] = sci_i2c_tei_isr,
    };

    const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] = {
      [0] = BSP_PRV_IELS_ENUM(EVENT_USBFS_INT),            /* USBFS INT (USBFS interrupt) */
      [1] = BSP_PRV_IELS_ENUM(EVENT_USBFS_RESUME),         /* USBFS RESUME (USBFS resume interrupt) */
      #ifndef RENESAS_CORTEX_M23
      [2] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_0),         /* USBFS FIFO 0 (DMA transfer request 0) */
      [3] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_1),         /* USBFS FIFO 1 (DMA transfer request 1) */
      #endif
      #ifdef BOARD_HAS_USB_HIGHSPEED
      [4] = BSP_PRV_IELS_ENUM(EVENT_USBHS_USB_INT_RESUME), /* USBHS USB INT RESUME (USBHS interrupt) */
      [5] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_0),         /* USBHS FIFO 0 (DMA transfer request 0) */
      [6] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_1),         /* USBHS FIFO 1 (DMA transfer request 1) */
      #endif
      [7] = BSP_PRV_IELS_ENUM(EVENT_FCU_FRDYI),
      [8] = BSP_PRV_IELS_ENUM(EVENT_FCU_FIFERR),
      [9] = BSP_PRV_IELS_ENUM(EVENT_SCI3_TXI),
      [10] = BSP_PRV_IELS_ENUM(EVENT_SCI3_TEI), 
    };
    // SCI3 - P310 - P309

    bool status = false;
    static void sci_i2c_callback(i2c_master_callback_args_t *arg) {
      if (arg->event == I2C_MASTER_EVENT_TX_COMPLETE) {
        status = true;
      }
    }

    static iic_master_instance_ctrl_t p_api_ctrl;
    static sci_i2c_extended_cfg_t m_sci_i2c_extend = {
      .clock_settings = {
        .clk_divisor_value = 0,
        .brr_value = 14,
        .mddr_value = 255,
        .bitrate_modulation = false,
        .cycles_value = 15,
        .snfr_value = (1),
      }
    };
    static i2c_master_cfg_t m_i2c_cfg = {
      .p_extend = &m_sci_i2c_extend,
      .p_callback = sci_i2c_callback,
      .channel = 3,
      .rate = I2C_MASTER_RATE_STANDARD,
      .slave = 0,
      .addr_mode = I2C_MASTER_ADDR_MODE_7BIT,
      .txi_irq = 9,
      .tei_irq = 10,
      .ipl = (12),
      .p_context = &m_i2c_cfg,
    };

    void i2c_begin() {
      R_SCI_I2C_Open(&p_api_ctrl, &m_i2c_cfg);
    }

    void i2c_write(uint8_t address, uint8_t reg, uint8_t value) {
      R_SCI_I2C_SlaveAddressSet(&p_api_ctrl, address, m_i2c_cfg.addr_mode);
      uint8_t data[2] = { reg, value };
      R_SCI_I2C_Write(&p_api_ctrl, data, 2, false);
      R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MILLISECONDS);
    }
  #else // BSP_FEATURE_FLASH_HP_VERSION
  
    /* UNO R4 MINIMA */
    //void usbfs_interrupt_handler(void);
    //void usbfs_resume_handler(void);
    //void usbfs_d0fifo_handler(void);
    //void usbfs_d1fifo_handler(void);
    //void usbhs_interrupt_handler(void);
    //void usbhs_d0fifo_handler(void);
    //void usbhs_d1fifo_handler(void);
    

    /* interrupt table */

    BSP_DONT_REMOVE BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS)
    const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] = {
      [0] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
      [1] = usbfs_resume_handler,    /* USBFS RESUME (USBFS resume interrupt) */
      #ifndef RENESAS_CORTEX_M23
      [2] = usbfs_d0fifo_handler,    /* USBFS FIFO 0 (DMA transfer request 0) */
      [3] = usbfs_d1fifo_handler,    /* USBFS FIFO 1 (DMA transfer request 1) */
      #endif  
      #ifdef BOARD_HAS_USB_HIGHSPEED
      [4] = usbhs_interrupt_handler, /* USBHS INT (USBHS interrupt) */
      [5] = usbhs_d0fifo_handler,    /* USBHS FIFO 0 (DMA transfer request 0) */
      [6] = usbhs_d1fifo_handler,    /* USBHS FIFO 1 (DMA transfer request 1) */
      #endif  
    };

    const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] = {
      [0] = BSP_PRV_IELS_ENUM(EVENT_USBFS_INT),            /* USBFS INT (USBFS interrupt) */
      [1] = BSP_PRV_IELS_ENUM(EVENT_USBFS_RESUME),         /* USBFS RESUME (USBFS resume interrupt) */
      #ifndef RENESAS_CORTEX_M23
      [2] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_0),         /* USBFS FIFO 0 (DMA transfer request 0) */
      [3] = BSP_PRV_IELS_ENUM(EVENT_USBFS_FIFO_1),         /* USBFS FIFO 1 (DMA transfer request 1) */
      #endif
      #ifdef BOARD_HAS_USB_HIGHSPEED
      [4] = BSP_PRV_IELS_ENUM(EVENT_USBHS_USB_INT_RESUME), /* USBHS USB INT RESUME (USBHS interrupt) */
      [5] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_0),         /* USBHS FIFO 0 (DMA transfer request 0) */
      [6] = BSP_PRV_IELS_ENUM(EVENT_USBHS_FIFO_1),         /* USBHS FIFO 1 (DMA transfer request 1) */
      #endif
    };

   
  #endif // BSP_FEATURE_FLASH_HP_VERSION

#endif 

