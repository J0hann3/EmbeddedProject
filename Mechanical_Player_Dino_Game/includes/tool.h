#ifndef TOOL_H
# define TOOL_H

# include <avr/io.h>
# include <util/delay.h>

# define SET(PORT, N) ((PORT) |= (1 << (N)))
# define RESET(PORT, N) ((PORT) &= ~(1 << (N)))
# define TOGGLE(PORT, N) ((PORT) ^= (1 << (N)))

#endif