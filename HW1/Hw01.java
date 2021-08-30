import java.io.*;
import java.util.Scanner;

public class Hw01 {

    public static BST searchTree;//Create an instance of BST.
   
    public static void main(String[] args) throws Exception{

        //Instantiate a BST.
        searchTree = new BST();
        
       if (args.length > 0){
           //Open the file passed as the first argument.
            File file = new File(args[0]);
            //Open 2 scanners. One to print the input.
            //Another to execute commands.
            Scanner fileScnr = new Scanner(file);
            Scanner readScnr = new Scanner(file);
            
            //Read and print the file using the first scanner.
            if (readScnr.hasNext())
                System.out.println(args[0] + " contains:");   
            while (readScnr.hasNext()){
                System.out.println(readScnr.nextLine());
            }
           
            //Start reading the file and executing commands.
            while (fileScnr.hasNext()){//Loops until there is nothing to read.
                String option = fileScnr.next();
                if (option.equals("i")){// Insert command.
                    searchTree.insert(searchTree.root, fileScnr.nextInt());
                }
                else if (option.equals("d")){//Delete command.
                    searchTree.delete(fileScnr.nextInt());
                }
                else if (option.equals("s")){//Search command.
                    int searchVal = fileScnr.nextInt();
                    //If the data wasn't found.
                    if (searchTree.search(searchTree.root, searchVal) == null){
                        System.out.printf("%d: NOT found\n", searchVal);
                    }
                    else//If the number was found.
                        System.out.printf("%d: found\n", searchVal);
                }
                else if (option.equals("p")){//Print option. Prints inorder.
                    searchTree.print(searchTree.root);
                    System.out.println("");
                }
                else if (option.equals("q")){//Quit option. Prints depth.
                    searchTree.quit();
                }
                else {
                }
            }
        }
    }  

 }

//Class for BST structure and methods.    
class BST{
    
    Node root;
     
    //Constructor
    public BST(){
            
    }
    
    //Insert Method    
    public void insert(Node currNode, int inValue){
        
        //If the root is null. Make it the root.
        if (root == null){
            Node tempNode = new Node(inValue);
            currNode = tempNode;
            root = currNode;
        }
        
        //If there is a root.
        else{
            //If the insert value is greater, traverse to the right.
            if (inValue >= currNode.getData()){
                //If the right child is null, insert there.
                if (currNode.rChild == null){
                    Node tempNode = new Node(inValue);
                    currNode.rChild = tempNode;
                }
                //If the right child isnt null, continue down to the right.
                else {
                   insert(currNode.getNextRight(), inValue); 
                }           
            }
            else{//If the insert value is smaller, traverse to the left. 
                //If the left child is null, insert there.
                if (currNode.lChild == null){
                    Node tempNode = new Node(inValue);
                    currNode.lChild = tempNode;

                }
                //If its not null, keep traversing to the left.
                else {
                    insert(currNode.getNextLeft(), inValue);
                }
            } 
        }
    }
    
    //calls deleteNode passing the root and data as parameters.
    public void delete (int data){
        deleteNode(root, data);
    }
    
    //Main delete function.
    public Node deleteNode(Node root, int data){
        
        //If the tree is empty
        if (root == null)
            return root;
        
        //Recur down the tree until finding the key
        if (data < root.data)
            root.lChild = deleteNode(root.lChild, data);
        else if (data > root.data)
            root.rChild = deleteNode(root.rChild, data);
        
        //Once the key is found
        else{
            
            //If the node is a leaf.
            if (root.lChild == null && root.rChild == null){
                return null;
            }
            
            //If the node only has a right child.
            else if (root.lChild == null)
                return root.rChild;
            
            //If the node only has a left child.
            else if (root.rChild == null)
                return root.lChild;
            
            //If the node has two children.
            else {
                //Find the minimum value on the right subtree of the node.
                int min = minVal(root.rChild).data;
                //Set the node to the minumum data which would replace it.
                root.data = min;
                //Delete the node with the min data to the right of the subtree.
                root.rChild = deleteNode(root.rChild, min);
            }
        }
        return root;
    }
        
    
    //Method to find the minimum value of a subtree.
    public Node minVal(Node currNode){
        if (currNode.getNextLeft() == null)
            return currNode;
        else
            return minVal(currNode.getNextLeft());
    }
    
    //Search method. Iterative.
    public Node search (Node currNode, int findVal){
        
        while(currNode != null){
            
            if (findVal < currNode.data)
                currNode = currNode.lChild;
            else if (findVal > currNode.data)
                currNode = currNode.rChild;
            else
                return currNode;
        }
        
        return null;
    }
    
    //Print method. Prints inorder.
    public void print(Node currNode){
        
        if(currNode != null){
            print(currNode.lChild);
            System.out.print(" " + currNode.getData());
            print(currNode.rChild);
        }
    }
    
    //Quit method. Prints depth, children, and compleity indicator.
    public void quit(){
        
        //Initialize ending sequence
        System.out.printf("left children:%11d\n", countChildren(root.getNextLeft()));
        System.out.printf("left depth:%14d\n", getDepth(root.getNextLeft()));
        System.out.printf("right children:%10d\n", countChildren(root.getNextRight()));
        System.out.printf("right depth:%13d\n", getDepth(root.getNextRight()));
        complexityIndicator();
        System.exit(0);
        
    }
    
    //Complexity Indicator with nid, difficulty and hours spent.
    public void complexityIndicator(){
        System.err.println("ma915739;3.5;12");
    }
    
    //Gets depth of a subtree.
    public int getDepth(Node currNode){
        
        int left, right;
        
        if (currNode == null)
            return 0;
        else {
            left = getDepth(currNode.lChild);
            right = getDepth(currNode.rChild);

            if (left > right)
                return left + 1;
            else 
                return right + 1;
        }
      
    }
    
    //Counts all children in a subtree.
    public int countChildren(Node currNode){
        
        if (currNode != null)
            return 1 + countChildren(currNode.getNextLeft()) + countChildren(currNode.getNextRight());
        else
            return 0;
        
    }
}

//Class for a node structure.    
class Node {
    
    Node lChild;
    Node rChild;
    int data;

    // Node constructor
    public Node(int dataValue) {
        lChild = null;
        rChild = null;
        data = dataValue;
    }

    // these methods should be self-explanatory
    public int getData() {
        return data;
    }

    @SuppressWarnings("unused")
    public void setData(int dataValue) {
        data = dataValue;
    }

    public Node getNextLeft() {
        return lChild;
    }
    
    public Node getNextRight(){
        return rChild;
    }

    public void setNextRight(Node nextValue) {
        rChild = nextValue;
    }
    
    public void setNextLeft(Node nextValue){
        lChild = nextValue;
    }

}
   

