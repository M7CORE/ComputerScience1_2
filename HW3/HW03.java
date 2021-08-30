/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package hw03;
import java.util.Scanner;
import java.io.*; 
/**
 *
 * @author moisessrodriguez
 */
public class Hw03 
{

    /**
     * @param args the command line arguments
     */
    public static int hash(String input, int len)
    {
        int randVal1 = 0XBCDE98EF;  // <- 0XBCDE98EF arbitrary value
        int randVal2 = 0X7890FACE;  // <- 0X7890FACE
        int hashVal  = 0XFA01BC96;   // <- 0XFA01BC96 start seed value
        int roundedEnd = len & 0XFFFFFFFC;  // <- len & 0XFFFFFFFC Array d gets 4 bye blocks  
        int tempData = 0;
        // instead of i++ it should be i+4
        for(int i =0; i < roundedEnd; i = i + 4)
        {
            tempData = (input.charAt(i) & 0XFF)|((input.charAt(i+1) & 0XFF) << 8)| ((input.charAt(i + 2) & 0XFF) << 16)
                        |(input.charAt(i + 3) << 24);
//            System.out.println("temp1: " + tempData);
            tempData *= randVal1;
//            System.out.println("temp2: " + tempData);
            tempData= Integer.rotateLeft(tempData, 12); // Rotate left 12 btis
//            System.out.println("temp3: " + tempData);
            tempData *= randVal2;
//            System.out.println("temp4: " + tempData);
            hashVal ^= tempData;
//            System.out.println("has1: " + hashVal);
            hashVal= Integer.rotateLeft(hashVal, 13); // Rotate left 13 bits
//            System.out.println("has2: " + hashVal);
            hashVal = (hashVal * 5) + 0X46B6456E;
//            System.out.println("has3: " + hashVal);
        }
        // Now collect orphan input characters
        tempData = 0;
        // IF len & 0X03
        if((len & 0X03) == 3)
        {
            tempData = (input.charAt(roundedEnd + 2) & 0XFF) << 16;
//            System.out.println("temp1: " + tempData);
            len = len - 1;
        }
        if((len & 0X03) == 2)
        {
            tempData |= (input.charAt(roundedEnd + 1) & 0XFF) << 8;
//            System.out.println("temp2: " + tempData);
            len = len - 1;
        }
        if((len & 0X03) == 1)
        {
            tempData |= (input.charAt(roundedEnd) & 0XFF);
//            System.out.println("temp3: " + tempData);
            tempData *= randVal1; // Multiply
//            System.out.println("temp4: " + tempData);
            tempData = Integer.rotateLeft(tempData,14); // Rotate left 14 bits
//            System.out.println("temp5: " + tempData);
            tempData *= randVal2; // Another Multiply
//            System.out.println("temp6: " + tempData);
            hashVal ^= tempData;
//            System.out.println("hash1: " + hashVal);
        }
        hashVal ^= len; // XOR
        hashVal &= 0XB6ACBE58; // AND
        hashVal = hashVal ^ hashVal >>> 13;
        hashVal *= 0X53EA2B2C; //Another arbitrary value
        hashVal = hashVal ^ hashVal >>> 16;
        return hashVal; // Return the 32 bit int hash
    }
    // This method will print the complexity indicator.
    public static void complexityIndicator()
    {
        System.err.println("mo723506;3;15");
    }
    public static void main(String[] args) 
    {   
	complexityIndicator();
        File file = new File(args[0]);
        //Opening the .txt file ...
        try {
            Scanner scan = new Scanner(file);
            while (scan.hasNext())
            {
                String input = scan.next();
                int length = input.length();
                int hashValue = hash(input, length);

                System.out.format("%10x:%s\n", hashValue, input);
                //System.out.println(input);
                //System.out.println(input.charAt(i));
                
                //System.out.format("%x\n", (int)input.charAt(0));
                
            }
        } catch(Exception e){
            e.printStackTrace();
        }
        System.out.println("Input file processed");
    }
    
}
