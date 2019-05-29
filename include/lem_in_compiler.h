/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_compiler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:05:06 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/27 17:44:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_COMPILER_H
# define LEM_IN_COMPILER_H

/*
**	These builtins instruct the compiler which branch of the program
**	is more likely to be executed.
*/
# define LIKELY(x)			__builtin_expect(!!(x), 1)
# define UNLIKELY(x)		__builtin_expect(!!(x), 0)

#endif
