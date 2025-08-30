/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map_parser_toolkit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:09:41 by mmalie            #+#    #+#             */
/*   Updated: 2025/08/25 20:01:48 by yel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libxkit.h"

int	check_chars(char **arr, int nb_lines, char *set)
{
	int	i;

	i = 0;
	while (i < nb_lines)
	{
		if (ft_strnopbrk(arr[i], set) != NULL)
		{
			perror("Error\n[check_chars] char not in set ❌\n");
			return (1);
		}
		i++;
	}
	ft_printf("✅ [check_chars] all chars valid\n");
	return (0);
}

/* For each index (matching counter index), 'required' expects: 
 * - if expected a precise value: a positive int (1 = only one)
 * - if expected a minimal value: a negative int (-1 = at least 1)
 * - 0 is considered positive (0 = not even one).
 * The counter array should be initialised to 0 beforehand.
 * [0]=empty | [1]=wall | [2]=C (coll) | [3]=E (exit) | [4]=P (start pos)
 * The first index is ignored at the number of empty does not matter.
 */
int	check_count(char **arr, int nb_lines, char *set, t_count_req *c)
{
	int	i;
	int	j;

	ft_init_two_ints(0, &i, &j);
	while (i < nb_lines)
	{
		count_chars(arr[i], set, c->count);
		i++;
	}
	j++;
	return (0);
}

/* Stores the number of occurrences of each char in set to the corresponding
 * index in counter (counter[0] = number of times set[0] appears, etc.).
 */
void	count_chars(char *str, char *set, int *counter)
{
	int	i;
	int	j;
	int	set_len;
	int	str_len;

	set_len = ft_strlen(set);
	str_len = ft_strlen(str) - 1;
	i = 0;
	while (i < str_len)
	{
		j = 0;
		while (j < set_len)
		{
			if (str[i] == set[j])
			{
				counter[j] = counter[j] + 1;
				break ;
			}
			j++;
		}
		i++;
	}
}
