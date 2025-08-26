public class Principal{
    public static void main(String[] args){
        Bomba b = new Bomba("gasolina", 5, 100);
        b.abValor(10);
        b.abLitro(2);
System.out.println("aaaaaaaaaaaaaaaaa");
        b.alValor(6);
        b.abValor(10);
        b.abLitro(2);
         System.out.println("aaaaaaaaaaaaaaaaa");

        b.alLitro(10);
        b.abValor(10);
        b.abLitro(9);

        System.out.println("aaaaaaaaaaaaaaaaa");
        b.abcombo(100);
         b.abValor(10);
        b.abLitro(9);

    }
}