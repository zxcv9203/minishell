/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:40:24 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/08 17:13:10 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(void)
{
	char *a;

	a = "aa";
	//write(1, "aaaa"a,6); 안됨
}
