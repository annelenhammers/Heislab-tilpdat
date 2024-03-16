/*!
* @file
* @brief Elevator_cab stores the current direction and floor of the elevator, and constructs and initializes the cab 
*/

#pragma once

#include "elevio.h"
#include "con_load.h"
#include <stdbool.h>
#include <stdio.h>

/*!
 * @brief Floor is an enum to keep track of the defined elevator floors
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
 * @c floor Holds a floor value from the @c Floor enum
 * @c direction Holds a motor direction value from the @c MotorDirection struct
 * 
 */
typedef struct {
    
    Floor floor;
    MotorDirection direction;               

} Elevator_cab;

/*!
 * @brief reads the current floor from the floor sensor
 * 
 * @return int with a value from -1 to 3 depending on the floor 
 */
int read_current_floor();

/*!
 * @brief Brings the elevator cab to the first floor when starting the program. Sets and checks the states floor- and direction states in order to do so
 * 
 * @param[in, out] elevator_cab Pointer to an @c Elevator_cab object
 */

void initialize_elevator_cab(Elevator_cab* elevator_cab);

/*!
 * @brief creates a pointer to an elevator_cab object
 * 
 * @param[in] floor Sets the floor memeber variable of @c elevator_cab to the value of @p floor
 * @param[in] direction Sets the direction memeber variable of @c elevator_cab to the value of @p direction
 * @return &Elevator_cab dereferenced pointer value of @c elevatro_cab
 * @details
 * - @c elevator_cab is a global variable in the c-file
 */
Elevator_cab* elevator_cab_constructor(Floor floor, MotorDirection direction);


