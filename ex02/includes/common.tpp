/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:23:02 by ple-stra          #+#    #+#             */
/*   Updated: 2024/03/03 15:23:33 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template<typename Container>
bool is_sorted(Container const &container)
{
	Container newContainer(container);

	sort(newContainer.begin(), newContainer.end());
	return container == newContainer;
}
