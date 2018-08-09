

import java.util.Random;

import org.junit.Test;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {
		//Brian: we probably only need one of these URLVal objects, so I made it a class variable
		UrlValidator val = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		//Brian: stringbool array is the same as a ResultPair array. I created this class at the end of the 
		//document, because the ResultPair class has an error in it for URLValidatorInCorrect.
		//Failures are commented out, because the test stops on failed assertions
		//I still need to investigate and document the failures
	   StringBool[] manualTestURLs = {new StringBool("http://www.facebook.com", true),
              //fails new StringBool("www.facebook.com", true),
             //fails new StringBool("facebook.com", true),
             //fails  new StringBool("facebook.edu", true),
			   	new StringBool("", false),
	   			new StringBool("a", false)};
               //error new StringBool("a://a.a.a", false),
	   		//fails	new StringBool("http://www.facebook.com/fb", false),
             //fails  new StringBool("www.facebook.com/fb", true),
	   		//fails new StringBool("facebook.com/fb", true),
	   		 //fails new StringBool("facebook.com/fb", true)};
	   		 //fails new StringBool("www.facebook.com/w/index.php", true)};
	   		 //fails new StringBool("www.facebook.com/w/index.php?query=string", true)};
	   		 //fails new StringBool("www.facebook.com/w/index.php?query=string&otherquery=string", true)};
	   		 //fails new StringBool("www.facebook.comwww.facebook.com", true)};
               
	   String partitionTestURL1 = new String("http://www.facebook.com");
 
   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   @Test
   public void testManualTest()
   {
	   
	   //Brian: runs through the array of StringBool objects (aka URL strings and expected t/f outcomes)
	   for(int i = 0; i < manualTestURLs.length; i++) {
		   tryTest(manualTestURLs[i]);
	   }
	   
   }

   @Test
   public void testYourFirstPartition() 
   {
	 //You can use this function to implement your First Partition testing
	   for (int i = 0; i < 2000; i++) {
		   String randomString = scrambleString(partitionTestURL1);
		   StringBool randomSB = new StringBool(randomString, false);
		   printResult(randomSB);
		   tryTest(randomSB);
	   }
	   
   }
   
   @Test
   public void testYourSecondPartition() {
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   @Test
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   
   //Brian: We can use this to test the URLs against our expected results
   public void tryTest(StringBool url) {
		 assertEquals(url.s, url.b, val.isValid(url.s)); 
   }
   
   //Brian: This method is probably unnecessary since running the test shows which url failed if you
   //pass in the string as the first argument
   public void printResult(StringBool url) {
	   System.out.println(url.s + " Expected: " + url.b);
	   
   }
   
   //Brian: This will return a random partition of any string. I wrote this in my first CS class,
   //which is why every line is explained.
   public String scrambleString(String s) 
   {

             Random r = new Random(); //preparing for random number generation
             int wordLength = s.length(); //range within which to generate random number
             StringBuilder fromWord = new StringBuilder(s); //assists with building scrambled word
             StringBuilder toScram = new StringBuilder(); //will become scrambled word
             
             /*The below loop creates the randomized word by generating a random number based on the word length, getting 
              *the character that is within the index location represented by that number, appending that character to 
              *a stringbuilder object, and removing that character from the original word it was taken from so that 
              *it is not selected again.
              */
             while(wordLength > 0) 
             {
               int random = r.nextInt(wordLength); //gets random number
               char letter = fromWord.charAt(random); //gets random character from word
               fromWord.delete(random, random+1); //deletes current random character from word so that the character is not used again
               toScram.append(letter); //adds random character to build scrambled word
               wordLength--; //subtracts from word length to account for the removed character
             }
             String scramWord = toScram.toString(); //assigns final scrambled word to a string
          
          return scramWord; 
        }        
   
   //Brian: I added this class as a working copy of the ResultPair class. Since the one that came with
   //URLValidatorIncorrect always returns the opposite Boolean value
   public class StringBool {
	    public String s;
	    public boolean b;

	    public StringBool(String s, boolean b) {
	       this.s = s;
	       this.b = b;  //Weather the individual part of url is valid.
	    }
	 }

}
