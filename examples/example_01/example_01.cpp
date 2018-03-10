//
// Created by Marcin Zawada on 07.12.2017.
//

#include <cstdio>
#include "../../src/ADNS_5050.h"

int main () {
    ADNS_5050 *adns_5050 = new ADNS_5050();

    unsigned char product_id = adns_5050->get_product_id();
    printf ("Product id: %02x\n", product_id);

    delete adns_5050;
}