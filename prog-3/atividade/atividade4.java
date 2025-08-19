
class Conta {
     private String agencia;
     private String numero;
    private double saldo;
     private Titular titular;

    //transferencias de valores

    boolean sacar(double valor) {
        if (this.saldo >= valor && valor > 0){
            this.saldo = this.saldo - valor; //this para referir ao atributo da classe
        return true;
        }
        return false;
    }

    boolean depositar(double valor) {
        if (valor > 0){
            this.saldo += valor;
            return true;
        }
        return false;
    }

    boolean transfere(Conta conta, double valor){
        return this.sacar(valor) && conta.depositar(valor);

    }

    //retornar valores

    public double getSaldo(){
        return this.saldo;
    }

    public String getAgencia(){
        return this.agencia;
    }

    public String getNumero(){
        return this.numero;
    }

    public Titular getTitular(){
        return this.titular;
    }

    //setar valores

    public void setAgencia(String agencia){
        this.agencia = agencia;
    }

    public void setNumero(String numero){
        this.numero = numero;
    }

    public void setTitular(Titular titular){
        this.titular = titular;
    }

    
}
class Titular{
      String cpf,nome;

}

public class atividade4 {
      public static void main(String[] args) {
            Conta c1 = new Conta();
            c1.setAgencia("352663-3");
            c1.depositar(100);
           
        System.out.println(c1.getSaldo());
      }
}
