
import java.net.*;
import java.io.*;
//import org.json.JSONObjec

 class readers{

public static void main(String[] args)throws Exception {
  String[] book;
  book = new String[50];
  String[] chpt;
  chpt = new String[100];
  int i = 0;
  int k = 0;
  BufferedReader br = new BufferedReader(new FileReader("Genesis.txt"));
  try {
    StringBuilder sb = new StringBuilder();
    String line = br.readLine();

    while (line != null) {
      sb.append(line);
      sb.append(System.lineSeparator());
      line = br.readLine();
      chpt[i] = line;
      if(StartsChapter(line)){
        
        chpt = new String[100];
        System.out.println(line);
      }
    }
    String everything = sb.toString();
  } finally {
    br.close();
  }


}

public static boolean StartsChapter(String line){
  //boolean match = true;
  if(line == null || line.length() < 8){
    return false;
  }
  String ch = "CHAPTER ";
  char[] l = line.toCharArray();
  char[] c = ch.toCharArray();
  int i = 0;
  while (i < 8){
    if (l[i] != c[i]) {
      return false;
    }
  i++;
  }
  return true;
}


}
