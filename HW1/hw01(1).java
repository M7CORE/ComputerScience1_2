/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package cop3503c_hw1;

import java.io.*;
import java.util.Scanner;

public class Hw01 {

    public static BST searchTree;//Create an instance of BST.
    
    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args) throws Exception{
/*TESTING METHODS
        searchTree = new BST();
        
        searchTree.insert(searchTree.root, 99);
        searchTree.insert(searchTree.root, 10);
        searchTree.insert(searchTree.root, 9);
        searchTree.insert(searchTree.root, 4000);
        searchTree.insert(searchTree.root, 12);
        searchTree.delete(10);
        searchTree.print(searchTree.root);
        System.out.println("");
        int searchVal = 4000;
        if (searchTree.search(searchTree.root, searchVal) == null){
                System.out.printf("%d: NOT found\n", searchVal);
            }
        else
                System.out.printf("%d: found\n", searchVal);
        searchVal = 10;
        if (searchTree.search(searchTree.root, searchVal) == null){
                System.out.printf("%d: NOT found\n", searchVal);
            }
        else
                System.out.printf("%d: found\n", searchVal);
        
        searchTree.search(searchTree.root, 10);
        searchTree.print(searchTree.root);
        System.out.println("");
        searchTree.quit();
 *///TESTING METHOD END       
        
//REAL PROGRAM        
        searchTree = new BST();
        
       if (args.length > 0){
            File file = new File(args[0]);
            Scanner fileScnr = new Scanner(file);
            Scanner readScnr = new Scanner(file);
            
            //Read and print the file.
            if (readScnr.hasNext())
                System.out.println(args[0] + " contains:");   
            while (readScnr.hasNext()){
                System.out.println(readScnr.nextLine());
            }
           
            while (fileScnr.hasNext()){
                String option = fileScnr.next();
                if (option.equals("i")){
                    searchTree.insert(searchTree.root, fileScnr.nextInt());
                }
                else if (option.equals("d")){
                    searchTree.delete(searchTree.root, fileScnr.nextInt());
                }
                else if (option.equals("s")){
                    int searchVal = fileScnr.nextInt();
                    if (searchTree.search(searchTree.root, searchVal) == null){
                        System.out.printf("%d: NOT found\n", searchVal);
                    }
                    else
                        System.out.printf("%d: found\n", searchVal);
                }
                else if (option.equals("p")){
                    searchTree.print(searchTree.root);
                    System.out.println("");
                }
                else if (option.equals("q")){
                    searchTree.quit();
                }
                else {
                }
            }
        }
    }  


//    }
 }

    
class BST{
    
    Node root;
     
    //Constructor
    public BST(){
            
    }
    
    //Insert Method    
    public void insert(Node currNode, int inValue){
        
        if (currNode == null){
            Node tempNode = new Node(inValue);
//            currNode = tempNode;
            root = tempNode;
        }
        else{
            if (inValue >= currNode.getData()){
                if (currNode.rChild == null){
                    Node tempNode = new Node(inValue);
                    currNode.rChild = tempNode;
                    currNode.rChild.parent = currNode; 
                }
                else {
                   insert(currNode.getNextRight(), inValue); 
                }           
            }
            else{
                if (currNode.lChild == null){
                    Node tempNode = new Node(inValue);
                    currNode.lChild = tempNode;
                    currNode.lChild.parent = currNode; 
                }
                else {
                    insert(currNode.getNextLeft(), inValue);
                }
            } 
        }
    }
    
    
 /*   public Node delete(int delVal){
        Node newDelNode, saveNode, delNode;
        int saveData;
        
        delNode = search(root, delVal);
        
//        parent = findParentNode(delNode, root);
        
        //check if the node is a leaf.
        if (delNode != null){
            
            if (delNode.lChild == null && delNode.rChild == null){
     //           System.out.println("NODE IS A LEAF");
                if (delNode.parent == null){
                    return null;
                }

                else if (delNode.getData() < delNode.parent.getData()){
                    delNode.parent.lChild = null;
                }

                else{
                    delNode.parent.rChild = null;
                }

                return root;
            }

            else if(delNode.lChild != null && delNode.rChild == null){
    //            System.out.println("NODE HAS ONLY LEFT CHILD");
                if (delNode.parent == null){
                    saveNode = delNode.lChild;
                }

                else if (delNode.parent.getData() > delNode.getData()){
                    saveNode = delNode.parent.lChild;
                    delNode.parent.setNextLeft(delNode.parent.getNextLeft().getNextLeft());
                }

                else {
                    saveNode = delNode.parent.getNextRight();
                    delNode.parent.setNextRight(delNode.parent.getNextRight().getNextLeft());  
                }

                return saveNode;
            }

            else if(delNode.lChild == null && delNode.rChild != null){
     //           System.out.println("NODE HAS ONLY RIGHT CHILD");
                if (delNode.parent == null){
                    saveNode = delNode.getNextRight();
                }

                else if (delNode.parent.getData() > delNode.getData()){
                    saveNode = delNode.parent.getNextLeft();
                    delNode.parent.setNextLeft(delNode.parent.getNextLeft().getNextRight());
                }

                else {
                    saveNode = delNode.parent.getNextRight();
                    delNode.parent.rChild = delNode.parent.getNextRight().getNextRight();
                }

                return saveNode;   
            }
     //       System.out.println("NODE HAS 2 CHILDREN");

            //New delete node is equal to the max value to the left.
            newDelNode = maxVal(delNode.getNextLeft());
     //       System.out.println("NEW DEL NODE: " + newDelNode.getData());

            //Copy the data of the new delete node into saveData.
            saveData = newDelNode.getData();

            //Delete the new delete node.
            delete(newDelNode.getData());

            //Copy data from the delete node to the return node.
            delNode.setData(saveData);
    //        saveData = delNode.getData();

            return root;  
        }
        else
            return null;
    }*/
    
