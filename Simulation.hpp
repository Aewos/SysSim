#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

/*	Simulation.hpp
 *
 *		Définit les paramètres de simulation et l'exécute. Le système ainsi que
 * l'intégrateur son des objets externes qui dérivent respectivement de
 * DynamicalSystem et Integrator.
 */

/* TODO
 *	Faire gestion des erreurs. Il faut lancer des exceptions lorsque l'on essaye
 * de faire un "run" alors le système ou l'intégrateur n'ont pas été défini.
 */

#include <iostream>
#include <sstream>
#include <string>

#include "DynamicalSystem.hpp"
#include "Integrators.hpp"

template<typename T>
class Simulation
{
	protected:
		DynamicalSystem<T> *dynamicalsystem;
		Integrator<T> *integrator;

	public:
		Simulation(void);
		Simulation(DynamicalSystem<T> &dynamicalsystem);
		Simulation(Integrator<T> &integrator);
		Simulation(DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator);
		virtual ~Simulation(void){};

		inline DynamicalSystem<T> &getdynamicalsystem();
		inline Integrator<T> &getintegrator();
		inline void setdynamicalsystem(DynamicalSystem<T> &dynamicalsystem);
		inline void setintegrator(Integrator<T> &integrator);
		inline void unsetdynamicalsystem(void);
		inline void unsetintegrator(void);

		void run(std::ostream &ostream, T ti, T tf, T tisim);
		inline void run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, T tisim);
		inline void run(std::ostream &ostream, T ti, T tf, Integrator<T> &integrator, T tisim);
		inline void run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, T tisim);
	
		void run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints);
		inline void run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, unsigned long nbskipedpoints);
		inline void run(std::ostream &ostream, unsigned long nbpoitns, Integrator<T> &integrator, unsigned long nbskipedpoints);
		inline void run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, unsigned long nbskipedpoints);

};

template<typename T>
Simulation<T>::Simulation(void)
{
	this->unsetdynamicalsystem();
	this->unsetintegrator();
	return;
}

template<typename T>
Simulation<T>::Simulation(DynamicalSystem<T> &dynamicalsystem)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->unsetintegrator();
	return;
}

template<typename T>
Simulation<T>::Simulation(Integrator<T> &integrator)
{
	this->unsetdynamicalsystem();
	this->setintegrator(integrator);
	return;
}

template<typename T>
Simulation<T>::Simulation(DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	return;
}





template<typename T>
inline DynamicalSystem<T> &Simulation<T>::getdynamicalsystem()
{
	return this->*dynamicalsystem;
}

template<typename T>
inline Integrator<T> &Simulation<T>::getintegrator()
{
	return this->*integrator;
}

template<typename T>
inline void Simulation<T>::setdynamicalsystem(DynamicalSystem<T> &dynamicalsystem)
{
	this->dynamicalsystem = &dynamicalsystem;
	return;
}

template<typename T>
inline void Simulation<T>::setintegrator(Integrator<T> &integrator)
{
	this->integrator = &integrator;
	return;
}

template<typename T>
inline void Simulation<T>::unsetdynamicalsystem(void)
{
	this->dynamicalsystem = NULL;
	return;
}

template<typename T>
inline void Simulation<T>::unsetintegrator(void)
{
	this->integrator = NULL;
	return;
}





template<typename T>
void Simulation<T>::run(std::ostream &ostream, T ti, T tf, T tisim = (T)0.0)
{
	std::ostringstream oss;
	std::string aff;
	T t = tisim;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	while (t < ti)
	{
		(*this->integrator)(t, *this->dynamicalsystem);
	}

	while (t <= tf)
	{
		oss.precision(3);
		oss.width(6);
		oss << t;
		aff = oss.str();
		oss.str("");
		this->dynamicalsystem->toString(aff,3,7);
		ostream << aff << std::endl;

		(*this->integrator)(t, *this->dynamicalsystem);
	}

	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, T tisim = (T)0.0)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->run(ostream, ti, tf, tisim);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, T ti, T tf, Integrator<T> &integrator, T tisim = (T)0.0)
{
	this->setintegrator(integrator);
	this->run(ostream, ti, tf, tisim);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, T tisim = (T)0.0)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	this->run(ostream, ti, tf, tisim);
	return;
}





template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints = 0)
{
	std::ostringstream oss;
	std::string aff;
	T t = 0.0;
	unsigned long i;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	for(i = 0; i < nbskipedpoints; ++i)
	{
		(*this->integrator)(t, *this->dynamicalsystem);
	}

	for(i = 0; i < nbpoints; ++i)
	{
		oss.precision(3);
		oss.width(6);
		oss << t;
		aff = oss.str();
		oss.str("");
		this->dynamicalsystem->toString(aff,7,3);
		ostream << aff << std::endl;

		(*this->integrator)(t, *this->dynamicalsystem);
	}

	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, unsigned long nbskipedpoints = 0)
{
	this->setdynamicalsytem(dynamicalsystem);
	this->run(ostream, nbpoints, nbskipedpoints);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, Integrator<T> &integrator, unsigned long nbskipedpoints = 0)
{
	this->setintegrator(integrator);
	this->run(ostream, nbpoints, nbskipedpoints);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, unsigned long nbskipedpoints = 0)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	this->run(ostream, nbpoints, nbskipedpoints);
	return;
}







#endif

