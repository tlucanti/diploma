
#include <iostream>

struct AdcMsg {
    uint8_t id;
    uint8_t selftest;
    uint8_t ovr;
    uint8_t rsvd;
    uint16_t cycle;
    uint16_t impulse;
    uint32_t offset;
    uint16_t flags;
    uint16_t temperature;
    uint8_t data[1408];
} __attribute__((__packed__));

int main()
{
	struct AdcMsg msg = {
		.id=0,
		.selftest=0,
		.ovr=0,
		.rsvd=0,
		.cycle=q
	}
}

