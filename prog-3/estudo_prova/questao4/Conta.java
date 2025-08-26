public class Conta {
    private String titular;
    private double saldo;
    

    public void depositar(double valor){
    if(valor>0){
        this.saldo+=valor;
        System.out.println(this.saldo);
    }
}
    public void sacar(double valor){
        if(this.saldo>=valor){
            this.saldo-=valor;
            System.out.println(this.saldo);
        }
    }

    public String gettitular(){
        return titular;
    }

    public void settitular(String titular){
        this.titular = titular;
    }

    public double getsaldo(){
        return saldo;
    }

    public void setsaldo(double saldo){
        this.saldo = saldo;
    }
}
