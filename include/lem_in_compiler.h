/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_compiler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:04:23 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/06 17:55:06 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_COMPILER_H
# define LEM_IN_COMPILER_H

# define __hot_function		__attribute__((hot))
# define __pure_function	__attribute__((pure))
# define __unused			__attribute__((unused))

/*
**	Macros qui permettent au processeur de savoir à l'avance si une condition
**	a plus de chances d'être vraie ou non.
*/
# define likely(x)			__builtin_expect(!!(x), 1)
# define unlikely(x)		__builtin_expect(!!(x), 0)

#endif
