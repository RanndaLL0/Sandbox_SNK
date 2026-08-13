#include <stdint.h>
#include <unistd.h>

typedef struct {
  uint32_t D[8];
  uint32_t A[8]; //A7: ponteiro para pilha do usuario
  uint32_t PC;

  /*
   * O lower byte serão utilizados como flags do processados, X,N,Z,V,C
   * O outro byte sera utilizado como flags de controle para o hardware.
   * */
  uint16_t SR;
} m68k_cpu;

m68k_cpu cpu;
uint8_t ram[1024 * 1024];


uint8_t m68k_read(uint32_t addr) {
  return ram[addr];
}

uint16_t m68k_read_word(uint32_t addr) {
  uint8_t high_byte = ram[addr];
  uint8_t lower_byte = ram[addr + 1];

  return (high_byte << 8) | lower_byte;
}

uint32_t m68k_read_long_word(uint32_t addr) {
  
  uint16_t high_byte = m68k_read_word(addr);
  uint16_t lower_byte = m68k_read_word(addr + 2);

  return (high_byte << 16) | lower_byte;
}

void mk68k_write(uint32_t addr, uint8_t data) {
  ram[addr] = data;
}

void m68k_write_word(uint32_t addr, uint16_t data) {
  uint8_t lower_byte = (data & 0xFF);
  uint8_t high_byte = (data >> 8) & 0xFF; //nao precisava da mascara, mas vai que
  ram[addr] = high_byte;
  ram[addr + 1] = lower_byte;
}

void m68k_write_long_word(uint32_t addr, uint32_t data) {
  uint16_t lower_word = (data & 0xFFFF);
  uint16_t high_word = (data >> 16) & 0xFFFF;
  m68k_write_word(addr, high_word);
  m68k_write_word(addr + 2, lower_word);
}


