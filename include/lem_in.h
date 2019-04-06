/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/06 17:55:06 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFF_SIZE		512
# define C_RED			"\e[41m"
# define C_NONE			"\033[0;00m"

/*
**	Messages d'erreurs
*/
# define UNKCOMM		"Command line not well formatted"
# define OUTDOMAIN		"Numerical argument out of domain"
# define NONNUM			"Non-numeric value encountered"
# define BADINPUT		"Invalid argument"
# define EMPTYLINE		"Empty line"

typedef struct			s_graph
{
	uint32_t			ants;
	uint16_t			rooms;
	uint16_t			connections;
}						t_graph;

uint8_t					ft_read_std_input(t_graph *graph);

#endif
