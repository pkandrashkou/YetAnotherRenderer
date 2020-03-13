//
//  math.c
//  YetAnotherRender
//
//  Created by Pavel Kondrashkov on 3/13/20.
//  Copyright © 2020 pkondrashkov. All rights reserved.
//

#include "math.h"

#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void interpolate(int i0, int d0, int i1, int d1, int *values[]) {
    *values = (int *)calloc(i1 - i0, sizeof(int));
    if (i0 == i1) {
        (*values)[0] = d0;
        return;
    }
    float a = (d1 - d0) / (float) (i1 - i0);
    float d = (float)d0;
    int value_inedx = 0;
    for (int i = i0; i < i1; i++) {
        (*values)[value_inedx] = (int)d;
        value_inedx++;
        d = d + a;
    }
}
