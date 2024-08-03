/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:12:25 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 11:12:27 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

double	convert_to_radians(double angle_in_degrees)
{
	return (angle_in_degrees * (PI / 180.0));
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	print_goodbye_message(void)
{
	printf("\n*****************************\n");
	printf(" *                           *\n");
	printf("*   Thank you for playing!  *\n");
	printf(" *                           *\n");
	printf("*     See you again! =)     *\n");
	printf(" *                           *\n");
	printf("*****************************\n\n");
}
