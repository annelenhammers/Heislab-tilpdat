/*!
 * @file 
 * @brief Door keeps the doorstates, and have functions to open, close and construct a door
 */

#pragma once

/*!
 * @brief Doorstate is an enum containing the doorstates @p OPEN and @p CLOSED
 * 
 */
typedef enum {
   
    OPEN = 1,
    CLOSED = 0

} DoorState;

/*!
 * @brief Door is a struct that keeps the Doorstate
 */
typedef struct {
    DoorState doorstate;
} Door;

/*!
 * @brief Opens the door by setting the doorlight, and changes the Doorstate to OPEN
 * @param[in] door is a pointer to a door object
 */
void _openDoor(Door* door);

/*!
 * @brief Closes door by setting the doorlight, and changes the Doorstate to CLOSED
 * 
 * @param[in] door is a pointer to a door object
 */

void close_door(Door* door);

/*!
 * @brief Constructs an instance of a door object
 * 
 * @param Door 
 * @return door
 */
Door door_constructor(DoorState Door);



