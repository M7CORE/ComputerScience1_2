/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package hw02chegg;

/**
 *
 * @author moisessrodriguez
 */
import java.io.BufferedReader;

import java.io.FileNotFoundException;

import java.io.FileReader;

import java.io.IOException;

import java.util.ArrayList;

import java.util.List;

public class SkipList {

/*

* These are starting pointers. They are always from top layer.

*/

private Node negativeInfinity;

private Node positiveInfinity;

public SkipList() {

negativeInfinity = new Node(Integer.MIN_VALUE);

positiveInfinity = new Node(Integer.MAX_VALUE);

negativeInfinity.setRight(positiveInfinity);

positiveInfinity.setLeft(negativeInfinity);

}

public Node search(int data) {

Node current = negativeInfinity;

while (current != null) {

while (current.right != null && current.right.data <= data) {

current = current.right;

}

if (current.data == data) {

break;

}

current = current.down;

}

return current;

}

public boolean insert(int data) {

Node current = negativeInfinity;

List<Node> pointersToUpdate = new ArrayList<Node>();

while (current != null) {

while (current.right != null && current.right.data < data) {

current = current.right;

}

pointersToUpdate.add(current);

current = current.down;

}

// insert after this node.

int level = 0;

Node newNode = null;

while (level == 0 || flipCoin()) {

// now move up.

if (newNode == null) {

newNode = new Node(data);

} else {

newNode = new Node(newNode);

}

Node nodeToUpdate = null;

if (pointersToUpdate.size() <= level) {

createNewLayer();

nodeToUpdate = this.negativeInfinity;

} else {

nodeToUpdate = pointersToUpdate.get(pointersToUpdate.size() - level - 1);

}

newNode.right = nodeToUpdate.right;

newNode.left = nodeToUpdate;

newNode.right.left = newNode;

nodeToUpdate.right = newNode;

level++;

}

return true;

}

public boolean delete(int data) {

Node current = this.negativeInfinity;

List<Node> pointersToUpdate = new ArrayList<Node>();

while (current != null) {

while (current.right != null && current.right.data < data) {

current = current.right;

}

if (current.right.data == data) {

pointersToUpdate.add(current);

}

current = current.down;

}

for (int i = 0; i < pointersToUpdate.size(); i++) {

Node nodeToUpdate = pointersToUpdate.get(i);

Node nodeToDelete = nodeToUpdate.right;

nodeToUpdate.right = nodeToDelete.right;

nodeToDelete.right.left = nodeToUpdate;

nodeToDelete.up = null;

nodeToDelete.down = null;

}

return true;

}

private void createNewLayer() {

Node negativeInfinity = new Node(Integer.MIN_VALUE);

Node positiveInfinity = new Node(Integer.MAX_VALUE);

negativeInfinity.setRight(positiveInfinity);

positiveInfinity.setLeft(negativeInfinity);

this.negativeInfinity.up = negativeInfinity;

negativeInfinity.down = this.negativeInfinity;

this.negativeInfinity = negativeInfinity;

this.positiveInfinity.up = positiveInfinity;

positiveInfinity.down = this.positiveInfinity;

this.positiveInfinity = positiveInfinity;

}

private boolean flipCoin() {

return Math.random() >= 0.5;

}

public void print() {

Node current = this.negativeInfinity;

while (current.down != null) {

current = current.down;

}

current = current.right;

while (current.right != null) {

System.out.print(current.data + " ");

current = current.right;

}

System.out.println();

}

public void printAll() {

Node current = this.negativeInfinity;

while (current != null) {

Node firstInLevel = current;

firstInLevel = firstInLevel.right;

while (firstInLevel.right != null) {

System.out.print(firstInLevel.data + " ");

firstInLevel = firstInLevel.right;

}

current = current.down;

System.out.println();

}

}

public static void main(String[] args) {

SkipList list = new SkipList();

boolean result = false;

try {

BufferedReader br;

br = new BufferedReader(new FileReader(args[0]));

StringBuilder sb = new StringBuilder();

String line = br.readLine();

while (line != null) {

sb.append(line);

sb.append(System.lineSeparator());

line = br.readLine();

}

String everything = sb.toString();

String[] input = everything.split(",");

for (int i = 0; i < input.length; i++) {

String temp = input[i];

if (temp.startsWith("i")) {

result = list.insert(Integer.parseInt(temp.substring(2)));

} else if (temp.startsWith("s")) {

Node node = list.search(Integer.parseInt(temp.substring(2)));

if (node != null) {

System.out.println(temp.substring(2) + " found");

} else {

System.out.println(temp.substring(2) + " not found");

}

} else if (temp.startsWith("d")) {

result = list.delete(Integer.parseInt(temp.substring(2)));

if (result == true) {

System.out.println(temp.substring(2) + " deleted");

} else {

System.out.println(temp.substring(2) + " not deleted");

}

} else if (temp == "p") {

System.out.println("For the input file ");

System.out.println("With the RNG succeeded");

System.out.println("The current skip list is shown below");

list.printAll();

}

}

} catch (Exception e) {

// TODO Auto-generated catch block

e.printStackTrace();

}

}

public static class Node {

private int data;

private Node left;

private Node right;

private Node up;

private Node down;

public Node(int data) {

this.data = data;

this.left = null;

this.right = null;

this.up = null;

this.down = null;

}

public Node(Node lowerLevelNode) {

this.data = lowerLevelNode.data;

this.left = null;

this.right = null;

this.up = null;

this.down = lowerLevelNode;

}

public Node getLeft() {

return left;

}

public void setLeft(Node left) {

this.left = left;

}

public Node getRight() {

return right;

}

public void setRight(Node right) {

this.right = right;

}

public Node getUp() {

return up;

}

public void setUp(Node up) {

this.up = up;

}

public Node getDown() {

return down;

}

public void setDown(Node down) {

this.down = down;

}

}

}

