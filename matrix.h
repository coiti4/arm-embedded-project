#ifndef MATRIX_H
#define MATRIX_H

typedef enum {false=0, true=1} bool;  

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

void RST(bool x);
void SB(bool x);
void LAT(bool x);
void SCK(bool x);
void SDA(bool x);
void ROW0(bool x);
void ROW1(bool x);
void ROW2(bool x);
void ROW3(bool x);
void ROW4(bool x);
void ROW5(bool x);
void ROW6(bool x);
void ROW7(bool x);

void matrix_init();

void pulse_SCK();

void pulse_LAT();

void deactivate_rows();

void activate_row(int row);

void send_byte(uint8_t val, int bank);

void mat_set_row(int row, const rgb_color *val);

void init_bank0();

void test_row(int row);

void test_pixels();

void affiche_limage();

#endif