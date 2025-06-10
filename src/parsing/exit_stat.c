<<<<<<< HEAD:exit_stat.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:07:45 by michoi            #+#    #+#             */
/*   Updated: 2025/05/30 19:42:12 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/**
 * When cmd is executed, this function is called and exit status code is saved and returned.
 * @param code: exit status code from an executed command.
 * @param set: determins if the status code is set or retrieved.
 */
int    set_and_get_exit_status(int code, bool set)
{
    static int stat_code = 0;
    if (set)
       stat_code = code;
    // custom_export()
    return (stat_code);
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:07:45 by michoi            #+#    #+#             */
/*   Updated: 2025/06/07 14:51:09 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * When cmd is executed, this function is called and exit status code is saved and returned.
 * @param code: exit status code from an executed command.
 * @param set: determins if the status code is set or retrieved.
 */
int    set_and_get_exit_status(int code, bool set)
{
    static int stat_code = 0;
    if (set)
       stat_code = code;
    // custom_export()
    return (stat_code);
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/parsing/exit_stat.c
}