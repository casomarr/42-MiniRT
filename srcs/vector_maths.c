/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:03:57 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/14 15:55:04 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Function to subtract two vectors
t_vec	vecSubstract(t_vec a, t_vec b) {
    t_vec result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

// Function to add two vectors
t_vec   vecAdd(t_vec a, t_vec b) {
    t_vec result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

// Function to multiply two vectors
t_vec   vecProduct(t_vec a, t_vec b) {
    t_vec result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

/*Pour eviter des operations intermediaires je pourrai
convertir toutes ces fonctions en fonctions variadiques
pour pouvoir par exemple multiplier plus de seulement 2
vecteurs a la fois. */