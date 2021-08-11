/*
 * kalman_filter.h
 *
 *  Created on: Jul 23, 2021
 *      Author: PC5
 */

#ifndef SRC_RANG_DONG_KALMAN_FILTER_H_
#define SRC_RANG_DONG_KALMAN_FILTER_H_

#include "math.h"
void KalmanFilter_init(float mea_e, float est_e, float q);
float KalmanFilter_updateEstimate(float mea);
void setMeasurementError(float mea_e);
void setEstimateError(float est_e);
void setProcessNoise(float q);
float getKalmanGain();
float getEstimateError();
#endif /* SRC_RANG_DONG_KALMAN_FILTER_H_ */
