// Nestor Vallejos
// ne088412
// COP 3503, Spring 2019

import java.io.*;
import java.util.*;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;

class Node<T extends Comparable<T>>
{	
	private ArrayList<Node<T>> list;
	private int height;
	private T data;

	Node(int height)
	{	
		// initialize a node with the height passed in
		this.height = height;
		list = new ArrayList<Node<T>>(height);

		for (int i = 0; i < height; i++)
			this.list.add(null);
	}

	Node(T data, int height)
	{	
		// initialize a node with height and data fields
		this.height = height;
		this.data = data;
		list = new ArrayList<Node<T>>();

		for (int i = 0; i < height; i++)
			this.list.add(null);
	}

	public T value()
	{
		return this.data;
	}

	public int height()
	{
		return this.height;
	}

	// get what the next node is at a certain level
	public Node<T> next(int level)
	{	
		if (level < 0 || level > (this.height - 1))
			return null;

		return this.list.get(level);
	}

	// link a node with another at specified level 
	public void setNext(int level, Node<T> node)
	{	
		if (level > this.height)
			return;

		this.list.set(level, node);
	}

	// increase node by height of 1
	public void grow()
	{
		list.add(null);

		this.height++;
	}

	// with a 50% probability, grow a nodes height by 1
	public boolean maybeGrow()
	{
		if(Math.random() < 0.5)
		{
			grow();
			return true;
		}

		return false;
	}

	// trim a node down to specified height
	public void trim(int height)
	{
		for (int i = height; i < this.height; i++)
			this.list.set(i, null);

		this.height = height;
	}

}

public class SkipList<T extends Comparable<T>>
{
	private Node<T> head;
	private int size;
	private int height;

	SkipList()
	{	
		// makes a new empty (no nodes) skiplist with default height of 1
		this.size = 0;
		this.height = 1;
		this.head = new Node<T>(this.height);
	}

	SkipList(int height)
	{	
		// same as above skiplist but with head node being a specified height
		this.size = 0;
		this.height = height;
		this.head = new Node<T>(height);
	}

	public int size()
	{	
		return this.size;
	}

	public int height()
	{	
		return this.head.height();
	}

	public Node<T> head()
	{	
		return this.head;
	}

	// helper method to do insertion algorithim
	private void insert(Map<Integer, Node<T>> map, int height, Node<T> node)
	{
		int i = height - 1;

		while (i >= 0)
		{	
			// link node to what the previous nodes were pointing to
			node.setNext(i, map.get(i).next(i));
			// link the previous nodes up to the new node
			map.get(i).setNext(i, node);
			i--; 
		}
	}

	public void insert(T data)
	{	
		int level, randomHeight;
		Node<T> temp = this.head;
		Node<T> newNode;
		// hash map that keeps track of the levels and nodes associated with level
		Map<Integer, Node<T>> list = new HashMap<>();
		this.size++;

		// check if we need to grow the skiplist by checking how many nodes we have
		if (getMaxHeight(this.size) > this.height)
		{
			this.height = getMaxHeight(this.size);
			this.growSkipList();
		}

		level = this.height - 1;

		// traverses through skip list by levels till we find the place to insert
		while (temp != null && level >= 0)
		{	
			if (temp.next(level) == null || (temp.next(level).value()).compareTo(data) >= 0)
			{	
				// hash the node with the level it was in to keep track of previous nodes
				list.put(level, temp);
				level--;
			}

			// move forward in skiplist if next value is smaller than data we putting in
			else if ((temp.next(level).value()).compareTo(data) < 0)
				temp = temp.next(level);
		}

		// generate a random height to assign to new node
		randomHeight = generateRandomHeight(this.height);
		newNode = new Node<T>(data, randomHeight);

		// method to insert
		insert(list, randomHeight, newNode);
	}

