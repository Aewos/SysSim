#ifndef __ROSSLERCONNECTION_HPP__
#define __ROSSLERCONNECTION_HPP__

/* 	RosslerConnection.hpp
 *
 * Copyright Adrien KERFOURN (2014)
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 *
 */

#include "Connection.hpp"

template<typename T>
class RosslerConnection: public Connection<T>
{

	private:
		Network<T> *network;
		long i,j;
		T K;

	public:
		RosslerConnection(Network<T>& network, long i, long j, T gain);
		virtual ~RosslerConnection(void){};

		T operator()(void);
};

template<typename T>
RosslerConnection<T>::RosslerConnection(Network<T>& network, long i, long j, T gain)
{
	this->network = &network;
	this->i = i;
	this->j = j;
	this->K = gain;
	return;
}

template<typename T>
T RosslerConnection<T>::operator()(void)
{
	return K*( this->network->x(this->i) - this->network->x(this->j) );
}

#endif

