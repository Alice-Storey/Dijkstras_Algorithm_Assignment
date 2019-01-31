#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace quadratic
{

	int nextPrime( int n );

	// QuadraticProbing Hash table class
	//
	// CONSTRUCTION: an approximate initial size or default of 101
	//
	// ******************PUBLIC OPERATIONS*********************
	// bool insert( x )       --> Insert x
	// bool remove( x )       --> Remove x
	// bool contains( x )     --> Return true if x is present
	// void makeEmpty( )      --> Remove all items
	// int hash( string str ) --> Global method to hash strings

	template <typename HashedObj>
	class HashTable
	{
	  public:
		explicit HashTable( int size = 1009, bool canrehash= true ) : array( nextPrime( size ) )
		  {
			makeEmpty( );
			rehashAllowed = canrehash;
			resetProbeCount();
		  }

		void resetProbeCount()
		{
			probeCount[S][OPERATIONS] = 0;
			probeCount[S][PROBES] = 0;
			probeCount[UI][OPERATIONS] = 0;
			probeCount[UI][PROBES] = 0;
		}

		bool contains( const HashedObj & x )
		{
			int probes = 0;
			bool active = isActive( findPos( x, probes ) );
			if (active)
			{
				probeCount[S][OPERATIONS] ++;
				probeCount[S][PROBES] += probes;
			}
			else
			{
				probeCount[UI][OPERATIONS] ++;
				probeCount[UI][PROBES] += probes;
			}

			return active;
		}

		void makeEmpty( )
		{
			currentSize = 0;
			for( unsigned int i = 0; i < array.size( ); i++ )
				array[ i ].info = EMPTY;
		}

		bool insert( const HashedObj & x, int index )
		{
				// Insert x as active
			int probes = 0;
			int currentPos = findPos( x, probes );
			probeCount[UI][OPERATIONS] ++;
			probeCount[UI][PROBES] += probes;
			if( isActive( currentPos ) )
			{
				array[ currentPos ].index = index;
				return false;
			}

			array[ currentPos ] = HashEntry( x, ACTIVE );
			array[ currentPos ].index = index;
			currentSize++;

				// Rehash; see Section 5.5
			if( rehashAllowed && ++currentSize > array.size( ) / 2 )
				rehash( );

			return true;
		}

		bool remove( const HashedObj  x )
		{
			int probes = 0;
			int currentPos = findPos( x, probes );
			if( !isActive( currentPos ) )
				return false;

			array[ currentPos ].info = DELETED;
			return true;
		}

		double getLoadFactor()
		{
			return double(currentSize) / double( array.size() );
		}

		double getAvgProbes(int operation)
		{
			return double( probeCount[operation][PROBES]  ) / probeCount[operation][OPERATIONS];
		}

		int indexOf (HashedObj  key)
		{
			int probes;
			int pos = findPos (key, probes);
			if (isActive(pos))
				return array[pos].index;
			else
				return -1;

		}


		enum EntryType { ACTIVE, EMPTY, DELETED };
		enum Operations { S, UI };
		enum WhichData { OPERATIONS, PROBES } ;

	  private:
		struct HashEntry
		{
			HashedObj element;
			EntryType info;
			int index;

			HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
			  : element( e ), info( i ) { }
		};

		vector<HashEntry> array;
		int currentSize;
		int probeCount[2][2];
		bool rehashAllowed;

		bool isActive( int currentPos ) const
		  { return array[ currentPos ].info == ACTIVE; }

		int findPos( const HashedObj & x, int & probes )
		{
			int offset = 1;
			int currentPos = myhash( x );

			while( array[ currentPos ].info != EMPTY &&
					array[ currentPos ].element != x )
			{
				currentPos += offset;  // Compute ith probe
				offset += 2;
				probes++;
				if( currentPos >= array.size( ) )
					currentPos -= array.size( );
			}

			return currentPos;
		}

		void rehash( )
		{
			vector<HashEntry> oldArray = array;

				// Create new double-sized, empty table
			array.resize( nextPrime( 2 * oldArray.size( ) ) );
			for( int j = 0; j < array.size( ); j++ )
				array[ j ].info = EMPTY;

				// Copy table over
			currentSize = 0;
			for( int i = 0; i < oldArray.size( ); i++ )
				if( oldArray[ i ].info == ACTIVE )
					insert( oldArray[ i ].element, oldArray[i].index );
		}
		int myhash( const HashedObj & x ) const
		{
			int hashVal = hash( x );

			hashVal %= array.size( );
			if( hashVal < 0 )
				hashVal += array.size( );

			return hashVal;
		}
	};

	int hash( const string & key );
	int hash( int key );
	bool isPrime( int n );
	int nextPrime( int n );

}

#endif
