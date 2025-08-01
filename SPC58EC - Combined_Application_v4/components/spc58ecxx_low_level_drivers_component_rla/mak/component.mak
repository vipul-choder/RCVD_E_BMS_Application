# List of library files exported by the component.
LIB_C_SRC       += ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/spc5_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/spc5_edma.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/can_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/serial_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/pit_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/spi_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/saradc_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/wkpu_lld.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/lib/src/spc5_linflex.c \

LIB_CPP_SRC     +=

LIB_ASM_SRC     +=

LIB_INCLUDES    += ./components/spc58ecxx_low_level_drivers_component_rla/lib/include

APP_C_SRC       += \
                   ./components/spc58ecxx_low_level_drivers_component_rla/cfg/serial_lld_cfg.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/cfg/can_lld_cfg.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/cfg/pit_lld_cfg.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/cfg/spi_lld_cfg.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/cfg/saradc_lld_cfg.c \
                   ./components/spc58ecxx_low_level_drivers_component_rla/cfg/wkpu_lld_cfg.c \

APP_CPP_SRC     +=

APP_ASM_SRC     +=

APP_INCLUDES    += ./components/spc58ecxx_low_level_drivers_component_rla/cfg
