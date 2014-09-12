#include "drivers/common.h"
#include "drivers/HTPB-driver.h"

// Hardware-specific support functions that MUST be customized:
#define I2CSPEED 100
void I2C_delay() { volatile int v; int i; for (i=0; i < I2CSPEED/2; i++) v; }
bool read_SCL(void); // Set SCL as input and return current level of line, 0 or 1
bool read_SDA(void); // Set SDA as input and return current level of line, 0 or 1
void clear_SCL(void); // Actively drive SCL signal low
void clear_SDA(void); // Actively drive SDA signal low
void arbitration_lost(void);
void setupI2C(short pin);
task readI2C();
