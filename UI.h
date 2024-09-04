#ifndef UI_H
#define UI_H

void setBackgroundColor();
void changeColor(ColorOption bg, ColorOption text);
void drawBox(int x, int y, int width, int height, uint16_t fg, uint16_t bg);
void drawUI();
void tb_print(int x, int y, uint16_t fg, uint16_t bg, const char *str);

#endif // UI_H
