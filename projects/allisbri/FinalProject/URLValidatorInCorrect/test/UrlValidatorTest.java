

import java.util.Random;

import org.junit.Test;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {
	// Brian: we probably only need one of these URLVal objects, so I made it a
	// class variable
	UrlValidator val = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	String[] query = new String [] {"?test=1" , "", "tests1=true&test2=false"};
	String[] goodPath  = new String[] {"", "/path", "/path", "/path/path", "/1234567"  };
	String[] badPath  = new String[] {"1234567", "//path", "path//path"  };
	String[] goodScheme  = new String[] {"https://", "http://", "ftp://"  };
	String[] badScheme  = new String[] {"https:/", "http//", ""  };
	String[] goodPorts = new String[] {":80", ":1234", "" };
	String[] badPorts = new String[] {"80", ":a1234", ":-1", ":" };
	String[] goodDomain = new String[] {"www.google.com", "www.wikipedia.org", "1.1.1.1" };
	String[] badDomain = new String[] {"www.google.moc", "w3.wikipedia.org", "1.1.1.1.1.1.1.1", "" };
	
	// Brian: stringbool array is the same as a ResultPair array. I created this
	// class at the end of the
	// document, because the ResultPair class has an error in it for
	// URLValidatorInCorrect.
	// Failures are commented out, because the test stops on failed assertions
	// I still need to investigate and document the failures
	StringBool[] manualTestURLs = { // new StringBool("http://www.facebook.com", true),
			//fails bug5
			new StringBool("HTTP://WWW.FACEBOOK.COM", true),
			// fails bug1 because of false return from scheme is null
			//new StringBool("www.facebook.com", true),
			// fails bug2
			// new StringBool("http://", false),
			// error bug3
			// new StringBool("ftp://", false),
			//error bug3 - from partitionTestURL1()
			//new StringBool("bwo.wactec.toophkmfw://", false),
			//error bug4 - from partitionTestURL1()
			//new StringBool("oowph.kwt.cofec://wtbma", false),
			new StringBool(".com", false), new StringBool("/hi", false), 
			new StringBool("", false),
			// fails bug1
			// new StringBool("0.0.0.0", true),
			// fails
			// new StringBool("255.255.255.255", true),
			// passes for the wrong reason, bug1
			new StringBool("256.256.256.256", false),
			// fails bug1
			// new StringBool("facebook.com", true),
			// fails bug1
			// new StringBool("facebook.edu", true),
			new StringBool("", false),

			// error bug4 (similar to bug3)
			// new StringBool("a://a.a.a", false),
			new StringBool("http://www.facebook.com/fb", true),
			// fails bug4
			// new StringBool("http://www.facebook.com/fb/bf", true),
			new StringBool("http://www.facebook.com/fb?a=c&b=d", true),
			new StringBool("http://www.facebook.com/fb?a=c", true),
			// fails bug1
			// new StringBool("www.facebook.com/fb", true),
			// fails bug1
			// new StringBool("facebook.com/fb", true),
			// fails bug1
			// new StringBool("facebook.com/fb", true)};
			// fails bug1
			// new StringBool("www.facebook.com/w/index.php", true)};
			// fails bug1
			// new StringBool("www.facebook.com/w/index.php?query=string", true)};
			// fails bug1
			// new StringBool("www.facebook.com/w/index.php?query=string&otherquery=string",
			// true)};
			// fails bug1
			// new StringBool("www.facebook.comwww.facebook.com", true)};
			new StringBool("a", false) };
	String partitionTestURL1 = new String("http://www.facebook.com/fb?a=c&b=dm");
 
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
	   for (int i = 0; i < 10000000; i++) {
		   int r1;
		   String randomString;
		   do {
			   randomString = scrambleString(partitionTestURL1);
			   r1 = randomString.indexOf("://");
		   } while ((r1 != -1) || (randomString.equalsIgnoreCase("http:/")) || (randomString.equals("http:")));
		   StringBool randomSB = new StringBool(randomString, false);
		   printResult(randomSB);
		   tryTest(randomSB);
	   }
	   
   }
   
   @Test
   public void testYourSecondPartition() {
	   Random r = new Random();
	  
	   
	   
	   for (int i = 0; i < 100; i++) {
		  StringBool[] testStrings = new StringBool[6];
		  
				   
					testStrings[0] = (new StringBool(goodScheme[r.nextInt( goodScheme.length)] + goodDomain[r.nextInt(goodDomain.length)] + goodPorts[r.nextInt(goodPorts.length)] + goodPath[r.nextInt(goodPath.length)] +  query[r.nextInt(query.length)], true));
					testStrings[1] = (new StringBool(badScheme[r.nextInt(badScheme.length)] + goodDomain[r.nextInt(goodDomain.length)] + goodPorts[r.nextInt(goodPorts.length)] + goodPath[r.nextInt(goodPath.length)] +  query[r.nextInt(query.length)], false));
							testStrings[2] =(new StringBool(goodScheme[r.nextInt(goodScheme.length)] + badDomain[r.nextInt(badDomain.length)] + goodPorts[r.nextInt(goodPorts.length)] + goodPath[r.nextInt(goodPath.length)] +  query[r.nextInt(query.length)], false));
									testStrings[3] =(new StringBool(goodScheme[r.nextInt(goodScheme.length)] + goodDomain[r.nextInt(goodDomain.length)] + badPorts[r.nextInt(badPorts.length)] + goodPath[r.nextInt(goodPath.length)] +  query[r.nextInt(query.length)], false));
											testStrings[4] =(new StringBool(goodScheme[r.nextInt(goodScheme.length)] + goodDomain[r.nextInt(goodDomain.length)] + goodPorts[r.nextInt(goodPorts.length)] + badPath[r.nextInt(badPath.length)] +  query[r.nextInt(query.length)], false));
													testStrings[5] = (new StringBool(goodScheme[r.nextInt(goodScheme.length)] + goodDomain[r.nextInt(goodDomain.length)] + goodPorts[r.nextInt(goodPorts.length)] + goodPath[r.nextInt(goodPath.length)], true));
						  
				   
				      
		  for(int j = 0; j <6; j++)
		  {
			  printResult(testStrings[j]);
				try {
			  tryTest(testStrings[j]);  
				}
				catch(AssertionFailedError e)
			   	{
					 System.out.println("Error in partion item " + (j+1));
			   	 System.out.println(e);
			   	}

		  }
		 
	   }




   }
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
             int randomLen = 0;
             while (randomLen == 0) {
            	 randomLen = r.nextInt(wordLength);
             }
             
             /*The below loop creates the randomized word by generating a random number based on the word length, getting 
              *the character that is within the index location represented by that number, appending that character to 
              *a stringbuilder object, and removing that character from the original word it was taken from so that 
              *it is not selected again.
              */
             while(randomLen > 0) 
             {
               int random = r.nextInt(randomLen); //gets random number
               char letter = fromWord.charAt(random); //gets random character from word
               fromWord.delete(random, random+1); //deletes current random character from word so that the character is not used again
               toScram.append(letter); //adds random character to build scrambled word
               randomLen--; //subtracts from word length to account for the removed character
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