	public void insert(T data, int height)
	{	
		int level, j;
		Node<T> temp = this.head;
		Node<T> newNode = new Node<T>(data, height);
		Map<Integer, Node<T>> list = new HashMap<>();

		if (height < 1)
			return;

		// check to see if we need to grow the skip list by checking number of nodes
		if (getMaxHeight(this.size) > this.height)
		{
			this.height = getMaxHeight(this.size);
			this.growSkipList();
		}

		level = this.height - 1;

		// for an empty list just simply link the head with the new node
		if (this.size == 0)
		{
			for (int i = height - 1; i >= 0; i--)
				this.head.setNext(i,newNode);

			this.size++;
			return;
		}

		this.size++;

		// traverse through skip list by going down its levels
		while (temp != null && level >= 0)
		{	
			if (temp.next(level) == null || (temp.next(level).value()).compareTo(data) >= 0)
			{	
				// hash the node with the level it was in in the list
				list.put(level, temp);
				level--;
			}

			// skip over a node if data is greater than nodes next value
			else if ((temp.next(level).value()).compareTo(data) < 0)
				temp = temp.next(level);
		}

		// method to insert
		insert(list, height, newNode);
	}

	public void delete(T data)
	{
		int level = this.height - 1;
		Node<T> temp = this.head;
		Map<Integer, Node<T>> list = new HashMap<>();

		// traverse through skip list until we are where at node to be deleted
		while (temp != null && level >= 0)
		{
			if (temp.next(level) == null || (temp.next(level).value()).compareTo(data) > 0)
				level--;
			else if ((temp.next(level).value()).compareTo(data) < 0)
				temp = temp.next(level);
			else
			{
				list.put(level, temp);
				level--;
			}
		}

		// move to node to be deleted
		temp = temp.next(level + 1);

		// check to see if we are at the node to be deleted
		if (temp != null && (temp.value()).compareTo(data) == 0)
		{	
			int i = temp.height() - 1;
			this.size--;

			while (i >= 0)
			{	
				// link the previous nodes to what the node being deleted was linked to
				list.get(i).setNext(i, temp.next(i));
				i--;
			}

			// after deleting check what our new height could be
			int newHeight = ((this.size <= 1) ? 1 : getMaxHeight(this.size));

			// trimp skip list down to what our new height should be
			if (newHeight < this.height)
			{
				this.height = newHeight;
				this.trimSkipList();
			}
		}

	}

	public boolean contains(T data)
	{
		Node<T> temp = this.head;
		int level = this.height - 1;

		// same algorithm to traverse down skip list until we reach our node
		while (temp != null && level >= 0)
		{
			if (temp.next(level) == null || ((temp.next(level).value()).compareTo(data) > 0))
				level--;
			else if ((temp.next(level).value()).compareTo(data) < 0)
				temp = temp.next(level);
			else
				// we found the node with data we were looking for
				return true;
		}

		return false;
	}

	public Node<T> get(T data)
	{
		Node<T> temp = this.head;
		int level = this.height - 1;

		// same algorithm to traverse down skip list until we are at our node
		while (temp != null && level >= 0)
		{
			if (temp.next(level) == null || ((temp.next(level).value()).compareTo(data) > 0))
				level--;
			else if ((temp.next(level).value()).compareTo(data) < 0)
				temp = temp.next(level);
			else
				// we found the node we were looking for
				return temp;
		}

		return null;
	}

	private static int getMaxHeight(int n)
	{	
		// the ceiling of log base 2 n with n nodes
		return (int)(Math.ceil((Math.log(n) / Math.log(2))));
	}

	private static int generateRandomHeight(int maxHeight)
	{	
		int height = 1;
		int i = 1;

		while (i < maxHeight)
		{
			boolean prob = (Math.random() < 0.5);

			// generate a height with 50% probability each time
			if(prob)
				break;
			else
				height++;

			i++;
		}

		return height;
	}

	public void growSkipList()
	{	
		Node<T> temp = this.head;
		Node<T> forward = temp;
		int level = this.height - 1;
		// grow the head regardless
		this.head.grow();

		while (temp.next(level) != null)
		{	
			forward = forward.next(level);

			// check to see if the node in front will grow
			if (forward.maybeGrow())
			{	
				// link the previous node to node in front at new height then move forward
				temp.setNext(this.height, forward);
				temp = forward;
			}

			// do nothing if it didnt grow
			else
				;
		}
	}

	private void trimSkipList()
	{
		trimSkipList(this.head);
	}

	// recursive method to traverse through whole skip list and trim as we go back
	private void trimSkipList(Node<T> temp)
	{
		if (temp == null)
			return;

		trimSkipList(temp.next(this.height - 1));
		temp.trim(this.height);
	}

	public static double difficultyRating()
	{
		return 5.0;
	}

	public static double hoursSpent()
	{
		return 50.0;
	}
}