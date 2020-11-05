/*
 * Author: Jakub Standarski
 * Email: jstand.jakub.standarski@gmail.com
 *
 * Date: 05.11.2020
 *
 */

#ifndef PWR_H
    #define PWR_H

/*****************************************************************************/
/* PUBLIC FUNCTIONS PROTOTYPES */
/*****************************************************************************/

/**
 * @brief   Enable power controller, its clock and backup domain access.
 *          Set regulation voltage scalling output.
 *
 * @param   None.
 *
 * @retval  None.
 */
void pwr_init(void);



#endif /* PWR_H */

