/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 21:36:16 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/08 21:36:58 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(void)
{
	write(1, "a", 1);
	write(1, "a", 1);
	write(1, "a", 1);
	write(1, "a", 1);
	write(1, "a", 1);
	write(1, "aaaaa", 5);
}
