class Conta{
      String numero, agencia;
      Titular titular;
      double saldo;

      
    boolean sacar(double valor){

            if (this.saldo>=valor) {
               this.saldo = this.saldo - valor;
    return true;
}
 return false;
      }

      boolean depositar(double valor){
            if(valor>0){
                  this.saldo+=valor;
                  return true;
            }
            return false;

      }

       boolean transfere(Conta conta, double valor){
            return (this.sacar(valor) && conta.depositar(valor));
          

       }

}
class Titular{
      String cpf,nome;

}

public class atividade4 {
      public static void main(String[] args) {
            Conta c1 = new Conta();
            c1.agencia ="352663-3";
            c1.numero ="6363y3t3";
            Titular t1 =new Titular();
            t1.cpf = "2r2533";
            t1.nome ="joao";
            c1.titular =t1;



             Conta c2 = new Conta();
            c2.agencia ="352663-3";
            c2.numero ="6363y3t3";

            System.out.println("saldo"+ c1.saldo);
            c1.depositar(1000);
            System.out.println(c1.saldo);
            c1.sacar(101);
             System.out.println(c1.saldo);
             System.out.println("trafere");
             c1.transfere(c2, 100);
             System.out.println(c2.saldo+"  "+ c1.saldo);
        
      }
}
