/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_attenuation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:32:15 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/09 20:33:28 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	attenuate_color(t_vec color, float dist_light)
{
	float	attenuation;

	attenuation = 1.0 / (C_ATTENUATION + L_ATTENUATION * dist_light \
	+ Q_ATTENUATION * powf(dist_light, 2));
	color = vec_multiply_float(color, attenuation);
	return (color);
}
