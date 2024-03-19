/*!
* @file
* @brief elevator_cab.h stores the current direction and floor of the elevator, and constructs and initializes an elevator
*/

#pragma once

#include "elevio.h"
#include "con_load.h"
#include <stdbool.h>
#include <stdio.h>

/*!
 * @brief Physically stops the motor
 * 
 */
void stopMotor();

/*!
 * @brief Enum that keeps track of the defined elevator floors
 * 
 */

typedef enum {
    
    FIRST_FLOOR =  0,
    SECOND_FLOOR = 1,
    THIRD_FLOOR = 2,
    FOURTH_FLOOR = 3

} Floor;

/*!
 * @brief Struct that contains an elevator floor and elevator direction
 * - @p floor Holds a floor value from the @c Floor enum
 * - @p direction Holds a motor direction value from the @c MotorDirection struct
 */

typedef struct {
    
    Floor floor;
    MotorDirection direction;               

} Elevator_cab;

/*!
 * @brief Reads the current floor from the floor sensor
 * 
 * @return integer with a value from -1 (in between floors) and 0 to 3 depending on the floor 
 */
int read_current_floor();

/*!
 * @brief Brings the elevator cab to the first floor when starting the program. Sets and checks the floor- and direction states in order to do so
 * @param[in, out] elevator_cab Pointer to an @c Elevator_cab object
 */

void initialize_elevator_cab(Elevator_cab* elevator_cab);

/*!
 * @brief Creates a pointer to an @c Elevator_cab object
 * 
 * @param[in] floor Sets the floor memeber variable of @c elevator_cab to the value of @p floor
 * @param[in] direction Sets the direction memeber variable of @c elevator_cab to the value of @p direction
 * @return &elevator_cab Pointer to the global variable @c elevator_cab
 * @details
 * - @c elevator_cab is a global variable in the c-file, to later take care of the initialization of the @c Statemachine object
 */

Elevator_cab* elevator_cab_constructor(Floor floor, MotorDirection direction);


