#include "bulb.h"

enum WIZ_SCAN_STATE
{
    NOTHING = 0,
    SCANNING,
    NOT_FOUND,
    FOUND,
};

class WiZard
{
private:
    Bulb bulb;

    WIZ_SCAN_STATE scan_state = WIZ_SCAN_STATE::NOTHING;

    int rgb[3] = {0};

    static void *_scan(void *context);
    static void *_turn_on(void *context);
    static void *_turn_off(void *context);
    static void *_set_rgb(void *context);

public:
    void scan();

    void turn_on();
    void turn_off();

    void set_rgb(int r, int g, int b);

    std::string get_device_ip();

    WIZ_SCAN_STATE get_scan_state();
};