/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_imges_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:46:14 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/25 23:00:15 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"



t_delete *create_node(void *adrress, t_status status)
{
    t_delete *node;

    node = malloc(sizeof(t_delete));
    if (!node)
        return (NULL);
    node->adrress = adrress;
    node->status = status;
    node->next = NULL;
    return (node);
}

void addback(t_delete **head, t_delete *new)
{
    t_delete *tmp;

    if (!*head)
    {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void save_imgs_texs(t_data *data, void *adrress, t_status status)
{
    static t_delete *head;
    t_delete *new;

    new = create_node(adrress, status);
    if (!new)
        return;
    if (status == TEXTURE || status == IMAGE)
        addback(&head, new);
    else
    {
        while (head)
        {
            if (head->status == TEXTURE)
                mlx_delete_texture((mlx_texture_t *)head->adrress);
            else if (head->status == IMAGE)
                mlx_delete_image(data->mlx,(mlx_image_t *) head->adrress);
            head = head->next;
        }
        head = NULL;
    }
}
