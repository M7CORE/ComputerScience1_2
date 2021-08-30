 import java.util.ArrayList;

import java.util.List;

import java.io.BufferedReader;

import java.io.File;

import java.io.FileReader;

import java.io.IOException;
import java.util.Random;

 
 public class Hw02{


public static void main(String[] args) throws IOException {

      try {


            File f = new File(args[0]); //gets .txt files


            BufferedReader b = new BufferedReader(new FileReader(f));


            String readLine = "";

          SkipList list = new SkipList();
          
          System.out.println("For the input file named " + args[0]);
          
          System.out.println("With the RNG unseeded,");
          
          System.out.println("the current Skip List is shown below: ");
         

            while ((readLine = b.readLine()).charAt(0) != 'q')

            {


                if (readLine.charAt(0) == 'i')

                {

                  String[] arrOfStr = readLine.split(" ", 2);

                  int result = Integer.parseInt(arrOfStr[1]);

			if(list.searchNode(result)!= true)

                  {

                    list.insert(result);

                  }


                }

                if (readLine.charAt(0) == 'd')

                {

                  String[] arrOfStr = readLine.split(" ", 2);

                  int result = Integer.parseInt(arrOfStr[1]);

                  if(list.searchNode(result)== true)

                  {

                    list.delete(result);

                    System.out.println(result + “ deleted”);

                  }

                  else

                  {

                    System.out.println(result+ " integer not found - delete not successful”);

                  }

                }

                if (readLine.charAt(0) == 's')

                {

                   String[] arrOfStr = readLine.split(" ", 2);

                  int result = Integer.parseInt(arrOfStr[1]);

                  if(list.searchNode(result)== true)

                  {

                    System.out.println(result+ " found”);

                  }

                  else

                  {

                    System.out.println(result+ " NOT FOUND");

                  }

                }

                if (readLine.charAt(0) == 'p')

{

                  list.print();     

                }

            }

            

            complexityIndicator();

            

        } catch (IOException e) {

            e.printStackTrace();

        }

}

  public static void complexityIndicator() {

        System.err.println("ga358104;4;17”);

    }

 }
  
class SkipList {
/*

* These are starting pointers. They are always from top layer.

*/

 Node negativeInf;

 Node positiveInf;
 
 Random rand;


public SkipList() {


negativeInf = new Node(Integer.MIN_VALUE);

positiveInf = new Node(Integer.MAX_VALUE);

rand = new Random(42);

negativeInf.setRight(positiveInf);

positiveInf.setLeft(negativeInf);

}


public Node search(int value) {

Node cur = negativeInf;


while (cur != null) {

while (cur.right != null && cur.right.value <= value ) {

cur = cur.right;

}


if (cur.value == value) {

break;

}


cur = cur.down;

}


return cur;

}


  public boolean searchNode (int value) {

Node cur = negativeInf;


while (cur != null) {

while (cur.right != null && cur.right.value <= value ) {

cur = cur.right;

}


if (cur.value == value) {

return true;

}


cur = cur.down;

}


return false;

}

public boolean insert(int value) {


Node cur = negativeInf;


List<Node> pointersToUpdate = new ArrayList<Node>();


while (cur != null) {

while (cur.right != null && cur.right.value < value ) {

cur = cur.right;

}


pointersToUpdate.add(cur);

cur = cur.down;

}


// insert after this node.

int level = 0;

Node newNode = null;


while (level == 0 || flipCoin()) {


// now move up.

if (newNode == null) {

newNode = new Node(value);

} else {

newNode = new Node(newNode);
newNode.down.up = newNode;
}


Node nodeToUpdate = null;


if (pointersToUpdate.size() <= level) {

createNewLayer();

nodeToUpdate = this.negativeInf;

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


public boolean delete(int value) {


Node cur = this.negativeInf;


List<Node> pointersToUpdate = new ArrayList<Node>();


while (cur != null) {

while (cur.right != null && cur.right.value < value ) {

cur = cur.right;

}


if (cur.right.value == value) {

pointersToUpdate.add(cur);

}


cur = cur.down;

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


public void createNewLayer() {


Node negativeInf = new Node(Integer.MIN_VALUE);

Node positiveInf = new Node(Integer.MAX_VALUE);


negativeInf.setRight(positiveInf);

positiveInf.setLeft(negativeInf);


this.negativeInf.up = negativeInf;

negativeInf.down = this.negativeInf;

this.negativeInf = negativeInf;


this.positiveInf.up = positiveInf;

positiveInf.down = this.positiveInf;

this.positiveInf = positiveInf;

}


public boolean flipCoin() {

    if (rand.nextInt() % 2 == 1)
            return true;
return false;

}


public void print() {


Node cur = this.negativeInf;

    System.out.print("---infinity");

while(cur.down != null) {

cur = cur.down;

}


cur = cur.right;


while (cur.right != null) {
    
    System.out.println();

System.out.print(" " +cur.value + "; ");

    while (cur.up != null) {
        
        cur = cur.up;
        
        System.out.print(" " + cur.value + "; ");
        
    }
    
    while (cur.down != null) {
    
        cur = cur.down;
        
    }

cur = cur.right;

}

    System.out.println("\n+++infinity");
    
    System.out.println("---End of Skip List---");
}


public void printAllLevel() {


Node cur = this.negativeInf;


while(cur != null) {


Node firstInLevel = cur;

firstInLevel = firstInLevel.right;


while (firstInLevel.right != null) {

System.out.print(firstInLevel.value + " ");

firstInLevel = firstInLevel.right;

}


cur = cur.down;

System.out.println();

}

}


    }

class Node {

public int value;

public Node left;

public Node right;

public Node up;

public Node down;


public Node(int value) {

this.value = value;


this.left = null;

this.right = null;

this.up = null;

this.down = null;

}


public Node(Node lowerLevelNode) {

this.value = lowerLevelNode.value;


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



