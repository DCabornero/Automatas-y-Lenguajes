#ifndef MINIMIZA_H
#define MINIMIZA_H

#include <stdio.h>
#include "afnd.h"
#include "particion.h"

AFND* AFNDMinimiza(AFND* afnd);

SetEstados* Reachable(AFND* afnd);

#endif
