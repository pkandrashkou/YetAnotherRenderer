//
//  math.h
//  YetAnotherRender
//
//  Created by Pavel Kondrashkov on 3/13/20.
//  Copyright © 2020 pkondrashkov. All rights reserved.
//

#ifndef math_h
#define math_h

#ifdef __cplusplus
extern "C" {
#endif

void swap(int *a, int *b);
void interpolate(int i0, int d0, int i1, int d1, int *values[]);

#ifdef __cplusplus
}
#endif

#endif /* math_h */
