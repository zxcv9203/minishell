/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:44:02 by yongckim          #+#    #+#             */
/*   Updated: 2021/05/08 20:46:19 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>


int main(int argc, char **argv, char **envp)
{
	// int i;

	// i = 0;
	// while(envp[i])
	// {
	// 	write(1, envp[i], strlen(envp[i]));
	// 	write(1, "\n", 1);
	// 	i++;
	// }
	write(1, envp[0], strlen(envp[0]));
}
