#ifndef __PREPOSTOP_HPP__
#define	__PREPOSTOP_HPP__

/*	PrePostOp.hpp
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
 *
 *
 *		Permet de définir des opérations pré- et post-intégration (c'est-à-dire
 * des opérations exécutés juste avant l'appel de l'intégrateur ou exécutés
 * juste après l'appel de l'intégrateur).
 *
 */

#include "Integrators.hpp"
#include "SystemStates.hpp"

template<typename T>
class PrePostOp
{
	public:
		PrePostOp(void){};
		virtual ~PrePostOp(){};

		virtual void operator()(Integrator<T>& integrator, SystemStates<T>& states) = 0;
};

/*	NoOp	(No Operation)
 *
 * 		Définition d'une opération (pré- ou post-intégration) qui ne fait rien.
 * Elle ne sert que pour éviter de rajouter des conditions encadrants les appels
 * aux opérations pré- et post-intégration.
 */
template<typename T>
class NoOp: public PrePostOp<T>
{
	public:
		void operator()(Integrator<T>& integrator, SystemStates<T>& states);
};

template<typename T>
inline void NoOp<T>::operator()(Integrator<T>& integrator, SystemStates<T>& states)
{
	return;
}


#endif
