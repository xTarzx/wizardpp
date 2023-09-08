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

    static void *_scan(void *context);

public:
    void scan();

    std::string get_device_ip();

    WIZ_SCAN_STATE get_scan_state();
};