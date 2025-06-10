
public class atividade {

    public static void main(String[] args) {
        int a= 25000;
        int b= 68000;
        int c=0;
        while (a<b) {
            a = a+(a*10/100);
            b = b+(b*2/100);
            c++;
            
        }
        System.out.println(c);
    }
    
}
