/*!
 * @file 
 * @brief Door.h keeps the doorstates, and contains functions to open, close and construct a door instance
 */

#pragma once

/*!
 * @brief Enum containing the doorstates @p OPEN and @p CLOSED
 * 
 */
typedef enum {
   
    OPEN = 1,
    CLOSED = 0

} DoorState;

/*!
 * @brief Struct that keeps a @p Doorstate
 */
typedef struct {
    DoorState doorstate;
} Door;

/*!
 * @brief Opens the door by setting the door lamp, and changes the Doorstate to OPEN
 * @param[in] door Pointer to a door object
 */

void open_Door(Door* door);

/*!
 * @brief Closes door by setting the doorlight, and changes the Doorstate to CLOSED
 * @param[in] door Pointer to a door object
 */

void close_door(Door* door);

/*!
 * @brief Constructs an instance of a door object
 * @param[in] Door sets the doorstate value of the newly created Door-instance
 * @return the Door-instance
 */
Door door_constructor(DoorState Door);



