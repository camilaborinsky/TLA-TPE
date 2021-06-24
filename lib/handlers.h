#ifndef HANDLERS_H
#define HANDLERS_H

void set_interval(unsigned long long ms, void (*callback)(void));
void on_key(int key, void (*handler)(void));
void loop();

#endif