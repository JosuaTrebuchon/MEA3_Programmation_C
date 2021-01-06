/*
 * math_stat.h
 *
 *  Created on: 13 nov. 2020
 *      Author: mea
 */

#ifndef __MATH_STAT_H__
#define __MATH_STAT_H__

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * Calculate the average of the specified array.
 *
 * @param array
 * @param size - size of the array
 * @return the calculated average
 */
float stat_avg(float array[], unsigned int size){
	// Initialisation of the sum and the number of values
	float sum = 0;
	float nb_values = 0;
	int i;

	for(i = 0; i < size; i++){
		sum += array[i];
		nb_values++;
	}
	// We return the average (sum divided by the number of values used)
	// Cast as a float value to avoid interger value the resulte of the division
	return (float) (sum / nb_values);
}

/**
 * Calculate the variance of the specified array.
 *
 * @param array
 * @param size - size of the array
 * @return the calculated variance
 */
float stat_var(float array[], unsigned int size){
	float square_array[size];
	float avg = stat_avg(array, size);
	float avg_sqrd_values;
	// On fabrique un tableau des valeurs au carré
	for(int i = 0; i < size; i++){
		square_array[i] = array[i]*array[i];
	}
	// on calcule la moyenne des xi carrés
	avg_sqrd_values = stat_avg(square_array, size);

	return (float) (avg_sqrd_values - (avg*avg));
}

/**
 * Calculate the covariance between the two specified arrays.
 * They must have to same size.
 *
 * @param array_1
 * @param array_2
 * @param size - size of the two arrays
 * @return the calculated covariance
 */
float stat_covar(float array_1[], float array_2[], unsigned int size){
	float array_xy[size];

	for(int i = 0; i < size; i++){
		array_xy[i] = array_1[i]*array_2[i];
	}

	return (stat_avg(array_xy, size) - (stat_avg(array_1, size)*stat_avg(array_2, size)));
}

/**
 * Calculate the Pearson correlation coefficients of the two specified arrays
 *
 * @param array_1
 * @param array_2
 * @param size - size of the two arrays
 * @return the calculated pearson correlation coefficients
 */
float stat_pearson(float array_1[], float array_2[], unsigned int size){

	float mul = stat_var(array_2, size) * stat_var(array_1, size);

	return (stat_covar(array_1, array_2, size) / sqrt(mul));
}
/**
 * Calculate the two coefficients of the linear regression of the two specified arrays,
 * display the equation E(Y) = a * X + b and estimate E(Y) for x.
 *
 * @param array_1
 * @param array_2
 * @param size - size of the two arrays
 * @param x - value to estimate the E(Y) of
 * @return the estimated value of E(Y) for x
 */
float stat_lin_reg(float array_1[], float array_2[], unsigned int size, float x){
	float a = stat_covar(array_1, array_2, size) / stat_var(array_1, size);
	float b = stat_avg(array_2, size) - (a * stat_avg(array_1, size));

	printf("E(Y) = %.3f * X + %.3f\n", a, b);

	return ((a*x)+b);
}

#endif // __MATH_STAT_H__
