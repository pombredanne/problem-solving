// @JUDGE_ID:  17051CA  424  Java
// @begin_of_source_code
import java.io.*;
import java.util.*;

class Main{

  static String ReadLn (int maxLg){  // utility function to read from stdin
    byte lin[] = new byte [maxLg];
    int lg = 0, car = -1;
    String line = "";
    
    try{
      while (lg < maxLg){
	car = System.in.read();
	if ((car < 0) || (car == '\n')) break;
	lin [lg++] += car;
      }
    } catch (IOException e){
      return (null);
    }
    
    if ((car < 0) && (lg == 0)) return (null);  // eof
    return (new String (lin, 0, lg));
  }
  
  public static void main (String args[]){  // entry point from OS
    Main myWork = new Main();  // create a dinamic instance
    myWork.Begin();            // the true entry point
  }
  
  void Begin(){
    String input;
    StringTokenizer st;
    
    int tmp[];

    while ((input = Main.ReadLn (255)) != null){
      if( input.equals("0") ) return;
      int size = input.length();
      tmp = new int[ size ];
      int k=0;
      for(int i=size-1 ; i>=0 ;i--){
	tmp[k++] = Character.getNumericValue(input.charAt(i));
      } 
      
    }
  }
}
// @end_of_source_code
