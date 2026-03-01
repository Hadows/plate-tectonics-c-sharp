/******************************************************************************
 *  plate-tectonics, a plate tectonics simulation library
 *  Copyright (C) 2012-2013 Lauri Viitanen
 *  Copyright (C) 2014-2015 Federico Tomassetti, Bret Curtis
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see http://www.gnu.org/licenses/
 *****************************************************************************/

#ifndef PLATECAPI_H
#define PLATECAPI_H

#include <stdint.h>

#if defined(_WIN32) || defined(__CYGWIN__)
  #if defined(PLATEC_BUILD_DLL)
    #define PLATEC_API __declspec(dllexport)
  #elif defined(PLATEC_USE_DLL)
    #define PLATEC_API __declspec(dllimport)
  #else
    #define PLATEC_API
  #endif
  #define PLATEC_CALL __cdecl
#else
  #if __GNUC__ >= 4
    #define PLATEC_API __attribute__((visibility("default")))
  #else
    #define PLATEC_API
  #endif
  #define PLATEC_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

PLATEC_API void* PLATEC_CALL platec_api_create(
    long seed, uint32_t width, uint32_t height, float sea_level, uint32_t erosion_period,
    float folding_ratio, uint32_t aggr_overlap_abs, float aggr_overlap_rel, uint32_t cycle_count,
    uint32_t num_plates);

PLATEC_API void PLATEC_CALL platec_api_destroy(void*);
PLATEC_API const uint32_t* PLATEC_CALL platec_api_get_agemap(uint32_t);
PLATEC_API float* PLATEC_CALL platec_api_get_heightmap(void*);
PLATEC_API uint32_t* PLATEC_CALL platec_api_get_platesmap(void*);
PLATEC_API uint32_t PLATEC_CALL platec_api_is_finished(void*);
PLATEC_API void PLATEC_CALL platec_api_step(void*);

PLATEC_API float PLATEC_CALL platec_api_velocity_unity_vector_x(void*, uint32_t plate_index);
PLATEC_API float PLATEC_CALL platec_api_velocity_unity_vector_y(void*, uint32_t plate_index);

PLATEC_API uint32_t PLATEC_CALL lithosphere_getMapWidth(void* object);
PLATEC_API uint32_t PLATEC_CALL lithosphere_getMapHeight(void* object);

#ifdef __cplusplus
}
#endif

#endif
