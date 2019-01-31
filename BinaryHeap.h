#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

//#include "dsexceptions.h"
#include "QuadraticProbing.h"
#include <vector>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted



template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 )
      : array( capacity + 1 ), currentSize( 0 )
    {
    	table = quadratic::HashTable<int>();
    }

    explicit BinaryHeap( const vector<Comparable> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
    	table = quadratic::HashTable<int>();
        for( int i = 0; i < items.size( ); i++ )
        {

            array[ i + 1 ] = items[ i ];
            table.insert(array[i+1].id, i+1);
        }
        buildHeap( );
    }

    bool isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const Comparable & findMin( )
    {
        if( isEmpty( ) )
            return NULL;

        return array[ 1 ];
    }
    /**
     * Insert item x, allowing duplicates.
     */
    void insert(  Comparable & x )
    {
        if( currentSize == array.size( ) - 1 )
            array.resize( array.size( ) * 2 );

            // Percolate up
        int hole = ++currentSize;
        for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
        {
            array[ hole ] = array[ hole / 2 ];
            table.insert( array[hole].id, hole );
        }
        array[ hole ] = x;
        table.insert (x.id, hole);

        //cout << "new item at " << table.indexOf(x) << ";\n";
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) )
            return;

        array[ 1 ] = array[ currentSize-- ];
        table.insert (array[1].id, 1);
        percolateDown( 1 );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            return;

        minItem = array[ 1 ];
        table.remove(array[1].id);
        array[ 1 ] = array[ currentSize-- ];
        table.insert (array[1].id, 1);
        percolateDown( 1 );
    }

    void makeEmpty( )
      { currentSize = 0; table.makeEmpty(); }

    bool increaseKey(int id, double delta)
    {
    	int index = table.indexOf(id);

    	if (array[index].dist >= delta)
    		return false;

		array[index].dist = delta;
		percolateDown(index);
		return true;
    }

    bool decreaseKey(int id, double delta)
    {

    	int index = table.indexOf(id);

		if (array[index].dist <= delta)
			return false;
		cout << "index: " << index << " " << table.indexOf(1) << " " << table.indexOf(2) << endl;
		array[index].dist = delta;
    	percolateUp(index);
    	return true;
    }

    bool remove(Comparable &key)
    {
    	int index = table.indexOf(key);

    	if( isEmpty( ) || !table.contains(key))
			return false;

    	//treat remove as a deleteMin on the subtree with [key] as root
    	table.remove(array[index].id);
		array[ index ] = array[ currentSize-- ];
		table.insert (array[index].id, index);
		percolateDown( index );
		return true;
    }

    Comparable& itemat(int id)
    {
    	return array[table.indexOf(id)];
    }


  private:
    int                currentSize;  // Number of elements in heap
    vector<Comparable> array;        // The heap array
    quadratic::HashTable<int> table;

    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
            percolateDown( i );
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = array[ hole ];

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
                child++;
            if( array[ child ] < tmp )
            {
                array[ hole ] = array[ child ];
                table.insert( array[hole].id, hole );
            }
            else
                break;
        }
        array[ hole ] = tmp;
        table.insert( array[hole].id, hole );
    }

    void percolateUp( int hole )
	{
		Comparable x = array[ hole ];

		// Percolate up
		for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
		{
			array[ hole ] = array[ hole / 2 ];
			table.insert( array[hole].id, hole );
		}
		array[ hole ] = x;
		table.insert (x.id, hole);
	}
};

#endif
