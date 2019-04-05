/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/05 16:48:40 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFF_SIZE		512
# define C_RED			"\033[0;31m"
# define C_NONE			"\033[0;00m"

/*
**	Messages d'erreurs
*/
# define NOTNUM			"Non-numeric value encountered"
# define OUTDOMAIN		"Numerical argument out of domain"

typedef struct			s_graph
{
	uint32_t			ants;
	uint16_t			rooms;
	uint16_t			connections;
}						t_graph;

#endif
