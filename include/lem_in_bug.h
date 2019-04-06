/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bug.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/06 17:55:06 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_BUG_H
# define LEM_IN_BUG_H

/*
**	Code couleur pour l'affichage des erreurs
*/
# define C_RED			"\e[41m"
# define C_NONE			"\033[0;0m"

/*
**	Messages d'erreurs
*/
# define UNKCOMM		"Command line not well formatted"
# define OUTDOMAIN		"Numerical argument out of domain"
# define NONNUM			"Non-numeric value encountered"
# define BADINPUT		"Invalid argument"
# define EMPTYLINE		"Empty line"

#endif
