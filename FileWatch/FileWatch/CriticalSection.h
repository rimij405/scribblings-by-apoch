//
// FileWatch filesystem monitoring utility
// By Mike Lewis, June 2011
// http://scribblings-by-apoch.googlecode.com/
//
// Declaration of critical section wrapper for thread synchronization
//
// Appropriated from the Epoch Language Project
// http://epoch-language.googlecode.com/
//


#pragma once


namespace Threads
{

	//
	// Wrapper for a system critical section object.
	// Use the helper class for RAII semantics, to
	// ensure that the critical section is always
	// entered and exited correctly.
	//
	class CriticalSection
	{
	// Construction and destruction
	public:
		CriticalSection();
		~CriticalSection();

	// Entry and exit
	public:
		void Enter() const;
		void Exit() const;

	// RAII helper
	public:
		struct Auto
		{
			Auto(const CriticalSection& critsec)
				: BoundCritSec(critsec)
			{
				BoundCritSec.Enter();
			}

			~Auto()
			{
				BoundCritSec.Exit();
			}

		private:
			const CriticalSection& BoundCritSec;
		};

	// Internal tracking
	private:
		CRITICAL_SECTION CritSec;
	};

}

