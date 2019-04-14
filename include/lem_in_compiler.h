/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_compiler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:05:06 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/14 17:41:11 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_COMPILER_H
# define LEM_IN_COMPILER_H

# define __UNUSED			__attribute__((unused))

/*
**	Macros qui permettent au processeur de savoir à l'avance si une condition
**	a plus de chances d'être vraie ou non.
*/
# define LIKELY(x)			__builtin_expect(!!(x), 1)
# define UNLIKELY(x)		__builtin_expect(!!(x), 0)

#endif
