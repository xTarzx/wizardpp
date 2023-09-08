#include <string>
#include <pthread.h>

#include "wizard.h"
#include "jansson.h"

void *WiZard::_scan(void *context)
{
    WiZard *wiz = (WiZard *)context;
    // get broadcast address from system; maybe add input for it
    wiz->scan_state = WIZ_SCAN_STATE::SCANNING;
    std::string res = wiz->bulb.discover("192.168.1.255");
    json_t *root;
    json_error_t error;
    root = json_loads(res.c_str(), 0, &error);

    if (root == NULL)
    {
        wiz->bulb.setDeviceIP("");
        wiz->scan_state = WIZ_SCAN_STATE::NOT_FOUND;
        // error finding devices
        pthread_exit(NULL);
    }

    json_t *bulb_response = json_object_get(root, "bulb_response");
    json_t *ip = json_object_get(bulb_response, "ip");

    std::string b_ip = json_string_value(ip);
    wiz->scan_state = WIZ_SCAN_STATE::FOUND;
    wiz->bulb.setDeviceIP(b_ip);

    json_decref(root);
    // std::cout << "bulb ip: " << b_ip << std::endl;
    pthread_exit(NULL);
};

void WiZard::scan()
{
    pthread_t thread;

    int ret = pthread_create(&thread, NULL, &_scan, this);
    // std::cout << "ret: " << ret << std::endl;
    (void)ret;
}

void *WiZard::_turn_on(void *context)
{
    WiZard *wiz = (WiZard *)context;

    wiz->bulb.toggleLight(true);
    pthread_exit(NULL);
}

void WiZard::turn_on()
{
    pthread_t thread;

    int ret = pthread_create(&thread, NULL, &_turn_on, this);
    // std::cout << "ret: " << ret << std::endl;
    (void)ret;
}

void *WiZard::_turn_off(void *context)
{
    WiZard *wiz = (WiZard *)context;

    wiz->bulb.toggleLight(false);
    pthread_exit(NULL);
}

void WiZard::turn_off()
{
    pthread_t thread;

    int ret = pthread_create(&thread, NULL, &_turn_off, this);
    // std::cout << "ret: " << ret << std::endl;
    (void)ret;
}

void *WiZard::_set_rgb(void *context)
{
    WiZard *wiz = (WiZard *)context;

    wiz->bulb.setRGBColor(wiz->rgb[0], wiz->rgb[1], wiz->rgb[2]);
    pthread_exit(NULL);
}

void WiZard::set_rgb(int r, int g, int b)
{
    this->rgb[0] = r;
    this->rgb[1] = g;
    this->rgb[2] = b;
    pthread_t thread;

    int ret = pthread_create(&thread, NULL, &_set_rgb, this);
    // std::cout << "ret: " << ret << std::endl;
    (void)ret;
}

std::string WiZard::get_device_ip()
{
    return this->bulb.getDeviceIp();
}

WIZ_SCAN_STATE WiZard::get_scan_state()
{
    return this->scan_state;
}