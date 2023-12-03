import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class StringComparing {

    static String s;
    static final long magicNum = 479001599;
    static List<Long> stringHash;
    static List<Long> magicDegs;

    static void computeHashes(String s){
        stringHash = new ArrayList<>();
        stringHash.add((long)0);
        magicDegs = new ArrayList<>();
        magicDegs.add((long)1);
        for(int i=0;i<s.length();i++){
            stringHash.add(stringHash.get(i)*magicNum+s.charAt(i));
            magicDegs.add(magicDegs.get(i)*magicNum);
        }
    }
    static boolean checkEntry(int s_l1,int s_r1, int s_l2, int s_r2){
        return stringHash.get(s_r1)-stringHash.get(s_l1)*magicDegs.get(s_r1-s_l1) ==
                stringHash.get(s_r2)-stringHash.get(s_l2)*magicDegs.get(s_r2-s_l2);
    }

    public static void main(String[] args){
        Scanner scanner  = new Scanner(System.in);
        s=scanner.next();
        int m = scanner.nextInt();
        computeHashes(s);
        for(int i=0;i<m;i++){
            System.out.println((
                    checkEntry(scanner.nextInt()-1,scanner.nextInt(),scanner.nextInt()-1,scanner.nextInt())?
                            "Yes":"No"
                    ));
        }
    }
}
