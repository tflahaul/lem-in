/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bug.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:07:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 19:41:04 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_BUG_H
# define LEM_IN_BUG_H

/*
**	Code couleur pour l'affichage des erreurs
*/
# define C_RED			"\e[41m"
# define C_NONE			"\033[0m"

/*
**	Messages d'erreurs
*/
# define BADNAME		"Invalid verticle name"
# define MEMERR			"Memory allocation failure"
# define TOOBIG			"Number of rooms out of domain, adjust MAX_VERTICES"
# define UNKCOMM		"Command line not well formatted"
# define DUPLICATE		"Two rooms cannot have the same name"
# define OUTDOMAIN		"Numerical argument out of domain"
# define NONNUM			"Non-numeric value encountered"
# define MEMFULL		"No space left on device"
# define BADINPUT		"Invalid argument"
# define EMPTYLINE		"Empty line"
# define DUPLINK		"Connection already exists"
# define NOROOM			"Room doesn't exist"

#endif