    public Node delete(Node node, int data){
        
        if (node == null)
            return node;
        
        else {
            Node delNode;
            delNode = search(node, data);
            
            if (delNode == null)
                return node;
            
            if (delNode.lChild == null)
                return delNode.rChild;
            else if (delNode.rChild == null)
                return delNode.lChild;
            
            delNode.data = minVal(delNode.rChild).data;
            
            delNode.rChild = delete(delNode.rChild, delNode.data);
        }
        
        return root;
    }
    
/*    public Node findParentNode(Node currNode, Node mainNode){
        
        if (currNode == null || currNode == mainNode)
            return null;
        else if (mainNode.getNextLeft() == currNode || mainNode.getNextRight() == currNode)
            return mainNode;
        else if (mainNode.getData() > currNode.getData())
            return findParentNode(currNode, mainNode.getNextLeft());
        else if (mainNode.getData() < currNode.getData())
            return findParentNode(currNode, mainNode.getNextRight());
        return null;
    }*/
    
    public Node minVal(Node currNode){
        if (currNode.getNextLeft() == null)
            return currNode;
        else
            return minVal(currNode.getNextLeft());
    }
    
/*    public Node search(Node currNode, int findVal){
        
        if (currNode == null ||currNode.getData() == findVal)
            return currNode;
        else if (findVal > currNode.getData())
            return search(currNode.getNextRight(), findVal);
        else 
            return search(currNode.getNextLeft(), findVal);
    }*/
    
    public Node search (Node currNode, int findVal){
        
        while(currNode != null){
            
            if (findVal < currNode.data)
                currNode = currNode.lChild;
            else if (findVal > currNode.data)
                currNode = currNode.lChild;
            else
                return currNode;
        }
        
        return null;
    }
    
    public void print(Node currNode){
        
        if(currNode != null){
            print(currNode.lChild);
            System.out.print(" " + currNode.getData());
            print(currNode.rChild);
        }
    }
    
    public void quit(){
        
        //Initialize ending sequence
        System.out.printf("left children:%11d\n", countChildren(root.getNextLeft()));
        System.out.printf("left depth:%14d\n", getDepth(root.getNextLeft()));
        System.out.printf("right children:%10d\n", countChildren(root.getNextRight()));
        System.out.printf("right depth:%13d\n", getDepth(root.getNextRight()));
        complexityIndicator();
        System.exit(0);
        
    }
    
    public void complexityIndicator(){
        System.err.println("ma915739;3;8\n");
    }
    
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
    
    public int countChildren(Node currNode){
        
        if (currNode != null)
            return 1 + countChildren(currNode.getNextLeft()) + countChildren(currNode.getNextRight());
        else
            return 0;
        
    }
}

    
class Node {
    
    Node lChild;
    Node rChild;
    Node parent;
    int data;

    // Node constructor
    public Node(int dataValue) {
        lChild = null;
        rChild = null;
        parent = null;
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
   
